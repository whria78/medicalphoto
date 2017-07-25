#pragma once

#include "basic_client.h"

#include "../share/config.h"
#include "../share/datatype.h"
#include "../share/netpath.h"
#include "../share/cmycout.h"
#include "../cximage/ximage.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

//#include "basic_async_connection.h"

class CWhriaClient :
	public basic_client
//	,basic_async_connection
{
public:
  CWhriaClient(boost::asio::io_service& io_,CMyCout& l_)
    : basic_client(io_,socket_)
//	,basic_async_connection(io_,socket_,l_)
	,socket_(io_)
	,io_service_(io_)
  {
  }

  void cmd_upload(const std::string& stNetPath,const tstring& stLocalPath);
  void cmd_tupload(const std::string& stNetPath,unsigned char* buffer,const __int64 size);


  void cmd_tdownload(const std::string& stNetPath,unsigned char** buffer_ptr,__int64& size)
  {download(THUMB_DOWNLOADFILE,ChangePath(stNetPath),buffer_ptr,size);}
   void cmd_download(const std::string& stNetPath,unsigned char** buffer_ptr,__int64& size)
   {download(DOWNLOADFILE,ChangePath(stNetPath),buffer_ptr,size);}
   void download(__int32 iOrderCode,const std::string& stNetPath,unsigned char** buffer_ptr,__int64& size,update_struct* update_struct_=NULL);

  void download(__int64 lFileSize,unsigned char* buff);
  __int64 prepare_download(__int32 iOrderCode,const std::string& stNetPath,update_struct* update_struct_=NULL);

  void server_quit()
  {__int64 blank_=0;execute_order(SERVERQUIT,blank_,blank_,blank_);}
 
  void login(const std::string& stID,const std::string& stPass,config& server_config)
  {__int64 blank_=0;execute_order(LOGIN,stID,stPass,server_config);}

  void idlesignal()
  {__int64 blank_=0;execute_order(IDLESIGNAL,blank_,blank_,blank_);}

  void get_version(version_checker& version_)
  {__int64 blank_=0;execute_order(GET_VERSIONFILE,blank_,blank_,version_);}

  void passwd_change(const std::string& stNewID,const std::string& stNewPass)
  {__int64 blank_=0;execute_order(PASSWD_CHANGE,stNewID,stNewPass,blank_);}
  
  void getuserdx(const std::string& stDiagnosis,userdx_list& result)
  {__int64 blank_=0;execute_order(GETUSERDX,stDiagnosis,blank_,result);}
  
  void setuserdx(const userdx& diagnosis_from_,const userdx& diagnosis_to_)
  {
	  if (diagnosis_from_==diagnosis() &&
		  diagnosis_to_==diagnosis())
		  return;
	  __int64 blank_=0;execute_order(SETUSERDX,diagnosis_from_,diagnosis_to_,blank_);
  }

  void getcomment(const std::vector<std::string> stNetPath_list,comment_list & result)
  {__int64 blank_=0;ChangePath(stNetPath_list);execute_order(GETCOMMENT,stNetPath_list,blank_,result);}
  
  void setcomment(const comment_list & comment_list_from_,const comment_list & comment_list_to_)
  {__int64 blank_=0;execute_order(SETCOMMENT,comment_list_from_,comment_list_to_,blank_);}

  void search_comment(const std::string stComment,fileinfo_list & result)
  {__int64 blank_=0;execute_order(SEARCHCOMMENT,ChangePath(stComment),blank_,result);}

  void getdx(const std::string& stDiagnosis,dx_list& result)
  {__int64 blank_=0;execute_order(GETDX,stDiagnosis,blank_,result);}

  void updateprevuserdx(const dx_list& dx_from,const dx_list& dx_to)
  {__int64 blank_=0;execute_order(UPDATEPREVUSERDX,dx_from,dx_to,blank_);}

  void cmd_download(const std::string& stNetPath,const std::string& stLocalPath)
  {__int64 blank_=0;execute_order(DOWNLOADFILE,ChangePath(stNetPath),blank_,blank_);}

  void update(update_struct& update_struct_,const std::string& stAppName,const std::string& stVersion);

  void deletefile(const std::string& stNetPath)
  {__int64 blank_=0;execute_order(DELETEFILE,ChangePath(stNetPath),blank_,blank_);}
  
  void renamefile(const std::string& from,const std::string& to)
  {__int64 blank_=0;execute_order(RENAMEFILE,ChangePath(from),ChangePath(to),blank_);}

  void renamefolder(const std::string& from,const std::string& to)
  {__int64 blank_=0;execute_order(RENAMEFOLDER,ChangePath(from),ChangePath(to),blank_);}

  void createfolder(const std::string& stNetPath)
  {__int64 blank_=0;execute_order(CREATEFOLDER,ChangePath(stNetPath),blank_,blank_);}

  void createfolder_auto(const std::string& stNetPathRoot,int iDateType,std::string& stCreatedPath)
  {execute_order(CREATEFOLDER_AUTO,ChangePath(stNetPathRoot),iDateType,stCreatedPath);}

  void deletefolder(const std::string& stNetPath)
  {__int64 blank_=0;execute_order(DELETEFOLDER,ChangePath(stNetPath),blank_,blank_);}
  
  void setpathinfo(const fileinfo& fileinfo_from,const fileinfo& fileinfo_to)
  {__int64 blank_=0;execute_order(SETPATHINFO,fileinfo_from,fileinfo_to,blank_);}

  void getfolderlist(const std::string& stNetPath,bool bFileOnly,fileinfo_list& result)
  {
	  execute_order(GETFOLDERLIST,ChangePath(stNetPath),bFileOnly,result);
	  std::sort(result.begin(),result.end(),sort_fileinfo());
  }

  void getvollist(volname_list& result)
  {__int64 blank_=0;execute_order(GETVOLLIST,blank_,blank_,result);}

  void searchfile(const std::vector<std::string>& stKeyword_list,const std::vector<std::string>& stField_list,fileinfo_list& result)
  {execute_order(SEARCHFILE_EXT,stKeyword_list,stField_list,result);}

  void searchfile(const std::string& stField,const std::string& stKeyword,fileinfo_list& result)
  {execute_order(SEARCH,stField,stKeyword,result);}

  void searchfile_by_date(const std::string& stFrom,const std::string& stTo,fileinfo_list& result)
  {execute_order(SEARCH_WITH_DATE,stFrom,stTo,result);}

  void searchfile_by_query(const std::string& stQuery,const std::vector<bool>& bMask,fileinfo_list& result)
  {
/*	  std::vector<bool> bMask;
	  bMask.push_back((bool)config_.Compare(SEARCH_PATH,1));
	  bMask.push_back((bool)config_.Compare(SEARCH_ID,1));
	  bMask.push_back((bool)config_.Compare(SEARCH_NAME,1));
	  bMask.push_back((bool)config_.Compare(SEARCH_DIAGNOSIS,1));
	  bMask.push_back((bool)config_.Compare(SEARCH_ICD10,1));*/
	  execute_order(SEARCH_QUERY,stQuery,bMask,result);
  }

  void searchfile_by_path(const std::string& stKeyword,fileinfo_list& result)
  {execute_order(SEARCH,ChangePath(stKeyword),std::string(fileinfo::get_primary()),result);}

  void searchfile_by_path_exact(const std::string& stKeyword,fileinfo_list& result)
  {execute_order(SEARCH_EXACT,ChangePath(stKeyword),std::string(fileinfo::get_primary()),result);}

  void search_by_path(const std::string& stKeyword,fileinfo_list& result)
  {execute_order(SEARCH_WITH_PATH,ChangePath(stKeyword),std::string(fileinfo::get_primary()),result);}

  void search_by_path_exact(const std::string& stKeyword,fileinfo_list& result)
  {execute_order(SEARCH_WITH_PATH_EXACT,ChangePath(stKeyword),std::string(fileinfo::get_primary()),result);}

  void getpathinfo(const filepath_list& list_,fileinfo_list& result)
  {__int64 blank_=0;execute_order(GETPATHINFO,list_,blank_,result);}
  
  void reloadconfig()
  {__int64 blank_=0;execute_order(RELOADCONFIG,blank_,blank_,blank_);}
  
  void setconfig(const config& config_)
  {__int64 blank_=0;execute_order(SETCONFIG,config_,blank_,blank_);}

  void image_rotate(const std::string& stNetPath,int iRotate)
  {__int64 blank_=0;execute_order(IMAGE_ROTATE,stNetPath,iRotate,blank_);}

  void download_buffer(unsigned char* buffer_,size_t& size_);
  void upload_buffer(unsigned char* buffer_,size_t size_);
protected:
	boost::asio::ip::tcp::socket socket_;
	boost::asio::io_service& io_service_;
};


