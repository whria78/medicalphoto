#include "stdafx.h"

#include "ConvertUTF8.h"

CT2U8::CT2U8() 
	: m_psz(NULL), m_pwsz(NULL), m_pszUtf8(NULL)
{
	
}

CT2U8::CT2U8( const char* pszString )
	: m_psz(NULL), m_pwsz(NULL), m_pszUtf8(NULL)
{
	*this = pszString;
}


CT2U8::CT2U8( const std::string& strString )
: m_psz(NULL), m_pwsz(NULL), m_pszUtf8(NULL)
{
	*this = strString;
}


CT2U8::CT2U8( const wchar_t* pwszString )
	: m_psz(NULL), m_pwsz(NULL), m_pszUtf8(NULL)
{
	*this = pwszString;
}

CT2U8::CT2U8( const std::wstring& strString )
: m_psz(NULL), m_pwsz(NULL), m_pszUtf8(NULL)
{
	*this = strString;
}

CT2U8::CT2U8( const CT2U8& string )
	: m_psz(NULL), m_pwsz(NULL), m_pszUtf8(NULL)
{
	*this = string;
}

CT2U8& CT2U8::operator =( const char* pszString )
{
	if( pszString )
	{
		DeletePtrA<char*>(m_psz);
		int nSize = strlen( pszString ) + 1;
		m_psz = new char[ nSize ];
		memset( m_psz, '\0', nSize * sizeof(char) );
		strcpy_s( m_psz, nSize, pszString );
	}

	return *this;
}

CT2U8& CT2U8::operator =( const std::string& strString )
{
	if( strString.empty() == false )
	{
		DeletePtrA<char*>(m_psz);
		int nSize =strString.length() + 1;
		m_psz = new char[ nSize ];
		memset( m_psz, '\0', nSize * sizeof(char) );
		strcpy_s( m_psz, nSize, strString.c_str() );
	}

	return *this;
}

CT2U8& CT2U8::operator =( const wchar_t* pwszString )
{
	if( pwszString )
	{
		DeletePtrA<wchar_t*>(m_pwsz);
		int nSize = wcslen( pwszString ) + 1;
		m_pwsz = new wchar_t[ nSize ];
		memset( m_pwsz, '\0', nSize  * sizeof(wchar_t) );
		wcscpy_s( m_pwsz, nSize, pwszString );
	}

	return *this;
}

CT2U8& CT2U8::operator =( const std::wstring& strString )
{
	if( strString.empty() == false )
	{
		DeletePtrA<wchar_t*>(m_pwsz);
		int nSize = strString.length() + 1;
		m_pwsz = new wchar_t[ nSize ];
		memset( m_pwsz, '\0', nSize  * sizeof(wchar_t) );
		wcscpy_s( m_pwsz, nSize, strString.c_str() );
	}

	return *this;
}

CT2U8& CT2U8::operator =( const CT2U8& string )
{
	if( string.m_psz )
	{
		DeletePtrA<char*>(m_psz);
		int nSize = strlen( string.m_psz ) + 1;
		m_psz = new char[ nSize ];
		memset( m_psz, '\0', nSize * sizeof(char) );
		strcpy_s( m_psz, nSize, string.m_psz );
	}
	if( string.m_pwsz )
	{
		DeletePtrA<wchar_t*>(m_pwsz);
		int nSize = wcslen( string.m_pwsz ) + 1;
		m_pwsz = new wchar_t[ nSize ];
		memset( m_pwsz, '\0', nSize  * sizeof(wchar_t) );
		wcscpy_s( m_pwsz, nSize, string.m_pwsz );
	}

	return *this;
}

