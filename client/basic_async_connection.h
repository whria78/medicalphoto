//
// connection_basic.h
// ~~~~~~~~~~~~~~
//
#pragma once

#include "../boost.h"
#include "../share/unicode.h"
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/format.hpp>

#include "connection_basic.h"
#include "../share/cmycout.h"
/*
#include "../share/config.h"
#include "../share/sql_db.h"
#include "../share/datatype.h"
#include "../share/file.h"
#include "../share/cmycout.h"
#include "../share/netpath.h"
#include "../share/etc.h"
*/
#ifdef _DEBUG
#define ORDER_WAITING_TIMEOUT 600
#define STREAMING_TIMEOUT 600
#endif
#ifndef _DEBUG
#define ORDER_WAITING_TIMEOUT 6
#define STREAMING_TIMEOUT 5
#endif

class basic_async_connection 
	: 
	public connection_basic,
	public boost::enable_shared_from_this<basic_async_connection>,
	private boost::noncopyable
{
public:
  explicit basic_async_connection(boost::asio::io_service& io_service
	  ,boost::asio::ip::tcp::socket& soc_
	  ,CMyCout& l_)
    : connection_basic(io_service,soc_)
	,log(l_)
	,bRunningFlag(false)
	{
		clear();
	}
	~basic_async_connection()
	{
	}

	void start() 
	{
//		stIPAddress=socket().remote_endpoint().address().to_string();
//		log<<_T("## [Connect] ") << MCodeChanger::_CCL(stIPAddress) << log.endl() ;
		handle_waiting_order();
	}
	void stop() {connection_basic::stop();}

	void pause();
	void resume();

	boost::asio::ip::tcp::socket& socket() {return connection_basic::socket();}

protected:

	std::string stIPAddress;

  
	CMyCout& log;

	command command_;
	error_message result_message;
	__int64 blank_;

  void clear() 
  {
	command_.clear();
	result_message.clear();
	blank_=0;
  }

  bool bRunningFlag;
  boost::mutex mutex_con;
  boost::mutex mutex_blockingexec;
  boost::condition condition_con;

  template <typename T>
  void serial_out(boost::archive::text_oarchive& archieve,const T&t){archieve << t;}
  template <typename T>
  void serial_in(const boost::archive::text_iarchive& archieve,T&t){archieve >> t;}

  // Error Handling

  virtual void process_error(const error_message& err) {log.WriteError(err);}
  virtual void process_socket_error(const boost::system::error_code& e) ; 	

  void process_file_error(const std::string& err) 	{error_message err_;err_.Add(FILE_ERROR,0,err);process_error(err_);}
  void process_other_error(const std::string& err) 	{error_message err_;err_.Add(OTHER_ERROR,0,err);process_error(err_);}
  void process_error(const int& error_code,const std::string& err) 	{error_message err_;err_.Add(error_code,0,err);process_error(err_);}

protected:
  // Server Execute

	void handle_waiting_order(const boost::system::error_code& e);
	void handle_waiting_order();
    void handle_execute_order(const boost::system::error_code& e);
    void handle_logoff();
    virtual void LogOff();

	virtual void WaitingOrder();
	virtual void ExecuteOrder(boost::archive::text_iarchive& archive_in
		,boost::archive::text_oarchive& archive_out)=0;
};

typedef boost::shared_ptr<basic_async_connection> basic_async_connection_ptr;
typedef std::vector<basic_async_connection_ptr> basic_async_connection_list;

