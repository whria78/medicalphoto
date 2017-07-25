#pragma once

#include "../boost.h"
#include "error.h"
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>
#include <boost/date_time/gregorian/greg_serialize.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include "datatype_basic.h"
//#include "../SqliteStatic/CppSQLite3.h"
#include "../sqlite/CppSQLite3.h"
#include "codechange.h"
#include "unicode.h"

//class MFile;

class user
{
public:
	std::string stName;
	std::string stUserID;
	std::string stHospitalID;
	std::string stPasswd;
	std::string iGrade;

	std::string stLocale;

	user() {clear();}
	void clear()
	{
		stName.clear();
		stUserID.clear();
		stHospitalID.clear();
		stPasswd.clear();
		iGrade.clear();
		stLocale.clear();
	}

	template <typename Type>
	user(Type& t,int* index)
	{
		stName=t.fieldValue(*index);(*index)++;
		stUserID=t.fieldValue(*index);(*index)++;
		stHospitalID=t.fieldValue(*index);(*index)++;
		stPasswd=t.fieldValue(*index);(*index)++;
		iGrade=t.fieldValue(*index);(*index)++;
		stLocale=t.fieldValue(*index);(*index)++;
	}

	std::string sql_set_values(const std::string& stFormat=",") const 
	{
		std::string stQuery="name='%%s'%suserid='%%s'%shospitalid='%%s'%spasswd='%%s'%sgrade='%%s'%slocale='%%s'";
		boost::format pre_fmt(stQuery);
		pre_fmt % stFormat
			% stFormat
			% stFormat
			% stFormat
			% stFormat;

		return get_sql(pre_fmt.str());
//		return get_sql("name='%s',userid='%s',hospitalid='%s',passwd='%s',grade='%s',locale='%s'");
	}
	std::string sql_values() const {return get_sql("'%s','%s','%s','%s','%s','%s'");}
	std::string get_sql (const std::string& stFormat) const 
	{
		boost::format fmt(stFormat);
		fmt % sql_helper::sql_escape(stName) 
			% sql_helper::sql_escape(stUserID) 
			% sql_helper::sql_escape(stHospitalID)
			% sql_helper::sql_escape(stPasswd)
			% sql_helper::sql_escape(iGrade)
			% sql_helper::sql_escape(stLocale);
		return fmt.str();
	}

	static char* create_sql_table()
	{
		return "create table `user`(name TEXT,userid TEXT UNIQUE,passwd TEXT,hospitalid TEXT,grade TEXT,locale TEXT);create index index_user ON `user`(userid);";
	}

	static char* get_tablename() {return "`user`";}
	static char* get_primary() {return "userid";}

	user operator = (const user &wf)
	{
		stName=wf.stName;
		stUserID=wf.stUserID;
		stHospitalID=wf.stHospitalID;
		stPasswd=wf.stPasswd;
		iGrade=wf.iGrade;
		stLocale=wf.stLocale;
		return *this;
	}