std::string	CT2U8::GetMBCS()
{
	// 이미 한번 변환해서 MBCS가 있다면 그대로 반환
	if( m_psz != NULL )
		return m_psz;

	if( m_pwsz == NULL )
		return "";

	// 없다면 unicode 에서 변환
	int nReqSize = WideCharToMultiByte( CP_ACP, WC_NO_BEST_FIT_CHARS, m_pwsz, -1, m_psz, 0, NULL, NULL );
	m_psz = new char[ nReqSize ];
	memset( m_psz, '\0', nReqSize );

	int nRetSize = WideCharToMultiByte( CP_ACP, WC_NO_BEST_FIT_CHARS, m_pwsz, -1, m_psz, nReqSize, NULL, NULL );
	if( nRetSize > 0 ) 
		return m_psz;

	return "";
}

std::wstring	CT2U8::GetUTF16()
{
	if( m_pwsz != NULL )
		return m_pwsz;

	if( m_psz == NULL )
		return L"";

	int nReqSize = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, m_psz, -1, m_pwsz, 0 );
	m_pwsz = new wchar_t[ nReqSize ];
	memset( m_pwsz, '\0', sizeof(wchar_t) * nReqSize );

	int nRetSize = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, m_psz, -1, m_pwsz, nReqSize );
	if( nRetSize > 0 )
		return m_pwsz;

	return L"";
}

std::string	CT2U8::GetUTF8()
{
	if( m_pszUtf8 != NULL )
		return m_pszUtf8;
	else if( m_pwsz != NULL )
	{
		int nReqSize = WideCharToMultiByte( CP_UTF8, 0, m_pwsz, -1, m_pszUtf8, 0, NULL, NULL );
		m_pszUtf8 = new char[ nReqSize ];
		memset( m_pszUtf8, '\0', nReqSize );

		int nRetSize = WideCharToMultiByte( CP_UTF8, 0, m_pwsz, -1, m_pszUtf8, nReqSize, NULL, NULL );
		if( nRetSize > 0 )
			return m_pszUtf8;
	}
	else if( m_pwsz == NULL && m_psz != NULL )
	{
		// UTF8 로의 변환은 UNICODE 상태에서만 가능
		std::wstring strString = CT2U8(m_psz).GetUTF16();

		int nReqSize = WideCharToMultiByte( CP_UTF8, 0, strString.c_str(), -1, m_pszUtf8, 0, NULL, NULL );
		m_pszUtf8 = new char[ nReqSize ];
		memset( m_pszUtf8, '\0', nReqSize );

		int nRetSize = WideCharToMultiByte( CP_UTF8, 0, strString.c_str(), -1, m_pszUtf8, nReqSize, NULL, NULL );
		if( nRetSize > 0 )
			return m_pszUtf8;
	}

	return "";
}


CT2U8::~CT2U8()
{
	DeletePtrA<char*>(m_psz);
	DeletePtrA<char*>(m_pszUtf8);
	DeletePtrA<wchar_t*>(m_pwsz);
}


///////////////////////////////////////////////////////////////////////////////////////////

CU8T2::CU8T2() 
	: m_psz(NULL), m_pwsz(NULL), m_pszUtf8(NULL)
{

}

CU8T2::CU8T2( const char* pszString )
	: m_psz(NULL), m_pwsz(NULL), m_pszUtf8(NULL)
{
	*this = pszString;
}

CU8T2::CU8T2( const std::string& strString )
	: m_psz(NULL), m_pwsz(NULL), m_pszUtf8(NULL)
{
	*this = strString;
}

CU8T2::CU8T2( const CU8T2& string )
	: m_psz(NULL), m_pwsz(NULL), m_pszUtf8(NULL)
{
	*this = string;
}

CU8T2& CU8T2::operator =( const char* pszString )
{
	if( pszString )
	{
		DeletePtrA<char*>(m_psz);
		int nSize = strlen( pszString ) + 1;
		m_psz = new char[ nSize ];
		memset( m_psz, '\0', nSize * sizeof(char) );
		strcpy_s( m_psz, nSize, pszString );
	}

	return *this;
}

CU8T2& CU8T2::operator =( const std::string& strString )
{
	if( strString.length() > 0 )
	{
		DeletePtrA<char*>(m_psz);
		int nSize = strlen( strString.c_str() ) + 1;
		m_psz = new char[ nSize ];
		memset( m_psz, '\0', nSize * sizeof(char) );
		strcpy_s( m_psz, nSize, strString.c_str() );
	}

	return *this;
}

