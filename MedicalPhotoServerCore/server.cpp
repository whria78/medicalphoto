//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2007 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "stdafx.h"


//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2007 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "server.hpp"

server::server(config& c_,connection_manager& m_)
  : 
	connection_manager_(m_),
	endpoint_(boost::asio::ip::tcp::v4(), atoi(c_.Get(SERVER_PORT).c_str())),
	acceptor_(io_service_,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), atoi(c_.Get(SERVER_PORT).c_str()))),
	log(c_.log),
//	sql(c_.log),
	netstorage_(c_),
	config_(c_),
//	bStopBuildSQL(false),
	connection_id(0)
{
  // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
/*
	boost::asio::ip::tcp::resolver resolver(io_service_);
  boost::asio::ip::tcp::resolver::query query(address, port);
  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
  acceptor_.open(endpoint.protocol());
  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  acceptor_.bind(endpoint);
  acceptor_.listen();
  */
	_tcout << _T("Initiate Medieye Server\n");
	log << _T("Accept : Port( ") << MCodeChanger::_CCL(config_.Get(SERVER_PORT)) << _T(" )") << log.endl();
}

void server::initiate()
{
//	netstorage_.Close();
	try{
		netstorage_.Open();
	}
	catch (CppSQLite3Exception& e)
	{
		log << e.errorMessage() << log.endl();
	}
	catch (std::exception& e)
	{
		log << e.what() << log.endl();
	}
	log << _T("Initiate Server\n");

//	bStopBuildSQL=false;
/*
	if (bBuildThumbnailOnly)
		boost::thread BuildThread(boost::bind(&server::BuildThumb,this));
	else
		boost::thread BuildThread(boost::bind(&server::Build,this));
*/
}

/*void server::BuildThumbnail()
{
	boost::thread BuildThread(boost::bind(&server::BuildThumbThread,this));
}
*/


void server::handle_accept(const boost::system::error_code& e)
{
  if (!e)
  {
	  log << "accept : " << connection_id++ <<log.endl();
//	  connection_list_.push_back(new_connection_);

//	  acceptor_.local_endpoint();

   connection_manager_.start(new_connection_);
   
   new_connection_.reset(new connection(connection_id,io_service_, config_,connection_manager_));

    acceptor_.async_accept(new_connection_->socket(),
        boost::bind(&server::handle_accept, this,
          boost::asio::placeholders::error));
  }
}
void server::handle_stop()
{
  // The server is stopped by cancelling all outstanding asynchronous
  // operations. Once all operations have finished the io_service::run() call
  // will exit.
  acceptor_.close();
  connection_manager_.stop_all();
//  io_service_.stop();
}

void server::start()
{
//	log << _T("### server start ###") << log.endl();

	try
	{
		io_service_.reset();
		new_connection_.reset(new connection(connection_id,io_service_, config_,connection_manager_));

	//  acceptor_.open();
	  if (!acceptor_.is_open())
	  {
		  acceptor_.open(endpoint_.protocol());
		  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		  acceptor_.bind(endpoint_);
		  acceptor_.listen();
	  }

	  acceptor_.async_accept(new_connection_->socket(),
		  boost::bind(&server::handle_accept, this,
			boost::asio::placeholders::error));
/*
#ifdef _WIN32
	HWND m_hwnd=Utility::GetConsoleHwnd();
		HWND hwnd = ::FindWindow(_T("MedicalPhotoServer"), NULL);
		if (hwnd!=NULL)
		{
			COPYDATASTRUCT cds;
			cds.cbData=0;
			cds.dwData=WM_COPYDATA_SERVERSTART;
			SendMessage(hwnd,WM_COPYDATA,(WPARAM)m_hwnd,(LPARAM)&cds);
		}
#endif*/
	  io_service_.run();
	}
	catch (CppSQLite3Exception& e)
	{
		log << e.errorMessage() << log.endl();
	}
	catch (std::exception& e)
	{
		log << e.what() << log.endl();
	}
//	log << _T("### server end ###") << log.endl();
}

void server::stop()
{
	connection_manager_.stop_all();

	acceptor_.close();
	io_service_.stop();
	/*
#ifdef _WIN32
	HWND m_hwnd=Utility::GetConsoleHwnd();
		HWND hwnd = ::FindWindow(_T("MedicalPhotoServer"), NULL);
		if (hwnd!=NULL)
		{
			COPYDATASTRUCT cds;
			cds.dwData=WM_COPYDATA_SERVERSTOP;
			cds.cbData=0;
			SendMessage(hwnd,WM_COPYDATA,(WPARAM)m_hwnd,(LPARAM)&cds);
		}
#endif*/
}

