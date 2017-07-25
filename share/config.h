#pragma once

#include "../boost.h"
#include <boost/serialization/vector.hpp>
#include <string>
#include <boost/algorithm/string.hpp>
//#include <vector>
//#include <boost/bind.hpp>
//#include <cstdlib>

#include "exif.h"

#include "cmycout.h"
#include "file.h"
#include "codechange.h"
#include "unicode.h"
#include "../boost.h"
#include <boost/tuple/tuple.hpp>
#include "etc.h"

namespace bfs=boost::filesystem; 

#define MEDIEYE_PORT "9999"
#define APPLICATIONNAME _T("MedicalPhoto.exe")

#define CLIENT_APPLICATIONNAME "MedicalPhoto.exe"
#define SERVER_APPLICATIONNAME "MedicalPhotoServer.exe"
#define SERVER_CONSOLE_APPLICATIONNAME "console.exe"
#define ASSIST_APPLICATIONNAME "Assist.exe"

#define MEDICAL_FIELD "derma.dat"

#define SERVER_CONFIG_FILENAME _T("s_config.txt")
#define CLIENT_CONFIG_FILENAME _T("c_config.txt")

#ifdef _DEBUG
#define VERSION_CONFIG_FILENAME "../version.dat"
#endif
#ifndef _DEBUG
#define VERSION_CONFIG_FILENAME "./version.dat"
#endif

#define MAX_CONFIG 100

typedef boost::tuple<tstring,std::string,std::string> element_tuple;

class config_common
{
public:
	bool load(const TCHAR* stFilename);
	void save(const TCHAR* stFilename);
	void clear();

	config_common(CMyCout& l)
		:
	log(l)
	{
		prog_path=boost::filesystem::initial_path<_tpath>();
		iSize=0;
	}
/*	bool operator ==( const config_common& config_common_ ) const
	{
		for (int i=0;i<MAX_CONFIG;i++)
		{
			if (strcmp(Get(i).c_str(),config_common_.Get(i).c_str())!=0)
				return false;
		}
		return true;
	}
	bool operator !=( const config_common& config_common_ ) const
	{
		for (int i=0;i<MAX_CONFIG;i++)
		{
			if (strcmp(Get(i).c_str(),config_common_.Get(i).c_str())!=0)
				return true;
		}
		return false;
	}
*/

	void RefinePath(int iIndex);

	CMyCout& log;

	int GetSize();
	void Insert(int iIndex,const tstring& text,const std::string& default_value);
	std::string Get(int iIndex);
	std::string Get(int iIndex,int iSubIndex);
	int GetInt(int iIndex);
	std::string GetDefault(int iIndex);
	void LoadDefault(int iIndex);
	void Set(int iIndex,const int value);
	void Set(int iIndex,const bool value);
	void Set(int iIndex,const std::string& value);
	tstring GetText(int iIndex);
	void Add(int iIndex,const int value);
	void Add(int iIndex,const std::string& value);

	bool Compare(int iIndex,int value);
	bool Compare(int iIndex,const std::string& value);
	void SplitParams(int iIndex,std::vector<std::string>& param_list)
	{
		Utility::SplitParams(Get(iIndex),param_list);
	}

private:
	element_tuple data_[MAX_CONFIG];
	int iSize;

protected:
	_tpath prog_path;

	std::string to_string(int interger);
	bool Exist(const tstring& command,const tstring& param_name);
	void SetParam(std::string& param,std::string value);
	void Update(const tstring& command, const tstring& param_name,const std::string& param_data,FILE* fp);
	void Merge(const std::vector<tstring>& command_list,const tstring& param_name,const std::string& param_data,FILE* fp);
	void Insert(const tstring& param_name,const int param_data,FILE* fp);
	void Insert(const tstring& param_name,const std::string& param_data,FILE* fp);
	tstring join(const tstring& command,const std::string& param);
	tstring join(const tstring& command,const int& param);

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		for (int i=0;i<MAX_CONFIG;i++)
		{
			ar & data_[i].get<2>();
		}
	}
};
typedef std::vector<std::string> param_list;