//#define MAX_WHRIACACHE 5

class ImageBuffer
{
public:
	ImageBuffer()
	{
	}
	~ImageBuffer()
	{
		Clear();
//		Clear();
	}
	void Clear()
	{
		while (GetSize()>0)
		{
			EraseAt(0);
		}
	}
	int NewBuffer()
	{
		buffer_vector.push_back(NULL);
		size_vector.push_back(0);
		return (GetSize()-1);
	}
	unsigned char** GetBufferPtr(int i)
	{
//		if (i>=(int)buffer_vector.size()) return 0;
		return &buffer_vector[i];
	}
	__int64& Size(int i)
	{
//		if (i>=(int)size_vector.size()) return 0;
		return size_vector[i];
	}
	void Insert(unsigned char* buffer_ptr,__int64 size)
	{
		unsigned char* buffer=NULL;
		buffer=new unsigned char[size];
		memcpy(buffer,buffer_ptr,size);
		buffer_vector.push_back(buffer);
		size_vector.push_back(size);
	}
	void GetAt(int i,CxImage& image)
	{
		CxMemFile memfile((BYTE*)buffer_vector[i],size_vector[i]);
		if (image.Decode(&memfile,CXIMAGE_FORMAT_UNKNOWN)==false)
			return;
	}
	void EraseAt(int i)
	{		
		delete [] buffer_vector[i];
		buffer_vector.erase(buffer_vector.begin()+i);
		size_vector.erase(size_vector.begin()+i);
	}

