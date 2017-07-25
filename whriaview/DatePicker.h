#pragma once


// CDatePicker dialog

class CDatePicker : public CDialog
{
	DECLARE_DYNAMIC(CDatePicker)

public:
	CDatePicker(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDatePicker();

// Dialog Data
	enum { IDD = IDD_DIALOG_DATEPICKER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CTime m_DateFrom;
	CTime m_DateTo;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
