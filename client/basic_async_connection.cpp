#include "stdafx.h"

#include "basic_async_connection.h"

void basic_async_connection::process_socket_error(const boost::system::error_code& e)
{
	if (e!=boost::asio::error::operation_aborted)
	{
		error_message err_;
		err_.Add(SOC_ERROR,e.value(),e.message());
		process_error(err_);
		stop();
	}
}

void basic_async_connection::handle_execute_order(const boost::system::error_code& e)
{
	if (e) {
		process_socket_error(e);
		return;
	}
	bRunningFlag=true;


#ifdef _DEBUG
	  log<<_T("basic_async_connection::handle_execute_order\n");
#endif

	clear();

	std::istringstream archive_stream_in(connection_basic::InboundBuffer());
	boost::archive::text_iarchive archive_in(archive_stream_in);

	std::ostringstream archive_stream_out;
	boost::archive::text_oarchive archive_out(archive_stream_out);

	try
	{
		ExecuteOrder(archive_in,archive_out);
	}
	catch (CppSQLite3Exception& e)
	{
		connection_basic::free_InboundBuffer();

		result_message.Add(SQL_ERROR,e.errorCode(),e.errorMessage());
		process_error(result_message);
	}
    catch (std::exception& e)
    {
		connection_basic::free_InboundBuffer();

		std::string stErrMsg=e.what();
		boost::algorithm::replace_first(stErrMsg,"boost::filesystem::","");
		result_message.Add(DECODING_DATA,0,stErrMsg);
		process_error(result_message);
	}

	if (result_message.CheckError())
		serial_out(archive_out,result_message);

	connection_basic::OutboundBuffer()= archive_stream_out.str();

	if (command_.order_code==LOGIN && result_message.CheckError())
	{
		connection_basic::async_write(boost::bind(&basic_async_connection::handle_logoff, this),
		boost::posix_time::seconds(STREAMING_TIMEOUT));
		return;
	}

	connection_basic::async_write(boost::bind(&basic_async_connection::handle_waiting_order, this,boost::asio::placeholders::error),
	boost::posix_time::seconds(STREAMING_TIMEOUT));
}


void basic_async_connection::handle_logoff()
{
	LogOff();
}
 void basic_async_connection::LogOff()
{
	stop();
}
 
  void basic_async_connection::handle_waiting_order(const boost::system::error_code& e)
  {
	if (e) {process_socket_error(e);return;}
	  handle_waiting_order();
  }
 void basic_async_connection::WaitingOrder()
 {
#ifdef _DEBUG
	  log<<_T("basic_async_connection::handle_waiting_order\n");
#endif

	  clear();
	  connection_basic::async_read(boost::bind(&basic_async_connection::handle_execute_order,this,boost::asio::placeholders::error),
		  boost::posix_time::hours(ORDER_WAITING_TIMEOUT));
 }


void basic_async_connection::handle_waiting_order()
{
	WaitingOrder();
	condition_con.notify_one();
	bRunningFlag=false;
}

void basic_async_connection::pause()
{
	if (bRunningFlag)
	{
		boost::mutex::scoped_lock lock(mutex_con);
		condition_con.wait(lock);
	}
	socket().cancel();
}
void basic_async_connection::resume()
{
	handle_waiting_order();
}

