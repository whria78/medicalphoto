// OptionPage2.cpp : implementation file
//

#include "stdafx.h"
#include "WhriaView.h"
#include "OptionPage2.h"


// COptionPage_UserManagement dialog

IMPLEMENT_DYNAMIC(COptionPage_UserManagement, CDialog)

COptionPage_UserManagement::COptionPage_UserManagement(CWnd* pParent /*=NULL*/)
	: CDialog(COptionPage_UserManagement::IDD, pParent)
	, m_NewUser(_T(""))

{

}

COptionPage_UserManagement::~COptionPage_UserManagement()
{
}

void COptionPage_UserManagement::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USERLIST, m_UserList);
	DDX_Text(pDX, IDC_EDIT_NEWUSER, m_NewUser);
}


BEGIN_MESSAGE_MAP(COptionPage_UserManagement, CDialog)
END_MESSAGE_MAP()


// COptionPage_UserManagement message handlers

BOOL COptionPage_UserManagement::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    if (pMsg->message == WM_KEYDOWN)
    {
		if (pMsg->wParam == VK_ESCAPE)
		{
			GetParent()->PostMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
