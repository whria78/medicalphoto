/*
	프로그래밍에 도움되는 유용한 함수, 클래스, 선언들 모음

	재구성, 제작 : 헬마.

*/

#pragma once

#include <locale>
#include <string>
#include <utility>
#include <functional>

std::string format(const char *fmt, ...);
std::string format_arg_list(const char *fmt, va_list args);
std::wstring format(const wchar_t *fmt, ...);
std::wstring format_arg_list(const wchar_t *fmt, va_list args);

extern const std::locale locKoKr;

bool IsAlphabet( const std::string& strString );
bool IsAlphabet( const std::wstring& strString );

bool IsNumber( const std::string& strString );
bool IsNumber( const std::wstring& strString );

template <typename T> inline 
void DeletePtr( T ptr ) 
{ 
	if( ptr != NULL )
	{
		delete ptr; 
		ptr = NULL; 
	}
}

template <typename T> inline
void DeletePtrA( T ptr )
{
	if( ptr != NULL )
	{
		delete [] ptr;
		ptr = NULL;
	}
}

class lt_nocaseW
	: public std::binary_function< wchar_t*, wchar_t*, bool>
{
public:
	bool operator()( std::wstring x, std::wstring y ) const
	{
		int ret = _wcsicmp( x.c_str(), y.c_str() );
		if( ret == 0 )
			return false;
		return true;
	}
};

class lt_nocaseA
	: public std::binary_function< char*, char*, bool>
{
public:
	bool operator()( std::string x, std::string y ) const
	{
		int ret = _stricmp( x.c_str(), y.c_str());
		if( ret == 0 )
			return false;
		return true;
	}
};
