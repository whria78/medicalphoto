// DataManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataManagerDlg.h"


// CDataManagerDlg dialog

IMPLEMENT_DYNAMIC(CDataManagerDlg, CDialog)

CDataManagerDlg::CDataManagerDlg(config& c_,CMyCout& l_,CWnd* pParent /*=NULL*/)
	: CDialog(CDataManagerDlg::IDD, pParent)
	,data_manager(c_,l_)
	,log_(l_)
	,bStopThread(false)
	,bStartThread(false)
{

}

CDataManagerDlg::~CDataManagerDlg()
{
}

void CDataManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STATUS, m_StatusList);
}

bool CDataManagerDlg::BuildSQLFileInfo(const _tpath& p,netvolume& netvolume_,bool bCheckExist)
{
	_tformat fmt(_T("[BuildInfo]  :  %s"));
	fmt % p.native_directory_string();
	WriteString(fmt.str());

	return data_manager::BuildSQLFileInfo(p,netvolume_,bCheckExist);
}
void CDataManagerDlg::CheckSQLFileInfo(const std::string& stNetPath,netvolume& netvolume_)
{
	_tformat fmt(_T("[CheckInfo]  :  %s"));
	fmt % MCodeChanger::_CCL(stNetPath);
	WriteString(fmt.str());

	data_manager::CheckSQLFileInfo(stNetPath,netvolume_);
}
void CDataManagerDlg::BuildThumbnail(const std::string& stNetPath,netvolume& netvolume_)
{
	_tformat fmt(_T("[BuildThumbnail]  :  %s"));
	fmt % MCodeChanger::_CCL(stNetPath);
	WriteString(fmt.str());

	data_manager::BuildThumbnail(stNetPath,netvolume_);
}
bool CDataManagerDlg::CheckThumbnail(const _tpath& p)
{
	_tformat fmt(_T("[CheckThumbnail]  :  %s"));
	fmt % p.native_directory_string();
	WriteString(fmt.str());

	return data_manager::CheckThumbnail(p);
}
void CDataManagerDlg::BuildMetaTag(const std::string& stNetPath,netvolume& netvolume_)
{
	_tformat fmt(_T("[Collecting meta-datas]  :  %s"));
	fmt % MCodeChanger::_CCL(stNetPath);
	WriteString(fmt.str());

	data_manager::BuildMetaTag(stNetPath,netvolume_);
}

void CDataManagerDlg::StopBuild()
{
	WriteString(_T("### Stop ###"));
	data_manager::StopBuild();
//	boost::mutex::scoped_lock lock(mutex_);
}

void CDataManagerDlg::Build()
{
	boost::thread BuildThread(boost::bind(&CDataManagerDlg::Build_Thread,this));
}
void CDataManagerDlg::BuildSQL()  // non-thread
{
	boost::thread BuildThread(boost::bind(&CDataManagerDlg::BuildSQL_Thread,this));
}
void CDataManagerDlg::BuildThumbnail()  // non-thread
{
	boost::thread BuildThread(boost::bind(&CDataManagerDlg::BuildThumbnail_Thread,this));
}

void CDataManagerDlg::Build_Thread()
{
	boost::mutex::scoped_lock lock(mutex_);

	while (!bStartThread)
	{
		Utility::sleep(100);
	}
	WriteString(_T("### Start to Build All ###"));
	data_manager::Build();
	WriteString(_T("### End ###"));
	Utility::sleep(100);
	PostMessage(WM_CLOSE,0,0);

}
void CDataManagerDlg::BuildSQL_Thread()
{
	boost::mutex::scoped_lock lock(mutex_);

	while (!bStartThread)
	{
		Utility::sleep(100);
	}
	WriteString(_T("### Start to Collect File Informations ###"));
	data_manager::BuildSQL();

	WriteString(_T("### End ###"));
	Utility::sleep(100);
	PostMessage(WM_CLOSE,0,0);
}
void CDataManagerDlg::BuildThumbnail_Thread()
{
	boost::mutex::scoped_lock lock(mutex_);

	while (!bStartThread)
	{
		Utility::sleep(100);
	}
	WriteString(_T("### Start to Build Thumbnails ###"));
	data_manager::BuildThumbnail();

	WriteString(_T("### End ###"));
	Utility::sleep(100);
	PostMessage(WM_CLOSE,0,0);
}

void CDataManagerDlg::WriteString(const tstring& str)
{
	m_StatusList.InsertItem(0,str.c_str(),0);
	if (m_StatusList.GetItemCount()>100)
		m_StatusList.DeleteItem(100);
}

BEGIN_MESSAGE_MAP(CDataManagerDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CDataManagerDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CDataManagerDlg message handlers

BOOL CDataManagerDlg::OnInitDialog()
{
	__super::OnInitDialog();

	// TODO:  Add extra initialization here

	RECT listRect;
	m_StatusList.GetClientRect(&listRect);
	int nListWidth = (listRect.right - listRect.left);

	m_StatusList.InsertColumn(0,_T("Message"),LVCFMT_LEFT, nListWidth*2);
	m_StatusList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0);

	data_manager::initiate();
	WriteString(_T("### Loading... It will take several minutes ###"));
	bStartThread=true;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDataManagerDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	if (MessageBox(_T("Are you sure to stop the process ?"),_T("Stop"),MB_YESNO)!=IDYES)
		return;
	StopBuild();
}
/*
void CDataManagerDlg::Exit(bool bResult)
{
	data_manager::StopBuild();
	if (bResult)
		OnOK();
	else
		OnCancel();
}
*/
void CDataManagerDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	boost::mutex::scoped_lock lock(mutex_);
	EndDialog(0);
//	__super::OnClose();
}
