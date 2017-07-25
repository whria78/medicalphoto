/********************************************************************************************
* MOD-NAME      : DialogEx.h
* LONG-NAME     : 
*
* AUTHOR        : Martin Ziacek (Martin.Ziacek@pobox.sk)
* DEPARTMENT    : 
* TELEPHONE     : 
* CREATION-DATE : 22/02/2000 09:15:33
* SP-NO         : 
* FUNCTION      : 
* 
*********************************************************************************************/
#ifndef __DIALOGEX_H__
#define __DIALOGEX_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ControlsEx.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogWhria 

class CDialogWhria : public CDialog
{
public:
	CDialogWhria();
	CDialogWhria(UINT nIDTemplate,CWnd* pParentWnd = NULL);

	CStatusBar* GetStatusBar() { return &m_CSBCtrlStatus; }				
	CToolBar*   GetToolBar()   { return &m_CSToolBar; }

// Implementation
protected:

	CDlgStatusBar	m_CSBCtrlStatus;
	CDlgToolBar		m_CSToolBar;
	UINT			m_nIDTracking;
	UINT			m_nIDLastMessage;
	BOOL			m_bResetPrompt;

	BOOL			m_bToolTips;
	BOOL			m_bStatusBar;
	BOOL			m_bToolBar;

	BOOL			m_bKillItself;

	BOOL			m_bModal;
	UINT			m_Timer;

	BOOL InitDialogEx(BOOL bToolTips = FALSE, BOOL bStatusBar = FALSE, UINT *pIndicators = NULL, UINT nIndicators = 0, UINT uiToolBar = 0, DWORD dwToolBarStyle = TBSTYLE_FLAT | WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogWhria)
	public:
	virtual void OnCancel();
	virtual void OnOK();
	virtual int DoModal();
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CDialogWhria)
	afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);
	afx_msg LRESULT OnPopMessageString(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetMessageString(WPARAM wParam, LPARAM lParam = 0L);
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	afx_msg void OnUpdateKeyIndicator(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStatusBarMenu(CCmdUI* pCmdUI);
	afx_msg void OnStatusBarCheck();
	afx_msg void OnToolBarCheck();
	afx_msg void OnUpdateToolBarMenu(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg LRESULT OnKickIdle(WPARAM, LPARAM lCount);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	BOOL OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

#endif //__DIALOGEX_H__

