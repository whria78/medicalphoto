#if !defined(AFX_IMAGEDISPLAY_H__6E839C76_57BD_4487_80F8_95B73B3E2338__INCLUDED_)
#define AFX_IMAGEDISPLAY_H__6E839C76_57BD_4487_80F8_95B73B3E2338__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IMAGEDISPLAY.h : header file
//

#include "../CxImage/ximage.h"
#include "Monitors.h"
#include "MultiMonitor.h"
#include "MonitorDC.h"
#include "../share/datatype.h"
#include "afxwin.h"
#include "bmpbutton.h"
#include "dragdialog.h"

/////////////////////////////////////////////////////////////////////////////
// CIMAGEDISPLAY dialog

class CIMAGEDISPLAY : public CDragDialog
{
// Construction
public:
	CIMAGEDISPLAY(CWnd* pParent = NULL);   // standard constructor

	CxImage  image;
	fileinfo fileinfo_;

	CDialog* m_parent;
	CMonitor monitor;

	BOOL bZoom;
	POINT pZoomPoint;

	POINT pMoveTo;
	POINT pMoveFrom;
	bool bImageOn;
	int iDisplaySelected;
	int iRotateAngle;

	void Reset()
	{
		iRotateAngle=0;
		iDisplaySelected=-1;
		bImageOn=false;
		bZoom=false;
		fileinfo_.clear();
	}

	void ResetButtons();
	void ResetToolTip()
	{
/*		int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

		m_tooltip.RemoveAllTools();
		CString info=fileinfo_.get_tooltip_info().c_str();
		m_tooltip.AddTool(this, info ,CRect (nScreenWidth/2-50, nScreenHeight/2-50, nScreenWidth/2+50, nScreenHeight/2+50));
*/
	}

//	void UpdateImage();

// Dialog Data
	//{{AFX_DATA(CIMAGEDISPLAY)
	enum { IDD = IDD_DIALOG_IMAGEDISPLAY };
	CStatic	m_Picture;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIMAGEDISPLAY)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMonitor current_monitor;

	long iZoomRate; // 10 = 100 % ªÁ¿Ã
//	CPPToolTip m_tooltip;
	// Generated message map functions
	//{{AFX_MSG(CIMAGEDISPLAY)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	CBmpButton m_Left;
	CBmpButton m_Right;
	CBmpButton m_Zoom;

	afx_msg void OnStnClickedStaticLeft();
	afx_msg void OnStnClickedStaticRight();
public:
	afx_msg void OnStnClickedStaticZoom();
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
public:
	afx_msg void OnClose();
public:
	CBmpButton m_NextBtn;
public:
	CBmpButton m_PrevBtn;
public:
	afx_msg void OnStnClickedStaticPrev();
public:
	afx_msg void OnStnClickedStaticNext();
public:
	CBmpButton m_Rotate;
public:
	afx_msg void OnStnClickedStaticRotate();
	CBmpButton m_RotateReverse;
	afx_msg void OnStnClickedStaticRotate2();
	CBmpButton m_ClosedBtn;
	afx_msg void OnClickedStaticClosed();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEDISPLAY_H__6E839C76_57BD_4487_80F8_95B73B3E2338__INCLUDED_)
