#include "stdafx.h"
#include "data_manager.h"

data_manager::data_manager(boost::asio::io_service& io_service_,config& c_,CMyCout& l_)
: bStopBuildSQL(false)
,config_(c_)
,log(l_)
,netstorage_(c_)
,socket_(io_service_)
{
}
data_manager::data_manager(boost::asio::io_service& io_service_,config& c_)
: bStopBuildSQL(false)
,config_(c_)
,log(c_.log)
,netstorage_(c_)
,socket_(io_service_)
{
}
bool data_manager::initiate()
{
	try{
		netstorage_.Open();
//		netstorage_.Vacuum();
	}
	catch (CppSQLite3Exception& e)
	{
		log << e.errorMessage() << log.endl();
		return false;
	}
	catch (std::exception& e)
	{
		log << e.what() << log.endl();
		return false;
	}
	return true;
}

void data_manager::RunSchedule()
{
	boost::thread BuildThread(boost::bind(&data_manager::BackupSQL_Schedule,this));

	if (config_.GetInt(SCHEDULE_BUILD_DATE)!=-2)
		boost::thread BuildThread(boost::bind(&data_manager::Build_Schedule,this
			,config_.GetInt(SCHEDULE_BUILD_DATE),config_.GetInt(SCHEDULE_BUILD_TIME),0));

	if (config_.GetInt(SCHEDULE_CHECK_DATE)!=-2)
		boost::thread BuildThread(boost::bind(&data_manager::Check_Schedule,this
			,config_.GetInt(SCHEDULE_CHECK_DATE),config_.GetInt(SCHEDULE_CHECK_TIME),0));

	if (config_.GetInt(BACKUP_DATE)!=-2)
		boost::thread BuildThread(boost::bind(&data_manager::Backup_Schedule,this
			,config_.GetInt(BACKUP_DATE),config_.GetInt(BACKUP_TIME),0));

	boost::thread BuildThread2(boost::bind(&data_manager::Refresh_Schedule,this));
}
void data_manager::Refresh_Schedule()
{
	try
	{
		while (true)
		{
			if (config_.GetInt(IDLE_CONNECTION_INTERVAL)==0)
			{
				Utility::sleep_sec(60*10);
			}
			else
			{
				Utility::sleep_sec(config_.GetInt(IDLE_CONNECTION_INTERVAL)*60);
			}
			connect();
			socket_.close();
		}
	}
	catch( const std::exception & e )
	{
		log << _T("[Refresh_Schedule] Error  : ")<< MCodeChanger::_CCL(e.what()) << log.endl();
	}
	catch (CppSQLite3Exception& e)
	{
		error_message err_;
		err_.Add(SQL_ERROR,e.errorCode(),e.errorMessage());
		log << _T("[Refresh_Schedule] Error  : ")<< err_ << log.endl();
	}
	catch (...)
	{
		log << _T("[Refresh_Schedule] Error  : ")<< log.endl();
	}
}

void data_manager::connect()
  {
    // Resolve the host name into an IP address.
	
    boost::asio::ip::tcp::resolver resolver(socket_.get_io_service());
    boost::asio::ip::tcp::resolver::query query("127.0.0.1", config_.Get(SERVER_PORT));
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator =
      resolver.resolve(query);

	while (endpoint_iterator!=boost::asio::ip::tcp::resolver::iterator())
	{
		boost::optional<boost::system::error_code> timer_result;
		boost::optional<boost::system::error_code> socket_result;

		boost::asio::ip::tcp::endpoint endpoint=*endpoint_iterator;
		
		connect(endpoint,timer_result,socket_result);
		endpoint_iterator++;
		
		if (!(*socket_result)) 
			return;
		else
		{
			if (timer_result)
			{
				socket_.close();
				throw std::logic_error("Timeout");
//				return;
			}
			else
			{
				socket_.close();
				throw std::logic_error(socket_result->message());
//				throw ConnectionEx(SOC_ERROR,socket_result->value(),);
//				return;
			}
		}
		socket_.close();
	}
  }

