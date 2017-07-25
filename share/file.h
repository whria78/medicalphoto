////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../boost.h"
#include "datatype.h"
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/format.hpp>
//#include "../share/error.h"
#include "codechange.h"
#include "cmycout.h"
#include <boost/algorithm/string.hpp>
#include "unicode.h"

namespace bfs=boost::filesystem; 
typedef std::vector<_tpath> path_list;

#include "etc.h"
//class Utility;
//class fileinfo;

class MFile
{
public:
	static void ProcessError(const tstring & str,const tstring & param1,const tstring & param2=_T(""))
	{
		CMyCout log(_tcout);
		_tformat fmt(_T("File Error : %s %s %s"));
		fmt % str % param1 % param2;
		log << fmt.str();
	}
#ifdef _UNICODE
	static void ProcessError(const std::string & str,const tstring & param1,const tstring & param2=_T(""))
	{
		ProcessError(MCodeChanger::_CCL(str),param1,param2);
	}
#endif
	static _tpath GetInitialPath()
	{
		try
		{
			return bfs::initial_path<_tpath>();
		}
		catch( const _tfilesystem_error& e )
		{
			ProcessError(e.what(),_T(""));
			return _tpath();
		}
	}
	static tstring GetLocal(const _tpath& p) {return p.c_str();}
	static std::string UTF8Clear(const std::string& str)
	{
		return MCodeChanger::_CCU(_tpath(MCodeChanger::_CCL(str)).c_str());
	}
	static tstring UTF8Clear(tstring str)
	{
		return _tpath(str).c_str();
	}

	static tstring LocalClear(tstring str)
	{
		return _tpath(str).c_str();
	}
/*
	static bool GetFileInfo(const tstring& str,fileinfo & result)
	{
		return GetFileInfo(Path(str),result);
	}
	static bool GetFileInfo(const _tpath& path,fileinfo & result)
	{
	}
*/
	static _tpath refinepath(_tpath path_)
	{
		tstring temp=path_.c_str();
		boost::replace_all(temp, _T("\\"), _T("/"));
		return _tpath(temp);
	}

	static tstring leaf(_tpath path_)
	{
		if (bfs::is_directory(path_))
		{
			std::vector<tstring> split_vec;
			tstring temp = path_.c_str();
			boost::split(split_vec, temp, boost::is_any_of(_T("/")));
			if (split_vec.size() > 0)
			{
				tstring result = split_vec[split_vec.size() - 1];
				return result;
			}
			else
				return tstring();
		}
		else
		{
			return path_.filename().c_str();
		}
	}

	static tstring native_directory_string(_tpath path_)
	{
		tstring temp=path_.c_str();
		boost::replace_all(temp, _T("/"), _T("\\"));
		return temp;
	}


		

	static _tpath PathFromUTF8(const std::string& str) 
	{
		try
		{
			_tpath result(MCodeChanger::_CCL((str)));
			return result;
		}
		catch( const _tfilesystem_error& e )
		{
			ProcessError(e.what(),MCodeChanger::_CCL(str));
			return _tpath();
		}
	}

	static FILE* OpenReadL(const tstring& str)
	{
		FILE* result=_tfopen(str.c_str(),_T("r"));
		if (result==NULL)
		{
			ProcessError(_T("File Open Read"),str);
		}
		return result;
	}
	static FILE* OpenWriteL(const tstring& str)
	{
		FILE* result=_tfopen(str.c_str(),_T("w"));
		if (result==NULL)
		{
			ProcessError(_T("File Open Write"),str);
		}
		return result;
	}

	static bool IsDir(const _tpath& path)
	{
		try
		{
			return boost::filesystem::is_directory(path);
		}
		catch( const _tfilesystem_error& e )
		{
			ProcessError(e.what(),path.c_str());
			return false;
		}
	}
	
	static bool IsDirL(const tstring& stPath)
	{
		return IsDir(_tpath(stPath));
	}
	static size_t FileSize(const _tpath& str)
	{
		try
		{
			size_t result=(size_t)(bfs::file_size(str));
			return result;
		}
		catch( const _tfilesystem_error& e )
		{
			ProcessError(e.what(),str.c_str());
			return 0;
		}
	}
	static size_t FileSizeL(const tstring& str)
	{
		try
		{
			return FileSize(_tpath(str));
		}
		catch( const _tfilesystem_error& e )
		{
			ProcessError(e.what(),str);
			return 0;
		}
	}

	static bool FindL(const _tpath & dir_path, const tstring & file_name, path_list & pfound)
	{
		try
		{
    bool successFlag(false);
	pfound.clear();

    if( exists(dir_path) && is_directory(dir_path) )
    {
        _tdirectory_iterator iter(dir_path), end_iter;
        for(; iter!= end_iter; ++iter)
        {
			_tpath temp=MFile::refinepath(*iter);
            if( bfs::is_directory(temp) )
            {
                if( FindL(temp, file_name, pfound) )
                     successFlag = true;
                     break;
            }
			else if( file_name.find(temp.filename().c_str())!= tstring::npos)
            {
				pfound.push_back(temp);
                 successFlag = true;
                 break;
            }
        }
    }

	return successFlag;

		}
		catch( const _tfilesystem_error& e )
		{
			ProcessError(e.what(),dir_path.c_str(),file_name);
			return false;
		}
	}
	static bool ExistsL(const tstring& p)
	{
		return Exists(_tpath(p));
	}

