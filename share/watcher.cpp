#include "stdafx.h"
//#include "PCH.h"
#include "Watcher.h"

namespace
{
    /*
    const DWORD FILTER = 
        FILE_NOTIFY_CHANGE_SECURITY |
        FILE_NOTIFY_CHANGE_CREATION |
        FILE_NOTIFY_CHANGE_LAST_ACCESS |
        FILE_NOTIFY_CHANGE_LAST_WRITE |
        FILE_NOTIFY_CHANGE_SIZE |
        FILE_NOTIFY_CHANGE_ATTRIBUTES |
        FILE_NOTIFY_CHANGE_DIR_NAME |
        FILE_NOTIFY_CHANGE_FILE_NAME;
    */

    /// �۾��� ����
    enum Operation
    {
        CONTINUE_MONITORING,  ///< ����͸��� ��� �Ѵ�.
        STOP_MONITORING,      ///< ����͸��� �ߴ��Ѵ�.
    };

    /// ����͸��� �̺�Ʈ�� ����
  /*  const DWORD FILTER = 
        FILE_NOTIFY_CHANGE_CREATION | 
//        FILE_NOTIFY_CHANGE_LAST_WRITE |
//        FILE_NOTIFY_CHANGE_SIZE |
        FILE_NOTIFY_CHANGE_DIR_NAME |
        FILE_NOTIFY_CHANGE_FILE_NAME;
*/
    /// MONITOR ������ ũ��
    const size_t BUFFER_SIZE = sizeof(FILE_NOTIFY_INFORMATION) * 1024;

    /// FILE_NOTIFY_INFORMATION ����ü �ȿ� ���̵� ���ڿ��� tstring ���·� 
    /// ��ȯ�ؼ� ��ȯ�Ѵ�.
    tstring ExtractFileName(const FILE_NOTIFY_INFORMATION* info)
    {
        TCHAR fileName[1024] = {0, };
		

	/*
        int count = WideCharToMultiByte(
            CP_ACP, 0, info->FileName, info->FileNameLength / sizeof(WCHAR), 
            fileName, _ARRAYSIZE(fileName) - 1, NULL, NULL);
		*/
		_tcscpy(fileName,info->FileName);
        fileName[info->FileNameLength/sizeof(TCHAR)] = _T('\0');
		return tstring(fileName);
//        return tstring(fileName);*/
    }

    /// ��� ������ �齽������ �߰��� ��θ� ��ȯ�Ѵ�.
    tstring AddBackslash(const tstring& path)
    {
        if (path.empty()) return tstring(_T(""));
        return path[path.size()-1] != _T('\\') ? path + tstring(_T("\\")) : path;
    }

    /// ���丮 + ���� �̸��� ���ļ� ��ü ��θ� �����Ѵ�.
    tstring Combine(const tstring& dir, const tstring& file)
    {
        return AddBackslash(dir) + file;
    }

