// AutoUpdater.cpp: implementation of the CAutoUpdater class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoUpdater.h"
#include "../share/codechange.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAutoUpdater::CAutoUpdater()
{
	// Initialize WinInet
	hInternet = InternetOpen(_T("AutoUpdateAgent"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);	
}

CAutoUpdater::~CAutoUpdater()
{
	if (hInternet) {
		InternetCloseHandle(hInternet);
	}
}


CString CAutoUpdater::GetLocalIP()

{

    WORD wVersionRequested;

    WSADATA wsaData;

    char name[255];

    CString ip; // 여기에 lcoal ip가 저장됩니다.

    PHOSTENT hostinfo;

    wVersionRequested = MAKEWORD( 2, 0 );

 

    if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )

    {

 

        if( gethostname ( name, sizeof(name)) == 0)

        {

              if((hostinfo = gethostbyname(name)) != NULL)

              {

 

                  ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);

 

                }

 

        }      

 

        WSACleanup( );

    }

  return ip;

}

// Check if an update is required
//
CString CAutoUpdater::IsUpdateExist(LPCTSTR UpdateServerURL)
{
	if (!InternetOkay())
	{
		return _T("");
	}

	bool bTransferSuccess = false;

	// Get the version number of our executable and compare to see if an update is needed
	CString executable = GetExecutable();
	CString fileVersion = GetFileVersion(executable);
	if (fileVersion.IsEmpty())
	{
		return _T("");
	}

	// First we must check the remote configuration file to see if an update is necessary
	CString URL = UpdateServerURL + CString(LOCATION_UPDATE_FILE_CHECK) + _T("?version=") + fileVersion + _T("&ip=") + GetLocalIP();
	HINTERNET hSession = GetSession(URL);
	if (!hSession)
	{
		return _T("");
	}

	BYTE pBuf[TRANSFER_SIZE];
	memset(pBuf, NULL, sizeof(pBuf));
	bTransferSuccess = DownloadConfig(hSession, pBuf, TRANSFER_SIZE);
	InternetCloseHandle(hSession);
	if (!bTransferSuccess)
	{
		return _T("");
	}

	std::string dumy = (char*) pBuf;
	CString updateVersion = MCodeChanger::_CCL(dumy).c_str();

//	CString updateVersion = (TCHAR *) pBuf;
//	updateVersion=updateVersion.Left(updateVersion.GetLength()-1);
	if (CompareVersions(updateVersion, fileVersion) != 1)
	{	
		return _T("");
	}
	return updateVersion;
}


CAutoUpdater::ErrorType CAutoUpdater::CheckForUpdate(LPCTSTR UpdateServerURL)
{		
	if (!InternetOkay())
	{
		return InternetConnectFailure;
	}

	bool bTransferSuccess = false;

	// First we must check the remote configuration file to see if an update is necessary
	CString URL = UpdateServerURL + CString(LOCATION_UPDATE_FILE_CHECK);
	HINTERNET hSession = GetSession(URL);
	if (!hSession)
	{
		return InternetSessionFailure;
	}

	BYTE pBuf[TRANSFER_SIZE];
	memset(pBuf, NULL, sizeof(pBuf));
	bTransferSuccess = DownloadConfig(hSession, pBuf, TRANSFER_SIZE);
	InternetCloseHandle(hSession);
	if (!bTransferSuccess)
	{
		return ConfigDownloadFailure;
	}

	// Get the version number of our executable and compare to see if an update is needed
	CString executable = GetExecutable();
	CString fileVersion = GetFileVersion(executable);
	if (fileVersion.IsEmpty())
	{
		return NoExecutableVersion;
	}

	std::string dumy = (char*) pBuf;
	CString updateVersion = MCodeChanger::_CCL(dumy).c_str();
//	CString updateVersion = (TCHAR *) pBuf;
//	updateVersion=updateVersion.Left(updateVersion.GetLength()-1);
	if (CompareVersions(updateVersion, fileVersion) != 1)
	{	
		return UpdateNotRequired;
	}

	// At this stage an update is required	
	TCHAR path[MAX_PATH];
	GetTempPath(MAX_PATH, path);
	CString exeName = executable.Mid(1+executable.ReverseFind(_T('\\')));
	CString directory = path;
	
	// Download the updated file
	URL = UpdateServerURL;
	URL+= _T("setup.exe");
	hSession = GetSession(URL);
	if (!hSession)
	{
		return InternetSessionFailure;
	}

	CString msg;
	msg.Format(_T("An update, version [%s] is now available. Proceed with the update?"), updateVersion);
	if (IDNO == MessageBox(GetActiveWindow(), msg, _T("Update is available"), MB_YESNO|MB_ICONQUESTION))
	{
		return UpdateNotComplete;	
	}


	// Proceed with the update
//	CString updateFileLocation = directory+exeName;
	CString updateFileLocation = directory+_T("setup.exe");
	bTransferSuccess = DownloadFile(hSession, updateFileLocation);
//	bTransferSuccess = DownloadFile(URL, updateFileLocation);
	if (!bTransferSuccess)
	{
		return FileDownloadFailure;
	}	

	InternetCloseHandle(hSession);

	ShellExecute(NULL, _T("open"), updateFileLocation, NULL, NULL, SW_SHOWNORMAL);
	exit(1);

/*	if (!Switch(executable, updateFileLocation, false))
	{
		return UpdateNotComplete;
	}*/
	
	return Success;
}

