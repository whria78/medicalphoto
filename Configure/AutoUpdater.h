// AutoUpdater.h: interface for the CAutoUpdater class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOUPDATER_H__227B2B21_B6AE_4164_B3A5_BFDAAF13D85D__INCLUDED_)
#define AFX_AUTOUPDATER_H__227B2B21_B6AE_4164_B3A5_BFDAAF13D85D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Wininet.h>
//#include "..\httpdownloaddlg\HttpDownloadDlg.h"
#include <winsock2.h>

#define LOCATION_UPDATE_FILE_CHECK _T("update.php")
#define TRANSFER_SIZE 4096

class CAutoUpdater  
{
public:
	CAutoUpdater();
	virtual ~CAutoUpdater();

	enum ErrorType { Success, InternetConnectFailure, InternetSessionFailure, 
						ConfigDownloadFailure, FileDownloadFailure, NoExecutableVersion,
						UpdateNotRequired, UpdateNotComplete };

	ErrorType CheckForUpdate(LPCTSTR UpdateServerURL);
	CString IsUpdateExist(LPCTSTR UpdateServerURL);

	HINTERNET GetSession(CString &URL);

	bool InternetOkay();
	bool DownloadConfig(HINTERNET hSession, BYTE *pBuf, DWORD bufSize);
	virtual bool DownloadFile(HINTERNET hSession, LPCTSTR localFile);
//	bool DownloadFile(const CString& stWebPath, const CString& localFile);
//	virtual BOOL WriteFile(HANDLE hFile,LPCVOID lpBuffer,DWORD nNumberOfBytesToWrite,LPDWORD lpNumberOfBytesWritten,LPOVERLAPPED lpOverlapped);

	virtual void SetPos(DWORD iIndex)
	{
	}
	virtual void SetRange(DWORD iIndex)
	{
	}

	CString GetFileVersion(LPCTSTR file);
	int		CompareVersions(CString ver1, CString ver2);
	bool	IsDigits(CString text);
	CString GetExecutable();
	bool	Switch(CString executable, CString update, bool WaitForReboot);

	CString strFilepath;


	CString GetLocalIP();

private:
	HINTERNET hInternet;
};

#endif // !defined(AFX_AUTOUPDATER_H__227B2B21_B6AE_4164_B3A5_BFDAAF13D85D__INCLUDED_)