    /// ���丮�� �����ϴ����� ���θ� ��ȯ�Ѵ�.
    bool IsDirectoryExist(const tstring& path)
    {
        DWORD attr = GetFileAttributes(path.c_str());
        return (attr != INVALID_FILE_ATTRIBUTES) && (attr & FILE_ATTRIBUTE_DIRECTORY);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ������
/// \param type ������ ����
/// \param directory ���丮
/// \param fileName ���� �̸�
////////////////////////////////////////////////////////////////////////////////
cFileSystemEvent::cFileSystemEvent(ChangeType type, 
                                   const tstring& directory, 
                                   const tstring& fileName)
: m_ChangeType(type), 
m_Directory(directory), 
m_FileName(fileName)
{
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ������
/// \param directory ���丮
/// \param oldFileName ���� �̸�
/// \param newFileName ����� �̸�
////////////////////////////////////////////////////////////////////////////////
cFileSystemEvent::cFileSystemEvent(const tstring& directory, 
                                   const tstring& oldFileName, 
                                   const tstring& newFileName)
: m_ChangeType(RENAMED),
m_Directory(directory), 
m_FileName(oldFileName),
m_NewFileName(newFileName)
{
}

////////////////////////////////////////////////////////////////////////////////
/// \brief �Ҹ���
////////////////////////////////////////////////////////////////////////////////
cFileSystemEvent::~cFileSystemEvent()
{
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ���丮���� ������ ���� ��θ� ��ȯ�Ѵ�.
/// \return tstring ��� ���ڿ�
////////////////////////////////////////////////////////////////////////////////
tstring cFileSystemEvent::GetFullPath() const
{
    return Combine(m_Directory, m_FileName);
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ���丮���� ������ ���� ���� ��θ� ��ȯ�Ѵ�.
/// \return tstring ��� ���ڿ�
////////////////////////////////////////////////////////////////////////////////
tstring cFileSystemEvent::GetOldFullPath() const
{
    return Combine(m_Directory, m_FileName);
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ���丮���� ������ ���ο� ���� ��θ� ��ȯ�Ѵ�.
/// \return tstring ��� ���ڿ�
////////////////////////////////////////////////////////////////////////////////
tstring cFileSystemEvent::GetNewFullPath() const
{
    return Combine(m_Directory, m_NewFileName);
}


////////////////////////////////////////////////////////////////////////////////
/// \struct cFileSystemWatcher::MONITOR
/// \brief �񵿱� �Լ� ȣ���� ���� OVERLAPPED ����ü
////////////////////////////////////////////////////////////////////////////////

struct cFileSystemWatcher::MONITOR : public OVERLAPPED
{
    BYTE                Buffer[BUFFER_SIZE]; ///< ����
    int                 Operation;           ///< �۾��� ����
    cFileSystemWatcher* Watcher;             ///< ��ó ��ü
};

////////////////////////////////////////////////////////////////////////////////
/// \brief ������
////////////////////////////////////////////////////////////////////////////////
cFileSystemWatcher::cFileSystemWatcher()
: m_hDirectory(INVALID_HANDLE_VALUE), m_Monitor(NULL)
{
    ZeroMemory(m_EventHandler, sizeof(PFN_EVENT_HANDLER) * cFileSystemEvent::MAX);
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ������ + Open
/// \param directory ����͸��� ���丮
////////////////////////////////////////////////////////////////////////////////
/*
cFileSystemWatcher::cFileSystemWatcher(const tstring& directory)
: m_hDirectory(INVALID_HANDLE_VALUE), m_Monitor(NULL)
{
    ZeroMemory(m_EventHandler, sizeof(PFN_EVENT_HANDLER) * cFileSystemEvent::MAX);

    if (!Open(directory))
        Close();
}
*/
////////////////////////////////////////////////////////////////////////////////
/// \brief �Ҹ���
////////////////////////////////////////////////////////////////////////////////
cFileSystemWatcher::~cFileSystemWatcher()
{
    Close();
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ����͸��� �����Ѵ�.
/// \param directory ����͸��� ���丮
/// \return bool ������ ����͸��� �����ߴٸ� true, ���� ������ ����ٸ� false
////////////////////////////////////////////////////////////////////////////////
bool cFileSystemWatcher::Open(const tstring& directory,DWORD filter,bool bSub)
{
	old_directory=directory;
	old_filter=filter;
	old_sub=bSub;

    Close();

	FILTER=filter;
	bMonitorSubDirectory=bSub;

    bool success = false;

    do 
    {
        m_Path = AddBackslash(directory);
        if (!IsDirectoryExist(m_Path))
            break;

        m_hDirectory = CreateFile(m_Path.c_str(),
            FILE_LIST_DIRECTORY,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            NULL,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS 
			| FILE_FLAG_OVERLAPPED
			,
            NULL
            );

        if (m_hDirectory == INVALID_HANDLE_VALUE)
            break;

        m_Monitor = reinterpret_cast<MONITOR*>(HeapAlloc(GetProcessHeap(), 0, sizeof(MONITOR)));
        if (!m_Monitor)
            break;

        ZeroMemory(m_Monitor, sizeof(MONITOR));
        m_Monitor->Watcher = this;

        if (!PostChangeNotificationRequest(CONTINUE_MONITORING))
            break;

        success = true;
    } while(0);

    if (!success)
        Close();

    return success;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ����͸��� �����Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void cFileSystemWatcher::Close()
{
    m_Path = _T("");

    if (m_hDirectory != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_hDirectory);
        m_hDirectory = INVALID_HANDLE_VALUE;
    }

    if (m_Monitor)
    {
        HeapFree(GetProcessHeap(), 0, m_Monitor);
        m_Monitor = NULL;
    }
}
bool cFileSystemWatcher::ReOpen()
{
	return Open(old_directory,old_filter,old_sub);
}


////////////////////////////////////////////////////////////////////////////////
/// \brief ��ü�� ���°� ������������ ���θ� ��ȯ�Ѵ�.
/// \return bool �������̶�� true
////////////////////////////////////////////////////////////////////////////////
bool cFileSystemWatcher::IsGood() const
{
    return m_hDirectory != INVALID_HANDLE_VALUE && m_Monitor != NULL;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ���� �Լ�
/// \param period �񵿱� �Լ� ȣ�� ����� ó���� �ð�
////////////////////////////////////////////////////////////////////////////////
void cFileSystemWatcher::Heartbeat(DWORD period)
{
    if (IsGood())
    {
        SleepEx(period, TRUE); // make thread alertable
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \brief �̺�Ʈ �ڵ鷯�� �����Ѵ�.
/// \param type �̺�Ʈ�� ����
/// \param handler �ڵ鷯
////////////////////////////////////////////////////////////////////////////////
void cFileSystemWatcher::SetEventHandler(
    cFileSystemEvent::ChangeType type, cFileSystemWatcher::PFN_EVENT_HANDLER handler)
{
    if (0 <= type && type < cFileSystemEvent::MAX)
        m_EventHandler[type] = handler;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ���� ���� ��û�� ����Ʈ�Ѵ�.
/// \param operation �۾��� ����
/// \return bool ������ �����ߴٸ� true ���� ������ ����ٸ� false
////////////////////////////////////////////////////////////////////////////////
bool cFileSystemWatcher::PostChangeNotificationRequest(int operation)
{
    if (!IsGood()) return false;

    m_Monitor->Operation = operation;

    DWORD bytesReturned = 0;
    DWORD bufferSize = static_cast<DWORD>(BUFFER_SIZE);

    if (ReadDirectoryChangesW(m_hDirectory, m_Monitor->Buffer, bufferSize, 
        bMonitorSubDirectory, FILTER, &bytesReturned, m_Monitor, FileSystemWatcherCallback))
    {
        return true;
    }
    else
    {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ���� ������ �ܺο��� ȣ���ϱ� ���� �Լ�
/// \param fileName ������ ���� �̸�
////////////////////////////////////////////////////////////////////////////////
void cFileSystemWatcher::OnCreate(const tstring& fileName)
{
    if (m_EventHandler[cFileSystemEvent::CREATED])
    {
        cFileSystemEvent evt(cFileSystemEvent::CREATED, m_Path, fileName);
        m_EventHandler[cFileSystemEvent::CREATED](evt);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ���� ����� �ܺο��� ȣ���ϱ� ���� �Լ�
/// \param fileName ����� ���� �̸�
////////////////////////////////////////////////////////////////////////////////
void cFileSystemWatcher::OnChange(const tstring& fileName)
{
    if (m_EventHandler[cFileSystemEvent::CHANGED])
    {
        cFileSystemEvent evt(cFileSystemEvent::CHANGED, m_Path, fileName);
        m_EventHandler[cFileSystemEvent::CHANGED](evt);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ���� ������ �ܺο��� ȣ���ϱ� ���� �Լ�
/// \param fileName ������ ���� �̸�
////////////////////////////////////////////////////////////////////////////////
void cFileSystemWatcher::OnDelete(const tstring& fileName)
{
    if (m_EventHandler[cFileSystemEvent::DELETED])
    {
        cFileSystemEvent evt(cFileSystemEvent::DELETED, m_Path, fileName);
        m_EventHandler[cFileSystemEvent::DELETED](evt);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \brief ���� �̸� ����� �ܺο��� ȣ���ϱ� ���� �Լ�
/// \param oldFileName ���� ���� �̸�
/// \param newFileName ����� ���� �̸�
////////////////////////////////////////////////////////////////////////////////
void cFileSystemWatcher::OnRename(const tstring& oldFileName, const tstring& newFileName)
{
    if (m_EventHandler[cFileSystemEvent::RENAMED])
    {
        cFileSystemEvent evt(m_Path, oldFileName, newFileName);
        m_EventHandler[cFileSystemEvent::RENAMED](evt);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \brief �Ϸ� ���� �Լ�
/// \param errorCode ���� �ڵ�
/// \param bytesTransferred ������ ó���� ��
/// \param overlapped ReadDirectoryChangesW �Լ����� �ѱ� �������� ����ü
////////////////////////////////////////////////////////////////////////////////
void CALLBACK cFileSystemWatcher::FileSystemWatcherCallback(
    DWORD errorCode, DWORD bytesTransferred, LPOVERLAPPED overlapped)
{
    cFileSystemWatcher::MONITOR* monitor = 
        reinterpret_cast<cFileSystemWatcher::MONITOR*>(overlapped);
    cFileSystemWatcher* watcher = monitor->Watcher;

    if (errorCode == ERROR_SUCCESS)
    {
        PFILE_NOTIFY_INFORMATION info = NULL;
        size_t offset = 0;
        tstring fileName, oldFileName, newFileName;

        do
        {
            info = reinterpret_cast<PFILE_NOTIFY_INFORMATION>(&monitor->Buffer[offset]);
            offset += info->NextEntryOffset;

            if (info->Action == FILE_ACTION_ADDED)
            {
                fileName = ExtractFileName(info);
                watcher->OnCreate(fileName);
            }
            else if (info->Action == FILE_ACTION_REMOVED)
            {
                fileName = ExtractFileName(info);
                watcher->OnDelete(fileName);
            }
            else if (info->Action == FILE_ACTION_MODIFIED)
            {
                fileName = ExtractFileName(info);
                watcher->OnChange(fileName);
            }

			else if (info->Action == FILE_ACTION_RENAMED_OLD_NAME)
            {
                oldFileName = ExtractFileName(info);
            }
            else if (info->Action == FILE_ACTION_RENAMED_NEW_NAME)
            {
                newFileName = ExtractFileName(info);
                watcher->OnRename(oldFileName, newFileName);
            }
        } while (info->NextEntryOffset != 0);
    }

    if (monitor->Operation == CONTINUE_MONITORING)
        watcher->PostChangeNotificationRequest(CONTINUE_MONITORING);
}


boost::mutex net_watcher::mutex_;
std::vector<boost::tuple<int,tstring,tstring>> net_watcher::watch_list;
bool net_watcher::bCutFlag=false;
tstring net_watcher::stCutFolder;
int net_watcher::bPrevOrderType;
tstring net_watcher::bPrev_from;
tstring net_watcher::bPrev_to;

#ifdef _DEBUG
#include "../share/cmycout.h"
#endif

void net_watcher::Add(int iOrderType,const tstring& stNetFromPath_org,const tstring& stNetToPath_org)
{
#ifdef _DEBUG
	CMyCout log(_tcout);
	log << (int)watch_list.size() << _T("Add ") << stNetFromPath_org << _T(" / ") << stNetToPath_org << _T("\n");
#endif
	tstring stNetFromPath=Utility::RefinePath(stNetFromPath_org);
	tstring stNetToPath=Utility::RefinePath(stNetToPath_org);
	watch_list.push_back(boost::tuples::make_tuple(iOrderType,stNetFromPath,stNetToPath));
	
	if (iOrderType==WATCH_CREATE)
	{
		if (!boost::filesystem::is_directory(_tpath(stNetFromPath)))
			Add(WATCH_MODIFY,stNetFromPath_org,stNetToPath_org);
	}
	
}
void net_watcher::Remove(int iOrderType,const tstring& stNetFromPath_org,const tstring& stNetToPath_org)
{
#ifdef _DEBUG
	CMyCout log(_tcout);
	log << (int)watch_list.size() << _T("Remove ") << stNetFromPath_org << _T(" / ") << stNetToPath_org << _T("\n");
#endif
	tstring stNetFromPath=Utility::RefinePath(stNetFromPath_org);
	tstring stNetToPath=Utility::RefinePath(stNetToPath_org);

	for (unsigned int i=0;i<watch_list.size();i++)
	{
		if (watch_list[i].get<0>()==iOrderType
			&& _tcscmp(watch_list[i].get<1>().c_str(),stNetFromPath.c_str())==0
			&& _tcscmp(watch_list[i].get<2>().c_str(),stNetToPath.c_str())==0)
		{
			watch_list.erase(watch_list.begin()+i);
			return;
		}
	}
}
void net_watcher::RemoveAll(int iOrderType,const tstring& stNetFromPath_org,const tstring& stNetToPath_org)
{
#ifdef _DEBUG
	CMyCout log(_tcout);
	log << (int)watch_list.size() << _T("RemoveAll ") << stNetFromPath_org << _T(" / ") << stNetToPath_org << _T("\n");
#endif

	tstring stNetFromPath=Utility::RefinePath(stNetFromPath_org);
	tstring stNetToPath=Utility::RefinePath(stNetToPath_org);

	for (int i=(int)(watch_list.size()-1);i>=0;i--)
	{
		if (watch_list[i].get<0>()==iOrderType
			&& _tcscmp(watch_list[i].get<1>().c_str(),stNetFromPath.c_str())==0
			&& _tcscmp(watch_list[i].get<2>().c_str(),stNetToPath.c_str())==0)
		{
			watch_list.erase(watch_list.begin()+i);
		}
	}
}

bool net_watcher::ChecknRemove(int iOrderType,const tstring& stNetFromPath_org,const tstring& stNetToPath_org)
{
#ifdef _DEBUG
	CMyCout log(_tcout);
	log << (int)watch_list.size() << _T("ChecknRemove ") << stNetFromPath_org << _T(" / ") << stNetToPath_org << _T("\n");

	if (watch_list.size()==1)
	{
		log << watch_list[0].get<0>() << _T("\n");
	}

#endif

	tstring stNetFromPath=Utility::RefinePath(stNetFromPath_org);
	tstring stNetToPath=Utility::RefinePath(stNetToPath_org);
	for (unsigned int i=0;i<watch_list.size();i++)
	{
		if (watch_list[i].get<0>()==iOrderType
			&& _tcscmp(watch_list[i].get<1>().c_str(),stNetFromPath.c_str())==0
			&& _tcscmp(watch_list[i].get<2>().c_str(),stNetToPath.c_str())==0)
		{
			watch_list.erase(watch_list.begin()+i);
			return true;
		}
	}
	return false;
}
bool net_watcher::Check(int iOrderType,const tstring& stNetFromPath_org,const tstring& stNetToPath_org)
{
#ifdef _DEBUG
	CMyCout log(_tcout);
	log << (int)watch_list.size() << _T("Check ") << stNetFromPath_org << _T(" / ") << stNetToPath_org << _T("\n");
#endif

	tstring stNetFromPath=Utility::RefinePath(stNetFromPath_org);
	tstring stNetToPath=Utility::RefinePath(stNetToPath_org);
	for (unsigned int i=0;i<watch_list.size();i++)
	{
		if (watch_list[i].get<0>()==iOrderType
			&& _tcscmp(watch_list[i].get<1>().c_str(),stNetFromPath.c_str())==0
			&& _tcscmp(watch_list[i].get<2>().c_str(),stNetToPath.c_str())==0)
			return true;
	}
	return false;
}
