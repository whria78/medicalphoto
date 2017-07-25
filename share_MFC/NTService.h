#pragma once

#include <stdio.h>
#include <windows.h>
#include <winbase.h>
#include <winsvc.h>
#include <process.h>
#include "../boost.h"
#include "../share/unicode.h"
#include "../share/cmycout.h"
#include "../share/config.h"
#include <boost/filesystem/path.hpp>
/*
SERVICE_TABLE_ENTRY   DispatchTable[] = 
{ 
	{pServiceName, XYNTServiceMain}, 
	{NULL, NULL}
};
*/
class NTService
{
public:
	NTService(CMyCout& l_)
		:log_(l_)
	{
	}
	BOOL KillService(const TCHAR* pName);
	BOOL RunService(const TCHAR* pName, int nArg, TCHAR** pArg);
	BOOL RunService(const TCHAR* pName) {return RunService(pName,0,NULL);}
	bool UnInstall(const TCHAR* pName);
	bool Install(const TCHAR* pPath, const TCHAR* pName);
	bool IsInstalled(const TCHAR* pName);
	bool GetRunStatus(const TCHAR* pName,DWORD& dwStatus);
	bool GetExePath(const TCHAR* pName, tstring & stPath);

//	SC_HANDLE OpenService();

private:
	CMyCout& log_;

	void ThrowError();
	void WriteLog(TCHAR* pMsg);

	TCHAR pServiceName[501];
	TCHAR pExeFile[501];
	TCHAR pInitFile[501];
	TCHAR pLogFile[501];
	PROCESS_INFORMATION pProcInfo[127];

	SERVICE_STATUS          serviceStatus; 
	SERVICE_STATUS_HANDLE   hServiceStatusHandle; 

//	VOID WINAPI XYNTServiceMain( DWORD dwArgc, LPTSTR *lpszArgv );
//	VOID WINAPI XYNTServiceHandler( DWORD fdwControl );

//	CRITICAL_SECTION myCS;

};


class MedicalPhoto_NTService
	:
	public NTService
{
public:
	MedicalPhoto_NTService(config& c)
		: NTService(c.log)
		,config_(c)
		,stServiceName(MCodeChanger::_CCL(config_.Get(NTSERVICE_NAME)))
	{
		_tpath prog_path=bfs::initial_path<_tpath>();
		prog_path/=MCodeChanger::_CCL(config_.version_.Get(SERVICE_FILE_NAME));
		stServiceExeName=prog_path.c_str();
	}
	BOOL KillService()
	{
		return NTService::KillService(stServiceName.c_str());
	}
	BOOL RunService()
	{
		return NTService::RunService(stServiceName.c_str());
	}
	bool UnInstall()
	{
		return NTService::UnInstall(stServiceName.c_str());
	}
	bool Install()
	{
		return NTService::Install(stServiceExeName.c_str(),stServiceName.c_str());
	}
	bool IsInstalled()
	{
		return NTService::IsInstalled(stServiceName.c_str());
	}
	bool GetRunStatus(DWORD& dwStatus)
	{
		return NTService::GetRunStatus(stServiceName.c_str(),dwStatus);
	}
	bool CheckService()
	{
		tstring stPath;
		NTService::GetExePath(stServiceName.c_str(), stPath);
		if (_tcscmp(stPath.c_str(), stServiceExeName.c_str()) == 0) 
			return true;
		else
			return false;
	}
	bool IsRunning()
	{
		DWORD dwStatus;
		if (!GetRunStatus(dwStatus))
			return false;
		if (dwStatus==SERVICE_RUNNING)
			return true;
		else
			return false;
	}
private:
	config& config_;
	tstring stServiceName;
	tstring stServiceExeName;
};