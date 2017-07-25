// ConfigureDlg.h : header file
//

#pragma once

#include "../share/config.h"

#include "DataIntegrity.h"
#include "Apptype.h"
#include "DataManagerDlg.h"
#include "Others.h"
#include "SelectFolders.h"
#include "AppType.h"
//#include "AutoUpdater.h"
#include "UpdateDlg.h"

#define SERVERUPDATEADDRESS _T("http://medicalphoto.org/repo/update2/")
#define SETUPAPPLICATIONNAME _T("setup.exe")

// CConfigureDlg dialog
class CConfigureDlg : public CDialog
{
// Construction
public:
	CConfigureDlg(config& c,CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CONFIGURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	bool bExpress;

	// Implementation
protected:

	bool bBuildThumb;
	bool bExecuteMonitor;

	void UpdatePos();
	HICON m_hIcon;
	config& config_;

	int iPosition;
	CDataIntegrity DataIntegrity;
	COthers Others;
	CSelectFolders SelectFolders;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPrev();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
