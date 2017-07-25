#pragma once
#include "afxwin.h"


// CViewLogo dialog

class CViewLogo : public CDialog
{
	DECLARE_DYNAMIC(CViewLogo)

public:
	CViewLogo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CViewLogo();

// Dialog Data
	enum { IDD = IDD_DIALOG_VIEWLOGO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_Logo;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
