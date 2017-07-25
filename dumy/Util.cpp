#include "stdafx.h"

#include <stdio.h>
#include <stdarg.h>
#include <memory.h>

#include "Util.h"

const std::locale locKoKr( "Korean_Korea" );

/* 유용한 std::string 에 대한 formatting 함수 */
__inline std::string format_arg_list(const char *fmt, va_list args)
{
	if (!fmt) return "";
	int   result = -1, length = 512;
	char *buffer = 0;
	while (result == -1)    {
		if (buffer)
			delete [] buffer;
		buffer = new char [length + 1];
		memset(buffer, 0, (length + 1) * sizeof(char) );

		// remove deprecate warning
		//result = _vsnprintf(buffer, length, fmt, args);

		result = _vsnprintf_s(buffer, length, _TRUNCATE, fmt, args);
		length *= 2;
	}
	std::string s(buffer);
	delete [] buffer;
	return s;
}

__inline std::wstring format_arg_list(const wchar_t *fmt, va_list args)
{
	if (!fmt) return L"";
	int   result = -1, length = 512;
	wchar_t *buffer = 0;
	while (result == -1)    {
		if (buffer)
			delete [] buffer;
		buffer = new wchar_t [length + 1];
		memset(buffer, 0, (length + 1) * sizeof(wchar_t) );

		// remove deprecate warning
		//result = _vsnprintf(buffer, length, fmt, args);

		result = _vsnwprintf_s(buffer, length, _TRUNCATE, fmt, args);
		length *= 2;
	}
	std::wstring s(buffer);
	delete [] buffer;
	return s;
}

std::string format(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	std::string s = format_arg_list(fmt, args);
	va_end(args);
	return s;
}

std::wstring format(const wchar_t *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	std::wstring s = format_arg_list(fmt, args);
	va_end(args);
	return s;
}

bool IsAlphabet( const std::string& strString )
{
	for( std::string::const_iterator iterChar = strString.begin(); iterChar != strString.end(); ++iterChar )
		if( isalpha( *iterChar, locKoKr ) == true )
			return true;
	return false;
}

bool IsAlphabet( const std::wstring& strString )
{
	for( std::wstring::const_iterator iterChar = strString.begin(); iterChar != strString.end(); ++iterChar )
		if( isalpha( *iterChar, locKoKr ) == true )
			return true;
	return false;
}

bool IsNumber( const std::string& strString )
{
	for( std::string::const_iterator iterChar = strString.begin(); iterChar != strString.end(); ++iterChar )
		if( isdigit( *iterChar, locKoKr ) == false )
			return false;

	return true;
}

bool IsNumber( const std::wstring& strString )
{
	for( std::wstring::const_iterator iterChar = strString.begin(); iterChar != strString.end(); ++iterChar )
		if( isdigit( *iterChar, locKoKr ) == false )
			return false;
	return true;
}