void data_manager::connect(boost::asio::ip::tcp::endpoint endpoint,
						 boost::optional<boost::system::error_code>& timer_result,
						 boost::optional<boost::system::error_code>& socket_result)
{
    boost::asio::deadline_timer timer(socket_.get_io_service()); 
    timer.expires_from_now(boost::posix_time::seconds(30)); 
	timer.async_wait(boost::bind(&data_manager::set_stream_result,this,
		&timer_result, boost::asio::placeholders::error)); 

	  // Start an asynchronous connect operation.
	  socket_.async_connect(endpoint,
		boost::bind(&data_manager::set_result, this,
		&socket_result,boost::asio::placeholders::error));

    socket_.get_io_service().reset(); 
    while (socket_.get_io_service().run_one()) 
    { 
      if (socket_result) 
        timer.cancel(); 
      else if (timer_result)
	  {
		  socket_.close();
		  throw std::logic_error("Timeout");
	  }
    } 
}


void data_manager::BackupSQL_Schedule()
{

	try
	{
		while (true)
		{
			boost::mutex::scoped_lock lock1(buildsqlfileinfo_);
			boost::mutex::scoped_lock lock2(checksqlfileinfo_);
//			boost::mutex::scoped_lock lock3(buildmetatag_);
			boost::mutex::scoped_lock lock4(buildthumbnail_);
			boost::mutex::scoped_lock lock5(checkthumbnail_);
			boost::mutex::scoped_lock lock6(build_);
			boost::mutex::scoped_lock lock7(buildsql_);
			boost::mutex::scoped_lock lock8(buildthumb_);
			boost::mutex::scoped_lock lock9(schedule_build);
			boost::mutex::scoped_lock lock10(schedule_check);
			boost::mutex::scoped_lock lock11(schedule_backup);

			_tpath backup_path(MCodeChanger::_CCL(config_.Get(BACKUP_PATH)));

			// Old backup delete
			log << _T("[Schedule] Backup database to ") << backup_path.c_str() << log.endl();

			Utility::DeleteOldFiles(backup_path,24*config_.GetInt(SQLBACKUP_DURATION));

			// Start Backup
			backup_path /= Utility::GetToday(2); backup_path = Utility::refinepath(backup_path);
			MFile::CreateFolder(backup_path);

			// main DB
			_tpath prog_path=bfs::initial_path<_tpath>();
			prog_path /= MCodeChanger::_CCL(config_.Get(DATA_FILENAME)); prog_path = Utility::refinepath(prog_path);

			MFile::Delete(Utility::refinepath(_tpath(backup_path / MFile::leaf(prog_path))));
			Utility::sleep(1000);
			boost::filesystem::copy_file(prog_path,Utility::refinepath(_tpath(backup_path / MFile::leaf(prog_path))));

			// folder DB
			std::vector<std::string> param_list;
			config_.SplitParams(DATA_PATH,param_list);

			for (unsigned int i=0;i<param_list.size();i++)
			{
				_tpath root_path(MCodeChanger::_CCL(param_list[i]));

				_tpath db_path;
				tstring filename=MFile::leaf(_tpath(root_path)).c_str();
				filename+=_T(".dat");
				db_path=Utility::refinepath(_tpath(root_path) / filename); 



				MFile::Delete(Utility::refinepath(_tpath(backup_path / MFile::leaf(db_path))));
				Utility::sleep(1000);

				boost::filesystem::copy_file(db_path, Utility::refinepath(_tpath(backup_path / MFile::leaf(db_path))));
			}

			Utility::sleep(-1,3,0);
		}
	}
	catch (std::exception& e)
	{
		log << _T("[BackupSQL_Schedule] Error  : ")<< MCodeChanger::_CCL(e.what()) << log.endl();
	}
	catch (...)
	{
		log << _T("[BackupSQL_Schedule] Error  : ")<< log.endl();
	}
}

