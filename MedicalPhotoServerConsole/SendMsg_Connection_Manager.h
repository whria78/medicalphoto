#pragma once

#include "../MedicalPhotoServerCore/async_connection_manager.hpp"
#include "../MedicalPhotoServerCore/server_connection.h"
#include "../share/config.h"
#include "../share/datatype_basic.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class SendMsg_Connection_Manager
	: public async_connection_manager
{
public:
	void SetHWND(HWND hwnd)
	{
		m_hwnd=hwnd;
	}

	void GetList(std::vector<connection_info>& connection_info_list)
	{
		for (unsigned int i=0;i<async_connections_.size();i++)
		{
			connection_info connection_info_;
			async_connection_ptr c=async_connections_[i];


			connection_info_.iConnectionID=c->GetConnectionID();
			connection_info_.stIPAddress=c->socket().remote_endpoint().address().to_string();

			server_connection* p_server_connection;
			p_server_connection=(server_connection*)(c.get());
			connection_info_.stUserID=p_server_connection->GetUserID();

			connection_info_list.push_back(connection_info_);
		}
	}

	void start(async_connection_ptr c)
	{
#ifdef _WIN32
		HWND hwnd = ::FindWindow(_T("MedicalPhotoServer"), NULL);
		if (hwnd!=NULL)
		{
			std::ostringstream archive_stream_out;
			boost::archive::text_oarchive archive_out(archive_stream_out);

			int iConnectionID=c->GetConnectionID();
			server_connection* p_server_connection;
			p_server_connection=(server_connection*)(c.get());

			archive_out 
				<< iConnectionID
				<< p_server_connection->GetUserID()
				<< c->socket().remote_endpoint().address().to_string();
			
			std::string steamout_=archive_stream_out.str();
			COPYDATASTRUCT cds;
			cds.dwData=WM_COPYDATA_ADDUSER;
			cds.cbData=steamout_.length();
			cds.lpData=(void*)steamout_.c_str();
			
			SendMessage(hwnd,WM_COPYDATA,(WPARAM)m_hwnd,(LPARAM)&cds);
		}
#endif
		async_connection_manager::start(c);
	}
	void stop(async_connection_ptr c)
	{
#ifdef _WIN32
		HWND hwnd = ::FindWindow(_T("MedicalPhotoServer"), NULL);
		if (hwnd!=NULL)
		{
			std::ostringstream archive_stream_out;
			boost::archive::text_oarchive archive_out(archive_stream_out);

			int iConnectionID=c->GetConnectionID();
			archive_out 
				<< iConnectionID;
			
			std::string steamout_=archive_stream_out.str();
			COPYDATASTRUCT cds;
			cds.dwData=WM_COPYDATA_DELUSER;
			cds.cbData=steamout_.length();
			cds.lpData=(void*)steamout_.c_str();
			
			SendMessage(hwnd,WM_COPYDATA,(WPARAM)m_hwnd,(LPARAM)&cds);
		}
#endif
		async_connection_manager::stop(c);
	}
private:
	HWND m_hwnd;
};