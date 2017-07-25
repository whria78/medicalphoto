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
  client_connection(boost::asio::io_service& io_service,boost::asio::ip::tcp::socket& soc_)
    : io_service_(io_service)
	,log(_tcout)
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

  boost::asio::ip::tcp::socket& socket() {return socket_;}

  void connect(const std::string& host,const std::string& service);
  void scan(const std::string& host,const std::string& service);

private:
  void connect(boost::asio::ip::tcp::endpoint endpoint,
						 boost::optional<boost::system::error_code>& timer_result,
						 boost::optional<boost::system::error_code>& socket_result);
  void scan(boost::asio::ip::tcp::endpoint endpoint,
						 boost::optional<boost::system::error_code>& timer_result,
						 boost::optional<boost::system::error_code>& socket_result);

 //serialize

protected:
  std::string InboundBuffer() {return std::string(inbound_data_);}
  std::string& OutboundBuffer() {return outbound_data_;}

  // Serialization
  void async_write();
  void async_read_header();
  void async_read_data();
  void handle_async_read();

  void free_InboundBuffer()
  {
	  if (inbound_data_!=NULL) 
	  {
		  delete [] inbound_data_;
		  inbound_data_=NULL;
	  }
  }


protected:
  boost::asio::ip::tcp::socket& socket_;
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

