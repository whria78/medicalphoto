#include "stdafx.h"
#include "basic_client.h"

boost::mutex basic_client::mutex_;

void basic_client::connect(const std::string& host,const std::string& port)
{
	boost::mutex::scoped_lock lock(mutex_);
	client_connection::connect(host,port);
}
