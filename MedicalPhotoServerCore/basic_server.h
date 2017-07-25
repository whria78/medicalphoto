//
// basic_server.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2007 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

#include "async_connection.h"
#include "async_connection_manager.hpp"

#include "../share/unicode.h"
#include "../share/error.h"
#include "../share/config.h"

template <class ConnectionType>
class basic_server
	: private boost::noncopyable
{
public:

	explicit basic_server(int iPort,CMyCout& l_,config& c_,async_connection_manager& m_)
	  : connection_manager_(m_)
		,endpoint_(boost::asio::ip::tcp::v4(),iPort)
		,acceptor_(io_service_,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), iPort))
		,connection_id(0)
		,log_(l_)
		,config_(c_)
	{
	}
	~basic_server()
	{
		stop();
	}

	void start()
	{
		accept();
		run();
		/*
		try
		{
			io_service_.reset();
			new_connection_.reset(new ConnectionType(connection_id,io_service_, config_,connection_manager_));

		  if (!acceptor_.is_open())
		  {
			  acceptor_.open(endpoint_.protocol());
			  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
			  acceptor_.bind(endpoint_);
			  acceptor_.listen();
		  }

		  acceptor_.async_accept(new_connection_->socket(),
			  boost::bind(&basic_server::handle_accept, this,
				boost::asio::placeholders::error));

		  io_service_.run();
		}
		catch (CppSQLite3Exception& e)
		{
			log_ << e.errorMessage() << log_.endl();
	//		err_.Add(SQL_ERROR,e.errorCode,e.errorMessage());
		}
		catch (std::exception& e)
		{
			log_ << e.what() << log_.endl();
	//		err_.Add(OTHER_ERROR,0,e.what());
		}
		*/
	}

	void accept()
	{
		try
		{
			new_connection_.reset(new ConnectionType(connection_id,io_service_, config_,connection_manager_));

		  if (!acceptor_.is_open())
		  {
			  acceptor_.open(endpoint_.protocol());
			  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
			  acceptor_.bind(endpoint_);
			  acceptor_.listen();
		  }

		  acceptor_.async_accept(new_connection_->socket(),
			  boost::bind(&basic_server::handle_accept, this,
				boost::asio::placeholders::error));
		}
		catch (CppSQLite3Exception& e)
		{
			log_ << e.errorMessage() << log_.endl();
		}
		catch (std::exception& e)
		{
			log_ << e.what() << log_.endl();
		}
	}
	void run()
	{
		try
		{
			io_service_.reset();
			io_service_.run();
		}
		catch (std::exception& e)
		{
			log_ << e.what() << log_.endl();
		}

	}
	void stop()
	{
		connection_manager_.stop_all();

		acceptor_.close();
		io_service_.stop();
	}
/*
	template <typename T1,typename T2,typename R>
	void ExecuteBlockingOrder(int order_code_,T1& t1,T2& t2,R& result) 
	{connection_manager_.ExecuteBlockingOrder(order_code_,t1,t2,result);}
*/
	boost::asio::ip::tcp::endpoint endpoint_;

protected:

	async_connection_manager& connection_manager_;

	boost::shared_ptr<ConnectionType> new_connection_;
	std::vector<boost::shared_ptr<ConnectionType>> log_connection_list_;
	int connection_id;

	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::acceptor acceptor_;

protected:

	CMyCout& log_;
	config& config_;

	void handle_accept(const boost::system::error_code& e)
	{
		if (!e)
		{
			connection_manager_.start(new_connection_);
			connection_id++;
			new_connection_.reset(new ConnectionType(connection_id,io_service_, config_,connection_manager_));

			acceptor_.async_accept(new_connection_->socket(),
			boost::bind(&basic_server::handle_accept, this,
			  boost::asio::placeholders::error));
		}
	}
	void handle_stop()
	{
	  acceptor_.close();
	  connection_manager_.stop_all();
	}
};

