#pragma once

#include "../share/unicode.h"
#include <boost/noncopyable.hpp>
#include <algorithm>
#include <boost/bind.hpp>
#include "async_connection.h"

class async_connection_manager
  : private boost::noncopyable
{
public:

	virtual void start(async_connection_ptr c);
	virtual void stop(async_connection_ptr c);
	virtual void stop_all();
//	virtual void add(async_connection_ptr c);

/*	template <typename T1,typename T2,typename R>
	void ExecuteBlockingOrder(int order_code_,T1& t1,T2& t2,R& result)
	{
		for (unsigned int i=0;i<async_connections_.size();i++)
		{
			async_connections_[i]->ExecuteBlockingOrder(order_code_,t1,t2,result);
		}
	}
*/
protected:
	std::vector<async_connection_ptr> async_connections_;
};