enum version_checker_element{
VERSION_FILE_VERSION,
VERSION_FILE,
CLIENT_VERSION,
CLIENT_APP_NAME,
SERVER_VERSION,
SERVER_APP_NAME,
CONSOLESERVER_VERSION,
CONSOLESERVER_APP_NAME,
ICD10_FILE_VERSION,
ICD10_FILE_NAME,
DATA_FILE_VERSION,
DATA_FILE_NAME,
SERVICE_FILE_VERSION,
SERVICE_FILE_NAME,
CONFIG_FILE_VERSION,
CONFIG_FILE_NAME
};

class version_checker : public config_common
{
public:
	version_checker(CMyCout& l) 
		: config_common(l)
	{
		Insert(VERSION_FILE,_T("VERSION_FILE"),VERSION_CONFIG_FILENAME);
		Insert(VERSION_FILE_VERSION,_T("VERSION_FILE_VERSION"),"1.0.0.0");
		Insert(CLIENT_APP_NAME,_T("CLIENT_APP_NAME"),"MedicalPhoto.exe");
		Insert(CLIENT_VERSION,_T("CLIENT_VERSION"),"1.0.0.0");
		Insert(SERVER_APP_NAME,_T("SERVER_APP_NAME"),"MedicalPhotoServer.exe");
		Insert(SERVER_VERSION,_T("SERVER_VERSION"),"1.0.0.0");
		Insert(CONSOLESERVER_APP_NAME,_T("CONSOLESERVER_APP_NAME"),"console.exe");
		Insert(CONSOLESERVER_VERSION,_T("CONSOLESERVER_VERSION"),"1.0.0.0");
		Insert(ICD10_FILE_NAME,_T("ICD10_FILE_NAME"),"./diagnosis/icd10.dat,./diagnosis/icd10_small.dat,./diagnosis/derma.dat");
		Insert(ICD10_FILE_VERSION,_T("ICD10_FILE_VERSION"),"1.0.0.0");
		Insert(DATA_FILE_NAME,_T("DATA_FILE_NAME"),std::string(""));
		Insert(DATA_FILE_VERSION,_T("DATA_FILE_VERSION"),"1.0.0.0");
		Insert(SERVICE_FILE_NAME,_T("SERVICE_FILE_NAME"),"MedicalPhotoService.exe");
		Insert(SERVICE_FILE_VERSION,_T("SERVICE_FILE_VERSION"),"1.0.0.0");
		Insert(CONFIG_FILE_NAME,_T("CONFIG_FILE_NAME"),"Config.exe");
		Insert(CONFIG_FILE_VERSION,_T("CONFIG_FILE_VERSION"),"1.0.0.0");
	}

	void load();
	void save()
	{
		prog_path /= MCodeChanger::_CCL(Get(VERSION_FILE)); prog_path = Utility::refinepath(prog_path);
		config_common::save(prog_path.c_str());
	}

	void check_data_exist(int iIndex);
	void increase_version(int iIndex);
	std::string get_increase_version(int iIndex);
	
	static tstring GetTemp(const std::string& stAppName);
	bool NeedUpdate(int iTarget,const std::string& stVersion); // 0=client / 1=server / 2=data
};


enum config_element
{
	ADMIN_PASS,
	DATA_PATH,
	THUMB_PATH,
	FAVORATE_PATH,
	DIRECTORY_WATCH_ON,
	DATA_FILENAME,
	THUMB_HEIGHT,
	THUMB_WIDTH,
	MULTIUSER_SUPPORT,
	CONNECT_MEDIEYENET,
	BACKUP_INTERVAL,
	BACKUP_MAX_NUM_FILE,
	SUPERADMIN_ID,
	SERVER_PORT,
//	LOG_PORT,
	THREADS_NUMBER,
	HOSPITAL_ID_LENGTH,
	AUTO_START,
	MINIMIZE,
	HOSPITAL_NAME,
	FILE_EXTENSIONS,
	BACKUP_PATH,
	MAX_SEARCH_RESULT_NUMBER,
	MAX_REPORT_RESULT_NUMBER,
	STARTUP_CHECK_DB,
	SMART_RETRIEVE_IDNAME_SEPARATOR,

//	STARTUP_CHECK_SCHEDULE,
	SAVE_ROTATEIMAGE,

