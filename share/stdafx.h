// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef _PRECOMPILEHEADER

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <cstring>
#include <exception>
#include <iostream>
#include <string>
#include <cstdlib>
#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <malloc.h>

#include "tchar.h"

#include "../boost.h"
#include <boost/thread/mutex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>
#include <boost/date_time/gregorian/greg_serialize.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/thread/xtime.hpp>



// TODO: reference additional headers your program requires here
#endif