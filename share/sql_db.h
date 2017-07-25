////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../boost.h"
#include "unicode.h"
//#include "../SqliteStatic/CppSQLite3.h"
#include "../sqlite/CppSQLite3.h"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/format.hpp>
#include <boost/thread/mutex.hpp>
#include "datatype.h"
#include "file.h"
#include "config.h"

#include "cmycout.h"

namespace bfs=boost::filesystem; 

#define SQL_VERSION 2
#define SUPER_ADMIN_ID "superadmin"

class SQL_DB :public CppSQLite3DB
{
public:
	SQL_DB(CMyCout& l)
		: log(l)
		,bOnTransaction(false)
	{
	}
	~SQL_DB()
	{
		close();
	}

protected:
	CMyCout& log;

public :
	//

	void Open(const std::string& db_utf_path)
	{
//		bfs::path prog_path=bfs::initial_path();
//		prog_path /= "database.dat";

//		_tpath prog_path=bfs::initial_path<_tpath>();
//		prog_path /= db_path;
//		CppSQLite3DB::close();
		MFile::CreateFolder(_tpath(MCodeChanger::_CCL(db_utf_path)).parent_path());
#ifdef _DEBUG
		log << _T("Try to open the Database [ ") << MCodeChanger::_CCL(db_utf_path.c_str()) << _T(" ]\n");
#endif
		CppSQLite3DB::open(db_utf_path.c_str());
	}

	void Close()
	{
		CppSQLite3DB::close();
	}

	bool Check()
	{
		if (!tableExists("version"))
		{
			execDML("create table `version`(version INTEGER );");
			boost::format fmt("insert into `version` values(%d)");fmt % SQL_VERSION;
			execDML(fmt.str().c_str());
			
			CreateTable();
			return false;
		}
		return true;
	}

	bool CheckLowVersion(int* iVersion)
	{
		if (!tableExists("version"))
		{
			return true;
		}
		else
		{
			CppSQLite3Query q=execQuery("select * from `version`;");

			*iVersion=-1;
			for (int i=0;i<q.numFields();i++)
			{
				if (strcmp(q.fieldName(i),"version")==0)
				{
					*iVersion=q.getIntField(i);
				}
			}

			if (*iVersion==-1) return true;
			if (SQL_VERSION > *iVersion) return true;
		}
		return false;
	}

	bool UpdateVersionInfo()
	{
		std::string stQuery="UPDATE `version` SET version='%d' WHERE version='1';";
		boost::format fmt(stQuery);
		fmt % SQL_VERSION; 
		if (execDML(fmt.str().c_str())!=1)
		{
			log << _T("Fail to update version info\n");
			return false;
		}
		return true;
	}
public:
	virtual void CreateTable()
	{
		log<< _T("Build SQL Information\n");

		BeginTransaction();
	//	execDML(comment::create_sql_table());
	//	execDML(fileinfo::create_sql_table());

		execDML(group::create_sql_table());
		execDML(groupmember::create_sql_table());
		execDML(hospital::create_sql_table());
		execDML(grade::create_sql_table());
		execDML(patientinfo::create_sql_table());
		execDML(user::create_sql_table());
		execDML("create table `userdx`(diagnosis TEXT,icd10 TEXT);");
		execDML("create index index_userdx ON `userdx`(diagnosis);");
		execDML("INSERT INTO `user` VALUES('Administrator','superadmin','0000','AMC','Fellow','Korea');");
		execDML("INSERT INTO `group` VALUES('superadmin','Administrator');");
		execDML("INSERT INTO `groupmember` VALUES('superadmin','superadmin');");

		execDML(sqllog::create_sql_table());
	/*
		execDML("create table log(message TEXT,date TEXT);");
		execDML("create table logerror(errorflag INTERGER,code INTERGER,message TEXT,date TEXT);");
		execDML("create table logcommand(userid TEXT,order_code INTERGER);");
		execDML("create table logcommandparams(logcommand_index INTERGER,param TEXT);");
	*/
		CommitTransaction();
	}


	int DeleteTable(const std::string& stTableName)
	{
		boost::format fmt("Drop Table if exists %s;");
		fmt % stTableName;
		return execDML(fmt.str().c_str());
	}

