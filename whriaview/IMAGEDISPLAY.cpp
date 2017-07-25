// IMAGEDISPLAY.cpp : implementation file
//

#include "stdafx.h"
#include "whriaview.h"
#include "IMAGEDISPLAY.h"
#include ".\imagedisplay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIMAGEDISPLAY dialog


CIMAGEDISPLAY::CIMAGEDISPLAY(CWnd* pParent /*=NULL*/)
	: CDragDialog(CIMAGEDISPLAY::IDD, pParent)
	,bImageOn(false)
	,iRotateAngle(0)
{
	//{{AFX_DATA_INIT(CIMAGEDISPLAY)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CIMAGEDISPLAY::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIMAGEDISPLAY)
	//}}AFX_DATA_MAP
	//	DDX_Control(pDX, IDC_STATIC_LEFT, m_Left);
	//	DDX_Control(pDX, IDC_STATIC_RIGHT, m_Right);
	DDX_Control(pDX, IDC_STATIC_LEFT, m_Left);
	DDX_Control(pDX, IDC_STATIC_RIGHT, m_Right);
	DDX_Control(pDX, IDC_STATIC_ZOOM, m_Zoom);
	DDX_Control(pDX, IDC_STATIC_NEXT, m_NextBtn);
	DDX_Control(pDX, IDC_STATIC_PREV, m_PrevBtn);
	DDX_Control(pDX, IDC_STATIC_ROTATE, m_Rotate);
	DDX_Control(pDX, IDC_STATIC_ROTATE2, m_RotateReverse);
	DDX_Control(pDX, IDC_STATIC_CLOSED, m_ClosedBtn);
}


BEGIN_MESSAGE_MAP(CIMAGEDISPLAY, CDragDialog)
	//{{AFX_MSG_MAP(CIMAGEDISPLAY)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
	ON_STN_CLICKED(IDC_STATIC_LEFT, &CIMAGEDISPLAY::OnStnClickedStaticLeft)
	ON_STN_CLICKED(IDC_STATIC_RIGHT, &CIMAGEDISPLAY::OnStnClickedStaticRight)
	ON_STN_CLICKED(IDC_STATIC_ZOOM, &CIMAGEDISPLAY::OnStnClickedStaticZoom)
	ON_WM_KILLFOCUS()
	ON_WM_CLOSE()
	ON_STN_CLICKED(IDC_STATIC_PREV, &CIMAGEDISPLAY::OnStnClickedStaticPrev)
	ON_STN_CLICKED(IDC_STATIC_NEXT, &CIMAGEDISPLAY::OnStnClickedStaticNext)
	ON_STN_CLICKED(IDC_STATIC_ROTATE, &CIMAGEDISPLAY::OnStnClickedStaticRotate)
	ON_STN_CLICKED(IDC_STATIC_ROTATE2, &CIMAGEDISPLAY::OnStnClickedStaticRotate2)
	ON_STN_CLICKED(IDC_STATIC_CLOSED, &CIMAGEDISPLAY::OnClickedStaticClosed)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIMAGEDISPLAY message handlers

void CIMAGEDISPLAY::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here

//		CMonitorDC dc( &monitor);

//		monitor.GetMonitorRect( &rect );

//		int nScreenWidth = rect.Width();
//		int nScreenHeight = rect.Height();
		CRect rect2;
		monitor.GetMonitorRect( &rect2 );
		int nScreenWidth=rect2.Width();
		int nScreenHeight=rect2.Height();
		CRect rect(0,0,nScreenWidth,nScreenHeight);
		
