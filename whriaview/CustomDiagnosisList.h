#pragma once

#include "listctrl.h"
#include "afxcmn.h"
#include "../client/whriaclient.h"
#include "../share/datatype.h"
#include "ACEdit.h"

// CCustomDiagnosisList dialog

class CCustomDiagnosisList : public CDialog
{
	DECLARE_DYNAMIC(CCustomDiagnosisList)

public:
	CCustomDiagnosisList(CWhriaCacheClient&w,CACEdit& m_edit,fileinfo_list& f_list,CWnd* pParent = NULL);   // standard constructor
	virtual ~CCustomDiagnosisList();

	CWhriaCacheClient& WhriaClient;
	CACEdit& m_DxListCtrl;
	fileinfo_list& m_SelectedImage;

	userdx_list userdx_list_;

	void LoadCustomDx();
// Dialog Data
	enum { IDD = IDD_DIALOG_CUSTOMDX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CImageList m_Img;
	gxListCtrl m_CustomList;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkListCustomdx(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnNMClickListCustomdx(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnLvnEndlabeleditListCustomdx(NMHDR *pNMHDR, LRESULT *pResult);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnBnClickedButtonExit();
};