	template <typename T>
	bool GetInfo_from_Primary(const std::string& stUnique,T& result)
	{
		return GetInfo(result.get_tablename(),result.get_primary(),stUnique,result);
	}
	template <typename T>
	bool GetInfo(const std::string& stTable,const std::string& stField,const std::string& stUnique,T& result)
	{
	boost::format fmt("SELECT * FROM %s WHERE %s='%s';");
	fmt % stTable % stField % sql_helper::sql_escape(stUnique);
	CppSQLite3Table t=getTable(fmt.str().c_str());
	if (t.numRows()!=1) return false;
	t.setRow(0);
	int index=0;
	result=T(t,&index);
	return true;
	}

	template <typename T>
	bool CheckExistInfo_from_Primary(int stUnique,const T& const_temp)
	{
		boost::format fmt("%d");
		fmt % sql_helper::sql_escape(stUnique);
//		return CheckExistInfo_from_Primary(fmt.str(),const_temp);
		return CheckExistInfo(const_temp.get_tablename(),const_temp.get_primary(),fmt.str());
	}
	template <typename T>
	bool CheckExistInfo_from_Primary(const std::string& stUnique,const T& const_temp)
	{
		return CheckExistInfo(const_temp.get_tablename(),const_temp.get_primary(),stUnique);
	}
//	template <typename T>
	bool CheckExistInfo(const std::string& stTable,const std::string& stField,const std::string& stUnique)
	{
	boost::format fmt("SELECT %s FROM %s WHERE %s='%s';");
	fmt % stField % stTable % stField % sql_helper::sql_escape(stUnique);
	CppSQLite3Table t=getTable(fmt.str().c_str());
	if (t.numRows()==0) 
		return false;
	else
		return true;
	}
	/*
	template <typename T>
	bool IsExists(const T& t) {return IsExists(T::get_tablename(),t);}
	template <typename T>
	bool IsExists(const std::string& stTable, const T& t)
	{
		std::string stQuery;
		stQuery="SELECT %s FROM %s WHERE %s='%s';";

		boost::format fmt(stQuery);
		fmt % T::get_primary() % stTable % T::get_primary() % t.get_unique();

		CppSQLite3Table result=getTable(fmt.str().c_str());
		
		if (result.numRows()>0) 
			return true;
		else
			return false;
	}
	*/
	template <typename T>
	bool IsEmpty(const T& temp)
	{
		std::string stQuery;
		stQuery="SELECT %s FROM %s;";

		boost::format fmt(stQuery);
		fmt % T::get_primary() % T::get_tablename();

		fmt.str();

		CppSQLite3Table result = getTable(fmt.str().c_str());
		if (result.numRows()>0)
			return false;
		else
			return true;
	}


	template <typename T>
	bool IsExists(const T& t)
	{
		std::string stQuery;
		stQuery="SELECT %s FROM %s WHERE %s;";

		std::string query=t.sql_set_values(" AND ");

/*		size_t i = 0;
		while ((i = query.find(",")) != std::string::npos)
			query.replace(i, 1, " AND ");
*/
		boost::format fmt(stQuery);
		fmt % T::get_primary() % t.get_tablename() % query;

		CppSQLite3Table result=getTable(fmt.str().c_str());
		
		if (result.numRows()>0) 
			return true;
		else
			return false;
	}

	template <typename T>
	bool IsExistsFromPrimary(const std::string& stUnique,const T& t)
	{
		std::string stQuery;
		stQuery="SELECT %s FROM %s WHERE %s='%s';";

		boost::format fmt(stQuery);
		fmt % T::get_primary() 
			% T::get_tablename() 
			% T::get_primary() 
			% sql_helper::sql_escape(stUnique);

		CppSQLite3Table result=getTable(fmt.str().c_str());
		
		if (result.numRows()>0) 
			return true;
		else
			return false;
	}

	// INSERT INTO foo VALUES (a,b,c);
	// UPDATE foo SET a='b',c='d' WHERE ...;
	template <typename T>
	int Insert(const T& info) {return Insert(info.get_tablename(),info);}
	template <typename T>
	int Insert(const std::string& stTable,const T& info)
	{
		boost::format fmt("INSERT INTO %s VALUES (%s);");
		fmt % stTable % info.sql_values();
		return execDML(fmt.str().c_str());
	}

	template <typename T>
	int Delete(const T& t)
	{
		boost::format fmt("DELETE FROM %s WHERE %s;");

		std::string query=t.sql_set_values(" AND ");
/*		size_t i = 0;
		while ((i = query.find(",")) != std::string::npos)
			query.replace(i, 1, " AND ");
*/
		fmt % T::get_tablename()
			% query;

		return execDML(fmt.str().c_str());
	}

