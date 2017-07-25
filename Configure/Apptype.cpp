// Apptype.cpp : implementation file
//

#include "stdafx.h"
#include "Configure.h"
#include "Apptype.h"


// CApptype dialog

IMPLEMENT_DYNAMIC(CApptype, CDialog)

CApptype::CApptype(CWnd* pParent /*=NULL*/)
	: CDialog(CApptype::IDD, pParent)
//	,config_(c_)
{

}

CApptype::~CApptype()
{
}

void CApptype::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CApptype, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CApptype::OnBnClickedButtonExit)
END_MESSAGE_MAP()


// CApptype message handlers

void CApptype::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	return;
	CDialog::OnClose();
}

void CApptype::OnBnClickedButtonExit()
{
	OnOK();
	// TODO: Add your control notification handler code here
}
