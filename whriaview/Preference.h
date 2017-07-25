#pragma once


// CPreference dialog
#include "MyTabCtrl.h"
#include "afxcmn.h"
#include "../share/config.h"
#include "../client/whriaclient.h"

class CPreference : public CDialog
{
	DECLARE_DYNAMIC(CPreference)

public:
	CPreference(CWhriaCacheClient&w,client_config& c,CWnd* pParent = NULL);   // standard constructor
	virtual ~CPreference();

	client_config& config_;
//	client_config config_old_;

	CWhriaCacheClient& WhriaClient;
// Dialog Data
	enum { IDD = IDD_DIALOG_OPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CMyTabCtrl m_OptionTabCtrl;
	afx_msg void OnBnClickedCancel();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
