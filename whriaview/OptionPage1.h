#pragma once


#include "XBrowseForFolder.h"
#include "../share/config.h"
#include "../share/dxdb.h"
#include "afxwin.h"
// COptionPage_General dialog

class COptionPage_General : public CDialog
{
	DECLARE_DYNAMIC(COptionPage_General)

public:
	COptionPage_General(client_config& c,CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionPage_General();

// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	client_config& config_;

	DECLARE_MESSAGE_MAP()
public:
	CString m_IP;
	CString m_Passwd;
	BOOL m_bFilename;
	BOOL m_bID;
	BOOL m_bName;
	BOOL m_bDiagnosis;
	BOOL m_bICD;
	BOOL m_bComment;
	BOOL m_ChangeFilename;
	CListBox m_DxFile;
	CListBox m_ActiveDxFile;

public:
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
public:
	virtual BOOL OnInitDialog();
protected:
	void UpdateStatus();
	CString ChooseFolder(const CString& stTitle=_T("Select a Folder"));
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
};
