// MedicalPhotoServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MedicalPhotoServer.h"
#include "MedicalPhotoserverdlg.h"

#include "Sddl.h"
#include <initguid.h>
#include <stdio.h>
#include <sys/stat.h>
#include <Accctrl.h>
#include <Aclapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CTrayDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CTrayDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CTrayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}




BEGIN_MESSAGE_MAP(CAboutDlg, CTrayDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedicalPhotoServerDlg dialog

CMedicalPhotoServerDlg::CMedicalPhotoServerDlg(config& c_,CWnd* pParent /*=NULL*/)
	: CTrayDialog(CMedicalPhotoServerDlg::IDD, pParent)
	,log_(m_Log)
	,config_(c_)
//	,server_(config_,connection_manager_)
	,connection_manager_(m_StateList,config_)
//	,data_manager_(config_,log_)
	,m_Folder(MCodeChanger::_CCL(c_.Get(DATA_PATH)).c_str())
//	,log_server_(c_.GetInt(LOG_PORT))
{
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMedicalPhotoServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CTrayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedicalPhotoServerDlg)
	DDX_Control(pDX, IDC_LIST_LOG, m_Log);
	DDX_Text(pDX, IDC_EDIT_FOLDER, m_Folder);
	DDX_Control(pDX, IDC_LIST_STATE, m_StateList);
}

BEGIN_MESSAGE_MAP(CMedicalPhotoServerDlg, CTrayDialog)
	//{{AFX_MSG_MAP(CMedicalPhotoServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
//	ON_COMMAND(ID_TRAY_START, OnMenuitemStart)
//	ON_COMMAND(ID_TRAY_STOP, OnMenuitemStop)
	ON_COMMAND(ID_MENUITEM_EXIT, OnMenuitemExit)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
//	ON_STN_CLICKED(IDC_STATIC_CHECK, &CMedicalPhotoServerDlg::OnStnClickedStaticCheck)
	ON_BN_CLICKED(IDC_BUTTON_OPTION, &CMedicalPhotoServerDlg::OnBnClickedButtonOption)
	ON_COMMAND(ID_TRAY_START, &CMedicalPhotoServerDlg::OnTrayStart)
	ON_COMMAND(ID_TRAY_STOP, &CMedicalPhotoServerDlg::OnTrayStop)
	ON_WM_COPYDATA()
	ON_COMMAND(ID_TRAY_OPEN, &CMedicalPhotoServerDlg::OnTrayOpen)
	ON_BN_CLICKED(IDC_BUTTON_CHECKDATA, &CMedicalPhotoServerDlg::OnBnClickedButtonCheckdata)
	ON_BN_CLICKED(IDC_BUTTON_RELOADLOG, &CMedicalPhotoServerDlg::OnBnClickedButtonReloadlog)
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedicalPhotoServerDlg message handlers

BOOL CMedicalPhotoServerDlg::OnInitDialog()
{
	CTrayDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	} 

//	CViewLogo m_ViewDlg;
//	m_ViewDlg.DoModal();
//	m_ViewDlg.CloseWindow();

