#pragma once
#include "afxcmn.h"

#include "../share/datatype.h"


// CSelectCheck dialog

class CSelectCheck : public CDialog
{
	DECLARE_DYNAMIC(CSelectCheck)

public:
	CSelectCheck(fileinfo_list& f_list,CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectCheck();

// Dialog Data
	enum { IDD = IDD_DIALOG_SELECTCHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	fileinfo_list& f_list;
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedCancel();
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
