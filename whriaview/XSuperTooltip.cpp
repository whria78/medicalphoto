// XSuperTooltip.cpp  Version 1.1
//
// Author:  Hans Dietrich
//          hdietrich@gmail.com
//
// Description:
//     XSuperTooltip implements CXSuperTooltip, a class that displays
//     a super tooltip like those in Office 2007.  See article on
//     www.codeproject.com for details.
//
// History
//     Version 1.1 - 2006 August 4
//     - Changes to more closely emulate Office 2007 super tooltips
//       (see article on www.codeproject.com for details).
//
//     Version 1.0 - 2006 July 31
//     - Initial public release
//
// License:
//     This software is released into the public domain.  You are free to use
//     it in any way you like, except that you may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XSuperTooltip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CXSuperTooltip, CPPToolTip)
	//{{AFX_MSG_MAP(CXSuperTooltip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// ctor
CXSuperTooltip::CXSuperTooltip()
{
	m_eScreenTipScheme = SCREENTIP_SHOW_SUPER;
}

///////////////////////////////////////////////////////////////////////////////
// dtor
CXSuperTooltip::~CXSuperTooltip()
{
}

///////////////////////////////////////////////////////////////////////////////
// Create
BOOL CXSuperTooltip::Create(CWnd* pParentWnd, 
							BOOL bBalloon /*= TRUE*/)
{
	BOOL bRet = CPPToolTip::Create(pParentWnd, bBalloon);

	ASSERT(bRet);
	if (!bRet)
	{
		TRACE(_T("ERROR: CPPToolTip::Create failed\n"));
	}
	else
	{
		InitSuper();
	}
	return bRet;
}

///////////////////////////////////////////////////////////////////////////////
// InitSuper
void CXSuperTooltip::InitSuper()
{
	SetSize(CPPToolTip::PPTTSZ_MARGIN_CX, 6);
	SetSize(CPPToolTip::PPTTSZ_MARGIN_CY, 4);
	SetSize(CPPToolTip::PPTTSZ_ROUNDED_CX, 2);
	SetSize(CPPToolTip::PPTTSZ_ROUNDED_CY, 2);
	SetSize(CPPToolTip::PPTTSZ_WIDTH_ANCHOR, 0);
	SetSize(CPPToolTip::PPTTSZ_HEIGHT_ANCHOR, 0);
	SetBorder(RGB(118,118,118));
	SetTooltipShadow(5, 5, 20, TRUE, 3, 3);
	//SetDebugMode(TRUE);
	SetNotify();
	SetColorBk(RGB(255, 0, 0));
	SetMaxTipWidth(XSUPERTOOLTIP_DEFAULT_WIDTH);
	SetDelayTime(TTDT_AUTOPOP, 60000);
	BOOL bFade = FALSE;
	SystemParametersInfo(SPI_GETTOOLTIPFADE, 0, &bFade, 0);
	if (bFade)
		SetDelayTime(PPTOOLTIP_TIME_FADEOUT, 80);
	else
		SetDelayTime(PPTOOLTIP_TIME_FADEOUT, 0);
}

#if 0  // Example of generated HTML:
<font color=#000000><b>Merge and Center</b>
<indent>
Joins the selected cells into one larger cell and centers the contents in the new cell. </indent>
<indent>
This is often used to create labels that span multiple columns.</indent></font><indent size=-50><br>
<hr width=500px color=#69696B></indent>
<table>
<tr>
<td width=20><ilst idres=131 mask cx=16 cy=16 width=100% height=100%></td><br>
<td><b><font color=#000000>Press F1 for more help</b></td></font></tr></table>
#endif // end example