//	m_ViewDlg.Create(IDD_DIALOG_VIEWLOGO);
//	m_tabPages[1]->Create(IDD_DIALOG_CUSTOMDX, this);
//	m_ViewDlg.ShowWindow(SW_SHOW);
//	m_tabPages[1]->ShowWindow(SW_HIDE);
//	m_ViewDlg.m_Logo.ShowWindow(SW_SHOW);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here







	LPWSTR *szArglist;
	int nArgs;
	bool bNotMinimize = false;
	bool bRestart = false;

	szArglist = CommandLineToArgvW(GetCommandLine(), &nArgs);
	if (NULL != szArglist && nArgs == 2)
	{
		if (_tcscmp(szArglist[1], _T("nomin")) == 0)
			bNotMinimize = true;
		if (_tcscmp(szArglist[1], _T("restart")) == 0)
			bRestart = true;
	}

	LocalFree(szArglist);


	if (bRestart == false)
	{
		// MUTEX

		HANDLE hMutex = NULL;
		hMutex = CreateMutex(NULL, FALSE, _T("MedicalPhotoServer"));

		if (ERROR_ALREADY_EXISTS == ::GetLastError()) {

			AfxMessageBox(_T("MedicalPhoto Server Commander is already running."));
			CloseHandle(hMutex);
			exit(1);
		}
	}
	else
	{
		Utility::sleep(2000);
	}
	
	HANDLE    hMemMap = NULL;
	HWND* lpMapping=NULL;
	
	HANDLE hMap = NULL;
	DWORD dwError = 0;
	DWORD dwRes = 0;
	PSID pEveryoneSID = NULL;
	PACL pACL = NULL;
	PSECURITY_DESCRIPTOR pSD = NULL;
	EXPLICIT_ACCESS ea;
	SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
	SECURITY_ATTRIBUTES sa;
	OSVERSIONINFO osvi;

	if (!AllocateAndInitializeSid(&SIDAuthWorld, 1,
		SECURITY_WORLD_RID,
		0, 0, 0, 0, 0, 0, 0,
		&pEveryoneSID)
		) {
//		printDebugLog("AllocateAndInitializeSid Error %u\n", GetLastError());
//		goto Cleanup;
	}

	// Initialize an EXPLICIT_ACCESS structure for an ACE.
	// The ACE will allow Everyone all access to the shared memory object.
	ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));
	ea.grfAccessPermissions = FILE_MAP_ALL_ACCESS;
	ea.grfAccessMode = SET_ACCESS;
	ea.grfInheritance = NO_INHERITANCE;
	ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
	ea.Trustee.ptstrName = (LPTSTR)pEveryoneSID;

	// Create a new ACL that contains the new ACEs.
	dwRes = SetEntriesInAcl(1, &ea, NULL, &pACL);
	if (ERROR_SUCCESS != dwRes) {
//		fprintf(stderr, "SetEntriesInAcl Error %u\n", GetLastError());
//		goto Cleanup;
	}

	// Initialize a security descriptor.  
	pSD = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
	if (NULL == pSD) {
//		printDebugLog("LocalAlloc Error %u\n", GetLastError());
//		goto Cleanup;
	}

	if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION)) {
//		printDebugLog("InitializeSecurityDescriptor Error %u\n", GetLastError());
//		goto Cleanup;
	}

	// Add the ACL to the security descriptor. 
	if (!SetSecurityDescriptorDacl(pSD,
		TRUE,     // bDaclPresent flag   
		pACL,
		FALSE) // not a default DACL 
		) {
//		printDebugLog("SetSecurityDescriptorDacl Error %u\n", GetLastError());
//		goto Cleanup;
	}

	// Initialize a security attributes structure.
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = pSD;
	sa.bInheritHandle = FALSE;

	hMemMap = CreateFileMapping(INVALID_HANDLE_VALUE, &sa, PAGE_READWRITE, 0,16,_T("Global\\MedicalPhotoServerHWND"));

	if (hMemMap != NULL)
	{
		// 파일에 매핑하기
		lpMapping = (HWND*)MapViewOfFile(hMemMap,FILE_MAP_ALL_ACCESS,0,0,0);
		*lpMapping = AfxGetApp()->m_pMainWnd->GetSafeHwnd();
		UnmapViewOfFile(lpMapping);
	}
	

	// TRAY 에 보내기

    TraySetIcon(IDR_MAINFRAME);
	TraySetToolTip(_T("MedicalPhoto Server"));
    TraySetMenu(IDR_MENU_TRAY);


	// config load && version
	config_.load();
#ifdef _DEBUG
	config_.version_.increase_version(SERVER_VERSION);
