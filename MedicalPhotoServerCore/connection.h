//
// connection_basic.h
// ~~~~~~~~~~~~~~
//

#ifndef MEDIEYE_SESSION_H
#define MEDIEYE_SESSION_H

#include "../share/unicode.h"
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/format.hpp>

#include "connection_basic.h"
#include "../share/config.h"
#include "../share/sql_db.h"
#include "../share/datatype.h"
#include "../share/file.h"
#include "../share/cmycout.h"
#include "../share/netpath.h"
#include "../share/etc.h"

/// The connection class provides serialization primitives on top of a socket.
/**
 * Each message sent using this class consists of:
 * @li An 8-byte header containing the length of the serialized data in
 * hexadecimal.
 * @li The serialized data.
 */

#ifdef _DEBUG
#define ORDER_WAITING_TIMEOUT 600
#define STREAMING_TIMEOUT 600
#endif
#ifndef _DEBUG
#define ORDER_WAITING_TIMEOUT 6
#define STREAMING_TIMEOUT 5
#endif

class connection_manager;

class connection 
	: 
	public connection_basic,
	public boost::enable_shared_from_this<connection>,
	private boost::noncopyable
//	: public boost::enable_shared_from_this<connection>
{
public:
  explicit connection(int connection_id_,boost::asio::io_service& io_service,config& c_,connection_manager& manager)
    : 
	connection_basic(io_service),
	connection_manager_(manager),
	config_(c_),
	log(c_.log),
	sql(c_.log),
	netpath_(c_),
	connection_id(connection_id_),
	bLogin(false)
	{
		_tpath prog_path=bfs::initial_path<_tpath>();
		prog_path /= MCodeChanger::_CCL(c_.Get(DATA_FILENAME));
		sql.Open(MCodeChanger::_CCU(prog_path.native_directory_string()));
	}
	~connection()
	{
//	  stop();
	//	  log << _T("disconnect\n");
	}

  void start() 
  {
	log<<_T("Start to receive order \n");
	handle_waiting_order();
  }
  void stop() {connection_basic::stop();}

  boost::asio::ip::tcp::socket& socket() 
  {
	  return connection_basic::socket();
  }
  std::string GetUserID() {return CurrentUser.stUserID;}
  int GetConnectionID() {return connection_id;}

private:

  connection_manager& connection_manager_;
  SQL_DB sql;
  netpath netpath_;
  config& config_;
  int connection_id;
 
  bool bLogin;
  user CurrentUser;

  std::string Transfer_Format(const std::string& str)
  {
	  std::string result=str;
	  boost::algorithm::trim(result);
	  size_t i = 0;
	  while ((i = result.find("\\")) != std::string::npos)
			result.replace(i, 1, "/");
	  return result;
  }
  // temp

//  
  command command_;

//  FILE *fp;
//  __int64 lFileSize;
//  std::string stNetPath;

  void clear()
  {
//	  fp=NULL;
	  command_.clear();
//	  connection_basic::clear();
  }

  template <typename T>
  void serial_out(boost::archive::text_oarchive& archieve,const T&t){archieve << t;}
  template <typename T>
  void serial_in(const boost::archive::text_iarchive& archieve,T&t){archieve >> t;}


  // Server Execute

  void handle_waiting_order(const boost::system::error_code& e);
  void handle_waiting_order();
  void handle_execute_order(const boost::system::error_code& e);
  void handle_filetransfer(const boost::system::error_code& e,FILE* fp,const tstring& stLocalPath,__int64 lFileSize);
  void handle_uploadprocess(const boost::system::error_code& e,const tstring& stLocalPath);
  void handle_logoff();

  bool check_netpath_priv(const std::string& stNetPath,const bool& bWrite=false)
  {
	  if (config_.GetInt(MULTIUSER_SUPPORT)==0) return true;
	  if (config_.Compare(SUPERADMIN_ID,CurrentUser.stUserID)) return true;

	  fileinfo fileinfo_;
	  if (!netpath_.GetFileInfo(stNetPath,fileinfo_))
		{process_error(SQL_ERROR,stNetPath);return false;}
	  return sql.CheckPriv(CurrentUser.stUserID,fileinfo_,bWrite);
  }


  // Error Handling

  void process_socket_error(const boost::system::error_code& e) ; 	
//  void process_socket_error(const std::string& err) 	{error_message err_;err_.Add(SOC_ERROR,err);process_error(err_);}
  void process_file_error(const std::string& err) 	{error_message err_;err_.Add(FILE_ERROR,0,err);process_error(err_);}
  void process_other_error(const std::string& err) 	{error_message err_;err_.Add(OTHER_ERROR,0,err);process_error(err_);}
  void process_error(const int& error_code,const std::string& err) 	{error_message err_;err_.Add(error_code,0,err);process_error(err_);}
  void process_error(const error_message& err);

private:
	CMyCout& log;

};

typedef boost::shared_ptr<connection> connection_ptr;
typedef std::vector<connection_ptr> connection_list;

#endif // SERIALIZATION_CONNECTION_HPP
