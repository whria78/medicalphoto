#if !defined(AFX_BMPBUTTON_H__7604480E_B8E7_11D5_8A13_00E0293DE0CC__INCLUDED_)
#define AFX_BMPBUTTON_H__7604480E_B8E7_11D5_8A13_00E0293DE0CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BmpButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBmpButton window

class CBmpButton : public CStatic
{
// Construction
public:
	CBmpButton();

	
	BOOL LoadButtonBitmaps(int idDefault, int idUp = -1, int idDown = -1);
	void ResetButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBmpButton();

	// Generated message map functions
protected:

	CBitmap m_bmpDefault;
	CBitmap	m_bmpUp;
	CBitmap m_bmpDown;

	//{{AFX_MSG(CBmpButton)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPBUTTON_H__7604480E_B8E7_11D5_8A13_00E0293DE0CC__INCLUDED_)
