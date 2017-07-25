//
// win_main.cpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2007 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "stdafx.h"

#include <iostream>
#include <string>

#include "../boost.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>

#include "../share/unicode.h"
#include "../share/etc.h"
#include "../share/cmycout.h"

#include "../MedicalPhotoServerCore/async_server.hpp"
#include "../MedicalPhotoServerCore/data_manager.h"

#include "SendMsg_Connection_Manager.h"
#include "SendMsgCout.h"

#define CFTPSERVER_CONFIG_H_PATH	"../CFtpServer/CFtpServerConfig.h"
#include "../CFtpServer/CFtpServer.h"

/*
//#include "../MedicalPhotoServerCore/server.hpp"
#include "../MedicalPhotoServerCore/async_server.hpp"
//#include "../MedicalPhotoServerCore/log_server.h"
#include "../share/unicode.h"
//#include "../share/cmycout.h"
#include "../share/etc.h"
#include "../MedicalPhotoServerCore/data_manager.h"
#include <stdlib.h>


#ifdef _WIN32
//#include "SendMsg_Connection_Manager.h"
#include "SendMsgCout.h"
#endif

#include "../share/cmycout.h"
*/
//#include "../DirectoryChanges.h"

/*
boost::function0<void> console_ctrl_function;

BOOL WINAPI console_ctrl_handler(DWORD ctrl_type)
{
  switch (ctrl_type)
  {
  case CTRL_C_EVENT:
  case CTRL_BREAK_EVENT:
  case CTRL_CLOSE_EVENT:
  case CTRL_SHUTDOWN_EVENT:
	  {
    console_ctrl_function();
    return TRUE;
	  }
  default:
    return FALSE;
  }
}
*/
class builder
{
public:

	builder(data_manager& d)
		: data_manager_(d)
	{
	}
	void Start()
	{
		boost::thread BuildThread(boost::bind(&builder::BuildInfo,this));
	}
	void Stop()
	{
		data_manager_.StopBuild();
		boost::mutex::scoped_lock lock(build_info_mutex);
	}
	boost::mutex build_info_mutex;

private:
	data_manager& data_manager_;
	void BuildInfo()
	{
		boost::mutex::scoped_lock lock(build_info_mutex);
		data_manager_.Build();
	}
};


void WatcherThread(data_manager& data_manager_)
{
    while (true)
    {
        data_manager_.Heartbeat(1000);
    }
}
void ServerRunThread(async_server& async_server_)
{
	async_server_.start();
}
void Server_Exit(void)
{
	CMyCout log(_tcout);
	log << _T("Server Exit") << log.endl();
}

// Global Variables:
SendMsg_Connection_Manager connection_manager_;

