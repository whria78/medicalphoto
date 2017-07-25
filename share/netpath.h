#pragma once

#include "sql_db.h"
#include "watcher.h"
#include "etc.h"
#include "../cximage/ximage.h"
#include "imageprocess.h"

/*
#include "../exiv2/image.hpp"
#include "../exiv2/iptc.hpp"
#include "../exiv2/exif.hpp"
#include "../exiv2/exiv2.hpp"
#include "../cximage/ximajpg.h"
*/
#include "../cximage/ximajpg.h"
class netvolume
	: public SQL_DB,public cFileSystemWatcher
{
public:
	netvolume(config& c_,CMyCout& l)
		: SQL_DB(l)
		,log(l)
		,config_(c_)
	{
	}
	~netvolume()
	{
		StopWatch();
		SQL_DB::Close();
	}

	// watcher
	void StartWatch();
	void StopWatch();
	void Heartbeat(DWORD period)
	{
		cFileSystemWatcher::Heartbeat(period);
	}

//	void WatchThread();
protected:

	void BuildInfo(_tpath& path,bool bRoot=false);

	// file watch
	void OnCreate(tstring filename_org);
	void OnDelete(tstring filename_org);
	void OnChange(tstring filename_org);
    void OnRename(tstring oldFileName_org, tstring newFileName_org);

//	static void ThrowError(tstring stErrorMsg,const tstring& param=_T(""));


public:
	bool UpgradeTable(int iOldVersion);

	template <typename T>
	bool UpgradeDate(const T& const_temp);

	virtual void MakeThumbnail(const tstring& thumbpath,const std::string& stNetPath,bool bForce=false);
	virtual void MakeThumbnail(const tstring& thumbpath,CxImage& image,bool bForce=false);
//	static void MakeThumbnail(CxImage& image,config& config_);

	bool LoadMetatag(fileinfo& fileinfo_);

	std::string GetNetDir(const _tpath& _tPath);
	std::string GetNetDir(const tstring& stLocalPath)
	{
		return GetNetDir(_tpath(stLocalPath));
	}

	std::string GetPath_s_Vol(std::string stNetPath);  //  /aa/bb.jpb

	std::string Local_Net(const tstring& stLocalPath);
	tstring Net_Local(const std::string& stNetPath);

	tstring Net_Thumb(const std::string& stNetPath);

	static void ThrowSQLInsertError(const std::string& stNetPath);
	static void ThrowSQLUpdateError(const std::string& stNetPathFrom,const std::string& stNetPathTo);
	static void ThrowSQLDeleteError(const std::string& stNetPath);

	void MoveFile(const std::string& stNetpathFrom,const std::string& stNetpathTo);
	void MoveFolder(const std::string& stNetpathFrom,const std::string& stNetpathTo);

	void DeleteFile(const std::string& stNetpath);
	void DeleteFolder(const std::string& stNetpath,bool bSQLOnly=true);

	fileinfo CreateFileInfo(const _tpath& str,const std::string& stUserID=""); // Local
	bool Open(const tstring& path);
	void Close() {SQL_DB::Close();}
	tstring GetRootPath() const;
	tstring GetVolName() const;

	virtual void CreateTable();
	void DeleteTable();
	void Vacuum();

	bool GetFileInfo(const std::string& stNetPath,fileinfo& result);

	void UpdateDiagnosis(const dx_list& dx_from,const dx_list& dx_to);

	void FindFile(const std::string& stKeyword,fileinfo_list& f_list,bool bExact);
	void FindFile(const std::vector<std::string>& Field_list,const std::vector<std::string>& Keyword_list,fileinfo_list& f_list,bool bExact);
	void FindbyDir(const std::string& stKeyword,fileinfo_list& f_list,bool bExact,bool bFileOnly=false);
	void FindPath(const std::string& stKeyword,fileinfo_list& f_list,bool bExact);
	void FindComment_by_Path(const std::vector<std::string>& stNetPath,comment_list& c_list,bool bExact);
	void FindComment_by_Comment(const std::string& stComment,comment_list& c_list,bool bExact);

	void FindFile_by_Date(const std::string& stFrom,const std::string& stTo,fileinfo_list& f_list);
	void FindFile_byQuery(const std::string& stQuery,const std::vector<bool>& bMask,fileinfo_list& f_list);

	std::string GetQueryWhere(const std::string& stTableName,const std::vector<std::string>& Field_list,const std::vector<std::string>& Keyword_list);
	std::string GetQueryField(const std::string& stSearch,const std::vector<bool>& bMask,bool bSearchComment);
	std::string Interprete(const std::string& stQuery,const std::vector<bool>& bMask,bool bComment);

	bool CheckRootPriv(const std::string & stUserID,const _tpath& dir_,bool bWrite=false);
//	void DeleteFolder(const std::string& stNetPath);

	netvolume operator = (const netvolume &wf)
	{
		root_path=wf.GetRootPath();
//		Open(wf.GetRootPath());
		return *this;
	}
	
	bool IsPart(const tstring& full_path);
	static void ThrowError(tstring stErrorMsg,const tstring& param=_T(""))
	{
		stErrorMsg+=_T(" : ");
		stErrorMsg+=param;
		throw std::logic_error(MCodeChanger::_CCN(stErrorMsg));
	}

protected:
	_tpath db_path;
	tstring sql_filename;
	tstring root_path;
	CMyCout& log;
	config& config_;
	net_watcher net_watcher_;
};
typedef std::vector<netvolume*> netvolume_ptr_list;
typedef std::vector<std::string> volname_list;

