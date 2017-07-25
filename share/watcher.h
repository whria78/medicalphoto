////////////////////////////////////////////////////////////////////////////////
/// \file FileSystemWatcher.h
/// \author excel96
/// \date 2006.10.26
////////////////////////////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////////////////////////////
/// \class cFileSystemEvent
/// \brief 변경된 파일 시스템에 대한 정보.
///
/// 변경된 파일은 일반 파일일 수도 있고, 디렉토리일 수도 있다. 이름만으로는 
/// 변경된 것이 파일인지 디렉토리인지 구분할 수 없으므로, GetFileAttributes
/// 함수를 이용해서 구분하도록 한다.
////////////////////////////////////////////////////////////////////////////////

#include "../share/unicode.h"
#include <boost/tuple/tuple.hpp>
#include "etc.h"

class cFileSystemEvent
{
public:
    enum ChangeType 
    {
        CREATED, ///< 파일 생성
        CHANGED, ///< 파일 내용 변경
        DELETED, ///< 파일 삭제
        RENAMED, ///< 파일 이름 변경
        MAX,     ///< 배열을 위한 맥스값
    };


private:
    ChangeType  m_ChangeType;   ///< 변경의 종류
    tstring m_Directory;    ///< 디렉토리
    tstring m_FileName;     ///< 원래 파일 이름
    tstring m_NewFileName;  ///< 변경된 파일 이름


public:
    /// \brief 생성자
    cFileSystemEvent(ChangeType type, const tstring& directory, 
        const tstring& fileName);

    /// \brief 생성자
    cFileSystemEvent(const tstring& directory, 
        const tstring& oldFileName, const tstring& newFileName);

    /// \brief 소멸자
    ~cFileSystemEvent();


public:
    /// \brief 디렉토리까지 포함한 파일 경로를 반환한다.
    tstring GetFullPath() const;

    /// \brief 디렉토리까지 포함한 이전 파일 경로를 반환한다.
    tstring GetOldFullPath() const;

    /// \brief 디렉토리까지 포함한 새로운 파일 경로를 반환한다.
    tstring GetNewFullPath() const;


public:
    /// \name Simple getter/setter
    /// \{ 
    ChangeType GetChangeType() const { return m_ChangeType; }
    const tstring& GetDirectory() const { return m_Directory; }
    const tstring& GetFileName() const { return m_FileName; }
    const tstring& GetOldFileName() const { return m_FileName; }
    const tstring& GetNewFileName() const { return m_NewFileName; }
    /// \} 
};


////////////////////////////////////////////////////////////////////////////////
/// \class cFileSystemWatcher
/// \brief 파일 시스템 변경 모니터링을 위한 클래스.
///
/// 클래스 인스턴스를 생성하고, Open 함수를 통해 모니터링할 디렉토리를 지정한 
/// 다음, 메인 루프 어딘가에서 Heartbeat() 함수를 지속적으로 호출해줘야 한다.
///
/// <pre>
///
/// cFileSystemWatcher watcher("C:\\Program Files");
/// watcher.SetEventHandler(cFileSystemEvent::CREATED, MyCreateHandler);
/// watcher.SetEventHandler(cFileSystemEvent::CHANGED, MyChangeHandler);
/// watcher.SetEventHandler(cFileSystemEvent::DELETED, MyDeleteHandler);
/// watcher.SetEventHandler(cFileSystemEvent::RENAMED, MyRenameHandler);
/// ...
/// while (true)
/// {
///     ...
///     watcher.Heartbeat();
/// }
/// </pre>
////////////////////////////////////////////////////////////////////////////////

class cFileSystemWatcher
{
public:
    typedef void (*PFN_EVENT_HANDLER)(const cFileSystemEvent& args);


private:
    struct MONITOR;

    tstring       m_Path;                                ///< 디렉토리 경로 문자열
    HANDLE            m_hDirectory;                          ///< 디렉토리 핸들
    MONITOR*          m_Monitor;                             ///< OVERLAPPED 구조체
    PFN_EVENT_HANDLER m_EventHandler[cFileSystemEvent::MAX]; ///< 이벤트 핸들러

	tstring old_directory;
	DWORD old_filter;
	bool old_sub;

public:
    /// \brief 생성자
    cFileSystemWatcher();

    /// \brief 생성자 + Open
//    cFileSystemWatcher(const tstring& directory);

