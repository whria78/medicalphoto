#include "stdafx.h"

#include "WhriaClient.h"

void CWhriaClient::update(update_struct& update_struct_,const std::string& stAppName,const std::string& stVersion)
{
	unsigned char* buffer=NULL;
	__int64 size=0;

	download(UPDATE,stVersion,&buffer,size,&update_struct_);
	
	FILE* fp;
	
	MFile::DeleteL(version_checker::GetTemp(stAppName));

	fp=_tfopen(version_checker::GetTemp(stAppName).c_str(),_T("wb"));
	if (fp==NULL) return;
	fwrite(buffer,1,size,fp);

	if (buffer!=NULL) delete [] buffer;
	if (fp!=NULL) {fclose(fp);fp=NULL;}
}

void CWhriaClient::download(__int32 iOrderCode,const std::string& stNetPath,unsigned char** buffer_ptr,__int64& size,update_struct* update_struct_)
{
	boost::mutex::scoped_lock lock(mutex_);
	
	size=prepare_download(iOrderCode,stNetPath,update_struct_);
	if (size<=0)
	  throw basic_client::ConnectionEx(SIZE_ERROR);

	(*buffer_ptr)=new unsigned char[size];

	download(size,(*buffer_ptr));
}

__int64 CWhriaClient::prepare_download(__int32 iOrderCode,const std::string& stNetPath,update_struct* update_struct_)
{

	command cmd_;cmd_.order_code=iOrderCode;

  
	try
    {
		std::ostringstream archive_stream;
	 	boost::archive::text_oarchive archive(archive_stream);
		client_connection::serial_out(archive,cmd_);
		if (update_struct_!=NULL)
			client_connection::serial_out(archive,*update_struct_);
		client_connection::serial_out(archive,stNetPath);
		client_connection::OutboundBuffer()= archive_stream.str();
	}
    catch (std::exception& e)
    {
		  client_connection::free_InboundBuffer();
		  throw client_connection::ConnectionEx(DECODING_DATA,0,e.what());
    }
	client_connection::async_write();


	size_t lfileSize=0;
	error_message err_;

	client_connection::async_read_header();
	client_connection::async_read_data();

	try
    {
        std::istringstream archive_stream(client_connection::InboundBuffer());
        boost::archive::text_iarchive archive(archive_stream);
        archive >> err_;
		if (!err_.CheckError())
			archive >> lfileSize;
		if (lfileSize<0) lfileSize=0;
		client_connection::free_InboundBuffer();
    }
    catch (std::exception& e)
    {
		// Unable to decode data.
		client_connection::free_InboundBuffer();
		throw client_connection::ConnectionEx(DECODING_DATA,0,e.what());
    }

	if (err_.CheckError())
	{
		if (err_.iErrCode==SOC_ERROR)
			throw client_connection::ConnectionEx(err_);
		else
			throw basic_client::ConnectionEx(err_);
	}

	return lfileSize;
}

void CWhriaClient::download(__int64 lFileSize,unsigned char* buffer_)
{
//	boost::mutex::scoped_lock lock(mutex_);

	size_t iRemain=lFileSize;
//	buffer_=new unsigned char[lFileSize];
//	buffer_=new unsigned char[BUFFER_SIZE];
	
	while (iRemain>0)
	{
		if (iRemain<BUFFER_SIZE)
		{
			size_t iTransferred=iRemain;
			download_buffer(buffer_+lFileSize-iRemain,iTransferred);
			iRemain-=iTransferred;
		}
		else
		{
			size_t iTransferred=BUFFER_SIZE;
			download_buffer(buffer_+lFileSize-iRemain,iTransferred);
			iRemain-=iTransferred;
		}
	}
}


