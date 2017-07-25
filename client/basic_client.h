#pragma once

#include "../boost.h"
#include <boost/thread/mutex.hpp>

#include "connection.h"
#include "../share/etc.h"
//#include "../share/config.h"
//#include "../share/datatype.h"

class basic_client :
	public client_connection
{
public:
  basic_client(boost::asio::io_service& io_,boost::asio::ip::tcp::socket& soc_)
    : io_service_(io_)
	,client_connection(io_,soc_)
  {
  }
  void connect(const std::string& host,const std::string& port);
  void disconnect() {socket().close();}

  class ConnectionEx
  {
  public:
	  std::string stMessage;
	  size_t iErrorCode;
	  size_t iErrorCode_Detail;
	  ConnectionEx(int code,int iErrorCode_Detail,const std::string& msg)
	  {
		  iErrorCode=code;
		  stMessage=msg;
		  iErrorCode_Detail=-1;
	  }
	  ConnectionEx(int code)
	  {
		  iErrorCode=code;
		  stMessage=error_list[iErrorCode];
		  iErrorCode_Detail=-1;
	  }
	  ConnectionEx(const error_message& err)
	  {
		  iErrorCode=err.iErrCode;
		  stMessage=err.stErrMessage;
		  iErrorCode_Detail=err.iErrCodeDetail;
	  }
  };

protected:

  boost::asio::io_service& io_service_;

  template <typename Param1,typename Param2,typename Result>
  void execute_order(__int32 order_code_,const Param1& p1_,const Param2& p2_,Result& result_)
  {
	boost::mutex::scoped_lock lock(mutex_);

	clear_temp();
	command cmd_;cmd_.order_code=order_code_;

    try
    {
	    std::ostringstream archive_stream;
	    boost::archive::text_oarchive archive(archive_stream);
		serial_out(archive,cmd_);
		serial_out(archive,p1_);
		serial_out(archive,p2_);
		client_connection::OutboundBuffer()= archive_stream.str();
	}
    catch (std::exception& e)
    {
		  client_connection::free_InboundBuffer();
		  throw client_connection::ConnectionEx(DECODING_DATA,0,e.what());
    }
	client_connection::async_write();

	error_message err_;

	client_connection::async_read_header();
	client_connection::async_read_data();
	try
    {
        std::istringstream archive_stream(client_connection::InboundBuffer());
        boost::archive::text_iarchive archive(archive_stream);
        archive >> err_;
		if (!err_.CheckError())
			archive >> result_;
		client_connection::free_InboundBuffer();
    }
    catch (std::exception& e)
    {
		// Unable to decode data.
		client_connection::free_InboundBuffer();
		throw client_connection::ConnectionEx(DECODING_DATA,0,e.what());
    }

	if (err_.CheckError())
	{
		if (err_.iErrCode==SOC_ERROR)
			throw client_connection::ConnectionEx(err_);
		else
			throw basic_client::ConnectionEx(err_);
	}

  }

  void set_stream_result(boost::optional<boost::system::error_code>* a, const boost::system::error_code& b) 
  { 
	  a->reset(b);
  } 
  void set_result(boost::optional<boost::system::error_code>* a, const boost::system::error_code& b,size_t* length,const size_t& len) 
  { 
	  a->reset(b);
	  *length=len;
  } 
	std::string ChangePath(const std::string& str)
	{
		return Utility::ChangePath(str);
	}
	void ChangePath(std::vector<std::string> str)
	{
		for (unsigned int i=0;i<str.size();i++)
		{
			str[i]=Utility::ChangePath(str[i]);
		}
	}
	static boost::mutex mutex_;

};