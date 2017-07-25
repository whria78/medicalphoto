#if !defined(AFX_MYTABCTRL_H__F3E8650F_019C_479F_9E0F_60FE1181F49F__INCLUDED_)
#define AFX_MYTABCTRL_H__F3E8650F_019C_479F_9E0F_60FE1181F49F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTabCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl window
#include "OptionPage1.h"
#include "OptionPage2.h"
//#include "CustomDiagnosisList.h"
#include "../share/config.h"
#include "../client/whriaclient.h"

class CMyTabCtrl : public CTabCtrl
{
// Construction
public:
	CMyTabCtrl(CWhriaCacheClient&w,client_config& c);
	CDialog *m_tabPages[3];
	int m_tabCurrent;
	int m_nNumberOfPages;

	client_config& config_;
	CWhriaCacheClient& WhriaClient;

// Attributes
public:

// Operations
public:
	void Init();
	void SetRectangle();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTabCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyTabCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyTabCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTABCTRL_H__F3E8650F_019C_479F_9E0F_60FE1181F49F__INCLUDED_)
