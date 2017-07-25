#pragma once

#include "../share/etc.h"

// CDialogInput dialog

class CDialogInput : public CDialog
{
	DECLARE_DYNAMIC(CDialogInput)

public:
	CDialogInput(const CString& m_default,CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogInput();

// Dialog Data
	enum { IDD = IDD_DIALOG_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_InputBox;
public:
	afx_msg void OnBnClickedOk();
};