	static bool Exists(const _tpath& p)
	{
		try
		{
			return bfs::exists(p);
		}
		catch( const _tfilesystem_error& e )
		{
			ProcessError(e.what(),p.c_str());
			return false;
		}
	}
	static bool List(const _tpath & p,path_list & pfound)
	{
		try
		{
		if( !bfs::exists(p) ) 
		{
//			tstring mess;sprintf(mess,"File Not Found : %s",MCodeChanger::L_U(p.string()));
//			err_.Add(FILE_ERROR,mess);
			return false;
		}
		if(!bfs::is_directory(p) )
		{
//			tstring mess;sprintf(mess,"Not Directory : %s",MCodeChanger::L_U(p.string()));
//			err_.Add(FILE_ERROR,mess);
			return false;
		}

		_tdirectory_iterator end_iter;

		for ( _tdirectory_iterator dir_itr( p );
          dir_itr != end_iter;
          ++dir_itr )
		{
			pfound.push_back(MFile::refinepath(*dir_itr));
		}
		return true;


		}
		catch( const _tfilesystem_error& e )
		{
			ProcessError(e.what(),p.c_str());
			return false;
		}
	}
	static bool CopyFileL(const tstring& from,const tstring& to)
	{
		try
		{
			bfs::copy_file(_tpath(from),_tpath(to));
			return true;
		}
		catch( const _tfilesystem_error& e )
		{
			ProcessError(e.what(),from,to);
			return false;
		}
	}
	static bool RenameL(const tstring& from,const tstring& to)
	{
		try
		{
			bfs::rename(from,to);
			return true;
		}
		catch( const _tfilesystem_error& e )
		{
			ProcessError(e.what(),from,to);
			return false;
		}
	}
	static bool Rename(const _tpath& from,const _tpath& to) 
	{
		return RenameL(from.c_str(),to.c_str());
	}

	static bool CreateFolderL(const tstring & str)
	{
		return CreateFolder(_tpath(str));
	}

	static bool CreateFolder(const _tpath & str)
	{
		try
		{
			if (!Exists(str.parent_path()))
			{
				if (_tcscmp(str.parent_path().c_str(),_T(""))==0)
					return false;
				if (!CreateFolder(str.parent_path())) 
					return false;
			}
			bool bResult=bfs::create_directory(str);
			return bResult;
		}
		catch( const _tfilesystem_error& e )
		{
			ProcessError(e.what(),str.c_str());
			return false;
		}
	}
	static bool DeleteL(const tstring& str)
	{
		return Delete(_tpath(str));
	}
	static bool Delete(const _tpath& path)
	{
		try
		{
			bfs::remove(path);
			return true;
		}
		catch( const _tfilesystem_error& e )
		{
			ProcessError(e.what(),path.c_str());
			return false;
		}
	}
	static bool DeleteAllL(const tstring& str)
	{
		return DeleteAll(_tpath(str));
	}
	
	static bool DeleteAll(const _tpath& path)
	{
		try
		{
			bfs::remove_all(path);
			return true;
		}
		catch( const _tfilesystem_error& e )
		{
			ProcessError(e.what(),path.c_str());
			return 0;
		}
	}

	static tstring GetFileNameL(const tstring& csFilePath) //	aa.jpg
	{
		_tpath temp(csFilePath);
		if (bfs::is_directory(temp))
			return tstring(_T(""));
		else
		return _tpath(csFilePath).filename().c_str();
	}
	static tstring GetFileNamesExtL(const tstring& path) //	aa
	{
		if (bfs::is_directory(_tpath(path)))
		{
			std::vector<tstring> split_vec;
			tstring path = _tpath(path).c_str();
			boost::split(split_vec, path, boost::is_any_of(_T("/")));
			return split_vec.back();
			//return _tpath(path).filename().c_str();
		}
		else
		{
			tstring result=GetFileNameL(path);
			boost::algorithm::replace_first(result,GetFileExtL(path),"");
			return result;
		}
	}
	static tstring GetFileDirL(const tstring& path) //		/aa
	{
		tstring result=_tpath(path).parent_path().c_str();
//		boost::algorithm::replace_last(result,_T("\\"),_T(""));
		return result;
	}
	static tstring GetFileExtL(const tstring& path) //		.jpg
	{
		std::vector<tstring> split_vec;
		tstring temp_string=GetFileNameL(path);
		boost::split(split_vec,temp_string,boost::is_any_of(_T(".")));

		if (split_vec.size()>1)
		{
			_tformat fmt(_T(".%s"));
			fmt % split_vec[split_vec.size()-1];

			return fmt.str();
		}
		return _T("");
	}


};


