////////////////////////////////////////////////////////////////////// 
// NT Service Stub Code (For XYROOT )
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NTService.h"

void NTService::WriteLog(TCHAR* pMsg)
{
	// write error or other information into log file

	log_ << pMsg;
	return;
}

////////////////////////////////////////////////////////////////////// 
//
// Configuration Data and Tables
//

BOOL NTService::KillService(const TCHAR* pName) 
{ 
	// kill service with given name
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("OpenSCManager failed, error code = %d"), nError);
		WriteLog(pTemp);
	}
	else
	{
		// open the service
		SC_HANDLE schService = OpenService( schSCManager, pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("OpenService failed, error code = %d"), nError);
			WriteLog(pTemp);
		}
		else
		{
			// call ControlService to kill the given service
			SERVICE_STATUS status;
			if(ControlService(schService,SERVICE_CONTROL_STOP,&status))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				return TRUE;
			}
			else
			{
				long nError = GetLastError();
				TCHAR pTemp[121];
				_stprintf(pTemp, _T("ControlService failed, error code = %d"), nError);
				WriteLog(pTemp);
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return FALSE;
}

BOOL NTService::RunService(const TCHAR* pName, int nArg, TCHAR** pArg) 
{ 
	// run service with given name
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("OpenSCManager failed, error code = %d"), nError);
		WriteLog(pTemp);
	}
	else
	{
		// open the service
		SC_HANDLE schService = OpenService( schSCManager, pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp,_T("OpenService failed, error code = %d"), nError);
			WriteLog(pTemp);
		}
		else
		{
			// call StartService to run the service
			if(StartService(schService,nArg,(const TCHAR**)pArg))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				return TRUE;
			}
			else
			{
				long nError = GetLastError();
				TCHAR pTemp[121];
				_stprintf(pTemp,_T("StartService failed, error code = %d"), nError);
				WriteLog(pTemp);
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return FALSE;
}


////////////////////////////////////////////////////////////////////// 
//
// Uninstall
//
bool NTService::UnInstall(const TCHAR* pName)
{
	bool bResult=false;
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp,_T("OpenSCManager failed, error code = %d"), nError);
		WriteLog(pTemp);
	}
	else
	{
		SC_HANDLE schService = OpenService( schSCManager, pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp,_T("OpenService failed, error code = %d"), nError);
			WriteLog(pTemp);
		}
		else
		{
			if(!DeleteService(schService)) 
			{
				TCHAR pTemp[121];
				_stprintf(pTemp,_T("Failed to delete service %s"), pName);
				WriteLog(pTemp);
			}
			else 
			{
				TCHAR pTemp[121];
				_stprintf(pTemp,_T("Service %s removed"),pName);
				WriteLog(pTemp);
				bResult=true;
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager);	
	}
	return bResult;
}

