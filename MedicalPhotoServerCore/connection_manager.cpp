//
// connection_manager.cpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2007 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "stdafx.h"

#include "connection_manager.hpp"
#include <algorithm>
#include <boost/bind.hpp>


void connection_manager::start(connection_ptr c)
{
  connections_.push_back(c);
  c->start();
}

void connection_manager::stop(connection_ptr c)
{
	int iIndex=-1;
	for (unsigned int i=0;i<connections_.size();i++)
	{
		if (connections_[i]==c)
		{iIndex=i;break;}
	}
	if (iIndex==-1) return;

	connections_.erase(connections_.begin()+iIndex);
	c->stop();
}

void connection_manager::stop_all()
{
//  std::for_each(connections_.begin(), connections_.end(),
//      boost::bind(&connection::stop, _1));
	for (unsigned int i=0;i<connections_.size();i++)
	{
		connections_[i]->stop();
	}
//  connections_.clear();
}

