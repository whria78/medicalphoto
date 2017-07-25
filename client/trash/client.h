#ifndef MEDIEYE_CLIENT_H
#define MEDIEYE_CLIENT_H

#define ACCEPT_TIMEOUT 3

class client
{
public:
  /// Constructor starts the asynchronous connect operation.
  client(boost::asio::io_service& io_service,
      const std::string& host, const std::string& service)
    : connection_(io_service)
  {
    // Resolve the host name into an IP address.
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(host, service);
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator =
      resolver.resolve(query);
    boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;

    // Start an asynchronous connect operation.
    connection_.socket().async_connect(endpoint,
        boost::bind(&client::handle_connect, this,
          boost::asio::placeholders::error, ++endpoint_iterator));

	timer_.expires_from_now(boost::posix_time::seconds(ACCEPT_TIMEOUT));
	timer_.async_wait(boost::bind(&client::handle_close, this));
  }

  void handle_close() {connection_.socket().close();}

  /// Handle completion of a connect operation.
  void handle_connect(const boost::system::error_code& e,
      boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
  {
    if (!e)
    {
      // Successfully established connection. Start operation to read the list
      // of stocks. The connection::async_read() function will automatically
      // decode the data that is read from the underlying socket.
      connection_.async_read(stocks_,
          boost::bind(&client::handle_read, this,
            boost::asio::placeholders::error));
    }
    else if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator())
    {
      // Try the next endpoint.
      connection_.socket().close();
      boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
      connection_.socket().async_connect(endpoint,
          boost::bind(&client::handle_connect, this,
            boost::asio::placeholders::error, ++endpoint_iterator));
    }
    else
    {
      // An error occurred. Log it and return. Since we are not starting a new
      // operation the io_service will run out of work to do and the client will
      // exit.
      std::cerr << e.message() << std::endl;
    }
  }

  /// Handle completion of a read operation.
  void handle_read(const boost::system::error_code& e)
  {
  _tcout<<"result";

	  if (!e)
    {
      // Print out the data that was received.
	  message t_me;
	  t_me.code="order";
		connection_.async_write(t_me,
          boost::bind(&client::handle_write, this,
            boost::asio::placeholders::error));

	}
    else
    {
      // An error occurred.
      std::cerr << e.message() << std::endl;
    }

    // Since we are not starting a new operation the io_service will run out of
    // work to do and the client will exit.
  }

  void handle_write(const boost::system::error_code& e)
  {
	  _tcout<<"order";
		connection_.async_read(t_re,
          boost::bind(&client::handle_read, this,
            boost::asio::placeholders::error));
  }

private:
  /// The connection to the server.
  connection connection_;
};

#endif