void CWhriaClient::download_buffer(unsigned char* buffer_,size_t& size_)
{
	boost::optional<boost::system::error_code> timer_result; 
    boost::asio::deadline_timer timer(io_service_);
    timer.expires_from_now(boost::posix_time::seconds(FILETRANSFER_TIMEOUT)); 
	timer.async_wait(boost::bind(&CWhriaClient::set_stream_result,this,
		&timer_result, boost::asio::placeholders::error)); 

	boost::optional<boost::system::error_code> socket_result;

	socket_.async_read_some(boost::asio::buffer(buffer_,size_),
		boost::bind(&CWhriaClient::set_result, this,
		&socket_result,
		boost::asio::placeholders::error,
		&size_,
		boost::asio::placeholders::bytes_transferred
		));

	io_service_.reset();
    while (io_service_.run_one())
    { 
      if (socket_result) 
        timer.cancel(); 
      else if (timer_result)
	  {
		  throw client_connection::ConnectionEx(TIMEOUT);
	  }
    } 
	if (*socket_result)
	{
		throw client_connection::ConnectionEx(SOC_ERROR,socket_result->value(),socket_result->message());
	}
}

void CWhriaClient::cmd_upload(const std::string& stNetPath,const tstring&stLocalPath)
{
	boost::mutex::scoped_lock lock(mutex_);

	__int64 lFileSize=MFile::FileSizeL(stLocalPath);
	if (lFileSize<=0)
		  throw basic_client::ConnectionEx(SIZE_ERROR);

	FILE* fp=_tfopen(stLocalPath.c_str(),_T("rb"));
	if (fp==NULL)
		  throw basic_client::ConnectionEx(FILE_READ_OPEN);

	command cmd_;cmd_.order_code=UPLOADFILE;

    try
    {
	    std::ostringstream archive_stream;
	    boost::archive::text_oarchive archive(archive_stream);
		client_connection::serial_out(archive,cmd_);
		client_connection::serial_out(archive,stNetPath);
		client_connection::serial_out(archive,lFileSize);
		client_connection::OutboundBuffer()= archive_stream.str();
	}
    catch (std::exception& e)
    {
		if (fp!=NULL) {fclose(fp);fp=NULL;}
		  client_connection::free_InboundBuffer();
		  throw client_connection::ConnectionEx(DECODING_DATA,0,e.what());
    }
	client_connection::async_write();


	error_message err_;
	client_connection::async_read_header();
	client_connection::async_read_data();

	try
    {
        std::istringstream archive_stream(client_connection::InboundBuffer());
        boost::archive::text_iarchive archive(archive_stream);
        archive >> err_;
		client_connection::free_InboundBuffer();
    }
    catch (std::exception& e)
    {
		// Unable to decode data.
		client_connection::free_InboundBuffer();
		if (fp!=NULL) {fclose(fp);fp=NULL;}
		throw client_connection::ConnectionEx(DECODING_DATA,0,e.what());
    }

	if (err_.CheckError())
	{
		if (fp!=NULL) {fclose(fp);fp=NULL;}
		if (err_.iErrCode==SOC_ERROR)
			throw client_connection::ConnectionEx(err_);
		else
			throw basic_client::ConnectionEx(err_);
	}


	unsigned char buffer_[BUFFER_SIZE];

	__int64 lTransferred=0;
	__int64 lRemain=lFileSize;

	__int64 lSend;

	while (lSend=fread(buffer_,sizeof(unsigned char),BUFFER_SIZE,fp))
	{
		upload_buffer(buffer_,lSend);
		lRemain-=lSend;
		lTransferred+=lSend;
	}

	if (lTransferred!=lFileSize)
	{
		if (fp!=NULL) {fclose(fp);fp=NULL;}
		throw basic_client::ConnectionEx(SIZE_ERROR);
	}

	if (fp!=NULL) {fclose(fp);fp=NULL;}
}

void CWhriaClient::upload_buffer(unsigned char* buffer_,size_t size_)
{
	boost::optional<boost::system::error_code> timer_result; 
    boost::asio::deadline_timer timer(io_service_);
    timer.expires_from_now(boost::posix_time::seconds(FILETRANSFER_TIMEOUT)); 
	timer.async_wait(boost::bind(&CWhriaClient::set_stream_result,this,
		&timer_result, boost::asio::placeholders::error)); 

	boost::optional<boost::system::error_code> socket_result; 

    boost::asio::async_write(socket_, boost::asio::buffer(buffer_,size_),
		boost::bind(&CWhriaClient::set_stream_result, this,
		&socket_result,boost::asio::placeholders::error));

	io_service_.reset();
    while (io_service_.run_one())
    { 
      if (socket_result) 
        timer.cancel(); 
      else if (timer_result)
	  {
		  throw client_connection::ConnectionEx(TIMEOUT);
	  }
    } 
	if (*socket_result)
	{
		throw client_connection::ConnectionEx(SOC_ERROR,socket_result->value(),socket_result->message());
	}

}


