// AppTypeSelect.cpp : implementation file
//

#include "stdafx.h"
#include "WhriaView.h"
#include "AppTypeSelect.h"


// CAppTypeSelect dialog

IMPLEMENT_DYNAMIC(CAppTypeSelect, CDialog)

CAppTypeSelect::CAppTypeSelect(client_config& c,CWnd* pParent /*=NULL*/)
	: CDialog(CAppTypeSelect::IDD, pParent)
	,config_(c)
{

}

CAppTypeSelect::~CAppTypeSelect()
{
}

void CAppTypeSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAppTypeSelect, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SINGLE, &CAppTypeSelect::OnBnClickedButtonSingle)
	ON_BN_CLICKED(IDC_BUTTON_MULTI, &CAppTypeSelect::OnBnClickedButtonMulti)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CAppTypeSelect::OnBnClickedButtonExit)
END_MESSAGE_MAP()


// CAppTypeSelect message handlers

void CAppTypeSelect::OnBnClickedButtonSingle()
{
	// TODO: Add your control notification handler code here
//	config_.Set(APP_TYPE,0);
	config_.save();
	OnOK();
}

void CAppTypeSelect::OnBnClickedButtonMulti()
{
	// TODO: Add your control notification handler code here
//	config_.Set(APP_TYPE,1);
	config_.save();
	OnOK();
}

void CAppTypeSelect::OnBnClickedButtonExit()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
