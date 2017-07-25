#include "stdafx.h"

#include "async_connection.h"
#include "async_connection_manager.hpp"
//#include <boost/enable_shared_from_this.hpp>

void async_connection::process_socket_error(const boost::system::error_code& e)
{
	if (e!=boost::asio::error::operation_aborted)
	{
		if (e.value()==2)
		{
			async_connection_manager_.stop(shared_from_this());
		}
		else
		{
			error_message err_;
			err_.Add(SOC_ERROR,e.value(),e.message());
			process_error(err_);
			async_connection_manager_.stop(shared_from_this());
		}
	}
}

/*
void async_connection::PostExecuteOrder(boost::archive::text_iarchive& archive_in
		,boost::archive::text_oarchive& archive_out)
{

}*/
void async_connection::handle_execute_order(const boost::system::error_code& e)
{
	if (e) {
		process_socket_error(e);
		return;
	}
	bRunningFlag=true;


#ifdef _DEBUG
	  log<<_T("async_connection::handle_execute_order\n");
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
		if (fp!=NULL) {fclose(fp);fp=NULL;}

		result_message.Add(SQL_ERROR,e.errorCode(),e.errorMessage());
		process_error(result_message);
	}
    catch (std::exception& e)
    {
		connection_basic::free_InboundBuffer();
		if (fp!=NULL) {fclose(fp);fp=NULL;}

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
		connection_basic::async_write(boost::bind(&async_connection::handle_logoff, this),
		boost::posix_time::seconds(STREAMING_TIMEOUT));
		return;
	}

	if (bFileTransfer)
	{
		connection_basic::async_write(boost::bind(&async_connection::handle_filetransfer, this,
		  boost::asio::placeholders::error,
		  fp,
		  stLocalPath,lFileSize),
		  boost::posix_time::seconds(STREAMING_TIMEOUT));
	}
	else
	{
		connection_basic::async_write(boost::bind(&async_connection::handle_postexecute_order, this,boost::asio::placeholders::error),
		boost::posix_time::seconds(STREAMING_TIMEOUT));
	}
}


void async_connection::handle_logoff()
{
	LogOff();
}
 void async_connection::LogOff()
{
	async_connection_manager_.stop(shared_from_this());
}
 
  void async_connection::handle_waiting_order(const boost::system::error_code& e)
  {
	if (e) {process_socket_error(e);return;}
	  handle_waiting_order();
  }
 void async_connection::WaitingOrder()
 {
#ifdef _DEBUG
	  log<<_T("async_connection::handle_waiting_order\n");
#endif

	  clear();
	  connection_basic::async_read(boost::bind(&async_connection::handle_execute_order,this,boost::asio::placeholders::error),
		  boost::posix_time::hours(ORDER_WAITING_TIMEOUT));
 }


void async_connection::handle_waiting_order()
{
	WaitingOrder();
	condition_con.notify_one();
	bRunningFlag=false;
}
/*
void async_connection::pause()
{
	boost::thread BuildThread(boost::bind(&async_connection::pausethread,this));
	BuildThread.join();
}
*/


void async_connection::pause()
{
	if (bRunningFlag)
	{
		boost::mutex::scoped_lock lock(mutex_con);
		condition_con.wait(lock);
	}
	socket().cancel();
}
void async_connection::resume()
{
	handle_waiting_order();
}


  void async_connection::handle_filetransfer(const boost::system::error_code& e,FILE* fp,const tstring& stLocalPath,__int64 lFileSize)
{
	if (e) 
	{
		process_socket_error(e);
		if (fp!=NULL) {fclose(fp);fp=NULL;}
		return;
	}

#ifdef _DEBUG
	  log<<_T("async_connection::handle_filetransfer\n");
#endif

	switch (command_.order_code)
	{

		case UPLOADFILE:
			{
				connection_basic::async_download_file(fp,
					stLocalPath,
					lFileSize,
					boost::bind(&async_connection::handle_uploadprocess, this,boost::asio::placeholders::error));
			}
			break;
		case THUMB_UPLOADFILE:
			{
				connection_basic::async_download_file(fp,
					stLocalPath,
					lFileSize,
					boost::bind(&async_connection::handle_postexecute_order, this,boost::asio::placeholders::error));
			}
			break;

		case UPDATE:
		case DOWNLOADFILE:
		case THUMB_DOWNLOADFILE:
			{
				connection_basic::async_upload_file(fp,
					stLocalPath,
					lFileSize,
					boost::bind(&async_connection::handle_postexecute_order, this,boost::asio::placeholders::error));
			}
			break;

	}

}
void async_connection::handle_uploadprocess(const boost::system::error_code& e)
{

	if (e) 
	{
		process_socket_error(e);
		return;
	}

	  // update sql

	error_message result_message;
	try
	{
	  fileinfo fileinfo_=netpath_.CreateFileInfoL(stLocalPath);
	  netpath_.LoadMetatag(fileinfo_);
	  netpath_.Insert(fileinfo_);
	}
	catch (CppSQLite3Exception& e)
	{
		result_message.Add(SQL_ERROR,e.errorCode(),e.errorMessage());
		process_error(result_message);
	}
    catch (std::exception& e)
    {
		result_message.Add(DECODING_DATA,0,e.what());
		process_error(result_message);
	}

	handle_postexecute_order(e);
}

void async_connection::handle_postexecute_order(const boost::system::error_code& e)
{
	if (e) 
	{
		process_socket_error(e);
		return;
	}

	try
	{
		PostExecuteOrder();
	}
	catch (CppSQLite3Exception& e)
	{
		connection_basic::free_InboundBuffer();
		if (fp!=NULL) {fclose(fp);fp=NULL;}

		result_message.Add(SQL_ERROR,e.errorCode(),e.errorMessage());
		process_error(result_message);
	}
    catch (std::exception& e)
    {
		connection_basic::free_InboundBuffer();
		if (fp!=NULL) {fclose(fp);fp=NULL;}

		std::string stErrMsg=e.what();
		boost::algorithm::replace_first(stErrMsg,"boost::filesystem::","");
		result_message.Add(DECODING_DATA,0,stErrMsg);
		process_error(result_message);
	}
	handle_waiting_order();
}

void async_connection::PostExecuteOrder()
{
}
void async_connection::handle_asyncexecute_order(const boost::system::error_code& e)
{
	if (e) {
		process_socket_error(e);
		return;}
	handle_waiting_order();
}
