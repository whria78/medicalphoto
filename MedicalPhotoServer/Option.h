#pragma once


// COption dialog
#include "../share/config.h"
#include "afxwin.h"
#include "XBrowseForFolder.h"

class COption : public CDialog
{
	DECLARE_DYNAMIC(COption)

public:
	COption(config& c,CWnd* pParent = NULL);   // standard constructor
	virtual ~COption();

// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	config& config_;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_SuperAdminPasswd;
	CString m_HospitalName;
	BOOL m_bAutostart;
	BOOL m_bMinimize;
	CString m_ThumbnailPath;
	int m_Thumb_Height;
	int m_Thumb_Width;
	CComboBox m_BackupInterval;

	BOOL UpdateData(BOOL bSaveAndValidate);

public:
	afx_msg void OnBnClickedButtonChooseThumbFolder();
public:
	int iBackup1,iBackup2;
	int iSchedule1,iSchedule2;
	int iCheck1,iCheck2;

	CComboBox m_Backup1;
	CComboBox m_Backup2;
	CComboBox m_Schedule1;
	CComboBox m_Schedule2;

	BOOL m_CheckDB_Start;

	CString ChooseFolder();

	void UpdateStatus();
public:
	virtual BOOL OnInitDialog();
public:
	CComboBox m_Check1;
public:
	CComboBox m_Check2;
public:
	afx_msg void OnCbnSelchangeComboSchedule1();
public:
	afx_msg void OnCbnSelchangeComboCheck1();
};