CU8T2& CU8T2::operator =( const CU8T2& string )
{
	if( string.m_psz )
	{
		DeletePtrA<char*>(m_psz);
		int nSize = strlen( string.m_psz ) + 1;
		m_psz = new char[ nSize ];
		memset( m_psz, '\0', nSize * sizeof(char) );
		strcpy_s( m_psz, nSize, string.m_psz );
	}
	if( string.m_pwsz )
	{
		DeletePtrA<wchar_t*>(m_pwsz);
		int nSize = wcslen( string.m_pwsz ) + 1;
		m_pwsz = new wchar_t[ nSize ];
		memset( m_pwsz, '\0', nSize * sizeof(wchar_t) );
		wcscpy_s( m_pwsz, nSize, string.m_pwsz );
	}

	return *this;
}

std::string	CU8T2::GetMBCS()
{
	// 이미 한번 변환해서 MBCS가 있다면 그대로 반환
	if( m_psz != NULL )
		return m_psz;

	if( m_pwsz == NULL )
		return "";

	// 없다면 unicode 에서 변환
	int nReqSize = WideCharToMultiByte( CP_ACP, WC_NO_BEST_FIT_CHARS, m_pwsz, -1, m_psz, 0, NULL, NULL );
	m_psz = new char[ nReqSize ];
	memset( m_psz, '\0', nReqSize );

	int nRetSize = WideCharToMultiByte( CP_ACP, WC_NO_BEST_FIT_CHARS, m_pwsz, -1, m_psz, nReqSize, NULL, NULL );
	if( nRetSize > 0 ) 
		return m_psz;

	return "";
}

std::wstring	CU8T2::GetUTF16()
{
	if( m_pwsz != NULL )
		return m_pwsz;

	if( m_psz == NULL )
		return L"";

	int nReqSize = MultiByteToWideChar( CP_UTF8, 0, m_psz, -1, m_pwsz, 0 );
	m_pwsz = new wchar_t[ nReqSize ];
	memset( m_pwsz, '\0', sizeof(wchar_t) * nReqSize );

	int nRetSize = MultiByteToWideChar( CP_UTF8, 0, m_psz, -1, m_pwsz, nReqSize );
	if( nRetSize > 0 )
		return m_pwsz;

	return L"";
}

std::string	CU8T2::GetUTF8()
{
	if( m_pszUtf8 != NULL )
		return m_pszUtf8;
	else if( m_pwsz != NULL )
	{
		int nReqSize = WideCharToMultiByte( CP_UTF8, 0, m_pwsz, -1, m_pszUtf8, 0, NULL, NULL );
		m_pszUtf8 = new char[ nReqSize ];
		memset( m_pszUtf8, '\0', nReqSize );

		int nRetSize = WideCharToMultiByte( CP_UTF8, 0, m_pwsz, -1, m_pszUtf8, nReqSize, NULL, NULL );
		if( nRetSize > 0 )
			return m_pszUtf8;
	}
	else if( m_pwsz == NULL && m_psz != NULL )
	{
		// UTF8 로의 변환은 UNICODE 상태에서만 가능
		std::wstring strString = CT2U8(m_psz).GetUTF16();

		int nReqSize = WideCharToMultiByte( CP_UTF8, 0, strString.c_str(), -1, m_pszUtf8, 0, NULL, NULL );
		m_pszUtf8 = new char[ nReqSize ];
		memset( m_pszUtf8, '\0', nReqSize );

		int nRetSize = WideCharToMultiByte( CP_UTF8, 0, strString.c_str(), -1, m_pszUtf8, nReqSize, NULL, NULL );
		if( nRetSize > 0 )
			return m_pszUtf8;
	}

	return "";
}


CU8T2::~CU8T2()
{
	DeletePtrA<char*>(m_psz);
	DeletePtrA<char*>(m_pszUtf8);
	DeletePtrA<wchar_t*>(m_pwsz);
}

