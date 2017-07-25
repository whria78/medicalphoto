#pragma once
#include "afxcmn.h"
#include "resource.h"

#include "../MedicalPhotoServerCore/data_manager.h"
#include "../share/cmycout.h"

// CDataManagerDlg dialog

class CDataManagerDlg : public CDialog
	,public data_manager
{
	DECLARE_DYNAMIC(CDataManagerDlg)
public:
	void Build();
	void BuildSQL();  // non-thread
	void BuildThumbnail();  // non-thread

	void Build_Thread();
	void BuildSQL_Thread();  // non-thread
	void BuildThumbnail_Thread();  // non-thread

	bool bStopThread;
	bool bStartThread;

	void StopBuild();

protected:
	bool BuildSQLFileInfo(const _tpath& p,netvolume& netvolume_,bool bCheckExist=true);
	void CheckSQLFileInfo(const std::string& stNetPath,netvolume& netvolume_);

	void BuildThumbnail(const std::string& stNetPath,netvolume& netvolume_);
	bool CheckThumbnail(const _tpath& p);
	void BuildMetaTag(const std::string& stNetPath,netvolume& netvolume_);

protected:
	void WriteString(const tstring& str);
//	void Exit(bool bResult);
	CMyCout& log_;
	boost::mutex mutex_;

public:
	CDataManagerDlg(config& c_,CMyCout& l_,CWnd* pParent = NULL);   // standard constructor
	virtual ~CDataManagerDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_DATAMANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_StatusList;
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnClose();
};
