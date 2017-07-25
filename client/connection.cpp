#include "stdafx.h"

#include "connection.h"

void client_connection::connect(const std::string& host,const std::string& service)
  {
    // Resolve the host name into an IP address.
    boost::asio::ip::tcp::resolver resolver(io_service_);
    boost::asio::ip::tcp::resolver::query query(host, service);
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator =
      resolver.resolve(query);

	while (endpoint_iterator!=boost::asio::ip::tcp::resolver::iterator())
	{
		boost::optional<boost::system::error_code> timer_result;
		boost::optional<boost::system::error_code> socket_result;

		boost::asio::ip::tcp::endpoint endpoint=*endpoint_iterator;
		
		connect(endpoint,timer_result,socket_result);
		endpoint_iterator++;
		
		if (!(*socket_result)) 
			return;
		else
		{
			if (timer_result)
			{
				socket_.close();
			  throw ConnectionEx(TIMEOUT);
			}
			else
			{
				socket_.close();
				throw ConnectionEx(SOC_ERROR,socket_result->value(),socket_result->message());
			}
		}

		socket_.close();
	}
  }

void client_connection::connect(boost::asio::ip::tcp::endpoint endpoint,
						 boost::optional<boost::system::error_code>& timer_result,
						 boost::optional<boost::system::error_code>& socket_result)
{
    boost::asio::deadline_timer timer(io_service_);
    timer.expires_from_now(boost::posix_time::seconds(ACCEPT_TIMEOUT)); 
	timer.async_wait(boost::bind(&client_connection::set_stream_result,this,
		&timer_result, boost::asio::placeholders::error)); 

	  // Start an asynchronous connect operation.
	  socket_.async_connect(endpoint,
		boost::bind(&client_connection::set_result, this,
		&socket_result,boost::asio::placeholders::error));

	  io_service_.reset();
    while (io_service_.run_one())
    { 
      if (socket_result) 
        timer.cancel(); 
      else if (timer_result)
	  {
		  socket_.close();
		  throw ConnectionEx(TIMEOUT);
	  }
    } 
}

void client_connection::scan(const std::string& host,const std::string& service)
  {
    // Resolve the host name into an IP address.
    boost::asio::ip::tcp::resolver resolver(io_service_);
    boost::asio::ip::tcp::resolver::query query(host, service);
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator =
      resolver.resolve(query);

	while (endpoint_iterator!=boost::asio::ip::tcp::resolver::iterator())
	{
		boost::optional<boost::system::error_code> timer_result;
		boost::optional<boost::system::error_code> socket_result;

		boost::asio::ip::tcp::endpoint endpoint=*endpoint_iterator;
		
		connect(endpoint,timer_result,socket_result);
		endpoint_iterator++;
		
		if (!(*socket_result)) 
			return;
		else
		{
			if (timer_result)
			{
				socket_.close();
			  throw ConnectionEx(TIMEOUT);
			}
			else
			{
				socket_.close();
				throw ConnectionEx(SOC_ERROR,socket_result->value(),socket_result->message());
			}
		}

		socket_.close();
	}
  }

