// WhriaViewDlg.h : header file
//

#if !defined(AFX_WHRIAVIEWDLG_H__9C3588E5_6F4B_41B0_8DF5_94785DC6A294__INCLUDED_)
#define AFX_WHRIAVIEWDLG_H__9C3588E5_6F4B_41B0_8DF5_94785DC6A294__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWhriaViewDlg dialog

#include "HyperlinkStatic.h"
#include "InputServerAddress.h"
#include "TextProgressCtrl.h"
#include "afxcmn.h"
#include "afxtempl.h"
#include "afxwin.h"
#include "selectdiagnosislist.h"
#include "CustomDiagnosisList.h"
#include "ProgressDialog.h"
#include "ViewLogo.h"
#include "DatePicker.h"

#include "listctrl.h"
#include "msppt9.h"

#include "../client/whriaclient.h"
#include "../share/config.h"
#include "../share/file.h"
#include "../share/codechange.h"
#include "../share/dxdb.h"
#include "../share/datatype.h"
#include "../share/etc.h"
#include "../share/imageprocess.h"

#include "../cximage/ximage.h"

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

#include "XBrowseForFolder.h"
#include "IMAGEDISPLAY.h"
#include "TextProgressCtrl.h"
#include "Monitors.h"
#include "MultiMonitor.h"
#include "MonitorDC.h"
#include "DialogInput.h"
#include "AppTypeSelect.h"
#include "dragdialog.h"
#include "SelectCheck.h"
#include "Preference.h"
#include "tooltiplistctrl.h"
#include "ACEdit.h"
#include "ColorListBox.h"
#include "XSuperTooltip.h"
#include "BasicExcel.hpp"

#define WM_CLICKPICTURE (WM_USER+1)
#define WM_IDLEPROCESS (WM_USER+3)
#define WM_REMOTESEARCH (WM_USER+4)

class CWhriaViewDlg : public CDialog
{
// Construction
public:
	CWhriaViewDlg(CMyCout&l, CWhriaCacheClient&w,CWnd* pParent = NULL);	// standard constructor

	~CWhriaViewDlg()
	{
//		pListDC->SelectObject(pOldFont);
//		if (pListDC->GetSafeHdc())
//			ReleaseDC(pListDC);
		if (bRunAssist)
			TerminateProcess(_T(ASSIST_APPLICATIONNAME));

		for (unsigned int i=0;i<ImageDisplay.size();i++)
		{
			delete ImageDisplay[i];
		}
		m_font.DeleteObject();
	}

	// MFC Core
	HICON m_hIcon;
	enum { IDD = IDD_WHRIAVIEW_DIALOG };

private:
	bool bRunAssist;
	BOOL GetProcess(CString name);
	BOOL TerminateProcess(CString name);
	
	CString TransMsg(UINT nID)
	{
		CString stMsg;
		stMsg.LoadString(nID);
		return stMsg;
	}
	CFont          cTreeFont;

protected:
	
	RGBQUAD border;

	CXSuperTooltip   m_tooltip;
	void InsertTooltip(int iControlID,const CString& stTitle,const CString& stMsg);

	// TREE
	CImageList m_smTreeImg;
	CString GetFilePathFromTree(HTREEITEM pTree);   //   /test/ 식으로 리턴
	void BrowseTree(HTREEITEM pTree);
	std::string stCurrentPath;
	CTreeCtrl	m_FolderTree;
	bool bTreeLeftClick;

	volname_list vol_list_;

	// ScreenSaver
	void CheckIdleThread();
	bool bIdle;
	bool bIdleDoModal;

	// ETCS

	CViewLogo m_ViewDlg;
	void Hide_Logo_Thread_Delay()
	{
		Sleep(2000);
		m_ViewDlg.ShowWindow(SW_HIDE);

		// STARTUP LOCK
		if (config_.server_config.Get(ADMIN_PASS).compare("") != 0)
		{
			bCheck_idleprocess = false;
			if (GetSafeHwnd())
				PostMessage(WM_IDLEPROCESS, NULL, NULL);
			bCheck_idleprocess = true;
		}
	}

	CString	m_Input;

	CString ChooseFolder(const CString& stTitle=_T("Select a Folder"));
	bool ExportPPT(const fileinfo_list& f_list);
	bool ExportXLS(fileinfo_list& f_list,const tstring& cstSheetName);
	void Exit();
	bool bExitFlag;