void CWhriaClient::cmd_tupload(const std::string& stNetPath,unsigned char* buffer,const __int64 size)
{
	boost::mutex::scoped_lock lock(mutex_);

	if (size<=0)
		  throw basic_client::ConnectionEx(SIZE_ERROR);

	command cmd_;cmd_.order_code=THUMB_UPLOADFILE;

    try
    {
	    std::ostringstream archive_stream;
	    boost::archive::text_oarchive archive(archive_stream);
		client_connection::serial_out(archive,cmd_);
		client_connection::serial_out(archive,stNetPath);
		client_connection::serial_out(archive,__int64(size));
		client_connection::OutboundBuffer()= archive_stream.str();
	}
    catch (std::exception& e)
    {
		  client_connection::free_InboundBuffer();
		  throw client_connection::ConnectionEx(DECODING_DATA,0,e.what());
    }
	client_connection::async_write();


	error_message err_;

	client_connection::async_read_header();
	client_connection::async_read_data();
	client_connection::InboundBuffer();

	try
    {
        std::istringstream archive_stream(client_connection::InboundBuffer());
        boost::archive::text_iarchive archive(archive_stream);
        archive >> err_;
		client_connection::free_InboundBuffer();
    }
    catch (std::exception& e)
    {
		// Unable to decode data.
		client_connection::free_InboundBuffer();
		throw client_connection::ConnectionEx(DECODING_DATA,0,e.what());
    }

	if (err_.CheckError())
	{
		if (err_.iErrCode==SOC_ERROR)
			throw client_connection::ConnectionEx(err_);
		else
			throw basic_client::ConnectionEx(err_);
	}

	__int64 lTransferred=0;
	__int64 lRemain=size;

	__int64 lSend;

	while (lRemain>0)
	{
		lSend=BUFFER_SIZE;
		if (lRemain<BUFFER_SIZE) lSend=lRemain;

		upload_buffer(buffer+lTransferred,lSend);

		lRemain-=lSend;
		lTransferred+=lSend;
	}
}

/*
  template <typename Param1,typename Param2,typename Result>
  void CWhriaClient::execute_order(__int32 order_code_,Param1 p1_,Param2 p2_,Result result_)
  {
	boost::mutex::scoped_lock lock(mutex_);

	command cmd_;cmd_.order_code=order_code_;

    try
    {
	    std::ostringstream archive_stream;
	    boost::archive::text_oarchive archive(archive_stream);
		serial_out(archive,cmd_);
		serial_out(archive,p1_);
		serial_out(archive,p2_);
		client_connection::OutboundBuffer()= archive_stream.str();
	}
    catch (std::exception& e)
    {
		  client_connection::free_InboundBuffer();
		  throw client_connection::ConnectionEx(DECODING_DATA,0,e.what());
    }
	client_connection::async_write();

	error_message err_;

	client_connection::async_read_header();
	client_connection::async_read_data();
	try
    {
        std::istringstream archive_stream(client_connection::InboundBuffer());
        boost::archive::text_iarchive archive(archive_stream);
        archive >> result_ >> err_;
		client_connection::free_InboundBuffer();
    }
    catch (std::exception& e)
    { 
		// Unable to decode data.
		client_connection::free_InboundBuffer();
		throw client_connection::ConnectionEx(DECODING_DATA,0,e.what());
    }

	if (err_.CheckError())
		throw client_connection::ConnectionEx(err_);
  }

*/


void CWhriaCacheClient::ForwardCache_Thread(const std::string& stNetPath)
{
	int iIndex=-1;
	try
	{
		Utility::sleep(500);
		boost::mutex::scoped_lock lock(cache_mutex);

		if (stNetPath_list.size()>iMaxCache_Num)
		{
			erase(0);
		}

		for (unsigned int i=0;i<stNetPath_list.size();i++)
		{
			if (strcmp(stNetPath.c_str(),stNetPath_list[i].c_str())==0)
			{
				return;
			}
		}

		__int64 size=0;
		iIndex=ImageBuffer_.NewBuffer();

		CWhriaClient::cmd_download(stNetPath
			,ImageBuffer_.GetBufferPtr(iIndex)
			,size);

		ImageBuffer_.Size(iIndex)=size;

		stNetPath_list.push_back(stNetPath);
		iFileSize_list.push_back(size);

	}
	catch(...)
	{
		if (iIndex!=-1)
			ImageBuffer_.EraseAt(iIndex);
	}
}

