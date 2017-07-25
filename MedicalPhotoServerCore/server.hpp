//
// server.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2007 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef HTTP_SERVER3_SERVER_HPP
#define HTTP_SERVER3_SERVER_HPP

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

#include "connection_basic.h"
#include "connection.h"
#include "connection_manager.hpp"

#include "../cximage/ximage.h"
#include "../share/file.h"
#include "../share/unicode.h"
#include "../share/cmycout.h"
#include "../share/etc.h"
#include "../share/netpath.h"

class server
  : private boost::noncopyable
{
public:

	explicit server(config& config_,connection_manager& m_);
	~server()
	{
		stop();
	}

	void initiate();
	void start();
	void stop();

	boost::asio::ip::tcp::endpoint endpoint_;

protected:

	CMyCout& log;
	netstorage netstorage_;

	config& config_;
	int connection_id;
	connection_list connection_list_;

	void handle_accept(const boost::system::error_code& e);
	void handle_stop();

	connection_manager& connection_manager_;
	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::acceptor acceptor_;
	connection_ptr new_connection_;
};

#endif // HTTP_SERVER3_SERVER_HPP
