#pragma once
#include "afxcmn.h"


// CUpdateDlg dialog

#include "AutoUpdater.h"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

class CUpdateDlg : public CDialog, public CAutoUpdater
{
	DECLARE_DYNAMIC(CUpdateDlg)

public:
	CUpdateDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUpdateDlg();

	void SetPos(DWORD iIndex)
	{
		m_Progress.SetPos(iIndex/1024);
//		Sleep(10);
	}
	void SetRange(DWORD iIndex)
	{
		m_Progress.SetRange(0,iIndex/1024);
	}
	void CheckForUpdate(LPCTSTR UpdateServerURL)
	{
		boost::thread BuildThread(boost::bind(&CUpdateDlg::CheckForUpdateThread,this,UpdateServerURL));
	}
	void CheckForUpdateThread(LPCTSTR UpdateServerURL)
	{
		while (!bStartThread)
		{
			Sleep(100);
		}
		UpdateErrorType=CAutoUpdater::CheckForUpdate(UpdateServerURL);
		Sleep(100);
		if (GetSafeHwnd())
			PostMessage(WM_CLOSE,0,0);
	}

	bool DownloadFile(HINTERNET hSession, LPCTSTR localFile)
	{	
		TCHAR bufQuery[32] ;
		DWORD dwLengthBufQuery = sizeof (bufQuery);
		BOOL bQuery = ::HttpQueryInfo(hSession,HTTP_QUERY_CONTENT_LENGTH,
										bufQuery, &dwLengthBufQuery,NULL) ;
		DWORD dwFileSize =(DWORD)_ttol(bufQuery);
		SetRange(dwFileSize);

		HANDLE	hFile;
		BYTE	pBuf[TRANSFER_SIZE];
		DWORD	dwReadSizeOut, dwTotalReadSize = 0;

		hFile = CreateFile(localFile, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE) return false;

		do {
			DWORD dwWriteSize, dwNumWritten;
			BOOL bRead = InternetReadFile(hSession, pBuf, TRANSFER_SIZE, &dwReadSizeOut);
			dwWriteSize = dwReadSizeOut;

			if (bRead && dwReadSizeOut > 0) {
				dwTotalReadSize += dwReadSizeOut;
				WriteFile(hFile, pBuf, dwWriteSize, &dwNumWritten, NULL);
				SetPos(dwTotalReadSize);
				// File write error
				if (dwWriteSize != dwNumWritten) {
					CloseHandle(hFile);					
					return false;
				}
			}
			else {
				if (!bRead)
				{
					// Error
					CloseHandle(hFile);	
					return false;
				}			
				break;
			}
			if (bStopThread) 
			{
				Sleep(1000);
				PostMessage(WM_CLOSE,0,0);
				return false;
			}

		} while(1);

		CloseHandle(hFile);
		return true;
		
	}
	boost::mutex thread_mutex;
	bool bStopThread;
	bool bStartThread;

	CAutoUpdater::ErrorType UpdateErrorType;

// Dialog Data
	enum { IDD = IDD_DIALOG_UPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_Progress;
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
};
