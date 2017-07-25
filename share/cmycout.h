#pragma once

#include "../boost.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <boost/thread/mutex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include "codechange.h"
#include "error.h"
#include "unicode.h"
#include "codechange.h"
//#include "etc.h"
#include "../share/datatype_basic.h"

#define MEDIEYE_LOGSIZE 1000000 

class CMyCout:public _tostream
{
public:
	CMyCout(_tostream& os):
    	      _tostream(os.rdbuf()),os_(os)
				  ,iSetFlag(0)
	      {
			  prog_path=boost::filesystem::initial_path<_tpath>();
			  prog_path /= _T("log.txt");
	      }
		  
	~CMyCout();

	void SetFlag(int iSet) {iSetFlag=iSet;}

	friend CMyCout& operator<<(CMyCout& c, int data);
	friend CMyCout& operator<<(CMyCout& c, const TCHAR* string);
	friend CMyCout& operator<<(CMyCout& c, const tstring& string);
	friend CMyCout& operator<<(CMyCout& c, const error_message& err);
	friend CMyCout& operator<<(CMyCout& c, const log_struct& log_struct_);
	static tstring endl()
	{
	   tstring time=to_simple_tstring(boost::posix_time::second_clock::local_time());

		TCHAR buff[255];
		_stprintf(buff,_T(" : %s\n"),time.c_str());

		return tstring(buff);
	}
	virtual tstring WriteError(const error_message& err);
	virtual tstring WriteCommand(const std::string& user_id,int iOrderCode,const std::string& param1,const std::string& param2="");
	virtual tstring WriteCommand(const std::string& user_id,int iOrderCode,const std::string& param1,int param2)
	{
	   boost::format fmt("%d");fmt % param2;
	   return WriteCommand(user_id,iOrderCode,param1,fmt.str());
	}
	virtual tstring WriteCommand(const std::string& user_id,int iOrderCode)
	{
		return WriteCommand(user_id,iOrderCode,"");
	}

	_tostream& os_;
	tstring data_;
	static boost::mutex log_mutex;
private:
	_tpath prog_path;
	void WriteAll();
protected:
	virtual void WriteString(const tstring& str);
	tstring save_data_;
	void SaveString(tstring& save_data_);
	int iSetFlag;
};
