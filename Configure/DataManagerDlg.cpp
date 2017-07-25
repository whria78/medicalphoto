// DataManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataManagerDlg.h"


// CDataManagerDlg dialog

IMPLEMENT_DYNAMIC(CDataManagerDlg, CDialog)

CDataManagerDlg::CDataManagerDlg(boost::asio::io_service &io_service_,config& c_,CMyCout& l_,CWnd* pParent /*=NULL*/)
	: CDialog(CDataManagerDlg::IDD, pParent)
	,data_manager(io_service_,c_,l_)
	,log_(l_)
	,config_(c_)
	,bBuildit(false)
	, bBuildThumb(false)
{

}

CDataManagerDlg::~CDataManagerDlg()
{
}

void CDataManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STATUS, m_StatusList);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}

bool CDataManagerDlg::BuildSQLFileInfo(const _tpath& p,netvolume& netvolume_,bool bCheckExist)
{
	_tformat fmt(_T("[BuildInfo]  :  %s"));
	fmt % p.c_str();
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

void CDataManagerDlg::MakeThumbnail(const tstring& thumbpath,const std::string& stNetPath)
{
	_tformat fmt(_T("[BuildThumbnail]  :  %s"));
	fmt % thumbpath;
	WriteString(fmt.str());

	data_manager::MakeThumbnail(thumbpath,stNetPath);
}

bool CDataManagerDlg::CheckThumbnail(const _tpath& p)
{
	_tformat fmt(_T("[CheckThumbnail]  :  %s"));
	fmt % p.c_str();
	WriteString(fmt.str());

	return data_manager::CheckThumbnail(p);
}
/*
void CDataManagerDlg::BuildMetaTag(const std::string& stNetPath,netvolume& netvolume_)
{
	_tformat fmt(_T("[Collecting meta-data]  :  %s"));
	fmt % MCodeChanger::_CCL(stNetPath);
	WriteString(fmt.str());

	data_manager::BuildMetaTag(stNetPath,netvolume_);
}
*/

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

void CDataManagerDlg::Build_Thread()
{
	boost::mutex::scoped_lock lock(mutex_);

	try
	{
		if (IsAnyEmpty())
			bBuildit=true;

		if (bBuildit)
		{
			CString stText;stText.LoadString(IDS_STRING_DOREBUILD);MessageBox(stText);
			WriteString(_T("### Build Data and Thumbnails"));
			data_manager::BuildSQL();
		}
	}
	catch (std::exception& e)
	{
		log << MCodeChanger::_CCL(e.what()) << log.endl();
		CString stText;stText.LoadString(IDS_STRING_BUILDSQLERR);MessageBox(stText);
	}
	catch (CppSQLite3Exception& e)
	{
		log << MCodeChanger::_CCL(e.errorMessage()) << log.endl();
		CString stText;stText.LoadString(IDS_STRING_BUILDSQLERR);MessageBox(stText);
	}
	catch(...)
	{
		log << _T("BuildSQL Error : Unknown") << log.endl();
		CString stText;stText.LoadString(IDS_STRING_BUILDSQLERR);MessageBox(stText);
	}

	MedicalPhoto_NTService NTService_(config_);
	BOOL bInstallResult=true;
	BOOL bRunResult=true;
	try
	{
		if (NTService_.IsInstalled())
		{
			if (NTService_.IsRunning())
			{
				WriteString(_T("### Stop the Service\n"));
				NTService_.KillService();
			}
			WriteString(_T("### Remove the service previously installed\n"));
			bInstallResult&=NTService_.UnInstall();
		}
		Sleep(1000);
		CString stMsg=_T("### Install a MedicalPhoto Service\n");
		WriteString((LPCTSTR)stMsg);
		
		bInstallResult&=NTService_.Install();

		Sleep(1000);
		WriteString(_T("### Start a Service\n"));
		bRunResult&=NTService_.RunService();

		if (!bRunResult)
			NTService_.UnInstall();
		if (!bRunResult || !bInstallResult)
		{
			CString stText;stText.LoadString(IDS_STRING_SERVICEERR);MessageBox(stText);
			PostMessage(WM_CLOSE,0,0);
			return;
		}
	}
	catch(...)
	{
		CString stText;stText.LoadString(IDS_STRING_SERVICEERR);MessageBox(stText);
		NTService_.UnInstall();
		PostMessage(WM_CLOSE,0,0);
		return;
	}

//인스톨시 thumbnail 을 만드는 부분이나 사용자가 헷갈려하고 인스톨 시간 관계로.. bBuildThumb

	if (bBuildThumb)
	{
		CString stText;
		stText.LoadString(IDS_STRING_ASKTHUMB);

		if (MessageBox(stText,_T("Build Thumbnail"),MB_YESNO)==IDYES)
		{
			try
			{
				data_manager::BuildThumbnail();
			}
			catch (std::exception& e)
			{
				log << MCodeChanger::_CCL(e.what()) << log.endl();
				MessageBox(_T("BuildThumbnail Error"));
			}
			catch (CppSQLite3Exception& e)
			{
				log << MCodeChanger::_CCL(e.errorMessage()) << log.endl();
				MessageBox(_T("BuildThumbnailError"));
			}
			catch(...)
			{
				log << _T("BuildThumbnail Error : Unknown") << log.endl();
				MessageBox(_T("BuildThumbnail Error"));
			}
		}
	}

WriteString(_T("### Finished"));
	Utility::sleep(1000);

	CString stText;
	stText.LoadString(IDS_STRING_YOURIP);
	stText.Replace(_T("localip"),GetLocalIP());
	MessageBox(stText);

	if (!bStopBuildSQL && GetSafeHwnd())
		PostMessage(WM_CLOSE,0,0);
}

CString CDataManagerDlg::GetLocalIP()

{

    WORD wVersionRequested;

    WSADATA wsaData;

    char name[255];

    CString ip; // 여기에 lcoal ip가 저장됩니다.

    PHOSTENT hostinfo;

    wVersionRequested = MAKEWORD( 2, 0 );

 

    if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )

    {

 

        if( gethostname ( name, sizeof(name)) == 0)

        {

              if((hostinfo = gethostbyname(name)) != NULL)

              {

 

                  ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);

 

                }

 

        }      

 

        WSACleanup( );

    }

  return ip;

}


