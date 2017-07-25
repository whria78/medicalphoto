// Preference.cpp : implementation file
//

#include "stdafx.h"
#include "WhriaView.h"
#include "Preference.h"


// CPreference dialog

IMPLEMENT_DYNAMIC(CPreference, CDialog)

CPreference::CPreference(CWhriaCacheClient&w,client_config&c,CWnd* pParent /*=NULL*/)
	: CDialog(CPreference::IDD, pParent)
	,config_(c)
	,WhriaClient(w)
	,m_OptionTabCtrl(w,c)
//	,config_old_(CMyCout(_tcout))
{

}

CPreference::~CPreference()
{
}

void CPreference::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_OPTION, m_OptionTabCtrl);
}


BEGIN_MESSAGE_MAP(CPreference, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CPreference::OnBnClickedCancel)
END_MESSAGE_MAP()


// CPreference message handlers

BOOL CPreference::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	m_OptionTabCtrl.InsertItem(0, _T("General"));
//	m_OptionTabCtrl.InsertItem(1, _T("Custom Diagnosis"));
	if (config_.server_config.Compare(MULTIUSER_SUPPORT,1))
	{
		m_OptionTabCtrl.InsertItem(1, _T("User Management"));
	}
	m_OptionTabCtrl.Init();

//	config_old_=config_;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPreference::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

BOOL CPreference::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    if (pMsg->message == WM_KEYDOWN)
    {
		if (pMsg->wParam == VK_ESCAPE)
		{
			OnBnClickedCancel();
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