	bool operator == (const user &wf) const
	{
		if (strcmp(stName.c_str(),wf.stName.c_str())==0 &&
		strcmp(stUserID.c_str(),wf.stUserID.c_str())==0 &&
		strcmp(stHospitalID.c_str(),wf.stHospitalID.c_str())==0 &&
		strcmp(stPasswd.c_str(),wf.stPasswd.c_str())==0 &&
		strcmp(iGrade.c_str(),wf.iGrade.c_str())==0 &&
		strcmp(stLocale.c_str(),wf.stLocale.c_str())==0)
			return true;
		else
			return false;
	}

private:
	friend class boost::serialization::access;

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
	ar & stName;
	ar & stUserID;
	ar & stHospitalID;
	ar & stPasswd;
	ar & iGrade;
	ar & stLocale;
	}
};
typedef std::vector<user> user_list;
typedef std::vector<std::string> id_list;
/*
class priv
{
public:
	bool bUserRead;
	bool bUserWrite;
	bool bGroupRead;
	bool bGroupWrite;
	bool bOtherRead;
	bool bOtherWrite;

	bool CheckWritePriv(user User,std::string stPath);
	bool CheckReadPriv(user User,std::string stPath);

	std::string get_sql(const std::string& stFormat) const
	{
		boost::format fmt(stFormat);
		fmt % to_string();
		return fmt.str();
	}
	std::string sql_set_values(const std::string& stFormat=",") const 
	{
		return get_sql("priv='%s'");
	} 
	std::string sql_values() const {return get_sql("'%s'");}

	std::string to_string() const
	{
		char strPriv[]="      \0";
		if (bUserRead) strPriv[0]='r';
		if (bUserWrite) {strPriv[1]='w';strPriv[0]='r';}
		if (bGroupRead) strPriv[2]='r';
		if (bGroupWrite) {strPriv[3]='w';strPriv[2]='r';}
		if (bOtherRead) strPriv[4]='r';
		if (bOtherWrite) {strPriv[5]='w';strPriv[4]='r';}

		return strPriv;
	}
	bool from_string(const std::string& stPriv)
	{
		if (stPriv.length()<6) return false;
		if (stPriv[0]=='r') bUserRead=true; else bUserRead=false; 
		if (stPriv[1]=='w') bUserWrite=true; else bUserWrite=false; 
		if (stPriv[2]=='r') bGroupRead=true; else bGroupRead=false;
		if (stPriv[3]=='w') bGroupWrite=true; else bGroupWrite=false;
		if (stPriv[4]=='r') bOtherRead=true; else bOtherRead=false;
		if (stPriv[5]=='w') bOtherWrite=true; else bOtherWrite=false;
		return true;
	}

	template <typename Type>
	priv(Type& t,int* index)
	{
		from_string(t.fieldValue(*index));(*index)++;
	}
	priv()
	{
		clear();
	}

	priv operator = (const priv &wf)
	{
		bUserRead=wf.bUserRead;
		bUserWrite=wf.bUserWrite;
		bGroupRead=wf.bGroupRead;
		bGroupWrite=wf.bGroupWrite;
		bOtherRead=wf.bOtherRead;
		bOtherWrite=wf.bOtherWrite;
		return *this;
	}

	void clear()
	{
		bUserRead=true;
		bUserWrite=true;
		bGroupRead=true;
		bGroupWrite=true;
		bOtherRead=false;
		bOtherWrite=false; 
	}

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
	ar & bUserRead;
	ar & bUserWrite;
	ar & bGroupRead;
	ar & bGroupWrite;
	ar & bOtherRead;
	ar & bOtherWrite;
	}
};
*/

class priv
{
public:
	// 1: Read  2: Write  3: Read&Write

	int iUserPriv;
	int iGroupPriv;
	int iOtherPriv;

	bool CheckWritePriv(user User,std::string stPath);
	bool CheckReadPriv(user User,std::string stPath);


	std::string sql_set_values(const std::string& stFormat=",") const
	{
		std::string stQuery="userpriv='%%s'%sgrouppriv='%%s'%sotherpriv='%%s'";
		boost::format pre_fmt(stQuery);
		pre_fmt 
			% stFormat
			% stFormat;

		boost::format fmt(pre_fmt.str());
		fmt % iUserPriv
			% iGroupPriv
			% iOtherPriv;
		return fmt.str();
	}
	std::string sql_values() const 
	{
		boost::format fmt("'%s','%s','%s'");
		fmt % iUserPriv
			% iGroupPriv
			% iOtherPriv;
		return fmt.str();
	}

	template <typename Type>
	priv(Type& t,int* index)
	{
		iUserPriv=t.getIntField(*index);(*index)++;
		iGroupPriv=t.getIntField(*index);(*index)++;
		iOtherPriv=t.getIntField(*index);(*index)++;
	}
	priv()
	{
		clear();
	}

	priv operator = (const priv &wf)
	{
		iUserPriv=wf.iUserPriv;
		iGroupPriv=wf.iGroupPriv;
		iOtherPriv=wf.iOtherPriv;
		return *this;
	}

	void clear()
	{
		iUserPriv=3;
		iGroupPriv=3;
		iOtherPriv=0;
	}

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
	ar & iUserPriv;
	ar & iGroupPriv;
	ar & iOtherPriv;
	}
};

