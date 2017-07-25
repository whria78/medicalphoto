#if !defined(AFX_SELECTDIAGNOSISLIST_H__CE00500A_9C67_4D9F_ACB5_C8BD1DFEA7DD__INCLUDED_)
#define AFX_SELECTDIAGNOSISLIST_H__CE00500A_9C67_4D9F_ACB5_C8BD1DFEA7DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectDiagnosisList.h : header file
//

#include "../share/codechange.h"
#include "../share/datatype.h"
#include "../client/whriaclient.h"
#include "../share/dxdb.h"
#include "../share/etc.h"
#include "afxcmn.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectDiagnosisList dialog

class CSelectDiagnosisList : public CDialog
{
// Construction
public:
	CSelectDiagnosisList(CWhriaCacheClient& w,client_config& c,DxDB& dxdb,diagnosis& dx,const CString& s,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectDiagnosisList)
	enum { IDD = IDD_DIALOG_DXSELECTLIST };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectDiagnosisList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	int iNumDiagnosisStack;

	// Generated message map functions
	//{{AFX_MSG(CSelectDiagnosisList)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListChooseDx();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	diagnosis& diagnosis_;
	CWhriaCacheClient& WhriaClient;
	client_config& config_;
	CString stSearch;
	DxDB& DxDB_;

	userdx_list dx_list_;

public:
	CListCtrl m_DxList;
	afx_msg void OnNMDblclkListDx(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTDIAGNOSISLIST_H__CE00500A_9C67_4D9F_ACB5_C8BD1DFEA7DD__INCLUDED_)
