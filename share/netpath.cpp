#include "stdafx.h"
#include "netpath.h"

#define SLEEP_FOR_WATCH 5
#define SLEEP_FOR_WRITE 100

void netvolume::BuildInfo(_tpath& path,bool bRoot)
{
	try
	{
		if (!bRoot)
		{
			fileinfo new_fileinfo=CreateFileInfo(path.string());
			LoadMetatag(new_fileinfo);
			Insert(new_fileinfo);
		}
		_tdirectory_iterator end_iter;
		for ( _tdirectory_iterator dir_itr( path );
		  dir_itr != end_iter;
		  ++dir_itr )
		{
			_tpath temp = MFile::refinepath(*dir_itr);

			if (bfs::is_directory(temp))
			{
				BuildInfo(temp);
			}
			else
			{
				tstring filepath=temp.c_str();
				if (config_.Compare(FILE_EXTENSIONS,MCodeChanger::_CCU(MFile::GetFileExtL(filepath))))
				{
					fileinfo new_fileinfo=CreateFileInfo(filepath);
					LoadMetatag(new_fileinfo);
					Insert(new_fileinfo);
					log << _T("[Watcher] Create :") << filepath << log.endl();
				}
	//			file_list.push_back(*dir_itr);
			}
		}
	}
	catch(std::exception& e)
	{
		log << _T("[Watcher] Create Error : ") << MCodeChanger::_CCL(e.what()) << log.endl();
	}
	catch (CppSQLite3Exception& e)
	{
		log << _T("[Watcher] Create Error : ") << MCodeChanger::_CCL(e.errorMessage()) << log.endl();
	}
	catch(...)
	{
		log << _T("[Watcher] Create Error") << log.endl();
	}

}

void netvolume::OnCreate(tstring filename_org)
{
	boost::replace_all(filename_org, _T("\\"), _T("/"));

	try
	{
		if (filename_org.find(sql_filename)==0)
			return;

#ifdef _DEBUG
	log << _T("[Call Watcher] Create :") << filename_org << log.endl();
#endif

	Utility::sleep(SLEEP_FOR_WRITE);

//		log << _T("[Watcher] Create Add :") << path.string() << _T("\n");
		_tpath path(root_path);
		path /= filename_org; path = Utility::refinepath(path);
		tstring filename=path.c_str();

		net_watcher_.RemoveModify(WATCH_CREATE,filename);

		tstring stCutFolder;
		if (net_watcher_.GetCutFlag(stCutFolder))
		{
			_tpath tmp(stCutFolder);
			tmp /= tmp.filename(); tmp = Utility::refinepath(tmp);
			
			if (_tcscmp(path.c_str(),
				tmp.c_str())!=0)
			{
				net_watcher_.SetCutFlag(false);
			}
			else
			{
				BeginTransaction();
				BuildInfo(_tpath(stCutFolder),true);
				CommitTransaction();
				net_watcher_.SetCutFlag(false);
			}
			MFile::Delete(tmp);
			net_watcher_.Add(WATCH_DELETE,tmp.c_str());
		}

		if (!boost::filesystem::is_directory(path) 
			&& !config_.Compare(FILE_EXTENSIONS,MCodeChanger::_CCU(MFile::GetFileExtL(filename_org))))
			return;

		if (net_watcher_.ChecknRemove(WATCH_CREATE,filename))
			return;

	
		if (!boost::filesystem::is_directory(path))
		{
			net_watcher_.Add(WATCH_MODIFY,filename);
			net_watcher_.Add(WATCH_MODIFY,filename);
			net_watcher_.Add(WATCH_MODIFY,filename);
		}
		

		log << _T("[Watcher] Create :") << filename << log.endl();

		fileinfo new_fileinfo=CreateFileInfo(filename);
		LoadMetatag(new_fileinfo);
		
		if (boost::filesystem::is_directory(path))
		{
			Utility::sleep(100);

			_tdirectory_iterator end_iter;
			_tdirectory_iterator dir_itr(path);
			if (dir_itr != end_iter)
			{
				net_watcher_.SetCutFlag(true,path.c_str());
				_tpath tmp=path;
				tmp /= path.filename(); tmp = Utility::refinepath(tmp);
				FILE* fp=_tfopen(tmp.c_str(),_T("wb"));
				if (fp!=NULL)
				{fclose(fp);fp=NULL;}
			}

		}

		Insert(new_fileinfo);
		MFile::DeleteL(Net_Thumb(Local_Net(filename)));
	}
	catch(std::exception& e)
	{
		log << _T("[Watcher] Create Error : ") << MCodeChanger::_CCL(e.what()) << log.endl();
	}
	catch (CppSQLite3Exception& e)
	{
		log << _T("[Watcher] Create Error : ") << MCodeChanger::_CCL(e.errorMessage()) << log.endl();
	}
	catch(...)
	{
		log << _T("[Watcher] Create Error") << log.endl();
	}
}
void netvolume::OnDelete(tstring filename_org)
{
	boost::replace_all(filename_org, _T("\\"), _T("/"));
	try
	{
		if (filename_org.find(sql_filename)==0)
			return;

#ifdef _DEBUG
	log << _T("[Call Watcher] Delete :") << filename_org << log.endl();
#endif

		_tpath path(root_path);
		path /= filename_org; path = Utility::refinepath(path);
		tstring filename=path.c_str();

		net_watcher_.RemoveModify(WATCH_DELETE,filename);

		fileinfo fileinfo_;
		if (GetFileInfo(Local_Net(path.c_str()),fileinfo_)==false)
			return;

		if (net_watcher_.ChecknRemove(WATCH_DELETE,filename))
			return;
		log << _T("[Watcher] Delete :") << filename << log.endl();

		if (fileinfo_.IsDir())
			DeleteFolder(Local_Net(filename));
		else
			DeleteFile(Local_Net(filename));
		
	}
	catch(std::exception& e)
	{
		log << _T("[Watcher] Delete Error : ") << MCodeChanger::_CCL(e.what()) << log.endl();
	}
	catch (CppSQLite3Exception& e)
	{
		log << _T("[Watcher] Delete Error : ") << MCodeChanger::_CCL(e.errorMessage()) << log.endl();
	}
	catch(...)
	{
		log << _T("[Watcher] Delete Error") << log.endl();
	}
}
void netvolume::OnChange(tstring filename_org)
{
	boost::replace_all(filename_org, _T("\\"), _T("/"));
	try
	{
		if (filename_org.find(sql_filename)==0)
			return;

Utility::sleep(SLEEP_FOR_WRITE);

#ifdef _DEBUG
	log << _T("[Call Watcher] Change :") << filename_org << log.endl();
#endif

		_tpath path(root_path);
		path/=filename_org;		path = Utility::refinepath(path);
		tstring filename=path.c_str();

		net_watcher_.RemoveModify(WATCH_MODIFY,filename);

		if (!boost::filesystem::is_directory(path) 
			&& !config_.Compare(FILE_EXTENSIONS,MCodeChanger::_CCU(MFile::GetFileExtL(filename_org))))
			return;
		if (net_watcher_.ChecknRemove(WATCH_MODIFY,filename))
			return;
		if (boost::filesystem::is_directory(path))
			return;

		net_watcher_.Add(WATCH_MODIFY,filename);
		net_watcher_.Add(WATCH_MODIFY,filename);
		net_watcher_.Add(WATCH_MODIFY,filename);

		log << _T("[Watcher] Modify :") << filename << log.endl();

		fileinfo new_fileinfo=CreateFileInfo(filename);
		LoadMetatag(new_fileinfo);

		fileinfo old_fileinfo;
		if (GetFileInfo(new_fileinfo.GetNetPath(),old_fileinfo))
		{
//			Update(old_fileinfo,new_fileinfo);
		}
		else
		{
			Insert(new_fileinfo);
		}

		MFile::DeleteL(Net_Thumb(Local_Net(filename)));

	}
	catch(std::exception& e)
	{
		log << _T("[Watcher] Modify Error : ") << MCodeChanger::_CCL(e.what()) << log.endl();
	}
	catch (CppSQLite3Exception& e)
	{
		log << _T("[Watcher] Modify Error : ") << MCodeChanger::_CCL(e.errorMessage()) << log.endl();
	}
	catch(...)
	{
		log << _T("[Watcher] Modify Error") << log.endl();
	}}
void netvolume::OnRename(tstring oldFileName_org, tstring newFileName_org)
{
	boost::replace_all(oldFileName_org, _T("\\"), _T("/"));
	boost::replace_all(newFileName_org, _T("\\"), _T("/"));
#ifdef _DEBUG
	log << _T("[Call Watcher] Rename :") << oldFileName_org << _T(" -> ") << newFileName_org << log.endl();
#endif

	try
	{
		_tpath path(root_path);
		path /= newFileName_org; path = Utility::refinepath(path);

		_tpath path1(root_path);
		path1/=oldFileName_org;		path1 = Utility::refinepath(path1);
		tstring oldFilename=path1.c_str();
		_tpath path2(root_path);
		path2/=newFileName_org;		path2 = Utility::refinepath(path2);
		tstring newFilename=path2.c_str();

		net_watcher_.RemoveModify(WATCH_RENAME,oldFilename,newFilename);

		if (!boost::filesystem::is_directory(path) 
			&& !config_.Compare(FILE_EXTENSIONS,MCodeChanger::_CCU(MFile::GetFileExtL(newFileName_org))))
			return;

		if (net_watcher_.ChecknRemove(WATCH_RENAME,oldFilename,newFilename))
			return;
		log << _T("[Watcher] Rename :") << oldFilename << _T(" -> ") << newFilename << log.endl();

		if (boost::filesystem::is_directory(path2))
			MoveFolder(Local_Net(oldFilename),Local_Net(newFilename));
		else
			MoveFile(Local_Net(oldFilename),Local_Net(newFilename));
	}
	catch(std::exception& e)
	{
		log << _T("[Watcher] Rename Error : ") << MCodeChanger::_CCL(e.what()) << log.endl();
	}
	catch (CppSQLite3Exception& e)
	{
		log << _T("[Watcher] Rename Error : ") << MCodeChanger::_CCL(e.errorMessage()) << log.endl();
	}
	catch(...)
	{
		log << _T("[Watcher] Rename Error") << log.endl();
	}
}

void netvolume::StartWatch()
{
	if (
		boost::filesystem::path(config_.Get(THUMB_PATH)).string().find(boost::filesystem::path(config_.Get(DATA_PATH)).string())==0 ||
		boost::filesystem::path(config_.Get(DATA_ROOT_PATH)).string().find(boost::filesystem::path(config_.Get(DATA_PATH)).string())==0 ||
		boost::filesystem::path(config_.Get(TMP_PATH)).string().find(boost::filesystem::path(config_.Get(DATA_PATH)).string())==0 ||
		boost::filesystem::path(config_.Get(FAVORATE_PATH)).string().find(boost::filesystem::path(config_.Get(DATA_PATH)).string())==0
		)
		return;

    DWORD FILTER = 
  /*      FILE_NOTIFY_CHANGE_CREATION | 
        FILE_NOTIFY_CHANGE_DIR_NAME |
//		FILE_NOTIFY_CHANGE_LAST_WRITE |
		FILE_NOTIFY_CHANGE_SIZE |
        FILE_NOTIFY_CHANGE_FILE_NAME;
*/
//        FILE_NOTIFY_CHANGE_SECURITY |
        FILE_NOTIFY_CHANGE_CREATION |
//        FILE_NOTIFY_CHANGE_LAST_ACCESS |
        FILE_NOTIFY_CHANGE_LAST_WRITE |
        FILE_NOTIFY_CHANGE_SIZE |
//        FILE_NOTIFY_CHANGE_ATTRIBUTES |
        FILE_NOTIFY_CHANGE_DIR_NAME |
        FILE_NOTIFY_CHANGE_FILE_NAME;

	if (cFileSystemWatcher::Open(root_path,FILTER,true))
		log << _T("[Startup] Start watching : ") << root_path << _T("\n");
}
void netvolume::StopWatch()
{
	cFileSystemWatcher::Close();
}

void netvolume::Vacuum()
{
	log << _T("[Startup] Vacuum the database : ") << db_path.c_str() << _T("\n");
	execDML("vacuum;");
	log << _T("[Startup] ") << execScalar("SELECT count(*) from fileinfo;") << _T(" photographic files exist in ") << db_path.c_str() << _T("\n");
}

