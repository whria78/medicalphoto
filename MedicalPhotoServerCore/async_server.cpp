#include "stdafx.h"
#include "async_server.hpp"
/*
async_server::async_server(config& c_,async_connection_manager& m_)
  : 
	server_connection_manager_(m_),
	endpoint_(boost::asio::ip::tcp::v4(), atoi(c_.Get(SERVER_PORT).c_str())),
	acceptor_(io_service_,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), atoi(c_.Get(SERVER_PORT).c_str()))),
	log(c_.log),
	netstorage_(c_),
	config_(c_),
	server_connection_id(0)
{
	_tcout << _T("Initiate Medieye Server\n");
	log << _T("Accept : Port( ") << MCodeChanger::_CCL(config_.Get(SERVER_PORT)) << _T(" )") << log.endl();
}
	*/
async_server::async_server(CMyCout& l_,config& c_,async_connection_manager& m_)
  : basic_server<server_connection>(c_.GetInt(SERVER_PORT),l_,c_,m_)
  ,log_(l_)
	,config_(c_)
{
	log_ << _T("[Startup] Open port ") << MCodeChanger::_CCL(config_.Get(SERVER_PORT)) << _T("\n");
//	WriteString(_T("Initiate Log Server\n"));
}


/*
void async_server::initiate()
{
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

}


void async_server::handle_accept(const boost::system::error_code& e)
{
	if (!e)
	{
		log << "accept : " << server_connection_id++ <<log.endl();

		server_connection_manager_.start(new_server_connection_);

		new_server_connection_.reset(new server_connection(server_connection_id,io_service_, config_,server_connection_manager_));

		acceptor_.async_accept(new_server_connection_->socket(),
		boost::bind(&async_server::handle_accept, this,
		  boost::asio::placeholders::error));
	}
}
void async_server::handle_stop()
{
  acceptor_.close();
  server_connection_manager_.stop_all();
//  io_service_.stop();
}

void async_server::start()
{
//	log << _T("### async_server start ###") << log.endl();
	try
	{
		io_service_.reset();
		new_server_connection_.reset(new server_connection(server_connection_id,io_service_, config_,server_connection_manager_));

	  if (!acceptor_.is_open())
	  {
		  acceptor_.open(endpoint_.protocol());
		  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		  acceptor_.bind(endpoint_);
		  acceptor_.listen();
	  }

	  acceptor_.async_accept(new_server_connection_->socket(),
		  boost::bind(&async_server::handle_accept, this,
			boost::asio::placeholders::error));

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
//	log << _T("### async_server end ###") << log.endl();
}

void async_server::stop()
{
	server_connection_manager_.stop_all();

	acceptor_.close();
	io_service_.stop();
}

*/