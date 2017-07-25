// MedicalPhotoServer.h : main header file for the MedicalPhotoSERVER application
//

#if !defined(AFX_MedicalPhotoSERVER_H__4629F9B9_1C74_41DD_8EC1_3BDD950467CF__INCLUDED_)
#define AFX_MedicalPhotoSERVER_H__4629F9B9_1C74_41DD_8EC1_3BDD950467CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
//#include "commctrl.h"

/////////////////////////////////////////////////////////////////////////////
// CMedicalPhotoServerApp:
// See MedicalPhotoServer.cpp for the implementation of this class
//
#include <ws2tcpip.h>
#include <wspiapi.h>
#define GetAddrInfo WspiapiGetAddrInfo
#define FreeAddrInfo WspiapiFreeAddrInfo

#include "../share/config.h"

class CMedicalPhotoServerApp : public CWinApp
{
public:
	CMedicalPhotoServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedicalPhotoServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMedicalPhotoServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MedicalPhotoSERVER_H__4629F9B9_1C74_41DD_8EC1_3BDD950467CF__INCLUDED_)