void client_connection::scan(boost::asio::ip::tcp::endpoint endpoint,
						 boost::optional<boost::system::error_code>& timer_result,
						 boost::optional<boost::system::error_code>& socket_result)
{
    boost::asio::deadline_timer timer(io_service_); 
	timer.expires_from_now(boost::posix_time::milliseconds(SCAN_TIMEOUT)); 
	timer.async_wait(boost::bind(&client_connection::set_stream_result,this,
		&timer_result, boost::asio::placeholders::error)); 

	  // Start an asynchronous connect operation.
	  socket_.async_connect(endpoint,
		boost::bind(&client_connection::set_result, this,
		&socket_result,boost::asio::placeholders::error));

    io_service_.reset(); 
    while (io_service_.run_one()) 
    { 
      if (socket_result) 
        timer.cancel(); 
      else if (timer_result)
	  {
		  socket_.close();
		  throw ConnectionEx(TIMEOUT);
	  }
    } 
}
void client_connection::async_read_header()
  {
	free_InboundBuffer();

	boost::optional<boost::system::error_code> timer_result; 
    boost::asio::deadline_timer timer(io_service_); 
    timer.expires_from_now(boost::posix_time::seconds(STREAMING_TIMEOUT)); 
	timer.async_wait(boost::bind(&client_connection::set_stream_result,this,
		&timer_result, boost::asio::placeholders::error)); 

	boost::optional<boost::system::error_code> socket_result; 

	boost::asio::async_read(socket_, boost::asio::buffer(inbound_header_),
		boost::bind(&client_connection::set_stream_result, this,
		&socket_result,boost::asio::placeholders::error));

	io_service_.reset();
    while (io_service_.run_one())
    { 
      if (socket_result) 
	  {
        timer.cancel(); 
		#ifdef _DEBUG
	log << _T("async_read_header") << MCodeChanger::_CCW(inbound_header_) << _T("\n");
		#endif
	  }
      else if (timer_result)
	  {
		  throw ConnectionEx(TIMEOUT);
	  }
    } 
	if (*socket_result)
	{
		throw ConnectionEx(SOC_ERROR,socket_result->value(),socket_result->message());
	}
  }

  void client_connection::async_read_data()
  {
	boost::optional<boost::system::error_code> timer_result; 
    boost::asio::deadline_timer timer(io_service_);
    timer.expires_from_now(boost::posix_time::seconds(STREAMING_TIMEOUT)); 
	timer.async_wait(boost::bind(&client_connection::set_stream_result,this,
		&timer_result, boost::asio::placeholders::error)); 

	boost::optional<boost::system::error_code> socket_result; 

	// Determine the length of the serialized data.
    std::istringstream is(std::string(inbound_header_, header_length));
    std::size_t inbound_data_size = 0;
    if (!(is >> std::hex >> inbound_data_size))
    {
		// Header doesn't seem to be valid. Inform the caller.
		throw ConnectionEx(DECODING_DATA);
	}

	inbound_data_=new char [inbound_data_size+1];
	inbound_data_[inbound_data_size]=NULL;

	boost::asio::async_read(socket_, boost::asio::buffer(inbound_data_,inbound_data_size),
		boost::bind(&client_connection::set_stream_result, this,
		&socket_result,boost::asio::placeholders::error));

	io_service_.reset();
    while (io_service_.run_one())
    { 
      if (socket_result) 
	  {
        timer.cancel(); 
		#ifdef _DEBUG
		std::wstring dumy=MCodeChanger::_CCW(inbound_data_);dumy.length();
		log << _T("async_read_data") << dumy << _T("\n\n");
		#endif
	  }
      else if (timer_result)
	  {
		  throw ConnectionEx(TIMEOUT);
	  }
    } 
	if (*socket_result)
	{
		throw ConnectionEx(SOC_ERROR,socket_result->value(),socket_result->message());
	}
  }


  void client_connection::async_write()
  {
	boost::optional<boost::system::error_code> timer_result; 
    boost::asio::deadline_timer timer(io_service_);
    timer.expires_from_now(boost::posix_time::seconds(STREAMING_TIMEOUT)); 
	timer.async_wait(boost::bind(&client_connection::set_stream_result,this,
		&timer_result, boost::asio::placeholders::error)); 

	boost::optional<boost::system::error_code> socket_result; 

	  // Format the header.
    std::ostringstream header_stream;
    header_stream << std::setw(header_length)
      << std::hex << outbound_data_.size();
    if (!header_stream || header_stream.str().size() != header_length)
    {
      // Something went wrong, inform the caller.
		throw ConnectionEx(DECODING_DATA);
    }
    outbound_header_ = header_stream.str();

    // Write the serialized data to the socket. We use "gather-write" to send
    // both the header and the data in a single write operation.
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back(boost::asio::buffer(outbound_header_));
    buffers.push_back(boost::asio::buffer(outbound_data_));

	#ifdef _DEBUG
	log << _T("async_write") << MCodeChanger::_CCW(outbound_data_) << _T("\n");
	#endif

    boost::asio::async_write(socket_, buffers,
		boost::bind(&client_connection::set_stream_result, this,
		&socket_result,boost::asio::placeholders::error));

	io_service_.reset();
    while (io_service_.run_one())
    { 
      if (socket_result) 
        timer.cancel(); 
      else if (timer_result)
	  {
		  throw ConnectionEx(TIMEOUT);
	  }
    } 
	if (*socket_result)
	{
		throw ConnectionEx(SOC_ERROR,socket_result->value(),socket_result->message());
	}
  }
