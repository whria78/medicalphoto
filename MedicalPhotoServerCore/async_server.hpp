//
// async_server.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2007 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

//#include "connection_basic.h"
#include "server_connection.h"
//#include "async_connection_manager.hpp"
#include "basic_server.h"
//#include "../cximage/ximage.h"
//#include "../share/file.h"
#include "../share/cmycout.h"
//#include "../share/etc.h"
//#include "../share/netpath.h"
#include "../share/config.h"

class async_server
  : public basic_server<server_connection>
{
public:

	explicit async_server(CMyCout& l_,config& config_,async_connection_manager& m_);
/*
	void initiate();
	void start();
	void stop();
*/
protected:

	CMyCout& log_;
	config& config_;
//	netstorage netstorage_;

/*	server_connection_list server_connection_list_;
	int server_connection_id;

	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::acceptor acceptor_;
	server_connection_ptr new_server_connection_;
*/
protected:

///	void handle_accept(const boost::system::error_code& e);
//	void handle_stop();
};