////////////////////////////////////////////////////////////////////// 
//
// Install
//
bool NTService::Install(const TCHAR* pPath, const TCHAR* pName) 
{  
	bool bResult=false;
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_CREATE_SERVICE); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp,_T("OpenSCManager failed, error code = %d"), nError);
		WriteLog(pTemp);
	}
	else
	{
		SC_HANDLE schService = CreateService
		( 
			schSCManager,	/* SCManager database      */ 
			pName,			/* name of service         */ 
			pName,			/* service name to display */ 
			SERVICE_ALL_ACCESS,        /* desired access          */ 
			SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS , /* service type            */ 
			SERVICE_AUTO_START,      /* start type              */ 
			SERVICE_ERROR_NORMAL,      /* error control type      */ 
			pPath,			/* service's binary        */ 
			NULL,                      /* no load ordering group  */ 
			NULL,                      /* no tag identifier       */ 
			NULL,                      /* no dependencies         */ 
			NULL,                      /* LocalSystem account     */ 
			NULL
		);                     /* no password             */ 
		if (schService==0) 
		{
			long nError =  GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp,_T("Failed to create service %s, error code = %d"), pName, nError);
			WriteLog(pTemp);
		}
		else
		{
			TCHAR pTemp[121];
			_stprintf(pTemp,_T("Service %s installed"), pName);
			WriteLog(pTemp);
			CloseServiceHandle(schService);
			bResult=true;
		}
		CloseServiceHandle(schSCManager);
	}	
	return bResult;
}
bool NTService::GetExePath(const TCHAR* pName,tstring& stPath)
{
	SC_HANDLE schService, schSCManager;
	LPQUERY_SERVICE_CONFIG lpqscBuf;
	// Service name, service to query
	LPSERVICE_DESCRIPTION lpqscBuf2;
	DWORD dwBytesNeeded;
	BOOL bSuccess = TRUE;
	stPath = _T("");

	// Open a handle to the SC Manager database...
	schSCManager = OpenSCManager(
		NULL, // local machine
		NULL, // SERVICES_ACTIVE_DATABASE database is opened by default
		SC_MANAGER_ALL_ACCESS); // full access rights, not a good choice

	if (NULL == schSCManager)
	{
		WriteLog(_T("OpenSCManager(), Open a handle to the SC Manager database failed, error"));
	}

	// Open a handle to the service.
	schService = OpenService(
		schSCManager, // SCManager database
		pName, // name of service
		SERVICE_QUERY_CONFIG);// need QUERY access

	if (schService == NULL)
	{
		WriteLog(_T("OpenService() failed, error"));
		return FALSE;
	}

	// Allocate a buffer for the configuration information.
	lpqscBuf = (LPQUERY_SERVICE_CONFIG)LocalAlloc(LPTR, 4096);
	if (lpqscBuf == NULL)
		return FALSE;

	lpqscBuf2 = (LPSERVICE_DESCRIPTION)LocalAlloc(LPTR, 4096);
	if (lpqscBuf2 == NULL)
		return FALSE;

	// Get the Windows service configuration information.

	if (!QueryServiceConfig(schService, lpqscBuf, 4096, &dwBytesNeeded))
	{
		WriteLog(_T("QueryServiceConfig() failed, error: "));
		bSuccess = FALSE;
	}

	if (!QueryServiceConfig2(schService, SERVICE_CONFIG_DESCRIPTION, (LPBYTE)lpqscBuf2, 4096, &dwBytesNeeded))
	{
		WriteLog(_T("QueryServiceConfig2() failed, error"));
		bSuccess = FALSE;
	}

	stPath = lpqscBuf->lpBinaryPathName;

/*
	// Print the configuration information.

	printf("\n%S service configuration: \n", pName);
	printf(" Type: 0x%x\n", lpqscBuf->dwServiceType);
	printf(" Start Type: 0x%x\n", lpqscBuf->dwStartType);
	printf(" Error Control: 0x%x\n", lpqscBuf->dwErrorControl);
	printf(" Binary path: %S\n", lpqscBuf->lpBinaryPathName);
	if (lpqscBuf->lpLoadOrderGroup != NULL)
		printf(" Load order group: %S\n", lpqscBuf->lpLoadOrderGroup);
	if (lpqscBuf->dwTagId != 0)
		printf(" Tag ID: %d\n", lpqscBuf->dwTagId);
	if (lpqscBuf->lpDependencies != NULL)
		printf(" Dependencies: %S\n", lpqscBuf->lpDependencies);
	if (lpqscBuf->lpServiceStartName != NULL)
		printf(" Start Name: %S\n", lpqscBuf->lpServiceStartName);
	if (lpqscBuf2->lpDescription != NULL)
		printf(" Description: %S\n", lpqscBuf2->lpDescription);
*/
	LocalFree(lpqscBuf);
	LocalFree(lpqscBuf2);
	return bSuccess;
}

bool NTService::IsInstalled(const TCHAR* pName)
{
	bool RetVal = false;
	bool bErrorFlag = false;

	SC_HANDLE  SCM;
	SC_HANDLE  Service;


	SCM = OpenSCManager(NULL, NULL, GENERIC_READ);
	if (NULL == SCM)
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp,_T("OpenSCManager failed, error code = %d"), nError);
		WriteLog(pTemp);
                       // Error
		bErrorFlag=true;
	}
	else
	{
		Service = OpenService(SCM, pName, GENERIC_READ);
		if (NULL == Service)
		{
			long nError=GetLastError();
			if (nError==ERROR_SERVICE_DOES_NOT_EXIST)
			{
				RetVal=false;
			}
			else
			{
				TCHAR pTemp[121];
				_stprintf(pTemp,_T("OpenService failed, error code = %d"), nError);
				WriteLog(pTemp);
				bErrorFlag=true;
			}
		}
		else
		{
			RetVal = true;
			CloseServiceHandle(Service);
		}
		CloseServiceHandle(SCM);
	}
	if (bErrorFlag)
		ThrowError();
	return RetVal;
}

bool NTService::GetRunStatus(const TCHAR* pName,DWORD& dwStatus)
{
	dwStatus = -1;
	bool bErrorFlag = false;

	SC_HANDLE  SCM;
	SC_HANDLE  Service;

	SCM = OpenSCManager(NULL, NULL, GENERIC_READ);
	if (NULL == SCM)
	{
		long nError=GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp,_T("OpenSCManager failed, error code = %d"), nError);
		WriteLog(pTemp);
		bErrorFlag=true;
                     // Error
	}
	else
	{
		Service = OpenService(SCM, pName, GENERIC_READ);
		if (NULL == Service)
		{
			long nError=GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp,_T("OpenService failed, error code = %d"), nError);
			WriteLog(pTemp);
			bErrorFlag=true;
            // Error
		}
		else
		{
			SERVICE_STATUS ServiceStatus;
			if (FALSE == QueryServiceStatus(Service, &ServiceStatus))
			{
				long nError=GetLastError();
				TCHAR pTemp[121];
				_stprintf(pTemp,_T("QueryServiceStatus failed, error code = %d"), nError);
				WriteLog(pTemp);
				bErrorFlag=true;
                                                     // Error
			}
			else
			{
				dwStatus = ServiceStatus.dwCurrentState;
			}
			CloseServiceHandle(Service);
		}
		CloseServiceHandle(SCM);
	}
	if (bErrorFlag)
		ThrowError();

	if (dwStatus==-1) 
		return false;
	else
		return true;
}

void NTService::ThrowError()
{
	throw std::logic_error("NTService Error");
}