/*
	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
		
		CRect rect(0,0,nScreenWidth,nScreenHeight);
*/
		long x,y;
		long a,b;
		long m,n;

		m=image.GetWidth();
		n=image.GetHeight();
		if (m==0 || n==0) return;

		x=nScreenWidth;
		y=nScreenHeight;

		a=pZoomPoint.x;
		b=pZoomPoint.y;

		RGBQUAD border;
		border.rgbBlue=0;
		border.rgbGreen=0;
		border.rgbRed=0;

		CxImage CxImage_Crop;

		if (m>x || n>y)
		{
			if (bZoom==TRUE)
			{
	
				long x1,y1;
				long x2,y2;

				x1=a*m/x-a-pMoveTo.x+pMoveFrom.x;
				y1=b*n/y-b-pMoveTo.y+pMoveFrom.y;
				x2=a*m/x-a+x-pMoveTo.x+pMoveFrom.x;
				y2=b*n/y-b+y-pMoveTo.y+pMoveFrom.y;

				if (x1<0)
					pMoveTo.x=a*m/x-a+pMoveFrom.x;
				if (x2>m)
					pMoveTo.x=a*m/x-a+x+pMoveFrom.x-m;
				if (y1<0)
					pMoveTo.y=b*n/y-b+pMoveFrom.y;
				if (y2>n)
					pMoveTo.y=b*n/y-b+y+pMoveFrom.y-n;

				x1=a*m/x-a-pMoveTo.x+pMoveFrom.x;
				y1=b*n/y-b-pMoveTo.y+pMoveFrom.y;
				x2=a*m/x-a+x-pMoveTo.x+pMoveFrom.x;
				y2=b*n/y-b+y-pMoveTo.y+pMoveFrom.y;

				if (m>x && n>y)
				{
					image.Crop(x1,y1,x2,y2,&CxImage_Crop);
				}
				else
				{
					if (m<=x)
					{
					image.Crop(0,y1,m,y2,&CxImage_Crop);
					CxImage_Crop.Expand((x-m)/2,0,(x-m)/2,0,border);

					}
					if (n<=y)
					{
					image.Crop(x1,0,x2,n,&CxImage_Crop);
					CxImage_Crop.Expand(0,(y-n)/2,0,(y-n)/2,border);
					}
				}

			}
			else
			{
				if (m*y > x*n)
				{
					image.Resample(x,n*x/m,1,&CxImage_Crop);
					CxImage_Crop.Expand(0,(y-n*x/m)/2,0,(y-n*x/m)/2,border);
				}
				if (m*y <= x*n)
				{
					image.Resample(m*y/n,y,1,&CxImage_Crop);
					CxImage_Crop.Expand((x-m*y/n)/2,0,(x-m*y/n)/2,0,border);
				}
			}
		}
		else
		{
			image.Expand((x-m)/2,(y-n)/2,(x-m)/2,(y-n)/2,border,&CxImage_Crop);
		}


		CxImage_Crop.Draw(dc.m_hDC,rect);

		// information display


		if (fileinfo_.Time!=boost::posix_time::ptime())
		{
			CRect rc;
			rc.left = 0;
			rc.right = 200;
			rc.top=0;
			rc.bottom=50;
			dc.DrawText(MCodeChanger::_CCL(fileinfo_.GetDateString()).c_str(),&rc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		}


	// Do not call CDialog::OnPaint() for painting messages
}

void CIMAGEDISPLAY::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