class owner
{
public:
	std::string stUserID;
	std::string stGroupID;
	priv Priv;

	owner() {clear();}
	owner(const std::string& user)
		: stUserID(user)
		,stGroupID(user)
	{
	}
	void clear()
	{
		stUserID.clear();
		stGroupID.clear();
		Priv.clear();
	}


	template <typename Type>
	owner(Type& t,int* index)
	{
		stUserID=t.fieldValue(*index);(*index)++;
		stGroupID=t.fieldValue(*index);(*index)++;
		Priv=priv(t,index);
//		(*index)++;
	}

	std::string sql_set_values(const std::string& stFormat=",") const
	{
		std::string stQuery="userid='%%s'%sgroupid='%%s'%s%%s";
		boost::format pre_fmt(stQuery);
		pre_fmt % stFormat
			% stFormat;

		boost::format fmt(pre_fmt.str());
//		boost::format fmt("userid='%s',groupid='%s',%s");
		fmt % sql_helper::sql_escape(stUserID)
			% sql_helper::sql_escape(stGroupID)
			% Priv.sql_set_values(stFormat);
		return fmt.str();
	}
	std::string sql_values() const 
	{
		boost::format fmt("'%s','%s',%s");
		fmt % sql_helper::sql_escape(stUserID)
			% sql_helper::sql_escape(stGroupID)
			% Priv.sql_values();
		return fmt.str();
	}

	owner operator = (const owner &wf)
	{
		stUserID=wf.stUserID;
		stGroupID=wf.stGroupID;
		Priv=wf.Priv;
		return *this;
	}
	bool operator == (const owner &wf) const
	{
		if (strcmp(stUserID.c_str(),wf.stUserID.c_str())==0 &&
		strcmp(stGroupID.c_str(),wf.stGroupID.c_str())==0)
			return true;
		else
			return false;
	}

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
	ar & stUserID;
	ar & stGroupID;
	ar & Priv;
	}
};

class hospital
{
public:
	std::string stHospitalID;
	std::string stHospitalName;

	hospital() {clear();}
	void clear()
	{
		stHospitalID.clear();
		stHospitalName.clear();
	}

	template <typename Type>
	hospital(Type& t,int* index)
	{
		stHospitalID=t.fieldValue(*index);(*index)++;
		stHospitalName=t.fieldValue(*index);(*index)++;
	}

	std::string sql_set_values(const std::string& stFormat=",") const 
	{
		std::string stQuery="hospitalid='%%s'%shospitalname='%%s'";
		boost::format pre_fmt(stQuery);
		pre_fmt % stFormat;

		boost::format fmt(pre_fmt.str());
//		boost::format fmt("hospitalid='%s',hospitalname='%s'");
		fmt % sql_helper::sql_escape(stHospitalID)
			% sql_helper::sql_escape(stHospitalName);
		return fmt.str();
	}
	std::string sql_values() const 
	{
		boost::format fmt("'%s','%s'");
		fmt % sql_helper::sql_escape(stHospitalID)
			% sql_helper::sql_escape(stHospitalName);
		return fmt.str();
	}
	static char* create_sql_table()
	{
		return "create table `hospitalinfo`(hospitalid TEXT UNIQUE,hospitalname TEXT);create index index_hospitalinfo ON `hospitalinfo`(hospitalid);";
	}
	static char* get_tablename() {return "`hospitalinfo`";}
	static char* get_primary() {return "hospitalid";}


	hospital operator = (const hospital &wf)
	{
		stHospitalID=wf.stHospitalID;
		stHospitalName=wf.stHospitalName;
		return *this;
	}

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
	ar & stHospitalID;
	ar & stHospitalName;
	}
};

class grade
{
public:
	std::string iGrade;
	std::string stTitle;

	grade() {clear();}
	void clear()
	{
		iGrade.clear();
		stTitle.clear();
	}


	template <typename Type>
	grade(Type& t,int* index)
	{
		iGrade=t.fieldValue(*index);(*index)++;
		stTitle=t.fieldValue(*index);(*index)++;
	}