void CWhriaCacheClient::cmd_download(const std::string& stNetPath,CxImage& image,__int64& size)
	{
		boost::mutex::scoped_lock lock(cache_mutex);

		if (bCacheOn)
		{
			if (stNetPath_list.size()>iMaxCache_Num)
			{
				erase(0);
			}

			for (unsigned int i=0;i<stNetPath_list.size();i++)
			{
				if (strcmp(stNetPath.c_str(),stNetPath_list[i].c_str())==0)
				{
//					image=Image_list[i];
					ImageBuffer_.GetAt(i,image);
					size=iFileSize_list[i];
					return;
				}
			}
		}

		int iIndex=ImageBuffer_.NewBuffer();

		try
		{
			CWhriaClient::cmd_download(stNetPath
				,ImageBuffer_.GetBufferPtr(iIndex)
				,size);
		}
		catch (const client_connection::ConnectionEx& err_)
		{
			ImageBuffer_.EraseAt(iIndex);
			throw client_connection::ConnectionEx(err_);
		}
		catch (const basic_client::ConnectionEx& err_)
		{
			ImageBuffer_.EraseAt(iIndex);
			throw basic_client::ConnectionEx(err_);
		}

		CxMemFile memfile((BYTE*)(*ImageBuffer_.GetBufferPtr(iIndex)),size);
		if (image.Decode(&memfile,CXIMAGE_FORMAT_UNKNOWN)==false)
		{
			ImageBuffer_.EraseAt(iIndex);
			size=0;
			return;
		}

		if (bCacheOn)
		{
			ImageBuffer_.Size(iIndex)=size;
			stNetPath_list.push_back(stNetPath);
			iFileSize_list.push_back(size);
		}
		else
		{
			ImageBuffer_.EraseAt(iIndex);
		}
	}

	void CWhriaCacheClient::deletefile(const std::string& stNetPath)
	{
		boost::mutex::scoped_lock lock(cache_mutex);
		CWhriaClient::deletefile(stNetPath);

		if (bCacheOn)
		{
			for (unsigned int i=0;i<stNetPath_list.size();i++)
			{
				if (strcmp(stNetPath.c_str(),stNetPath_list[i].c_str())==0)
				{
					erase(i);
					return;
				}
			}
		}
	}

	void CWhriaCacheClient::renamefile(const std::string& from,const std::string& to)
	{
		boost::mutex::scoped_lock lock(cache_mutex);
		CWhriaClient::renamefile(from,to);

		if (bCacheOn)
		{

			for (unsigned int i=0;i<stNetPath_list.size();i++)
			{
				if (strcmp(from.c_str(),stNetPath_list[i].c_str())==0)
				{
					stNetPath_list[i]=to;
					return;
				}
			}
		}
	}

	void CWhriaCacheClient::renamefolder(const std::string& from,const std::string& to)
	{
		boost::mutex::scoped_lock lock(cache_mutex);
		CWhriaClient::renamefolder(from,to);

		if (bCacheOn)
		{

			for (unsigned int i=0;i<stNetPath_list.size();i++)
			{
				if (stNetPath_list[i].find(from)==0)
				{
					boost::algorithm::replace_first(stNetPath_list[i],from,to);
				}
			}
		}

	}

	void CWhriaCacheClient::deletefolder(const std::string& stNetPath)
	{
		boost::mutex::scoped_lock lock(cache_mutex);
		CWhriaClient::deletefolder(stNetPath);

		if (bCacheOn)
		{

			for (unsigned int i=0;i<stNetPath_list.size();i++)
			{
				if (stNetPath_list[i].find(stNetPath)==0)
				{
					erase(i);
				}
			}
		}
	}

	void CWhriaCacheClient::ForwardCache(const std::string& stNetPath)
	{
		if (!bCacheOn) return;
		boost::thread BuildThread(boost::bind(&CWhriaCacheClient::ForwardCache_Thread,this,stNetPath));
	}