bool netvolume::Open(const tstring& path)
{
	if (!MFile::ExistsL(path)) 
	{
		log << path << _T(" does not exist\n");
		MFile::CreateFolderL(path);
		if (!MFile::ExistsL(path))
		{
			ThrowError(_T("Volume Not Exists"));
		}
		return false;
	}

	root_path=_tpath(path).c_str();

	tstring filename=MFile::leaf(_tpath(root_path));
	filename+=_T(".dat");
	db_path= Utility::refinepath(_tpath(root_path) / filename);


//	log << _T("Open database : ") << db_path.c_str() << _T("\n");

	SQL_DB::Open(MCodeChanger::_CCU(db_path.c_str()));
	sql_filename=filename;

	if (!SQL_DB::Check())
	{
		if (!SQL_DB::Check())
		{
			log << _T("Invalid Data Table\n");
			SQL_DB::Close();
		}
	}
	int iVersion;
	if (SQL_DB::CheckLowVersion(&iVersion))
	{
		log << _T("Old version of Database. Need to upgrade\n");
		if (UpgradeTable(iVersion))
			return true;
		else
		{
			SQL_DB::Close();
			return false;
		}
	}

	return true;
}
/*
template <typename T>
bool netvolume::UpgradeDate(const T& const_temp)
{
	std::string stQuery="SELECT DISTINCT count(date) from %s;";
	boost::format fmt(stQuery);
	fmt % T::get_tablename();

	int iTotal=execScalar(fmt.str().c_str());
#define UPGRADE_NUMBER 2000
	int iTotalLoop=iTotal/UPGRADE_NUMBER;

	int i;
//	time_t tmStart, tmEnd;

	for (i=0;i<iTotalLoop+1;i++)
	{
		boost::posix_time::ptime tmStart(boost::posix_time::second_clock::local_time());

		int iStart=i*UPGRADE_NUMBER;
		int iEnd=(i+1)*UPGRADE_NUMBER-1;
		if (i==iTotalLoop)
		{
			iEnd=iTotal;
		}
		std::string stQuery="SELECT DISTINCT date FROM %s LIMIT %d,%d;";
		boost::format fmt(stQuery);
		fmt % T::get_tablename()
			% iStart 
			% UPGRADE_NUMBER;

		CppSQLite3Query q=execQuery(fmt.str().c_str());

		BeginTransaction();
		while (!q.eof())
		{
			std::string Old_Date=q.fieldValue(0);
			std::string New_Date;

			boost::posix_time::ptime Time;
			try
			{
				Time=boost::posix_time::time_from_string(Old_Date);
			}
			catch (...)
			{
			}

			if (Time==boost::posix_time::ptime())
				New_Date="";
			else
			{
				New_Date=boost::posix_time::to_iso_extended_string(Time);
				boost::algorithm::replace_all(New_Date,"T"," ");
			}

			if (strcmp(Old_Date.c_str(),New_Date.c_str())!=0)
			{
				boost::format fmt("UPDATE %s SET date='%s' WHERE date='%s';");
				fmt % T::get_tablename() 
					% New_Date
					% Old_Date; 
				if (execDML(fmt.str().c_str())==0)
				{
					log << _T("Fail to upgrade : ") << MCodeChanger::_CCL(Old_Date) << _T(" -> ") << MCodeChanger::_CCL(New_Date) << _T("\n");
					return false;
				}
			}
			q.nextRow();
		}
		CommitTransaction();

		boost::posix_time::ptime tmEnd(boost::posix_time::second_clock::local_time());


		log << _T("Upgrade Database ( ") << (i+1) << _T(" / ") << (iTotalLoop+1) << _T(" ), ");

		if (i==iTotalLoop)
		{
			log << _T(" Finished\n");
		}
		else
		{
			boost::posix_time::time_duration tmInterval=tmEnd-tmStart;
			tmInterval*=(iTotal-(i+1)*UPGRADE_NUMBER);
			tmInterval/=UPGRADE_NUMBER;
			log << HString::Left(MCodeChanger::_CCL(boost::posix_time::to_simple_string(tmInterval)),8);
			log << _T(" left.\n");
		}
	}
	return true;
}

*/

template <typename T>
bool netvolume::UpgradeDate(const T& const_temp)
{
	std::string stQuery="SELECT count(*) from %s;";
	boost::format fmt(stQuery);
	fmt % T::get_tablename();

	int iTotal=execScalar(fmt.str().c_str());

	log << _T("Upgrade Database : ") << iTotal << _T(" records.\n");

#define UPGRADE_NUMBER 5000
	int iTotalLoop=iTotal/UPGRADE_NUMBER;

	int i;
//	time_t tmStart, tmEnd;

	boost::posix_time::ptime tmStart(boost::posix_time::second_clock::local_time());
	for (i=0;i<iTotalLoop+1;i++)
	{

		int iStart=i*UPGRADE_NUMBER;
		int iEnd=(i+1)*UPGRADE_NUMBER-1;
		if (i==iTotalLoop)
		{
			iEnd=iTotal;
		}
		std::string stQuery="SELECT rowid,date FROM %s LIMIT %d,%d;";
		boost::format fmt(stQuery);
		fmt % T::get_tablename()
			% iStart 
			% UPGRADE_NUMBER;

		CppSQLite3Query q=execQuery(fmt.str().c_str());

		BeginTransaction();
		while (!q.eof())
		{
			__int64 rowid=_atoi64(q.fieldValue(0));
			std::string Old_Date=q.fieldValue(1);
			std::string New_Date;

			boost::posix_time::ptime Time;
			try
			{
				Time=boost::posix_time::time_from_string(Old_Date);
			}
			catch (...)
			{
			}

			if (Time==boost::posix_time::ptime())
				New_Date="";
			else
			{
				New_Date=boost::posix_time::to_iso_extended_string(Time);
				boost::algorithm::replace_all(New_Date,"T"," ");
			}

			if (strcmp(Old_Date.c_str(),New_Date.c_str())!=0)
			{
				boost::format fmt("UPDATE %s SET date='%s' WHERE rowid='%d';");
				fmt % T::get_tablename() 
					% New_Date
					% rowid; 
				if (execDML(fmt.str().c_str())==0)
				{
					log << _T("Fail to upgrade : ") << MCodeChanger::_CCL(Old_Date) << _T(" -> ") << MCodeChanger::_CCL(New_Date) << _T("\n");
					return false;
				}
			}
			q.nextRow();
		}
		CommitTransaction();

		boost::posix_time::ptime tmEnd(boost::posix_time::second_clock::local_time());


		log << _T("Upgrade Database ( ") << (i+1) << _T(" / ") << (iTotalLoop+1) << _T(" ), ");

		if (i==iTotalLoop)
		{
			log << _T(" Finished\n");
		}
		else
		{
			boost::posix_time::time_duration tmInterval=tmEnd-tmStart;
			tmInterval*=(iTotal-(i+1)*UPGRADE_NUMBER);
			tmInterval/=(i+1)*UPGRADE_NUMBER;
			log << HString::Left(MCodeChanger::_CCL(boost::posix_time::to_simple_string(tmInterval)),8);
			log << _T(" left.\n");
		}
	}
	return true;
}
/*
//		fileinfo_list f_list;
		std::vector<T> f_list;
		FindCommon(fmt.str(),f_list,const_temp);

		BeginTransaction();
		for (unsigned int j=0;j<f_list.size();j++)
		{
			boost::format fmt("UPDATE %s SET %s WHERE %s='%s';");
			fmt % T::get_tablename() % f_list[j].sql_set_values() % T::get_primary() % sql_helper::sql_escape(f_list[j].get_unique());
			if (execDML(fmt.str().c_str())!=1)
			{
				log << _T("Fail to upgrade : ") << Net_Local(f_list[j].get_unique()) << _T("\n");
				return false;
			}
		}
		CommitTransaction();
		log << _T("Upgrade Database ( ") << i << _T(" / ") << iTotalLoop << _T(" )\n");
	}
	return true;
	*/

bool netvolume::UpgradeTable(int iOldVersion)
{
	log << _T("Start to upgrade the database.\n");
	if (iOldVersion==1)
	{
		tstring stBackupPath;
		if (!Utility::BackupFile(db_path.c_str(),stBackupPath))
		{
			log << _T("## BACKUP THE OLD VERSION DATABASE FILE : ") << stBackupPath << _T("\n");
			log << _T("Backup Fails\n");
			return false;
		}

		try
		{

			log << _T("## BACKUP THE OLD VERSION DATABASE FILE : ") << stBackupPath << _T("\n");
			log << _T("1) Fileinfo DB\n");
			if (!UpgradeDate(fileinfo()))
			{
				SQL_DB::Close();
				if (!Utility::RedoBackupFile(db_path.c_str(),stBackupPath))
					log << _T("## RESTORE THE DATABASE FAILS. RENAME THE OLD DATABASE ( ") << stBackupPath << _T(" TO ") << db_path.c_str() << _T(" MANUALLY.\n");
				return false;
			}
			log << _T("2) Comment DB\n");
			if (!UpgradeDate(comment()))
			{
				SQL_DB::Close();
				if (!Utility::RedoBackupFile(db_path.c_str(),stBackupPath))
					log << _T("## RESTORE THE DATABASE FAILS. RENAME THE OLD DATABASE ( ") << stBackupPath << _T(" TO ") << db_path.c_str() << _T(" MANUALLY.\n");
				return false;
			}

			// Add New DB

			log << _T("3) Add CustomField DB\n");
			execDML(customfield::delete_sql_table());
			execDML(customfield::create_sql_table());
//			log << _T("4) Add SearchHistory DB\n");
//			execDML(searchhistory::create_sql_table());
//			log << _T("5) Add SQLLog DB\n");
//			execDML(sqllog::create_sql_table());

			log << _T("4) Update the Privilege Column.\n");
			execDML("BEGIN TRANSACTION;");

			execDML("CREATE TEMPORARY TABLE `fileinfo_backup`(netpath TEXT UNIQUE,netdir TEXT,groupid TEXT,userid TEXT,date TEXT,diagnosis TEXT,icd10 TEXT,patientid TEXT,patientname TEXT,isdir TEXT);");
			execDML("INSERT INTO `fileinfo_backup` SELECT netpath,netdir,groupid,userid,date,diagnosis,icd10,patientid,patientname,isdir FROM `fileinfo`;");
			execDML("DROP TABLE IF EXISTS `fileinfo`;");
			execDML("DROP INDEX IF EXISTS `index_fileinfo`;");
			execDML(fileinfo::create_sql_table());
			execDML("INSERT INTO `fileinfo`(netpath,netdir,groupid,userid,date,diagnosis,icd10,patientid,patientname,isdir) SELECT netpath,netdir,groupid,userid,date,diagnosis,icd10,patientid,patientname,isdir FROM fileinfo_backup;");
			execDML("DROP TABLE `fileinfo_backup`;");

			execDML("UPDATE `fileinfo` SET userpriv=3,grouppriv=3,otherpriv=0,attribute=0;");

			execDML("CREATE TEMPORARY TABLE `comment_backup`(netpath TEXT,date TEXT,detail TEXT,userid TEXT,groupid TEXT);");
			execDML("INSERT INTO `comment_backup` SELECT netpath,date,detail,userid,groupid FROM `comment`;");
			execDML("DROP TABLE IF EXISTS `comment`;");
			execDML("DROP INDEX IF EXISTS `index_comment`;");
			execDML(comment::create_sql_table());
			execDML("INSERT INTO `comment`(netpath,date,detail,userid,groupid) SELECT netpath,date,detail,userid,groupid FROM comment_backup;");
			execDML("DROP TABLE `comment_backup`;");

			execDML("UPDATE `comment` SET userpriv=3,grouppriv=3,otherpriv=0;");

			execDML("COMMIT;");

			if (!SQL_DB::UpdateVersionInfo())
			{
				SQL_DB::Close();
				if (!Utility::RedoBackupFile(db_path.c_str(),stBackupPath))
					log << _T("## RESTORE THE DATABASE FAILS. RENAME THE OLD DATABASE ( ") << stBackupPath << _T(" TO ") << db_path.c_str() << _T(" MANUALLY.\n");
				return false;
			}

			log << _T("Finished to upgrade all database.\n");
		}
		catch (CppSQLite3Exception& e)
		{
			log << MCodeChanger::_CCL(e.errorMessage()) << _T("\n");
				SQL_DB::Close();
				if (!Utility::RedoBackupFile(db_path.c_str(),stBackupPath))
					log << _T("## RESTORE THE DATABASE FAILS. RENAME THE OLD DATABASE ( ") << stBackupPath << _T(" TO ") << db_path.c_str() << _T(" MANUALLY.\n");
			return false;
		}
		catch (std::exception& e)
		{
			log << MCodeChanger::_CCL(e.what()) << _T("\n");
				SQL_DB::Close();
				if (!Utility::RedoBackupFile(db_path.c_str(),stBackupPath))
					log << _T("## RESTORE THE DATABASE FAILS. RENAME THE OLD DATABASE ( ") << stBackupPath << _T(" TO ") << db_path.c_str() << _T(" MANUALLY.\n");
			return false;
		}
		catch(...)
		{
				SQL_DB::Close();
				if (!Utility::RedoBackupFile(db_path.c_str(),stBackupPath))
					log << _T("## RESTORE THE DATABASE FAILS. RENAME THE OLD DATABASE ( ") << stBackupPath << _T(" TO ") << db_path.c_str() << _T(" MANUALLY.\n");
			return false;
		}
		return true;
	}
	else
	{
		log << _T("Unknown version : ") << iOldVersion << _T("\n");
		return false;
	}
}

tstring netvolume::GetRootPath() const
{
	return root_path;
}
tstring netvolume::GetVolName() const  // c:/aaaa/bbb --> bbb
{
	return MFile::leaf(_tpath(GetRootPath()));
	/*
	std::vector<tstring> split_vec;
	tstring path=_tpath(GetRootPath()).c_str();
	boost::split(split_vec,GetRootPath(),boost::is_any_of(_T("/")));
	return split_vec.back();
	*/
//	return _tpath(GetRootPath()).filename().c_str();
}

