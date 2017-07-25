#pragma once


// CSelectFolders dialog
#include "../share/config.h"
#include "../MedicalPhotoServerCore/data_manager.h"
#include "XBrowseForFolder.h"

class CSelectFolders : public CDialog
{
	DECLARE_DYNAMIC(CSelectFolders)

public:
	CSelectFolders(config& c_,CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectFolders();

// Dialog Data
	enum { IDD = IDD_DIALOG_PATHS };

protected:
	CString ChooseFolder();

//	config& config_;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPicturefolder();
	afx_msg void OnBnClickedButtonDatafolder();
public:
	CString m_DataRootPath;
	CString m_PicturePath;

	CString m_FavoratePath;
	CString m_ThumbnailPath;
	CString m_TmpPath;
};