	SQLBACKUP_DURATION,
	BACKUP_DATE,
	BACKUP_TIME,
	SCHEDULE_BUILD_DATE,
	SCHEDULE_BUILD_TIME,
	SCHEDULE_CHECK_DATE,
	SCHEDULE_CHECK_TIME,
// FTP
	FTP_SERVER_ON,
	FTP_SERVER_ADMINID,
	FTP_SERVER_ADMINPASS,
	FTP_SERVER_PORT,
	FTP_ANONYMOUS_ON,

//
	UPLOAD_WATCH_PATH,

//	NTSERVICE,
	DATA_ROOT_PATH,
	TMP_PATH,

	NTSERVICE_NAME,
	IDLE_CONNECTION_INTERVAL
//	APP_TYPE
};

class config : public config_common
{
public:
	version_checker version_;

	void load()
	{
		config_common::load(SERVER_CONFIG_FILENAME);
		version_.load();
//		fileinfo::Open(Get(DATA_PATH));
		RefinePath(DATA_PATH);
		RefinePath(FAVORATE_PATH);
		RefinePath(THUMB_PATH);
		RefinePath(BACKUP_PATH);
		RefinePath(DATA_ROOT_PATH);
		RefinePath(TMP_PATH);
	}
	void save()
	{
		prog_path /= SERVER_CONFIG_FILENAME; prog_path = Utility::refinepath(prog_path);
		config_common::save(prog_path.c_str());
	}

