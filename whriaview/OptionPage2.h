#pragma once


// COptionPage_UserManagement dialog

class COptionPage_UserManagement : public CDialog
{
	DECLARE_DYNAMIC(COptionPage_UserManagement)

public:
	COptionPage_UserManagement(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionPage_UserManagement();

// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_UserList;
	CString m_NewUser;

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
