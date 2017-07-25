#pragma once

#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <vector>
#include "file.h"
#include "datatype.h"
//#include "exif.h"
#include "thread_list.h"
#include "codechange.h"
#include "../exiv2/exif.hpp"
#include "../exiv2/image.hpp"
#include <windows.h>

class ThreadControl
{
public:
	ThreadControl(int iThreadType);
	~ThreadControl();
	bool Check(bool* bCheckTerminate=NULL);
	void Clear();
private:
	int iThreadID;
	int iThreadType;
	static std::vector<boost::tuple<int,int>> ID_list;
	static boost::mutex mutex_;
	bool* bCheckTerminate;
};

class HString
{
public:
	static tstring Left(const tstring& str,int i)
	{
		if (i>=(int)str.size())
			return str;
		if (i<=0)
			return _T("");

		TCHAR* dumy;
		dumy=new TCHAR[i+1];
		dumy[i]=NULL;

		str.copy(dumy,i);
		tstring result(dumy);
		delete dumy;
		return result;
	}
	static std::string Left(const std::string& str,int i)
	{
		if (i>=(int)str.size())
			return str;
		if (i<=0)
			return "";

		char* dumy;
		dumy=new char[i+1];
		dumy[i]=NULL;

		str.copy(dumy,i);
		std::string result(dumy);
		delete dumy;
		return result;
	}

	static std::string Mid(const std::string& str,int iStart,int i)
	{
//		if (i>=(int)str.size())
//			return str;
		if (i<=0)
			return "";
		if (iStart>=(int)str.size())
			return "";
		if (i>(int)str.length()-iStart)
			i=str.length()-iStart;

		char* dumy;
		dumy=new char[i+1];
		dumy[i]=NULL;

		str.copy(dumy,i,iStart);
		std::string result(dumy);
		delete dumy;
		return result;
	}

	static tstring Right(const tstring& str,int i)
	{
		if (i>=(int)str.size())
			return str;
		if (i<=0)
			return _T("");

		TCHAR* dumy;
		dumy=new TCHAR[i+1];
		dumy[i]=NULL;

		str.copy(dumy,i,str.size()-i);
		tstring result(dumy);
		delete dumy;
		return result;
	}
	static std::string Right(const std::string& str,int i)
	{
		if (i>=(int)str.size())
			return str;
		if (i<=0)
			return "";

		char* dumy;
		dumy=new char[i+1];
		dumy[i]=NULL;

		str.copy(dumy,i,str.size()-i);
		std::string result(dumy);
		delete dumy;
		return result;
	}
};
class Utility
{
public:
	static void SplitParams(const std::string& temp_string,std::vector<std::string>& param_list)
	{
		param_list.clear();
		std::vector<std::string> split_vec;
		boost::split(split_vec,temp_string,boost::is_any_of(","));

		unsigned int i;
		for (i=0;i<split_vec.size();i++)
		{
			boost::algorithm::trim(split_vec[i]);
			param_list.push_back(split_vec[i]);
		}
	}
	static bool RedoBackupFile(const tstring& stFilePath,const tstring& stDestPath)
	{
		sleep_sec(1);
		try
		{
			boost::filesystem::remove(_tpath(stFilePath));
			boost::filesystem::rename(_tpath(stDestPath),_tpath(stFilePath));
		}
		catch (std::exception& e)
		{
			e.what();
			return false;
		}

		catch(...)
		{
			return false;
		}
		return true;
	}

	static bool BackupFile(const tstring& stFilePath,tstring& stDestPath)
	{
		_tpath dest_path(stFilePath);

		_tpath backup_path=dest_path.parent_path();
		tstring backup_filename=dest_path.filename().c_str();
		backup_filename+=_T(".old");
		backup_path /= backup_filename; backup_path = Utility::refinepath(backup_path);

		int iRenameCount=0;

		stDestPath=Utility::GetNumericName(iRenameCount,backup_path.c_str());
		iRenameCount++;

		try
		{
			while (boost::filesystem::exists(_tpath(stDestPath)))
			{
				stDestPath=GetNumericName(iRenameCount,backup_path.c_str());
				iRenameCount++;
			}
			boost::filesystem::copy_file(_tpath(stFilePath),_tpath(stDestPath));
			return true;
		}
		catch(...)
		{
			return false;
		}
	}

