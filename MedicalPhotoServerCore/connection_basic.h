//
// connection_basic.hpp
// ~~~~~~~~~~~~~~
//

#ifndef MEDIEYE_SERIALIZATION_CONNECTION_HPP
#define MEDIEYE_SERIALIZATION_CONNECTION_HPP

#include "../boost.h"

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#include <winsock2.h>
#include <ws2tcpip.h>
#include <wspiapi.h>
#define GetAddrInfo WspiapiGetAddrInfo
#define FreeAddrInfo WspiapiFreeAddrInfo

#include "../share/unicode.h"

#include <boost/asio.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

//#include <boost/noncopyable.hpp>
//#include <boost/enable_shared_from_this.hpp>

#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

#include "../share/error.h"
#include "../share/file.h"

#include "../share/cmycout.h"
//#include "../client/basic_client.h"

#ifdef _DEBUG
#define BUFFER_SIZE 409600
#endif
#ifndef _DEBUG
#define BUFFER_SIZE 4096
#endif

#ifdef _DEBUG
#define FILETRANSFER_TIMEOUT 10
#endif
#ifndef _DEBUG
#define FILETRANSFER_TIMEOUT 10
#endif

class connection_basic 
//	:public basic_client
{
public:
  explicit connection_basic(boost::asio::io_service& io_service)
    : socket_(io_service)
	,io_service_(io_service)
//	,basic_client(io_service,socket_)
#ifdef _DEBUG
	,log(_tcout)
#endif
	,timer_(io_service)
  {
	  inbound_data_=NULL;
	  clear();
  }
  ~connection_basic()
  {
//	  stop();
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

  void stop() {socket_.close();}
  void cancel() {socket_.cancel();}

  void clear()
  {
	  lFileSize=0;
	  stFilePath.clear();
	  bytes_transfered_=0;
	  bytes_write=0;
	  bytes_read=0;
	  fp=NULL;

	  outbound_header_.clear();
	  outbound_data_.clear();
	  inbound_data_vector.clear();
	  free_InboundBuffer();
  }
public:

#ifdef _DEBUG
  CMyCout log;
#endif

protected:
  boost::asio::deadline_timer timer_;
  boost::asio::ip::tcp::socket socket_;
  boost::asio::io_service& io_service_; 

private:
  
  // file
  __int64 bytes_transfered_;
  __int64 bytes_write;
  __int64 bytes_read;

  FILE *fp;
  __int64 lFileSize;
  tstring stFilePath;


  // Streaming

  enum { header_length = 8 };
  std::string outbound_header_;
  std::string outbound_data_;
  char inbound_header_[header_length];
  std::vector<char> inbound_data_vector;
  char* inbound_data_;

protected:
  void free_InboundBuffer()
  {
	  if (inbound_data_!=NULL) 
	  {
		  delete [] inbound_data_;
		  inbound_data_=NULL;
	  }
  }

public:
  unsigned char data_[BUFFER_SIZE];

public:
  std::string InboundBuffer() {return std::string(inbound_data_);}
  std::string& OutboundBuffer() {return outbound_data_;}

private:

  template <typename T>
  void serial_out(boost::archive::text_oarchive& archieve,const T&t){archieve << t;}
  template <typename T>
  void serial_in(const boost::archive::text_iarchive& archieve,T&t){archieve >> t;}

  // Error Handling

  void handle_timeout(const boost::system::error_code& err,const char* message) 
  {
	  if (!err)
	  {
#ifdef _DEBUG
		  log << _T("Timeout : ") << MCodeChanger::_CCL(message) << log.endl();
#endif
		  socket_.close();
	  }
  }
  void handle_download_timeout(const boost::system::error_code& err,const char* message) 
  {
	  if (!err)
	  {

		  boost::format fmt("Timeout : %s : %s\n");
		  fmt % message % MCodeChanger::_CCN(stFilePath);

		  process_file_error(fmt.str(),true);
		  socket_.close();
	  }
  }
  void process_file_error(const std::string& err,bool bDownload) 	
  {
	  //closefp();
	  if (bDownload) MFile::DeleteL(stFilePath.c_str());
#ifdef _DEBUG
	  log << MCodeChanger::_CCL(err.c_str()) << log.endl();
#endif
  }

  void closefp()
  {
	if (fp!=NULL) {fclose(fp);fp=NULL;}
  }


public:


	// File


  template <typename Handler>
  void async_download_file(FILE* filepointer,const tstring& stLocalPath,__int64 filesize,Handler handler)
{
#ifdef _DEBUG
	log << _T("async_download_file\n");
#endif
	fp=filepointer;
	lFileSize=filesize;
	stFilePath=stLocalPath;
	
	bytes_transfered_=0;
	bytes_write=0;

	size_t download_size=BUFFER_SIZE;
	if (lFileSize<BUFFER_SIZE) download_size=(size_t)lFileSize;

	void (connection_basic::*f) (const boost::system::error_code &, const size_t& , boost::tuple<Handler>)
		=&connection_basic::handle_download_buffer<Handler>;

	socket_.async_read_some(boost::asio::buffer(data_,download_size),
		boost::bind(f,this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred,
		//		download_size,
		make_tuple(handler)));

    
	timer_.expires_from_now(boost::posix_time::seconds(FILETRANSFER_TIMEOUT));
	timer_.async_wait(boost::bind(&connection_basic::handle_download_timeout, this,boost::asio::placeholders::error,"download"));
}
  

  template <typename Handler>
  void handle_download_buffer(const boost::system::error_code& error,const size_t& bytes_transferred,boost::tuple<Handler> handler)
{
#ifdef _DEBUG
	log << _T("handle_download_buffer\n");
#endif
	if (error) {
		boost::get<0>(handler)(error);
//	closefp();
		return;
	}

	bytes_transfered_+=bytes_transferred;

	if (fp!=NULL) bytes_write+=fwrite(data_,sizeof(unsigned char),bytes_transferred,fp);

	if (bytes_transfered_==lFileSize)
	{
		if (bytes_write!=lFileSize) 
		{
			boost::format fmt("Receive & Write Not Matched : %s");fmt % MCodeChanger::_CCN(stFilePath.c_str());
			process_file_error(fmt.str(),true);

			boost::system::error_code error(boost::asio::error::eof);
			io_service_.post(boost::bind(boost::get<0>(handler), error));
//	closefp();
			return;
		}

		closefp();
		boost::get<0>(handler)(error);
		return;
	}
	else
	{

		size_t transfer_size=BUFFER_SIZE;
		if ((lFileSize-bytes_transfered_)<BUFFER_SIZE) transfer_size=(size_t)(lFileSize-bytes_transfered_);

		void (connection_basic::*f) (const boost::system::error_code &, const size_t& , boost::tuple<Handler>)
			=&connection_basic::handle_download_buffer<Handler>;

		socket_.async_read_some(boost::asio::buffer(data_,transfer_size),
		boost::bind(f,this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred,
		handler));

    
		timer_.expires_from_now(boost::posix_time::seconds(FILETRANSFER_TIMEOUT));
		timer_.async_wait(boost::bind(&connection_basic::handle_download_timeout, this,boost::asio::placeholders::error,"downloadbuffer"));
	}

}

 template <typename Handler>
 void async_upload_file(FILE* filepointer,const tstring& stLocalPath,__int64 filesize,Handler handler)
{
#ifdef _DEBUG
	log << _T("async_upload_file\n");
#endif
	fp=filepointer;
	lFileSize=filesize;
	stFilePath=stLocalPath;

	size_t upload_size;
	bytes_transfered_=0;
	bytes_read=0;

	if (fp!=NULL) 
	{
		upload_size=fread(data_,sizeof(unsigned char),BUFFER_SIZE,fp);
		bytes_read+=upload_size;
	}

	void (connection_basic::*f) (const boost::system::error_code &,const size_t& , boost::tuple<Handler>)
		=&connection_basic::handle_upload_buffer<Handler>;
	
	boost::asio::async_write(socket_,boost::asio::buffer(data_,upload_size),
		boost::bind(f,this,
		boost::asio::placeholders::error,
		upload_size,
		make_tuple(handler)));

    
	timer_.expires_from_now(boost::posix_time::seconds(FILETRANSFER_TIMEOUT));
	timer_.async_wait(boost::bind(&connection_basic::handle_timeout, this,boost::asio::placeholders::error,"upload"));

}

  template <typename Handler>
  void handle_upload_buffer(const boost::system::error_code& error,const size_t& bytes_transferred,boost::tuple<Handler> handler)
{
#ifdef _DEBUG
	log << _T("handle_upload_buffer\n");
#endif

	if (error) {
		boost::get<0>(handler)(error);
	//closefp();
		return;
	}

	bytes_transfered_+=bytes_transferred;

	if (bytes_transfered_==lFileSize) 
	{
		if (bytes_read!=lFileSize) 
		{
			boost::format fmt("Receive & Write Not Matched : %s");fmt % MCodeChanger::_CCN(stFilePath.c_str());
			process_file_error(fmt.str(),false);

			boost::system::error_code error(boost::asio::error::eof);
			io_service_.post(boost::bind(boost::get<0>(handler), error));
	//closefp();
			return;
		}

		closefp();

		boost::get<0>(handler)(error);
		return;
	}

	size_t upload_size=0;
	if (fp!=NULL) 
	{
		upload_size=fread(data_,sizeof(unsigned char),BUFFER_SIZE,fp);
		bytes_read+=upload_size;
	}
	if (upload_size==0) 
	{
		boost::system::error_code error(boost::asio::error::eof);
		io_service_.post(boost::bind(boost::get<0>(handler), error));
		//closefp();
		return;
	}

	void (connection_basic::*f) (const boost::system::error_code &, const size_t& , boost::tuple<Handler>)
		=&connection_basic::handle_upload_buffer<Handler>;

	boost::asio::async_write(socket_,boost::asio::buffer(data_,upload_size),
		boost::bind(f,this,
		boost::asio::placeholders::error,
		upload_size,
		handler));

	timer_.expires_from_now(boost::posix_time::seconds(FILETRANSFER_TIMEOUT));
	timer_.async_wait(boost::bind(&connection_basic::handle_timeout, this,boost::asio::placeholders::error,"uploadbuffer"));

}

	


  // Basic socket :: serialization


  template <typename T, typename Handler,typename Timeout>
  void async_write(const T& t,Handler handler,const Timeout & time_out_)
  {
    // Serialize the data first so we know how large it is.
    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);
    archive << t;
    outbound_data_ = archive_stream.str();
	async_write(handler,time_out_);
  }




  template <typename Handler,typename Timeout>
  void async_write(Handler handler,const Timeout & time_out_)
  {

    // Format the header.
    std::ostringstream header_stream;
    header_stream << std::setw(header_length)
      << std::hex << outbound_data_.size();
    if (!header_stream || header_stream.str().size() != header_length)
    {
      // Something went wrong, inform the caller.
      boost::system::error_code error(boost::asio::error::invalid_argument);
      io_service_.post(boost::bind(handler, error));
	//closefp();
	return;
    }
    outbound_header_ = header_stream.str();

#ifdef _DEBUG
	log<<_T("async_write ") << MCodeChanger::_CCL(outbound_data_) <<_T("\n");
#endif

    // Write the serialized data to the socket. We use "gather-write" to send
    // both the header and the data in a single write operation.
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back(boost::asio::buffer(outbound_header_));
    buffers.push_back(boost::asio::buffer(outbound_data_));

    boost::asio::async_write(socket_, buffers, handler);

//	boost::asio::deadline_timer timer(io_service_); 
//	timer.expires_at(boost::posix_time::second_clock::local_time()+boost::posix_time::seconds(30));
	timer_.expires_from_now(time_out_);
	timer_.async_wait(boost::bind(&connection_basic::handle_timeout, this,boost::asio::placeholders::error,"write"));

  }


  template <typename Handler,typename Timeout>
  void async_read(Handler handler,const Timeout & time_out_)
  {

	  free_InboundBuffer();

    // Issue a read operation to read exactly the number of bytes in a header.
    void (connection_basic::*f)(
        const boost::system::error_code&,
        boost::tuple<Handler>,const Timeout&)
      = &connection_basic::handle_read_header<Handler,Timeout>;

    boost::asio::async_read(socket_, boost::asio::buffer(inbound_header_),
        boost::bind(f,
          this, boost::asio::placeholders::error, 
          boost::make_tuple(handler),
		  time_out_));

	  
	  timer_.expires_from_now(time_out_);
	  timer_.async_wait(boost::bind(&connection_basic::handle_timeout, this,boost::asio::placeholders::error,"read1"));


  }

  template <typename Handler,typename Timeout>
  void handle_read_header(const boost::system::error_code& e,boost::tuple<Handler> handler,const Timeout & time_out_)
  {

    if (e)
    {
      boost::get<0>(handler)(e);
    }
    else
    {
		#ifdef _DEBUG
		log<<_T("async_read_header") << MCodeChanger::_CCL(inbound_header_) << _T("\n");
		#endif

		// Determine the length of the serialized data.
      std::istringstream is(std::string(inbound_header_, header_length));
      std::size_t inbound_data_size = 0;
      if (!(is >> std::hex >> inbound_data_size))
      {
        // Header doesn't seem to be valid. Inform the caller.
        boost::system::error_code error(boost::asio::error::invalid_argument);
        boost::get<0>(handler)(error);
	//closefp();
        return;
      }

      // Start an asynchronous call to receive the data.

	  inbound_data_=new char [inbound_data_size+1];
	  inbound_data_[inbound_data_size]=NULL;

	  void (connection_basic::*f)(
          const boost::system::error_code&,
          boost::tuple<Handler>)
        = &connection_basic::handle_read_data<Handler>;

	  boost::asio::async_read(socket_, boost::asio::buffer(inbound_data_,inbound_data_size),
        boost::bind(f, this,
		boost::asio::placeholders::error, 
		handler));

	  timer_.expires_from_now(time_out_);
	  timer_.async_wait(boost::bind(&connection_basic::handle_timeout, this,boost::asio::placeholders::error,"read2"));

    }


  }
  template <typename Handler>
  void handle_read_data(const boost::system::error_code& e,boost::tuple<Handler> handler)
  {
#ifdef _DEBUG
	  log<<_T("async_read") << MCodeChanger::_CCL(inbound_data_) << _T("\n");
#endif

     boost::get<0>(handler)(e);
  }
/*

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
  } */

};

typedef boost::shared_ptr<connection_basic> connection_basic_ptr;
#endif // SERIALIZATION_connection_basic_HPP
