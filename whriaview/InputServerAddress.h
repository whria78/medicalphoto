#if !defined(AFX_INPUTSERVERADDRESS_H__96AD47CE_7414_429F_A3F3_6D789C96505B__INCLUDED_)
#define AFX_INPUTSERVERADDRESS_H__96AD47CE_7414_429F_A3F3_6D789C96505B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputServerAddress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputServerAddress dialog

#include "../share/config.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include "afxwin.h"
#include <Wininet.h>

class CInputServerAddress : public CDialog
{
// Construction
public:
	CInputServerAddress(client_config& c,CWnd* pParent = NULL);   // standard constructor
	~CInputServerAddress()
	{
		boost::mutex::scoped_lock lock(search_mutex);

		for (int i=0;i<256;i++)
		{
			boost::mutex::scoped_lock lock(search_host_mutex[i]);
		}
		if (hInternet) {
			InternetCloseHandle(hInternet);
		}

	}

// Dialog Data
	//{{AFX_DATA(CInputServerAddress)
	enum { IDD = IDD_DIALOG_CLIENTCONFIG };

	CString stIPAddress;
	CString stPassword;
	CString	m_FTP_Pass;
	CString m_ID;

	client_config& config_;
	//}}AFX_DATA

	bool SearchHost(int iIndex,const std::string& ip,const std::string& port);


	HINTERNET CInputServerAddress::GetSession(CString &URL);
	bool DownloadConfig(HINTERNET hSession, BYTE *pBuf, DWORD bufSize);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputServerAddress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HINTERNET hInternet;

	CString IPListing(CStringArray *csaAddress);
	CString GetLocalIP();

	bool bConnected;
	boost::mutex search_mutex;
	boost::mutex search_host_mutex[256];
	bool bStop;

	// Generated message map functions
	//{{AFX_MSG(CInputServerAddress)
	virtual void OnOK();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedButtonUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CEdit m_IP;
	CEdit m_Password;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTSERVERADDRESS_H__96AD47CE_7414_429F_A3F3_6D789C96505B__INCLUDED_)
