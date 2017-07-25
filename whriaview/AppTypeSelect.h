#pragma once

#include "../share/config.h"

// CAppTypeSelect dialog

class CAppTypeSelect : public CDialog
{
	DECLARE_DYNAMIC(CAppTypeSelect)

protected:
	client_config& config_;

public:
	CAppTypeSelect(client_config& c,CWnd* pParent = NULL);   // standard constructor
	virtual ~CAppTypeSelect();

// Dialog Data
	enum { IDD = IDD_DIALOG_SELECT_TYPE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSingle();
public:
	afx_msg void OnBnClickedButtonMulti();
public:
	afx_msg void OnBnClickedButtonExit();
};
