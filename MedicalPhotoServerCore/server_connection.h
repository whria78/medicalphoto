#pragma once

#include "async_connection.h"
#include "../share/watcher.h"

class server_connection
	:
	public async_connection
{
public:
	server_connection(int async_connection_id_
		,boost::asio::io_service& io_service
		,config& c_
		,async_connection_manager& manager)
		: async_connection(async_connection_id_,io_service,c_,manager)
	,config_(c_)
	,bLogin(false)
//	,bUpdateDone(false)
	,sql(c_.log)
	{
		_tpath prog_path=bfs::initial_path<_tpath>();
		prog_path /= MCodeChanger::_CCL(c_.Get(DATA_FILENAME));	prog_path = Utility::refinepath(prog_path);
		sql.Open(MCodeChanger::_CCU(prog_path.c_str()));

		if (!sql.Check())
		{
			if (!sql.Check())
			{
				log << _T("Invalid Data Table\n");
				sql.close();
			}
		}
		int iVersion;
		if (sql.CheckLowVersion(&iVersion))
		{
			log << _T("Old version of Database.\n");
			if (UpgradeTable(iVersion))
				return;
			else
			{
				sql.close();
				return;
			}
		}
	}

	~server_connection()
	{
//		SendExit();
	}
	bool UpgradeTable(int iOldVersion)
	{
		if (iOldVersion==1)
		{
			log << _T("[UPGRADE] Add SQLLog DB\n");
			sql.execDML(sqllog::create_sql_table());

			return sql.UpdateVersionInfo();
		}
		else
		{
			log << _T("Unknown version : ") << iOldVersion << _T("\n");
			return false;
		}
	}

	void SendExit()
	{
		__int64 blank_=0;
		async_connection::AsyncExecuteOrder(CLIENTSTOP,blank_,blank_,blank_);
	}

	std::string GetUserID() {return CurrentUser.stUserID;}

//	void start() {async_connection::start();}
//	void stop() {async_connection::stop();}
protected:
	SQL_DB sql;
	config& config_;
	net_watcher net_watcher_;

	bool bLogin;
	user CurrentUser;
	std::string Transfer_Format(const std::string& str) {return Utility::Transfer_Format(str);}
	void Transfer_Format(std::vector<std::string>& str) 
	{
		for (unsigned int i=0;i<str.size();i++)
		{
			str[i]=Utility::Transfer_Format(str[i]);
		}
	}

	// Execute

	void ExecuteOrder(boost::archive::text_iarchive& archive_in
		,boost::archive::text_oarchive& archive_out);

	void PostExecuteOrder();
//	void PostExecuteOrder(boost::archive::text_iarchive& archive_in
//		,boost::archive::text_oarchive& archive_out);

	void process_error(const error_message& err) {async_connection::process_error(err);}
	void process_socket_error(const boost::system::error_code& e);
};

typedef boost::shared_ptr<server_connection> server_connection_ptr;
typedef std::vector<server_connection_ptr> server_connection_list;