// Ensure the internet is ok to use
//
bool CAutoUpdater::InternetOkay()
{
	if (hInternet == NULL) {
		return false;
	}

	// Important step - ensure we have an internet connection. We don't want to force a dial-up.
	DWORD dwType;
	if (!InternetGetConnectedState(&dwType, 0))
	{
		return false;
	}

	return true;
}

// Get a session pointer to the remote file
//
HINTERNET CAutoUpdater::GetSession(CString &URL)
{
	// Canonicalization of the URL converts unsafe characters into escape character equivalents
	TCHAR canonicalURL[1024];
	DWORD nSize = 1024;
	InternetCanonicalizeUrl(URL, canonicalURL, &nSize, ICU_BROWSER_MODE);		
	
	DWORD options = INTERNET_FLAG_NEED_FILE|INTERNET_FLAG_HYPERLINK|INTERNET_FLAG_RESYNCHRONIZE|INTERNET_FLAG_RELOAD;
	HINTERNET hSession = InternetOpenUrl(hInternet, canonicalURL, NULL, NULL, options, 0);
	URL = canonicalURL;

	return hSession;
}

// Download a file into a memory buffer
//
bool CAutoUpdater::DownloadConfig(HINTERNET hSession, BYTE *pBuf, DWORD bufSize)
{	
	DWORD	dwReadSizeOut;
	InternetReadFile(hSession, pBuf, bufSize, &dwReadSizeOut);
	if (dwReadSizeOut <= 0)
	{
		return false;
	}

	
	return true;
}

// Download a file to a specified location
//
//bool CAutoUpdater::DownloadFile(const CString& stWebPath, const CString& localFile)

bool CAutoUpdater::DownloadFile(HINTERNET hSession, LPCTSTR localFile)
{	
/*	CHttpDownloadDlg dlg;
	dlg.m_sURLToDownload = stWebPath;
	dlg.m_sFileToDownloadInto = localFile;
	if (dlg.DoModal() == IDOK)
		return true;
	return false;
*/
	
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
	} while(1);

	CloseHandle(hFile);
	return true;
	
}

