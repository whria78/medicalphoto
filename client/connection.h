//
// client_connection.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2007 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//

#ifndef MEDIEYE_BASIC_CONNECTION_HPP
#define MEDIEYE_BASIC_CONNECTION_HPP

#include "../boost.h"

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#pragma warning(disable: 4005)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <wspiapi.h>
#define GetAddrInfo WspiapiGetAddrInfo
#define FreeAddrInfo WspiapiFreeAddrInfo

#include <boost/asio.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/format.hpp>

#include <boost/asio/ssl.hpp>

#include "../share/datatype.h"
#include "../share/file.h"
#include "../share/config.h"

#ifdef _DEBUG
#include "../share/cmycout.h"
#endif
	
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

#include "../share/unicode.h"

#define BUFFER_SIZE 4096

#ifdef _DEBUG

#define ORDER_WAITING_TIMEOUT 30
#define STREAMING_TIMEOUT 30
#define FILETRANSFER_TIMEOUT 10
#define ACCEPT_TIMEOUT 30
#define SCAN_TIMEOUT 30

#endif
#ifndef _DEBUG

#define ORDER_WAITING_TIMEOUT 30
#define STREAMING_TIMEOUT 30
#define FILETRANSFER_TIMEOUT 10
#define ACCEPT_TIMEOUT 5
#define SCAN_TIMEOUT 30

#endif
class client_connection
{
public:
  client_connection(boost::asio::io_service& io_service, boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& soc_)
    : io_service_(io_service)
    ,log(_tcout)
	,timer_(io_service)
	,socket_(soc_)
  {
	 inbound_data_=NULL;
  }

  ~client_connection()
  {
//	  io_service_.stop();
  }


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

  boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& socket() {return socket_;}

  void connect(const std::string& host,const std::string& service);
  void scan(const std::string& host,const std::string& service);

  // SSL
  void socket_close()
  {
	  // Cancel any ongoing operations
	  socket_.lowest_layer().cancel();

	  // Start async shutdown
	  socket_.async_shutdown(
		  boost::bind(&client_connection::shutdown_handler, this, boost::asio::placeholders::error));

	  // Set a timeout for shutdown
	  timer_.expires_from_now(boost::posix_time::seconds(5));
	  timer_.async_wait(boost::bind(&client_connection::shutdown_timeout, this, boost::asio::placeholders::error));
  }

private:

	// 기존 handle_connect를 handshake를 고려하여 수정
	void handle_connect(boost::optional<boost::system::error_code>* socket_result,
		const boost::system::error_code& error)
	{
		if (!error)
		{
			std::cout << "Connected, starting handshake...\n";
			socket_.async_handshake(boost::asio::ssl::stream_base::client,
				boost::bind(&client_connection::handle_handshake, this, socket_result,
					boost::asio::placeholders::error));
		}
		else
		{
			std::cout << "Connect failed: " << error.message() << "\n";
			set_result(socket_result, error);
		}
	}

	// handshake 완료 후 set_result 호출
	void handle_handshake(boost::optional<boost::system::error_code>* socket_result,
		const boost::system::error_code& error)
	{
		if (!error)
		{
			std::cout << "Handshake successful!\n";
		}
		else
		{
			std::cout << "Handshake failed: " << error.message() << "\n";
		}
		set_result(socket_result, error); // handshake 완료 후 socket_result 설정
	}

  void connect(boost::asio::ip::tcp::endpoint endpoint,
						 boost::optional<boost::system::error_code>& timer_result,
						 boost::optional<boost::system::error_code>& socket_result);
  void scan(boost::asio::ip::tcp::endpoint endpoint,
						 boost::optional<boost::system::error_code>& timer_result,
						 boost::optional<boost::system::error_code>& socket_result);

private:
	void shutdown_handler(const boost::system::error_code& ec)
	{
		timer_.cancel(); // Cancel timeout timer

		if (ec)
		{
			//std::cerr << "SSL shutdown error: " << ec.message() << std::endl;
			std::wstring dumy = MCodeChanger::_CCW("SSL shutdown error: " + ec.message());log << dumy << _T("\n");
		}

		// Close the underlying socket
		boost::system::error_code close_ec;
		socket_.lowest_layer().close(close_ec);
		if (close_ec)
		{
			//std::cerr << "Socket close error: " << close_ec.message() << std::endl;
			std::wstring dumy = MCodeChanger::_CCW("Socket close error: " + close_ec.message()); log << dumy << _T("\n");
		}
	}

	void shutdown_timeout(const boost::system::error_code& ec)
	{
		if (!ec) // If timeout occurred
		{
			//std::cerr << "SSL shutdown timed out. Forcing socket close." << std::endl;
			std::wstring dumy = MCodeChanger::_CCW("SSL shutdown timed out. Forcing socket close."); log << dumy << _T("\n");
			socket_.lowest_layer().close();
		}
	}

protected:
  std::string InboundBuffer() {return std::string(inbound_data_);}
  std::string& OutboundBuffer() {return outbound_data_;}

  // Serialization
  void async_write();
  void async_read_header();
  void async_read_data();
  //void handle_async_read();

  void free_InboundBuffer()
  {
	  if (inbound_data_!=NULL) 
	  {
		  delete [] inbound_data_;
		  inbound_data_=NULL;
	  }
  }


protected:
	boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& socket_;
	boost::asio::deadline_timer timer_;
	CMyCout log; 

public:  boost::asio::io_service& io_service_;

  void set_result(boost::optional<boost::system::error_code>* a, const boost::system::error_code& b) 
  { 
	  a->reset(b);
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


  // serialize
  enum { header_length = 8 };
  std::string outbound_header_;
  std::string outbound_data_;
  char inbound_header_[header_length];
  std::vector<char> inbound_data_vector;
  char* inbound_data_;
  unsigned char data_[BUFFER_SIZE];


  void clear_temp()
  {
	  outbound_header_.clear();
	  outbound_data_.clear();
	  inbound_data_vector.clear();
	  free_InboundBuffer();
  }

  template <typename T>
  void serial_out(boost::archive::text_oarchive& archieve,const T&t){archieve << t;}
  template <typename T>
  void serial_in(const boost::archive::text_iarchive& archieve,T&t){archieve >> t;}
};

typedef boost::shared_ptr<client_connection> client_connection_ptr;

#endif // SERIALIZATION_client_connection_HPP