void data_manager::Build_Schedule(const int date,const int hour,const int minute)
{
	try
	{
		while (true)
		{
			Utility::sleep(date,hour,minute);

			boost::mutex::scoped_lock lock(schedule_build);

			log << _T("### Start Build_Schedule ###") << log.endl();
//			boost::mutex::scoped_lock lock(build_mutex);

			netstorage netstorage_(config_);netstorage_.Open();
			for (int i=0;i<netstorage_.GetSize();i++)
			{
				log << _T("## Volume : ") << netstorage_.Vol(i).GetRootPath() << _T("\n");


				ThreadControl threadcontrol1(SQLBUILD_THREAD);
				boost::mutex::scoped_lock lock1(buildsqlfileinfo_);
				if (threadcontrol1.Check())
				{
					if (bStopBuildSQL) return;
					log << _T("### Build Item ###") << log.endl();
					BuildSQLFileInfo(_tpath(netstorage_.Vol(i).GetRootPath()),netstorage_.Vol(i),true);
				}
				else
				{
					log << _T("### Skip Build Item ###") << log.endl();
				}
				threadcontrol1.Clear();

				/*
				ThreadControl threadcontrol2(BUILDMETATAG_THREAD);
				boost::mutex::scoped_lock lock2(buildmetatag_);
				if (threadcontrol2.Check())
				{
					if (bStopBuildSQL) return;
					log << _T("### Build MetaTag Information ###") << log.endl();
					BuildMetaTag(MCodeChanger::_CCU(netstorage_.Vol(i).GetVolName())
						,netstorage_.Vol(i));
				}
				else
				{
					log << _T("### Skip MetaTag Information ###") << log.endl();
				}
				threadcontrol2.Clear();
				*/

				ThreadControl threadcontrol3(THUMBBUILD_THREAD);
				boost::mutex::scoped_lock lock3(buildthumbnail_);
				if (threadcontrol3.Check())
				{
					if (bStopBuildSQL) return;
//					boost::mutex::scoped_lock lock2(build_thumb_mutex);
					log << _T("### Build Thumbnails ###") << log.endl();
					BuildThumbnail(MCodeChanger::_CCU(netstorage_.Vol(i).GetVolName())
						,netstorage_.Vol(i));
				}
				else
				{
					log << _T("### Skip Build Thumbnails ###") << log.endl();
				}
				threadcontrol3.Clear();
			}

			log << _T("### End Build_Schedule ###") << log.endl();
		}
	}
	catch( const std::exception & e )
	{
		log << _T("[Build_Schedule] Error  : ")<< MCodeChanger::_CCL(e.what()) << log.endl();
	}
	catch (CppSQLite3Exception& e)
	{
		error_message err_;
		err_.Add(SQL_ERROR,e.errorCode(),e.errorMessage());
		log << _T("[Build_Schedule] Error  : ")<< err_ << log.endl();
	}
	catch (...)
	{
		log << _T("[Build_Schedule] Error  : ")<< log.endl();
	}
}
void data_manager::Check_Schedule(const int date,const int hour,const int minute)
{
	try
	{
		while (true)
		{
			Utility::sleep(date,hour,minute);

			boost::mutex::scoped_lock lock(schedule_check);

			log << _T("### Start Check_Schedule ###") << log.endl();

			netstorage netstorage_(config_);netstorage_.Open();
			for (int i=0;i<netstorage_.GetSize();i++)
			{
				log << _T("## Volume : ") << netstorage_.Vol(i).GetRootPath() << _T("\n");

				ThreadControl threadcontrol1(SQLCHECK_THREAD);
				boost::mutex::scoped_lock lock1(checksqlfileinfo_);
				if (threadcontrol1.Check())
				{
					if (bStopBuildSQL) return;
					log << _T("### Check Item ###") << log.endl();
					CheckSQLFileInfo(MCodeChanger::_CCU(netstorage_.Vol(i).GetVolName())
						,netstorage_.Vol(i));
				}
				else
				{
					log << _T("### Skip Check Item ###") << log.endl();
				}
				threadcontrol1.Clear();
			}

				ThreadControl threadcontrol2(SQLCHECK_THREAD);
				boost::mutex::scoped_lock lock2(checkthumbnail_);
				if (threadcontrol2.Check())
				{
//					boost::mutex::scoped_lock lock2(build_thumb_mutex);
					log << _T("### Check Thumbnails ###") << log.endl();
					CheckThumbnail(_tpath(MCodeChanger::_CCL(config_.Get(THUMB_PATH))));
				}
				else
				{
					log << _T("### Skip Check Thumbnails ###") << log.endl();
				}
				threadcontrol2.Clear();

			log << _T("### End Check_Schedule ###") << log.endl();
		}
	}
	catch( const std::exception & e )
	{
		log << _T("[Check_Schedule] Error  : ")<< MCodeChanger::_CCL(e.what()) << log.endl();
	}
	catch (CppSQLite3Exception& e)
	{
		error_message err_;
		err_.Add(SQL_ERROR,e.errorCode(),e.errorMessage());
		log << _T("[Check_Schedule] Error  : ") << err_ << log.endl();
	}
	catch (...)
	{
		log << _T("[Check_Schedule] Error  : ")<< log.endl();
	}

}