	config(CMyCout& l)
		:config_common(l)
		,version_(l)
	{
		Insert(SERVER_PORT,_T("SERVER_PORT"),"9999");
		Insert(IDLE_CONNECTION_INTERVAL,_T("IDLE_CONNECTION_INTERVAL"),"10");

//		Insert(LOG_PORT,_T("LOG_PORT"),"9998");
		Insert(ADMIN_PASS,_T("ADMIN_PASS"),"");
		Insert(DATA_PATH,_T("DATA_PATH"),std::string(""));

		_tpath path_dataroot= Utility::refinepath(MFile::GetInitialPath() / _T("data"));
		Insert(DATA_ROOT_PATH,_T("DATA_ROOT_PATH"),MCodeChanger::_CCU(path_dataroot.c_str()));

		_tpath path2= Utility::refinepath(path_dataroot / _T("thumb"));
		Insert(THUMB_PATH,_T("THUMB_PATH"),MCodeChanger::_CCU(path2.c_str()));
		_tpath path_favorate= Utility::refinepath(path_dataroot / _T("favorate"));
		Insert(FAVORATE_PATH,_T("FAVORATE_PATH"),MCodeChanger::_CCU(path_favorate.c_str()));
		_tpath path_tmp= Utility::refinepath(path_dataroot / _T("tmp"));
		Insert(TMP_PATH,_T("TMP_PATH"),MCodeChanger::_CCU(path_tmp.c_str()));

		Insert(DATA_FILENAME,_T("DATA_FILENAME"),"database.dat");

		Insert(SMART_RETRIEVE_IDNAME_SEPARATOR,_T("SMART_RETRIEVE_IDNAME_SEPARATOR")," _");

		Insert(FTP_SERVER_ON,_T("FTP_SERVER_ON"),"0");
		Insert(FTP_ANONYMOUS_ON,_T("FTP_ANONYMOUS_ON"),"0");
		Insert(FTP_SERVER_PORT,_T("FTP_SERVER_PORT"),"21");
		Insert(FTP_SERVER_ADMINID,_T("FTP_SERVER_ADMINID"),"medicalphoto");
		Insert(FTP_SERVER_ADMINPASS,_T("FTP_SERVER_ADMINPASS"),"medicalphoto");

		Insert(THUMB_HEIGHT,_T("THUMB_HEIGHT"),"200");
		Insert(THUMB_WIDTH,_T("THUMB_WIDTH"),"300");
		Insert(MULTIUSER_SUPPORT,_T("MULTIUSER_SUPPORT"),"0");
//		Insert(CONNECT_MEDIEYENET,_T("CONNECT_MEDIEYENET"),"0");
//		Insert(BACKUP_MAX_NUM_FILE,_T("BACKUP_MAX_NUM_FILE"),"30");
		Insert(SUPERADMIN_ID,_T("SUPERADMIN_ID"),"superadmin");
//		Insert(THREADS_NUMBER,_T("THREADS_NUMBER"),"1");
		Insert(HOSPITAL_ID_LENGTH,_T("HOSPITAL_ID_LENGTH"),"4");
		Insert(AUTO_START,_T("AUTO_START"),"1");
		Insert(MINIMIZE,_T("MINIMIZE"),"1");

		Insert(SAVE_ROTATEIMAGE,_T("SAVE_ROTATEIMAGE"),"1");
		Insert(DIRECTORY_WATCH_ON,_T("DIRECTORY_WATCH_ON"),"1");

		Insert(UPLOAD_WATCH_PATH,_T("UPLOAD_WATCH_PATH"),"");

		Insert(HOSPITAL_NAME,_T("HOSPITAL_NAME"),std::string(""));
		Insert(FILE_EXTENSIONS,_T("FILE_EXTENSIONS"),".jpg, .jpeg");
		Insert(MAX_SEARCH_RESULT_NUMBER,_T("MAX_SEARCH_RESULT_NUMBER"),"1000");
		Insert(MAX_REPORT_RESULT_NUMBER,_T("MAX_REPORT_RESULT_NUMBER"),"100000");

		_tpath path_backup= Utility::refinepath(MFile::GetInitialPath() / _T("backup"));
		Insert(BACKUP_PATH,_T("BACKUP_PATH"),MCodeChanger::_CCU(path_backup.c_str()));
		Insert(SQLBACKUP_DURATION,_T("SQLBACKUP_DURATION"),"14");

		Insert(STARTUP_CHECK_DB,_T("STARTUP_CHECK_DB"),"0");
//		Insert(STARTUP_CHECK_SCHEDULE,_T("STARTUP_CHECK_SCHEDULE"),"1");
		Insert(BACKUP_DATE,_T("BACKUP_DATE"),"-1");
		Insert(BACKUP_TIME,_T("BACKUP_TIME"),"0");
		Insert(SCHEDULE_BUILD_DATE,_T("SCHEDULE_BUILD_DATE"),"-1");
		Insert(SCHEDULE_BUILD_TIME,_T("SCHEDULE_BUILD_TIME"),"1");
		Insert(SCHEDULE_CHECK_DATE,_T("SCHEDULE_CHECK_DATE"),"0");
		Insert(SCHEDULE_CHECK_TIME,_T("SCHEDULE_CHECK_TIME"),"3");
//		Insert(NTSERVICE,_T("NTSERVICE"),"1");
		Insert(NTSERVICE_NAME,_T("NTSERVICE_NAME"),"MedicalPhoto");
//		Insert(APP_TYPE,_T("APP_TYPE"),"1"); // 0 : stand-alone 1 : networked
	}
	void Set(int iIndex,const std::string& value)
	{
		config_common::Set(iIndex,value);
		if (iIndex == DATA_PATH) RefinePath(DATA_PATH);
		if (iIndex == FAVORATE_PATH) RefinePath(FAVORATE_PATH);
		if (iIndex == THUMB_PATH) RefinePath(THUMB_PATH);
		if (iIndex == DATA_ROOT_PATH) RefinePath(DATA_ROOT_PATH);
		if (iIndex == TMP_PATH) RefinePath(TMP_PATH);
	}
	void Set(int iIndex,const int value)
	{
		config_common::Set(iIndex,value);
	}
	void Set(int iIndex,const bool value)
	{
		config_common::Set(iIndex,value);
	}
	