void netvolume::CreateTable()
{
	log<< _T("Build SQL Volume Information\n");

	BeginTransaction();
	execDML(comment::create_sql_table());
	execDML(fileinfo::create_sql_table());
	execDML(customfield::create_sql_table());
//	execDML(searchhistory::create_sql_table());
//	execDML(sqllog::create_sql_table());

	CommitTransaction();
}
void netvolume::DeleteTable()
{
	log<< _T("Reset SQL Volume Information\n");
	BeginTransaction();
	SQL_DB::DeleteTable(fileinfo::get_tablename());
	SQL_DB::DeleteTable(comment::get_tablename());
	SQL_DB::DeleteTable(customfield::get_tablename());
//	SQL_DB::DeleteTable(searchhistory::get_tablename());
//	SQL_DB::DeleteTable(sqllog::get_tablename());

	CommitTransaction();
}
bool netvolume::GetFileInfo(const std::string& stPath,fileinfo& result) 
{return GetInfo_from_Primary(stPath,result);}

void netvolume::UpdateDiagnosis(const dx_list& dx_from,const dx_list& dx_to)
{
	if (dx_from.size()!=dx_to.size())
		return;

	BeginTransaction();

	for (unsigned int i=0;i<dx_from.size();i++)
	{
		if (dx_from[i]==diagnosis())
		{
		}
		else
		{
			std::string stQuery="UPDATE %s SET %s WHERE %s;";

			boost::format fmt(stQuery);
			fmt % fileinfo::get_tablename()
				% dx_to[i].sql_set_values()
				% dx_from[i].sql_set_values(" AND ");

//			log << MCodeChanger::_CCL(fmt.str());
			execDML(fmt.str().c_str());
		}
	}

	CommitTransaction();
}


void netvolume::FindFile(const std::vector<std::string>& Field_list,const std::vector<std::string>& Keyword_list,fileinfo_list& f_list,bool bExact)
{
	if (Field_list.size()!=Keyword_list.size() || Keyword_list.size()==0) return;

	std::string stQuery="SELECT * FROM %s WHERE (";

	for (unsigned int i=0;i<Field_list.size();i++)
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
	boost::algorithm::replace_last(stQuery,"OR ",") AND isdir='0';");

	boost::format fmt(stQuery);
	fmt % fileinfo::get_tablename();

	for (unsigned int i=0;i<Field_list.size();i++)
	{
		fmt % Field_list[i] % sql_helper::sql_escape(Keyword_list[i]);
	}
	FindCommon(fmt.str(),f_list,fileinfo());
}

void netvolume::FindFile(const std::string& stKeyword,fileinfo_list& f_list,bool bExact)
{
	std::string stQuery;
	if (bExact)
		stQuery="SELECT * FROM %s WHERE %s='%s' AND isdir='0';";
	else
		stQuery="SELECT * FROM %s WHERE %s LIKE '%%%s%%' AND isdir='0';";

	boost::format fmt(stQuery);
	fmt % fileinfo::get_tablename() % fileinfo::get_primary() % sql_helper::sql_escape(stKeyword);	

	FindCommon(fmt.str(),f_list,fileinfo());
}

void netvolume::FindFile_by_Date(const std::string& stFrom,const std::string& stTo,fileinfo_list& f_list)
{
	std::string stQuery;
	stQuery="SELECT * FROM %s WHERE date>='%s' AND date<='%s';";

	boost::format fmt(stQuery);
	fmt % fileinfo::get_tablename() 
		% sql_helper::sql_escape(stFrom)
		% sql_helper::sql_escape(stTo);

	FindCommon(fmt.str(),f_list,fileinfo());
}
void netvolume::FindFile_byQuery(const std::string& stQuery,const std::vector<bool>& bMask,fileinfo_list& f_list)
{
	std::string stFileInfoQuery=Interprete(stQuery,bMask,false);
	std::string stCommentQuery=Interprete(stQuery,bMask,true);

//	boost::split(split_vec,config_.Get(DATA_PATH),boost::is_any_of(","));

	std::string stFinalQuery="SELECT * FROM %s WHERE (%s) AND isdir='0' UNION SELECT %s.* from %s INNER JOIN %s WHERE %s.%s=%s.%s AND (%s) AND isdir='0' LIMIT %d;";

	boost::format fmt(stFinalQuery);
	fmt 
		% fileinfo::get_tablename()
		% stFileInfoQuery
		% fileinfo::get_tablename()
		% comment::get_tablename()
		% fileinfo::get_tablename()
		% comment::get_tablename()
		% fileinfo::get_primary()
		% fileinfo::get_tablename()
		% fileinfo::get_primary()
		% stCommentQuery
		% config_.GetInt(MAX_SEARCH_RESULT_NUMBER);

	FindCommon(fmt.str(),f_list,fileinfo());
}


std::string netvolume::GetQueryWhere(const std::string& stTableName,const std::vector<std::string>& Field_list,const std::vector<std::string>& Keyword_list)
{
	if (Field_list.size()!=Keyword_list.size() || Keyword_list.size()==0) return "";

	std::string stQuery="(";

	for (unsigned int i=0;i<Field_list.size();i++)
	{
		stQuery+="%s.%s LIKE '%%%s%%' OR ";
	}
	boost::algorithm::replace_last(stQuery," OR ",")");

	boost::format fmt(stQuery);
	for (unsigned int i=0;i<Field_list.size();i++)
	{
		fmt % stTableName
			% Field_list[i]
			% sql_helper::sql_escape(Keyword_list[i]);
	}
	return fmt.str();
}
std::string netvolume::GetQueryField(const std::string& stSearch,const std::vector<bool>& bMask,bool bSearchComment)
{
	int iFieldCharLoc=stSearch.find("[");
	if (stSearch[stSearch.length()-1]==']' && iFieldCharLoc!=std::string::npos)
	{
		std::string stField=HString::Mid(stSearch,iFieldCharLoc+1,stSearch.length()-2-iFieldCharLoc);
//		stField=HString::Left(stField,stField.length()-1);
		boost::algorithm::to_upper(stField);

		if (strcmp(stField.c_str(),"ID")==0)
		{
			std::string stFieldData=fileinfo::get_tablename();
			std::string stAdd=HString::Left(stSearch,iFieldCharLoc);
			if (stAdd[0]=='\"' && stAdd[stAdd.length()-1]=='\"')
				stAdd=HString::Mid(stAdd,1,stAdd.length()-2);
			if (stAdd.length()!=0)
			{
				stFieldData+=".patientid LIKE '%";
				stFieldData+=stAdd;
				stFieldData+="%'";
				return stFieldData;
			}
		}
		if (strcmp(stField.c_str(),"NAME")==0)
		{
			std::string stFieldData=fileinfo::get_tablename();
			std::string stAdd=HString::Left(stSearch,iFieldCharLoc);
			if (stAdd[0]=='\"' && stAdd[stAdd.length()-1]=='\"')
				stAdd=HString::Mid(stAdd,1,stAdd.length()-2);
			if (stAdd.length()!=0)
			{
				stFieldData+=".patientname LIKE '%";
				stFieldData+=stAdd;
				stFieldData+="%'";
				return stFieldData;
			}
		}
		if (strcmp(stField.c_str(),"DX")==0)
		{
			std::string stFieldData=fileinfo::get_tablename();
			std::string stAdd=HString::Left(stSearch,iFieldCharLoc);
			if (stAdd[0]=='\"' && stAdd[stAdd.length()-1]=='\"')
				stAdd=HString::Mid(stAdd,1,stAdd.length()-2);
			if (stAdd.length()!=0)
			{
				stFieldData+=".diagnosis LIKE '%";
				stFieldData+=stAdd;
				stFieldData+="%'";
				return stFieldData;
			}
		}
		if (strcmp(stField.c_str(),"ICD")==0)
		{
			std::string stFieldData=fileinfo::get_tablename();
			std::string stAdd=HString::Left(stSearch,iFieldCharLoc);
			if (stAdd[0]=='\"' && stAdd[stAdd.length()-1]=='\"')
				stAdd=HString::Mid(stAdd,1,stAdd.length()-2);
			if (stAdd.length()!=0)
			{
				stFieldData+=".icd10 LIKE '%";
				stFieldData+=stAdd;
				stFieldData+="%'";
				return stFieldData;
			}
		}
		if (strcmp(stField.c_str(), "<") == 0)
		{
			std::string stFieldData = fileinfo::get_tablename();
			std::string stAdd = HString::Left(stSearch, iFieldCharLoc);
			if (stAdd[0] == '\"' && stAdd[stAdd.length() - 1] == '\"')
				stAdd = HString::Mid(stAdd, 1, stAdd.length() - 2);
			if (stAdd.length() != 0)
			{
				stFieldData += ".date >= '";
				stAdd += "-01-01 00:00:00";
				stFieldData += stAdd;
				stFieldData += "'";
				return stFieldData;
			}
		}
		if (strcmp(stField.c_str(), ">") == 0)
		{
			std::string stFieldData = fileinfo::get_tablename();
			std::string stAdd = HString::Left(stSearch, iFieldCharLoc);
			if (stAdd[0] == '\"' && stAdd[stAdd.length() - 1] == '\"')
				stAdd = HString::Mid(stAdd, 1, stAdd.length() - 2);
			if (stAdd.length() != 0)
			{
				stFieldData += ".date <= '";
				stAdd += "-12-31 23:99:99";
				stFieldData += stAdd;
				stFieldData += "'";
				return stFieldData;
			}
		}
	}

	std::vector<std::string> Field_list;
	std::vector<std::string> Keyword_list;

//	if (config_.Compare(SEARCH_PATH,1))
	if (bMask[0])
	{Field_list.push_back(fileinfo::get_primary());Keyword_list.push_back(stSearch);}

//	if (config_.Compare(SEARCH_ID,1))
	if (bMask[1])
	{Field_list.push_back("patientid");Keyword_list.push_back(stSearch);}

//	if (config_.Compare(SEARCH_NAME,1))
	if (bMask[2])
	{Field_list.push_back("patientname");Keyword_list.push_back(stSearch);}

//	if (config_.Compare(SEARCH_DIAGNOSIS,1))
	if (bMask[3])
	{Field_list.push_back("diagnosis");Keyword_list.push_back(stSearch);}

//	if (config_.Compare(SEARCH_ICD10,1))
	if (bMask[4])
	{Field_list.push_back("icd10");Keyword_list.push_back(stSearch);}

	if (bSearchComment)
	{
		std::string result=GetQueryWhere(fileinfo::get_tablename(),Field_list,Keyword_list);
		std::string stReplaceTo=" OR %s.detail LIKE '%%%s%%')";
	
		boost::format fmt(stReplaceTo);
		fmt % comment::get_tablename()
			% stSearch;

		boost::algorithm::replace_last(result,")",fmt.str());
		return result;
	}
	else
		return GetQueryWhere(fileinfo::get_tablename(),Field_list,Keyword_list);
}
std::string netvolume::Interprete(const std::string& stQuery_Org,const std::vector<bool>& bMask,bool bComment)
{
	std::string stQuery=stQuery_Org;
	boost::algorithm::trim(stQuery);

	std::string result;
	int iPosition=0;

	std::string stRemain=stQuery;

	bool bANDorOR=false;
	while (stRemain.length()>0)
	{
		int iDone=0;
		if (stRemain[0]=='(')
		{
			int iEnd=stRemain.find(")");
			if (iEnd!=std::string::npos)
			{
				iDone=iEnd+1;
				result+="(";
				result+=Interprete(HString::Mid(stRemain,1,iEnd-1),bMask,bComment);
				result+=")";
				bANDorOR=false;
			}
		}
		if (strcmp(HString::Left(stRemain,5).c_str()," AND ")==0)
		{
			iDone=5;
			result+=" AND ";
			bANDorOR=true;
		}
		if (strcmp(HString::Left(stRemain,4).c_str()," OR ")==0)
		{
			iDone=4;
			result+=" OR ";
			bANDorOR=true;
		}
		if (stRemain[0]==' ' && iDone==0)
		{
			iDone=1;
		}

		if (iDone==0)
		{
			int iSpacePos;

			if (iPosition!=0 && !bANDorOR) result+=" OR ";

			if (stRemain[0]=='"')
			{
				int iEnd=HString::Right(stRemain,stRemain.length()-1).find("\"");

				if (iEnd<(stRemain.length()-1))
				{
					if (stRemain[iEnd+2]=='[' && HString::Right(stRemain,stRemain.length()-1).find("]")!=std::string::npos)
					{
						int iFieldEnd=HString::Right(stRemain,stRemain.length()-iEnd).find("]");
						iSpacePos=iEnd+iFieldEnd;
						iDone=iSpacePos+1;

						result+=GetQueryField(HString::Mid(stRemain,1,iSpacePos),bMask,bComment);
					}
				}

				if (iDone==0)
				{
					if (iEnd==std::string::npos)
					{
						iSpacePos=stRemain.length();
						iDone=iSpacePos+1;
					}
					else
					{
						iSpacePos=iEnd;
						iDone=iSpacePos+2;
					}
					result+=GetQueryField(HString::Mid(stRemain,1,iSpacePos),bMask,bComment);
				}
			}
			else
			{
				iSpacePos=stRemain.find(" ");
				if (iSpacePos==std::string::npos)
					iSpacePos=stRemain.length();

				result+=GetQueryField(HString::Left(stRemain,iSpacePos),bMask,bComment);
				iDone=iSpacePos;
			}
			bANDorOR=false;
		}
		iPosition+=iDone;
		stRemain=HString::Right(stRemain,stRemain.length()-iDone);
	}
	return result;
}