	std::string sql_set_values(const std::string& stFormat=",") const 
	{
		std::string stQuery="grade='%%s'%stitle='%%s'";
		boost::format pre_fmt(stQuery);
		pre_fmt % stFormat;

		boost::format fmt(pre_fmt.str());
//		boost::format fmt("grade='%s',title='%s'");
		fmt % sql_helper::sql_escape(iGrade)
			% sql_helper::sql_escape(stTitle);
		return fmt.str();
	}
	std::string sql_values() const 
	{
		boost::format fmt("'%s','%s'");
		fmt % sql_helper::sql_escape(iGrade)
			% sql_helper::sql_escape(stTitle);
		return fmt.str();
	}
	static char* create_sql_table()
	{
		return "create table `grade`(grade TEXT ,title TEXT);";
	}
	static char* get_tablename() {return "`grade`";}

	grade operator = (const grade &wf)
	{
		iGrade=wf.iGrade;
		stTitle=wf.stTitle;
		return *this;
	}

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
	ar & iGrade;
	ar & stTitle;
	}
};

class group
{
public:
	std::string stGroupID;
	std::string stGroupName;

	group() {clear();}
	void clear()
	{
		stGroupID.clear();
		stGroupName.clear();
	}

	template <typename Type>
	group(Type& t,int* index)
	{
		stGroupID=t.fieldValue(*index);(*index)++;
		stGroupName=t.fieldValue(*index);(*index)++;
	}

	std::string sql_set_values(const std::string& stFormat=",") const 
	{
		std::string stQuery="groupid='%%s'%sgroupname='%%s'";
		boost::format pre_fmt(stQuery);
		pre_fmt % stFormat;

		boost::format fmt(pre_fmt.str());
//		boost::format fmt("groupid='%s',groupname='%s'");
		fmt % sql_helper::sql_escape(stGroupID)
			% sql_helper::sql_escape(stGroupName);
		return fmt.str();
	}
	std::string sql_values() const 
	{
		boost::format fmt("'%s','%s'");
		fmt % sql_helper::sql_escape(stGroupID)
			% sql_helper::sql_escape(stGroupName);
		return fmt.str();
	}
	static char* create_sql_table()
	{
		return "create table `group`(groupid TEXT UNIQUE,groupname TEXT);create index index_group ON `group`(groupid);";
	}
	static char* get_tablename() {return "`group`";}
	static char* get_primary() {return "groupid";}

	group operator = (const group &wf)
	{
		stGroupID=wf.stGroupID;
		stGroupName=wf.stGroupName;
		return *this;
	}

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
	ar & stGroupID;
	ar & stGroupName;
	}
};

class groupmember
{
public:
	std::string stUserID;
	std::string stGroupID;

	groupmember() {clear();}
	void clear()
	{
		stUserID.clear();
		stGroupID.clear();
	}

	template <typename Type>
	groupmember(Type& t,int* index)
	{
		stUserID=t.fieldValue(*index);(*index)++;
		stGroupID=t.fieldValue(*index);(*index)++;
	}

	std::string sql_set_values(const std::string& stFormat=",") const 
	{
		std::string stQuery="userid='%%s'%sgroupid='%%s'";
		boost::format pre_fmt(stQuery);
		pre_fmt % stFormat;

		boost::format fmt(pre_fmt.str());
//		boost::format fmt("userid='%s',groupid='%s'");
		fmt % sql_helper::sql_escape(stUserID)
			% sql_helper::sql_escape(stGroupID);
		return fmt.str();
	}
	std::string sql_values() const 
	{
		boost::format fmt("'%s','%s'");
		fmt % sql_helper::sql_escape(stUserID)
			% sql_helper::sql_escape(stGroupID);
		return fmt.str();
	}
	static char* create_sql_table()
	{
		return "create table `groupmember`(userid TEXT,groupid TEXT);create index index_groupmember ON `groupmember`(userid);";
	}
	static char* get_tablename() {return "`groupmember`";}

	groupmember operator = (const groupmember &wf)
	{
		stUserID=wf.stUserID;
		stGroupID=wf.stGroupID;
		return *this;
	}

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
	ar & stUserID;
	ar & stGroupID;
	}
};