	int Delete(const std::string& stTable,const std::string& stField,const std::string& stUnique,const std::string stOption)
	{
		std::string stQuery="DELETE FROM %s WHERE ";
		stQuery+=stOption;
		stQuery+=";";
			// 

		boost::format fmt(stQuery);
		fmt % stTable % stField % sql_helper::sql_escape(stUnique);
		return execDML(fmt.str().c_str());
	}
	int Delete(const std::string& stTable,const std::string& stField,const std::string& stUnique)
	{
		return Delete(stTable,stField,stUnique,"%s='%s'");
/*		boost::format fmt("DELETE FROM %s WHERE %s='%s';");
		fmt % stTable % stField % stUnique;
		return execDML(fmt.str().c_str());*/
	}
	template <typename T>
	int Delete(const std::string& stUnique,const T& t)
	{
		return Delete(T::get_tablename(),T::get_primary(),stUnique);
	}

	template <typename T>
	int Update(const T& info) {return Update(info.get_tablename(),info,info.get_primary(),info.get_unique());}
	template <typename T>
	int Update(const T& info,const std::string& stUnique) {return Update(info.get_tablename(),info,info.get_primary(),stUnique);}
	template <typename T>
	int Update(const std::string& stTable,const T& info,const std::string& stField,int stUnique)
	{
		boost::format fmt("%d");fmt % stUnique;
		return Update(stTable,info,stField,fmt.str());
	}
	template <typename T>
	int Update(const std::string& stTable,const T& info,const std::string& stField,const std::string& stUnique)
	{
		boost::format fmt("UPDATE %s SET %s WHERE %s='%s';");
		fmt % stTable % info.sql_set_values() % stField % sql_helper::sql_escape(stUnique);
		return execDML(fmt.str().c_str());
	}
	template <typename T>
	int Update(const T& from,const T&to)
	{
		boost::format fmt("UPDATE %s SET %s WHERE %s;");
		std::string query=from.sql_set_values(" AND ");

/*		size_t i = 0;
		while ((i = query.find(",")) != std::string::npos)
			query.replace(i, 1, " AND ");
*/
		fmt % T::get_tablename() % to.sql_set_values() % query;
		return execDML(fmt.str().c_str());
	}
/*
	int UpdatePath(const std::string& from,const std::string& to)
	{
		boost::format fmt("UPDATE %s SET %s='%s' WHERE %s='%s';");
		fmt % fileinfo::get_tablename() 
			% fileinfo::get_primary()
			% from
			% fileinfo::get_primary()
			% to;
		return execDML(fmt.str().c_str());
	}
	int UpdateDirPath(const std::string& from,const std::string& to)
	{
		boost::format fmt("UPDATE %s SET %s='%s' WHERE %s='%s';");
		fmt % fileinfo::get_tablename() 
			% "netdir"
			% from
			% "netdir"
			% to;
		return execDML(fmt.str().c_str());
	}

	int UpdateCommentPath(const std::string& from,const std::string& to)
	{
		boost::format fmt("UPDATE %s SET %s='%s' WHERE %s='%s';");
		fmt % comment::get_tablename() 
			% fileinfo::get_primary()
			% from
			% fileinfo::get_primary()
			% to;
		return execDML(fmt.str().c_str());
	}*/


//	bool GetFileInfo(const std::string& stPath,fileinfo& result) {return GetInfo_from_Primary(stPath,result);}

	/*
	group GetGroup(const std::string& stGroupID){group temp;GetInfo_from_Primary(stGroupID,temp);return temp;}	
	hospital GetHospital(const std::string& stHospitalID);
	grade GetGrade(const int& iGrade);
	patientinfo GetPatientInfo(const std::string& stPatientID);
	user GetUser(const std::string& stUserID);

	diagnosis GetNewDx(const std::string& stDiagnosis);
	*/
	user_list GetUser(const id_list& ID_List);