///////////////////////////////////////////////////////////////////////////////
// AddTool
CString CXSuperTooltip::AddTool(SUPER_TOOLTIP_INFO * pTI)
{
	//TRACE(_T("in CXSuperTooltip::AddTool\n"));

	InitSuper();

	PPTOOLTIP_INFO ti;

	int nWidth = pTI->nSizeX ? pTI->nSizeX : XSUPERTOOLTIP_DEFAULT_WIDTH;
	SetMaxTipWidth(nWidth);

	CString str = _T("");
	CString strHtml = _T("");

	if ((pTI->pWnd == 0) || (!::IsWindow(pTI->pWnd->m_hWnd)))
	{
		TRACE(_T("ERROR: bad pWnd\n"));
		ASSERT(FALSE);
		return _T("");
	}

	//TRACE(_T("pTI->pWnd->m_hWnd=0x%X\n"), pTI->pWnd->m_hWnd);

	if (GetScreenTipScheme() == SCREENTIP_SHOW_SUPER)
	{
		// show super tooltip

		ti.bSuperTooltip = TRUE;

		if (pTI->strBody.IsEmpty())
		{
			TRACE(_T("ERROR: body is empty\n"));
			ASSERT(FALSE);
			return _T("");
		}

		//TRACE(_T("rgbBegin=%06X  rgbMid=%06X  rgbEnd=%06X\n"), pTI->rgbBegin, pTI->rgbMid, pTI->rgbEnd);

		ti.crBegin         = pTI->rgbBegin;
		ti.crMid           = pTI->rgbMid;
		ti.crEnd           = pTI->rgbEnd;
		ti.nDirection      = PPTOOLTIP_TOPEDGE_LEFT;
		ti.nEffect         = CPPDrawManager::EFFECT_HSHADE;
		ti.nMask           = PPTOOLTIP_MASK_COLORS | 
							 PPTOOLTIP_MASK_DIRECTION |
							 PPTOOLTIP_MASK_EFFECT |
							 PPTOOLTIP_MASK_BEHAVIOUR;
		ti.nVirtualKeyCode = pTI->nVirtualKeyCode;
		ti.nKeyCodeId      = pTI->nKeyCodeId;
		ti.nIDTool         = pTI->nIDTool;
		ti.nBehaviour      = pTI->nBehaviour;

		// clean up input text

		pTI->strHeader.Replace(_T('\r'), _T(' '));
		pTI->strBody.Replace(_T('\r'), _T(' '));
		pTI->strFooter.Replace(_T('\r'), _T(' '));

		// add header to html

		BYTE r = GetRValue(pTI->rgbText);
		BYTE g = GetGValue(pTI->rgbText);
		BYTE b = GetBValue(pTI->rgbText);
		CString strFont = _T("");
		strFont.Format(_T("<font color=#%02X%02X%02X>"), r, g, b);

		strHtml += strFont;

		BOOL bHeader = !pTI->strHeader.IsEmpty();

		if (bHeader)
		{
			strHtml += _T("<b>");
			strHtml += pTI->strHeader;
			strHtml += _T("</b>");

			if (pTI->bLineAfterHeader)
			{
				COLORREF rgbHR = ti.crBegin;
				long lScale = 60;
				long red   = MulDiv(GetRValue(rgbHR),(255-lScale),255);
				long green = MulDiv(GetGValue(rgbHR),(255-lScale),255);
				long blue  = MulDiv(GetBValue(rgbHR),(255-lScale),255);
				rgbHR = RGB(red, green, blue); 

				str.Format(_T("<br><hr color=#%02X%02X%02X>"),
							GetRValue(rgbHR),
							GetGValue(rgbHR),
							GetBValue(rgbHR));
				strHtml += str;
			}
			else
			{
				strHtml += _T("\r\n");
			}
		}

		if (pTI->nBodyImage)
		{
			SetMaxTipWidth(nWidth + 100);

			strHtml += _T("<br><table><tr><td width=98>");
			str.Format(_T("<bmp idres=%d>"), pTI->nBodyImage);
			strHtml += str;
			strHtml += _T("</td><td width=190>");
		}

		CString strBodyHtml = GetBodyHtml(pTI);

		strHtml += strBodyHtml;
		strHtml += _T("</font>");

		if (pTI->nBodyImage)
		{
			strHtml += _T("</td></tr></table>");
		}

		if (!pTI->strFooter.IsEmpty())
		{
			// add footer to html

			if (pTI->bLineBeforeFooter)
			{
				COLORREF rgbHR = ti.crEnd;
				long lScale = 60;
				long red   = MulDiv(GetRValue(rgbHR),(255-lScale),255);
				long green = MulDiv(GetGValue(rgbHR),(255-lScale),255);
				long blue  = MulDiv(GetBValue(rgbHR),(255-lScale),255);
				rgbHR = RGB(red, green, blue); 

				str.Format(_T("<br><hr color=#%02X%02X%02X>"),
							GetRValue(rgbHR),
							GetGValue(rgbHR),
							GetBValue(rgbHR));
				strHtml += str;
			}
			else
			{
				strHtml += _T("\r\n");
			}

			if (pTI->nFooterImage)
			{
				strHtml += _T("\r\n<table>\r\n");
				strHtml += _T("<tr>\r\n");
				str.Format(_T("<td width=20><ilst idres=%d mask cx=16 cy=16 ")
						   _T("width=100%% height=100%%></td><br>\r\n"), pTI->nFooterImage);
				strHtml += str;
				strHtml += _T("<td><b>");
				strHtml += strFont;
				strHtml += pTI->strFooter;
				strHtml += _T("</b></td>");
				strHtml += _T("</font>");
				strHtml += _T("</tr></table>");
			}
			else
			{
				strHtml += _T("\r\n<b>");
				strHtml += pTI->strFooter;
				strHtml += _T("</b>\r\n");
			}
		}
		else if (pTI->nBodyImage)
		{
			strHtml += _T("\r\n");
		}

		ti.sTooltip = strHtml;

		CPPToolTip::AddTool(pTI->pWnd, ti);
	}
	else if (GetScreenTipScheme() == SCREENTIP_SHOW_NORMAL)
	{
		// show normal tooltip

		if (!pTI->strHeader.IsEmpty())
		{
			SetColorBk(GetSysColor(COLOR_INFOBK));
			SetIgnoreEnabledStatus(TRUE);
			SetSize(CPPToolTip::PPTTSZ_MARGIN_CX, 4);
			SetSize(CPPToolTip::PPTTSZ_MARGIN_CY, 2);
			SetSize(CPPToolTip::PPTTSZ_ROUNDED_CX, 0);
			SetSize(CPPToolTip::PPTTSZ_ROUNDED_CY, 0);
			SetSize(CPPToolTip::PPTTSZ_MARGIN_ANCHOR, 40);
			SetSize(CPPToolTip::PPTTSZ_HEIGHT_ANCHOR, 8);
			
			SetTooltipShadow(0, 0);
			SetBorder(RGB(0,0,0));

			ti.bSuperTooltip = FALSE;
			ti.nDirection    = PPTOOLTIP_LEFTEDGE_BOTTOM;
			ti.nBehaviour    = PPTOOLTIP_DISABLE_AUTOPOP |
							   PPTOOLTIP_NOCLOSE_OVER |
							   PPTOOLTIP_CLOSE_LEAVEWND |
							   PPTOOLTIP_MULTIPLE_SHOW;
			ti.nMask         = PPTOOLTIP_MASK_DIRECTION | PPTOOLTIP_MASK_BEHAVIOUR;

			pTI->strHeader.Replace(_T('\r'), _T(' '));
			strHtml = pTI->strHeader;
			ti.sTooltip = strHtml;
			CPPToolTip::AddTool(pTI->pWnd, ti);
		}
	}
	else
	{
		// show nothing
	}

	return strHtml;
}

