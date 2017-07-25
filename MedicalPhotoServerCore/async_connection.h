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

#include "../share/config.h"
#include "../share/sql_db.h"
#include "../share/datatype.h"
#include "../share/file.h"
#include "../share/cmycout.h"
#include "../share/netpath.h"
#include "../share/etc.h"

//#include "../client/basic_client.h"

#ifdef _DEBUG
#define ORDER_WAITING_TIMEOUT 6
#define STREAMING_TIMEOUT 30
#endif
#ifndef _DEBUG
#define ORDER_WAITING_TIMEOUT 6
#define STREAMING_TIMEOUT 30
#endif

class async_connection_manager;

class async_connection 
	: 
	public connection_basic,
	public boost::enable_shared_from_this<async_connection>,
	private boost::noncopyable
{
public:
  explicit async_connection(int async_connection_id_
	  ,boost::asio::io_service& io_service
	  ,config& c_
	  ,async_connection_manager& manager)
    : connection_basic(io_service)
	,async_connection_manager_(manager)
	,log(c_.log)
	,async_connection_id(async_connection_id_)
	,bRunningFlag(false)
	,netpath_(c_)
	{
		clear();
	}
	~async_connection()
	{
	}

	void start() 
	{
		stIPAddress=socket().remote_endpoint().address().to_string();
#ifdef _DEBUG
		log<<_T("## [Connect] ") << MCodeChanger::_CCL(stIPAddress) << log.endl() ;
#endif
		handle_waiting_order();
	}
	void stop() {connection_basic::stop();}

	void pause();
	void resume();
/*
	template <typename T1,typename T2,typename R>
	void ExecuteBlockingOrder(int order_code_,T1& p1_,T2& p2_,R& result_)
	{
		pause();
		execute_order(order_code_,p1_,p2_,result_);
		resume();
	}
*/
  boost::asio::ip::tcp::socket& socket() {return connection_basic::socket();}
  int GetConnectionID() {return async_connection_id;}

protected:

	std::string stIPAddress;

  async_connection_manager& async_connection_manager_;
  CMyCout& log;
  int async_connection_id;

	netpath netpath_;
	command command_;
	bool bFileTransfer;
	tstring stLocalPath;
	__int64 lFileSize;
	FILE *fp;
	error_message result_message;
	__int64 blank_;

  void clear() 
  {
	bFileTransfer=false;
	stLocalPath=_T("");
	lFileSize=0;
	fp=NULL;
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
  void LogOff();

  void handle_filetransfer(const boost::system::error_code& e,FILE* fp,const tstring& stLocalPath,__int64 lFileSize);
  void handle_uploadprocess(const boost::system::error_code& e);

  virtual void WaitingOrder();
  virtual void ExecuteOrder(boost::archive::text_iarchive& archive_in
		,boost::archive::text_oarchive& archive_out)=0;

public:
  virtual void PostExecuteOrder();
protected:
  void handle_postexecute_order(const boost::system::error_code& e);

public:
  template <typename Param1,typename Param2,typename Result>
  void AsyncExecuteOrder(__int32 order_code_,const Param1& p1_,const Param2& p2_,Result& result_)
  {
		clear();
		command cmd_;cmd_.order_code=order_code_;

		std::istringstream archive_stream_in(connection_basic::InboundBuffer());
		boost::archive::text_iarchive archive_in(archive_stream_in);

		std::ostringstream archive_stream_out;
		boost::archive::text_oarchive archive_out(archive_stream_out);

		serial_out(archive_out,cmd_);
		serial_out(archive_out,p1_);
		serial_out(archive_out,p2_);

		connection_basic::OutboundBuffer()= archive_stream_out.str();
		connection_basic::async_write(boost::bind(&async_connection::handle_asyncexecute_order, this,boost::asio::placeholders::error)
			,boost::posix_time::seconds(STREAMING_TIMEOUT));
  }

  void handle_asyncexecute_order(const boost::system::error_code& e);


};

typedef boost::shared_ptr<async_connection> async_connection_ptr;
typedef std::vector<async_connection_ptr> async_connection_list;