void netvolume::FindbyDir(const std::string& stKeyword,fileinfo_list& f_list,bool bExact,bool bFileOnly)
{
	std::string stQuery;
	if (bExact)
		stQuery="SELECT * FROM %s WHERE netdir='%s'";
	else
		stQuery="SELECT * FROM %s WHERE netdir LIKE '%s%%'";

	if (bFileOnly)
		stQuery+=" AND isdir='0'";

	stQuery+=";";

	boost::format fmt(stQuery);
	fmt % fileinfo::get_tablename() % sql_helper::sql_escape(stKeyword);	

	FindCommon(fmt.str(),f_list,fileinfo());
}
void netvolume::FindPath(const std::string& stKeyword,fileinfo_list& f_list,bool bExact)
{
	std::string stQuery;
	if (bExact)
		stQuery="SELECT * FROM %s WHERE %s='%s';";
	else
		stQuery="SELECT * FROM %s WHERE %s LIKE '%%%s%%';";

	boost::format fmt(stQuery);
	fmt % fileinfo::get_tablename() % fileinfo::get_primary() % sql_helper::sql_escape(stKeyword);	

	FindCommon(fmt.str(),f_list,fileinfo());
}
void netvolume::FindComment_by_Path(const std::vector<std::string>& stKeyword_list,comment_list& c_list,bool bExact)
{
/*	std::string stQuery;
	if (bExact)
		stQuery="SELECT * FROM %s WHERE %s='%s';";
	else
		stQuery="SELECT * FROM %s WHERE %s LIKE '%%%s%%';";

	boost::format fmt(stQuery);
	fmt % comment::get_tablename() % comment::get_primary() % stKeyword;	
*/
	std::vector<std::string> stField_list;
	for (unsigned int i=0;i<stKeyword_list.size();i++)
	{
		stField_list.push_back(comment::get_primary());
	}
	Find(comment::get_tablename(),stField_list,stKeyword_list,c_list,comment(),true);
//	FindCommon(fmt.str(),c_list,comment());
}
void netvolume::FindComment_by_Comment(const std::string& stKeyword,comment_list& c_list,bool bExact)
{
	std::string stQuery;
	if (bExact)
		stQuery="SELECT * FROM %s WHERE %s='%s';";
	else
		stQuery="SELECT * FROM %s WHERE %s LIKE '%%%s%%';";

	boost::format fmt(stQuery);
	fmt % comment::get_tablename() % "detail" % sql_helper::sql_escape(stKeyword);	

	FindCommon(fmt.str(),c_list,comment());
}

bool netvolume::CheckRootPriv(const std::string & stUserID,const _tpath& dir_,bool bWrite)
{
	if (strcmp(stUserID.c_str(),SUPER_ADMIN_ID)==0) return true;

	fileinfo dir_info;
	if (!GetInfo_from_Primary(MCodeChanger::_CCU(dir_.root_path().c_str()),dir_info))
		return false;

	if (CheckPriv(stUserID,dir_info,bWrite))
		return true;
	else
		return false;
}
/*
void netvolume::DeleteFolder(const std::string& stNetPath)
{
	fileinfo_list f_list;
	Find(stNetPath,f_list,fileinfo(),true);
	for (unsigned int i=0;i<f_list.size();i++)
	{
		if (f_list[i].IsDir())
			DeleteFolder(f_list[i].GetNetPath());
		else
			Delete(f_list[i]);
	}
}
*/
bool netvolume::IsPart(const tstring& full_path)
{
	if (full_path.length() < root_path.length()) return false;

	tstring new_full_path=_tpath(full_path).c_str();
	tstring new_partial_path=_tpath(root_path).c_str();

	if (new_full_path.find(new_partial_path)==std::string::npos)
		return false;
	else
		return true;
}



bool netvolume::LoadMetatag(fileinfo& fileinfo_)
{
	return Utility::LoadMetatag(Net_Local(fileinfo_.GetNetPath()),fileinfo_.Time);
/*
	FILE* hFile=_tfopen(Net_Local(fileinfo_.GetNetPath()).c_str(),_T("rb"));

	EXIFINFO m_exifinfo;

	if (hFile){

		memset(&m_exifinfo,0,sizeof(EXIFINFO));

		Cexif exif(&m_exifinfo);
		exif.DecodeExif(hFile);

		fclose(hFile);

		if (m_exifinfo.IsExif) 
		{

			try{
			std::string str=m_exifinfo.DateTime;
			std::vector<std::string> split_vec1,split_vec2,split_vec3;
			boost::split(split_vec1,str,boost::is_any_of(" "));
			std::string s1,s2,s3,s4,s5,s6;
			boost::split(split_vec2,split_vec1[0],boost::is_any_of(":"));
			if (split_vec2.size()!=3) return false;
			s1=split_vec2[0];
			s2=split_vec2[1];
			s3=split_vec2[2];
			boost::split(split_vec3,split_vec1[1],boost::is_any_of(":"));

			if (split_vec3.size()!=3) return false;
			s4=split_vec3[0];
			s5=split_vec3[1];
			s6=split_vec3[2];

			std::string time;
			boost::format fmt("%s-%s-%s %s:%s:%s.000");
			fmt % s1 %s2 %s3 %s4 %s5 %s6;
			
			fileinfo_.Time=boost::posix_time::time_from_string(fmt.str());

			return true;

			}
			catch (std::exception& e)
			{
				e.what();
				return false;
			}
		}
		else
			return false;
	}
	return false;
	*/
}

bool netstorage::LoadMetatag(fileinfo& fileinfo_)
{
	return Utility::LoadMetatag(Net_Local(fileinfo_.GetNetPath()),fileinfo_.Time);
/*
	FILE* hFile=_tfopen(Net_Local(fileinfo_.GetNetPath()).c_str(),_T("rb"));

	EXIFINFO m_exifinfo;

	if (hFile){

		memset(&m_exifinfo,0,sizeof(EXIFINFO));

		Cexif exif(&m_exifinfo);
		exif.DecodeExif(hFile);

		fclose(hFile);

		if (m_exifinfo.IsExif) 
		{

			try{
			std::string str=m_exifinfo.DateTime;
			std::vector<std::string> split_vec1,split_vec2,split_vec3;
			boost::split(split_vec1,str,boost::is_any_of(" "));
			std::string s1,s2,s3,s4,s5,s6;
			boost::split(split_vec2,split_vec1[0],boost::is_any_of(":"));
			if (split_vec2.size()!=3) return false;
			s1=split_vec2[0];
			s2=split_vec2[1];
			s3=split_vec2[2];
			boost::split(split_vec3,split_vec1[1],boost::is_any_of(":"));

			if (split_vec3.size()!=3) return false;
			s4=split_vec3[0];
			s5=split_vec3[1];
			s6=split_vec3[2];

			std::string time;
			boost::format fmt("%s-%s-%s %s:%s:%s.000");
			fmt % s1 %s2 %s3 %s4 %s5 %s6;
			
			fileinfo_.Time=boost::posix_time::time_from_string(fmt.str());

			return true;

			}
			catch (std::exception& e)
			{
				e.what();
				return false;
			}
		}
		else
			return false;
	}
	return false;
	*/
}

fileinfo netstorage::CreateFileInfoU(const std::string& str,const std::string& stUserID) // UTF-8
{
	return CreateFileInfo(MCodeChanger::_CCL(str),stUserID);
}
fileinfo netstorage::CreateFileInfoL(const tstring& str,const std::string& stUserID) // local
{
	return CreateFileInfo(_tpath(str),stUserID);
}
fileinfo netvolume::CreateFileInfo(const _tpath& stLocalPath,const std::string& stUserID) // local
{
	std::string Path,isDir,Dir;
	tstring path1=stLocalPath.c_str();
	tstring path2=_tpath(GetRootPath()).c_str();
	boost::replace_all(path1, _T("\\"), _T("/"));
	boost::replace_all(path2, _T("\\"), _T("/"));

	if (boost::algorithm::find_first(path1,path2))
	{
		boost::algorithm::replace_first(path1,path2,GetVolName());
		Path=MCodeChanger::_CCU(path1);
		if (bfs::is_directory(stLocalPath))
		{
			isDir="1";
			boost::algorithm::replace_last(path1,MFile::leaf(stLocalPath),_T(""));
			boost::algorithm::replace_last(path1,_T("/"),_T(""));
			Dir=MCodeChanger::_CCU(path1);
		}
		else
		{
			isDir="0";
			tstring filename=stLocalPath.filename().c_str();
			boost::algorithm::replace_last(path1,filename,_T(""));
			boost::algorithm::replace_last(path1,_T("/"),_T(""));
			Dir=MCodeChanger::_CCU(path1);
		}
	}
	return fileinfo(Path,Dir,isDir,owner(stUserID));
}
fileinfo netstorage::CreateFileInfo(const _tpath& stLocalPath,const std::string& stUserID) // local
{
	int iVol=GetVolumeNumber(stLocalPath.c_str());
	if (iVol==-1) return fileinfo();
	return netvolume_ptr_list_[iVol]->CreateFileInfo(stLocalPath,stUserID);
}
std::string netvolume::GetNetDir(const _tpath& stLocalPath)
{
	tstring path1=stLocalPath.c_str();
	tstring path2=_tpath(GetRootPath()).c_str();
	boost::replace_all(path1, _T("\\"), _T("/"));
	boost::replace_all(path2, _T("\\"), _T("/"));

	if (boost::algorithm::find_first(path1,path2))
	{
		boost::algorithm::replace_first(path1,path2,GetVolName());
		if (bfs::is_directory(stLocalPath))
		{
			boost::algorithm::replace_last(path1,MFile::leaf(stLocalPath),_T(""));
			boost::algorithm::replace_last(path1,_T("/"),_T(""));
			return MCodeChanger::_CCU(path1);
		}
		else
		{
			tstring filename=stLocalPath.filename().c_str();
			boost::algorithm::replace_last(path1,filename,_T(""));
			boost::algorithm::replace_last(path1,_T("/"),_T(""));
			return MCodeChanger::_CCU(path1);
		}
	}
	ThrowError(_T("Invalid Path"),stLocalPath.c_str());
	return "";
}

std::string netstorage::GetNetDir(const _tpath& stLocalPath)
{
	int iVol=GetVolumeNumber(stLocalPath.c_str());
	if (iVol==-1) return "";

	return netvolume_ptr_list_[iVol]->GetNetDir(stLocalPath);

/*	tstring path1=stLocalPath.string();
	tstring path2=_tpath(netvolume_ptr_list_[iVol]->GetRootPath()).string();

	if (boost::algorithm::find_first(path1,path2))
	{
		boost::algorithm::replace_first(path1,path2,netvolume_ptr_list_[iVol]->GetVolName());
		if (bfs::is_directory(stLocalPath))
		{
			boost::algorithm::replace_first(path1,stLocalPath.filename(),_T(""));
			boost::algorithm::replace_last(path1,_T("/"),_T(""));
			return MCodeChanger::_CCU(path1);
		}
		else
		{
			tstring filename=stLocalPath.filename();
			boost::algorithm::replace_first(path1,filename,_T(""));
			boost::algorithm::replace_last(path1,_T("/"),_T(""));
			return MCodeChanger::_CCU(path1);
		}
	}
	ThrowError(_T("Invalid Path"),stLocalPath.string());
	return "";*/
}

bool netstorage::Check()
{
	std::vector<std::string> param_list;
	config_.SplitParams(DATA_PATH,param_list);

	for (unsigned int i=0;i<param_list.size();i++)
	{
		tstring stPath=MCodeChanger::_CCL(param_list[i]);
		if (!MFile::ExistsL(stPath) || _tcscmp(MFile::leaf(_tpath(stPath)).c_str(),_T("/"))==0)
		{
			log << stPath << _T(" is invalid folder\n");
			log << _T("Check DATA_PATH in the config.txt\n");
			return false;
		}
	}
	return true;
}
void netstorage::Open()
{
	std::vector<std::string> param_list;
	config_.SplitParams(DATA_PATH,param_list);

	for (unsigned int i=0;i<param_list.size();i++)
	{
		AddVolume(MCodeChanger::_CCL(param_list[i]));
	}
}
void netstorage::Close()
{
	for (int i=0;i<GetSize();i++)
	{
		netvolume_ptr_list_[i]->Close();
		delete netvolume_ptr_list_[i];
		netvolume_ptr_list_.clear();
	}
}
void netstorage::Reset()
{
	Close();
	Open();
}
bool netstorage::IsAnyEmpty()
{
	for (int i=0;i<GetSize();i++)
	{
		if (netvolume_ptr_list_[i]->IsEmpty(fileinfo()))
			return true;
	}
	return false;
}

int netstorage::GetSize() {return (int)netvolume_ptr_list_.size();}
netvolume& netstorage::Vol(int i) 
{
	if (i>=GetSize())
		ThrowError(_T("Over Index"));
	return (*netvolume_ptr_list_[i]);
}
/*
bool netstorage::Check()
{
	for (int i=0;i<GetSize();i++)
	{
		if (!netvolume_ptr_list_[i]->Check()) return false;
	}
	return true;
}
*/
bool netstorage::AddVolume(const tstring& root_path)
{
	if (IsExistVolume(root_path))
		ThrowError(_T("Path Duplicated"),root_path);

	netvolume_ptr_list_.push_back(new netvolume(config_,log));
	bool bResult=netvolume_ptr_list_[netvolume_ptr_list_.size()-1]->Open(root_path);
	if (bResult)
		return true;
	else
	{
		log << _T("Fail to open ") << root_path << _T("\n");
		netvolume_ptr_list_.erase(netvolume_ptr_list_.end()-1);
		return false;
	}
//	netvolume_ptr_list_[0].Check();
}
void netstorage::DeleteVolume(const tstring& volname)
{
	for (int i=0;i<GetSize();i++)
	{
		if (_tcscmp(netvolume_ptr_list_[i]->GetVolName().c_str(),volname.c_str())==0)
		{
			delete netvolume_ptr_list_[i];
			netvolume_ptr_list_.erase(netvolume_ptr_list_.begin()+i);
			return;
		}
	}
	ThrowError(_T("Volume Not Exists"));
}

