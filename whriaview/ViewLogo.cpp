// ViewLogo.cpp : implementation file
//

#include "stdafx.h"
#include "WhriaView.h"
#include "ViewLogo.h"


// CViewLogo dialog

IMPLEMENT_DYNAMIC(CViewLogo, CDialog)

CViewLogo::CViewLogo(client_config& c,CWnd* pParent /*=NULL*/)
	: CDialog(CViewLogo::IDD, pParent)
	,bIdleStart(false)
	, config_(c)
{

}

CViewLogo::~CViewLogo()
{
}

void CViewLogo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_LOGO, m_Logo);
	DDX_Control(pDX, IDC_STATIC_TIP, m_logotip);
}


BEGIN_MESSAGE_MAP(CViewLogo, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
//	ON_STN_CLICKED(IDC_STATIC_TIP, &CViewLogo::OnStnClickedStaticTip)
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BUTTON_VIEWLOGO_EXIT, &CViewLogo::OnBnClickedButtonViewlogoExit)
END_MESSAGE_MAP()


// CViewLogo message handlers

BOOL CViewLogo::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
//	return CDialog::OnEraseBkgnd(pDC);
}


BOOL CViewLogo::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	if (config_.server_config.Get(ADMIN_PASS).compare("")!=0)
	{
		if (pMsg->message == WM_KEYDOWN)   // 키보드가 눌렸을때 처리
		{
			stPass += wchar_t(pMsg->wParam);
			if (stPass.Find(MCodeChanger::_CCL(config_.server_config.Get(ADMIN_PASS)).c_str()) != -1)
			{
				stPass = _T("");
				PostMessage(WM_KEYDOWN, VK_ESCAPE, 99);
			}
			if (pMsg->wParam == VK_ESCAPE && pMsg->lParam != 99)
				return true;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CViewLogo::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (bIdleStart)
	{
		if (Utility::GetLastInputTime()<3)
		{
			if (config_.server_config.Get(ADMIN_PASS).compare("") == 0)
				PostMessage(WM_KEYDOWN,VK_ESCAPE,99);
			return;
		}
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CViewLogo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
/*
	CRect rc;

	rc.left = 28;
	rc.right = 270;
	rc.top=300;
	rc.bottom=420;

	CString stMsg;
	srand( (unsigned)time( NULL ) );
	int iIndex=(rand() % (int)(11 + 1));
	stMsg.LoadString(IDS_TIP1+iIndex);

//	stMsg+=stMsg+stMsg;

	dc.DrawText(stMsg,&rc,DT_WORDBREAK);
*/
}


//void CViewLogo::OnStnClickedStaticTip()
//{
//	// TODO: Add your control notification handler code here
//}


BOOL CViewLogo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	CString stMsg;
	srand((unsigned)time(NULL));
	int iIndex = (rand() % (int)(12 + 1));
	stMsg.LoadString(IDS_TIP1 + iIndex);
	m_logotip.SetWindowText(stMsg);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


HBRUSH CViewLogo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIP)
		{
			pDC->SetTextColor(RGB(255, 0, 0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
	}
	}
	// TO
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void CViewLogo::OnBnClickedButtonViewlogoExit()
{
	// TODO: Add your control notification handler code here
	::PostMessage(GetParent()->m_hWnd, WM_QUIT, 0, 0);
}