void data_manager::Backup_Schedule(const int date,const int hour,const int minute)
{
	boost::mutex::scoped_lock lock(schedule_backup);
}

void data_manager::Build()
{
//	ResetBuild();
	boost::mutex::scoped_lock lock(build_);

	log << _T("### Start Build ###") << log.endl();
	try
	{
		netstorage netstorage_(config_);netstorage_.Open();

//		boost::mutex::scoped_lock lock(build_mutex);

		for (int i=0;i<netstorage_.GetSize();i++)
		{
			log << _T("## Volume : ") << netstorage_.Vol(i).GetRootPath() << _T("\n");

			bool bCheckExist=true;
			if (netstorage_.Vol(i).IsEmpty(fileinfo()) && netstorage_.Vol(i).IsEmpty(comment()))
			{
				log << _T("### Reset ###\n");
				netstorage_.Vol(i).DeleteTable();
				netstorage_.Vol(i).CreateTable();
				bCheckExist=false;
			}

			ThreadControl threadcontrol1(SQLBUILD_THREAD);
			boost::mutex::scoped_lock lock1(buildsqlfileinfo_);
			if (threadcontrol1.Check())
			{
				if (bStopBuildSQL) return;
				log << _T("### Build Item ###") << log.endl();
				BuildSQLFileInfo(_tpath(netstorage_.Vol(i).GetRootPath())
					,netstorage_.Vol(i),bCheckExist);
			}
			else
			{
				log << _T("### Skip Build Item ###") << log.endl();
			}
			threadcontrol1.Clear();

			if (bCheckExist)
			{
				ThreadControl threadcontrol2(SQLCHECK_THREAD);
				boost::mutex::scoped_lock lock2(checksqlfileinfo_);
				if (threadcontrol2.Check())
				{
					if (bStopBuildSQL) return;
					log << _T("### Check Item ###") << log.endl();
					CheckSQLFileInfo(MCodeChanger::_CCU(netstorage_.Vol(i).GetVolName())
						,netstorage_.Vol(i));
				}
				else
				{
					log << _T("### Skip Check Item ###") << log.endl();
				}
				threadcontrol2.Clear();
			}

			/*
			ThreadControl threadcontrol3(BUILDMETATAG_THREAD);
			boost::mutex::scoped_lock lock3(buildmetatag_);
			if (threadcontrol3.Check())
			{
				if (bStopBuildSQL) return;
				log << _T("### Build MetaTag Information ###") << log.endl();
				BuildMetaTag(MCodeChanger::_CCU(netstorage_.Vol(i).GetVolName())
					,netstorage_.Vol(i));
			}
			else
			{
				log << _T("### Skip MetaTag Information ###") << log.endl();
			}
			threadcontrol3.Clear();
			*/

			ThreadControl threadcontrol4(THUMBBUILD_THREAD);
			boost::mutex::scoped_lock lock4(buildthumbnail_);
			if (threadcontrol4.Check())
			{
	//			boost::mutex::scoped_lock lock2(build_thumb_mutex);
				if (bStopBuildSQL) return;
				log << _T("### Build Thumbnails ###") << log.endl();
				BuildThumbnail(MCodeChanger::_CCU(netstorage_.Vol(i).GetVolName())
					,netstorage_.Vol(i));
			}
			else
			{
				log << _T("### Skip Build Thumbnails ###") << log.endl();
			}
			threadcontrol4.Clear();
		}

		ThreadControl threadcontrol5(THUMBCHECK_THREAD);
		boost::mutex::scoped_lock lock5(checkthumbnail_);
		if (threadcontrol5.Check())
		{
	//			boost::mutex::scoped_lock lock2(build_thumb_mutex);
			if (bStopBuildSQL) return;
			log << _T("### Check Thumbnails ###") << log.endl();
			CheckThumbnail(_tpath(MCodeChanger::_CCL(config_.Get(THUMB_PATH))));
		}
		else
		{
			log << _T("### Skip Check Thumbnails ###") << log.endl();
		}
		threadcontrol5.Clear();

		log << _T("### End Build ###") << log.endl();
	}
	catch( const std::exception & e )
	{
		log << _T("[Build] Error  : ")<< MCodeChanger::_CCL(e.what()) << log.endl();
	}
	catch (CppSQLite3Exception& e)
	{
		error_message err_;
		err_.Add(SQL_ERROR,e.errorCode(),e.errorMessage());
		log << _T("[Build] Error  : ") << err_ << log.endl();
	}
	catch (...)
	{
		log << _T("[Build] Error  : ")<< log.endl();
	}

}
void data_manager::BuildSQL()
{
	boost::mutex::scoped_lock lock(buildsql_);
	log << _T("### Start Build DB ###") << log.endl();

	try
	{
		netstorage netstorage_(config_);netstorage_.Open();

		for (int i=0;i<netstorage_.GetSize();i++)
		{
			log << _T("## Volume : ") << netstorage_.Vol(i).GetRootPath() << _T("\n");

			bool bCheckExist=true;
			if (netstorage_.Vol(i).IsEmpty(fileinfo()) && netstorage_.Vol(i).IsEmpty(comment()))
			{
				log << _T("### Reset ###\n");
				netstorage_.Vol(i).DeleteTable();
				netstorage_.Vol(i).CreateTable();
				bCheckExist=false;
			}

			ThreadControl threadcontrol1(SQLBUILD_THREAD);
			boost::mutex::scoped_lock lock1(buildsqlfileinfo_);
			if (threadcontrol1.Check())
			{
				if (bStopBuildSQL) return;
				log << _T("### Build Item ###") << log.endl();
				BuildSQLFileInfo(_tpath(netstorage_.Vol(i).GetRootPath())
					,netstorage_.Vol(i),bCheckExist);
			}
			else
			{
				log << _T("### Skip Build Item ###") << log.endl();
			}
			threadcontrol1.Clear();

			if (bCheckExist)
			{
				ThreadControl threadcontrol2(SQLCHECK_THREAD);
				boost::mutex::scoped_lock lock2(checksqlfileinfo_);
				if (threadcontrol2.Check())
				{
					if (bStopBuildSQL) return;
					log << _T("### Check Item ###") << log.endl();
					CheckSQLFileInfo(MCodeChanger::_CCU(netstorage_.Vol(i).GetVolName())
						,netstorage_.Vol(i));
				}
				else
				{
					log << _T("### Skip Check Item ###") << log.endl();
				}
				threadcontrol2.Clear();
			}

			/*
			ThreadControl threadcontrol3(BUILDMETATAG_THREAD);
			boost::mutex::scoped_lock lock3(buildmetatag_);
			if (threadcontrol3.Check())
			{
				if (bStopBuildSQL) return;
				log << _T("### Build MetaTag Information ###") << log.endl();
				BuildMetaTag(MCodeChanger::_CCU(netstorage_.Vol(i).GetVolName())
					,netstorage_.Vol(i));
			}
			else
			{
				log << _T("### Skip MetaTag Information ###") << log.endl();
			}
			threadcontrol3.Clear();
			*/
		}
		log << _T("### End Build DB ###") << log.endl();
	}
	catch( const std::exception & e )
	{
		log << _T("[Build DB] Error  : ")<< MCodeChanger::_CCL(e.what()) << log.endl();
	}
	catch (CppSQLite3Exception& e)
	{
		error_message err_;
		err_.Add(SQL_ERROR,e.errorCode(),e.errorMessage());
		log << _T("[Build DB] Error  : ") << err_ << log.endl();
	}
	catch (...)
	{
		log << _T("[Build DB] Error  : ")<< log.endl();
	}
}
void data_manager::BuildThumbnail()
{
	boost::mutex::scoped_lock lock(buildthumb_);
	log << _T("### Start Build Thumbnail ###") << log.endl();

	try
	{
		netstorage netstorage_(config_);netstorage_.Open();

		for (int i=0;i<netstorage_.GetSize();i++)
		{
			log << _T("## Volume : ") << netstorage_.Vol(i).GetRootPath() << _T("\n");

			ThreadControl threadcontrol4(THUMBBUILD_THREAD);
			boost::mutex::scoped_lock lock4(buildthumbnail_);
			if (threadcontrol4.Check())
			{
				if (bStopBuildSQL) return;
				log << _T("### Build Thumbnails ###") << log.endl();
				BuildThumbnail(MCodeChanger::_CCU(netstorage_.Vol(i).GetVolName())
					,netstorage_.Vol(i));
			}
			else
			{
				log << _T("### Skip Build Thumbnails ###") << log.endl();
			}
			threadcontrol4.Clear();
		}

		ThreadControl threadcontrol5(THUMBCHECK_THREAD);
		boost::mutex::scoped_lock lock5(checkthumbnail_);
		if (threadcontrol5.Check())
		{
			if (bStopBuildSQL) return;
			log << _T("### Check Thumbnails ###") << log.endl();
			CheckThumbnail(_tpath(MCodeChanger::_CCL(config_.Get(THUMB_PATH))));
		}
		else
		{
			log << _T("### Skip Check Thumbnails ###") << log.endl();
		}
		threadcontrol5.Clear();

		log << _T("### End Build Thumbnail ###") << log.endl();
	}
	catch( const std::exception & e )
	{
		log << _T("[Build Thumbnail] Error  : ")<< MCodeChanger::_CCL(e.what()) << log.endl();
	}
	catch (CppSQLite3Exception& e)
	{
		error_message err_;
		err_.Add(SQL_ERROR,e.errorCode(),e.errorMessage());
		log << _T("[Build Thumbnail] Error  : ") << err_ << log.endl();
	}
	catch (...)
	{
		log << _T("[Build Thumbnail] Error  : ")<< log.endl();
	}
}

