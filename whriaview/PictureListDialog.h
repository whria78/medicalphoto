#if !defined(AFX_PICTURELISTDIALOG_H__D7D9CF41_D0AA_46AE_84D7_F70713932E8A__INCLUDED_)
#define AFX_PICTURELISTDIALOG_H__D7D9CF41_D0AA_46AE_84D7_F70713932E8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PictureListDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPictureListDialog dialog
#include "IMAGEDISPLAY.h"
//#include "PicLoadingThread.h"
#include "TextProgressCtrl.h"
#include "Monitors.h"
#include "MultiMonitor.h"
#include "MonitorDC.h"
#include "../cximage/ximage.h"
#include "../client/whriaclient.h"
#include "tooltiplistctrl.h"
//#include "../tooltip/pptooltip.h"
#include "XBrowseForFolder.h"
#include "CSpreadsheet.h"
#include "../share/datatype.h"
#include "../share/config.h"
#include <boost/thread/condition.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "listctrl.h"

class CPictureListDialog : public CDialog
{
// Construction
public:
	CPictureListDialog(CWhriaClient& w,client_config& c,gxListCtrl& m_c,CWnd* pParent = NULL);   // standard constructor
//	BOOL LoadPicture(CStringArray* csaSelectFiles);

	// Loading Thread 
	void DrawListItem(int nItem);
	void DrawListCheck(int nItem);
	long GenerateThumb(const fileinfo& fileinfo_,CxImage& image);
	__int64 ImageLoad (const std::string& stNetPath,CxImage  *image,bool bThumbnail);

	BOOL bTerminateLoadingThread;

	CxImage blank_image;
	CBitmap blank_bitmap;

//	CDC*  pListDC;

	void Thread_Run(fileinfo_list m_Next); 
	void LoadPicture(const fileinfo_list& m_Next,const std::string& stRootPath);
	int PrepareLoad(const fileinfo_list& m_Next);

	BOOL ResetList();

//	boost::condition main_condition;
	boost::mutex main_mutex;

	boost::mutex thread_mutex;

	//

	CWnd* m_parent;

	fileinfo_list m_SelectedImage;
//	fileinfo_list m_SelectedImage_Next;

	CString stPrevSearch;

//	int iListInterval; // 너무 빨리 안하기 위해

	void Unselectall();

	void UpdateTooltip();
	void SetToolTipText(int iIndex);

	CString ChooseFolder();

// Dialog Data
	//{{AFX_DATA(CPictureListDialog)
	enum { IDD = IDD_DIALOG_PICTURELIST };
	CTextProgressCtrl	m_Progress;
	CToolTipListCtrl	m_PictureList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictureListDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	void GetCommentThread(const std::string& stNetPath);

	std::string stCurrentPath;

// Implementation
protected:
	CWhriaClient& WhriaClient;
	client_config& config_;
	gxListCtrl& m_CommentList;

	BOOL bCtrlOn;

	CFont		 m_font;
	CDC*  pListDC; 
	
	CImageList m_ImageListCheck;
	CImageList m_ImageListThumb;
	CImageList m_Img;

//	CWinThread* m_pWinThreadDir;

//	HBITMAP     hBitmap[5];

	CxImage CxImageList[5];
	CIMAGEDISPLAY ImageDisplay[5];
	CMonitor monitor[5];
	BOOL bZoom[5];
	BOOL bImageOn[5];
	POINT ZoomPoint[5];
	
	BOOL ShowPictureMultiMon(int iMonitor);

	BOOL bTReload;

	int iPrimaryMonitor;
	int iMonitorCount;
	int GetCurrentMonitor();

//	CString GetCheckedListByOrder(CStringArray* s_array,int* iItemNb,CString* iItem);
//	CNetFileInfo GetCheckedListByOrder(CNetFileInfoArray* nfia_db);

	// tooltip

//	CPPToolTip m_tooltip;

//	int InteliCheck(int iIndex);

	// Generated message map functions
	//{{AFX_MSG(CPictureListDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListPicturelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
//	afx_msg LRESULT LoadPictureByMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnBegindragListPicturelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickListPicturelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawListPicturelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPopupCopy();
	afx_msg void OnPopupToexcelfile();
	afx_msg void OnNMRclickListPicturelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLvnBeginScrollListPicturelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnEndScrollListPicturelist(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnPopupDelete();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTURELISTDIALOG_H__D7D9CF41_D0AA_46AE_84D7_F70713932E8A__INCLUDED_)
