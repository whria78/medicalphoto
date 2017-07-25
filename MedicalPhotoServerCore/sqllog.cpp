#include "stdafx.h"
#include "sqllog.h"
/*
tstring CSQLLog::WriteError(const error_message& err)
{
	boost::mutex::scoped_lock lock(CMyCout::log_mutex);

	_tformat fmt(_T("(%d) %s :  %s\n\0"));
	fmt % err.iErrCodeDetail
		% MCodeChanger::_CCL(err.stErrMessage.c_str())
		% CMyCout::endl();

	data_=fmt.str();
	WriteAll();

   return fmt.str();
}
tstring CSQLLog::WriteCommand(const std::string& user_id,int iOrderCode,const std::string& param1,const std::string& param2)
{
	boost::mutex::scoped_lock lock(CMyCout::log_mutex);

	if (param2.empty())
	{
		_tformat fmt(_T("[%s]\t[%s]\t( %s )  %s"));
		fmt 
			% MCodeChanger::_CCL(user_id)
			% MCodeChanger::_CCL(command::code_to_string(iOrderCode))
			% MCodeChanger::_CCL(param1)
			% CMyCout::endl();
		data_=fmt.str();

		WriteAll();
		return fmt.str();
	}
	else
	{
		_tformat fmt(_T("[%s]\t[%s]\t( %s  /  %s )  %s"));
		fmt 
			% MCodeChanger::_CCL(user_id)
			% MCodeChanger::_CCL(command::code_to_string(iOrderCode))
			% MCodeChanger::_CCL(param1)
			% MCodeChanger::_CCL(param2)
			% CMyCout::endl();
		data_=fmt.str();

		WriteAll();
		return fmt.str();
	}
}
*/