	template <typename T_list,typename T>
	void Find(const std::string& stKeyword,T_list& t_list,const T& temp,bool bExact=false)
	{
		Find(temp.get_tablename(),temp.get_primary(),stKeyword,t_list,temp,bExact);
	}
	template <typename T_list,typename T>
	void Find(const std::string& stField,const std::string& stKeyword,T_list& t_list,const T& temp,bool bExact=false)
	{
		Find(temp.get_tablename(),stField,stKeyword,t_list,temp,bExact);
	}
	template <typename T_list,typename T>
	void Find(const std::string& stTable,const std::string& stField,const std::string& stKeyword,T_list& t_list,const T& temp,bool bExact=false)
	{
		std::string stQuery;
		if (bExact)
		{
			stQuery="SELECT * FROM %s WHERE %s='%s';";
		}
		else
		{
			stQuery="SELECT * FROM %s WHERE %s LIKE '%%%s%%';";
		}
		boost::format fmt(stQuery);
		fmt % stTable % stField % sql_helper::sql_escape(stKeyword);	

		FindCommon(fmt.str(),t_list,temp);
/*		CppSQLite3Query q=execQuery(fmt.str().c_str());

		while (!q.eof())
		{
			int index=0;
			t_list.push_back(T(q,&index));
			q.nextRow();
		}
*/
	}
	
	template <typename T_list,typename T>
	void Find(const std::string& stTable,const std::vector<std::string>& stField_list,const std::vector<std::string>& stKeyword_list
		,T_list& t_list,const T& temp,bool bExact=false)
	{
		std::string stQuery;
		if (bExact)
		{
			stQuery+="%s='%s' OR ";
		}
		else
		{
			stQuery+="%s LIKE '%%%s%%' OR ";
		}

		Find(stTable,stField_list,stKeyword_list,t_list,temp,stQuery);
		/*
		if (stField_list.size()!=stKeyword_list.size() || stField_list.size()==0) return;

		std::string stQuery="SELECT * FROM %s WHERE ";

		for (unsigned int i=0;i<stField_list.size();i++)
		{
			if (bExact)
			{
				stQuery+="%s='%s' OR ";
			}
			else
			{
				stQuery+="%s LIKE '%%%s%%' OR ";
			}
		}
		boost::algorithm::replace_last(stQuery,"OR ",";");

		boost::format fmt(stQuery);
		fmt % stTable;

		for (unsigned int i=0;i<stField_list.size();i++)
		{
			fmt % stField_list[i] % stKeyword_list[i];
		}

		FindCommon(fmt.str(),t_list,temp);*/
	}

	template <typename T_list,typename T>
	void Find(const std::string& stTable,const std::vector<std::string>& stField_list,const std::vector<std::string>& stKeyword_list
		,T_list& t_list,const T& temp,const std::string& stSearchOption)
	{
		if (stField_list.size()!=stKeyword_list.size() || stField_list.size()==0) return;

		std::string stQuery="SELECT * FROM %s WHERE ";

		for (unsigned int i=0;i<stField_list.size();i++)
		{
			stQuery+=stSearchOption;
			/*
			if (bExact)
			{
				stQuery+="%s='%s' OR ";
			}
			else
			{
				stQuery+="%s LIKE '%%%s%%' OR ";
			}*/
		}
		boost::algorithm::replace_last(stQuery,"OR ",";");

		boost::format fmt(stQuery);
		fmt % stTable;

		for (unsigned int i=0;i<stField_list.size();i++)
		{
			fmt % stField_list[i] % sql_helper::sql_escape(stKeyword_list[i]);
		}

		FindCommon(fmt.str(),t_list,temp);
	}


	template <typename T_list,typename T>
	void FindCommon(const std::string& stQuery,T_list& t_list,const T& temp)
	{
		CppSQLite3Query q=execQuery(stQuery.c_str());

		while (!q.eof())
		{
			int index=0;
			t_list.push_back(T(q,&index));
			q.nextRow();
		}
	}


	template <typename T_list,typename T>
	void GetTable(const std::string& stTable,T_list& t_list,const T& temp)
	{
		std::string stQuery;
		stQuery="SELECT * FROM %s;";

		boost::format fmt(stQuery);
		fmt % stTable;

		CppSQLite3Query q=execQuery(fmt.str().c_str());

		while (!q.eof())
		{
			int index=0;
			t_list.push_back(T(q,&index));
			q.nextRow();
		}
	}

	template <typename T_list,typename T>
	void FindEx(const std::string& stField,const std::string& stKeyword,T_list& t_list,const T& temp) {Find(stField,stKeyword,t_list,temp,true);}
	template <typename T_list,typename T>
	void FindEx(const std::string& stTable,const std::string& stField,const std::string& stKeyword,T_list& t_list,const T& temp) {Find(stTable,stField,stKeyword,t_list,temp,true);}

