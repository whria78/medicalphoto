// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <winsock2.h>
#include <ws2tcpip.h>
#include <wspiapi.h>
#define GetAddrInfo WspiapiGetAddrInfo
#define FreeAddrInfo WspiapiFreeAddrInfo

#include "../boost.h"
#pragma warning(disable: 4005)
#include <boost/asio.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/format.hpp>
#include <boost/thread/mutex.hpp>

#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
// TODO: reference additional headers your program requires here