	HANDLE hMutex;
	void OnUpdatecheck(); 

	void UpdateDetails(bool bSkipRetrieve);
	void StopAll()
	{
		StopLoadingThread();
		StopCommentThread();
		StopBrowseThread();
		StopImageProcessThread();
		StopDxDBThread();
		boost::mutex::scoped_lock lock(click_mutex);
		StopThread(&bCheck_idleprocess);
		StopIdleSignalThread();
	}
	void StopLoadingThread();
	void StopCommentThread();
	void StopBrowseThread();
	void StopImageProcessThread();
	void StopDxDBThread();
	void StopIdleSignalThread();

	void StopThread(bool* bStopSign,bool* bMutexCheck);
	void StopThread(bool* bMutexCheck);

	BOOL UpdateData(BOOL bSaveAndValidate=1);
	void UpdateData_FileInfo(fileinfo& fileinfo_,bool bSaveAndValidate);

	void ErrorExit(const client_connection::ConnectionEx& err_);
	void ErrorExit(const basic_client::ConnectionEx& err_);

	// SEARCH

	BOOL Search();
	CString stSearch;
	CString stPrevSearch;

	// SOCKET
	CInputServerAddress m_dlg_inputserver;

	void UploadFiles(const filepath_list& path_list);
	void UploadFolder(const tstring& stLocalPath,HTREEITEM pTree);
	void UploadCommon(const std::vector<_tpath>& local_list,filepath_list& net_list,bool bCheck);

	BOOL Login(const std::string&stIP,const std::string&stPort,const std::string& stID,const std::string& stPasswd);
	client_config config_;
	CWhriaCacheClient& WhriaClient;
	user CurrentUser;

	// IMAGE LIST
	// picturelist

	void SetPictureListCheck(int iIndex,bool bCheck);
	void UpdateCheckList();

	fileinfo_list m_SelectedImage;
	unsigned int iCurrentLoadingIndex;

	fileinfo_list GetCheckedList();
	int GetCheckedListCount();
	void DisplayFileNumber(int iNum);
	void DrawListItem(int nItem,bool bDrawItem,bool bDrawCheck,bool bDrawSubitem);

	long GenerateThumb(const fileinfo& fileinfo_,CxImage& image);
	__int64 ImageLoad (const std::string& stNetPath,CxImage  *image,bool bThumbnail);

	bool bTerminateConnectionThread;
	bool bTerminateLoadingThread;
	bool bTerminateBrowseThread;
	bool bTerminateDxDBThread;

	CxImage blank_image;
	CBitmap blank_bitmap;

	int iThumb_Height;
	int iThumb_Width;
	void ProcessThumbnailSize();
	int old_cx,old_cy;

	void ConnectionThread();
	void Thread_Run(fileinfo_list m_Next); 
	void LoadPicture(const fileinfo_list& m_Next,const std::string& stRootPath);
	int PrepareLoad(const fileinfo_list& m_Next);

	BOOL ResetList();

	void Unselectall();
	void UpdateTooltip();
	void SetToolTipText(int iIndex);

	CFont m_font;
	CDC*  pListDC; 
	
	CImageList m_ImageListCheck;
	CImageList m_ImageListThumb;

	void ForwardPictureCache(int iIndex);

	// MUTEX

	boost::mutex comment_mutex;
	boost::mutex thread_mutex;
	boost::mutex browse_mutex;
	boost::mutex processimage_mutex;
	boost::mutex click_mutex;
	boost::mutex dxdb_mutex;
	boost::mutex connection_mutex;


	bool bMutexCheck_picturelist;
	bool bMutexCheck_browse;
	bool bMutexCheck_thread;
	bool bMutexCheck_comment;
	bool bMutexCheck_processimage;
	bool bMutexCheck_dxdb;
	bool bMutexCheck_connection;

	bool bCheck_idleprocess;

	//
	// Update

	bool Switch(CString executable, CString update);

	// Version control
	version_checker version_;

	// Comment
	CImageList m_CommentImg;

	void GetCommentThread(const std::vector<std::string>& stNetPath_list);
	void SaveComment(int iListIndex,const CString& stComment);
	void UndoAddCheckedComment(int iListIndex);
	void AddCheckedComment(int iListIndex);
	bool bCheckControl;


	// MULTIMONITOR

	std::vector<CIMAGEDISPLAY*> ImageDisplay;
	int iLastDisplay;
	void ProcessRotate(int iCurrentMonitor);
	void ProcessRotateThread(int iDisplaySelected,int iRotateAngle);
	
