//
// log_server.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2007 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "basic_server.h"
#include "log_connection.h"
#include "../share/cmycout.h"
#include "../share/config.h"
#include "../client/whriaclient.h"

class log_server
  :public CMyCout,public basic_server<log_connection>
{
public:

	explicit log_server(int iLogPort);

	void BroadcastLog(const log_struct& log_struct_)
	{
		__int64 blank_=0;
		async_connection_manager_.ExecuteBlockingOrder(LOGSEND,log_struct_,blank_,blank_);
	}
	void WriteString(const tstring& str)
	{
		log_struct log_struct_;
		log_struct_.iFlag=CMyCout::iSetFlag;
		log_struct_.stDetail=MCodeChanger::_CCU(str);
		BroadcastLog(log_struct_);
		CMyCout::WriteString(str);
	}
	void Connect()
	{
		log_connection_.connect("localhost",config_.Get(LOG_PORT));
	}

protected:
	async_connection_manager async_connection_manager_;
	log_connection log_connection_;
	config config_;
	CMyCout log_;
//	CWhriaClient WhriaClient;
};

