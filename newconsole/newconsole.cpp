// newconsole.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "newconsole.h"

#include <iostream>
#include <string>
#include <stdlib.h>

#include "../boost.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>

#include "../share/unicode.h"
#include "../share/etc.h"
#include "../share/cmycout.h"
#include "../share/netwatcher.h"

#include "../MedicalPhotoServerCore/async_server.hpp"
#include "../MedicalPhotoServerCore/data_manager.h"

#include "SendMsg_Connection_Manager.h"
#include "SendMsgCout.h"


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

void ServerRunThread(async_server& async_server_)
{
	async_server_.start();
}
void Server_Exit(void)
{
	CMyCout log(_tcout);
	log << _T("Server Exit") << log.endl();
}


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HWND m_hwnd;
SendMsg_Connection_Manager connection_manager_;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
HWND				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
//	UNREFERENCED_PARAMETER(hPrevInstance);
//	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
//	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_NEWCONSOLE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:

	m_hwnd=InitInstance (hInstance, nCmdShow);
	if (m_hwnd==NULL)
		return FALSE;


	try
  {
	SendMsgCout log(m_hwnd,_tcout);
	config config_(log);
	config_.load();
	std::wcout.imbue(std::locale(""));

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

	// check DATA_PATH

	std::string stPicturePath=config_.Get(DATA_PATH);
	tstring stErrorMsg;
	if (!data_manager::CheckValidPicturePath(MCodeChanger::_CCL(stPicturePath),stErrorMsg))
	{
		log << stErrorMsg << _T("\n");
		return 0;
	}

	//

	connection_manager_.SetHWND(m_hwnd);
    async_server s(log,config_,connection_manager_);


	boost::asio::io_service io_service_;

	//
	netwatcher netwatcher_(config_,log);

	netwatcher_.StartWatch();




	//
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
	
	log << _T("[Startup] Server start\n");

	bool bWatchOn=(bool)config_.GetInt(DIRECTORY_WATCH_ON);

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

			netwatcher_.Heartbeat(1);
		}
	}

	connection_manager_.stop_all();
	data_manager_.StopBuild();
	builder_.Stop();
	exit(1);
  }
  catch (std::exception& e)
  {
	  _tcout << _T("exception: ") << MCodeChanger::_CCW(e.what()) << _T("\n");
  }

	return 0;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NEWCONSOLE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_NEWCONSOLE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
	   return NULL;
   }

//   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);

   return hWnd;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_REQUESTINFO:
		{
			std::ostringstream archive_stream_out;
			boost::archive::text_oarchive archive_out(archive_stream_out);

			std::vector<connection_info> connection_info_list;
			connection_manager_.GetList(connection_info_list);

			Utility::serialout(archive_out,connection_info_list);
			
			std::string steamout_=archive_stream_out.str();
			COPYDATASTRUCT cds;
			cds.dwData=WM_COPYDATA_CONNECTEDLIST;
			cds.cbData=(DWORD)steamout_.length();
			cds.lpData=(void*)steamout_.c_str();

			
			HANDLE    hMapRead;
			HWND* lpMapping;
			HWND hwnd;
			hMapRead = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, _T("Global\\MedicalPhotoServerHWND"));
			lpMapping = (HWND*)MapViewOfFile(hMapRead, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			if (lpMapping == NULL)
				CloseHandle(hMapRead);
			else
			{
				hwnd = *lpMapping;
				UnmapViewOfFile(lpMapping);
				CloseHandle(hMapRead);
			}
			
			if (hwnd == NULL) hwnd = ::FindWindow(_T("MedicalPhotoServer"), NULL);
			if (hwnd!=NULL)
			{
				SendMessage(hwnd,WM_COPYDATA,(WPARAM)m_hwnd,(LPARAM)&cds);
			}
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