///////////////////////////////////////////////////////////////////////////////
// GetBodyHtml
CString CXSuperTooltip::GetBodyHtml(SUPER_TOOLTIP_INFO * pTI)
{
	CString strHtml = _T("");

	CString strBody = pTI->strBody;

	int nLen = strBody.GetLength();

	if (nLen > 0)
	{
		BOOL bHeader = !pTI->strHeader.IsEmpty();
		int nTotal = 0;
		CString str = _T("");

		// loop to extract body
		for (;;)
		{
			str = _T("");

			int n = GetNextLine(strBody, str);
			if (n == 0)
				break;

			// add \r\n after previous line
			if (nTotal > 0)
			{
				strHtml += _T("\r\n");
			}

			if (!str.IsEmpty())
			{
			   // add next line to html

				if ((bHeader) && (pTI->nBodyImage == 0))
				{
					if ((nTotal == 0) && (!pTI->bLineAfterHeader))
						strHtml += _T("<indent>");
					else if (nTotal > 0)
						strHtml += _T("<indent>");
					else
						strHtml += _T("<b>");	// bold first text line after header,
												// if there is hr line drawn under header
					strHtml += _T("\r\n");
				}
				else if (nTotal > 0)
				{
					strHtml += _T("\r\n");
				}

				strHtml += str;

				if ((bHeader) && (pTI->nBodyImage == 0))
				{
					if ((nTotal == 0) && (!pTI->bLineAfterHeader))
						strHtml += _T("</indent>");
					else if (nTotal > 0)
						strHtml += _T("</indent>");
					else
						strHtml += _T("</b>");
				}

				strBody = strBody.Mid(n);
			}

			nTotal += n;

			if (nTotal >= nLen)
				break;
		}
	}

	return strHtml;
}

///////////////////////////////////////////////////////////////////////////////
// GetNextLine
int CXSuperTooltip::GetNextLine(CString strText, CString& strLine)
{
	int n = 0;
	strLine = _T("");
	int nLen = strText.GetLength();

	if (nLen > 0)
	{
		// a line is defined to be everything up to the next '\n'
		// -or- the end of strText

		TCHAR next = _T('\0');

		for (;;)
		{
			if (n >= nLen)
				break;

			next = strText[n];
			n++;

			if (next == _T('\n'))
			{
				break;
			}
			else
			{
				strLine += next;
			}
		}
	}

	strLine.TrimLeft();
	strLine.TrimRight();

	// return value includes ending '\n' if any
	return n;
}
