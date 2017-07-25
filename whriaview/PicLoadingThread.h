#if !defined(AFX_PICLOADINGTHREAD_H__BC6FC89D_F107_4C41_9BF8_80EE708B1303__INCLUDED_)
#define AFX_PICLOADINGTHREAD_H__BC6FC89D_F107_4C41_9BF8_80EE708B1303__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PicLoadingThread.h : header file
//
//#include	"il\il.h"
//#include	"il\ilu.h"
//#include	"il\ilut.h"
#include "../TextProgress/TextProgressCtrl.h"
#include "../CxImage/ximage.h"
#include "../client/WhriaClient.h"
#include "../ctooltiplist/tooltiplistctrl.h"
#include "../share/config.h"

//#define WM_LOADPICTURE 500

/////////////////////////////////////////////////////////////////////////////
// CPicLoadingThread thread

class CPicLoadingThread : public CWinThread
{
	DECLARE_DYNCREATE(CPicLoadingThread)
protected:
	CPicLoadingThread(CWhriaClient& w);           // protected constructor used by dynamic creation

// Attributes
public:
	CImageList* m_ImageListThumb;

	CWhriaClient& WhriaClient;
	config Config;
	CToolTipListCtrl*	m_PictureList;
	CDC*  pListDC;

	CxImage blank_image;
	CBitmap blank_bitmap;

	fileinfo_list m_SelectedImage;
	fileinfo_list* m_SelectedImage_Next;
	fileinfo_list* m_GlobalSelectedImage;

	CTextProgressCtrl*	m_Progress;
	CWnd* m_parent;

	BOOL bTerminate;
	BOOL bNext;
	BOOL bCheckTerminate;

	int iListInterval; // 너무 빨리 안하기 위해

private:
	void DrawListItem(int nItem);
	long GenerateThumb(const fileinfo& fileinfo_,CxImage& image);
	__int64 ImageLoad (const std::string& stNetPath,CxImage  *image);

	int PrepareLoad();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicLoadingThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPicLoadingThread();

	// Generated message map functions
	//{{AFX_MSG(CPicLoadingThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICLOADINGTHREAD_H__BC6FC89D_F107_4C41_9BF8_80EE708B1303__INCLUDED_)