	int GetSize() {return (int)buffer_vector.size();}
private:
	std::vector<unsigned char*> buffer_vector;
	std::vector<__int64> size_vector;
};

class CWhriaCacheClient 
	: public CWhriaClient
{
public:
	CWhriaCacheClient(boost::asio::io_service& io_,CMyCout& l_)
	: CWhriaClient(io_,l_)
	{
		MEMORYSTATUS stat;
		::GlobalMemoryStatus (&stat);
//		stat.dwTotalPhys;
		iMaxCache_Num=(int)stat.dwAvailPhys/3000000;
		bCacheOn=true;
		if (iMaxCache_Num>7) iMaxCache_Num=7;
		if (iMaxCache_Num<3)
		{
			bCacheOn=false;
		}
	}

	void cmd_download(const std::string& stNetPath,CxImage& image,__int64& size);
	void cmd_download(const std::string& stNetPath,unsigned char** buffer_ptr,__int64& size)
	{
		CWhriaClient::cmd_download(stNetPath,buffer_ptr,size);
	}
	void image_rotate(const std::string& stNetPath,int iRotate)
	{
		boost::mutex::scoped_lock lock(cache_mutex);
		CWhriaClient::image_rotate(stNetPath,iRotate);
		for (unsigned int i=0;i<stNetPath_list.size();i++)
		{
			if (strcmp(stNetPath_list[i].c_str(),stNetPath.c_str())==0)
			{
				erase(i);
			}
		}
//		ImageBuffer_.Erase(stNetPath);
	}

	void deletefile(const std::string& stNetPath);

	void renamefile(const std::string& from,const std::string& to);

	void renamefolder(const std::string& from,const std::string& to);

	void deletefolder(const std::string& stNetPath);

	void ForwardCache(const std::string& stNetPath);
	void ForwardCache_Thread(const std::string& stNetPath);
  
private:
	void erase(int iIndex)
	{
		stNetPath_list.erase(stNetPath_list.begin()+iIndex);
//		Image_list.erase(Image_list.begin()+iIndex);
		ImageBuffer_.EraseAt(iIndex);

		iFileSize_list.erase(iFileSize_list.begin()+iIndex);
	}
	/*
	void erase()
	{
		MEMORYSTATUS stat;
		::GlobalMemoryStatus (&stat);
		stat.dwTotalPhys;
		stat.dwAvailPhys;
	}
	*/

	bool bCacheOn;
	std::vector<std::string> stNetPath_list;
//	std::vector<CxImage> Image_list;
	ImageBuffer ImageBuffer_;

	std::vector<__int64> iFileSize_list;

	unsigned int iMaxCache_Num;

	boost::mutex cache_mutex;
};