#endif



	// 만약 startup 시 minimize 라면
	if (config_.GetInt(MINIMIZE) && bNotMinimize==false) 
		PostMessage(WM_SYSCOMMAND, SC_MINIMIZE);
	// configuration loading
//	GetDlgItem(IDC_BUTTON_START) -> EnableWindow(FALSE);
//	GetDlgItem(IDC_BUTTON_STOP) -> EnableWindow(FALSE);
//	TrayMenuDisable(ID_TRAY_STOP);
//	TrayMenuDisable(ID_TRAY_START);


	// Data Path Setup

	bool bForceReBuild=false;
	m_Folder=MCodeChanger::_CCL(config_.Get(DATA_PATH)).c_str();

	if (m_Folder==_T(""))
	{
		ShellExecute(NULL, _T("open")
			, CONFIG_EXE_FILENAME
			, _T("restart"), NULL, SW_SHOW);
		Exit();
		return TRUE;
	}
/*
	{
		MessageBox(_T("Select Photographic Folder"));
		m_Folder=ChooseFolder();
		if (m_Folder!=_T(""))
		{
			config_.Set(DATA_PATH,MCodeChanger::_CCU((LPCTSTR)m_Folder));
			config_.save();
			MessageBox(_T("Memorize Your IP Address : ")+GetLocalIP());
			bForceReBuild=true;
		}
		else
		{
			MessageBox(_T("You Must Select an Image Folder"));
			EndDialog(0);
			return FALSE;
		}
	}
*/

	// Initiate Control
	log_.InitiateCtrl();
	connection_manager_.InitiateCtrl();

	OnBnClickedButtonReloadlog();

	m_Log.InsertItem(0,_T(""),0);
	m_Log.InsertItem(0,_T(""),0);
	m_Log.InsertItem(0,_T("MedicalPhoto version ")+CString(MCodeChanger::_CCL(config_.version_.Get(VERSION_FILE_VERSION)).c_str()),1);

	CAutoUpdater updater;
	CString stResult=updater.IsUpdateExist(SERVERUPDATECHECKADDRESS);
	if (!stResult.IsEmpty())
	{
		m_Log.InsertItem(0,_T("Update is available : version ")+stResult,1);
		m_Log.InsertItem(0,_T("Download the last release : http://medicalphoto.org"),1);
	}


	// IP Listing 얻기
	m_Log.InsertItem(0,_T("Host Addresses : ")+GetLocalIP(),1);

	UpdateData(FALSE);

	// Initiate Server
	if (m_Folder!=_T(""))
	{
		MedicalPhoto_NTService NT_(config_);
		/*
		if (NT_.IsInstalled())
		{
			if (NT_.CheckService() == false)
			{
				log_.SetFlag(true);
				log_ << _T("... Remove Old Service\n");

				if (NT_.IsRunning())
				{
					log_ << (_T("### Stop the Service\n"));
					NT_.KillService();
				}
				log_ << (_T("### Remove the service previously installed\n"));
				if (NT_.UnInstall() == false)
				{
					MessageBox(_T("... Fail to Remove old Service. Recommend to reinstall MedicalPhoto."));
					Exit();
					return TRUE;
				}

				ShellExecute(NULL, _T("open")
					, MCodeChanger::_CCL(config_.version_.Get(SERVER_APP_NAME)).c_str()
					, _T("restart"), NULL, SW_SHOW);

				Exit();
				return TRUE;

			}
		}
		*/
		if (NT_.IsInstalled()==false)
		{
			log_.SetFlag(true);
			log_ << _T("... Install Service\n");


			SHELLEXECUTEINFO ShExecInfo = { 0 };
			ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
			ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
			ShExecInfo.hwnd = NULL;
			ShExecInfo.lpVerb = NULL;
			ShExecInfo.lpFile = CONFIG_EXE_FILENAME;
			ShExecInfo.lpParameters = _T("install");
			ShExecInfo.lpDirectory = NULL;
			ShExecInfo.nShow = SW_SHOW;
			ShExecInfo.hInstApp = NULL;
			ShellExecuteEx(&ShExecInfo);
			WaitForSingleObject(ShExecInfo.hProcess, INFINITE);


			if (NT_.IsInstalled()==false)
			{
				log_.SetFlag(true);
				log_ << _T("... Fail to Install Service\n");
				MessageBox(_T("... Fail to Install Service. Recommend to reinstall MedicalPhoto."));
				Exit();
				return TRUE;
			}
		}

//		Sleep(1000);
		if (NT_.IsRunning())
		{
			GetDlgItem(IDC_BUTTON_START) -> EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_STOP) -> EnableWindow(TRUE);
			TrayMenuDisable(ID_TRAY_START);
			TrayMenuEnable(ID_TRAY_STOP);
		}
		else
		{
			GetDlgItem(IDC_BUTTON_START) -> EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_STOP) -> EnableWindow(FALSE);
			TrayMenuDisable(ID_TRAY_STOP);
			TrayMenuEnable(ID_TRAY_START);
		}
	}

	HWND m_hwnd=AfxGetApp()->m_pMainWnd->GetSafeHwnd();
	HWND hwnd = ::FindWindow(_T("newconsole"), NULL);
	if (hwnd!=NULL)
	{
		::PostMessage(hwnd,WM_REQUESTINFO,0,0);
	} 

	TrayShow();

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CMedicalPhotoServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CTrayDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMedicalPhotoServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CTrayDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMedicalPhotoServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMedicalPhotoServerDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here

	if (m_Folder==_T(""))
	{
		CString dumy=ChooseFolder();
		if (dumy==_T("")) 
		{
			MessageBox(_T("Image Folder Empty"));
			return;
		}
		m_Folder=dumy;
		config_.Set(DATA_PATH,MCodeChanger::_CCU((LPCTSTR)m_Folder));
		config_.save();
		UpdateData(FALSE);
	}


	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = CONFIG_EXE_FILENAME;
	ShExecInfo.lpParameters = _T("start");
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);


	bool bStatus = UpdateStatus();

}