	static std::string GetDateString(const boost::posix_time::ptime& Time)
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


	static int GetLastInputTime()
	{
		DWORD idleTime = 0;
		LASTINPUTINFO lastInputInfo;

		lastInputInfo.cbSize = sizeof(lastInputInfo);
		lastInputInfo.dwTime = 0;
 
		DWORD curTicks = GetTickCount();
		if(GetLastInputInfo(&lastInputInfo))
		{
			DWORD lastInputTick = lastInputInfo.dwTime;
			idleTime = curTicks - lastInputTick;
		}
		return ((idleTime > 0) ? (idleTime / 1000) : idleTime);
	}

/*	static bool CopyMetatag(const tstring& stLocalPathFrom,Exiv2::Image::AutoPtr& readImg)
	{
		try
		{
			Exiv2::Image::AutoPtr readImg = Exiv2::ImageFactory::open(MCodeChanger::_CCN(stLocalPathFrom));
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
	static bool PasteMetatag(Exiv2::Image::AutoPtr& readImg,const tstring& stLocalPathTo)
	{
		try
		{
			Exiv2::Image::AutoPtr writeImg = Exiv2::ImageFactory::open(MCodeChanger::_CCN(stLocalPathTo));

			writeImg->setIptcData(readImg->iptcData());
			writeImg->setExifData(readImg->exifData());
			writeImg->setComment(readImg->comment());

			return true;
		}
		catch (...)
		{
			return false;
		}
	}
*/

	static bool LoadMetatag(const tstring& stLocalPath,boost::posix_time::ptime& Time)
	{
/*		FILE* hFile=_tfopen(stLocalPath.c_str(),_T("rb"));
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
				
				Time=boost::posix_time::time_from_string(fmt.str());

				return true;

				}
				catch (...)
				{
					return false;
				}
			}
			else
				return false;
		}
		return false;
		*/
						
		try{
//				std::string str=m_exifinfo.DateTime;

				Exiv2::Image::AutoPtr readImg = Exiv2::ImageFactory::open(MCodeChanger::_CCN(stLocalPath));
				readImg->readMetadata();
		//		Exiv2::IptcData iptcData=readImg->iptcData();
				Exiv2::ExifData exifData=readImg->exifData();
				std::string str=exifData["Exif.Photo.DateTimeOriginal"].toString();

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
				
				Time=boost::posix_time::time_from_string(fmt.str());

				return true;
			}
			catch (...)
			{
				return false;
			}
	}
	static _tpath refinepath(_tpath path_)
	{
		tstring temp = path_.c_str();
		boost::replace_all(temp, _T("\\"), _T("/"));
		return _tpath(temp);
	}

	static void GetAllSubFiles(const _tpath& _tpath_,std::vector<_tpath>& _tpath_list)
	{
		if (!boost::filesystem::is_directory(_tpath_))
			return;
		std::vector<_tpath> dir_list;
		_tdirectory_iterator end_iter;
		for ( _tdirectory_iterator dir_itr( _tpath_ );
		  dir_itr != end_iter;
		  ++dir_itr )
		{
			_tpath temp = refinepath(*dir_itr);

			if (boost::filesystem::is_directory(temp))
			{
				dir_list.push_back(temp);
			}
			else
			{
				_tpath_list.push_back(temp);
			}
		}
		for (unsigned int i=0;i<dir_list.size();i++)
		{
			GetAllSubFiles(dir_list[i],_tpath_list);
		}
	}