int main(int argc, char* argv[])
{
	atexit(Server_Exit);

  try
  {
    // Initialise server.

#ifdef _WIN32
	  HWND m_hwnd=Utility::GetConsoleHwnd();
	SendMsgCout log(m_hwnd,_tcout);
#endif

//	CMyCout log(_tcout);
	config config_(log);
	config_.load();

	std::wcout.imbue(std::locale(""));

	HWND hwnd = ::FindWindow(NULL, _T("MedicalPhotoServer"));
	if (hwnd==NULL)
		log << _T("NULL") << log.endl();

#ifdef _DEBUG
	config_.version_.increase_version(CONSOLESERVER_VERSION);
#endif

#ifdef _WIN32
	HANDLE hMutex = NULL;
    hMutex = CreateMutex(NULL, FALSE, _T("MedicalPhotoConsole"));

    if( ERROR_ALREADY_EXISTS == ::GetLastError() )  
	{
        log << _T("Medicalphoto console server is already running.\n");
        CloseHandle(hMutex);
		return 0;
    } 
#endif

	std::string stPicturePath=config_.Get(DATA_PATH);
	tstring stErrorMsg;
	if (!data_manager::CheckValidPicturePath(MCodeChanger::_CCL(stPicturePath),stErrorMsg))
	{
		log << stErrorMsg << _T("\n");
		return 0;
	}
	if (!MFile::ExistsL(MCodeChanger::_CCL(stPicturePath)))
	{
		log << _T("Data folder is not Exist\n");
		return 0;
	}


//	async_connection_manager connection_manager_;
	connection_manager_.SetHWND(m_hwnd);
    async_server s(log,config_,connection_manager_);

    // Set console control handler to allow server to be stopped.
//    console_ctrl_function = boost::bind(&async_server::stop, &s);
//    SetConsoleCtrlHandler(console_ctrl_handler, TRUE);

	boost::asio::io_service io_service_;
	data_manager data_manager_(io_service_,config_);
	if (!data_manager_.Check())
	{
		log << _T("Fail to identify database") << log.endl();
		return 0;
	}

	if (!data_manager_.initiate())
	{
		log << _T("Fail to initiate database") << log.endl();
		return 0;
	}
	data_manager_.StartWatch();

	bool bBuildDone=false;
	if (data_manager_.IsAnyEmpty())
	{
		bBuildDone=true;
		data_manager_.BuildSQL();
	}

	builder builder_(data_manager_);
	if (config_.GetInt(STARTUP_CHECK_DB)==1 && bBuildDone==false)
		builder_.Start();

	data_manager_.RunSchedule();

	boost::thread BuildThread(boost::bind(ServerRunThread,boost::ref(s)));


	// FTP SERVER

	bool WSADataOn=true;
	if (config_.GetInt(FTP_SERVER_ON)==1)
	{
		#ifdef WIN32
			WSADATA WSAData;
			if( WSAStartup( MAKEWORD(1, 0), &WSAData) != 0 ) {
				log << _T("WSAStartup failure: WSAGetLastError")
					<< WSAGetLastError() << _T("\n");
				WSADataOn=false;
			}
		#endif
	}

	CFtpServer FtpServer;

	if (config_.GetInt(FTP_SERVER_ON)==1 && WSADataOn)
	{
		FtpServer.SetMaxPasswordTries( 3 );
		FtpServer.SetNoLoginTimeout( 45 ); // seconds
		FtpServer.SetNoTransferTimeout( 90 ); // seconds
		FtpServer.SetDataPortRange( 100, 900 ); // data TCP-Port range = [100-999]
		FtpServer.SetCheckPassDelay( 500 ); // milliseconds. Bruteforcing protection.

		std::string stDataPath=MCodeChanger::_CCN(MCodeChanger::_CCL(config_.Get(DATA_PATH)));
		std::string stAdminID=MCodeChanger::_CCN(MCodeChanger::_CCL(config_.Get(FTP_SERVER_ADMINID)));
		std::string stAdminPass=MCodeChanger::_CCN(MCodeChanger::_CCL(config_.Get(FTP_SERVER_ADMINPASS)));

		#ifdef WIN32
		CFtpServer::CUserEntry *pUser = FtpServer.AddUser( 
			stAdminID.c_str(),stAdminPass.c_str(),stDataPath.c_str());
		#else
//			CFtpServer::CUserEntry *pUser = FtpServer.AddUser( "test", "pass", "/" );
		#endif


		CFtpServer::CUserEntry *pAnonymousUser=NULL;
		if (config_.GetInt(FTP_ANONYMOUS_ON)==1)
		{
			pAnonymousUser = FtpServer.AddUser( "anonymous", NULL, stDataPath.c_str() );
			if( pAnonymousUser ) {
				pAnonymousUser->SetPrivileges( CFtpServer::LIST | CFtpServer::READFILE );
			} else
				log << _T("Can't create anonymous user.\n");
		}

		if( pUser ) {

			printf( "-User successfully created ! :)\r\n" );

			pUser->SetMaxNumberOfClient( 0 ); // Unlimited

			pUser->SetPrivileges( CFtpServer::READFILE | CFtpServer::WRITEFILE |
				CFtpServer::LIST | CFtpServer::DELETEFILE | CFtpServer::CREATEDIR |
				CFtpServer::DELETEDIR );


	// If you only want to listen on the TCP Loopback interface,
	// replace 'INNADDR_ANY' by 'inet_addr("127.0.0.1")'.
		if( FtpServer.StartListening( INADDR_ANY, config_.GetInt(FTP_SERVER_PORT)) ) {

//					log << _T("FtpServer is listening :") << config_.GetInt(FTP_SERVER_PORT) << _T("\n");

		if( FtpServer.StartAccepting() ) {

			log << _T("FtpServer successfuly started :") << config_.GetInt(FTP_SERVER_PORT) << _T("\n");

		} else
			log << _T("Unable to start FtpServer\n");
	} else
	log << _T("Unable to start FtpServer\n");

		} else 
			log << _T("Unable to start FtpServer\n");
	}


	bool bWatchOn=config_.GetInt(DIRECTORY_WATCH_ON);

	// Main message loop:
	while (true)
	{
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (bWatchOn)
				data_manager_.Heartbeat(1);
			else
				Utility::sleep(100);
		}
	}

	connection_manager_.stop_all();
	FtpServer.StopListening();
	data_manager_.StopBuild();
	builder_.Stop();
	exit(1);
  }
  catch (std::exception& e)
  {
	  _tcout << _T("exception: ") << MCodeChanger::_CCW(e.what()) << _T("\n");
  }

/*
	tstring stDataPath=MCodeChanger::_CCL(config_.Get(DATA_PATH));
	if (!MFile::ExistsL(stDataPath))
	{
		config_.save();
		log << stDataPath << _T(" is invalid folder\n");
		log << _T("Check DATA_PATH in the config.txt\n");
		return 0;
	}
	else
	{
		log << _T("Data Path : ") << stDataPath << _T("\n");
	}
	async_connection_manager connection_manager_;
    async_server s(log,config_,connection_manager_);

	data_manager data_manager_(config_);
	data_manager_.initiate();
	data_manager_.StartWatch();

	bool bBuildDone=false;
	if (data_manager_.IsAnyEmpty())
	{
		bBuildDone=true;
		data_manager_.BuildSQL();
	}

	builder builder_(data_manager_);
	if (config_.GetInt(STARTUP_CHECK_DB)==1 && bBuildDone==false)
		builder_.Start();

	data_manager_.RunSchedule();

	boost::thread BuildThread(boost::bind(ServerRunThread,boost::ref(s)));

    while (true)
    {
        data_manager_.Heartbeat(1000);
    }

	data_manager_.StopBuild();
	builder_.Stop();
  }
  catch (std::exception& e)
  {
	  _tcout << _T("exception: ") << MCodeChanger::_CCW(e.what()) << _T("\n");
  }
*/
  return 0;
}

