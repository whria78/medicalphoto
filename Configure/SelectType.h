#pragma once


// CSelectType dialog

class CSelectType : public CDialog
{
	DECLARE_DYNAMIC(CSelectType)

public:
	CSelectType(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectType();

// Dialog Data
	enum { IDD = IDD_DIALOG_SELECTTYPE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int iType;
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonSingle();
	afx_msg void OnBnClickedButtonMulti();
};
