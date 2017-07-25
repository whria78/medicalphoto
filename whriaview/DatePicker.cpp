// DatePicker.cpp : implementation file
//

#include "stdafx.h"
#include "WhriaView.h"
#include "DatePicker.h"


// CDatePicker dialog

IMPLEMENT_DYNAMIC(CDatePicker, CDialog)

CDatePicker::CDatePicker(CWnd* pParent /*=NULL*/)
	: CDialog(CDatePicker::IDD, pParent)
	, m_DateFrom(CTime::GetCurrentTime())
	, m_DateTo(CTime::GetCurrentTime())
{

}

CDatePicker::~CDatePicker()
{
}

void CDatePicker::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_DateFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_DateTo);
}


BEGIN_MESSAGE_MAP(CDatePicker, CDialog)
	ON_BN_CLICKED(IDOK, &CDatePicker::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDatePicker::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDatePicker message handlers

void CDatePicker::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CDatePicker::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