	private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		config_common::serialize(ar,version);
		ar & version_;
	}


};

enum client_config_element{
CLIENT_PORT,
LAST_HOST_ADDRESS,
LAST_USER_ID,
LAST_USER_PASSWD,
SEARCH_FILENAME,
SEARCH_ID,
SEARCH_NAME,
SEARCH_PATH,
SEARCH_DIAGNOSIS,
SEARCH_COMMENT,
SEARCH_ICD10,
//LOAD_ICD10,
LOAD_DXCODE_LIST,
LOAD_CUSTOMDX,
VIEW_MODE,
SUBMIT_AUTOCHANGE_FILENAME,
//MULTI_CLIENT_SUPPORT,
//UPLOADEX_DATE_FORMAT,
CREATE_FOLDER_FORMAT,
DISPLAY_FOLDER_FORMAT,
IDLE_HIDE_SCREEN,
USE_CUSTOM_TEMPLATE,
RUN_ASSIST
};

class client_config : public config_common
{
public:
	client_config(CMyCout& l) 
		: server_config(l)
		, config_common(l)
	{
		Insert(CLIENT_PORT,_T("CLIENT_PORT"),MEDIEYE_PORT);
		Insert(LAST_HOST_ADDRESS,_T("LAST_HOST_ADDRESS"),"localhost");
		Insert(LAST_USER_ID,_T("LAST_USER_ID"),"superadmin");
//		Insert(LAST_USER_PASSWD,_T("LAST_USER_PASSWD"),"0000");
//		Insert(SEARCH_FILENAME,_T("SEARCH_FILENAME"),"1");
		Insert(SEARCH_ID,_T("SEARCH_ID"),"1");
		Insert(SEARCH_NAME,_T("SEARCH_NAME"),"1");
		Insert(SEARCH_PATH,_T("SEARCH_PATH"),"1");
		Insert(SEARCH_DIAGNOSIS,_T("SEARCH_DIAGNOSIS"),"1");
		Insert(SEARCH_COMMENT,_T("SEARCH_COMMENT"),"1");
		Insert(SEARCH_ICD10,_T("SEARCH_ICD10"),"1");
		Insert(LOAD_DXCODE_LIST,_T("LOAD_DXCODE_LIST"),"icd10.dat");
//		Insert(LOAD_ICD10,_T("LOAD_ICD10"),"1");
//		Insert(LOAD_CUSTOMDX,_T("LOAD_CUSTOMDX"),MEDICAL_FIELD);
		Insert(VIEW_MODE,_T("VIEW_MODE"),"1");
		Insert(SUBMIT_AUTOCHANGE_FILENAME,_T("SUBMIT_AUTOCHANGE_FILENAME"),"1");
//		Insert(MULTI_CLIENT_SUPPORT,_T("MULTI_CLIENT_SUPPORT"),"1");
		Insert(CREATE_FOLDER_FORMAT,_T("CREATE_FOLDER_FORMAT"),"2");
		Insert(DISPLAY_FOLDER_FORMAT,_T("DISPLAY_FOLDER_FORMAT"),"0");
		Insert(IDLE_HIDE_SCREEN,_T("IDLE_HIDE_SCREEN"),"10");

		Insert(USE_CUSTOM_TEMPLATE,_T("USE_CUSTOM_TEMPLATE"),"0");
		Insert(RUN_ASSIST, _T("RUN_ASSIST"), "0");
	}

	void save()
	{
		prog_path /= CLIENT_CONFIG_FILENAME; prog_path = Utility::refinepath(prog_path);
		config_common::save(prog_path.c_str());
	}
	void load()
	{
		config_common::load(CLIENT_CONFIG_FILENAME);
	}

	config server_config;

private:

};