class netstorage
{
public:
	netstorage(config& c)
		: log(c.log)
		,config_(c)
	{
	}
	~netstorage()
	{
		Close();
	}
	void StartWatch()
	{
		for (int i=0;i<GetSize();i++)
		{
			netvolume_ptr_list_[i]->StartWatch();
		}
	}
	void StopWatch()
	{
		for (int i=0;i<GetSize();i++)
		{
			netvolume_ptr_list_[i]->StopWatch();
		}
	}
	void Heartbeat(DWORD period)
	{
		for (int i=0;i<GetSize();i++)
		{
			netvolume_ptr_list_[i]->Heartbeat(period);
		}
	}

	bool Check();
	void Open();
	void Close();
	void Reset();

	bool IsAnyEmpty();

	int GetSize();
	netvolume& Vol(int i); 

	void Image_Rotate(const std::string& stNetPath,int iRotate);
	virtual void MakeThumbnail(const tstring& thumbpath,const std::string& stNetPath,bool bForce=false);

	bool AddVolume(const tstring& root_path);
	void DeleteVolume(const tstring& volname);

	void Vacuum();

	void CreateTable();
	void DeleteTable();

	void BeginTransaction();
	void CommitTransaction();

	bool IsExistVolume(const tstring& root_path);
	bool GetFileInfo(const std::string& stNetPath,fileinfo& result);
	void FindFile(const std::string& stKeyword,fileinfo_list& f_list,bool bExact);
	void FindFile(const std::vector<std::string>& Field_list,const std::vector<std::string>& Keyword_list,fileinfo_list& f_list,bool bExact);
	void FindbyDir(const std::string& stKeyword,fileinfo_list& f_list,bool bExact,bool bFileOnly=false);
	void FindPath(const std::string& stKeyword,fileinfo_list& f_list,bool bExact);
	void FindComment_by_Path(const std::vector<std::string>& stKeyword,comment_list& c_list,bool bExact);
	void FindComment_by_Comment(const std::string& stComment,comment_list& c_list,bool bExact);
	void FindFile_by_Date(const std::string& stFrom,const std::string& stTo,fileinfo_list& f_list);
	void FindFile_byQuery(const std::string& stQuery,const std::vector<bool>& bMask,fileinfo_list& f_list);

	void UpdateDiagnosis(const dx_list& dx_from,const dx_list& dx_to);

	bool CheckRootPriv(const std::string&stCurrentUserID,const _tpath& dir_,bool bWrite=false);

	template <typename T>
	bool IsExists(const T& t)
	{
		for (int i=0;i<GetSize();i++)
		{
			if (netvolume_ptr_list_[i]->IsExists(t)) return true;
		}
		return false;
	}

	template <typename T>
	bool IsExistsFromPrimary(const std::string& stUnique,const T& temp)
	{
		for (int i=0;i<GetSize();i++)
		{
			if (netvolume_ptr_list_[i]->IsExistsFromPrimary(stUnique,temp)) return true;
		}
		return false;
	}

	template <typename T>
	int Insert(const T& info)
	{
		int iVol=GetVolumeNumber(GetVolumeName(info.GetNetPath()));
		if (iVol==-1) return 0;
		return netvolume_ptr_list_[iVol]->Insert(info);
	}
	template <typename T>
	int Delete(const T& info)
	{
		int iVol=GetVolumeNumber(GetVolumeName(info.GetNetPath()));
		if (iVol==-1) return 0;
		return netvolume_ptr_list_[iVol]->Delete(info);
	}