bool data_manager::BuildSQLFileInfo(const _tpath& p,netvolume& netvolume_,bool bCheckExist)
{
	if (bStopBuildSQL) return false;
	if (bCheckExist)
		Utility::sleep(SLEEP_TIME);
	path_list pfound;

	if( !bfs::exists(p) ) 
	{
		return false;
	}
	if(!bfs::is_directory(p) )
	{
		return false;
	}

	_tdirectory_iterator end_iter;
	fileinfo_list f_list;

	fileinfo f_temp=netstorage_.CreateFileInfoL(p.c_str());

	log << _T("Check Folder : ") << p.c_str() << _T("\n");

	MFile::CreateFolderL(netstorage_.Net_Thumb(f_temp.GetNetPath()));

	
	if (strcmp(f_temp.GetNetPath().c_str()
		,MCodeChanger::_CCU(netvolume_.GetVolName()).c_str())!=0)
	{
		if (bCheckExist)
		{
			if (!netvolume_.CheckExistInfo_from_Primary(f_temp.GetNetPath(),fileinfo()))
			{
				log << _T("Create Item : ") << netstorage_.Net_Local(f_temp.GetNetPath()) << _T("\n");
				netvolume_.Insert(f_temp);
			}
		}
		else
		{
			log << _T("Create Item : ") << netstorage_.Net_Local(f_temp.GetNetPath()) << _T("\n");
			netvolume_.Insert(f_temp);
		}
	}

	std::vector<_tpath> dir_list,file_list;

	for ( _tdirectory_iterator dir_itr( p );
      dir_itr != end_iter;
      ++dir_itr )
	{
		if (bStopBuildSQL) return false;

		_tpath temp = MFile::refinepath(*dir_itr);

		if (bfs::is_directory(temp))
		{
			dir_list.push_back(temp);
		}
		else
		{
			file_list.push_back(temp);
		}
	}

	fileinfo_list temp_list,temp_list_org,final_list;
	netvolume_.Find("netdir",f_temp.GetNetPath(),temp_list_org,fileinfo(),true);

	SetProgress(file_list.size());

	for (unsigned int i=0;i<file_list.size();i++)
	{
		if (bStopBuildSQL) return false;

		fileinfo fileinfo_=netstorage_.CreateFileInfo(file_list[i]);
		netstorage_.LoadMetatag(fileinfo_);

		bool bExist=false;

		if (bCheckExist)
		{
			temp_list=temp_list_org;

			for (unsigned int j=0;j<temp_list.size();j++)
			{
				if (strcmp(temp_list[j].GetNetPath().c_str(),fileinfo_.GetNetPath().c_str())==0)
				{
					temp_list.erase(temp_list.begin()+j);
					bExist=true;break;
				}
			}
		}
		if (!bExist)
			final_list.push_back(fileinfo_);
		SetProgressPos(i+1,file_list[i].c_str());
	}

	SetProgressText(_T("Begin Transaction"));
	BuildSQLFileInfo_commit(final_list,netvolume_);
	SetProgressText(_T("Commit Transaction"));

	for (unsigned int i=0;i<dir_list.size();i++)
	{
		if (!BuildSQLFileInfo(dir_list[i],netvolume_,bCheckExist)) return false;
	}

	return true;
}
void data_manager::BuildSQLFileInfo_commit(const fileinfo_list& f_list,netvolume& netvolume_)
{
	unsigned int i;

	netvolume_.BeginTransaction();
	for (i=0;i<f_list.size();i++)
	{
		if (bStopBuildSQL) {netvolume_.CommitTransaction();return;}

		std::string ext1=MCodeChanger::_CCU(MFile::GetFileExtL(netstorage_.Net_Local(f_list[i].GetNetPath())));
		boost::algorithm::to_lower(ext1);

		if (config_.Compare(FILE_EXTENSIONS,ext1))
		{
			log << _T("Create Item : ") << netstorage_.Net_Local(f_list[i].GetNetPath()) << _T("\n");
			netvolume_.Insert(f_list[i]);
		}
	}
	netvolume_.CommitTransaction();
}

