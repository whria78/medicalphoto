#include "stdafx.h"
#include "log_server.h"

log_server::log_server(int iLogPort)
  : basic_server<log_connection>(iLogPort,log_,config_,async_connection_manager_)
	,CMyCout(_tcout)
	,log_(_tcout)
	,config_(log_)
	,log_connection_(0,basic_server::io_service_,config_,async_connection_manager_)
//	,WhriaClient(
//	,config_(c_)
{
	connection_id=1;
	boost::shared_ptr<log_connection> ptr;
	ptr.reset(&log_connection_);
	async_connection_manager_.add(ptr);
	config_.load();
	WriteString(_T("Initiate Log Server\n"));
}
