// Configure.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Configure.h"
#include "ConfigureDlg.h"
//#include "SelectType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CConfigureApp

BEGIN_MESSAGE_MAP(CConfigureApp, CWinApp)
//	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()
 

// CConfigureApp construction

CConfigureApp::CConfigureApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CConfigureApp object

CConfigureApp theApp;


// CConfigureApp initialization

BOOL CConfigureApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	WNDCLASS wc;
	::GetClassInfo(AfxGetInstanceHandle(), _T("#32770"), &wc);
    // Change the name of the class.
    wc.lpszClassName = _T("MedicalPhotoConfig");
    // Register this class so that MFC can use it.
    AfxRegisterClass(&wc);   


	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CMyCout log_(_tcout);

	bool bExpress=false;
	if (!MFile::ExistsL(SERVER_CONFIG_FILENAME))
	{
/*		CSelectType m_dlg;
		m_dlg.DoModal();
		if (m_dlg.iType==0)
		{
			bExpress=MFile::CopyFileL(_T("single.default"),SERVER_CONFIG_FILENAME);
		}
		else
		{
			bExpress=MFile::CopyFileL(_T("multi.default"),SERVER_CONFIG_FILENAME);
		}
*/
		bExpress=MFile::CopyFileL(_T("s_config.txt.org"),SERVER_CONFIG_FILENAME);
	}
	config config_(log_);
	config_.load();
#ifdef _DEBUG
	config_.version_.increase_version(CONFIG_FILE_VERSION);
#endif
	CConfigureDlg dlg(config_);
	dlg.bExpress=bExpress;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