bool CMedicalPhotoServerDlg::UpdateStatus()
{
	MedicalPhoto_NTService NT_(config_);
	if (NT_.IsInstalled())
	{
		if (NT_.IsRunning())
		{
			GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
			TrayMenuDisable(ID_TRAY_START);
			TrayMenuEnable(ID_TRAY_STOP);
			return true;
		}
		else
		{
			GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
			TrayMenuDisable(ID_TRAY_STOP);
			TrayMenuEnable(ID_TRAY_START);
			return false;
		}
	}
	return false;
}

void CMedicalPhotoServerDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here

	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = CONFIG_EXE_FILENAME;
	ShExecInfo.lpParameters = _T("stop");
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	bool bStatus=UpdateStatus();
}

BOOL CMedicalPhotoServerDlg::CheckValidFolder()
{
	if(_taccess(m_Folder,0) == -1 ) 
	{
		log_.SetFlag(true);
		log_.WriteString(_T("Invalid Image Folder\n"));
		return false;
	}
	return true;
}

void CMedicalPhotoServerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
/*
	boost::mutex::scoped_lock lock2(file_move_mutex);
	boost::mutex::scoped_lock l1(server_run_mutex);
	boost::mutex::scoped_lock l2(build_info_mutex);
	OnButtonStop();
	data_manager_.StopBuild();
*/
	PostMessage(WM_SYSCOMMAND, SC_MINIMIZE);


//	OnButtonExit();
//	CTrayDialog::OnClose();
}

