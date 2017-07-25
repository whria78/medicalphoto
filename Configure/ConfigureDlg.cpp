// ConfigureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Configure.h"
#include "ConfigureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CConfigureDlg dialog



CConfigureDlg::CConfigureDlg(config &c,CWnd* pParent /*=NULL*/)
	: CDialog(CConfigureDlg::IDD, pParent)
	,iPosition(0)
	,config_(c)
	,DataIntegrity(c)
	,Others(c)
	,SelectFolders(c)
	,bExpress(false)
	,bExecuteMonitor(false)
	, bBuildThumb(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConfigureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConfigureDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CConfigureDlg::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CConfigureDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDOK, &CConfigureDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CConfigureDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CConfigureDlg message handlers

BOOL CConfigureDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

   LPWSTR *szArglist;
   int nArgs;

   bool bInstall = false;
   bool bStart = false;
   bool bStop = false;

   szArglist = CommandLineToArgvW(GetCommandLine(), &nArgs);
   if( NULL != szArglist && nArgs>1)
   {
	   if (_tcscmp(szArglist[1], _T("restart")) == 0)
		   bExecuteMonitor = true;
	   if (_tcscmp(szArglist[1], _T("buildthumb")) == 0)
		   bBuildThumb = true;
	   if (_tcscmp(szArglist[1], _T("install")) == 0)
		   bInstall = true;
	   if (_tcscmp(szArglist[1], _T("start")) == 0)
		   bStart = true;
	   if (_tcscmp(szArglist[1], _T("stop")) == 0)
		   bStop = true;
   }
   if (NULL != szArglist && nArgs >2)
   {
	   if (_tcscmp(szArglist[2], _T("restart")) == 0)
		   bExecuteMonitor = true;
	   if (_tcscmp(szArglist[2], _T("buildthumb")) == 0)
		   bBuildThumb = true;
   }

   LocalFree(szArglist);


   // INSTALL , START, STOP

   MedicalPhoto_NTService NT_(config_);

   if (bInstall)
   {
	   Utility::sleep(1000);

	   if (NT_.IsInstalled())
	   {
		   if (NT_.CheckService() == false)
		   {
			   config_.log.SetFlag(true);
			   config_.log << _T("... Remove Old Service\n");

			   if (NT_.IsRunning())
			   {
				   config_.log << (_T("... Stop Old Service\n"));
				   NT_.KillService();
			   }
			   if (NT_.UnInstall() == false)
			   {
				   MessageBox(_T("... Fail to Remove old Service. Please reinstall MedicalPhoto."));
				   EndDialog(0);
				   return TRUE;
			   }

			   ShellExecute(NULL, _T("open")
				   , MCodeChanger::_CCL(config_.version_.Get(CONFIG_FILE_NAME)).c_str()
				   , _T("install"), NULL, SW_SHOW);

			   EndDialog(0);
			   return TRUE;
		   }
	   }
	   else
	   {
		   config_.log.SetFlag(true);
		   config_.log << _T("... Install Service\n");

		   if (NT_.Install() == false)
		   {
			   config_.log.SetFlag(true);
			   config_.log << _T("... Fail to Install Service\n");
			   MessageBox(_T("... Fail to Install Service. Please reinstall MedicalPhoto."));
			   EndDialog(0);
			   return TRUE;
		   }

		   if (NT_.IsInstalled())
		   {
			   Sleep(1000);
			   NT_.RunService();
		   }
	   }
	   EndDialog(0);
	   return TRUE;
   }

   if (bStart)
   {
	   NT_.RunService();
	   EndDialog(0);
	   return TRUE;
   }

   if (bStop)
   {
	   NT_.KillService();
	   EndDialog(0);
	   return TRUE;
   }
   
   // AUTOUPDATE
	CAutoUpdater updater;
	CString stResult=updater.IsUpdateExist(SERVERUPDATEADDRESS);
	if (!stResult.IsEmpty())
	{
		CUpdateDlg m_dlg;
		m_dlg.CheckForUpdate(SERVERUPDATEADDRESS);
		m_dlg.DoModal();
		CAutoUpdater::ErrorType error=m_dlg.UpdateErrorType;

//		CAutoUpdater::ErrorType error=updater.CheckForUpdate(SERVERUPDATEADDRESS);

		if (CAutoUpdater::Success == error)
		{
		}
		else if (CAutoUpdater::UpdateNotComplete == error)
		{
		}
		else
		{
			CString stText;stText.LoadString(IDS_STRING_FAILUPDATE);
			MessageBox(stText,_T("Updater"), MB_ICONINFORMATION|MB_OK);
		}
	}

	SelectFolders.Create(IDD_DIALOG_PATHS, this);
	DataIntegrity.Create(IDD_DIALOG_DATAINTEGRITY, this);
	Others.Create(IDD_DIALOG_OTHERS, this);

	// 간단한 configure 를 위해 항상 express 모드로
	//bExpress=true;

	if (bExpress)
	{
		iPosition=0;
		GetDlgItem(IDC_BUTTON_PREV)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_NEXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDOK)->ShowWindow(SW_SHOW);
		SelectFolders.ShowWindow(SW_SHOW);
	}
	else
	{
		iPosition=0;UpdatePos();
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CConfigureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CConfigureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CConfigureDlg::OnBnClickedButtonPrev()
{
	// TODO: Add your control notification handler code here
	if (iPosition==0 && SelectFolders.m_PicturePath==_T(""))
	{
		CString stText;stText.LoadString(IDS_STRING_SELECTPHOTO);MessageBox(stText);
		return;
	}
	if (iPosition==0 && !MFile::IsDirL((LPCTSTR)SelectFolders.m_PicturePath))
	{
		CString stText;stText.LoadString(IDS_STRING_INVALIDFOLDER);MessageBox(stText);
		return;
	}

	iPosition--;

	if (iPosition==1)
		iPosition--;

	UpdatePos();
	if (iPosition==0)
		GetDlgItem(IDC_BUTTON_PREV)->ShowWindow(SW_HIDE);
	else
		GetDlgItem(IDC_BUTTON_PREV)->ShowWindow(SW_SHOW);
}

void CConfigureDlg::OnBnClickedButtonNext()
{
	// TODO: Add your control notification handler code here
	DataIntegrity.UpdateData(TRUE);
	Others.UpdateData(TRUE);
	SelectFolders.UpdateData(TRUE);

	if (iPosition==0)
	{
		tstring stErrorMsg;
		if (!data_manager::CheckValidPicturePath((LPCTSTR)SelectFolders.m_PicturePath,stErrorMsg))
		{
			MessageBox(stErrorMsg.c_str());
			return;
		}
	}
	iPosition++;

	if (iPosition==1)
		iPosition++;

	UpdatePos();
	if (iPosition==2)
	{
		GetDlgItem(IDC_BUTTON_NEXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDOK)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_NEXT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	}
}

void CConfigureDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	DataIntegrity.UpdateData(TRUE);
	Others.UpdateData(TRUE);
	SelectFolders.UpdateData(TRUE);

	if (iPosition==0)
	{
		tstring stErrorMsg;
		if (!data_manager::CheckValidPicturePath((LPCTSTR)SelectFolders.m_PicturePath,stErrorMsg))
		{
			MessageBox(stErrorMsg.c_str());
			return;
		}
	}

	int iOldThumbHeight=config_.GetInt(THUMB_HEIGHT);
	int iOldThumbWidth=config_.GetInt(THUMB_WIDTH);

	// dataintegrity
	config_.Set(BACKUP_PATH,MCodeChanger::_CCU((LPCTSTR)DataIntegrity.m_BackupFolder));
	config_.Set(STARTUP_CHECK_DB,DataIntegrity.m_CheckDB_Start);
	config_.Set(SCHEDULE_BUILD_DATE,DataIntegrity.iSchedule1);
	config_.Set(SCHEDULE_BUILD_TIME,DataIntegrity.iSchedule2);
	config_.Set(SCHEDULE_CHECK_DATE,DataIntegrity.iCheck1);
	config_.Set(SCHEDULE_CHECK_TIME,DataIntegrity.iCheck2);
	config_.Set(BACKUP_DATE,DataIntegrity.iBackupTime1);
	config_.Set(BACKUP_TIME,DataIntegrity.iBackupTime2);

	// others
	config_.Set(THUMB_HEIGHT,Others.m_Thumb_Height);
	config_.Set(THUMB_WIDTH,Others.m_Thumb_Width);
	config_.Set(HOSPITAL_NAME,MCodeChanger::_CCU((LPCTSTR)Others.m_HospitalName));
	config_.Set(MINIMIZE,Others.m_bMinimize);
//	config_.Set(NTSERVICE,Others.m_bNTService);


//	config_.Set(ADMIN_PASS,MCodeChanger::_CCU((LPCTSTR)m_SuperAdminPasswd));
//	config_.Set(AUTO_START,m_bAutostart);

	// selectfolders

	config_.Set(DATA_PATH,MCodeChanger::_CCU((LPCTSTR)SelectFolders.m_PicturePath));
	config_.Set(DATA_ROOT_PATH,MCodeChanger::_CCU((LPCTSTR)SelectFolders.m_DataRootPath));
	config_.Set(FAVORATE_PATH,MCodeChanger::_CCU((LPCTSTR)SelectFolders.m_FavoratePath));
	config_.Set(THUMB_PATH,MCodeChanger::_CCU((LPCTSTR)SelectFolders.m_ThumbnailPath));
	config_.Set(TMP_PATH,MCodeChanger::_CCU((LPCTSTR)SelectFolders.m_TmpPath));
/*	config_.RefinePath(DATA_PATH);
	config_.RefinePath(FAVORATE_PATH);
	config_.RefinePath(THUMB_PATH);
	config_.RefinePath(DATA_ROOT_PATH);
	config_.RefinePath(TMP_PATH);
*/
	config_.save();

	if (iOldThumbHeight!=config_.GetInt(THUMB_HEIGHT)
		|| iOldThumbWidth!=config_.GetInt(THUMB_WIDTH))
	{
		MFile::DeleteAllL(MCodeChanger::_CCL(config_.Get(THUMB_PATH)));
	}

	HWND hwnd = ::FindWindow(_T("MedicalPhotoServer"), NULL);
	if (hwnd!=NULL)
		::PostMessage(hwnd,WM_QUIT,0,0);

	boost::asio::io_service io_service_;
	CDataManagerDlg DataManagerDlg(io_service_, config_, config_.log); 
	DataManagerDlg.SetBuildThumb(bBuildThumb);
	DataManagerDlg.DoModal();



// 별로 안 중요해서 생략
/*	if (DataManagerDlg.bBuildit && !bExecuteMonitor)
	{
		CApptype m_dlg;
		m_dlg.DoModal();
	}
*/
	if (bExecuteMonitor)
		ShellExecute(NULL,_T("open")
			,MCodeChanger::_CCL(config_.version_.Get(SERVER_APP_NAME)).c_str()
			,_T("nomin"),NULL,SW_SHOW);
	OnOK();
}

void CConfigureDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	if (bExecuteMonitor)
		ShellExecute(NULL,_T("open")
			,MCodeChanger::_CCL(config_.version_.Get(SERVER_APP_NAME)).c_str()
			,_T("nomin"),NULL,SW_SHOW);
	OnCancel();
}

void CConfigureDlg::UpdatePos()
{
	if (iPosition==0)
		SelectFolders.ShowWindow(SW_SHOW);
	else
		SelectFolders.ShowWindow(SW_HIDE);

	if (iPosition==1)
		DataIntegrity.ShowWindow(SW_SHOW);
	else
		DataIntegrity.ShowWindow(SW_HIDE);

	if (iPosition==2)
		Others.ShowWindow(SW_SHOW);
	else
		Others.ShowWindow(SW_HIDE);

	if (iPosition==0)
		GetDlgItem(IDC_BUTTON_PREV)->ShowWindow(SW_HIDE);
	else
		GetDlgItem(IDC_BUTTON_PREV)->ShowWindow(SW_SHOW);
	if (iPosition==1)
	{
		GetDlgItem(IDC_BUTTON_PREV)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_NEXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	}
	if (iPosition==2)
	{
		GetDlgItem(IDC_BUTTON_NEXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDOK)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_NEXT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	}

	/*
	if (iPosition==3)
		DataManager.ShowWindow(SW_SHOW);
	else
		DataManager.ShowWindow(SW_HIDE);
	*/
}
