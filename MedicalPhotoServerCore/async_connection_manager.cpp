#include "stdafx.h"

#include "async_connection_manager.hpp"


void async_connection_manager::start(async_connection_ptr c)
{
	async_connections_.push_back(c);
	c->start();
}
void async_connection_manager::stop(async_connection_ptr c)
{
	int iIndex=-1;
	for (unsigned int i=0;i<async_connections_.size();i++)
	{
		if (async_connections_[i]==c)
		{iIndex=i;break;}
	}
	if (iIndex==-1) return;

	async_connections_.erase(async_connections_.begin()+iIndex);
	c->stop();
}

void async_connection_manager::stop_all()
{
//  std::for_each(async_connections_.begin(), async_connections_.end(),
//      boost::bind(&async_connection::stop, _1));
	for (unsigned int i=0;i<async_connections_.size();i++)
	{
		async_connections_[i]->stop();
	}
//  async_connections_.clear();
}

