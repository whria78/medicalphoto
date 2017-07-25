#pragma once
#include "afxwin.h"
#include "../share/etc.h"
#include "../share/config.h"

// CViewLogo dialog

class CViewLogo : public CDialog
{
	DECLARE_DYNAMIC(CViewLogo)

public:
	CViewLogo(client_config& c,CWnd* pParent = NULL);   // standard constructor
	virtual ~CViewLogo();

// Dialog Data
	enum { IDD = IDD_DIALOG_VIEWLOGO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	client_config& config_;
	CString stPass;
public:
	CStatic m_Logo;
	bool bIdleStart;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
//	afx_msg void OnStnClickedStaticTip();
	CStatic m_logotip;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonViewlogoExit();
};
