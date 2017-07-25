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
#include "../share/codechange.h"

#include "../share/error.h"
#include "../share/unicode.h"
#include "../share/codechange.h"
#include "../share/datatype.h"
#include "../share/sql_db.h"
#include "../share/cmycout.h"

#include "../share/etc.h"

class CSQLLog
{
public:
	CSQLLog()
	{
	}
	~CSQLLog()
	{
	}

	tstring WriteError(const error_message& err);
	tstring WriteCommand(const std::string& user_id,int iOrderCode,const std::string& param1,const std::string& param2="");
	tstring WriteCommand(const std::string& user_id,int iOrderCode,const std::string& param1,int param2)
	{
	   boost::format fmt("%d");fmt % param2;
	   return WriteCommand(user_id,iOrderCode,param1,fmt.str());
	}
	tstring WriteCommand(const std::string& user_id,int iOrderCode)
	{
		return WriteCommand(user_id,iOrderCode,"");
	}
private:

protected:
};
