#if !defined(AFX_LISTCTRL_H__2EB671B4_0711_11D3_90AB_00E029355177__INCLUDED_)
#define AFX_LISTCTRL_H__2EB671B4_0711_11D3_90AB_00E029355177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// gxListCtrl window

#include "../share/datatype.h"
//#include "afxcmn.h"

typedef std::vector<int> modified_log;

class gxListCtrl : public CListCtrl
{
public:
			gxListCtrl (CString Text = _T(""));
    virtual ~gxListCtrl();

    CString DefaultText;

    CEdit*  EditSubItem (int Item, int Column);
    int	    HitTestEx (CPoint& Point, int* Column);
    int	    InsertItemEx (int Item);
    void    Resize (int cx, int cy);

    //{{AFX_VIRTUAL(gxListCtrl)
    //}}AFX_VIRTUAL
	void GetLog(modified_log& log);
	void ResetLog() {log_.clear();}
    void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	void DeleteAllItems()
	{
		CListCtrl::DeleteAllItems();
		ResetLog();
	}


protected:
	modified_log log_;

    //{{AFX_MSG(gxListCtrl)
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

    DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRL_H__2EB671B4_0711_11D3_90AB_00E029355177__INCLUDED_)