class patientinfo
{
public:
	std::string stPatientID;
	boost::gregorian::date Date;
	std::string bSex;
	std::string stName;
	std::string stHospitalID;

	patientinfo() {clear();}
	void clear()
	{
		stPatientID.clear();
		bSex.clear();
		stName.clear();
		stHospitalID.clear();
	}

	template <typename Type>
	patientinfo(Type& t,int* index)
	{
		stPatientID=t.fieldValue(*index);(*index)++;
		Date=boost::gregorian::from_string(t.fieldValue(*index));(*index)++;
		bSex=t.fieldValue(*index);(*index)++;
		stName=t.fieldValue(*index);(*index)++;
		stHospitalID=t.fieldValue(*index);(*index)++;
	}

	std::string GetDateString() const
	{
		if (Date==boost::gregorian::date())
			return "";
		else
			return boost::gregorian::to_simple_string(Date);
	}

	std::string sql_set_values(const std::string& stFormat=",") const 
	{
		std::string stQuery="patientid='%%s'%sage='%%s'%ssex='%%s'%sname='%%s'%shospitalid='%%s'";
		boost::format pre_fmt(stQuery);
		pre_fmt % stFormat
			% stFormat
			% stFormat
			% stFormat;

		boost::format fmt(pre_fmt.str());

//		boost::format fmt("patientid='%s',age='%s',sex='%s',name='%s',hospitalid='%s'");
		fmt % sql_helper::sql_escape(stPatientID)
			% GetDateString() 
			% sql_helper::sql_escape(bSex)
			% sql_helper::sql_escape(stName)
			% sql_helper::sql_escape(stHospitalID);
		return fmt.str();
	}
	std::string sql_values() const 
	{
		boost::format fmt("'%s','%s','%s','%s','%s'");
		fmt % sql_helper::sql_escape(stPatientID)
			% GetDateString() 
			% sql_helper::sql_escape(bSex)
			% sql_helper::sql_escape(stName)
			% sql_helper::sql_escape(stHospitalID);
		return fmt.str();
	}
	static char* create_sql_table()
	{
		return "create table `patientinfo`(patientid TEXT UNIQUE,age TEXT,sex TEXT,name TEXT,hospitalid TEXT);create index index_patientinfo ON `patientinfo`(patientid);";
	}
	static char* get_tablename() {return "`patientinfo`";}
	static char* get_primary() {return "patientid";}

	patientinfo operator = (const patientinfo &wf)
	{
		stPatientID=wf.stPatientID;
		Date=wf.Date;
		bSex=wf.bSex;
		stName=wf.stName;
		stHospitalID=wf.stHospitalID;
		return *this;
	}

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
	ar & stPatientID;
	ar & Date;
	ar & bSex;
	ar & stName;
	ar & stHospitalID;
	}
};

class fileinfo
{
public:
	std::string stNetPath;
	std::string stNetDir;
	owner Owner;
	boost::posix_time::ptime Time;
	diagnosis Diagnosis;
	std::string stPatientID;
	std::string stPatientName;
	std::string isDir; // 1 : dir
	int iAttribute;  // 1 : Hidden, 2 : Trash 

	bool bColor;

	fileinfo(const std::string& netpath
		,const std::string& netdir
		,const std::string& isdir
		,const owner& owner)

		: stNetPath(netpath)
		,stNetDir(netdir)
		,isDir(isdir)
		,Owner(owner)
	{
		Diagnosis.clear();
		stPatientID.clear();
		stPatientName.clear();
		bColor=false;
		iAttribute=0;
	}
		
	fileinfo() {clear();}
	void clear()
	{
		stNetPath.clear();
		stNetDir.clear();
		Owner.clear();

		Diagnosis.clear();
		stPatientID.clear();
		stPatientName.clear();
		isDir.clear();

		iAttribute=0;
		bColor=false;
	}
	std::string GetNetPath() const; //     /aa/b.jpg
	std::string GetNetDir() const;  //     /aa/
	bool IsDir() 
	{if (strcmp(isDir.c_str(),"1")==0) return true;
	else return false;}