    /// \brief 소멸자
    virtual ~cFileSystemWatcher();


public:
    /// \brief 모니터링을 시작한다.
    bool Open(const tstring& directory,DWORD filter,bool bSub);

    /// \brief 모니터링을 중단한다.
    void Close();
	bool ReOpen();

    /// \brief 객체의 상태가 정상적인지의 여부를 반환한다.
    bool IsGood() const;

    /// \brief 폴링 함수
    void Heartbeat(DWORD period = 1);

    /// \brief 이벤트 핸들러를 설정한다.
    void SetEventHandler(
        cFileSystemEvent::ChangeType type, PFN_EVENT_HANDLER handler);

    /// \brief 모니터링 중인 디렉토리를 반환한다.
    const tstring& GetPath() const { return m_Path; }


private:
    /// \brief 변경 사항 요청을 포스트한다.
    bool PostChangeNotificationRequest(int operation);

    /// \brief 파일 생성시 외부에서 호출하기 위한 함수
    virtual void OnCreate(const tstring& fileName);

    /// \brief 파일 변경시 외부에서 호출하기 위한 함수
    virtual void OnChange(const tstring& fileName);

    /// \brief 파일 삭제시 외부에서 호출하기 위한 함수
    virtual void OnDelete(const tstring& fileName);

    /// \brief 파일 이름 변경시 외부에서 호출하기 위한 함수
    virtual void OnRename(const tstring& oldFileName, const tstring& newFileName);

    /// \brief 완료 통지 함수
    static void CALLBACK FileSystemWatcherCallback(DWORD, DWORD, LPOVERLAPPED);

private:
	DWORD FILTER;
	bool bMonitorSubDirectory;
};


enum watcher_type
{
	WATCH_CREATE=1,
	WATCH_DELETE,
	WATCH_RENAME,
	WATCH_MODIFY
};

class net_watcher
{
public:
	net_watcher()
	{
	}
	static void Add(int iOrderType,const tstring& stFromPath,const tstring& stToPath=_T(""));
	static void Remove(int iOrderType,const tstring& stFromPath,const tstring& stToPath=_T(""));
	static void RemoveAll(int iOrderType,const tstring& stFromPath,const tstring& stToPath=_T(""));
	static bool Check(int iOrderType,const tstring& stFromPath,const tstring& stToPath=_T(""));
	static bool ChecknRemove(int iOrderType,const tstring& stFromPath,const tstring& stToPath=_T(""));

	static void clear()
	{
		watch_list.clear();
	}
	int size()
	{
		return (int)watch_list.size();
	}
	static bool GetCutFlag(tstring& stFolder)
	{
		stFolder=stCutFolder;
		return bCutFlag;
	}
	static void SetCutFlag(bool bSet,const tstring& stFolder=_T(""))
	{
		stCutFolder=stFolder;
		bCutFlag=bSet;
	}
	static bool IsSameAsPrev(int iOrderType,const tstring& stFromPath,const tstring& stToPath=_T(""))
	{
		if (bPrevOrderType==iOrderType
			&& _tcscmp(stFromPath.c_str(),bPrev_from.c_str())==0
			&& _tcscmp(stToPath.c_str(),bPrev_to.c_str())==0)
		{
//			RegisterPrev(iOrderType,stFromPath,stToPath);
			return true;
		}
		else
		{
//			RegisterPrev(iOrderType,stFromPath,stToPath);
			return false;
		}
	}
	static void RemoveModify(int iOrderType,const tstring& stFromPath,const tstring& stToPath=_T(""))
	{
		if (bPrevOrderType==WATCH_CREATE)
		{
			if (iOrderType!=WATCH_MODIFY
				|| _tcscmp(bPrev_from.c_str(),stFromPath.c_str())!=0
				|| _tcscmp(bPrev_to.c_str(),stToPath.c_str())!=0)
			{
				RemoveAll(WATCH_MODIFY,bPrev_from,bPrev_to);
			}
		}
		bPrevOrderType=iOrderType;
		bPrev_from=stFromPath;
		bPrev_to=stToPath;
	}
protected:
	static bool bCutFlag;
	static tstring stCutFolder;
	static boost::mutex mutex_;
	static std::vector<boost::tuple<int,tstring,tstring>> watch_list;
	static int bPrevOrderType;
	static tstring bPrev_from;
	static tstring bPrev_to;
};

