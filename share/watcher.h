////////////////////////////////////////////////////////////////////////////////
/// \file FileSystemWatcher.h
/// \author excel96
/// \date 2006.10.26
////////////////////////////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////////////////////////////
/// \class cFileSystemEvent
/// \brief ����� ���� �ý��ۿ� ���� ����.
///
/// ����� ������ �Ϲ� ������ ���� �ְ�, ���丮�� ���� �ִ�. �̸������δ� 
/// ����� ���� �������� ���丮���� ������ �� �����Ƿ�, GetFileAttributes
/// �Լ��� �̿��ؼ� �����ϵ��� �Ѵ�.
////////////////////////////////////////////////////////////////////////////////

#include "../share/unicode.h"
#include <boost/tuple/tuple.hpp>
#include "etc.h"

class cFileSystemEvent
{
public:
    enum ChangeType 
    {
        CREATED, ///< ���� ����
        CHANGED, ///< ���� ���� ����
        DELETED, ///< ���� ����
        RENAMED, ///< ���� �̸� ����
        MAX,     ///< �迭�� ���� �ƽ���
    };


private:
    ChangeType  m_ChangeType;   ///< ������ ����
    tstring m_Directory;    ///< ���丮
    tstring m_FileName;     ///< ���� ���� �̸�
    tstring m_NewFileName;  ///< ����� ���� �̸�


public:
    /// \brief ������
    cFileSystemEvent(ChangeType type, const tstring& directory, 
        const tstring& fileName);

    /// \brief ������
    cFileSystemEvent(const tstring& directory, 
        const tstring& oldFileName, const tstring& newFileName);

    /// \brief �Ҹ���
    ~cFileSystemEvent();


public:
    /// \brief ���丮���� ������ ���� ��θ� ��ȯ�Ѵ�.
    tstring GetFullPath() const;

    /// \brief ���丮���� ������ ���� ���� ��θ� ��ȯ�Ѵ�.
    tstring GetOldFullPath() const;

    /// \brief ���丮���� ������ ���ο� ���� ��θ� ��ȯ�Ѵ�.
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
/// \brief ���� �ý��� ���� ����͸��� ���� Ŭ����.
///
/// Ŭ���� �ν��Ͻ��� �����ϰ�, Open �Լ��� ���� ����͸��� ���丮�� ������ 
/// ����, ���� ���� ��򰡿��� Heartbeat() �Լ��� ���������� ȣ������� �Ѵ�.
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

    tstring       m_Path;                                ///< ���丮 ��� ���ڿ�
    HANDLE            m_hDirectory;                          ///< ���丮 �ڵ�
    MONITOR*          m_Monitor;                             ///< OVERLAPPED ����ü
    PFN_EVENT_HANDLER m_EventHandler[cFileSystemEvent::MAX]; ///< �̺�Ʈ �ڵ鷯

	tstring old_directory;
	DWORD old_filter;
	bool old_sub;

public:
    /// \brief ������
    cFileSystemWatcher();

    /// \brief ������ + Open
//    cFileSystemWatcher(const tstring& directory);

    /// \brief �Ҹ���
    virtual ~cFileSystemWatcher();


public:
    /// \brief ����͸��� �����Ѵ�.
    bool Open(const tstring& directory,DWORD filter,bool bSub);

    /// \brief ����͸��� �ߴ��Ѵ�.
    void Close();
	bool ReOpen();

    /// \brief ��ü�� ���°� ������������ ���θ� ��ȯ�Ѵ�.
    bool IsGood() const;

    /// \brief ���� �Լ�
    void Heartbeat(DWORD period = 1);

    /// \brief �̺�Ʈ �ڵ鷯�� �����Ѵ�.
    void SetEventHandler(
        cFileSystemEvent::ChangeType type, PFN_EVENT_HANDLER handler);

    /// \brief ����͸� ���� ���丮�� ��ȯ�Ѵ�.
    const tstring& GetPath() const { return m_Path; }


private:
    /// \brief ���� ���� ��û�� ����Ʈ�Ѵ�.
    bool PostChangeNotificationRequest(int operation);

    /// \brief ���� ������ �ܺο��� ȣ���ϱ� ���� �Լ�
    virtual void OnCreate(const tstring& fileName);

    /// \brief ���� ����� �ܺο��� ȣ���ϱ� ���� �Լ�
    virtual void OnChange(const tstring& fileName);

    /// \brief ���� ������ �ܺο��� ȣ���ϱ� ���� �Լ�
    virtual void OnDelete(const tstring& fileName);

    /// \brief ���� �̸� ����� �ܺο��� ȣ���ϱ� ���� �Լ�
    virtual void OnRename(const tstring& oldFileName, const tstring& newFileName);

    /// \brief �Ϸ� ���� �Լ�
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