	std::string GetDateString() const
	{
		if (Time==boost::posix_time::ptime())
			return "";
		else
		{
			std::string temp=boost::posix_time::to_iso_extended_string(Time);
			boost::algorithm::replace_all(temp,"T"," ");
			return temp;
		}
	}


	template <typename Type>
	fileinfo(Type& t,int* index)
	{
		stNetPath=t.fieldValue(*index);(*index)++;
		stNetDir=t.fieldValue(*index);(*index)++;
		Owner=owner(t,index);
		try
		{
			Time=boost::posix_time::time_from_string(t.fieldValue(*index));(*index)++;
		}
	    catch (std::exception& e) {e.what();(*index)++;}
		Diagnosis=diagnosis(t,index);
		stPatientID=t.fieldValue(*index);(*index)++;
		stPatientName=t.fieldValue(*index);(*index)++;
		isDir=t.fieldValue(*index);(*index)++;
		iAttribute=t.getIntField(*index);(*index)++;
	}

	std::string sql_set_values(const std::string& stFormat=",") const
	{
		std::string stQuery="netpath='%%s'%snetdir='%%s'%s%%s%sdate='%%s'%s%%s%spatientid='%%s'%spatientname='%%s'%sisdir='%%s'%sattribute='%%d'";
		boost::format pre_fmt(stQuery);
		pre_fmt % stFormat
			% stFormat
			% stFormat
			% stFormat
			% stFormat
			% stFormat
			% stFormat
			% stFormat;

//		boost::format fmt("netpath='%s',netdir='%s',%s,date='%s',%s,patientid='%s',patientname='%s',isdir='%s'");
		boost::format fmt(pre_fmt.str());
		fmt % sql_helper::sql_escape(stNetPath)
			% sql_helper::sql_escape(stNetDir)
			% Owner.sql_set_values(stFormat) 
			% GetDateString() 
			% Diagnosis.sql_set_values(stFormat)
			% sql_helper::sql_escape(stPatientID)
			% sql_helper::sql_escape(stPatientName)
			% sql_helper::sql_escape(isDir)
			% iAttribute;
		
		return fmt.str();
	}
	std::string sql_values() const 
	{
		boost::format fmt("'%s','%s',%s,'%s',%s,'%s','%s','%s','%s'");
		fmt % sql_helper::sql_escape(stNetPath)
			% sql_helper::sql_escape(stNetDir)
			% Owner.sql_values() 
			% GetDateString() 
			% Diagnosis.sql_values()
			% sql_helper::sql_escape(stPatientID)
			% sql_helper::sql_escape(stPatientName)
			% sql_helper::sql_escape(isDir)
			% iAttribute;
		return fmt.str();
	}

	tstring get_tooltip_info() const
	{
		tstring csTooltip;
		_tformat fmt(_T("ID : %s\nName :%s\nDiagnosis : %s\nICD10 : %s\nPath : %s\nDate : %s"));
		fmt % MCodeChanger::_CCL(stPatientID)
			% MCodeChanger::_CCL(stPatientName)
			% MCodeChanger::_CCL(Diagnosis.stDiagnosis)
			% MCodeChanger::_CCL(Diagnosis.stICD10)
			% MCodeChanger::_CCL(stNetPath)
			% MCodeChanger::_CCL(GetDateString());
		return csTooltip;
	}
	static char* create_sql_table()
	{
		return "create table `fileinfo`(netpath TEXT UNIQUE,netdir TEXT,groupid TEXT,userid TEXT,userpriv INTERGER,grouppriv INTERGER,otherpriv INTERGER,date TEXT,diagnosis TEXT,icd10 TEXT,patientid TEXT,patientname TEXT,isdir TEXT,attribute INTERGER);create index index_fileinfo ON `fileinfo`(netpath,netdir,groupid,userid,userpriv,grouppriv,otherpriv,diagnosis,icd10,patientid,patientname,isdir,attribute);";
	}
	static char* all_field_name()
	{
		return "fileinfo.netpath,fileinfo.netdir,fileinfo.groupid,fileinfo.userid,fileinfo.userpriv,fileinfo.grouppriv,fileinfo.otherpriv,fileinfo.date,fileinfo.diagnosis,fileinfo.icd10,fileinfo.patientid,fileinfo.patientname,fileinfo.isdir,fileinfo.attribute";
	}
	static char* get_tablename() {return "fileinfo";}
	static char* get_primary() {return "netpath";}
	std::string get_unique() const {return GetNetPath();}
//	std::string get_primary_value() const {return GetNetPath();}

