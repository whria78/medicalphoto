// MyTabCtrl.cpp : implementation file
//
/////////////////////////////////////////////////////
// This class is provided as is and Ben Hill takes no
// responsibility for any loss of any kind in connection
// to this code.
/////////////////////////////////////////////////////
// Is is meant purely as a educational tool and may
// contain bugs.
/////////////////////////////////////////////////////
// ben@shido.fsnet.co.uk
// http://www.shido.fsnet.co.uk
/////////////////////////////////////////////////////
// Thanks to a mystery poster in the C++ forum on 
// www.codeguru.com I can't find your name to say thanks
// for your Control drawing code. If you are that person 
// thank you very much. I have been able to use some of 
// you ideas to produce this sample application.
/////////////////////////////////////////////////////

#include "stdafx.h"
#include "WhriaView.h"
#include "MyTabCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl

CMyTabCtrl::CMyTabCtrl(CWhriaCacheClient& w,client_config& c)
: WhriaClient(w)
,config_(c)
{
	m_tabPages[0]=new COptionPage_General(c);
//	m_tabPages[1]=new CCustomDiagnosisList(w);

	m_nNumberOfPages=1;
	if (config_.server_config.Compare(MULTIUSER_SUPPORT,1))
	{
		m_tabPages[1]=new COptionPage_UserManagement;
		m_nNumberOfPages++;
	}

}

CMyTabCtrl::~CMyTabCtrl()
{
	for(int nCount=0; nCount < m_nNumberOfPages; nCount++){
		delete m_tabPages[nCount];
	}
}

void CMyTabCtrl::Init()
{
	m_tabCurrent=0;

	m_tabPages[0]->Create(IDD_DIALOG_OPTION1, this);
//	m_tabPages[1]->Create(IDD_DIALOG_CUSTOMDX, this);

	m_tabPages[0]->ShowWindow(SW_SHOW);
//	m_tabPages[1]->ShowWindow(SW_HIDE);

	if (config_.server_config.Compare(MULTIUSER_SUPPORT,1))
	{
		m_tabPages[1]->Create(IDD_DIALOG_OPTION2, this);
		m_tabPages[1]->ShowWindow(SW_HIDE);
	}


/*
	if (config_.server_config.Compare(MULTIUSER_SUPPORT,0) && m_tabCurrent==2)
	{
		AfxMessageBox(_T("The Application does not support the feature of Multi-User"));
		return;
	}
*/
	SetRectangle();
}

void CMyTabCtrl::SetRectangle()
{
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;

	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);

	nX=itemRect.left;
	nY=itemRect.bottom+1;
	nXc=tabRect.right-itemRect.left-1;
	nYc=tabRect.bottom-nY-1;

	m_tabPages[0]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	for(int nCount=1; nCount < m_nNumberOfPages; nCount++){
		m_tabPages[nCount]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
	}
}

BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CMyTabCtrl)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl message handlers

void CMyTabCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CTabCtrl::OnLButtonDown(nFlags, point);

	if(m_tabCurrent != GetCurFocus()){
		m_tabPages[m_tabCurrent]->ShowWindow(SW_HIDE);
		m_tabCurrent=GetCurFocus();
		m_tabPages[m_tabCurrent]->ShowWindow(SW_SHOW);
		m_tabPages[m_tabCurrent]->SetFocus();
	}
}
