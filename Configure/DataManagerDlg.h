#pragma once
#include "afxcmn.h"
#include "resource.h"

#include "../MedicalPhotoServerCore/data_manager.h"
#include "../share/cmycout.h"
#include "../share_mfc/NTService.h"

// CDataManagerDlg dialog

class CDataManagerDlg : public CDialog
	,public data_manager
{
	DECLARE_DYNAMIC(CDataManagerDlg)
public:
	void Build();
	void Build_Thread();

	void StopBuild();
	bool bBuildit;
	bool bBuildThumb;
	void SetBuildThumb(bool b_)
	{
		bBuildThumb = b_;
	}

protected:
	bool BuildSQLFileInfo(const _tpath& p,netvolume& netvolume_,bool bCheckExist=true);
	void CheckSQLFileInfo(const std::string& stNetPath,netvolume& netvolume_);

	void BuildThumbnail(const std::string& stNetPath,netvolume& netvolume_);
	bool CheckThumbnail(const _tpath& p);

	void MakeThumbnail(const tstring& thumbpath,const std::string& stNetPath);

	CString GetLocalIP();

protected:
	void SetProgress(int iMax);
	void SetProgressText(const tstring& stText);
	void SetProgressPos(int i,const tstring& stText);
	void SetProgressPos(int i);

	void WriteString(const tstring& str);
	CMyCout& log_;
	config& config_;
	boost::mutex mutex_;

public:
	CDataManagerDlg(boost::asio::io_service &io_service_,config& c_,CMyCout& l_,CWnd* pParent = NULL);   // standard constructor
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
	afx_msg void OnClose();
public:
	afx_msg void OnBnClickedButtonCancelbuild();
public:
	CProgressCtrl m_Progress;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