void CMedicalPhotoServerDlg::OnDestroy() 
{
	CTrayDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	UpdateData(TRUE);
/*
	CFile f;

	if (f.Open("MedicalPhoto.cfg",CFile::modeCreate | CFile::modeWrite)==FALSE)
	{
		MessageBox("Error in saving whriaview.cfg file");
		exit(1);
	}
	CArchive ar(&f,CArchive::store);

	ar<<m_Pass<<m_Folder<<m_HospitalID<<m_AutoStart<<m_NTService<<m_MinimizeAtStart<<iRegenTime;


	ar.Close();
	f.Close();
*/
}

CString CMedicalPhotoServerDlg::GetLocalIP()

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

CString CMedicalPhotoServerDlg::IPListing(CStringArray *csaAddress)
{
csaAddress->RemoveAll();

CStringA strTemp;
struct hostent *host;

struct in_addr *ptr; // To retrieve the IP Address 

DWORD dwScope = RESOURCE_CONTEXT;
NETRESOURCEA *NetResource = NULL;
HANDLE hEnum;
WNetOpenEnumA( dwScope, NULL, NULL, 
             NULL, &hEnum );

WSADATA wsaData;
WSAStartup(MAKEWORD(1,1),&wsaData);

if ( hEnum )
{
    DWORD Count = 0xFFFFFFFF;
    DWORD BufferSize = 2048;
    LPVOID Buffer = new char[2048];
    WNetEnumResourceA( hEnum, &Count, 
        Buffer, &BufferSize );
    NetResource = (NETRESOURCEA*)Buffer;

    char szHostName[200];
    unsigned int i;

    for ( i = 0; 
        i < BufferSize/sizeof(NETRESOURCEA); 
        i++, NetResource++ )
    {
        if ( NetResource->dwUsage == 
            RESOURCEUSAGE_CONTAINER && 
            NetResource->dwType == 
            RESOURCETYPE_ANY )
        {
            if ( NetResource->lpRemoteName )
            {
                CStringA strFullName = 
                    NetResource->lpRemoteName;
                if ( 0 == 
                    strFullName.Left(2).Compare("\\\\") )   
                    strFullName = 
                        strFullName.Right(
                            strFullName.GetLength()-2);

                gethostname( szHostName, 
                    strlen( szHostName ) );
                host = gethostbyname(strFullName);

                if(host == NULL) continue; 
                ptr = (struct in_addr *) 
                    host->h_addr_list[0];                    

                // Eg. 211.40.35.76 split up like this.             
                int a = ptr->S_un.S_un_b.s_b1;  // 211           
                int b = ptr->S_un.S_un_b.s_b2;  // 40
                int c = ptr->S_un.S_un_b.s_b3;  // 35
                int d = ptr->S_un.S_un_b.s_b4;  // 76

				if (strFullName!="LOCALHOST")
				{
                strTemp.Format("%s -->  %d.%d.%d.%d",
                    strFullName,a,b,c,d);
				csaAddress->Add(MCodeChanger::_CCW((LPCSTR)strTemp).c_str());
				}
//                AfxMessageBox(strTemp);
            }
        }
    }

    delete Buffer;
    WNetCloseEnum( hEnum ); 
}

WSACleanup();


	CString csResult;
	int i;
	for (i=0;i<csaAddress->GetSize();i++)
	{
		csResult+=csaAddress->GetAt(i)+_T(", ");
//		csResult+=", ";
	}

	if (csResult==_T("")) 
		return _T("");
	else
		return csResult.Left(csResult.GetLength()-2);
}


void CMedicalPhotoServerDlg::OnMenuitemStart() 
{
	// TODO: Add your command handler code here
	OnButtonStart();
}

void CMedicalPhotoServerDlg::OnMenuitemStop() 
{
	// TODO: Add your command handler code here
	OnButtonStop();
}

void CMedicalPhotoServerDlg::OnMenuitemExit() 
{
	// TODO: Add your command handler code here
	OnButtonExit();
//	CTrayDialog::OnOK();	
}