	fileinfo operator = (const fileinfo &wf)
	{
//		stPath=wf.GetPath();
		stNetPath=wf.stNetPath;
		stNetDir=wf.stNetDir;
		Owner=wf.Owner;
		Time=wf.Time;
		Diagnosis=wf.Diagnosis;
		stPatientID=wf.stPatientID;
		stPatientName=wf.stPatientName;
		isDir=wf.isDir;
		iAttribute=wf.iAttribute;
		return *this;
	}
//	static void Open(const std::string&Path) {stRootPath=Path;}

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
//	ar & stPath;
	ar & stNetPath;
	ar & stNetDir;
	ar & Owner;
	ar & Time;
	ar & Diagnosis;
	ar & stPatientID;
	ar & stPatientName;
	ar & isDir;
	ar & iAttribute;
	}
//	static std::string stRootPath;
};
typedef std::vector<fileinfo> fileinfo_list;
typedef std::vector<std::string> filepath_list;

class sort_fileinfo{
public:
	bool operator() (const fileinfo &a,const fileinfo &b) const
	{
		return a.stNetPath<b.stNetPath;
	}
};
/*
	class sort_fileinfo_by_Date{
public:
	bool operator() (const fileinfo &a,const fileinfo &b) const
	{
		return a.Time<b.Time;
	}
	*/
class sort_fileinfo_by_ID{
public:
	bool operator() (const fileinfo &a,const fileinfo &b) const
	{
		if (strcmp(a.stPatientID.c_str(),b.stPatientID.c_str())==0)
		{
			if (a.Time==boost::posix_time::ptime()) return false;
		if (b.Time==boost::posix_time::ptime()) return true;
			return a.Time>b.Time;
		}
		else
			return a.stPatientID<b.stPatientID;
	}
};
class sort_fileinfo_by_Time{
public:
	bool operator() (const fileinfo &a,const fileinfo &b) const
	{
		if (a.Time==boost::posix_time::ptime()) return false;
		if (b.Time==boost::posix_time::ptime()) return true;
		return a.Time>b.Time;
	}
};

class sort_fileinfo_by_PatientName_Time{
public:
	bool operator() (const fileinfo &a,const fileinfo &b) const
	{
		if (strcmp(a.stPatientName.c_str(),b.stPatientName.c_str())==0)
		{
			if (a.Time==boost::posix_time::ptime()) return false;
		if (b.Time==boost::posix_time::ptime()) return true;
			return a.Time>b.Time;
		}
		else
			return a.stPatientName<b.stPatientName;
	}
};

class comment
{
public:
	std::string stNetPath;
	boost::posix_time::ptime Time;
	std::string stDetail;
	owner Owner;

	comment() {clear();}
	comment(const std::string &path,const std::string userid,const std::string& detail)
		: Owner(userid)
		,stNetPath(path)
		,stDetail(detail)
		,Time(boost::posix_time::second_clock::local_time())
	{
	}
	void clear()
	{
		stNetPath.clear();
		stDetail.clear();
		Owner.clear();
	}
	std::string GetNetPath() const {return stNetPath;} 

	template <typename Type>
	comment(Type& t,int* index)
	{
		stNetPath=t.fieldValue(*index);(*index)++;
		Time=boost::posix_time::time_from_string(t.fieldValue(*index));(*index)++;
		stDetail=t.fieldValue(*index);(*index)++;
		Owner=owner(t,index);
	}

	std::string GetDateString() const
	{
		if (Time==boost::posix_time::ptime())
			return "";
		else
		{
			std::string temp=boost::posix_time::to_iso_extended_string(Time);
			boost::algorithm::replace_all(temp,"T"," ");
			return temp;
		}
	}

