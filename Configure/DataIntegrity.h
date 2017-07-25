#pragma once
#include "afxwin.h"


// CDataIntegrity dialog
#include "../share/config.h"
#include "XBrowseForFolder.h"

class CDataIntegrity : public CDialog
{
	DECLARE_DYNAMIC(CDataIntegrity)

public:
	CDataIntegrity(config& c_,CWnd* pParent = NULL);   // standard constructor
	virtual ~CDataIntegrity();

// Dialog Data
	enum { IDD = IDD_DIALOG_DATAINTEGRITY };

	BOOL UpdateData(BOOL bSaveAndValidate);
	int iBackupTime1,iBackupTime2;
	int iSchedule1,iSchedule2;
	int iCheck1,iCheck2;

protected:
	CString ChooseFolder();
	void UpdateStatus();
	config& config_;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonBSelect();
	CString m_BackupFolder;
	CComboBox m_BackupTime1;
	CComboBox m_BackupTime2;
	CComboBox m_Schedule1;
	CComboBox m_Schedule2;
	CComboBox m_Check1;
	CComboBox m_Check2;
	BOOL m_CheckDB_Start;

public:
	afx_msg void OnCbnSelchangeComboBDate();
	afx_msg void OnCbnSelchangeComboSchedule1();
	afx_msg void OnCbnSelchangeComboCheckdata1();
public:
	virtual BOOL OnInitDialog();
};
