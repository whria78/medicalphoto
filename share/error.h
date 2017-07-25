#pragma once
#include "../boost.h"
#include <boost/serialization/vector.hpp>
#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>
#include <cstdlib>
#include <string>
#include "unicode.h"

enum error_code
{
	NO_PRIV,
	NOT_LOGON,
	SOC_ERROR,
	DECODING_DATA,
	SQL_ERROR,
	FILE_ERROR,
	TIMEOUT,
	PASSWORD_MISMATCH,
	ID_NOTEXIST,
	FILE_WRITE_OPEN,
	FILE_READ_OPEN,
	FILE_DELETE,
	PATH_RENAME,
	FOLDER_CREATE,
	FOLDER_DELETE,
	INVALID_PARAM,
	FILE_DUPLICATE,
	FILE_NOT_EXIST,
	FILE_LIST,
	SIZE_ERROR,
	INVALID_COMMAND,
	NO_UPDATE,
	UPDATE_FAILURE,
	FOLDER_ALREADY_EXIST,
	INVALID_VOLUME,
	OTHER_ERROR,
	TOO_MANY_RESULTS
};

const std::string error_list[]=
{
	"No Privileage",
	"You are not Log in",
	"Socket Error",
	"Fail to decoding stream data",
	"SQL Error",
	"File I/O Error",
	"Server/Client does not response",
	"Invalid Password",
	"Invalid ID",
	"Fail to open file(write)",
	"Fail to open file(read)",
	"Fail to delete file",
	"Fail to rename path",
	"Fail to create folder",
	"Fail to delete folder",
	"Invalid params",
	"File Duplicated",
	"File Not Exist",
	"Fail to list file",
	"FileSize Error",
	"Invalid Command",
	"No Update",
	"Update Failure",
	"Folder already exists",
	"Invalid volume",
	"Other Error",
	"Too many results"
};

class error_message
{
public:
	error_message()
	{
		clear();
	}

	void clear()
	{
		bError=false;
#ifdef _DEBUG
		iErrCode=rand();
#endif
#ifndef _DEBUG
		iErrCode=-1;
#endif
		iErrCodeDetail=-1;
		stErrMessage.clear();
	}

	void Add(size_t errcode, size_t errdetail, int iCode)
	{
		boost::format fmt("%s");
		fmt % iCode;
		Add(errcode,errdetail,fmt.str());
	}
	void Add(size_t errcode, size_t errdetail, const std::string& errmessage)
	{

		bError=true;
		stErrMessage=errmessage;
		iErrCode=errcode;
		iErrCodeDetail=errdetail;
		ptime=boost::posix_time::second_clock::local_time();
	}
	void Add(size_t errcode) {Add(errcode,0,error_list[errcode]);}

	bool CheckError() {return bError;}
	std::string to_string()
	{
		if (iErrCode==-1) return "";
		return error_list[iErrCode];
	}

	size_t iErrCode;
	size_t iErrCodeDetail;
	std::string stErrMessage;
	boost::posix_time::ptime ptime;

private:
	friend class boost::serialization::access;
	bool bError;

  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
	  ar & bError;
	  ar & iErrCode;
	  ar & iErrCodeDetail;
	  ar & stErrMessage;
	  ar & ptime;
  }
};
//BOOST_CLASS_TRACKING(error_message, boost::serialization::track_never)