	/*
	int DeleteFile(const std::string& stNetPath)
	{
		int iVol=GetVolumeNumber(GetVolumeName(stNetPath));
		if (iVol==-1) return 0;
		return netvolume_ptr_list_[iVol]->Delete(fileinfo::get_tablename(),fileinfo::get_primary(),stNetPath);
	}
	*/
	int DeleteComment(const std::string& stNetPath)
	{
		int iVol=GetVolumeNumber(GetVolumeName(stNetPath));
		if (iVol==-1) return 0;
		return netvolume_ptr_list_[iVol]->Delete(comment::get_tablename(),comment::get_primary(),stNetPath);
	}
/*
	void DeleteFolder(const std::string& stNetPath)
	{
		int iVol=GetVolumeNumber(GetVolumeName(stNetPath));
		if (iVol==-1) return;
		netvolume_ptr_list_[iVol]->DeleteFolder(stNetPath);
	}
*/
	template <typename T>
	bool Update(const T& from,const T&to)
	{
		int iVolFrom=GetVolumeNumber(GetVolumeName(from.GetNetPath()));
		int iVolTo=GetVolumeNumber(GetVolumeName(to.GetNetPath()));

		if (iVolFrom==-1) return 0;
		if (iVolTo==-1) return 0;

		if (iVolFrom == iVolTo)
		{
			if (netvolume_ptr_list_[iVolFrom]->Update(from,to)==1) return true;
		}
		else
		{
			int iDelete=netvolume_ptr_list_[iVolFrom]->Delete(from);
			int iInsert=netvolume_ptr_list_[iVolTo]->Insert(to);
			if (iDelete!=1)
				ThrowError(_T("Update Error "),MCodeChanger::_CCL(from.GetNetPath()));
			if (iInsert!=1)
				ThrowError(_T("Update Error "),MCodeChanger::_CCL(to.GetNetPath()));
			return true;
		}
		ThrowError(_T("Update Failure "),MCodeChanger::_CCL(to.GetNetPath()));
		return false;
	}

	// Path

	std::string Local_Net(const tstring& stLocalPath);
	tstring Net_Local(const std::string& stNetPath);
	tstring Net_Thumb(const std::string& stNetPath);
	std::string Thumb_Net(const tstring& stThumbPath);

	// File

	fileinfo CreateFileInfoU(const std::string& str,const std::string& stUserID=""); // UTF-8
	fileinfo CreateFileInfoL(const tstring& str,const std::string& stUserID=""); // Local
	fileinfo CreateFileInfo(const _tpath& str,const std::string& stUserID=""); // Local
	std::string GetNetDir(const _tpath& _tPath);
	std::string GetNetDir(const tstring& stLocalPath)
	{
		return GetNetDir(_tpath(stLocalPath));
	}

	void CreateFile(const std::string& stNetpath,const std::string& stUserID,bool bSQLOnly=false);
	void CopyFile(const std::string& stNetpathFrom,const std::string& stNetpathTo,bool bSQLOnly=false);
	void MoveFile(const std::string& stNetpathFrom,const std::string& stNetpathTo,bool bSQLOnly=false);
	void DeleteFile(const std::string& stNetpath,bool bSQLOnly=false);

	void CopyFolder(const std::string& stNetpathFrom,const std::string& stNetpathTo,bool bSQLOnly=false);
	void MoveFolder(const std::string& stNetpathFrom,const std::string& stNetpathTo,bool bSQLOnly=false);
	void DeleteFolder(const std::string& stNetpath,bool bSQLOnly=false);
	void CreateFolder(const std::string& stNetpath,const std::string& stUserID,bool bSQLOnly=false);

	void GetVariableType(const std::string& stNetpath,tstring& stPath,_tpath& _tPath,int& iVol);
	void GetVariableType(const std::string& stNetpath,tstring& stPath,_tpath& _tPath,int& iVol,fileinfo& fileinfo_);
	bool LoadMetatag(fileinfo& fileinfo_);

protected:
	bool AddVirtual(const std::string& stNetPath,fileinfo fileinfo_);
	virtual int GetVolumeNumber(const tstring& stLocalPath);
	std::string GetVolumeName(const std::string& stNetPath); // root
	std::string GetPath_s_Vol(std::string stNetPath);  //  /aa/bb.jpb
	int GetVolumeNumber(const std::string& stVolumeName);
	static void ThrowError(tstring stErrorMsg,const tstring& param=_T(""));

	static void ThrowSQLInsertError(const std::string& stNetPath);
	static void ThrowSQLUpdateError(const std::string& stNetPathFrom,const std::string& stNetPathTo);
	static void ThrowSQLDeleteError(const std::string& stNetPath);
	static void ThrowInvalidVol(const std::string& stVolName);
	static void ThrowEmptyVol();
	static void ThrowAlreadyExist(const std::string& stNetPath);

	netvolume_ptr_list netvolume_ptr_list_;
	CMyCout& log;
	config& config_;
	net_watcher net_watcher_;
};

class netpath
	: public netstorage
{
public:
	netpath(config& c)
		: netstorage(c)
		,config_(c)
	{
	}
	~netpath()
	{
	}
	
	void Open(const std::string& userid);
	void CreateTable();
	bool CheckRootPriv(const _tpath& dir_,bool bWrite=false);

	template <typename T>
	bool CheckPriv(const T& t,bool bWrite=false)
	{
		for (int i=0;i<GetSize();i++)
		{
			if (netvolume_ptr_list_[i]->CheckPriv(stCurrentUserID,t,bWrite)) return true;
		}
		return false;
	}

protected:
	std::string stCurrentUserID;
	config& config_;
};


