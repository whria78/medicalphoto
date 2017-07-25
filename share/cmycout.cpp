#include "stdafx.h"
#include "cmycout.h"

boost::mutex CMyCout::log_mutex;

#ifdef _DEBUG
#define SAVE_BUFFER_SIZE 10
#endif
#ifndef _DEBUG
#define SAVE_BUFFER_SIZE 2048
#endif

CMyCout::~CMyCout()
{
	SaveString(save_data_);

	FILE* fp_r=NULL;
	FILE* fp_w=NULL;
	char* buff=NULL;

	try
	{
		long log_size=(long)(boost::filesystem::file_size(prog_path));

		if (log_size>MEDIEYE_LOGSIZE)
		{
			fp_r=_tfopen(prog_path.c_str(),_T("rb"));
			if (fp_r==NULL) return;
			fseek(fp_r,log_size-MEDIEYE_LOGSIZE,SEEK_SET);
			buff=new char[MEDIEYE_LOGSIZE];
			size_t iRead=fread(buff,1,MEDIEYE_LOGSIZE,fp_r);
			fclose(fp_r);fp_r=NULL;

			fp_w=_tfopen(prog_path.c_str(),_T("wb"));
			if (fp_w==NULL) 
			{
				delete [] buff;
				buff=NULL;
				return;
			}
			fwrite(buff,1,MEDIEYE_LOGSIZE,fp_w);
			fclose(fp_w);fp_w=NULL;
		}
	}
	catch( const _tfilesystem_error& e )
	{
		if (fp_r!=NULL) {fclose(fp_r);fp_r=NULL;}
		if (fp_w!=NULL) {fclose(fp_w);fp_w=NULL;}
		os_ << MCodeChanger::_CCL(e.what());
	}
	catch( const std::exception& e)
	{
		if (fp_r!=NULL) {fclose(fp_r);fp_r=NULL;}
		if (fp_w!=NULL) {fclose(fp_w);fp_w=NULL;}
		os_ << MCodeChanger::_CCL(e.what());
	}
	if (buff!=NULL) 
	{
		delete [] buff;
		buff=NULL;
	}
}

CMyCout& operator<<(CMyCout& c, int data)
{

	boost::mutex::scoped_lock lock(CMyCout::log_mutex);

	TCHAR buff[255];
	_stprintf(buff,_T("%d\0"),data);

	c.data_+=buff;

	return c;
}

CMyCout& operator<<(CMyCout& c, const TCHAR* string)
{
	boost::mutex::scoped_lock lock(CMyCout::log_mutex);

	   c.data_+=string;

	   if (boost::algorithm::find_first(string,_T("\n")))
		   c.WriteAll();

	   return c;
}
CMyCout& operator<<(CMyCout& c, const tstring& string)
{
	boost::mutex::scoped_lock lock(CMyCout::log_mutex);

		c.data_+=string.c_str();

	   if (boost::algorithm::find_first(string,_T("\n")))
		   c.WriteAll();
	   return c;
}

CMyCout& operator<<(CMyCout& c, const error_message& err)
{
	boost::mutex::scoped_lock lock(CMyCout::log_mutex);

	c.data_+=MCodeChanger::_CCL(err.stErrMessage);

	if (boost::algorithm::find_first(err.stErrMessage,_T("\n")))
		   c.WriteAll();
	   return c;
}
CMyCout& operator<<(CMyCout& c, const log_struct& log_struct_)
{
	boost::mutex::scoped_lock lock(CMyCout::log_mutex);

	std::string stTimeString;
	if (log_struct_.Time!=boost::posix_time::ptime())
		stTimeString=boost::posix_time::to_simple_string(log_struct_.Time);

//	_tformat fmt(_T("%s :  %s\n"));
//	fmt % MCodeChanger::_CCL(log_struct_.stDetail);
//		% MCodeChanger::_CCL(stTimeString);

	c.SetFlag(log_struct_.iFlag);
	c.data_+=MCodeChanger::_CCL(log_struct_.stDetail);
	c.WriteAll();

   return c;
}

tstring CMyCout::WriteError(const error_message& err)
{
	boost::mutex::scoped_lock lock(CMyCout::log_mutex);

	_tformat fmt(_T("(%d) %s :  %s\n\0"));
	fmt % err.iErrCodeDetail
		% MCodeChanger::_CCL(err.stErrMessage.c_str())
		% CMyCout::endl();

	data_=fmt.str();
	WriteAll();

   return fmt.str();
}
tstring CMyCout::WriteCommand(const std::string& user_id,int iOrderCode,const std::string& param1,const std::string& param2)
{
	boost::mutex::scoped_lock lock(CMyCout::log_mutex);
	if (param2.empty() && param1.empty())
	{
		_tformat fmt(_T("[%s]\t%s\t  %s"));
		fmt
			% MCodeChanger::_CCL(command::code_to_string(iOrderCode))
			% MCodeChanger::_CCL(user_id)
			% CMyCout::endl();
		data_ = fmt.str();

		WriteAll();
		return fmt.str();
	}
	else if (param2.empty())
	{
		_tformat fmt(_T("[%s]\t%s\t( %s )  %s"));
		fmt 
			% MCodeChanger::_CCL(command::code_to_string(iOrderCode))
			% MCodeChanger::_CCL(user_id)
			% MCodeChanger::_CCL(param1)
			% CMyCout::endl();
		data_=fmt.str();

		WriteAll();
		return fmt.str();
	}
	else
	{
		_tformat fmt(_T("[%s]\t[%s]\t( %s  /  %s )  %s"));
		fmt 
			% MCodeChanger::_CCL(user_id)
			% MCodeChanger::_CCL(command::code_to_string(iOrderCode))
			% MCodeChanger::_CCL(param1)
			% MCodeChanger::_CCL(param2)
			% CMyCout::endl();
		data_=fmt.str();

		WriteAll();
		return fmt.str();
	}
}

void CMyCout::WriteAll()
{
	os_.clear();
	os_ << data_;
	WriteString(data_);
	data_.clear();
}

void CMyCout::WriteString(const tstring& str)
{
	save_data_+=str;
	if (save_data_.length()>SAVE_BUFFER_SIZE)
		SaveString(save_data_);
	iSetFlag=0;
}

void CMyCout::SaveString(tstring& save_data_)
{
	if (save_data_.length()==0) return;
	FILE* fp=_tfopen(prog_path.c_str(),_T("a"));
   if (fp!=NULL) 
   {
	   fputs(MCodeChanger::_CCN(save_data_).c_str(),fp);
	   fclose(fp);
	   save_data_.clear();
   }
}