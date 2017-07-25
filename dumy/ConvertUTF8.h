/*
	MBCS, Unicode <---> UTF-8 변환을 지원하는 클래스 

	제작 : 헬마

	최초 완성 : 2009-04-16

	2009-05-11	: CT2U8 의 복사대입연산자에서 메모리 초기화 오류 수정
	2009-05-11	: CU8T2 의 복사대입연산자에서 메모리 초기화 오류 수정
	2009-05-17 : SDK 대상 OS 환경이 윈도 XP 일때도 컴파일이 가능하도록 인자 수정
	2009-05-29 : CU8T2 생성자에 std::string 도 받도록 추가, 반드시 utf8 형식이어야함
	2009-05-29 : CU8T2 클래스의 GetUTF16 함수의 버그 수정

	윈도 운영체제의 지원함수를 사용하기때문에 윈도 헤더 필요. 
	C 런타임 라이브러리는 UTF8 변환을 지원하지 않음
*/

#pragma once

#include <crtdefs.h>
#include <string>
#include "windows.h"
#include "Util.h"

// MBCS 또는 UTF16 으로 클래스를 생성 후 반대되는 문자열형을 대입하면 기존에 있던 문자열은 사라짐
// m_psz 와 m_pwsz 는 언제나 같은 내용의 문자열을 가르킴
class CT2U8
{
public:
	CT2U8();
	CT2U8( const char* pszString );
	CT2U8( const std::string& strString );
	CT2U8( const wchar_t* pwszString );
	CT2U8( const std::wstring& strString );
	CT2U8( const CT2U8& string );

	CT2U8&	operator =( const char* pszString );
	CT2U8&	operator =( const wchar_t* pwszString );
	CT2U8&	operator =( const std::string& strString );
	CT2U8&	operator =( const std::wstring& strString );
	CT2U8&	operator =( const CT2U8& string );

	std::string		GetMBCS();
	std::string		GetUTF8();
	std::wstring	GetUTF16();

	~CT2U8();

private:
	char*		m_psz;
	char*		m_pszUtf8;
	wchar_t*	m_pwsz;
};

class CU8T2
{
public:
	CU8T2();
	CU8T2( const char* pszString );
	CU8T2( const std::string& strString );
	CU8T2( const CU8T2& string );

	CU8T2&	operator =( const char* pszString );
	CU8T2&	operator =( const std::string& strString );
	CU8T2&	operator =( const CU8T2& string );

	std::string		GetMBCS();
	std::string		GetUTF8();
	std::wstring	GetUTF16();

	~CU8T2();
private:
	char*		m_psz;
	char*		m_pszUtf8;
	wchar_t*	m_pwsz;
};
