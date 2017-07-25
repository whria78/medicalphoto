// DialogInput.cpp : implementation file
//

#include "stdafx.h"
#include "WhriaView.h"
#include "DialogInput.h"


// CDialogInput dialog

IMPLEMENT_DYNAMIC(CDialogInput, CDialog)

CDialogInput::CDialogInput(const CString& m_default,CWnd* pParent /*=NULL*/)
	: CDialog(CDialogInput::IDD, pParent)
	, m_InputBox(m_default)
{

}

CDialogInput::~CDialogInput()
{
}

void CDialogInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUTBOX, m_InputBox);
}


BEGIN_MESSAGE_MAP(CDialogInput, CDialog)
	ON_BN_CLICKED(IDOK, &CDialogInput::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogInput message handlers

void CDialogInput::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (_tcscmp((LPCTSTR)m_InputBox,Utility::GetFilename((LPCTSTR)m_InputBox).c_str())!=0)
	{
		MessageBox(_T("Illegal filename characters"));
		return;
	}

	OnOK();
}
