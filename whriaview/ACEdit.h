#if !defined(AFX_ACEDIT_H__56D21C13_ECEA_41DF_AADF_55980E861AC2__INCLUDED_)
#define AFX_ACEDIT_H__56D21C13_ECEA_41DF_AADF_55980E861AC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ACEdit.h : Header-Datei
//

/*********************************************************************
*
* CACEdit
* Copyright (c) 2003 by Andreas Kapust
* All rights reserved.
* info@akinstaller.de
*
*********************************************************************/

#define WM_AUTOCOMPLETE (WM_USER+2) 

#define _MODE_ONLY_FILES		(1L << 16)
#define _MODE_ONLY_DIRS			(1L << 17)

#define _MODE_STANDARD_			(1L << 0)
#define _MODE_SEPARATION_		(1L << 1)
#define _MODE_FILESYSTEM_		(1L << 2)
#define _MODE_FS_START_DIR_		(1L << 3)
#define _MODE_CURSOR_O_LIST_	(1L << 4)
#define _MODE_FIND_ALL_			(1L << 5)

#define _MODE_FS_ONLY_FILE_	(_MODE_FILESYSTEM_|_MODE_ONLY_FILES)
#define _MODE_FS_ONLY_DIR_	(_MODE_FILESYSTEM_|_MODE_ONLY_DIRS)
#define _MODE_SD_ONLY_FILE_	(_MODE_FS_START_DIR_|_MODE_ONLY_FILES)
#define _MODE_SD_ONLY_DIR_	(_MODE_FS_START_DIR_|_MODE_ONLY_DIRS)  //Fix 1.2

/////////////////////////////////////////////////////////////////////////////
// Fenster CACEdit 
#include "ACListWnd.h"
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "../share/etc.h"

class CACEdit : public CWnd //CEdit
{
// Konstruktion
public:
	CACEdit();
	void SetMode(int iMode=_MODE_STANDARD_);
	void SetSeparator(LPCTSTR lpszString,TCHAR lpszPrefixChar = 0)
		{
		m_SeparationStr = lpszString;
		m_Liste.m_PrefixChar = m_PrefixChar = lpszPrefixChar;
		SetMode(_MODE_SEPARATION_);
		}

	// CComboBox
	int AddString( LPCTSTR lpszString);
	int GetLBText( int nIndex, LPTSTR lpszText );
	void GetLBText( int nIndex, CString& rString );
	int SetDroppedWidth(UINT nWidth);
	int FindString( int nStartAfter, LPCTSTR lpszString );
	int SelectString( int nStartAfter, LPCTSTR lpszString );
	void ShowDropDown(BOOL bShowIt = TRUE );
	void ResetContent();
	int GetCurSel();
	// Attribute
public:
	void Init();
	void AddSearchString(LPCTSTR lpszString);
	void AddSearchStrings(LPCTSTR Strings[]);
	void RemoveSearchAll();
	void SetStartDirectory(LPCTSTR lpszString);

	void SetTemporaryDisable()
	{
		temp_disable=true;
	}

	// Operationen
public:

// ?erschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions?erschreibungen
	//{{AFX_VIRTUAL(CACEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CACEdit();
	CACListWnd m_Liste;
	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	CString m_EditText, m_SeparationStr,m_LastDirectory;
	TCHAR m_PrefixChar;
	int m_iMode;
	//{{AFX_MSG(CACEdit)
	afx_msg void OnKillfocus();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChange();
	afx_msg void OnCloseList();
	//}}AFX_MSG
	afx_msg LONG OnUpdateFromList(UINT lParam, LONG wParam);
	DECLARE_MESSAGE_MAP()


	void FindListString(int nStartAfter,LPCTSTR lpszString)
	{
//		FindListString_Thread(nStartAfter,lpszString);
		if (temp_disable)
		{
			temp_disable=false;
			return;
		}
		bFocusState=true;
		boost::thread BuildThread(boost::bind(&CACEdit::FindListString_Thread,this
			,nStartAfter
			,lpszString));
	}

	bool bFocusState;
	boost::mutex edit_mutex;
	bool bMutexCheck_dxsearch;
	bool bTerminate_dxsearch;
	void FindListString_Thread(int nStartAfter,LPCTSTR lpszString)
	{
		ThreadControl ThreadControl_(DXSEARCH_THREAD);
		boost::mutex::scoped_lock lock(edit_mutex);
		if (!ThreadControl_.Check(&bMutexCheck_dxsearch))
			return;
		Utility::sleep(100);
		if (!ThreadControl_.Check(&bMutexCheck_dxsearch))
			return;

//		m_Liste.ShowWindow(false);
		if (bTerminate_dxsearch)
			return;

		if (bFocusState)
			m_Liste.FindString(nStartAfter,lpszString);
	}

	bool temp_disable;

	void ReadDirectory(CString m_Dir);
	int FindSepLeftPos(int pos, bool FindSepLeftPos = false);
	int FindSepLeftPos2(int pos);
	int FindSepRightPos(int pos);
	bool HandleKey(UINT nChar, bool m_bFromChild);

	bool m_CursorMode;
	int m_iType;
	CEdit *m_pEdit;

	TCHAR m_szDrive[_MAX_DRIVE], m_szDir[_MAX_DIR],m_szFname[_MAX_FNAME], m_szExt[_MAX_EXT];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f?t unmittelbar vor der vorhergehenden Zeile zus?zliche Deklarationen ein.

#endif // AFX_ACEDIT_H__56D21C13_ECEA_41DF_AADF_55980E861AC2__INCLUDED_
