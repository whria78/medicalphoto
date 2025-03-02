#pragma once
#include "afxcmn.h"
#include "TextProgressCtrl.h"
#include "../client/whriaclient.h"
#include "../share/datatype.h"
#include "../share/etc.h"
#include "../share/netpath.h"
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "tooltiplistctrl.h"
#include "../cximage/ximage.h"
#include "../share/imageprocess.h"
#include "xmessagebox.h"

// CProgressDialog dialog

class CProgressDialog : public CDialog
{
	DECLARE_DYNAMIC(CProgressDialog)

public:
	CProgressDialog(CWhriaCacheClient&w,client_config&c,CWnd* pParent = NULL);   // standard constructor
	virtual ~CProgressDialog();

public:
	void UploadFolder(const tstring& stLocalPath,const std::string& stDestNetPath);
	void UploadFiles(const filepath_list& path_list,const std::string& stCurrentPath);

	void UploadEx(const tstring& stLocalPath);

protected:
	void UploadExThread(const tstring& stLocalPath);

	void UploadFolderThread(const tstring& stLocalPath,const std::string& stDestNetPath);
	void UploadFilesThread(const filepath_list& path_list,const std::string& stCurrentPath);
	filepath_list UploadCommon(const std::vector<_tpath>& local_list,filepath_list& net_list,bool bCheck);

public:
	void DownloadFolder(const std::string& stNetPathFrom,const tstring& stFolderTo);
	void DownloadFile(const fileinfo_list& f_list,const tstring& stFolderTo);
	void ModifyPath(fileinfo_list& f_list,CToolTipListCtrl& m_PictureList,fileinfo& fileinfo_update);

protected:
	void DownloadFolderThread(const std::string& stNetPathFrom,const tstring& stFolderTo);
	void DownloadFileThread(const fileinfo_list& f_list,const tstring& stFolderTo);
	void ModifyPathThread(fileinfo_list& f_list,CToolTipListCtrl& m_PictureList,fileinfo& fileinfo_update);

public:
	void UpdateApp(version_checker& version_,version_checker& version_new_,bool& bUpdateResult,bool& bSucceedUpdate);
protected:
	void UpdateAppThread(version_checker& version_,version_checker& version_new_,bool& bUpdateResult,bool& bSucceedUpdate);
	bool Switch(CString executable, CString update);

protected:
	CWhriaCacheClient& WhriaClient;
	client_config& config_;
	boost::mutex thread_mutex;
	bool bStopThread;
	bool bStartThread;

// Dialog Data
	enum { IDD = IDD_DIALOG_PROGRESS };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	CProgressCtrl m_Progress;
	CTextProgressCtrl	m_Progress;
public:
	afx_msg void OnBnClickedCancel();
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnClose();
};
