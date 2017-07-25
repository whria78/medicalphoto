// OptionPage1.cpp : implementation file
//

#include "stdafx.h"
#include "WhriaView.h"
#include "OptionPage1.h"


// COptionPage_General dialog

IMPLEMENT_DYNAMIC(COptionPage_General, CDialog)

COptionPage_General::COptionPage_General(client_config& c,CWnd* pParent /*=NULL*/)
	: CDialog(COptionPage_General::IDD, pParent)
	, config_(c)
	, m_IP(c.Get(LAST_HOST_ADDRESS).c_str())
	, m_Passwd(c.Get(LAST_USER_PASSWD).c_str())
	, m_bFilename(c.GetInt(SEARCH_PATH))
	, m_bID(c.GetInt(SEARCH_ID))
	, m_bName(c.GetInt(SEARCH_NAME))
	, m_bDiagnosis(c.GetInt(SEARCH_DIAGNOSIS))
	, m_bICD(c.GetInt(SEARCH_ICD10))
	, m_bComment(c.GetInt(SEARCH_COMMENT))
//	, m_Single_DataFolder(_T(""))
	, m_ChangeFilename(c.GetInt(SUBMIT_AUTOCHANGE_FILENAME))
{
}

COptionPage_General::~COptionPage_General()
{
}

void COptionPage_General::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, m_IP);
	DDX_Text(pDX, IDC_EDIT_PASS, m_Passwd);
	DDX_Check(pDX, IDC_CHECK_SEARCH_FILENAME, m_bFilename);
	DDX_Check(pDX, IDC_CHECK_SEARCH_ID, m_bID);
	DDX_Check(pDX, IDC_CHECK_SEARCH_NAME, m_bName);
	DDX_Check(pDX, IDC_CHECK_SEARCH_DX, m_bDiagnosis);
	DDX_Check(pDX, IDC_CHECK_SEARCH_ICD, m_bICD);
	DDX_Check(pDX, IDC_CHECK_SEARCH_C, m_bComment);
	DDX_Control(pDX, IDC_LIST_DXFILE, m_DxFile);
	DDX_Control(pDX, IDC_LIST_DXACTIVEFILE, m_ActiveDxFile);
//	DDX_Control(pDX, IDC_CHECK_SINGLE_CLIENT, m_SingleClient);
//	DDX_Text(pDX, IDC_EDIT_SINGLE_DATA_FOLDER, m_Single_DataFolder);
	DDX_Check(pDX, IDC_CHECK_SUBMITCHANGE, m_ChangeFilename);
}


BEGIN_MESSAGE_MAP(COptionPage_General, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &COptionPage_General::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON2, &COptionPage_General::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &COptionPage_General::OnBnClickedButton1)
//	ON_BN_CLICKED(IDC_CHECK_SINGLE_CLIENT, &COptionPage_General::OnBnClickedCheckSingleClient)
//	ON_EN_CHANGE(IDC_EDIT_SINGLE_DATA_FOLDER, &COptionPage_General::OnEnChangeEditSingleDataFolder)
END_MESSAGE_MAP()


// COptionPage_General message handlers

void COptionPage_General::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
	if (MessageBox(_T("Save All Changes?"),_T("General Preference"),MB_YESNO)!=IDYES)
	return;

	std::string old_ip=config_.Get(LAST_HOST_ADDRESS);
	UpdateData(TRUE);
	config_.Set(LAST_HOST_ADDRESS,MCodeChanger::_CCU((LPCTSTR)m_IP));
	config_.Set(LAST_USER_PASSWD,MCodeChanger::_CCU((LPCTSTR)m_Passwd));
	config_.Set(SEARCH_PATH,m_bFilename);
	config_.Set(SEARCH_ID,m_bID);
	config_.Set(SEARCH_NAME,m_bName);
	config_.Set(SEARCH_DIAGNOSIS,m_bDiagnosis);
	config_.Set(SEARCH_ICD10,m_bICD);
	config_.Set(SEARCH_COMMENT,m_bComment);
	config_.Set(SUBMIT_AUTOCHANGE_FILENAME,m_ChangeFilename);
//	config_.Set(APP_TYPE,!m_SingleClient.GetCheck());
//	config_.server_config.Set(DATA_PATH
//		,MCodeChanger::_CCU((LPCTSTR)m_Single_DataFolder));

	config_.Set(LOAD_DXCODE_LIST,std::string(""));
	for (int i=0;i<m_ActiveDxFile.GetCount();i++)
	{
		CString temp;
		m_ActiveDxFile.GetText(i,temp);
		config_.Add(LOAD_DXCODE_LIST,MCodeChanger::_CCU((LPCTSTR)temp));
	}

	config_.save();
//	if (m_SingleClient.GetCheck())
//		config_.server_config.save();

//	MessageBeep(MB_ICONEXCLAMATION); // È®ÀÎ

	if (strcmp(old_ip.c_str(),config_.Get(LAST_HOST_ADDRESS).c_str())!=0)
	{
		if (MessageBox(_T("Restart to reconnect [")+m_IP+_T("] now ?"),_T("Restart"),MB_YESNO)!=IDYES)
			return;
		ShellExecute(NULL, _T("open"), MCodeChanger::_CCL(config_.server_config.version_.Get(CLIENT_APP_NAME)).c_str(), NULL, NULL, SW_SHOWNORMAL);
		PostMessage(WM_QUIT,0,0);
	}
}