void data_manager::CheckSQLFileInfo(const std::string& stNetPath,netvolume& netvolume_)
{
	if (bStopBuildSQL) return;
	Utility::sleep(SLEEP_TIME);
//	std::string stNetPath=stNetPath_org;

	if (!MFile::ExistsL(netstorage_.Net_Local(stNetPath)))
		netvolume_.Delete(fileinfo::get_tablename(),fileinfo::get_primary(),stNetPath);

	fileinfo_list temp_list;
	netvolume_.Find("netdir",stNetPath,temp_list,fileinfo(),true);

	fileinfo_list netDir_list,netFile_list;

	for (unsigned int i=0;i<temp_list.size();i++)
	{
		if (bStopBuildSQL) return;
		if (temp_list[i].IsDir())
		{
			if (strcmp(temp_list[i].GetNetPath().c_str(),stNetPath.c_str())!=0)
				netDir_list.push_back(temp_list[i]);
		}
		else
		{
			netFile_list.push_back(temp_list[i]);
		}
	}

	fileinfo_list f_list_,f_list_org_;
	_tdirectory_iterator end_iter;

	for ( _tdirectory_iterator dir_itr(_tpath(netstorage_.Net_Local(stNetPath)));
	  dir_itr != end_iter;
	  ++dir_itr )
	{
		if (bStopBuildSQL) return;
		f_list_org_.push_back(netstorage_.CreateFileInfo(MFile::refinepath(*dir_itr)));
	}

	fileinfo_list delete_list;
	for (unsigned int i=0;i<netFile_list.size();i++)
	{
		if (bStopBuildSQL) return;

		bool bExist=false;
		f_list_=f_list_org_;
		for (unsigned int j=0;j<f_list_.size();j++)
		{
			if (strcmp(f_list_[j].GetNetPath().c_str(),netFile_list[i].GetNetPath().c_str())==0)
			{
				f_list_.erase(f_list_.begin()+j);
				bExist=true;break;
			}
		}

		if (!bExist)
			delete_list.push_back(netFile_list[i]);
	}


	CheckSQLFileInfo_commit(delete_list,netvolume_);

	for (unsigned int i=0;i<netDir_list.size();i++)
	{
		CheckSQLFileInfo(netDir_list[i].GetNetPath(),netvolume_);
	}
}
void data_manager::CheckSQLFileInfo_commit(const fileinfo_list& delete_list,netvolume& netvolume_)
{
	netvolume_.BeginTransaction();
	for (unsigned int i=0;i<delete_list.size();i++)
	{
		netvolume_.Delete(delete_list[i]);
		log << _T("Delete Item : ") << MCodeChanger::_CCL(delete_list[i].GetNetPath()) << _T("\n");
		if (bStopBuildSQL) {netvolume_.CommitTransaction();return;}
	}
	netvolume_.CommitTransaction();
}


