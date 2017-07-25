// WhriaView.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "WhriaView.h"
#include "WhriaViewDlg.h"
//#include "commctrl.h"

#include "../client/whriaclient.h"
#include "../share/cmycout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWhriaViewApp

BEGIN_MESSAGE_MAP(CWhriaViewApp, CWinApp)
	//{{AFX_MSG_MAP(CWhriaViewApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
//	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWhriaViewApp construction

CWhriaViewApp::CWhriaViewApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWhriaViewApp object

CWhriaViewApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWhriaViewApp initialization

BOOL CWhriaViewApp::InitInstance()
{/*
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

//	InitCommonControls(); 
*/
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
    wc.lpszClassName = _T("WhriaView");
    // Register this class so that MFC can use it.
    AfxRegisterClass(&wc);   


	CWinApp::InitInstance();

	AfxEnableControlContainer();



	boost::asio::io_service io_service_;
	CMyCout log(_tcout);
	CWhriaCacheClient WhriaClient(io_service_,log);

	try
	{
		CWhriaViewDlg dlg(log,WhriaClient);
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
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
	}
	catch (std::exception& e)
	{
		CMyCout log(_tcout);
		log << MCodeChanger::_CCW(e.what());
	}



	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