	std::string sql_set_values(const std::string& stFormat=",") const 
	{
		std::string stQuery="netpath='%%s'%sdate='%%s'%sdetail='%%s'%s%%s";
		boost::format pre_fmt(stQuery);
		pre_fmt % stFormat
			% stFormat
			% stFormat;

		boost::format fmt(pre_fmt.str());
		fmt % sql_helper::sql_escape(stNetPath)
			% GetDateString()
			% sql_helper::sql_escape(stDetail)
			% Owner.sql_set_values(stFormat);
		return fmt.str();
	}
	std::string sql_values() const 
	{
		boost::format fmt("'%s','%s','%s',%s");
		fmt % sql_helper::sql_escape(stNetPath)
			% GetDateString() 
			% sql_helper::sql_escape(stDetail)
			% Owner.sql_values();
		return fmt.str();
	}
	static char* create_sql_table()
	{
		return "create table `comment`(netpath TEXT,date TEXT,detail TEXT,userid TEXT,groupid TEXT,userpriv INTERGER,grouppriv INTERGER,otherpriv INTERGER);create index index_comment ON `comment`(netpath,detail,userid,groupid,userpriv,grouppriv,otherpriv);";
	}
	static char* get_tablename() {return "comment";}
	static char* get_primary() {return "netpath";}
//	std::string get_unique() const {return GetNetPath();}
//	std::string get_primary_value() const {return stNetPath;}

	comment operator = (const comment &wf)
	{
		stNetPath=wf.stNetPath;
		Time=wf.Time;
		stDetail=wf.stDetail;
		Owner=wf.Owner;
		return *this;
	}
	bool operator == (const comment &wf) const
	{
		if (strcmp(stNetPath.c_str(),wf.stNetPath.c_str())==0 &&
		strcmp(stDetail.c_str(),wf.stDetail.c_str())==0 &&
		Owner==wf.Owner &&
		strcmp(boost::posix_time::to_iso_extended_string(Time).c_str(),boost::posix_time::to_iso_extended_string(wf.Time).c_str())==0)
			return true;
		else
			return false;
	}
	static bool compare_details(const comment& a,const comment& b)
	{
		if (strcmp(a.stDetail.c_str(),b.stDetail.c_str())==0
		&& a.Owner==b.Owner
		&& strcmp(boost::posix_time::to_iso_extended_string(a.Time).c_str(),boost::posix_time::to_iso_extended_string(b.Time).c_str())==0
		)


			return true;
		else
			return false;
	}

private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
	ar & stNetPath;
	ar & Time;
	ar & stDetail;
	ar & Owner;
	}
};

typedef std::vector<comment> comment_list;

class comment_cluster
{
public:
	std::vector<std::string> stNetPath_list;
	comment comment_;

	int size()
	{
		return (int)stNetPath_list.size();
	}
	void clear()
	{
		stNetPath_list.clear();
		comment_.clear();
	}
	void set(const comment& com_)
	{
		comment_=com_;
	}
	void add(const comment& com_)
	{
		stNetPath_list.push_back(com_.GetNetPath());
	}
private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & stNetPath_list;
		ar & comment_;
	}

};

typedef std::vector<comment_cluster> comment_cluster_list;

class customfield
{
public:
	static char* create_sql_table()
	{
		return "create table `customfield`(index_ INTERGER UNIQUE,fieldname TEXT,description TEXT,fieldtype INTERGER);";
	}
	static char* delete_sql_table()
	{
		return "drop table if exists `customfield`;";
	}
	static char* get_tablename() {return "`customfield`";}
	static char* get_primary() {return "index_";}

};
/*
class searchhistory
{
public:
	static char* create_sql_table()
	{
		return "create table `searchhistory`(keyword TEXT,userid TEXT,date DATE);";
	}
	static char* get_tablename() {return "`searchhistory`";}
};
*/
class sqllog
{
public:
	static char* create_sql_table()
	{
		return "create table `sqllog`(command TEXT,param1 TEXT,param2 TEXT,loglevel INTERGER,date DATE);";
	}
	static char* delete_sql_table()
	{
		return "drop table if exists `sqllog`;";
	}
	static char* get_tablename() {return "`sqllog`";}

};