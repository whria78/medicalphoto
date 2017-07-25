// ListCtrl.cpp : implementation file
//
#include "stdafx.h"

#include "ListCtrl.h"
#include "EditCell.h"
//#include "resource.h"		// main symbols

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_EDITCELL 1001

/////////////////////////////////////////////////////////////////////////////
// gxListCtrl

gxListCtrl::gxListCtrl (CString Text /* = "Some Text" */)
{
    DefaultText = Text;

}

gxListCtrl::~gxListCtrl()
{
}

BEGIN_MESSAGE_MAP(gxListCtrl, CListCtrl)
    //{{AFX_MSG_MAP(gxListCtrl)
    ON_WM_HSCROLL()
    ON_WM_VSCROLL()
//    ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndLabelEdit)
    ON_WM_LBUTTONDOWN()
    //}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(NM_CLICK, &gxListCtrl::OnNMClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// gxListCtrl message handlers

void 
gxListCtrl::Resize (int cx, int cy)
{
    CRect Rect (0, 0, cx, cy);
    MoveWindow (&Rect);
    InvalidateRect (Rect);
    SetColumnWidth (2, LVSCW_AUTOSIZE_USEHEADER);
}

CEdit* 
gxListCtrl::EditSubItem (int Item, int Column)
{
    // The returned pointer should not be saved

    // Make sure that the item is visible
    if (!EnsureVisible (Item, TRUE)) 
    {
		InsertItemEx (Item);
		if (!EnsureVisible (Item, TRUE)) 
			return NULL;
    }

    // Make sure that nCol is valid
    CHeaderCtrl* pHeader = (CHeaderCtrl*) GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();
    if (Column >= nColumnCount || GetColumnWidth (Column) < 5)
		return NULL;

    // Get the column offset
    int Offset = 0;
    for (int iColumn = 0; iColumn < Column; iColumn++)
		Offset += GetColumnWidth (iColumn);

    CRect Rect;
    GetItemRect (Item, &Rect, LVIR_BOUNDS);

    // Now scroll if we need to expose the column
    CRect ClientRect;
    GetClientRect (&ClientRect);
    if (Offset + Rect.left < 0 || Offset + Rect.left > ClientRect.right)
    {
		CSize Size;
		if (Offset + Rect.left > 0)
			Size.cx = -(Offset - Rect.left);
		else
			Size.cx = Offset - Rect.left;
		Size.cy = 0;
		Scroll (Size);
		Rect.left -= Size.cx;
    }

    // Get Column alignment
    LV_COLUMN lvCol;
    lvCol.mask = LVCF_FMT;
    GetColumn (Column, &lvCol);
    DWORD dwStyle;
    if ((lvCol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT)
		dwStyle = ES_LEFT;
    else if ((lvCol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT)
		dwStyle = ES_RIGHT;
    else dwStyle = ES_CENTER;

    Rect.left += Offset+4;
    Rect.right = Rect.left + GetColumnWidth (Column) - 3;
    if (Rect.right > ClientRect.right)
		Rect.right = ClientRect.right;

    dwStyle |= WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;
    CEdit *pEdit = new gxEditCell (this, Item, Column, GetItemText (Item, Column));
    pEdit->Create (dwStyle, Rect, this, IDC_EDITCELL);

    return pEdit;
}

int 
gxListCtrl::HitTestEx (CPoint& Point, int* pColumn)
{
    int ColumnNum = 0;
    int Row = HitTest (Point, NULL);
    
    if (pColumn)
		*pColumn = 0;

    // Make sure that the ListView is in LVS_REPORT
    if ((GetWindowLong (m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT)
		return Row;

    // Get the top and bottom row visible
    Row = GetTopIndex();
    int Bottom = Row + GetCountPerPage();
    if (Bottom > GetItemCount())
	    Bottom = GetItemCount();
    
    // Get the number of columns
    CHeaderCtrl* pHeader = (CHeaderCtrl*) GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();

    // Loop through the visible rows
    for(; Row <= Bottom; Row++)
    {
		// Get bounding rect of item and check whether point falls in it.
		CRect Rect;
		GetItemRect (Row, &Rect, LVIR_BOUNDS);
		if (Rect.PtInRect (Point))
		{
			// Now find the column
			for (ColumnNum = 0; ColumnNum < nColumnCount; ColumnNum++)
			{
				int ColWidth = GetColumnWidth (ColumnNum);
				if (Point.x >= Rect.left && Point.x <= (Rect.left + ColWidth))
				{
					if (pColumn)
						*pColumn = ColumnNum;
					return Row;
				}
				Rect.left += ColWidth;
			}
		}
    }
    return -1;
}

BOOL 
hexNumberToInt (CString HexNumber, int& Number)
{
    TCHAR* pStopString;
    Number = _tcstoul (HexNumber, &pStopString, 16);
    return Number != ULONG_MAX;
} // hexNumberToInt

int 
gxListCtrl::InsertItemEx (int Item)
{
    int Result = InsertItem (Item + 1, DefaultText);
//    CString ItemVal;

//	ItemVal.Format (_T("%d"), Item + 1);
    SetItemText (Item, 0, _T(""));

    SetColumnWidth (2, LVSCW_AUTOSIZE_USEHEADER);

	SetCheck(Item,true);

    return Result;
}

void 
gxListCtrl::OnHScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    if (GetFocus() != this) 
		SetFocus();
    
    CListCtrl::OnHScroll (nSBCode, nPos, pScrollBar);
}

void 
gxListCtrl::OnVScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    if (GetFocus() != this) 
		SetFocus();
    
    CListCtrl::OnVScroll (nSBCode, nPos, pScrollBar);
}

void 
gxListCtrl::OnEndLabelEdit (NMHDR* pNMHDR, LRESULT* pResult) 
{
    LV_DISPINFO *plvDispInfo = (LV_DISPINFO *)pNMHDR;
    LV_ITEM	*plvItem = &plvDispInfo->item;

    if (plvItem->pszText != NULL)
    {
		SetItemText (plvItem->iItem, plvItem->iSubItem, plvItem->pszText);
		log_.push_back(plvItem->iItem);
    }
    *pResult = FALSE;
}
void 
gxListCtrl::GetLog(modified_log& log)
{
	bool* bLog;
	bLog=new bool[GetItemCount()];

	int i;

	for (i=0;i<GetItemCount();i++)
	{
		bLog[i]=false;
	}
	for (unsigned i=0;i<log_.size();i++)
	{
		bLog[log_[i]]=true;
	}
	for (i=0;i<GetItemCount();i++)
	{
		if (bLog[i])
			log.push_back(i);
	}

	delete [] bLog;
}

void 
gxListCtrl::OnLButtonDown (UINT nFlags, CPoint Point) 
{
    CListCtrl::OnLButtonDown (nFlags, Point);

    int Index;
    int ColNum;
    if ((Index = HitTestEx (Point, &ColNum)) != -1)
    {
		if (ColNum==0) return;
		if (GetWindowLong (m_hWnd, GWL_STYLE) & LVS_EDITLABELS)
			EditSubItem (Index, ColNum);
    }
}

void gxListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	return;
	*pResult = 0;

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int iSelected=pNMListView->iItem;

	if (iSelected==-1) 
		InsertItemEx(GetItemCount());
}