CString CMedicalPhotoServerDlg::ChooseFolder()
{
	UpdateData(TRUE);
	TCHAR szFolder[MAX_PATH*2];
	szFolder[0] = _T('\0');
	CString csResult;

	BOOL bRet = XBrowseForFolder(m_hWnd,
		NULL,		// start with current directory
								 szFolder,
									sizeof(szFolder)/sizeof(TCHAR)-2);
	if (bRet) csResult.Format(_T("%s"),szFolder);
	else
		csResult=_T("");
	csResult.Replace(_T("\\"),_T("/"));
	return csResult;
}

void CMedicalPhotoServerDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	/*
	MedicalPhoto_NTService NTService_(config_);
	if (NTService_.IsInstalled())
	{
		if (NTService_.IsRunning())
		{
			if (MessageBox(_T("Do you want to stop the server before exit?"),_T("Stop the Server"),MB_YESNO)==IDYES)
				NTService_.KillService();
		}
	}
	*/
	Exit();

//	CTrayDialog::OnOK();	
}
void CMedicalPhotoServerDlg::Exit()
{
	log_.CloseCtrl();

/*	if (config_.GetInt(NTSERVICE)==0)
	{
		OnButtonStop();
		data_manager_.StopBuild();
	}
*/
	TrayHide();
//	boost::mutex::scoped_lock lock2(file_move_mutex);
//	boost::mutex::scoped_lock l1(server_run_mutex);
//	boost::mutex::scoped_lock l2(build_info_mutex);

	EndDialog(0);
}

/*
void CMedicalPhotoServerDlg::OnConnect(long lUserId)
{
	CString dumy;
	dumy.Format(_T("User ID %d is connected"),lUserId);
	m_Log.InsertItem(0,dumy,0);

}
*/
/*
void CMedicalPhotoServerDlg::OnDisconnect(long lUserId, NDKServerDisconnection disconnectionType)
{
	CString dumy;
	dumy.Format("User ID %d is disconnected",lUserId);
	m_Log.InsertItem(0,dumy,0);

	// list 에서 삭제

	int i,j;

	for (i=0;i<iNbRUser;i++)
	{
		if (lRequestUser[i]==lUserId)
		{
			for (j=i;j<iNbRUser;j++)
			{
				lRequestUser[j]=lRequestUser[j+1];
			}
			iNbRUser--;
		}
	}
}

*/
BOOL CMedicalPhotoServerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	if (pMsg->message == WM_KEYDOWN)
    {
	    if (pMsg->wParam == 242)
			{
				return TRUE;		    	// DO NOT process further
			}
    }
	if( pMsg->message == WM_MOUSEWHEEL )    //스크롤 메세지가 발생했다면
	{
		m_Log.SendMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}
/*
void CMedicalPhotoServerDlg::OnBnClickedButtonRegenthumb()
{
	// TODO: Add your control notification handler code here
	if (MessageBox("Are you sure to reload?","Reload Thumbnail",MB_YESNO)!=IDYES)
		return;
	ThumbGenAll(0);
}

void CMedicalPhotoServerDlg::OnBnClickedButtonReload()
{
	// TODO: Add your control notification handler code here
	if (MessageBox("Are you sure to reload?","Reload Folder",MB_YESNO)!=IDYES)
		return;
	FolderLoadAll(0);
}
*/