BOOL CIMAGEDISPLAY::OnInitDialog() 
{
	CDialog::OnInitDialog();

	iZoomRate=10;
//	m_tooltip.Create(this);
//	ResetToolTip();

	m_Right.LoadButtonBitmaps(IDB_BITMAP_R1,IDB_BITMAP_R2,IDB_BITMAP_R3);
	m_Left.LoadButtonBitmaps(IDB_BITMAP_L1,IDB_BITMAP_L2,IDB_BITMAP_L3);

	m_Zoom.LoadButtonBitmaps(IDB_BITMAP_Z1,IDB_BITMAP_Z2,IDB_BITMAP_Z3);
	m_Rotate.LoadButtonBitmaps(IDB_BITMAP_RO1,IDB_BITMAP_RO3,IDB_BITMAP_RO2);
	m_RotateReverse.LoadButtonBitmaps(IDB_BITMAP_ROT1,IDB_BITMAP_ROT3,IDB_BITMAP_ROT2);

	m_NextBtn.LoadButtonBitmaps(IDB_BITMAP_N1,IDB_BITMAP_N3,IDB_BITMAP_N2);
	m_PrevBtn.LoadButtonBitmaps(IDB_BITMAP_P1,IDB_BITMAP_P3,IDB_BITMAP_P2);

	m_ClosedBtn.LoadButtonBitmaps(IDB_BITMAP_C, IDB_BITMAP_C, IDB_BITMAP_C);

	// dragdrop dialog

	SetDragButtons(FALSE,FALSE);
//	SetFadeWhileDragging(80);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CIMAGEDISPLAY::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
//  m_tooltip.RelayEvent(pMsg);

	    if(pMsg->message == WM_KEYDOWN)   // 키보드가 눌렸을때 처리
		{
	        if(pMsg->wParam == VK_NEXT || 
				pMsg->wParam == VK_PRIOR || 
				pMsg->wParam == VK_TAB || 
				pMsg->wParam == VK_F12 ||
				pMsg->wParam == VK_SPACE ||
				pMsg->wParam == VK_RIGHT ||
				pMsg->wParam == VK_LEFT ||
				pMsg->wParam == VK_F11 ||
				pMsg->wParam == VK_ESCAPE

//				pMsg->wParam == VK_UP ||
//				pMsg->wParam == VK_DOWN
				)
			{
				m_parent->PostMessage(pMsg->message,pMsg->wParam,pMsg->lParam);	
				return TRUE;
			}

/*
			if (pMsg->wParam == VK_LEFT)
			{
//				int iCurrentMonitor=GetCurrentMonitor();

//				if (ImageDisplay[iCurrentMonitor].bImageOn==false) 
//					return CDialog::PreTranslateMessage(pMsg);

				image.RotateLeft();
				Invalidate(FALSE);

				return TRUE;
			}

*/
			if (pMsg->wParam == 82) // "r"
			{
//				int iCurrentMonitor=GetCurrentMonitor();

//				if (ImageDisplay[iCurrentMonitor].bImageOn==false)
//					return CDialog::PreTranslateMessage(pMsg);

				OnStnClickedStaticRotate();
				return TRUE;
			}
			if (pMsg->wParam == 69) // "r"
			{
				OnStnClickedStaticRotate2();
				return TRUE;
			}
			
/*			if (pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN)
			{
				image.Rotate180();
				Invalidate(FALSE);
				return TRUE;
			}
*/


			if (pMsg->wParam == 187 && bZoom==FALSE) // + 키
			{
				bZoom=TRUE;
				Invalidate(false);
			}
			if (pMsg->wParam == 189 && bZoom==TRUE) // - 키
			{
				bZoom=FALSE;
				Invalidate(false);
		  }

		}

		if (bZoom)
	return CDialog::PreTranslateMessage(pMsg);
		else
	return CDragDialog::PreTranslateMessage(pMsg);

}

int CIMAGEDISPLAY::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
//	CRect rect;
//	monitor.GetMonitorRect( &rect );

//	int nScreenWidth = rect.Width();
//	int nScreenHeight = rect.Height();

//	m_Right.MoveWindow(nScreenWidth-100,10,34,34);
//	m_Left.MoveWindow(nScreenWidth-150,10,34,34);


	return 0;
}

void CIMAGEDISPLAY::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
		CRect rect;
		monitor.GetMonitorRect( &rect );

		int nScreenWidth = rect.Width();
		int nScreenHeight = rect.Height();

	if (bZoom)
	{
		long a,b;
		long m,n;

		long x,y;
		x=nScreenWidth;
		y=nScreenHeight;

		m=image.GetWidth();
		n=image.GetHeight();
		if (m==0 || n==0) return;

		a=pZoomPoint.x;
		b=pZoomPoint.y;

		long x1,y1;
		long x2,y2;
		x1=a*m/x-a-pMoveTo.x+pMoveFrom.x;
		y1=b*n/y-b-pMoveTo.y+pMoveFrom.y;
		x2=a*m/x-a+x-pMoveTo.x+pMoveFrom.x;
		y2=b*n/y-b+y-pMoveTo.y+pMoveFrom.y;

		if (x1<0)
			pMoveTo.x=a*m/x-a+pMoveFrom.x;
		if (x2>m)
			pMoveTo.x=a*m/x-a+x+pMoveFrom.x-m;
		if (y1<0)
			pMoveTo.y=b*n/y-b+pMoveFrom.y;
		if (y2>n)
			pMoveTo.y=b*n/y-b+y+pMoveFrom.y-n;

		x1=a*m/x-a-pMoveTo.x+pMoveFrom.x;
		y1=b*n/y-b-pMoveTo.y+pMoveFrom.y;
		x2=a*m/x-a+x-pMoveTo.x+pMoveFrom.x;
		y2=b*n/y-b+y-pMoveTo.y+pMoveFrom.y;

		if (m!=x)
			pZoomPoint.x=x1*x/(m-x);
		else
			pZoomPoint.x=x/2;
		if (n!=y)
			pZoomPoint.y=y1*y/(n-y);
		else
			pZoomPoint.y=y/2;

//		bMouseMove=false;
		pMoveFrom.x=pMoveTo.x=point.x;
		pMoveFrom.y=pMoveTo.y=point.y;

		Invalidate(FALSE);
	}
	else
	{
		current_monitor= CMonitors::GetNearestMonitor(this);
	}