	BOOL ShowPictureMultiMon(int iMonitor);
	BOOL ShowPictureMultiMon2(int iMonitor);
	void HidePictureMultiMon(int iMonitor);

	int iMonitorCount;
	int GetCurrentMonitor();


	// VIEW MODE

	void SetAdvancedView();
	void SetBasicView();
	bool bAdvancedViewMode; // True=Advanced , FALSE=BASIC
	void ResizeWindow(int cx,int cy);
	void MoveCtrl(int iID,int a,int b,int c,int d);


	// DXDB
	DxDB DxDB_;

	void LoadDxDBThread();
	void ReLoadDxDBThread();
	void LoadDxDB();
	void ReLoadDxDB();


	afx_msg void OnDblclkListPicturelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindragListPicturelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickListPicturelist(NMHDR *pNMHDR, LRESULT *pResult);

	void OnNMClickListPicturelist(unsigned int iIndex);
	void OnNMClickListPicturelistThread(unsigned int iIndex);

	afx_msg void OnNMCustomdrawListPicturelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickListPicturelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnBeginScrollListPicturelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnEndScrollListPicturelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	// Generated message map functions
	//{{AFX_MSG(CWhriaViewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnButtonStop();
	void SetButtonStopStatus();
	afx_msg void OnButtonComment();
	afx_msg void OnSetfocusEditInput();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangedTreeRemote(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

		// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWhriaViewDlg)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

public:
	CString m_Dx;
	CString m_ID;
	CString m_Name;
	CString m_Date;
	CString m_ICD;
	afx_msg void OnEnKillfocusEditDx();

	afx_msg void OnBnClickedButtonSubmittag();
	CButton   m_stop_button;
	CButton   m_submit_ctrl;
	CButton  m_setup_ctrl;
	CButton  m_CustomDx_ctrl;
	CButton  m_ReloadThumb_Ctrl;
	CButton  m_About_Ctrl;
	afx_msg void OnNMRclickTreeRemote(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPopupCopy();
	afx_msg void OnPopupToexcelfile();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	gxListCtrl m_CommentList;
	comment_cluster_list active_comment_list_;

	afx_msg void OnNMDblclkListComment(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnViewAdvanced();
	afx_msg void OnViewBasic();
	afx_msg void OnPreferencePreference();
	afx_msg void OnAboutAbout();
	afx_msg void OnAboutUpdate();
	afx_msg void OnNMKillfocusListComment(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnPopupDelete2779();
	CTextProgressCtrl	m_Progress;
	CToolTipListCtrl	m_PictureList;
public:
	afx_msg void OnPopupListCopy();
public:
	afx_msg void OnPopupListToexcelfile();
public:
	afx_msg void OnPopupListDelete();
public:
	afx_msg void OnDestroy();
public:
	afx_msg void OnLvnEndlabeleditListComment(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnPopupTreeCreate();
public:
	afx_msg void OnTvnEndlabeleditTreeRemote(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnTvnBeginlabeleditTreeRemote(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnPopupRename();
public:
	afx_msg void OnPopupDelete();
public:
	afx_msg void OnPopupTopowerpointTree();
public:
	afx_msg void OnPopupTopowerpointList();
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
public:
	afx_msg void OnPopupListRename();
public:
	afx_msg void OnPopupTreeUpload();
public:
	afx_msg void OnPopupListUpload();
public:
	afx_msg void OnNMClickTreeRemote(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnHdnItemchangedListComment(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnDiagnosisUserdiagnosis();
	afx_msg void OnUploadUploadex();
	CStatic m_StaticF12;
	afx_msg void OnStnClickedStaticF12();
	afx_msg void OnEnKillfocusEditInput();
	afx_msg void OnPopupDisselectall();
	CColorListBox m_CheckList;
	bool bColorState;
//	std::vector<std::string> m_Checked_PathList;
	afx_msg void OnLbnDblclkListChecklist();
	CACEdit m_DxListCtrl;
	afx_msg void OnToolReport();
	afx_msg void OnPopupTreeReport();
	CEdit m_CEditName;
	CEdit m_CEditID;
	CEdit m_CEditSearch;
	CEdit m_CEditDate;
	CEdit m_CEditICD10;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WHRIAVIEWDLG_H__9C3588E5_6F4B_41B0_8DF5_94785DC6A294__INCLUDED_)