void data_manager::BuildThumbnail(const std::string& stNetPath,netvolume& netvolume_)
{
	if (bStopBuildSQL) return;
	Utility::sleep(SLEEP_TIME);
	fileinfo_list temp_list;

//	std::string stNetPath=stNetPath_org;
	netvolume_.Find("netdir",stNetPath,temp_list,fileinfo(),true);

	MFile::CreateFolderL(netstorage_.Net_Thumb(stNetPath));

	SetProgress(temp_list.size());

	for (unsigned int i=0;i<temp_list.size();i++)
	{
		Utility::sleep(THUMB_SLEEP_TIME);
		if (temp_list[i].IsDir() && strcmp(temp_list[i].GetNetPath().c_str(),stNetPath.c_str())!=0)
			BuildThumbnail(temp_list[i].GetNetPath(),netvolume_);
		else
		{
			tstring thumbpath=netstorage_.Net_Thumb(temp_list[i].stNetPath);
			MakeThumbnail(thumbpath,temp_list[i].GetNetPath());
		}
		SetProgressPos(i+1,MCodeChanger::_CCL(temp_list[i].GetNetPath()));

		if (bStopBuildSQL) return;
	}
}

void data_manager::MakeThumbnail(const tstring& thumbpath,const std::string& stNetPath)
{
	netstorage_.MakeThumbnail(thumbpath,stNetPath);
	/*
	if (!MFile::ExistsL(thumbpath))
	{
		RGBQUAD border;
		border.rgbBlue=0;
		border.rgbGreen=0;
		border.rgbRed=0;

		tstring stLocalPath=netstorage_.Net_Local(stNetPath);

		CxImage image;
		if (image.Load(stLocalPath.c_str(),CXIMAGE_FORMAT_UNKNOWN))
		{
			image.Thumbnail(config_.GetInt(THUMB_WIDTH)-2,config_.GetInt(THUMB_HEIGHT)-2,border);
			image.Expand(1,1,1,1,border);
			image.Save(thumbpath.c_str(),CXIMAGE_FORMAT_JPG);
//					log << _T("Create thumbnail  : ") << stLocalPath << "\n";
		}
	}
	*/
}