	static tstring GetDateString(const boost::gregorian::date &today,int iType)
	{
		try
		{
			_tformat stDate;

			_tformat a(_T("%d")),b(_T("%d"));
			a % today.month().as_number();
			b % today.day().as_number();
			tstring month_string=a.str();
			tstring day_string=b.str();
			while (month_string.length()<2)
			{
				tstring dumy=_T("0");
				dumy+=month_string;
				month_string=dumy;
			}
			while (day_string.length()<2)
			{
				tstring dumy=_T("0");
				dumy+=day_string;
				day_string=dumy;
			}

			switch (iType)
			{
			case 0:    // 01-01
				 {
					stDate=_tformat(_T("%s-%s"));
					stDate % month_string
						% day_string;
				 }
				 break;
			case 1:    // Jan-01
				 {
					stDate=_tformat(_T("%s-%s"));
					stDate % today.month()
						% day_string;
				 }
				 break;
			case 2:   // 2008-01-01
				 {
					stDate=_tformat(_T("%s-%s-%s"));
					stDate % today.year()
						% month_string
						% day_string;
				 }
				 break;
			case 3:   // 2008-Jan-01
				 {
					stDate=_tformat(_T("%s-%s-%s"));
					stDate % today.year() 
						% today.month()
						% day_string;
				 }
				 break;
			case 4:   // 08-01-01
				 {
					_tformat stYear(_T("%d"));
					stYear % today.year();
					stDate=_tformat(_T("%s-%s-%s"));
					stDate % HString::Right(stYear.str(),2) 
						% today.month()
						% day_string;
				 }
				 break;
			case 5:   // 08-Jan-01
				 {
					_tformat stYear(_T("%d"));
					stYear % today.year();
					stDate=_tformat(_T("%s-%s-%s"));
					stDate % HString::Right(stYear.str(),2) 
						% month_string
						% day_string;
				 }
				 break;
			default:
				{
					return _T("");
				}
				break;
			}
			return stDate.str();
		}
		catch (...)
		{
			return _T("");
		}
	}
	static tstring GetToday(int iType)
	{
		boost::gregorian::date today(boost::gregorian::day_clock::local_day());
		return GetDateString(today,iType);
	}

   static void sleep(int msec)
    {
		boost::xtime xt;
		xtime_get(&xt, TIME_UTC);
		xt.nsec += msec*1000000;
		boost::thread::sleep(xt);
    }
   static void sleep_sec(int sec)
    {
	   boost::xtime xt;
	   xtime_get(&xt,TIME_UTC);
	   xt.sec+=sec;
	   boost::thread::sleep(xt);
    }
   static void sleep(int week,int hour,int minute)
   {
	   if (week>6 || hour>>23 || minute>59) 
		   throw std::logic_error("Invalid Date&Time Range");

	   boost::gregorian::date from(boost::gregorian::day_clock::local_day());
	   boost::gregorian::date to;

	   if (week==-1)
		   to=from + boost::gregorian::date_duration(1);
	   else
	   {
		   int iNextWeek=abs(week-from.day_of_week().as_number());
		   if (iNextWeek==0)
			   to=from + boost::gregorian::date_duration(7);
		   else
			   to=from + boost::gregorian::date_duration(iNextWeek);
	   }

	   int hour_duration_=0;
	   int minute_duration_=0;
	   if (hour!=-1) hour_duration_=hour;
	   if (minute!=-1) minute_duration_=minute;

	   boost::posix_time::ptime aa=boost::posix_time::ptime(to,boost::posix_time::time_duration(hour_duration_,minute_duration_,0,0));
	   boost::posix_time::ptime bb=boost::posix_time::ptime(boost::posix_time::second_clock::local_time());
	   boost::posix_time::time_duration sleep_time=aa-bb;

	   boost::xtime xt;
	   xtime_get(&xt,TIME_UTC);
	   xt.sec+=sleep_time.total_seconds();;

	   boost::thread::sleep(xt);
   }
   static tstring GetNumericName(int iRenameCount,const tstring& stPath);

