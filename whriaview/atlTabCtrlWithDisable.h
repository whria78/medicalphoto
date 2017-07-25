#ifndef __ATL_TABCTRL_WITH_DISABLE__H
#define __ATL_TABCTRL_WITH_DISABLE__H

#pragma once

////////////////////////////////////////////////////////////////
// CTabCtrlWithDisable 1998 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// CTabCtrlWithDisable implements a CTabCtrl with tabs that you can disable.

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlWithDisable - Ported to WTL by Rashid Thadha 13/07/2002
//

#ifndef __ATLAPP_H__
	#error atltabctrlwithdisable.h requires atlctrls.h to be included first
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <class T, class TBase = CTabCtrl, class TWinTraits = CControlWinTraits>
class ATL_NO_VTABLE CTabCtrlWithDisableImpl : public CWindowImpl< T, TBase, TWinTraits >,
                                              public COwnerDraw< CTabCtrlWithDisableImpl >
{
public:
    CTabCtrlWithDisableImpl()
    {
    }
    
    virtual ~CTabCtrlWithDisableImpl() 
    {
    }

    BEGIN_MSG_MAP(CTabCtrlWithDisableImpl)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
        MESSAGE_HANDLER(WM_GETDLGCODE, OnGetDlgCode)
        REFLECTED_NOTIFY_CODE_HANDLER(TCN_SELCHANGING, OnSelChanging)
        CHAIN_MSG_MAP_ALT(COwnerDraw<CTabCtrlWithDisableImpl>, 1)
        DEFAULT_REFLECTION_HANDLER()
    END_MSG_MAP()

    virtual	BOOL IsTabEnabled(int nTab) = 0;  // you must override

	void Attach(HWND hWndNew)
	{
		ATLASSERT(::IsWindow(hWndNew));
        CWindowImpl< T, TBase, TWinTraits >::SubclassWindow(hWndNew);
        _Init();
	}

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
    {
        LRESULT lRes = DefWindowProc(uMsg, wParam, lParam);
        //@@ needs subclassing here, I suspect - Not tested when creating control dynamically
        _Init();
        return lRes;
    }

    void _Init()
    {
        ATLASSERT(::IsWindow(m_hWnd));
        ModifyStyle(0, TCS_OWNERDRAWFIXED);
        InitTabStatus();
    }

    BOOL SubclassDlgItem(UINT nID, HWND pParent)
    {
        if (!CWindowImpl< T, TBase, TWinTraits >::SubclassWindow(::GetDlgItem(pParent, nID)))
	        return FALSE;
        _Init();
        return TRUE;                
    }

    LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        LRESULT lRes = 0;
        short nShift = GetKeyState(VK_SHIFT);
        short nControl = GetKeyState(VK_CONTROL);
        
        bHandled = FALSE;
        switch (LOWORD(wParam))
        {                
            case VK_TAB :
            case VK_PRIOR :
            case VK_NEXT :
                {
                    if (nControl < 0)
                    {
		                int nNewTab = (LOWORD(wParam) == VK_PRIOR || nShift < 0) ?
			            PrevEnabledTab(GetCurSel(), TRUE) : NextEnabledTab(GetCurSel(), TRUE);
		                if (nNewTab >= 0)
			                SetActiveTab(nNewTab);
                        bHandled = TRUE;
                    }
                    else
                    {
                        // Normal Tab Mode
                        ::SetFocus(::GetNextDlgTabItem(GetParent(), m_hWnd, (nShift < 0)));

                    }
                }
            break;
            case VK_LEFT :
            case VK_RIGHT :
                {
		            int nNewTab = (LOWORD(wParam) == VK_LEFT) ?
			        PrevEnabledTab(GetCurSel(), TRUE) : NextEnabledTab(GetCurSel(), TRUE);
		            if (nNewTab >= 0)
			            SetActiveTab(nNewTab);
                    // No where to go lets set the focus back here
                    if (nNewTab == GetItemCount()-1)
                        ::SetFocus(m_hWnd);
                    bHandled = TRUE;
                }
            break;
            default :
               lRes = DefWindowProc(uMsg, wParam, lParam); 
            break;
        };
        
        return lRes;
    }

    int	NextEnabledTab(int nCurrentTab, BOOL bWrap)
    {
        int nTabs = GetItemCount();
	    if(nTabs)
        {
            for (int nTab = nCurrentTab+1; nTab != nCurrentTab; nTab++) 
            {
		        if (nTab >= nTabs) 
                {
			        if (!bWrap)
				        return -1;
			        nTab = 0;
		        }
		        if (IsTabEnabled(nTab)) 
                {
			        return nTab;
		        }
	        }
        }
	    return -1;    
    }

    int PrevEnabledTab(int nCurrentTab, BOOL bWrap)
    {
        for (int nTab = nCurrentTab-1; nTab != nCurrentTab; nTab--) 
        {
		    if (nTab < 0) 
            {
			    if (!bWrap)
				    return -1;
			    nTab = GetItemCount() - 1;
		    }
		    if (IsTabEnabled(nTab)) 
            {
			    return nTab;
		    }
            else
            {
                if (nTab == 0)
                    return GetItemCount() - 1;
            }
	    }
	    return -1;
    }

    BOOL SetActiveTab(UINT nNewTab)
    {
	    // send the parent TCN_SELCHANGING
	    NMHDR nmh;
	    nmh.hwndFrom = m_hWnd;
	    nmh.idFrom = GetDlgCtrlID();
	    nmh.code = TCN_SELCHANGING;

        if (::SendMessage(GetParent(), WM_NOTIFY, nmh.idFrom, (LPARAM)&nmh) >=0) {
		    // OK to change: set the new tab
		    SetCurSel(nNewTab);

		    // send parent TCN_SELCHANGE
		    nmh.code = TCN_SELCHANGE;
            ::SendMessage(GetParent(), WM_NOTIFY, nmh.idFrom, (LPARAM)&nmh);
		    return TRUE;
	    }
	    return FALSE;
    }

	LRESULT OnSelChanging(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
	    // Figure out index of new tab we are about to go to, as opposed
	    // to the current one we're at. Believe it or not, Windows doesn't
	    // pass this info
	    //
	    TCHITTESTINFO htinfo;
	    GetCursorPos(&htinfo.pt);
	    ScreenToClient(&htinfo.pt);
        htinfo.flags = TCHT_ONITEM;
	    int nNewTab = HitTest(&htinfo);

	    if (nNewTab != -1)
        {
            if (nNewTab >= 0 && !IsTabEnabled(nNewTab))
                return TRUE;// tab disabled: prevent selection
        }

		return 0;
	}

    void OnDrawText(CDCHandle& dc, CRect rc, CString sText, BOOL bDisabled)
    {
	    dc.SetTextColor(GetSysColor(bDisabled ? COLOR_3DHILIGHT : COLOR_BTNTEXT));
	    dc.DrawText(sText, -1, &rc, DT_CENTER|DT_VCENTER);

	    if (bDisabled) {
		    // disabled: draw again shifted northwest for shadow effect
		    rc += CPoint(-1,-1);
		    dc.SetTextColor(GetSysColor(COLOR_GRAYTEXT));
		    dc.DrawText(sText, -1, &rc, DT_CENTER|DT_VCENTER);
	    }
    }
    // Owner draw methods
    
    void DeleteItem(LPDELETEITEMSTRUCT lpdis)
    {
    }
    void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
    {
    }

    void DrawItem(LPDRAWITEMSTRUCT lpdis)
    {
        if (lpdis->itemID==-1)
            return; // If there are no list box items, skip this message. 
            
	    // use draw item DC
        CDCHandle dc(lpdis->hDC);

	    DRAWITEMSTRUCT& ds = *lpdis;
	    
	    int iItem = ds.itemID;

	    // Get tab item info
	    TCHAR text[512];
	    TCITEM tci;
	    tci.mask = TCIF_TEXT;
	    tci.pszText = text;
	    tci.cchTextMax = sizeof(text);
	    GetItem(iItem, &tci);

	    // calculate text rectangle and color
	    CRect rc = ds.rcItem;
	    rc += CPoint(1,4);						 // ?? by trial and error

	    // draw the text
	    OnDrawText(dc, rc, text, !IsTabEnabled(iItem));
    }	

    LRESULT OnGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
    {
        return DefWindowProc(uMsg, wParam, lParam) | DLGC_WANTALLKEYS;
    }

    void InitTabStatus()
    {
        // If first tab is disabled, go to next enabled tab
        if (!IsTabEnabled(0)) 
        {
	        int nTab = NextEnabledTab(0, TRUE);
	        SetActiveTab(nTab);
        }        
    }

protected:
};

class CTabCtrlWithDisable : public CTabCtrlWithDisableImpl<CTabCtrlWithDisable>
{
public:
    DECLARE_WND_CLASS(_T("WTL_TabCtrlWithDisable"))
};

#endif // __ATL_TABCTRL_WITH_DISABLE__H