void netstorage::CreateTable()
{
	for (int i=0;i<GetSize();i++)
	{
		netvolume_ptr_list_[i]->CreateTable();
	}
}
void netstorage::DeleteTable()
{
	for (int i=0;i<GetSize();i++)
	{
		netvolume_ptr_list_[i]->DeleteTable();
	}
}

void netstorage::BeginTransaction()
{
	for (int i=0;i<GetSize();i++)
	{
		netvolume_ptr_list_[i]->BeginTransaction();
	}
}
void netstorage::CommitTransaction()
{
	for (int i=0;i<GetSize();i++)
	{
		netvolume_ptr_list_[i]->CommitTransaction();
	}
}

bool netstorage::IsExistVolume(const tstring& root_path)
{
	for (int i=0;i<GetSize();i++)
	{
		if (_tcscmp(netvolume_ptr_list_[i]->GetRootPath().c_str(),root_path.c_str())==0)
			return true;
	}
	return false;
}

bool netstorage::GetFileInfo(const std::string& stNetPath,fileinfo& result)
{
	for (int i=0;i<GetSize();i++)
	{
		if (netvolume_ptr_list_[i]->GetFileInfo(stNetPath,result)) return true;
	}
	return false;
}

void netstorage::FindFile(const std::string& stKeyword,fileinfo_list& f_list,bool bExact)
{
	for (int i=0;i<GetSize();i++)
	{
		netvolume_ptr_list_[i]->FindFile(stKeyword,f_list,bExact);
	}
}
void netstorage::FindFile(const std::vector<std::string>& Field_list,const std::vector<std::string>& Keyword_list,fileinfo_list& f_list,bool bExact)
{
	for (int i=0;i<GetSize();i++)
	{
		netvolume_ptr_list_[i]->FindFile(Field_list,Keyword_list,f_list,bExact);
	}
}
void netstorage::FindFile_by_Date(const std::string& stFrom,const std::string& stTo,fileinfo_list& f_list)
{
	for (int i=0;i<GetSize();i++)
	{
		netvolume_ptr_list_[i]->FindFile_by_Date(stFrom,stTo,f_list);
	}
}

void netstorage::FindFile_byQuery(const std::string& stQuery,const std::vector<bool>& bMask,fileinfo_list& f_list)
{
	for (int i=0;i<GetSize();i++)
	{
		netvolume_ptr_list_[i]->FindFile_byQuery(stQuery,bMask,f_list);
	}
}

void netstorage::FindbyDir(const std::string& stKeyword,fileinfo_list& f_list,bool bExact,bool bFileOnly)
{
	for (int i=0;i<GetSize();i++)
	{
		netvolume_ptr_list_[i]->FindbyDir(stKeyword,f_list,bExact,bFileOnly);
	}
}
void netstorage::FindPath(const std::string& stKeyword,fileinfo_list& f_list,bool bExact)
{
	for (int i=0;i<GetSize();i++)
	{
		netvolume_ptr_list_[i]->FindPath(stKeyword,f_list,bExact);
	}
}
void netstorage::FindComment_by_Path(const std::vector<std::string>& stKeyword_list,comment_list& c_list,bool bExact)
{
	for (int i=0;i<GetSize();i++)
	{
		netvolume_ptr_list_[i]->FindComment_by_Path(stKeyword_list,c_list,bExact);
	}
}
void netstorage::FindComment_by_Comment(const std::string& stKeyword,comment_list& c_list,bool bExact)
{
	for (int i=0;i<GetSize();i++)
	{
		netvolume_ptr_list_[i]->FindComment_by_Comment(stKeyword,c_list,bExact);
	}
}

bool netstorage::CheckRootPriv(const std::string&stCurrentUserID,const _tpath& dir_,bool bWrite)
{
	for (int i=0;i<GetSize();i++)
	{
		if (netvolume_ptr_list_[i]->CheckRootPriv(stCurrentUserID,dir_,bWrite)) return true;
	}
	return false;
}
void netstorage::Vacuum()
{
	for (int i=0;i<GetSize();i++)
	{
		netvolume_ptr_list_[i]->Vacuum();
	}
}

void netstorage::UpdateDiagnosis(const dx_list& dx_from,const dx_list& dx_to)
{
	for (int i=0;i<GetSize();i++)
	{
		netvolume_ptr_list_[i]->UpdateDiagnosis(dx_from,dx_to);
	}
}


std::string netvolume::Local_Net(const tstring& stLocalPath)
{
	_tpath temp1(stLocalPath);
	_tpath temp2(GetRootPath());

	tstring path1=temp1.c_str();
	tstring path2=temp2.c_str();
	boost::replace_all(path1, _T("\\"), _T("/"));
	boost::replace_all(path2, _T("\\"), _T("/"));

	if (boost::algorithm::find_first(path1,path2))
	{
		boost::algorithm::replace_first(path1,path2,GetVolName());
		return MCodeChanger::_CCU(path1);
	}
	return "";
}

std::string netstorage::Local_Net(const tstring& stLocalPath)
{
	std::string result;

	int iVol=GetVolumeNumber(stLocalPath);
	if (iVol==-1) return "";


	return netvolume_ptr_list_[iVol]->Local_Net(stLocalPath);
/*	_tpath temp2(netvolume_ptr_list_[iVol]->GetRootPath());

	tstring path1=temp1.string();
	tstring path2=temp2.string();

	if (boost::algorithm::find_first(path1,path2))
	{
		boost::algorithm::replace_first(path1,path2,netvolume_ptr_list_[iVol]->GetVolName());
		return MCodeChanger::_CCU(path1);
	}
	return "";*/
}

tstring netvolume::Net_Local(const std::string& stNetPath)
{
	_tpath path(MCodeChanger::_CCL(GetPath_s_Vol(stNetPath)));
	path= Utility::refinepath(GetRootPath() / path);
	return path.c_str();
}

tstring netstorage::Net_Local(const std::string& stNetPath)
{
//	_tpath path(MCodeChanger::_CCL(GetPath_s_Vol(stNetPath)));
	int iVol=GetVolumeNumber(GetVolumeName(stNetPath));
	if (iVol==-1) return _T("");

	return netvolume_ptr_list_[iVol]->Net_Local(stNetPath);
}
tstring netvolume::Net_Thumb(const std::string& stNetPath)
{
	_tpath path(MCodeChanger::_CCL(config_.Get(THUMB_PATH)));
	path/= MCodeChanger::_CCL(stNetPath);	path = Utility::refinepath(path);
	return path.c_str();
}
tstring netstorage::Net_Thumb(const std::string& stNetPath)
{
	_tpath path(MCodeChanger::_CCL(config_.Get(THUMB_PATH)));
	path/= MCodeChanger::_CCL(stNetPath);	path = Utility::refinepath(path);
	return path.c_str();
}
std::string netstorage::Thumb_Net(const tstring& stThumbPath)
{
	std::string result;

	_tpath temp1(stThumbPath);
	_tpath temp2(MCodeChanger::_CCL(config_.Get(THUMB_PATH)));

	tstring path1=temp1.c_str();
	tstring path2=temp2.c_str();
	boost::replace_all(path1, _T("\\"), _T("/"));
	boost::replace_all(path2, _T("\\"), _T("/"));

	if (boost::algorithm::find_first(path1,path2))
	{
		boost::algorithm::replace_first(path1,path2,_T(""));
		boost::algorithm::replace_first(path1,_T("/"),_T(""));
		return MCodeChanger::_CCU(path1);
	}
	return "";
}

bool netstorage::AddVirtual(const std::string& stNetPath,fileinfo fileinfo_)
{
	fileinfo_.stNetPath=stNetPath;
	if (Insert(fileinfo_)==1) 
		return true;
	else 
		return false;
}
int netstorage::GetVolumeNumber(const tstring& stLocalPath)
{
	if (GetSize()==0)
	{
		ThrowEmptyVol();return -1;
	}
	for (int i=0;i<GetSize();i++)
	{
		if (netvolume_ptr_list_[i]->IsPart(stLocalPath))
			return i;
	}
	ThrowError(_T("Invalid Path"),stLocalPath);
	return -1;
}
std::string netstorage::GetVolumeName(const std::string& stNetPath) // root
{
	std::vector<std::string> split_vec;
	boost::split(split_vec,stNetPath,boost::is_any_of("/"));
	return split_vec[0];
}

std::string netvolume::GetPath_s_Vol(std::string stNetPath)  //  /aa/bb.jpb
{
	boost::algorithm::replace_first(stNetPath,MCodeChanger::_CCU(GetVolName()),"");
	return stNetPath;
}
std::string netstorage::GetPath_s_Vol(std::string stNetPath)  //  /aa/bb.jpb
{
	boost::algorithm::replace_first(stNetPath,GetVolumeName(stNetPath),"");
	return stNetPath;
}
int netstorage::GetVolumeNumber(const std::string& stVolumeName)
{
	if (GetSize()==0)
	{
		ThrowEmptyVol();return -1;
	}
	for (int i=0;i<GetSize();i++)
	{
		if (_tcscmp(netvolume_ptr_list_[i]->GetVolName().c_str()
			,MCodeChanger::_CCL(stVolumeName).c_str())==0)
			return i;
	}
	ThrowInvalidVol(stVolumeName);
	return -1;
}
void netstorage::ThrowError(tstring stErrorMsg,const tstring& param)
{
	netvolume::ThrowError(stErrorMsg,param);
}
void netstorage::ThrowSQLInsertError(const std::string& stNetPath)
{
	netvolume::ThrowSQLInsertError(stNetPath);
//	ThrowError(_T("SQL Error(Insert)"),MCodeChanger::_CCL(stNetPath));
}
void netstorage::ThrowSQLUpdateError(const std::string& stNetPathFrom,const std::string& stNetPathTo)
{
	netvolume::ThrowSQLUpdateError(stNetPathFrom,stNetPathTo);
/*	std::string msg=stNetPathFrom;
	msg+="->";
	msg+=stNetPathTo;
	ThrowError(_T("SQL Error(Update)"),MCodeChanger::_CCL(msg));*/
}
void netstorage::ThrowSQLDeleteError(const std::string& stNetPath)
{
	netvolume::ThrowSQLDeleteError(stNetPath);
//	ThrowError(_T("SQL Error(Delete)"),MCodeChanger::_CCL(stNetPath));
}

void netvolume::ThrowSQLInsertError(const std::string& stNetPath)
{
	ThrowError(_T("SQL Error(Insert)"),MCodeChanger::_CCL(stNetPath));
}
void netvolume::ThrowSQLUpdateError(const std::string& stNetPathFrom,const std::string& stNetPathTo)
{
	std::string msg=stNetPathFrom;
	msg+="->";
	msg+=stNetPathTo;
	ThrowError(_T("SQL Error(Update)"),MCodeChanger::_CCL(msg));
}
void netvolume::ThrowSQLDeleteError(const std::string& stNetPath)
{
	ThrowError(_T("SQL Error(Delete)"),MCodeChanger::_CCL(stNetPath));
}



void netstorage::ThrowInvalidVol(const std::string& stVolName)
{
	ThrowError(_T("Invalid Volume"),MCodeChanger::_CCL(stVolName));
}
void netstorage::ThrowEmptyVol()
{
	ThrowError(_T("Volume Empty"));
}

void netstorage::ThrowAlreadyExist(const std::string& stNetPath)
{
	ThrowError(_T("File/Folder Already Exist"),MCodeChanger::_CCL(stNetPath));
}


void netpath::Open(const std::string& userid)
{
	stCurrentUserID=userid;

	if (config_.GetInt(MULTIUSER_SUPPORT)==1)
	{
		_tpath favorate_path=_tpath(MCodeChanger::_CCL(config_.Get(FAVORATE_PATH)));
		favorate_path /= MCodeChanger::_CCL(userid); favorate_path = Utility::refinepath(favorate_path);
		MFile::CreateFolder(favorate_path);
		AddVolume(favorate_path.c_str());
	}
	netstorage::Open();
}
void netpath::CreateTable()
{
	netstorage::CreateTable();
}

bool netpath::CheckRootPriv(const _tpath& dir_,bool bWrite)
{
	return netstorage::CheckRootPriv(stCurrentUserID,dir_,bWrite);
}

void netstorage::GetVariableType(const std::string& stNetpath,tstring& stPath,_tpath& _tPath,int& iVol)
{
	stPath=Net_Local(stNetpath);
	_tPath=_tpath(stPath);
	iVol=GetVolumeNumber(GetVolumeName(stNetpath));
	if (iVol==-1) 
	{
		ThrowInvalidVol(stNetpath);
	}
}
void netstorage::GetVariableType(const std::string& stNetpath,tstring& stPath,_tpath& _tPath,int& iVol,fileinfo& fileinfo_)
{
	GetVariableType(stNetpath,stPath,_tPath,iVol);
	if (GetFileInfo(stNetpath,fileinfo_)==false)
	{
		ThrowError(_T("Fail to get information"),stPath);
	}
}


