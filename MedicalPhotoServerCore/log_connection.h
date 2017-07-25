#pragma once

#include "async_connection.h"
#include "../share/etc.h"

class log_connection
	:public async_connection
{
public:
  explicit log_connection(int async_connection_id_
	  ,boost::asio::io_service& io_service
	  ,config& c_
	  ,async_connection_manager& manager)
    : async_connection(async_connection_id_,io_service,c_,manager)
	,m_hwnd(Utility::GetConsoleHwnd())
	{
	}
	~log_connection()
	{
	}
	void ExecuteOrder(boost::archive::text_iarchive& archive_in
		,boost::archive::text_oarchive& archive_out);

	void InsertLog(const log_struct& log_struct_);
protected:
	HWND m_hwnd;
};

typedef boost::shared_ptr<log_connection> log_connection_ptr;
