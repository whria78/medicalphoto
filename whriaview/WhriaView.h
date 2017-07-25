// WhriaView.h : main header file for the WHRIAVIEW application
//

#if !defined(AFX_WHRIAVIEW_H__E01C0737_5298_455A_9397_7E724618974F__INCLUDED_)
#define AFX_WHRIAVIEW_H__E01C0737_5298_455A_9397_7E724618974F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

//#define MAXTHUMB 300

/////////////////////////////////////////////////////////////////////////////
// CWhriaViewApp:
// See WhriaView.cpp for the implementation of this class
//

class CWhriaViewApp : public CWinApp
{
public:
	CWhriaViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWhriaViewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
private:

	//{{AFX_MSG(CWhriaViewApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WHRIAVIEW_H__E01C0737_5298_455A_9397_7E724618974F__INCLUDED_)