void netstorage::CopyFile(const std::string& stNetPathFrom,const std::string& stNetPathTo,bool bSQLOnly)
{
	tstring stFrom,stTo;
	_tpath _tFrom,_tTo;
	int iVolFrom,iVolTo;
	fileinfo from,to;

	GetVariableType(stNetPathFrom,stFrom,_tFrom,iVolFrom,from);
	GetVariableType(stNetPathTo,stTo,_tTo,iVolTo);

	to=from;
	to.stNetPath=stNetPathTo;
	to.stNetDir=GetNetDir(stTo);

	if (netvolume_ptr_list_[iVolTo]->IsExistsFromPrimary(stNetPathTo,fileinfo()))
		ThrowAlreadyExist(stNetPathTo);

	if (!bSQLOnly)
	{
		MFile::CreateFolderL(MCodeChanger::_CCL(to.GetNetDir()));

		net_watcher_.Add(WATCH_CREATE,_tTo.c_str());

		// Execute
		boost::filesystem::copy_file(_tFrom,_tTo);
	//	boost::filesystem::remove(_tpath(Net_Thumb(stNetPathTo)));
	//	boost::filesystem::copy_file(_tpath(Net_Thumb(stNetPathFrom)),_tpath(Net_Thumb(stNetPathTo)));
		MFile::DeleteL(Net_Thumb(stNetPathTo));
		MFile::CopyFileL(Net_Thumb(stNetPathFrom),Net_Thumb(stNetPathTo));
	}

	if (iVolFrom == iVolTo)
	{

		// fileinfo

		if (netvolume_ptr_list_[iVolFrom]->Insert(to)!=1)
		{
			ThrowSQLInsertError(stNetPathTo); 
			return;
		}

		// comment

		comment_list comment_list_;
		netvolume_ptr_list_[iVolFrom]->FindEx(comment::get_tablename(),fileinfo::get_primary(),stNetPathFrom,comment_list_,comment());

		netvolume_ptr_list_[iVolFrom]->BeginTransaction();
		for (unsigned int i=0;i<comment_list_.size();i++)
		{
			comment temp=comment_list_[i];
			temp.stNetPath=stNetPathTo;
			if (netvolume_ptr_list_[iVolFrom]->Insert(temp)!=1)
				ThrowSQLInsertError(stNetPathTo); 
		}
		netvolume_ptr_list_[iVolFrom]->CommitTransaction();
	}
	else
	{
		// fileinfo

		int iInsert=netvolume_ptr_list_[iVolTo]->Insert(to);
		if (iInsert!=1)
		{
			ThrowSQLInsertError(stNetPathFrom); 
			return;
		}

		// comment
		comment_list comment_list_;
		netvolume_ptr_list_[iVolFrom]->FindEx(fileinfo::get_primary(),stNetPathFrom,comment_list_,comment());

		netvolume_ptr_list_[iVolTo]->BeginTransaction();
		for (unsigned int i=0;i<comment_list_.size();i++)
		{
			comment temp=comment_list_[i];
			temp.stNetPath=stNetPathTo;
			if (netvolume_ptr_list_[iVolTo]->Insert(temp)!=1)
				ThrowSQLInsertError(stNetPathTo); 
		}
		netvolume_ptr_list_[iVolTo]->CommitTransaction();
	}
	return;
}
void netstorage::CopyFolder(const std::string& stNetPathFrom,const std::string& stNetPathTo,bool bSQLOnly)
{
	tstring stFrom,stTo;
	_tpath _tFrom,_tTo;
	int iVolFrom,iVolTo;
	fileinfo from,to;

	GetVariableType(stNetPathFrom,stFrom,_tFrom,iVolFrom,from);
	GetVariableType(stNetPathTo,stTo,_tTo,iVolTo);

	to=from;
	to.stNetPath=stNetPathTo;
	to.stNetDir=GetNetDir(stTo);

	if (netvolume_ptr_list_[iVolTo]->IsExistsFromPrimary(stNetPathTo,fileinfo()))
		ThrowAlreadyExist(stNetPathTo);

	if (!bSQLOnly)
	{
		// 문제있음
		net_watcher_.Add(WATCH_CREATE,_tTo.c_str());

		// Execute
		MFile::CreateFolder(_tTo);
	//	boost::filesystem::remove_all(_tpath(Net_Thumb(stNetPathTo)));
		boost::filesystem::copy_file(_tpath(Net_Local(stNetPathFrom)),_tpath(Net_Local(stNetPathTo)));
		MFile::DeleteAllL(Net_Thumb(stNetPathTo));
		MFile::CopyFileL(Net_Thumb(stNetPathFrom),Net_Thumb(stNetPathTo));
	}

	if (iVolFrom == iVolTo)
	{

		// fileinfo

		if (netvolume_ptr_list_[iVolFrom]->Insert(to)!=1)
		{
			ThrowSQLInsertError(stNetPathTo); 
			return;
		}

		fileinfo_list f_list_;
		netvolume_ptr_list_[iVolFrom]->FindbyDir(stNetPathFrom,f_list_,false);

		netvolume_ptr_list_[iVolFrom]->BeginTransaction();

		if (netvolume_ptr_list_[iVolTo]->Insert(to)!=1)
			ThrowSQLInsertError(stNetPathTo); 

		for (unsigned int i=0;i<f_list_.size();i++)
		{
//			if (f_list_[i].GetNetDir().find(std::string(stNetPathFrom+"/"))==0 
//				|| strcmp(f_list_[i].GetNetDir().c_str(),stNetPathFrom.c_str())==0)
			{
				fileinfo temp;
				temp=f_list_[i];
				boost::algorithm::replace_first(temp.stNetPath,stNetPathFrom,stNetPathTo);
				boost::algorithm::replace_first(temp.stNetDir,stNetPathFrom,stNetPathTo);
				
				if (netvolume_ptr_list_[iVolFrom]->Insert(temp)!=1)
					ThrowSQLInsertError(stNetPathTo); 
			}
		}
		netvolume_ptr_list_[iVolFrom]->CommitTransaction();

		// comment

		comment_list comment_list_;
		netvolume_ptr_list_[iVolFrom]->Find(comment::get_tablename(),fileinfo::get_primary(),stNetPathFrom,comment_list_,comment(),"%s LIKE '%s%%' OR ");

		netvolume_ptr_list_[iVolFrom]->BeginTransaction();
		for (unsigned int i=0;i<comment_list_.size();i++)
		{
//			if (comment_list_[i].GetNetPath().find(std::string(stNetPathFrom+"/"))==0 
//				|| strcmp(comment_list_[i].GetNetPath().c_str(),stNetPathFrom.c_str())==0)
			{
				comment temp=comment_list_[i];
				temp.stNetPath=stNetPathTo;
				if (netvolume_ptr_list_[iVolFrom]->Insert(temp)!=1)
				ThrowSQLInsertError(stNetPathTo); 
			}
		}
		netvolume_ptr_list_[iVolFrom]->CommitTransaction();
	}
	else
	{
		// fileinfo

		int iInsert=netvolume_ptr_list_[iVolTo]->Insert(to);
		if (iInsert!=1)
		{
			ThrowSQLInsertError(stNetPathFrom); 
			return;
		}

		fileinfo_list f_list_;
		netvolume_ptr_list_[iVolFrom]->FindbyDir(stNetPathFrom,f_list_,false);

		netvolume_ptr_list_[iVolTo]->BeginTransaction();

		if (netvolume_ptr_list_[iVolTo]->Insert(to)!=1)
			ThrowSQLInsertError(stNetPathTo); 

		for (unsigned int i=0;i<f_list_.size();i++)
		{
//			if (f_list_[i].GetNetDir().find(std::string(stNetPathFrom+"/"))==0 
//				|| strcmp(f_list_[i].GetNetDir().c_str(),stNetPathFrom.c_str())==0)
			{
				fileinfo temp;
				temp=f_list_[i];
				boost::algorithm::replace_first(temp.stNetPath,stNetPathFrom,stNetPathTo);
				boost::algorithm::replace_first(temp.stNetDir,stNetPathFrom,stNetPathTo);
				
				if (netvolume_ptr_list_[iVolTo]->Insert(temp)!=1)
					ThrowSQLInsertError(stNetPathTo); 
			}
		}
		netvolume_ptr_list_[iVolTo]->CommitTransaction();


		// comment
		comment_list comment_list_;
		netvolume_ptr_list_[iVolFrom]->Find(comment::get_tablename(),fileinfo::get_primary(),stNetPathFrom,comment_list_,comment(),"%s LIKE '%s%%' OR ");

		netvolume_ptr_list_[iVolTo]->BeginTransaction();
		for (unsigned int i=0;i<comment_list_.size();i++)
		{
//			if (comment_list_[i].GetNetPath().find(std::string(stNetPathFrom+"/"))==0 
//				|| strcmp(comment_list_[i].GetNetPath().c_str(),stNetPathFrom.c_str())==0)
			{
				comment temp=comment_list_[i];
				temp.stNetPath=stNetPathTo;
				if (netvolume_ptr_list_[iVolTo]->Insert(temp)!=1)
				ThrowSQLInsertError(stNetPathTo); 
			}
		}
		netvolume_ptr_list_[iVolTo]->CommitTransaction();
	}
	return;
}
void netvolume::MoveFile(const std::string& stNetPathFrom,const std::string& stNetPathTo)
{
	fileinfo from,to;
	if (GetFileInfo(stNetPathFrom,from)==false)
		ThrowError(_T("Fail to get information"),MCodeChanger::_CCL(stNetPathFrom));

	to=from;
	to.stNetPath=stNetPathTo;
	to.stNetDir=GetNetDir(Net_Local(stNetPathTo));

	// fileinfo

	if (Update(from,to)!=1)
	{
		ThrowSQLUpdateError(stNetPathFrom,stNetPathTo); 
		return;
	}

	// comment

	comment_list comment_list_;
	FindEx(comment::get_tablename(),fileinfo::get_primary(),stNetPathFrom,comment_list_,comment());

	BeginTransaction();
	for (unsigned int i=0;i<comment_list_.size();i++)
	{
		comment temp=comment_list_[i];
		temp.stNetPath=stNetPathTo;
		if (Update(comment_list_[i],temp)!=1)
		ThrowSQLUpdateError(stNetPathFrom,stNetPathTo); 
	}
	CommitTransaction();
}

void netstorage::MoveFile(const std::string& stNetPathFrom,const std::string& stNetPathTo,bool bSQLOnly)
{
	tstring stFrom,stTo;
	_tpath _tFrom,_tTo;
	int iVolFrom,iVolTo;
	fileinfo from,to;

	GetVariableType(stNetPathFrom,stFrom,_tFrom,iVolFrom);
	GetVariableType(stNetPathTo,stTo,_tTo,iVolTo);

	/*
	GetVariableType(stNetPathFrom,stFrom,_tFrom,iVolFrom,from);
	GetVariableType(stNetPathTo,stTo,_tTo,iVolTo);

	to=from;
	to.stNetPath=stNetPathTo;
	to.stNetDir=GetNetDir(stTo);
*/
	if (netvolume_ptr_list_[iVolTo]->IsExistsFromPrimary(stNetPathTo,fileinfo()))
		ThrowAlreadyExist(stNetPathTo);

	if (!bSQLOnly)
	{
		net_watcher_.Add(WATCH_RENAME,_tFrom.c_str(),_tTo.c_str());

		// Execute
		MFile::CreateFolderL(MCodeChanger::_CCL(to.GetNetDir()));
		boost::filesystem::rename(_tFrom,_tTo);
		MFile::DeleteL(Net_Thumb(stNetPathTo));
		MFile::RenameL(Net_Thumb(stNetPathFrom),Net_Thumb(stNetPathTo));
	}

	if (iVolFrom == iVolTo)
	{
		netvolume_ptr_list_[iVolFrom]->MoveFile(stNetPathFrom,stNetPathTo);

		/*
		// fileinfo

		if (netvolume_ptr_list_[iVolFrom]->Update(from,to)!=1)
		{
			ThrowSQLUpdateError(stNetPathFrom,stNetPathTo); 
			return;
		}

		// comment

		comment_list comment_list_;
		netvolume_ptr_list_[iVolFrom]->FindEx(comment::get_tablename(),fileinfo::get_primary(),stNetPathFrom,comment_list_,comment());

		netvolume_ptr_list_[iVolFrom]->BeginTransaction();
		for (unsigned int i=0;i<comment_list_.size();i++)
		{
			comment temp=comment_list_[i];
			temp.stNetPath=stNetPathTo;
			if (netvolume_ptr_list_[iVolFrom]->Update(comment_list_[i],temp)!=1)
			ThrowSQLUpdateError(stNetPathFrom,stNetPathTo); 
		}
		netvolume_ptr_list_[iVolFrom]->CommitTransaction();
		*/
		
	}
	else
	{
		if (GetFileInfo(stNetPathFrom,from)==false)
			ThrowError(_T("Fail to get information"),MCodeChanger::_CCL(stNetPathFrom));

		to=from;
		to.stNetPath=stNetPathTo;
		to.stNetDir=GetNetDir(stTo);

		// fileinfo

		int iInsert=netvolume_ptr_list_[iVolTo]->Insert(to);
		if (iInsert!=1)
		{
			ThrowSQLInsertError(stNetPathFrom); 
			return;
		}

		int iDelete=netvolume_ptr_list_[iVolFrom]->Delete(from);

		if (iDelete!=1)
		{
			ThrowSQLDeleteError(stNetPathFrom); 
			return;
		}

		// comment
		comment_list comment_list_;
		netvolume_ptr_list_[iVolFrom]->FindEx(fileinfo::get_primary(),stNetPathFrom,comment_list_,comment());

		netvolume_ptr_list_[iVolTo]->BeginTransaction();
		for (unsigned int i=0;i<comment_list_.size();i++)
		{
			comment temp=comment_list_[i];
			temp.stNetPath=stNetPathTo;
			if (netvolume_ptr_list_[iVolTo]->Insert(temp)!=1)
			{
				netvolume_ptr_list_[iVolTo]->CommitTransaction();
				ThrowSQLDeleteError(stNetPathTo); 
			}
		}
		netvolume_ptr_list_[iVolTo]->CommitTransaction();

		netvolume_ptr_list_[iVolFrom]->BeginTransaction();
		for (unsigned int i=0;i<comment_list_.size();i++)
		{
			if (netvolume_ptr_list_[iVolFrom]->Delete(comment_list_[i])!=1)
			{
				netvolume_ptr_list_[iVolFrom]->CommitTransaction();
				ThrowSQLDeleteError(stNetPathFrom); 
			}
		}
		netvolume_ptr_list_[iVolFrom]->CommitTransaction();
	}
	return;
}

