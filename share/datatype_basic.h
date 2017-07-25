#pragma once

#include "../boost.h"
#include "error.h"
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>
#include <boost/date_time/gregorian/greg_serialize.hpp>
#include <boost/format.hpp>
//#include "../SqliteStatic/CppSQLite3.h"
#include "../sqlite/CppSQLite3.h"
#include "unicode.h"
#include <functional>

#define WM_COPYDATA_LOG 0
#define WM_COPYDATA_ADDUSER 1
#define WM_COPYDATA_DELUSER 2
#define WM_COPYDATA_SERVERSTOP 3
#define WM_COPYDATA_SERVERSTART 4
#define WM_COPYDATA_REQUESTINFO 5
#define WM_COPYDATA_CONNECTEDLIST 6
#define WM_REQUESTINFO (WM_USER+1) 

class sql_helper
{
public:
static std::string sql_escape(std::string str)
{
	boost::algorithm::replace_all(str,"'","''");
	return str;
}
};

class connection_info
{
public:
	int iConnectionID;
	std::string stUserID,stIPAddress;

  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & iConnectionID;
    ar & stUserID;
    ar & stIPAddress;
  }
};

enum command_code
{
	// No Priv
	UPDATE=0,
	// Never change UPDATE=0
	LOGIN,

	PASSWD_CHANGE,
	ADD_FAVORATE,
	DELETE_FAVORATE,

	GETUSERDX,
	SETUSERDX,
	GETDX,

	// Write Command //

	UPLOADFILE,
	DELETEFILE,
	RENAMEFILE,

	CREATEFOLDER,
	DELETEFOLDER,
	RENAMEFOLDER,

	SETPATHINFO,

	// Read Command //

	DOWNLOADFILE,
	THUMB_DOWNLOADFILE,
	THUMB_UPLOADFILE,

	GETVOLLIST,
	GETFOLDERLIST,
	GETPATHINFO,
	SEARCH,
	SEARCH_WITH_PATH,

	GETCOMMENT,
	SETCOMMENT,

	//
	GETUSERINFO,
	SETUSERINFO,

	// SuperUser Command //

	ADDUSER,
	SERVERSTOP,
	SERVERSTART,
	RELOADCONFIG,
	SETCONFIG,
	RELOADLIST,
	SERVERQUIT,
	CHECKSQLINFO,
	CHECKTHUMBNAIL,
	SEARCHCOMMENT,
	SEARCHFILE_EXT,
	SEARCH_WITH_PATH_EXACT,
	SEARCH_EXACT,
	GET_VERSIONFILE, // should be 40 for AUTOUPDATE
	CREATEFOLDER_AUTO,
	SEARCH_WITH_DATE,
	SEARCH_QUERY,

	LOGSEND,
	CLIENTSTOP,
	IMAGE_ROTATE,
	UPDATEPREVUSERDX,

	IDLESIGNAL
};

const std::string command_list[]=
{
	"UPDATE",
	"LOGIN",
	"PASSWD_CHANGE",
	"ADD_FAVORATE",
	"DELETE_FAVORATE",

	"GETUSERDX",
	"SETUSERDX",
	"GETDX",

	"UPLOADFILE",
	"DELETEFILE",
	"RENAMEFILE",

	"CREATEFOLDER",
	"DELETEFOLDER",
	"RENAMEFOLDER",

	"SETPATHINFO",

	"DOWNLOADFILE",
	"THUMB_DOWNLOADFILE",
	"THUMB_UPLOADFILE",

	"GETVOLLIST",
	"GETFOLDERLIST",
	"GETPATHINFO",
	"SEARCH",
	"SEARCH_WITH_PATH",

	"GETCOMMENT",
	"SETCOMMENT",

	"GETUSERINFO",
	"SETUSERINFO",

	"ADDUSER",
	"SERVERSTOP",
	"SERVERSTART",
	"RELOADCONFIG",
	"SETCONFIG",
	"RELOADLIST",
	"SERVERQUIT",
	"CHECKSQLINFO",
	"CHECKTHUMBNAIL",
	"SEARCHCOMMENT",
	"SEARCHFILE_EXT",
	"SEARCH_WITH_PATH_EXACT",
	"SEARCH_EXACT",
	"GET_VERSIONFILE",
	"CREATEFOLDER_AUTO",
	"SEARCH_WITH_DATE",
	"SEARCH_QUERY",

	"LOGSEND",
	"CLIENTSTOP",
	"IMAGE_ROTATE",
	"UPDATEPREVUSERDX",

	"IDLESIGNAL"
};
typedef std::vector<std::string> basic_params;
class command
{
public:
	command()
	{
		clear();
	}