void CDataManagerDlg::WriteString(const tstring& str)
{
	if (!bStopBuildSQL)
	{
		m_StatusList.InsertItem(0,str.c_str(),0);
		if (m_StatusList.GetItemCount()>100)
			m_StatusList.DeleteItem(100);
	}
}

BEGIN_MESSAGE_MAP(CDataManagerDlg, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CANCELBUILD, &CDataManagerDlg::OnBnClickedButtonCancelbuild)
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
	Build();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CDataManagerDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	boost::mutex::scoped_lock lock(mutex_);
	CDialog::OnClose();
}

void CDataManagerDlg::OnBnClickedButtonCancelbuild()
{
	// TODO: Add your control notification handler code here
	CString stText;stText.LoadString(IDS_STRING_ASKEXIT);
	if (MessageBox(stText,_T("Stop and Exit"),MB_YESNO)!=IDYES)
		return;
	StopBuild();
	OnCancel();
}

void CDataManagerDlg::SetProgress(int iMax)
{
	if (!bStopBuildSQL)
		m_Progress.SetRange(0,iMax);
}
void CDataManagerDlg::SetProgressPos(int i)
{
	if (!bStopBuildSQL)
		m_Progress.SetPos(i);
}
void CDataManagerDlg::SetProgressText(const tstring& stText)
{
}
void CDataManagerDlg::SetProgressPos(int i,const tstring& stText)
{
	SetProgressText(stText);
	SetProgressPos(i);
}

BOOL CDataManagerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if( pMsg->message == WM_MOUSEWHEEL )    //스크롤 메세지가 발생했다면
    {
		m_StatusList.SendMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
		return TRUE;
	}
	return __super::PreTranslateMessage(pMsg);
}
