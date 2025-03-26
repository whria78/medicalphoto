#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "../cximage/ximage.h"
#include "../share/file.h"
#include "../share/unicode.h"
#include "../share/cmycout.h"
#include "../share/etc.h"
#include "../share/netpath.h"
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
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
	data_manager(boost::asio::io_service& i_, boost::asio::ssl::context& context_,config& c_,CMyCout& l_);
	data_manager(boost::asio::io_service& i_, boost::asio::ssl::context& context_,config& c_);

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


	// SSL
	void socket_close()
	{
		// Cancel any ongoing operations
		socket_->lowest_layer().cancel();

		// Start async shutdown
		socket_->async_shutdown(
			boost::bind(&data_manager::shutdown_handler, this, boost::asio::placeholders::error));

		// Set a timeout for shutdown
		timer_.expires_from_now(boost::posix_time::seconds(5));
		timer_.async_wait(boost::bind(&data_manager::shutdown_timeout, this, boost::asio::placeholders::error));
	}
private:
	void shutdown_handler(const boost::system::error_code& ec)
	{
		timer_.cancel(); // Cancel timeout timer

		if (ec)
		{
			//std::cerr << "SSL shutdown error: " << ec.message() << std::endl;
			//std::wstring dumy = MCodeChanger::_CCW("SSL shutdown error: " + ec.message()); log << dumy << _T("\n");
		}

		// Close the underlying socket
		boost::system::error_code close_ec;
		socket_->lowest_layer().close(close_ec);
		if (close_ec)
		{
			//std::cerr << "Socket close error: " << close_ec.message() << std::endl;
			std::wstring dumy = MCodeChanger::_CCW("Socket close error: " + close_ec.message()); log << dumy << _T("\n");
		}
		else
		{
			//std::wstring dumy = MCodeChanger::_CCW("Socket Closed"); log << dumy << _T("\n");
		}
	}

	void shutdown_timeout(const boost::system::error_code& ec)
	{
		if (!ec) // If timeout occurred
		{
			//std::cerr << "SSL shutdown timed out. Forcing socket close." << std::endl;
			std::wstring dumy = MCodeChanger::_CCW("SSL shutdown timed out. Forcing socket close."); log << dumy << _T("\n");
			socket_->lowest_layer().close();
		}
	}


protected:
  //boost::asio::ip::tcp::socket socket_;
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket_;
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket>* socket_;
  boost::asio::io_service& io_service_;
  boost::asio::deadline_timer timer_;


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

  // 기존 handle_connect를 handshake를 고려하여 수정
  void handle_connect(boost::optional<boost::system::error_code>* socket_result,
	  const boost::system::error_code& error)
  {
	  if (!error)
	  {
		  //std::cout << "Connected, starting handshake...\n";
		  //std::wstring dumy = MCodeChanger::_CCW("Connected, starting handshake..."); log << dumy << _T("\n");
		  socket_->async_handshake(boost::asio::ssl::stream_base::client,
			  boost::bind(&data_manager::handle_handshake, this, socket_result,
				  boost::asio::placeholders::error));
	  }
	  else
	  {
		  //std::cout << "Connect failed: " << error.message() << "\n";
		  std::wstring dumy = MCodeChanger::_CCW("Connect failed: " + error.message()); log << dumy << _T("\n");
		  set_result(socket_result, error);
	  }
  }

  // handshake 완료 후 set_result 호출
  void handle_handshake(boost::optional<boost::system::error_code>* socket_result,
	  const boost::system::error_code& error)
  {
	  if (!error)
	  {
		  //std::cout << "Handshake successful!\n";
		  //std::wstring dumy = MCodeChanger::_CCW("Handshake successful!"); log << dumy << _T("\n");
	  }
	  else
	  {
		  //std::cout << "Handshake failed: " << error.message() << "\n";
		  std::wstring dumy = MCodeChanger::_CCW("Handshake failed: "+ error.message()); log << dumy << _T("\n");
	  }
	  set_result(socket_result, error); // handshake 완료 후 socket_result 설정

	  socket_close();
  }



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