	void clear()
	{
		order_code=-1;
//		params.clear();
	}
	static std::string code_to_string(int iOrderCode)
	{
		if (iOrderCode==-1) return "";
		return command_list[iOrderCode];
	}
	__int32 order_code;
//	basic_params params;

private:
 friend class boost::serialization::access;

  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & order_code;
//	ar & params;
  }
};

class log_struct{
public:
	std::string stDetail;
	int iFlag;
	boost::posix_time::ptime Time;
	log_struct()
		: Time(boost::posix_time::second_clock::local_time())
	{
	}
private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
	ar & stDetail;
	ar & iFlag;
	ar & Time;
	}
};

class update_struct{
public:
	int iAppCode;
	int iSubCode;
private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
	ar & iAppCode;
	ar & iSubCode;
	}
};


class diagnosis
{
public:
	std::string stDiagnosis;
	std::string stICD10;

	diagnosis() {clear();}
	void clear()
	{
		stDiagnosis.clear();
		stICD10.clear();
	}

	template <typename Type>
	diagnosis(Type& t,int* index)
	{
		stDiagnosis=t.fieldValue(*index);(*index)++;
		stICD10=t.fieldValue(*index);(*index)++;
//		stDiagnosis=t.fieldValue("diagnosis");
//		stICD10=t.fieldValue("icd10");
	}
	bool isempty()
	{
		if (strcmp(stDiagnosis.c_str(),"")==0 &&
			strcmp(stICD10.c_str(),"")==0)
			return true;
		else
			return false;
	}

	std::string sql_set_values(const std::string& stFormat=",") const
	{
		std::string stQuery="%%s='%%s'%sicd10='%%s'";
		boost::format pre_fmt(stQuery);
		pre_fmt % stFormat;

//		boost::format fmt("%s='%s',icd10='%s'");
		boost::format fmt(pre_fmt.str());
		fmt % get_primary()
			% sql_helper::sql_escape(stDiagnosis) 
			% sql_helper::sql_escape(stICD10);
		return fmt.str();
	}
	std::string sql_values() const 
	{
		boost::format fmt("'%s','%s'");
		fmt % sql_helper::sql_escape(stDiagnosis) % sql_helper::sql_escape(stICD10);
		return fmt.str();
	}
	bool operator == (const diagnosis &wf) const
	{
		if (stDiagnosis==wf.stDiagnosis
			&& stICD10==wf.stICD10)
			return true;
		else
			return false;
	}

	diagnosis operator = (const diagnosis &wf)
	{
		stDiagnosis=wf.stDiagnosis;
		stICD10=wf.stICD10;
		return *this;
	}
	bool CompareObj(const diagnosis &a,const diagnosis &b)
	{
		return true;
//		return strcmp(a.stDiagnosis.c_str(),b.stDiagnosis.c_str()) <0;
	}

	std::string get_unique() {return stDiagnosis;}
	static char* get_tablename() {return "`userdx`";}
	static char* get_primary() {return "diagnosis";}

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
	ar & stDiagnosis;
	ar & stICD10;
	}
};
typedef std::vector<diagnosis> dx_list;

typedef diagnosis userdx;
typedef std::vector<userdx> userdx_list;
typedef std::vector<tstring> localdx_list;
typedef std::vector<std::string> uni_dx_list;

class sort_diagnosis{
public:
	bool operator() (const diagnosis &a,const diagnosis &b) const
	{
		std::string aa=a.stDiagnosis;
		std::string bb=b.stDiagnosis;
		boost::algorithm::to_lower(aa);
		boost::algorithm::to_lower(bb);
		return aa<bb;
	}
};