// Get the version of a file
//
CString CAutoUpdater::GetFileVersion(LPCTSTR file)
{
	CString version;
	VS_FIXEDFILEINFO *pVerInfo = NULL;
	DWORD	dwTemp, dwSize, dwHandle = 0;
	BYTE	*pData = NULL;
	UINT	uLen;

	try {
		dwSize = GetFileVersionInfoSize((LPTSTR) file, &dwTemp);
		if (dwSize == 0) throw 1;

		pData = new BYTE[dwSize];
		if (pData == NULL) throw 1;

		if (!GetFileVersionInfo((LPTSTR) file, dwHandle, dwSize, pData))
			throw 1;

		if (!VerQueryValue(pData, _T("\\"), (void **) &pVerInfo, &uLen)) 
			throw 1;

		DWORD verMS = pVerInfo->dwFileVersionMS;
		DWORD verLS = pVerInfo->dwFileVersionLS;

		int ver[4];
		ver[0] = HIWORD(verMS);
		ver[1] = LOWORD(verMS);
		ver[2] = HIWORD(verLS);
		ver[3] = LOWORD(verLS);

		// Are lo-words used?
		if (ver[2] != 0 || ver[3] != 0)
		{
			version.Format(_T("%d.%d.%d.%d"), ver[0], ver[1], ver[2], ver[3]);
		}
		else if (ver[0] != 0 || ver[1] != 0)
		{
			version.Format(_T("%d.%d"), ver[0], ver[1]);
		}

		delete pData;
		return version;
	}
	catch(...) {
		return _T("");
	}	
}

// Compare two versions 
//
int CAutoUpdater::CompareVersions(CString ver1, CString ver2)
{
	int  wVer1[4], wVer2[4];
	int	 i;
	TCHAR *pVer1 = ver1.GetBuffer(256);
	TCHAR *pVer2 = ver2.GetBuffer(256);

	for (i=0; i<4; i++)
	{
		wVer1[i] = 0;
		wVer2[i] = 0;
	}

	// Get version 1 to DWORDs
	TCHAR *pToken = _tcstok(pVer1, _T("."));
	if (pToken == NULL)
	{
		return -21;
	}

	i=3;
	while(pToken != NULL)
	{
		if (i<0 || !IsDigits(pToken)) 
		{			
			return -21;	// Error in structure, too many parameters
		}		
		wVer1[i] = _ttoi(pToken);
		pToken = _tcstok(NULL, _T("."));
		i--;
	}
	ver1.ReleaseBuffer();

	// Get version 2 to DWORDs
	pToken = _tcstok(pVer2, _T("."));
	if (pToken == NULL)
	{
		return -22;
	}

	i=3;
	while(pToken != NULL)
	{
		if (i<0 || !IsDigits(pToken)) 
		{
			return -22;	// Error in structure, too many parameters
		}		
		wVer2[i] = _ttoi(pToken);
		pToken = _tcstok(NULL, _T("."));
		i--;
	}
	ver2.ReleaseBuffer();

	// Compare the versions
	for (i=3; i>=0; i--)
	{
		if (wVer1[i] > wVer2[i])
		{
			return 1;		// ver1 > ver 2
		}
		else if (wVer1[i] < wVer2[i])
		{
			return -1;
		}
	}

	return 0;	// ver 1 == ver 2
}

// Ensure a string contains only digit characters
//
bool CAutoUpdater::IsDigits(CString text)
{
	for (int i=0; i<text.GetLength(); i++)
	{
		TCHAR c = text.GetAt(i);
		if (c >= _T('0') && c <= _T('9'))
		{
		}
		else
		{
			return false;
		}
	}

	return true;
}

CString CAutoUpdater::GetExecutable()
{
	if (strFilepath!="") return strFilepath;

	HMODULE hModule = ::GetModuleHandle(NULL);
    ASSERT(hModule != 0);
    
    TCHAR path[MAX_PATH];
    VERIFY(::GetModuleFileName(hModule, path, MAX_PATH));
    return path;
}

bool CAutoUpdater::Switch(CString executable, CString update, bool WaitForReboot)
{
	int type = (WaitForReboot) ? MOVEFILE_DELAY_UNTIL_REBOOT : MOVEFILE_COPY_ALLOWED;

	const TCHAR *backup = _T("OldExecutable.bak");
	CString directory = executable.Left(executable.ReverseFind(_T('\\')));	
	CString backupFile = directory + _T('\\') + CString(backup);

	DeleteFile(backupFile);
	if (!MoveFileEx(executable, backupFile, type)) 
	{
		return false;
	}


	bool bMoveOK = (MoveFileEx(update, executable, type) == TRUE);
	int i = GetLastError();

	return bMoveOK;	
}