void netvolume::MoveFolder(const std::string& stNetPathFrom,const std::string& stNetPathTo)
{
	fileinfo from,to;
	if (GetFileInfo(stNetPathFrom,from)==false)
		ThrowError(_T("Fail to get information"),MCodeChanger::_CCL(stNetPathFrom));

	to=from;
	to.stNetPath=stNetPathTo;
	to.stNetDir=GetNetDir(Net_Local(stNetPathTo));

	// fileinfo

	if (Update(from,to)!=1)
	{
		ThrowSQLUpdateError(stNetPathFrom,stNetPathTo); 
		return;
	}

	fileinfo_list f_list_;
	FindbyDir(stNetPathFrom,f_list_,false);

	BeginTransaction();

	for (unsigned int i=0;i<f_list_.size();i++)
	{
//		if (f_list_[i].GetNetDir().find(std::string(stNetPathFrom+"/"))==0 
//			|| strcmp(f_list_[i].GetNetDir().c_str(),stNetPathFrom.c_str())==0)
		{
			fileinfo temp;
			temp=f_list_[i];
			boost::algorithm::replace_first(temp.stNetPath,stNetPathFrom,stNetPathTo);
			boost::algorithm::replace_first(temp.stNetDir,stNetPathFrom,stNetPathTo);
			
			if (Update(f_list_[i],temp)!=1)
			{
				CommitTransaction();
				ThrowSQLUpdateError(f_list_[i].GetNetPath(),temp.GetNetPath());
			}
		}
	}
	CommitTransaction();

	// comment

	comment_list comment_list_;
	Find(comment::get_tablename(),fileinfo::get_primary(),stNetPathFrom,comment_list_,comment(),"%s LIKE '%s%%' OR ");

	BeginTransaction();
	for (unsigned int i=0;i<comment_list_.size();i++)
	{
//		if (comment_list_[i].GetNetPath().find(std::string(stNetPathFrom+"/"))==0 
//			|| strcmp(comment_list_[i].GetNetPath().c_str(),stNetPathFrom.c_str())==0)
		{
			comment temp=comment_list_[i];
			boost::algorithm::replace_first(temp.stNetPath,stNetPathFrom,stNetPathTo);
//				temp.stNetPath=stNetPathTo;
			if (Update(comment_list_[i],temp)!=1)
			{
				CommitTransaction();
				ThrowSQLUpdateError(stNetPathFrom,stNetPathTo); 
			}
		}
	}
	CommitTransaction();

}

void netstorage::MoveFolder(const std::string& stNetPathFrom,const std::string& stNetPathTo,bool bSQLOnly)
{
	tstring stFrom,stTo;
	_tpath _tFrom,_tTo;
	int iVolFrom,iVolTo;
	fileinfo from,to;

	GetVariableType(stNetPathFrom,stFrom,_tFrom,iVolFrom);
	GetVariableType(stNetPathTo,stTo,_tTo,iVolTo);

	to=from;
	to.stNetPath=stNetPathTo;
	to.stNetDir=GetNetDir(stTo);

	if (netvolume_ptr_list_[iVolTo]->IsExistsFromPrimary(stNetPathTo,fileinfo()))
		ThrowAlreadyExist(stNetPathTo);

	if (!bSQLOnly)
	{
		net_watcher_.Add(WATCH_RENAME,_tFrom.c_str(),_tTo.c_str());

		// Execute
		boost::filesystem::rename(_tFrom,_tTo);
		MFile::DeleteAllL(Net_Thumb(stNetPathTo));
		MFile::RenameL(Net_Thumb(stNetPathFrom),Net_Thumb(stNetPathTo));
	}

	if (iVolFrom == iVolTo)
	{
		netvolume_ptr_list_[iVolFrom]->MoveFolder(stNetPathFrom,stNetPathTo);

		/*
		// fileinfo

		if (netvolume_ptr_list_[iVolFrom]->Update(from,to)!=1)
		{
			ThrowSQLUpdateError(stNetPathFrom,stNetPathTo); 
			return;
		}

		fileinfo_list f_list_;
		netvolume_ptr_list_[iVolFrom]->FindbyDir(stNetPathFrom,f_list_,false);

		netvolume_ptr_list_[iVolFrom]->BeginTransaction();

		for (unsigned int i=0;i<f_list_.size();i++)
		{
			if (f_list_[i].GetNetDir().find(std::string(stNetPathFrom+"/"))==0 
				|| strcmp(f_list_[i].GetNetDir().c_str(),stNetPathFrom.c_str())==0)
			{
				fileinfo temp;
				temp=f_list_[i];
				boost::algorithm::replace_first(temp.stNetPath,stNetPathFrom,stNetPathTo);
				boost::algorithm::replace_first(temp.stNetDir,stNetPathFrom,stNetPathTo);
				
				if (netvolume_ptr_list_[iVolFrom]->Update(f_list_[i],temp)!=1)
				{
					netvolume_ptr_list_[iVolFrom]->CommitTransaction();
					ThrowSQLUpdateError(f_list_[i].GetNetPath(),temp.GetNetPath());
				}
			}
		}
		netvolume_ptr_list_[iVolFrom]->CommitTransaction();

		// comment

		comment_list comment_list_;
		netvolume_ptr_list_[iVolFrom]->Find(comment::get_tablename(),fileinfo::get_primary(),stNetPathFrom,comment_list_,comment(),false);

		netvolume_ptr_list_[iVolFrom]->BeginTransaction();
		for (unsigned int i=0;i<comment_list_.size();i++)
		{
			if (comment_list_[i].GetNetPath().find(std::string(stNetPathFrom+"/"))==0 
				|| strcmp(comment_list_[i].GetNetPath().c_str(),stNetPathFrom.c_str())==0)
			{
				comment temp=comment_list_[i];
				boost::algorithm::replace_first(temp.stNetPath,stNetPathFrom,stNetPathTo);
//				temp.stNetPath=stNetPathTo;
				if (netvolume_ptr_list_[iVolFrom]->Update(comment_list_[i],temp)!=1)
				{
					netvolume_ptr_list_[iVolFrom]->CommitTransaction();
					ThrowSQLUpdateError(stNetPathFrom,stNetPathTo); 
				}
			}
		}
		netvolume_ptr_list_[iVolFrom]->CommitTransaction();
*/
		
	}
	else
	{
		if (GetFileInfo(stNetPathFrom,from)==false)
			ThrowError(_T("Fail to get information"),MCodeChanger::_CCL(stNetPathFrom));

		to=from;
		to.stNetPath=stNetPathTo;
		to.stNetDir=GetNetDir(stTo);

		// fileinfo

		int iInsert=netvolume_ptr_list_[iVolTo]->Insert(to);
		if (iInsert!=1)
		{
			ThrowSQLInsertError(stNetPathTo); 
			return;
		}
		iInsert=netvolume_ptr_list_[iVolFrom]->Delete(from);
		if (iInsert!=1)
		{
			ThrowSQLDeleteError(stNetPathFrom); 
			return;
		}


		fileinfo_list f_list_;
		netvolume_ptr_list_[iVolFrom]->FindbyDir(stNetPathFrom,f_list_,false);

		netvolume_ptr_list_[iVolTo]->BeginTransaction();
		netvolume_ptr_list_[iVolFrom]->BeginTransaction();

		if (netvolume_ptr_list_[iVolTo]->Insert(to)!=1)
		{
			netvolume_ptr_list_[iVolTo]->CommitTransaction();
			netvolume_ptr_list_[iVolFrom]->CommitTransaction();
			ThrowSQLInsertError(stNetPathTo);
		}
		if (netvolume_ptr_list_[iVolFrom]->Delete(from)!=1)
		{
			netvolume_ptr_list_[iVolTo]->CommitTransaction();
			netvolume_ptr_list_[iVolFrom]->CommitTransaction();
			ThrowSQLDeleteError(stNetPathFrom); 
		}

		for (unsigned int i=0;i<f_list_.size();i++)
		{
//			if (f_list_[i].GetNetDir().find(std::string(stNetPathFrom+"/"))==0 
//				|| strcmp(f_list_[i].GetNetDir().c_str(),stNetPathFrom.c_str())==0)
			{
				fileinfo temp;
				temp=f_list_[i];
				boost::algorithm::replace_first(temp.stNetPath,stNetPathFrom,stNetPathTo);
				boost::algorithm::replace_first(temp.stNetDir,stNetPathFrom,stNetPathTo);
				
				if (netvolume_ptr_list_[iVolTo]->Insert(temp)!=1)
				{
					netvolume_ptr_list_[iVolTo]->CommitTransaction();
					netvolume_ptr_list_[iVolFrom]->CommitTransaction();
					ThrowSQLInsertError(temp.GetNetPath()); 
				}

				if (netvolume_ptr_list_[iVolFrom]->Delete(f_list_[i])!=1)
				{
					netvolume_ptr_list_[iVolTo]->CommitTransaction();
					netvolume_ptr_list_[iVolFrom]->CommitTransaction();
					ThrowSQLDeleteError(f_list_[i].GetNetPath()); 
				}
			}
		}
		netvolume_ptr_list_[iVolTo]->CommitTransaction();
		netvolume_ptr_list_[iVolFrom]->CommitTransaction();

		// comment
		comment_list comment_list_;
		netvolume_ptr_list_[iVolFrom]->Find(comment::get_tablename(),fileinfo::get_primary(),stNetPathFrom,comment_list_,comment(),"%s LIKE '%s%%' OR ");

		netvolume_ptr_list_[iVolTo]->BeginTransaction();
		netvolume_ptr_list_[iVolFrom]->BeginTransaction();
		for (unsigned int i=0;i<comment_list_.size();i++)
		{
//			if (comment_list_[i].GetNetPath().find(std::string(stNetPathFrom+"/"))==0 
//				|| strcmp(comment_list_[i].GetNetPath().c_str(),stNetPathFrom.c_str())==0)
			{
				comment temp=comment_list_[i];
//				temp.stNetPath=stNetPathTo;
				boost::algorithm::replace_first(temp.stNetPath,stNetPathFrom,stNetPathTo);
				if (netvolume_ptr_list_[iVolTo]->Insert(temp)!=1)
				{
					netvolume_ptr_list_[iVolTo]->CommitTransaction();
					netvolume_ptr_list_[iVolFrom]->CommitTransaction();
					ThrowSQLInsertError(stNetPathTo); 
				}

				if (netvolume_ptr_list_[iVolFrom]->Delete(comment_list_[i])!=1)
				{
					netvolume_ptr_list_[iVolTo]->CommitTransaction();
					netvolume_ptr_list_[iVolFrom]->CommitTransaction();
					ThrowSQLDeleteError(stNetPathFrom); 
				}
			}
		}
		netvolume_ptr_list_[iVolTo]->CommitTransaction();
		netvolume_ptr_list_[iVolFrom]->CommitTransaction();

	}
	return;
}
void netvolume::DeleteFile(const std::string& stNetPathFrom)
{
	// fileinfo

	if (Delete(stNetPathFrom,fileinfo())!=1)
	{
		ThrowSQLDeleteError(stNetPathFrom); 
		return;
	}
	// comment
	Delete(comment::get_tablename(),fileinfo::get_primary(),stNetPathFrom);
}

void netstorage::DeleteFile(const std::string& stNetPathFrom,bool bSQLOnly)
{
	tstring stFrom;
	_tpath _tFrom;
	int iVolFrom;
	fileinfo from;

	GetVariableType(stNetPathFrom,stFrom,_tFrom,iVolFrom,from);

	if (!bSQLOnly)
	{
		net_watcher_.Add(WATCH_DELETE,_tFrom.c_str());

		// Execute
		boost::filesystem::remove(_tFrom);
		MFile::Delete(_tpath(Net_Thumb(stNetPathFrom)));
	}
	netvolume_ptr_list_[iVolFrom]->DeleteFile(stNetPathFrom);
/*
	// fileinfo

	if (netvolume_ptr_list_[iVolFrom]->Delete(from)!=1)
	{
		ThrowSQLDeleteError(stNetPathFrom); 
		return;
	}

	// comment

	netvolume_ptr_list_[iVolFrom]->Delete(comment::get_tablename(),fileinfo::get_primary(),stNetPathFrom);
	*/
}

