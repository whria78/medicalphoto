#if !defined(AFX_TOOLTIPLISTCTRL_H__EA17BA6D_ADD2_49E3_AB67_45B65316D19F__INCLUDED_)
#define AFX_TOOLTIPLISTCTRL_H__EA17BA6D_ADD2_49E3_AB67_45B65316D19F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolTipListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CToolTipListCtrl window

#include <afxtempl.h>
#include "../whriaview/resource.h"
#include "RDragDropFiles.h"
#include "../client/whriaclient.h"

/////////////////////////////////////////////////////////////////////////////
// CToolTipListCtrl, v.1.0
// 
// A CListCtrl derived class that
// can display per SubItem tooltips by itself
//
// Author: Jo? Filipe de Castro Ferreira (jfilipe@isr.uc.pt)
// Based on Nate Maynard's (nate.maynard@neomation.com) CToolTipTreeCtrl
//
// Last Modified: 7/11/2001
//
// License: Quoting Nate Maynard,
//  "use it however you want. If it helps you out, drop me a line and let me know. :-)"
//
// Disclaimer: This code comes with no warranty of any kind whatsoever. Use at your own risk.
//
/////////////////////////////////////////////////////////////////////////////


//The initial state of m_wHitMask
#define INITIAL_HITMASK LVHT_ONITEMICON
//#define MAX_CHECK 1024

class CToolTipListCtrl : public CListCtrl
{
// Construction
public:
	CToolTipListCtrl();

	void SetRect(int width,int height)
	{
		T_Width=width;
		T_Height=height;
	}
	
	/*
	void SetRedraw(bool bSet)
	{
		bRedraw=bSet;
		CListCtrl::SetRedraw(bSet);
	}
	bool GetRedraw()
	{
		return bRedraw;
	}
	*/
	
	void SetInsert(bool bSet)
	{
		bInsert=bSet;
	}
	bool GetInsert()
	{
		return bInsert;
	}

// Attributes
public:
	void SetRedraw(bool bSet)
	{
		bEraseBGR=bSet;
		CListCtrl::SetRedraw(bSet);
	}
	void NoBKDrawOnce()
	{
		bEraseBKOnce=false;
	}
	void StopNoBKDrawOnce()
	{
		bEraseBKOnce=true;
	}

protected:
	BOOL bEraseBGR;
	BOOL bEraseBKOnce;

	bool bInsert;
	bool bSearch;
	std::string stCurrentPath;
	// Map's SubItems to related tooltip text
	CMapStringToString m_ToolTipMap; 
	// A bit mask of LVHT_* flags the control will show tooltips for
	WORD m_wHitMask; 
	std::vector<bool> bChecked;
	std::vector<bool> bCheckedEx;
	CImageList m_ImageListCheck;

	int T_Width,T_Height;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTipListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:


	bool GetCheck(int nItem);
	void SetCheck(int nItem,bool nCheck);

	void SetCheckEx(int nItem,bool nCheck);
	bool GetCheckEx(int nItem);

	//** CWnd Overrides **
	//Provide our own logic for HitTests, specifically, make ToolHitTests respond per SubItem
	virtual int OnToolHitTest(CPoint point, TOOLINFO * pTI) const;

	
    //** CTreeCtrl Overrides **
    //Overriding the Delete functions makes sure m_ToolTipMap doesn't have excess mappings
    virtual BOOL DeleteAllItems( );
    virtual BOOL DeleteItem( int nItem );


	//** Additional Functions **

	//Set the TVHT_* flags that will trigger the display of a tooltip
	WORD SetToolTipHitMask(WORD wHitMask);
	//Clear all tooltips
	virtual void DeleteAllToolTips();
	//Set the tooltip text for a specific SubItem
	virtual BOOL SetItemToolTipText( int nItem, int nSubItem, LPCTSTR lpszToolTipText ); 
	//Retrieves the tooltip text for a specific SubItem 
	virtual CString GetItemToolTipText( int nItem, int nSubItem ); 

	
	virtual ~CToolTipListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolTipListCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	//Respondes to the TTN_NEEDTEXT* messages, provides the text of a tooltip
	virtual afx_msg BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult ); 

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLTIPLISTCTRL_H__EA17BA6D_ADD2_49E3_AB67_45B65316D19F__INCLUDED_)