void CMedicalPhotoServerDlg::OnBnClickedButtonOption()
{
	// TODO: Add your control notification handler code here
//	if (MessageBox(_T("Server will Exit and Load Configuration Agent"),_T("Exit"),MB_YESNO)!=IDYES)
//	{
//	}
	ShellExecute(NULL,_T("open")
		, CONFIG_EXE_FILENAME
		,_T("restart buildthumb"),NULL,SW_SHOW);

	Exit();
//	MessageBox(_T("Exit to take it a effect"));
/*	COption m_dlg(config_);
	std::string old_path=config_.Get(THUMB_PATH);
	m_dlg.DoModal();
	if (!config_.Compare(THUMB_PATH,old_path))
	{
		OnButtonStop();
		data_manager_.StopBuild();

		_tpath old_path_=_tpath(MCodeChanger::_CCL(old_path));
		_tpath new_path_=_tpath(MCodeChanger::_CCL(config_.Get(THUMB_PATH)));

		boost::thread BuildThread(boost::bind(&CMedicalPhotoServerDlg::MoveThumbnailThread,this,old_path_,new_path_));

		OnButtonStart();
	}
*/
}
/*
void CMedicalPhotoServerDlg::MoveThumbnailThread(const _tpath& old_path_,const _tpath& new_path_)
{
	boost::mutex::scoped_lock lock(file_move_mutex);
	MFile::Rename(old_path_,new_path_);
}
*/

void CMedicalPhotoServerDlg::OnTrayStart()
{
	// TODO: Add your command handler code here
	OnButtonStart();
}

void CMedicalPhotoServerDlg::OnTrayStop()
{
	// TODO: Add your command handler code here
	OnButtonStop();
}

BOOL CMedicalPhotoServerDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: Add your message handler code here and/or call default
 
	char* buff;
	buff=new char[pCopyDataStruct->cbData+1];
	buff[pCopyDataStruct->cbData]=NULL;
	memcpy(buff,pCopyDataStruct->lpData,pCopyDataStruct->cbData);

	std::istringstream archive_stream_in(buff);
	boost::archive::text_iarchive archive_in(archive_stream_in);

	if (pCopyDataStruct->dwData==WM_COPYDATA_LOG)
	{
//		std::string stMsg;
		log_struct log_struct_;
		archive_in >> log_struct_;
		log_ << log_struct_;
	}
	else if (pCopyDataStruct->dwData==WM_COPYDATA_ADDUSER)
	{
		int iConnectionID;
		std::string stUserID,stIPAddress;
		archive_in 
			>> iConnectionID
			>> stUserID
			>> stIPAddress;
		connection_manager_.Add(iConnectionID,MCodeChanger::_CCL(stIPAddress),MCodeChanger::_CCL(stUserID));
	}
	else if (pCopyDataStruct->dwData==WM_COPYDATA_CONNECTEDLIST)
	{
		std::vector<connection_info> connection_info_list;
		archive_in 
			>> connection_info_list;

		for (unsigned int i=0;i<connection_info_list.size();i++)
		{
			connection_manager_.Add(connection_info_list[i].iConnectionID
				,MCodeChanger::_CCL(connection_info_list[i].stIPAddress)
				,MCodeChanger::_CCL(connection_info_list[i].stUserID));
		}
	}
	else if (pCopyDataStruct->dwData==WM_COPYDATA_DELUSER)
	{
		int iConnectionID;
		archive_in 
			>> iConnectionID;
		connection_manager_.Del(iConnectionID);
	}
	else if (pCopyDataStruct->dwData==WM_COPYDATA_SERVERSTART)
	{
		GetDlgItem(IDC_BUTTON_START) -> EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_STOP) -> EnableWindow(TRUE);
	//	GetDlgItem(IDC_BUTTON_FOLDER) -> EnableWindow(TRUE);
	//	GetDlgItem(IDC_BUTTON_OPTION) -> EnableWindow(TRUE);

		TrayMenuDisable(ID_TRAY_START);
		TrayMenuEnable(ID_TRAY_STOP);
	}
	else if (pCopyDataStruct->dwData==WM_COPYDATA_SERVERSTOP)
	{
		GetDlgItem(IDC_BUTTON_START) -> EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_STOP) -> EnableWindow(FALSE);
	//	GetDlgItem(IDC_BUTTON_FOLDER) -> EnableWindow(TRUE);
	//	GetDlgItem(IDC_BUTTON_OPTION) -> EnableWindow(TRUE);

		TrayMenuDisable(ID_TRAY_STOP);
		TrayMenuEnable(ID_TRAY_START);
	}
	delete [] buff;
	
	return CTrayDialog::OnCopyData(pWnd, pCopyDataStruct);
}

