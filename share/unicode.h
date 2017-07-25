#pragma once

#ifdef _DEBUG
#pragma warning(disable: 4819)
#pragma warning(disable: 4996)
#pragma warning(disable: 4267)
#pragma warning(disable: 4244)
#pragma warning(disable: 4018)
#endif

# include <string>
# include <tchar.h>

#ifdef _UNICODE
	typedef wchar_t TCHAR;
	#define tstring std::wstring
	#define tostringstream std::wostringstream
    #define tistringstream std::wistringstream
	#define _tostring _towchar
	#define to_simple_tstring boost::posix_time::to_simple_wstring
	#define _tformat boost::wformat
	#define _tpath boost::filesystem::path
	#define _tfilesystem_error boost::filesystem::filesystem_error
	#define _tdirectory_iterator boost::filesystem::directory_iterator
	#define _tostream std::wostream
	#define _tcout std::wcout
#else 
	typedef char TCHAR;
	#define tstring std::string
    #define tostringstream std::ostringstream
    #define tistringstream std::istringstream
	#define _tostring _tochar
	#define to_simple_tstring boost::posix_time::to_simple_string
	#define _tformat boost::format
	#define _tpath boost::filesystem::path
	#define _tfilesystem_error boost::filesystem::filesystem_error
	#define _tdirectory_iterator boost::filesystem::directory_iterator
	#define _tostream std::ostream
	#define _tcout std::cout
#endif // _UNICODE


