#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "../cximage/ximage.h"
#include "../share/file.h"
#include "../share/unicode.h"
#include "../share/cmycout.h"
#include "../share/etc.h"
#include "../share/netpath.h"
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <vector>
#include <string>


#ifndef _DEBUG
#define SLEEP_TIME 1000
#define THUMB_SLEEP_TIME 100
#endif

#ifdef _DEBUG
#define SLEEP_TIME 0
#define THUMB_SLEEP_TIME 0
#endif

class data_manager
{
public:
	data_manager(boost::asio::io_service& io_service_,config& c_,CMyCout& l_);
	data_manager(boost::asio::io_service& io_service_,config& c_);

	static bool CheckValidPicturePath(const tstring& stOrgPath,tstring& stErrorMsg)
	{
		tstring stPath= stOrgPath;
		boost::replace_all(stPath, _T("\\"), _T("/"));

		std::vector<std::string> param_list;
		Utility::SplitParams(MCodeChanger::_CCU(stPath),param_list);

		for (unsigned int i=0;i<param_list.size();i++)
		{
			tstring stPath=MCodeChanger::_CCL(param_list[i]);
			if (stPath.empty())
			{
				stErrorMsg=_T("'Photography Folder' empty. Edit s_config.txt or execute the Configuration wizard.");
				return false;
			}
			if (!MFile::ExistsL(stPath))
			{
				stErrorMsg=_T("The photography folder not exist : ");
				stErrorMsg+=stPath;
				return false;
			}
			if (_tcscmp(MFile::leaf(_tpath(stPath)).c_str(),_T("/"))==0
				|| tstring(MFile::leaf(_tpath(stPath)).c_str()).find(_T(":"))!=tstring::npos)
			{
				stErrorMsg=_T("The photography folder should not be a root folder as like c:\\ or d:\\");
				return false;
			}
			if (!MFile::IsDirL(stPath))
			{
				stErrorMsg=_T("Invalid Folder : ");
				stErrorMsg+=stPath;
				return false;
			}
		}
		return true;
	}

	void Heartbeat(DWORD period)
	{
		netstorage_.Heartbeat(period);
	}
	void StartWatch()
	{
		netstorage_.StartWatch();
	}
	void StopWatch()
	{
		netstorage_.StopWatch();
	}

	bool Check()
	{
		return netstorage_.Check();
	}
	bool initiate();
	bool IsAnyEmpty() {return netstorage_.IsAnyEmpty();}

	~data_manager()
	{
		StopBuild();
		boost::mutex::scoped_lock lock_1(build_);
		boost::mutex::scoped_lock lock_2(buildsql_);
		boost::mutex::scoped_lock lock_3(buildthumb_);
		boost::mutex::scoped_lock lock_4(schedule_build);
		boost::mutex::scoped_lock lock_5(schedule_check);
		boost::mutex::scoped_lock lock_6(schedule_backup);
	}

	virtual void Build();
	virtual void BuildSQL();  // non-thread
	virtual void BuildThumbnail();  // non-thread
	virtual void RunSchedule();

	virtual void StopBuild() 
	{
		bStopBuildSQL=true;
	}
	void ResetBuild() 
	{
		StopBuild();
		bStopBuildSQL=false;
	}
protected:
  boost::asio::ip::tcp::socket socket_;
  void set_stream_result(boost::optional<boost::system::error_code>* a, const boost::system::error_code& b) 
  { 
	  a->reset(b);
  } 
  void set_result(boost::optional<boost::system::error_code>* a, const boost::system::error_code& b) 
  { 
	  a->reset(b);
  } 

  void connect();
  void connect(boost::asio::ip::tcp::endpoint endpoint,
						 boost::optional<boost::system::error_code>& timer_result,
						 boost::optional<boost::system::error_code>& socket_result);


	virtual bool BuildSQLFileInfo(const _tpath& p,netvolume& netvolume_,bool bCheckExist=true);
	void BuildSQLFileInfo_commit(const fileinfo_list& f_list,netvolume& netvolume_);

	virtual void CheckSQLFileInfo(const std::string& stNetPath,netvolume& netvolume_);
	void CheckSQLFileInfo_commit(const fileinfo_list& delete_list,netvolume& netvolume_);

	virtual void BuildThumbnail(const std::string& stNetPath,netvolume& netvolume_);
	virtual bool CheckThumbnail(const _tpath& p);
//	virtual void BuildMetaTag(const std::string& stNetPath,netvolume& netvolume_);

	virtual void Build_Schedule(const int date,const int hour,const int minute);
	virtual void Check_Schedule(const int date,const int hour,const int minute);
	virtual void Backup_Schedule(const int date,const int hour,const int minute);
	virtual void BackupSQL_Schedule();
	void Refresh_Schedule();

	virtual void MakeThumbnail(const tstring& thumbpath,const std::string& stNetPath);

	virtual void SetProgress(int iMax) {}
	virtual void SetProgressText(const tstring& stText) {}
	virtual void SetProgressPos(int i,const tstring& stText) {}
	virtual void SetProgressPos(int i) {}
	// Mutex

	boost::mutex buildsqlfileinfo_;
	boost::mutex checksqlfileinfo_;
//	boost::mutex buildmetatag_;

	boost::mutex buildthumbnail_;
	boost::mutex checkthumbnail_;

	boost::mutex build_;
	boost::mutex buildsql_;
	boost::mutex buildthumb_;

	boost::mutex schedule_build;
	boost::mutex schedule_check;
	boost::mutex schedule_backup;

	// data

	CMyCout& log;
	config& config_;

	net_watcher net_watcher_;
	netstorage netstorage_;
	bool bStopBuildSQL;
};
#endif