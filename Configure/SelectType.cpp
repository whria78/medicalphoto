// SelectType.cpp : implementation file
//

#include "stdafx.h"
#include "Configure.h"
#include "SelectType.h"


// CSelectType dialog

IMPLEMENT_DYNAMIC(CSelectType, CDialog)

CSelectType::CSelectType(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectType::IDD, pParent)
	,iType(0)
{

}

CSelectType::~CSelectType()
{
}

void CSelectType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSelectType, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SINGLE, &CSelectType::OnBnClickedButtonSingle)
	ON_BN_CLICKED(IDC_BUTTON_MULTI, &CSelectType::OnBnClickedButtonMulti)
END_MESSAGE_MAP()


// CSelectType message handlers

void CSelectType::OnClose()
{
	// TODO: Add your message handler code here and/or call default

//	CDialog::OnClose();
}

void CSelectType::OnBnClickedButtonSingle()
{
	iType=0;
	OnOK();
	// TODO: Add your control notification handler code here
}

void CSelectType::OnBnClickedButtonMulti()
{
	iType=1;
	OnOK();
	// TODO: Add your control notification handler code here
}