bool data_manager::CheckThumbnail(const _tpath& p)
{
	if (bStopBuildSQL) return false;
	Utility::sleep(SLEEP_TIME);
	path_list pfound;

	if( !bfs::exists(p) ) 
	{
		return false;
	}
	if(!bfs::is_directory(p) )
	{
		return false;
	}

	_tdirectory_iterator end_iter;

	for ( _tdirectory_iterator dir_itr( p );
          dir_itr != end_iter;
          ++dir_itr )
	{
		if (bfs::is_directory(*dir_itr))
		{
			try
			{
				if (!MFile::ExistsL(netstorage_.Net_Local(netstorage_.Thumb_Net(dir_itr->path().c_str()))))
					MFile::DeleteAll(*dir_itr);
			}
			catch(...)
			{
				MFile::DeleteAll(*dir_itr);
			}
		}
		else
		{
			try
			{
				if (!MFile::ExistsL(netstorage_.Net_Local(netstorage_.Thumb_Net(dir_itr->path().c_str()))))
					MFile::Delete(*dir_itr);
			}
			catch(...)
			{
				MFile::DeleteAll(*dir_itr);
			}
		}
		if (bStopBuildSQL) return false;
	}
	return true;
}

/*
void data_manager::BuildMetaTag(const std::string& stNetPath,netvolume& netvolume_)
{
	if (bStopBuildSQL) return;
	Utility::sleep(SLEEP_TIME);
	fileinfo_list temp_list,update_list;

//	netvolume netvolume_(log);netvolume_.Open();
//	std::string stNetPath=stNetPath_org;
	netvolume_.Find("netdir",stNetPath,temp_list,fileinfo(),true);

	boost::posix_time::ptime blank_time;

	SetProgress(temp_list.size());

	for (unsigned int i=0;i<temp_list.size();i++)
	{
		if (temp_list[i].IsDir() && strcmp(temp_list[i].GetNetPath().c_str(),stNetPath.c_str())!=0)
			BuildMetaTag(temp_list[i].GetNetPath(),netvolume_);
		else
		{
			if (temp_list[i].Time==blank_time)
			{
				if (netvolume_.LoadMetatag(temp_list[i]))
					update_list.push_back(temp_list[i]);
			}
		}
		SetProgressPos(i+1,MCodeChanger::_CCL(temp_list[i].GetNetPath()));
		if (bStopBuildSQL) return;
	}

//	unsigned int i;

	netvolume_.BeginTransaction();
	SetProgressText(_T("Begin Transaction"));

	for (unsigned int i=0;i<update_list.size();i++)
	{
		netvolume_.Update(update_list[i]);
		if (bStopBuildSQL) {netvolume_.CommitTransaction();return;}
	}
	netvolume_.CommitTransaction();
	SetProgressText(_T("Commit Transaction"));

}

*/