//	m_Left.OnLButtonDown(nFlags,point);
//	m_Right.OnLButtonDown(nFlags,point);

	if (bZoom)
	CDialog::OnLButtonDown(nFlags, point);
	else
	CDragDialog::OnLButtonDown(nFlags, point);
}

void CIMAGEDISPLAY::ResetButtons()
{
	m_Left.ResetButton();
	m_Right.ResetButton();
	m_Zoom.ResetButton();
	m_ClosedBtn.ResetButton();
	m_PrevBtn.ResetButton();
	m_NextBtn.ResetButton();
	m_Rotate.ResetButton();
	m_RotateReverse.ResetButton();
}

void CIMAGEDISPLAY::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	if (bZoom && (nFlags&MK_LBUTTON))
	{
		pMoveTo.x=point.x;
		pMoveTo.y=point.y;
		Invalidate(FALSE);
	}
	ResetButtons();

//	if (point.x>1000)
//	if (CMonitors::GetNearestMonitor(this)!=CMonitors::GetNearestMonitor(point))
//		MessageBox(_T("!"));

	if (bZoom)
	CDialog::OnMouseMove(nFlags, point);
	else
	CDragDialog::OnMouseMove(nFlags, point);
}

void CIMAGEDISPLAY::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
		CRect rect;
		monitor.GetMonitorRect( &rect );

		int nScreenWidth = rect.Width();
		int nScreenHeight = rect.Height();

	if (bZoom)
	{
		long a,b;
		long m,n;

		long x,y;
		x=nScreenWidth;
		y=nScreenHeight;

		m=image.GetWidth();
		n=image.GetHeight();
		if (m==0 || n==0) return;

		a=pZoomPoint.x;
		b=pZoomPoint.y;

		long x1,y1;
		long x2,y2;
		x1=a*m/x-a-pMoveTo.x+pMoveFrom.x;
		y1=b*n/y-b-pMoveTo.y+pMoveFrom.y;
		x2=a*m/x-a+x-pMoveTo.x+pMoveFrom.x;
		y2=b*n/y-b+y-pMoveTo.y+pMoveFrom.y;

		if (x1<0)
			pMoveTo.x=a*m/x-a+pMoveFrom.x;
		if (x2>m)
			pMoveTo.x=a*m/x-a+x+pMoveFrom.x-m;
		if (y1<0)
			pMoveTo.y=b*n/y-b+pMoveFrom.y;
		if (y2>n)
			pMoveTo.y=b*n/y-b+y+pMoveFrom.y-n;

		x1=a*m/x-a-pMoveTo.x+pMoveFrom.x;
		y1=b*n/y-b-pMoveTo.y+pMoveFrom.y;
		x2=a*m/x-a+x-pMoveTo.x+pMoveFrom.x;
		y2=b*n/y-b+y-pMoveTo.y+pMoveFrom.y;

		if (m!=x)
			pZoomPoint.x=x1*x/(m-x);
		else
			pZoomPoint.x=x/2;
		if (n!=y)
			pZoomPoint.y=y1*y/(n-y);
		else
			pZoomPoint.y=y/2;

//		bMouseMove=false;
		pMoveTo.x=0;
		pMoveTo.y=0;
		pMoveFrom.x=0;
		pMoveFrom.y=0;

		Invalidate(FALSE);
	}
