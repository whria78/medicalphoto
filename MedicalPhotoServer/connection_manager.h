#pragma once

#include "afxcmn.h"
#include "afxwin.h"
#include "../MedicalPhotoServerCore/async_connection_manager.hpp"
#include "../MedicalPhotoServerCore/server_connection.h"
#include "../share/config.h"
#include <boost/asio.hpp>
#include "../share_MFC/resource.h"

typedef struct _UserInfoStruct
{
public:
	tstring stIPAddress;
	tstring stUserID;
} UserInfoStruct;

class CConnection_Manager : public async_connection_manager
{
public:
	CConnection_Manager(CListCtrl& m,config& c)
		:	m_list(m)
		,config_(c)
	{
	}

	void InitiateCtrl();

	void start(server_connection_ptr c);
	void stop(server_connection_ptr c);
	void stop_all();

	void Add(int connection_id,const tstring& ipaddress,const tstring& stUserID);
	void Del(int connection_id);
	void DeleteAll();

private:
	CImageList m_Img;
	CListCtrl& m_list;
	std::vector<int> connection_id_list;
	config& config_;
};