void COptionPage_General::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	int iSelected=m_ActiveDxFile.GetCurSel();
	if (iSelected==LB_ERR) return;

	CString stItem;
	m_ActiveDxFile.GetText(iSelected,stItem);

	m_DxFile.AddString(stItem);
	m_ActiveDxFile.DeleteString(iSelected);
}

void COptionPage_General::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	int iSelected=m_DxFile.GetCurSel();
	if (iSelected==LB_ERR) return;

	CString stItem;
	m_DxFile.GetText(iSelected,stItem);

	m_ActiveDxFile.AddString(stItem);
	m_DxFile.DeleteString(iSelected);
}

BOOL COptionPage_General::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
//	m_SingleClient.SetCheck(!config_.GetInt(APP_TYPE));

	try
	{
		param_list param_list_;
		config_.SplitParams(LOAD_DXCODE_LIST,param_list_);

		_tpath db_path=bfs::initial_path<_tpath>();
		db_path /= _T("diagnosis");
		for (unsigned int i=0;i<param_list_.size();i++)
		{
			_tpath final_path=db_path;
			tstring item_name=MCodeChanger::_CCL(param_list_[i]);
			final_path /= item_name;
			if (MFile::Exists(final_path) && _tcscmp(MFile::GetFileExtL(item_name).c_str(),_T(".bak"))!=0)
			{
				m_ActiveDxFile.AddString(item_name.c_str());
			}
		}
		
		_tdirectory_iterator end_iter;

		for ( _tdirectory_iterator dir_itr( db_path );
		  dir_itr != end_iter;
		  ++dir_itr )
		{
			if (!bfs::is_directory(*dir_itr))
			{
				bool bExist=false;
				for (unsigned int i=0;i<param_list_.size();i++)
				{
					_tpath final_path=db_path;
					tstring item_name=MCodeChanger::_CCL(param_list_[i]);
					final_path /= item_name;
					tstring param_string=final_path.c_str();
					tstring path_string=dir_itr->path().c_str();
					boost::algorithm::to_lower(param_string);
					boost::algorithm::to_lower(path_string);
					if (_tcscmp(param_string.c_str(),path_string.c_str())==0)
					{
						bExist=true;break;
					}
				}
				if (!bExist)
				{
					tstring stAdd=_tpath(*dir_itr).c_str();
					if (DxDB::IsDBFile(stAdd.c_str())  && _tcscmp(MFile::GetFileExtL(stAdd).c_str(),_T(".bak"))!=0)
						m_DxFile.AddString(MFile::GetFileNameL(stAdd).c_str());
				}
			}
		}
	}
	catch (std::exception & e)
	{
		config_.log << MCodeChanger::_CCW(e.what()) << config_.log.endl();
	}

	UpdateStatus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
/*
void COptionPage_General::OnBnClickedCheckSingleClient()
{
	// TODO: Add your control notification handler code here
	UpdateStatus();
	if (m_SingleClient.GetCheck())
	{
		CString dumy=ChooseFolder();
		if (dumy!=_T(""))
			m_Single_DataFolder=dumy;
		UpdateData(FALSE);
	}
}
*/
void COptionPage_General::UpdateStatus()
{
	/*
	if (m_SingleClient.GetCheck())
	{
		GetDlgItem(IDC_EDIT_SINGLE_DATA_FOLDER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_IP)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_PASS)->EnableWindow(false);
		m_Single_DataFolder=MCodeChanger::_CCL(config_.server_config.Get(DATA_PATH)).c_str();
		if (m_Single_DataFolder==_T(""))
			m_Single_DataFolder=ChooseFolder(_T("Select Data Folder"));
	}
	*/
//	else
//	{
//	GetDlgItem(IDC_EDIT_SINGLE_DATA_FOLDER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_IP)->EnableWindow(true);
	if (!config_.server_config.GetInt(MULTIUSER_SUPPORT))
	{
		GetDlgItem(IDC_EDIT_PASS)->EnableWindow(false);
	}
	else
	{
		GetDlgItem(IDC_EDIT_PASS)->EnableWindow(true);
	}
//	m_Single_DataFolder=_T("");
//	}
	UpdateData(FALSE);
}

CString COptionPage_General::ChooseFolder(const CString& stTitle)
{
	TCHAR szFolder[MAX_PATH*2];
	szFolder[0] = _T('\0');
	CString csResult;

	TCHAR szPath[MAX_PATH*2];
	SHGetSpecialFolderPath(NULL, szPath, CSIDL_DRIVES, FALSE);

	BOOL bRet = XBrowseForFolder(m_hWnd
		,szPath
		,NULL
		,stTitle
		,szFolder
		,sizeof(szFolder)/sizeof(TCHAR)-2
		,FALSE);
	if (bRet) csResult.Format(_T("%s"),szFolder);
	else
		csResult=_T("");
//	csResult.Replace(_T("\\"),_T("/"));
	return csResult;
}
/*
void COptionPage_General::OnEnChangeEditSingleDataFolder()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	OnBnClickedCheckSingleClient();
}
*/
BOOL COptionPage_General::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    if (pMsg->message == WM_KEYDOWN)
    {
		if (pMsg->wParam == VK_ESCAPE)
		{
			GetParent()->PostMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
			return TRUE;
		}
		if (pMsg->wParam == 13)
		{
			if (GetFocus()==GetDlgItem(IDC_EDIT_IP))
			{
				OnBnClickedButtonSave();
				return TRUE;
			}
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
