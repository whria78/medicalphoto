// UpdateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Configure.h"
#include "UpdateDlg.h"


// CUpdateDlg dialog

IMPLEMENT_DYNAMIC(CUpdateDlg, CDialog)

CUpdateDlg::CUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateDlg::IDD, pParent)
{
	bStopThread=false;
	bStartThread=false;
}

CUpdateDlg::~CUpdateDlg()
{
}

void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_UPDATE, m_Progress);
}


BEGIN_MESSAGE_MAP(CUpdateDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CUpdateDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CUpdateDlg message handlers

void CUpdateDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	bStopThread=true;

//	OnCancel();
}

BOOL CUpdateDlg::OnInitDialog()
{
	__super::OnInitDialog();

	// TODO:  Add extra initialization here

	bStartThread=true;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CUpdateDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	EndDialog(0);

//	__super::OnClose();
}



