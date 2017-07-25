#include "stdafx.h"
#include "basic_server.h"
/*
template <class ConnectionType>
basic_server<ConnectionType>::basic_server(int iPort,config& c_,async_connection_manager& m_)
  : connection_manager_(m_)
	,endpoint_(boost::asio::ip::tcp::v4(),iPort)
	,acceptor_(io_service_,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), iPort))
	,connection_id(0)
	,log_(c_.log)
	,config_(c_)
{
}
/*
template <class ConnectionType>
void basic_server<ConnectionType>::handle_accept(const boost::system::error_code& e)
{
}
template <class ConnectionType>
void basic_server<ConnectionType>::handle_stop()
{
}
/*
template <class ConnectionType>
void basic_server<ConnectionType>::start()
{
}
*/

