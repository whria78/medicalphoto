// MedicalPhotoServer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MedicalPhotoServer.h"
#include "MedicalPhotoServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMedicalPhotoServerApp

BEGIN_MESSAGE_MAP(CMedicalPhotoServerApp, CWinApp)
	//{{AFX_MSG_MAP(CMedicalPhotoServerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
//	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedicalPhotoServerApp construction

CMedicalPhotoServerApp::CMedicalPhotoServerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMedicalPhotoServerApp object

CMedicalPhotoServerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMedicalPhotoServerApp initialization

BOOL CMedicalPhotoServerApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	WNDCLASS wc;
	::GetClassInfo(AfxGetInstanceHandle(), _T("#32770"), &wc);
    // Change the name of the class.
    wc.lpszClassName = _T("MedicalPhotoServer");
    // Register this class so that MFC can use it.
    AfxRegisterClass(&wc);   


	CWinApp::InitInstance();

	AfxEnableControlContainer();

	CMyCout log(_tcout);
	config config_(log);
	CMedicalPhotoServerDlg dlg(config_);
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

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
