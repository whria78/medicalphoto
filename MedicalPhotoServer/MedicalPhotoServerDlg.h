// MedicalPhotoServerDlg.h : header file
//

#if !defined(AFX_MedicalPhotoSERVERDLG_H__D01CA555_5104_4EBF_939C_70ABE16CC7C1__INCLUDED_)
#define AFX_MedicalPhotoSERVERDLG_H__D01CA555_5104_4EBF_939C_70ABE16CC7C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMedicalPhotoServerDlg dialog

#include "../boost.h"
#include "afxcmn.h"
#include <io.h>
#include <errno.h>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

#include "XBrowseForFolder.h"
#include "TrayDialog.h"

#include "option.h"
#include "connection_manager.h"
#include "DataManagerDlg.h"
//#include "viewlogo.h"
#include "modaless.h"

#include "AutoUpdater.h"

//#define SERVERUPDATEADDRESS _T("http://medicalphoto.org/repo/release/")
//#define SERVERUPDATECHECKADDRESS _T("http://medicalphoto.org/repo/update2/")
#define SETUPAPPLICATIONNAME _T("setup.exe")
#define CONFIG_EXE_FILENAME _T("Config.exe")

//#include "../MedicalPhotoServerCore/log_server.h"

/*
#include "../MedicalPhotoServerCore/data_manager.h"
*/

#include "../share/config.h"
#include "../share/cmycout.h"
#include "../share_mfc/logcommand.h"
#include "../share_mfc/ntservice.h"
//#include "../share/watcher.h"

class CMedicalPhotoServerDlg 
	: public CTrayDialog, public cFileSystemWatcher
{
// Construction
public:
	CMedicalPhotoServerDlg(config& c_,CWnd* pParent = NULL);	// standard constructor

	// watch log
/*	void OnChange(const tstring& filename_org);
	void StartWatch();
	void StopWatch();
	void HeartbeatThread();
	uintmax_t iOldSize;

*/
	BOOL SendFolderInfo();

	config& config_;
	CLogCommand log_;
//	CMyCout log_;
//	server server_;
//	log_server log_server_;
//	void StartLogThread();

	CConnection_Manager connection_manager_;
//	data_manager data_manager_;

//	boost::mutex server_run_mutex;
//	boost::mutex file_move_mutex;
//	boost::mutex build_info_mutex;

// Dialog Data
	//{{AFX_DATA(CMedicalPhotoServerDlg)
	enum { IDD = IDD_MedicalPhotoSERVER_DIALOG };
	CListCtrl	m_Log;
	CString	m_Folder;
/*	CString	m_Pass;
	CString	m_HospitalID;
	BOOL	m_AutoStart;
	BOOL	m_MinimizeAtStart;*/
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedicalPhotoServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	protected:
	HICON m_hIcon;

	CImageList m_Img;
	CStringArray csaAddress;

	CString ChooseFolder();


	bool UpdateStatus();


	CString IPListing(CStringArray *csaAddress);
	CString GetLocalIP();

	BOOL CheckValidFolder();

	void Exit();

//	BOOL	m_NTService;  // ¾ÆÁ÷ ¾È¾¸

	// Generated message map functions
	//{{AFX_MSG(CMedicalPhotoServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnMenuitemStart();
	afx_msg void OnMenuitemStop();
	afx_msg void OnMenuitemExit();
	afx_msg void OnButtonExit();
//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	afx_msg void OnStnClickedStaticCheck();
	afx_msg void OnBnClickedButtonOption();
	CListCtrl m_StateList;
public:
	afx_msg void OnTrayStart();
public:
	afx_msg void OnTrayStop();
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
public:
	afx_msg void OnTrayOpen();
public:
	afx_msg void OnBnClickedButtonCheckdata();
public:
	afx_msg void OnBnClickedButtonReloadlog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MedicalPhotoSERVERDLG_H__D01CA555_5104_4EBF_939C_70ABE16CC7C1__INCLUDED_)