	template <typename T>
	static void DeleteDup_by_NetPath(const T&org_list,T&result)
	{
		filepath_list filepath_list_;
		DeleteDup_by_NetPath(org_list,result,filepath_list_);
	}

	template <typename T>
	static void DeleteDup_by_NetPath(const T&org_list,T&result,filepath_list& filepath_list_)
	{
		for (unsigned int i=0;i<org_list.size();i++)
		{
		  bool bExist=false;
		  for (unsigned int j=0;j<filepath_list_.size();j++)
		  {
			  if (strcmp(org_list[i].GetNetPath().c_str(),filepath_list_[j].c_str())==0)
			  {bExist=true;break;}
		  }
		  if (!bExist)
		  {
			  filepath_list_.push_back(org_list[i].GetNetPath());
			  result.push_back(org_list[i]);
		  }
		}
	}
	template <typename T>
	static void DeleteDup_by_NetPath(const T&org_list1,const T&org_list2,T&result)
	{
		filepath_list filepath_list_;
		DeleteDup_by_NetPath(org_list1,result,filepath_list_);
		DeleteDup_by_NetPath(org_list2,result,filepath_list_);
	}

	template <typename T>
	static void DeleteDup(const T& data,T& result)
	{
		result=data;
		if (data.size()<2) return;

		for (int i=(data.size()-1);i>=0;i--)
		{
			for (int j=0;j<i;j++)
			{
				if (data[i]==data[j] && i!=j)
				{
					result.erase(result.begin()+i);
					break;
				}
			}
		}
	}
	static void DeleteDupString(const std::vector<std::string>& data,std::vector<std::string>& result)
	{
		result=data;
		if (data.size()<2) return;

		for (size_t i=(data.size()-1);i>=0;i--)
		{
			for (size_t j=0;j<i;j++)
			{
				if (strcmp(data[i].c_str(),data[j].c_str())==0 && i!=j)
				{
					result.erase(result.begin()+i);
					break;
				}
			}
		}
	}
	static void DeleteDupString(const std::vector<tstring>& data,std::vector<tstring>& result)
	{
		result=data;
		if (data.size()<2) return;

		for (size_t i=(data.size()-1);i>=0;i--)
		{
			for (size_t j=0;j<i;j++)
			{
				if (_tcscmp(data[i].c_str(),data[j].c_str())==0 && i!=j)
				{
					result.erase(result.begin()+i);
					break;
				}
			}
		}
	}
	static std::string Transfer_Format(const std::string& str)
	{
	  std::string result=str;
	  boost::algorithm::trim(result);
	  size_t i = 0;
	  while ((i = result.find("\\")) != std::string::npos)
			result.replace(i, 1, "/");
	  return result;
	}
	static std::string ChangePath(const std::string& str)
	{
		return MCodeChanger::_CCU(_tpath(MCodeChanger::_CCL(str)).c_str());
	}
	static tstring RefinePath(const tstring& str)
	{
		return _tpath(str).c_str();
	}
	static bool ComparePath(const tstring& from,const tstring& to)
	{
		if (_tcscmp(_tpath(from).c_str()
			,_tpath(to).c_str())==0)
			return true;
		else
			return false;
	}
	static std::string GetTimeString(boost::posix_time::ptime& Time)
	{
		if (Time==boost::posix_time::ptime())
			return "";
		else
			return boost::posix_time::to_simple_string(Time);
	}

	static void split( const tstring & s, const tstring & delimiter,std::vector<tstring>& newrow)
	{
	   std::size_t bpos, epos;
	   bpos = 0;
	   while(true){
		   epos = s.find_first_of(delimiter, bpos);
		   if(epos == tstring::npos){
			   newrow.push_back(s.substr(bpos, s.length() - bpos + 1));
			   break;
		   }
		   newrow.push_back(s.substr(bpos, epos - bpos));
		   bpos = epos + 1;
	   }
	}

