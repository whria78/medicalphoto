////////////////////////////////////////////////////////////////////////////////
// Copyright : Han Seung Seog
// https://medicalphoto.modelderm.com
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../boost.h"
#include <string>
#include <boost/format.hpp>
#include "tchar.h"
#include "utf8_codecvt_facet.hpp"
#include "unicode.h"
#include "windows.h"
//#include "convertUTF8.h"

#ifdef _UNICODE
	#define _CCL U_W
	#define _CCU W_U
	#define _CCW s2ws
	#define _CCN ws2s
#else 
	#define _CCL U_L
	#define _CCU L_U
	#define _CCW LocaltoLocal
	#define _CCN LocaltoLocal
#endif // _UNICODE

class MCodeChanger
{
public:
	static tstring LocaltoLocal(const tstring& str) 
	{
		return str;
	}

	static std::string L_U(const std::string& str)
	{
		std::locale local(std::locale(""),new utf8_codecvt_facet);
		return wcs_to_mbs(mbs_to_wcs(str),local);
	}
	static std::string U_L(const std::string& str)
	{
		std::locale local(std::locale(""),new utf8_codecvt_facet);
		return wcs_to_mbs(mbs_to_wcs(str,local));
	}
	static std::string W_U(const std::wstring& str)
	{
//		return CT2U8(str).GetUTF8();
		std::locale local(std::locale(""),new utf8_codecvt_facet);
		return wcs_to_mbs(str,local);
	}
	static std::wstring U_W(const std::string& str)
	{
//		return CU8T2(str).GetUTF16();
		std::locale local(std::locale(""),new utf8_codecvt_facet);
		return mbs_to_wcs(str,local);
	}

static std::wstring
mbs_to_wcs(std::string const& str, std::locale const& loc = std::locale(""))
{
    typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
    codecvt_t const& codecvt = std::use_facet<codecvt_t>(loc);
    std::mbstate_t state;
    std::vector<wchar_t> buf(str.size() + 1);
    char const* in_next = str.c_str();
    wchar_t* out_next = &buf[0];
    codecvt_t::result r = codecvt.in(state,
        str.c_str(), str.c_str() + str.size(), in_next,
        &buf[0], &buf[0] + buf.size(), out_next);
    return std::wstring(&buf[0]);
}
 
static std::string
wcs_to_mbs(std::wstring const& str, std::locale const& loc = std::locale(""))
{
    typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
    codecvt_t const& codecvt = std::use_facet<codecvt_t>(loc);
    std::mbstate_t state;
    std::vector<char> buf((str.size() + 1) * codecvt.max_length());
    wchar_t const* in_next = str.c_str();
    char* out_next = &buf[0];
    codecvt_t::result r = codecvt.out(state,
        str.c_str(), str.c_str() + str.size(), in_next,
        &buf[0], &buf[0] + buf.size(), out_next);
    return std::string(&buf[0]);
}
static std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

static std::string ws2s(const std::wstring& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
	char* buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0);
	std::string r(buf);
	delete[] buf;
	return r;
}

};


