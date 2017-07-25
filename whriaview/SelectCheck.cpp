// SelectCheck.cpp : implementation file
//

#include "stdafx.h"
#include "WhriaView.h"
#include "SelectCheck.h"


// CSelectCheck dialog

IMPLEMENT_DYNAMIC(CSelectCheck, CDialog)

CSelectCheck::CSelectCheck(fileinfo_list& f_l,CWnd* pParent /*=NULL*/)
	: CDialog(CSelectCheck::IDD, pParent)
	,f_list(f_l)
{

}

CSelectCheck::~CSelectCheck()
{
}

void CSelectCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SELECTLIST, m_List);
}


BEGIN_MESSAGE_MAP(CSelectCheck, CDialog)
	ON_BN_CLICKED(IDOK, &CSelectCheck::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSelectCheck::OnBnClickedCancel)
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CSelectCheck message handlers

void CSelectCheck::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CSelectCheck::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

BOOL CSelectCheck::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	RECT listRect;
	m_List.GetClientRect(&listRect);
	int nListWidth = (listRect.right - listRect.left);

	m_List.InsertColumn(0,_T("List of Files"),LVCFMT_LEFT, nListWidth*2);
	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0);

	for (unsigned int i=0;i<f_list.size();i++)
	{
		m_List.InsertItem(0,MCodeChanger::_CCL(f_list[i].GetNetPath()).c_str(),0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSelectCheck::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CSelectCheck::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	if( pMsg->message == WM_MOUSEWHEEL )    //스크롤 메세지가 발생했다면
    {
		m_List.SendMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
