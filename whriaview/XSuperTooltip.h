// XSuperTooltip.h  Version 1.1
//
// Author:  Hans Dietrich
//          hdietrich@gmail.com
//
// This software is released into the public domain.  You are free to use
// it in any way you like, except that you may not sell this source code.
//
// This software is provided "as is" with no expressed or implied warranty.
// I accept no liability for any damage or loss of business that this
// software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef XSUPERTOOLTIP_H
#define XSUPERTOOLTIP_H

#include "PPTooltip.h"

#define XSUPERTOOLTIP_DEFAULT_WIDTH 212

struct SUPER_TOOLTIP_INFO
{
	SUPER_TOOLTIP_INFO()
	{
		bSuperTooltip     = TRUE;
		pWnd              = NULL;
		nIDText           = 0;
		nIDTool           = 0;
		rectBounds        = CRect(0,0,0,0);
		nBehaviour        = PPTOOLTIP_NOCLOSE_OVER |
                            PPTOOLTIP_CLOSE_LEAVEWND |
                            PPTOOLTIP_MULTIPLE_SHOW;
		nSizeX            = 0;
		strHeader         = _T("");
		strBody           = _T("must not be empty");
		strFooter         = _T("");
		bLineAfterHeader  = FALSE;
		bLineBeforeFooter = FALSE;
		nBodyImage        = 0;
		nFooterImage      = 0;
		nVirtualKeyCode   = 0;
		nKeyCodeId        = 0;
		// default to black text on silver
		rgbBegin    = RGB(255,255,255);
		rgbMid      = RGB(242,242,246);
		rgbEnd      = RGB(212,212,224);
		rgbText     = RGB(0,0,0);
	};

	BOOL		bSuperTooltip;	// TRUE = super tooltip
	CWnd *		pWnd;			// pointer to window that contains the tool
	UINT		nIDText;		// ID of the string resource that contains the 
								// text for the tool
    UINT		nIDTool;		// ID of tool (can be anything)
    CRect		rectBounds;		// bounding rect for toolinfo to be displayed
	UINT        nBehaviour;		// the tooltip's behaviour
	int			nSizeX;			// custom size (0 if none) -
								// defaults to XSUPERTOOLTIP_DEFAULT_WIDTH
	CString		strHeader;		// super tooltip header (can be _T(""))
	CString		strBody;		//               body
	CString		strFooter;		//               footer (can be _T(""))
	BOOL		bLineAfterHeader;	// TRUE = draw line after header
	BOOL		bLineBeforeFooter;	// TRUE = draw line before footer
	UINT		nBodyImage;		// id of image to display in body (0 if none)
	UINT		nFooterImage;	// id of image to display in footer (0 if none)
	UINT		nVirtualKeyCode;	// virtual control code (VK_F1, etc.)
	UINT		nKeyCodeId;		// id that is sent to parent when nVirtualKeyCode
								// is seen (can be anything)
	COLORREF	rgbBegin;		// background begin color
	COLORREF    rgbMid;			// background mid color
	COLORREF	rgbEnd;			// background end color
	COLORREF	rgbText;		// text color
};

/////////////////////////////////////////////////////////////////////////////
// CXSuperTooltip window

class CXSuperTooltip : public CPPToolTip
{
// Construction
public:
	CXSuperTooltip();
	virtual ~CXSuperTooltip();

// Attributes
public:

// Operations
public:
	CString AddTool(SUPER_TOOLTIP_INFO * pTI);
	void AddTool(CWnd * pWnd, PPTOOLTIP_INFO & ti)
	{
		CPPToolTip::AddTool(pWnd, ti);
	}
	void AddTool(CWnd * pWnd, LPCTSTR lpszString = NULL, LPCRECT lpRectBounds = NULL, 
		DWORD dwIDTool = 0)
	{
		CPPToolTip::AddTool(pWnd, lpszString, lpRectBounds, dwIDTool);
	}
	BOOL Create(CWnd* pParentWnd, BOOL bBalloon = TRUE);
	int GetNextLine(CString strText, CString& strLine);
	CString GetBodyHtml(SUPER_TOOLTIP_INFO * pTI);
	enum ScreenTipScheme
	{
		SCREENTIP_SHOW_SUPER = 0,
		SCREENTIP_SHOW_NORMAL,
		SCREENTIP_SHOW_NONE
	};
	ScreenTipScheme GetScreenTipScheme() { return m_eScreenTipScheme; }
	void SetScreenTipScheme(ScreenTipScheme eScheme) { m_eScreenTipScheme = eScheme; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXSuperTooltip)
	//}}AFX_VIRTUAL

// Implementation
protected:
	ScreenTipScheme	m_eScreenTipScheme;
	void InitSuper();

	// Generated message map functions
protected:
	//{{AFX_MSG(CXSuperTooltip)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //XSUPERTOOLTIP_H