/*	else
	{
		POINT ptCursor;GetCursorPos(&ptCursor);
		if (!CMonitors::IsOnScreen(ptCursor))
		{
			AfxMessageBox(_T("!"));

		}
	}
	*/
//	bMouseMove=false;

//	m_Left.OnLButtonUp(nFlags,point);
//	m_Right.OnLButtonUp(nFlags,point);

	if (bZoom)
	CDialog::OnLButtonUp(nFlags, point);
	else
	CDragDialog::OnLButtonUp(nFlags, point);
/*
	CPoint pos;
	::GetCursorPos(&pos);
	CMonitor move_to=CMonitors::GetNearestMonitor(pos);
	if (monitor==move_to)
	{
		CRect rect;
		monitor.GetMonitorRect( &rect );
		MoveWindow(0,0,rect.Width(),rect.Height());
	}*/
}

 


BOOL CIMAGEDISPLAY::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return true;
	return CDialog::OnEraseBkgnd(pDC);
}

void CIMAGEDISPLAY::OnStnClickedStaticLeft()
{
	// TODO: Add your control notification handler code here
//	m_Left.SetBitmap(HBITMAP(IDB_BITMAP_L3));
	GetParent()->PostMessage(WM_KEYDOWN,VK_LEFT,0);

}

void CIMAGEDISPLAY::OnStnClickedStaticRight()
{
//	m_Right.SetBitmap(HBITMAP(IDB_BITMAP_R3));
	// TODO: Add your control notification handler code here
	GetParent()->PostMessage(WM_KEYDOWN,VK_RIGHT,0);
}

void CIMAGEDISPLAY::OnStnClickedStaticZoom()
{
	// TODO: Add your control notification handler code here
	bZoom=!bZoom;
	Invalidate(false);
}

void CIMAGEDISPLAY::OnKillFocus(CWnd* pNewWnd)
{
	CDialog::OnKillFocus(pNewWnd);
//	bImageOn=false;

	// TODO: Add your message handler code here
}

void CIMAGEDISPLAY::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CDragDialog::OnClose();
}

void CIMAGEDISPLAY::OnStnClickedStaticPrev()
{
	// TODO: Add your control notification handler code here
	GetParent()->PostMessage(WM_KEYDOWN,VK_NEXT,0);
}

void CIMAGEDISPLAY::OnStnClickedStaticNext()
{
	// TODO: Add your control notification handler code here
	GetParent()->PostMessage(WM_KEYDOWN,VK_PRIOR,0);
}

void CIMAGEDISPLAY::OnStnClickedStaticRotate()
{
	// TODO: Add your control notification handler code here
	image.RotateRight();
	iRotateAngle++;

	CRect rect;
	monitor.GetMonitorRect( &rect );

	if ((int)image.GetWidth() <= rect.Width()
		&& (int)image.GetHeight() <= rect.Height())
		m_Zoom.ShowWindow(SW_HIDE);
	else
		m_Zoom.ShowWindow(SW_SHOW);

	Invalidate(FALSE);
}

void CIMAGEDISPLAY::OnStnClickedStaticRotate2()
{
	// TODO: Add your control notification handler code here
	image.RotateLeft();
	iRotateAngle=iRotateAngle+3;

	CRect rect;
	monitor.GetMonitorRect( &rect );

	if ((int)image.GetWidth() <= rect.Width()
		&& (int)image.GetHeight() <= rect.Height())
		m_Zoom.ShowWindow(SW_HIDE);
	else
		m_Zoom.ShowWindow(SW_SHOW);

	Invalidate(FALSE);
}


void CIMAGEDISPLAY::OnClickedStaticClosed()
{
	// TODO: Add your control notification handler code here
//	MSG msg;
//	msg.message = WM_KEYDOWN;
//	msg.wParam = VK_ESCAPE;
	PostMessage(WM_KEYDOWN, VK_ESCAPE, NULL);
}
