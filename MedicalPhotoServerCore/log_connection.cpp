#include "stdafx.h"
#include "log_connection.h"

#include "async_connection_manager.hpp"

void log_connection::ExecuteOrder(boost::archive::text_iarchive& archive_in
								  ,boost::archive::text_oarchive& archive_out)
{
	archive_in >> command_;

	switch (command_.order_code)
	{
	  case LOGSEND:
	  {
		  log_struct log_struct_;
		  archive_in >> log_struct_;

		  InsertLog(log_struct_);

		  serial_out(archive_out,result_message);
//		  serial_out(archive_out,log_struct_);
	  }
	  break;
	  default:
	  {
		  result_message.Add(INVALID_COMMAND);

		  log.WriteError(result_message);
		  _tcout << _T("### INVALID COMMAND ###");
	  }
	  break;
	}
}

void log_connection::InsertLog(const log_struct& log_struct_)
{
#ifdef _WIN32
	std::ostringstream archive_stream_out;
	boost::archive::text_oarchive archive_out(archive_stream_out);

	archive_out 
		<< log_struct_;

	std::string steamout_=archive_stream_out.str();
	COPYDATASTRUCT cds;
	cds.dwData=WM_COPYDATA_LOG;
	cds.cbData=steamout_.length();
	cds.lpData=(void*)steamout_.c_str();

	SendMessage(m_hwnd,WM_COPYDATA,(WPARAM)m_hwnd,(LPARAM)&cds);
#endif
}