	template <typename T>
	bool CheckPriv(const std::string & stUserID,const T& t,bool bWrite=false)
	{
		if (strcmp(stUserID.c_str(),SUPER_ADMIN_ID)==0) return true;

		/*
		if (t.Owner.Priv.bOtherRead && bWrite==false) return true;
		if (t.Owner.Priv.bOtherWrite && bWrite==true) return true;

		if (strcmp(stUserID.c_str(),t.Owner.stUserID.c_str())==0)
		{
			if (t.Owner.Priv.bUserRead && bWrite==false) return true;
			if (t.Owner.Priv.bUserWrite && bWrite==true) return true;
		}
		groupmember g_member;
		if (GetInfo("groupmember","userid",stUserID,g_member))
		{
			if (t.Owner.Priv.bGroupRead && bWrite==false) return true;
			if (t.Owner.Priv.bGroupWrite && bWrite==true) return true;
		}
		*/
		return false;
	}
/*
	bool CheckRootPriv(const std::string & stUserID,const _tpath& dir_,bool bWrite=false)
	{
		if (strcmp(stUserID.c_str(),SUPER_ADMIN_ID)==0) return true;

		fileinfo dir_info;
		if (!GetInfo_from_Primary(MCodeChanger::_CCU(dir_.root_path().string()),dir_info))
			return false;

		if (CheckPriv(stUserID,dir_info,bWrite))
			return true;
		else
			return false;
	}
*/
	int BeginTransaction() 
	{
		boost::mutex::scoped_lock lock(sql_mutex);

		if (bOnTransaction) return 0;
		bOnTransaction=true;

		#ifdef _DEBUG
		log << _T("[sql] begin transaction\n");
		#endif
		return CppSQLite3DB::execDML("begin transaction;");
	}
	int CommitTransaction() 
	{
		boost::mutex::scoped_lock lock(sql_mutex);

		if (!bOnTransaction) return 0;
		bOnTransaction=false;

		#ifdef _DEBUG
		log << _T("[sql] commit transaction\n");
		#endif
		return CppSQLite3DB::execDML("commit transaction;");
	}
protected:
	bool bOnTransaction;

public:


	// MUTEX

	bool tableExists(const char* szTable)
	{
		boost::mutex::scoped_lock lock(sql_mutex);

		return CppSQLite3DB::tableExists(szTable);
	}
    int execDML(const char* szSQL)
	{
		boost::mutex::scoped_lock lock(sql_mutex);
		#ifdef _DEBUG
		log << _T("[sql] ") << MCodeChanger::_CCL(szSQL) << _T("\n");
		#endif
		return CppSQLite3DB::execDML(szSQL);
	}

	CppSQLite3Query execQuery(const char* szSQL)
	{
		boost::mutex::scoped_lock lock(sql_mutex);
		#ifdef _DEBUG
		log << _T("[sql] ") << MCodeChanger::_CCL(szSQL) << _T("\n");
		#endif

		return CppSQLite3DB::execQuery(szSQL);
	}

    int execScalar(const char* szSQL)
	{
		boost::mutex::scoped_lock lock(sql_mutex);
		#ifdef _DEBUG
		log << _T("[sql] ") << MCodeChanger::_CCL(szSQL) << _T("\n");
		#endif

		return CppSQLite3DB::execScalar(szSQL);
//		CppSQLite3Table t=CppSQLite3DB::getTable(szSQL);
//		return t.numRows();
	}

    CppSQLite3Table getTable(const char* szSQL)
	{
		boost::mutex::scoped_lock lock(sql_mutex);
		#ifdef _DEBUG
		log << _T("[sql] ") << MCodeChanger::_CCL(szSQL) << _T("\n");
		#endif

		return CppSQLite3DB::getTable(szSQL);
	}

    CppSQLite3Statement compileStatement(const char* szSQL)
	{
		boost::mutex::scoped_lock lock(sql_mutex);
		#ifdef _DEBUG
		log << _T("[sql] ") << MCodeChanger::_CCL(szSQL) << _T("\n");
		#endif

		return CppSQLite3DB::compileStatement(szSQL);
	}

    void interrupt()
	{
		boost::mutex::scoped_lock lock(sql_mutex);

		CppSQLite3DB::interrupt();
	}

	sqlite_int64 lastRowId()
	{
		boost::mutex::scoped_lock lock(sql_mutex);

		return CppSQLite3DB::lastRowId();
	}

public:

	static boost::mutex sql_mutex;
};
