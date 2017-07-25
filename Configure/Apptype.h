#pragma once


// CApptype dialog

#include "../share/config.h"

class CApptype : public CDialog
{
	DECLARE_DYNAMIC(CApptype)

public:
	CApptype(CWnd* pParent = NULL);   // standard constructor
	virtual ~CApptype();

// Dialog Data
	enum { IDD = IDD_DIALOG_APPTYPE };

protected:
//	config& config_;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
public:
	afx_msg void OnBnClickedButtonExit();
};
