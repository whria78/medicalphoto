// BmpButton.cpp : implementation file
//

#include "stdafx.h"
//#include "BmpButs.h"
#include "BmpButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpButton

CBmpButton::CBmpButton()
{
}

CBmpButton::~CBmpButton()
{
}


BEGIN_MESSAGE_MAP(CBmpButton, CStatic)
	//{{AFX_MSG_MAP(CBmpButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpButton message handlers

//--------------------------------------------------
//-- LoadButtonBitmaps
// Use this function to load the bitmaps you will 
// use for different states of the button
//---------------------------------------------------
BOOL CBmpButton::LoadButtonBitmaps(int idDefault, int idUp, int idDown)
{
	BOOL retVal = TRUE;

	retVal &= m_bmpDefault.LoadBitmap(idDefault);

	if (idUp < 0) m_bmpUp.LoadBitmap(idDefault);
	else retVal &= m_bmpUp.LoadBitmap(idUp);

	if (idDown < 0) m_bmpDown.LoadBitmap(idDefault);
	else retVal &= m_bmpDown.LoadBitmap(idDown);

	return retVal;
}

//--------------------------------------------------
//-- ResetButton
// Use this function to set the button default state
//---------------------------------------------------
void CBmpButton::ResetButton()
{
	SetBitmap(HBITMAP(m_bmpDefault));
}

//--------------------------------------------------
//-- ON_WM_LBUTTONDOWN
// Change the bitmap to "down" state
//---------------------------------------------------
void CBmpButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetBitmap(HBITMAP(m_bmpDown));

	CStatic::OnLButtonDown(nFlags, point);
}

//--------------------------------------------------
//-- ON_WM_LBUTTONDOWN
// Change the bitmap to "up" state
//---------------------------------------------------
void CBmpButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetBitmap(HBITMAP(m_bmpUp));

	CStatic::OnLButtonUp(nFlags, point);
}

//--------------------------------------------------
//-- ON_WM_MOUSEMOVE
// Change the bitmap to "selected" state
//---------------------------------------------------
void CBmpButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetBitmap(HBITMAP(m_bmpUp));

	CStatic::OnMouseMove(nFlags, point);
}