void netvolume::DeleteFolder(const std::string& stNetPathFrom,bool bSQLOnly)
{
	fileinfo from;
	if (GetFileInfo(stNetPathFrom,from)==false)
		ThrowError(_T("Fail to get information"),MCodeChanger::_CCL(stNetPathFrom));

	// fileinfo

	fileinfo_list f_list_;
	FindbyDir(stNetPathFrom,f_list_,false);


	if (Delete(from)!=1)
	{
		ThrowSQLDeleteError(stNetPathFrom); 
	}

	tstring stLocalPath=Net_Local(stNetPathFrom);
	_tpath _tLocalPath(stLocalPath);
	for (int i=(int)(f_list_.size()-1);i>=0;i--)
	{
//		if (f_list_[i].GetNetDir().find(std::string(stNetPathFrom+"/"))==0 
//			|| strcmp(f_list_[i].GetNetDir().c_str(),stNetPathFrom.c_str())==0)
//		{
			if (!bSQLOnly)
			{
				net_watcher_.Add(WATCH_DELETE,Net_Local(f_list_[i].GetNetPath()));
			}
//		}
//		else
//		{
//			f_list_.erase(f_list_.begin()+i);
//		}
	}

	if (!bSQLOnly)
	{
		net_watcher_.Add(WATCH_DELETE,stLocalPath);

		// Execute
		boost::filesystem::remove_all(_tLocalPath);
	}
	BeginTransaction();
	Delete(fileinfo::get_tablename(),fileinfo::get_primary(),stNetPathFrom,"%s LIKE '%s%%'");
	Delete(comment::get_tablename(),comment::get_primary(),stNetPathFrom,"%s LIKE '%s%%'");
	CommitTransaction();

/*	BeginTransaction();
	for (unsigned int i=0;i<f_list_.size();i++)
	{
		if (Delete(f_list_[i])!=1)
		{
			CommitTransaction();
			ThrowSQLDeleteError(stNetPathFrom); 
		}
	}
	CommitTransaction();

	// comment
	comment_list comment_list_;
	Find(comment::get_tablename(),fileinfo::get_primary(),stNetPathFrom,comment_list_,comment(),"%s LIKE '%s%%' OR ");

	BeginTransaction();
	for (unsigned int i=0;i<comment_list_.size();i++)
	{
//		if (comment_list_[i].GetNetPath().find(std::string(stNetPathFrom+"/"))==0 
//			|| strcmp(comment_list_[i].GetNetPath().c_str(),stNetPathFrom.c_str())==0)
		{
			if (Delete(comment_list_[i])!=1)
			{
				CommitTransaction();
				ThrowSQLDeleteError(stNetPathFrom); 
			}
		}
	}
	CommitTransaction();
*/
}

void netstorage::DeleteFolder(const std::string& stNetPathFrom,bool bSQLOnly)
{
/*	tstring stFrom;
	_tpath _tFrom;
	int iVolFrom;
	fileinfo from;

	GetVariableType(stNetPathFrom,stFrom,_tFrom,iVolFrom,from);
*/
	int iVol=GetVolumeNumber(GetVolumeName(stNetPathFrom));
	if (iVol==-1) 
	{
		ThrowInvalidVol(stNetPathFrom);
	}

	netvolume_ptr_list_[iVol]->DeleteFolder(stNetPathFrom,bSQLOnly);

	if (!bSQLOnly)
	{
		MFile::DeleteAllL(Net_Thumb(stNetPathFrom));
	}

/*	
	// fileinfo

	fileinfo_list f_list_;
	netvolume_ptr_list_[iVolFrom]->FindbyDir(stNetPathFrom,f_list_,false);

	netvolume_ptr_list_[iVolFrom]->BeginTransaction();

	if (netvolume_ptr_list_[iVolFrom]->Delete(from)!=1)
		ThrowSQLDeleteError(stNetPathFrom); 
	for (unsigned int i=0;i<f_list_.size();i++)
	{
			if (f_list_[i].GetNetDir().find(std::string(stNetPathFrom+"/"))==0 
				|| strcmp(f_list_[i].GetNetDir().c_str(),stNetPathFrom.c_str())==0)
		{
			if (netvolume_ptr_list_[iVolFrom]->Delete(f_list_[i])!=1)
			ThrowSQLDeleteError(stNetPathFrom); 
		}
	}
	netvolume_ptr_list_[iVolFrom]->CommitTransaction();

	// comment
	comment_list comment_list_;
	netvolume_ptr_list_[iVolFrom]->Find(comment::get_tablename(),fileinfo::get_primary(),stNetPathFrom,comment_list_,comment(),false);

	netvolume_ptr_list_[iVolFrom]->BeginTransaction();
	for (unsigned int i=0;i<comment_list_.size();i++)
	{
		if (comment_list_[i].GetNetPath().find(std::string(stNetPathFrom+"/"))==0 
			|| strcmp(comment_list_[i].GetNetPath().c_str(),stNetPathFrom.c_str())==0)
		{
			if (netvolume_ptr_list_[iVolFrom]->Delete(comment_list_[i])!=1)
			ThrowSQLDeleteError(stNetPathFrom); 
		}
	}
	netvolume_ptr_list_[iVolFrom]->CommitTransaction();*/
	
}

void netstorage::CreateFolder(const std::string& stNetPathFrom,const std::string& stUserID,bool bSQLOnly)
{
	tstring stFrom;
	_tpath _tFrom;
	int iVolFrom;

	GetVariableType(stNetPathFrom,stFrom,_tFrom,iVolFrom);

	if (strcmp(stNetPathFrom.c_str()
		,MCodeChanger::_CCU(netvolume_ptr_list_[iVolFrom]->GetVolName()).c_str())==0)
		return;
	
	if (!netvolume_ptr_list_[iVolFrom]->IsExistsFromPrimary(Local_Net(_tFrom.parent_path().c_str()),fileinfo())
		|| !boost::filesystem::exists(_tFrom.parent_path()))
	{
		CreateFolder(Local_Net(_tFrom.parent_path().c_str()),stUserID);
	}

	if (!netvolume_ptr_list_[iVolFrom]->IsExistsFromPrimary(stNetPathFrom,fileinfo()))
	{

		if (!bSQLOnly)
		{
//			net_watcher_.Add(WATCH_CREATE,_tFrom.string());
			net_watcher_.Add(WATCH_CREATE,_tFrom.c_str());
			MFile::CreateFolder(_tFrom);
			MFile::CreateFolderL(Net_Thumb(stNetPathFrom));
		}

		fileinfo fileinfo_=CreateFileInfo(_tFrom,stUserID);

		if (netvolume_ptr_list_[iVolFrom]->Insert(fileinfo_)!=1)
				ThrowSQLInsertError(stNetPathFrom); 
	}
	else
	{
		if (!boost::filesystem::exists(_tFrom))
		{
			net_watcher_.Add(WATCH_CREATE,_tFrom.c_str());
			MFile::CreateFolder(_tFrom);
			MFile::CreateFolderL(Net_Thumb(stNetPathFrom));
		}
	}
}


void netstorage::CreateFile(const std::string& stNetPathFrom,const std::string& stUserID,bool bSQLOnly)
{
	tstring stFrom;
	_tpath _tFrom;
	int iVolFrom;

	GetVariableType(stNetPathFrom,stFrom,_tFrom,iVolFrom);

	if (strcmp(stNetPathFrom.c_str()
		,MCodeChanger::_CCU(netvolume_ptr_list_[iVolFrom]->GetVolName()).c_str())==0)
		return;

	if (!netvolume_ptr_list_[iVolFrom]->IsExistsFromPrimary(stNetPathFrom,fileinfo()))
	{
		fileinfo fileinfo_=CreateFileInfo(_tFrom,stUserID);
		LoadMetatag(fileinfo_);

		if (!netvolume_ptr_list_[iVolFrom]->IsExistsFromPrimary(boost::filesystem::path(stNetPathFrom).parent_path().string(),fileinfo()))
		{
			CreateFolder(boost::filesystem::path(stNetPathFrom).parent_path().string(),stUserID);
		}

		tstring thumbpath=Net_Thumb(stNetPathFrom);
		MFile::DeleteL(thumbpath);
//		MakeThumbnail(Net_Thumb(stNetPathFrom),stNetPathFrom,true);

		if (netvolume_ptr_list_[iVolFrom]->Insert(fileinfo_)!=1)
				ThrowSQLInsertError(stNetPathFrom); 
	}
}

void netvolume::MakeThumbnail(const tstring& thumbpath,const std::string& stNetPath,bool bForce)
{
	if (!MFile::ExistsL(thumbpath) || bForce)
	{
		tstring stLocalPath=Net_Local(stNetPath);

		CxImage image;
		if (image.Load(stLocalPath.c_str(),CXIMAGE_FORMAT_UNKNOWN))
		{
			MakeThumbnail(thumbpath,image);

/*			image.Thumbnail(config_.GetInt(THUMB_WIDTH)-2,config_.GetInt(THUMB_HEIGHT)-2,border);
			image.Expand(1,1,1,1,border);
			image.Save(thumbpath.c_str(),CXIMAGE_FORMAT_JPG);
*/
			//					log << _T("Create thumbnail  : ") << stLocalPath << "\n";
		}
	}
}
void netvolume::MakeThumbnail(const tstring& thumbpath,CxImage& image,bool bForce)
{
/*	RGBQUAD border;
	border.rgbBlue=0;
	border.rgbGreen=0;
	border.rgbRed=0;

	image.Thumbnail(config_.GetInt(THUMB_WIDTH)-2,config_.GetInt(THUMB_HEIGHT)-2,border);
	image.Expand(1,1,1,1,border);
*/
	ImageProcess::MakeThumbnail(image,config_);
//	MakeThumbnail(image,config_);
	image.Save(thumbpath.c_str(),CXIMAGE_FORMAT_JPG);
}
/*
void netvolume::MakeThumbnail(CxImage& image,config& config_)
{
	
	RGBQUAD border;
	border.rgbBlue=0;
	border.rgbGreen=0;
	border.rgbRed=0;

	image.Thumbnail(config_.GetInt(THUMB_WIDTH)-2,config_.GetInt(THUMB_HEIGHT)-2,border);
	image.Expand(1,1,1,1,border);
	
}
*/
void netstorage::MakeThumbnail(const tstring& thumbpath,const std::string& stNetPath,bool bForce)
{
	int iVol=GetVolumeNumber(GetVolumeName(stNetPath));
	if (iVol==-1) return;
	netvolume_ptr_list_[iVol]->MakeThumbnail(thumbpath,stNetPath,bForce);
}

void netstorage::Image_Rotate(const std::string& stNetPath,int iRotate)
{
	tstring stFrom;
	_tpath _tFrom;
	int iVolFrom;

	GetVariableType(stNetPath,stFrom,_tFrom,iVolFrom);

	if (!MFile::Exists(_tFrom))
		ThrowError(_T("File Not Exist"),MCodeChanger::_CCL(stNetPath));

	
	net_watcher_.Add(WATCH_MODIFY,_tFrom.c_str());
	net_watcher_.Add(WATCH_MODIFY,_tFrom.c_str());
	net_watcher_.Add(WATCH_MODIFY,_tFrom.c_str());

	CxImageJPG image;

	if (image.Load(stFrom.c_str()))
	{
		try
		{
			CxIOFile in,out;
			if (in.Open(stFrom.c_str(),_T("rb")))
			{
				image.Decode(&in);
				in.Close();
				if (out.Open(stFrom.c_str(),_T("w+b")))
				{
					image.Rotate(90*(float)iRotate);
					image.Encode(&out);
					out.Close();
				}
			}
			netvolume_ptr_list_[iVolFrom]->MakeThumbnail(Net_Thumb(stNetPath),image,true);

			/*
			Exiv2::Image::AutoPtr readImg = Exiv2::ImageFactory::open(MCodeChanger::_CCN(stFrom));

			readImg->readMetadata();

			Exiv2::IptcData iptcData=readImg->iptcData();
			Exiv2::ExifData exifData=readImg->exifData();
			std::string comment=readImg->comment();

			

			CxMemFile memfile;
			memfile.Open();
			image.Encode(&memfile,CXIMAGE_FORMAT_JPG);
			memfile.Seek(0,SEEK_SET);

			CxImageJPG::CxExifInfo exif;
			exif.DecodeExif(&memfile);

			memfile.Close();

			memfile.Open();
			image.Encode(&memfile,CXIMAGE_FORMAT_JPG);
			memfile.Seek(0,SEEK_SET);
			exif.EncodeExif(&memfile);

			image.Decode(&memfile,CXIMAGE_FORMAT_JPG);
			memfile.Close();


//			netvolume_ptr_list_[iVolFrom]->Close();
//			image.Save(stFrom.c_str(),CXIMAGE_FORMAT_JPG);
//			netvolume_ptr_list_[iVolFrom]->ReOpen();

			
//			Exiv2::Image::AutoPtr writeImg = Exiv2::ImageFactory::open(MCodeChanger::_CCN(stFrom));

			writeImg->setIptcData(iptcData);
			writeImg->setExifData(exifData);
			writeImg->setComment(comment);

//			netvolume_ptr_list_[iVolFrom]->Close();
			writeImg->writeMetadata();
//			netvolume_ptr_list_[iVolFrom]->ReOpen();
			*/

		}
		catch(...)
		{
			ThrowError(_T("Failure to Rotate Image"),MCodeChanger::_CCL(stNetPath));
		}
	}
	else
	{
		ThrowError(_T("Failure to Load Image"),MCodeChanger::_CCL(stNetPath));
	}

}