	static tstring GetFilename(tstring str)
	{
		boost::algorithm::replace_all(str,_T("\\"),_T("_"));
		boost::algorithm::replace_all(str,_T("/"),_T("_"));
		boost::algorithm::replace_all(str,_T(":"),_T("_"));
		boost::algorithm::replace_all(str,_T("*"),_T("_"));
		boost::algorithm::replace_all(str,_T("?"),_T("_"));
		boost::algorithm::replace_all(str,_T("\""),_T("_"));
		boost::algorithm::replace_all(str,_T("<"),_T("_"));
		boost::algorithm::replace_all(str,_T(">"),_T("_"));
		boost::algorithm::replace_all(str,_T("|"),_T("_"));
		boost::algorithm::replace_all(str,_T("%"),_T("_"));
		boost::algorithm::replace_all(str,_T("#"),_T("_"));
		boost::algorithm::replace_all(str,_T("$"),_T("_"));
		return str;
	}
	template <typename T>
	static void serialout(boost::archive::text_oarchive& archive_out,const T& t)
	{
		archive_out << t;
	}

	static void DeleteOldFiles(const _tpath path,int iHour)
	{
		_tdirectory_iterator end_iter;
		if (!boost::filesystem::exists(path))
			return;

		bool bEmpty=true;
		std::vector<_tpath> dir_list;
		for ( _tdirectory_iterator dir_itr(path);
		  dir_itr != end_iter;
		  ++dir_itr )
		{
			_tpath temp = refinepath(*dir_itr);

			bEmpty=false;
			if (boost::filesystem::is_directory(temp))
			{
				dir_list.push_back(temp);
			}
			else
			{
				std::time_t ft=boost::filesystem::last_write_time(temp);
				boost::posix_time::ptime last_write_time_=boost::posix_time::from_time_t(ft);
				boost::posix_time::to_simple_string(last_write_time_);
				boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time());
				
				boost::posix_time::time_duration time_gap=boost::posix_time::second_clock::local_time()-last_write_time_;
				boost::posix_time::to_simple_string(time_gap);

			   if (time_gap > boost::posix_time::hours(iHour))
			   {
				   boost::filesystem::remove(temp);
			   }
			}
		}
		if (bEmpty)
		{
			boost::filesystem::remove(path);
		}
		for (unsigned int i=0;i<dir_list.size();i++)
		{
			DeleteOldFiles(dir_list[i],iHour);
		}
	}
/*	static void GetAllSubFiles(const _tpath path,std::vector<_tpath>& stResult)
	{
		_tdirectory_iterator end_iter;

		for ( _tdirectory_iterator dir_itr(path);
		  dir_itr != end_iter;
		  ++dir_itr )
		{
			if (boost::filesystem::is_directory(*dir_itr))
			{
				GetAllSubFiles(*dir_itr,stResult);
			}
			else
			{
				stResult.push_back(*dir_itr);
			}
		}
	}
*/
#ifdef _WIN32
   static HWND GetConsoleHwnd(void)
   {
       #define MY_BUFSIZE 1024 // Buffer size for console window titles.
       HWND hwndFound;         // This is what is returned to the caller.
       TCHAR pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
                                           // WindowTitle.
       TCHAR pszOldWindowTitle[MY_BUFSIZE]; // Contains original
                                           // WindowTitle.

       // Fetch current window title.

       GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);

       // Format a "unique" NewWindowTitle.

       wsprintf(pszNewWindowTitle,_T("%d/%d"),
                   GetTickCount(),
                   GetCurrentProcessId());

       // Change current window title.

       SetConsoleTitle(pszNewWindowTitle);

       // Ensure window title has been updated.

       Sleep(40);

       // Look for NewWindowTitle.

       hwndFound=FindWindow(NULL, pszNewWindowTitle);

       // Restore original window title.

       SetConsoleTitle(pszOldWindowTitle);

       return(hwndFound);
   }
#endif
};