void CMedicalPhotoServerDlg::OnTrayOpen()
{
	// TODO: Add your command handler code here

//	if (TrayHide())
		PostMessage(WM_SYSCOMMAND,SC_RESTORE);
		SetForegroundWindow();
	
//	TraySetMinimizeToTray(false);
//	ShowWindow(SW_SHOW);
}

void CMedicalPhotoServerDlg::OnBnClickedButtonCheckdata()
{
	// TODO: Add your control notification handler code here

	OnButtonStop();
	boost::asio::io_service io_service_;
	CDataManagerDlg DataManagerDlg(io_service_,config_,log_);
	DataManagerDlg.Build();
	DataManagerDlg.DoModal();
	OnButtonStart();
}

void CMedicalPhotoServerDlg::OnBnClickedButtonReloadlog()
{
	// TODO: Add your control notification handler code here
	m_Log.DeleteAllItems();
	try
	{
		long log_size=(long)(boost::filesystem::file_size(_tpath(_T("log.txt"))));
		FILE* fp_r;
		fp_r=_tfopen(_T("log.txt"),_T("rb"));
		if (fp_r!=NULL)
		{
			fseek(fp_r,log_size-5000,SEEK_SET);
			char* buff=NULL;
			buff=new char[5001];
			buff[5000]=NULL;
			size_t iRead=fread(buff,1,5000,fp_r);
			fclose(fp_r);fp_r=NULL;

			std::vector<std::string> split_vec;
			boost::split(split_vec,buff,boost::is_any_of("\n"));

			if (split_vec.size()>1)
			{
				for (unsigned int i=(split_vec.size()-1);i>0;i--)
				{
					if (!split_vec[i].empty())
						m_Log.InsertItem(0,MCodeChanger::_CCW(split_vec[i]).c_str(),0);
				}
			}
			else if (split_vec.size()==0)
			{
				m_Log.InsertItem(0,MCodeChanger::_CCW(split_vec[0]).c_str(),0);
			}
			delete [] buff;
		}
	}
	catch(...)
	{
	}
}
/*

void CMedicalPhotoServerDlg::OnChange(const tstring& filename_org)
{
	if (_tcscmp(filename_org.c_str(),_T("log.txt"))!=0)
		return;

	_tpath prog_path=bfs::initial_path<_tpath>();
	prog_path/=filename_org;

	uintmax_t iNewSize=boost::filesystem::file_size(prog_path);
	if (iOldSize==iNewSize)
		return;

	iOldSize=iNewSize;
	OnBnClickedButtonReloadlog();
}
void CMedicalPhotoServerDlg::StartWatch()
{
	_tpath prog_path=bfs::initial_path<_tpath>();
    
    DWORD FILTER = 
//        FILE_NOTIFY_CHANGE_SECURITY |
//        FILE_NOTIFY_CHANGE_CREATION |
//        FILE_NOTIFY_CHANGE_LAST_ACCESS |
        FILE_NOTIFY_CHANGE_LAST_WRITE;
//        FILE_NOTIFY_CHANGE_SIZE |
//        FILE_NOTIFY_CHANGE_ATTRIBUTES |
//        FILE_NOTIFY_CHANGE_DIR_NAME |
//        FILE_NOTIFY_CHANGE_FILE_NAME;

	Open(prog_path.native_directory_string(),FILTER,false);
	boost::thread BuildThread(boost::bind(&CMedicalPhotoServerDlg::HeartbeatThread,this));
}

void CMedicalPhotoServerDlg::StopWatch()
{
	Close();
}

void CMedicalPhotoServerDlg::HeartbeatThread()
{
	while (true)
	{
		Heartbeat();
	}
	}*/
void CMedicalPhotoServerDlg::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}
