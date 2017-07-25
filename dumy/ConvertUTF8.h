/*
	MBCS, Unicode <---> UTF-8 ��ȯ�� �����ϴ� Ŭ���� 

	���� : �︶

	���� �ϼ� : 2009-04-16

	2009-05-11	: CT2U8 �� ������Կ����ڿ��� �޸� �ʱ�ȭ ���� ����
	2009-05-11	: CU8T2 �� ������Կ����ڿ��� �޸� �ʱ�ȭ ���� ����
	2009-05-17 : SDK ��� OS ȯ���� ���� XP �϶��� �������� �����ϵ��� ���� ����
	2009-05-29 : CU8T2 �����ڿ� std::string �� �޵��� �߰�, �ݵ�� utf8 �����̾����
	2009-05-29 : CU8T2 Ŭ������ GetUTF16 �Լ��� ���� ����

	���� �ü���� �����Լ��� ����ϱ⶧���� ���� ��� �ʿ�. 
	C ��Ÿ�� ���̺귯���� UTF8 ��ȯ�� �������� ����
*/

#pragma once

#include <crtdefs.h>
#include <string>
#include "windows.h"
#include "Util.h"

// MBCS �Ǵ� UTF16 ���� Ŭ������ ���� �� �ݴ�Ǵ� ���ڿ����� �����ϸ� ������ �ִ� ���ڿ��� �����
// m_psz �� m_pwsz �� ������ ���� ������ ���ڿ��� ����Ŵ
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
