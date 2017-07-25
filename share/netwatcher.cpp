#include "stdafx.h"
#include "netwatcher.h"


void netwatcher::OnCreate(tstring filename_org)
{
	boost::replace_all(filename_org, _T("\\"), _T("/"));
	try
	{
		Utility::sleep(SLEEP_FOR_COPY);
		log << _T("[Watcher] Create :") << filename_org << log.endl();


		// 추가 작업
		//	MFile::Rename();


		tstring stFileExt=MFile::GetFileExtL(filename_org);

		if (config_.Compare(FILE_EXTENSIONS,MCodeChanger::_CCU(stFileExt))==false) return;

		boost::posix_time::ptime Time;
		_tpath dest_path;
		_tpath org_path(root_path);
		org_path/=filename_org;		org_path = Utility::refinepath(org_path);

		if (Utility::LoadMetatag(org_path.c_str(),Time))
		{
			boost::gregorian::date Date(Time.date());

			_tformat a(_T("%d")),b(_T("%d"));
			a % Date.month().as_number();
			b % Date.day().as_number();

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

			_tformat Year_Format(_T("%d"));
			Year_Format % Date.year();

			_tformat DatePath_Format(_T("%d/%d-%d/%s-%d-%d"));
			DatePath_Format 
				% Date.year()
				% Date.year()
				% month_string
				% HString::Right(Year_Format.str(),2)
				% month_string
				% day_string;

			dest_path=_tpath(MCodeChanger::_CCL(config_.Get(DATA_PATH)));
			dest_path/=DatePath_Format.str();
			dest_path/=org_path.filename();
			dest_path = Utility::refinepath(dest_path);
		}
		else
		{
			dest_path=_tpath(MCodeChanger::_CCL(config_.Get(DATA_PATH)));
			dest_path/=_T("date_unknown");
			dest_path/=org_path.filename();
			dest_path = Utility::refinepath(dest_path);
		}

		MFile::CreateFolder(dest_path.parent_path());
		MFile::Rename(org_path,dest_path);



	}
	catch(std::exception& e)
	{
		log << _T("[Watcher] Create Error : ") << MCodeChanger::_CCL(e.what()) << log.endl();
	}
	catch(...)
	{
		log << _T("[Watcher] Create Error") << log.endl();
	}
}

void netwatcher::StartWatch()
{
//	std::string dumy="d:\\to";
//	config_.Set(UPLOAD_WATCH_PATH,dumy);

	if (config_.Get(UPLOAD_WATCH_PATH)=="")
		return;

	root_path=MCodeChanger::_CCL(config_.Get(UPLOAD_WATCH_PATH));

    DWORD FILTER = 
  /*      FILE_NOTIFY_CHANGE_CREATION | 
        FILE_NOTIFY_CHANGE_DIR_NAME |
//		FILE_NOTIFY_CHANGE_LAST_WRITE |
		FILE_NOTIFY_CHANGE_SIZE |
        FILE_NOTIFY_CHANGE_FILE_NAME;
*/
//        FILE_NOTIFY_CHANGE_SECURITY |
        FILE_NOTIFY_CHANGE_CREATION |
//        FILE_NOTIFY_CHANGE_LAST_ACCESS |
        FILE_NOTIFY_CHANGE_LAST_WRITE |
        FILE_NOTIFY_CHANGE_SIZE |
//        FILE_NOTIFY_CHANGE_ATTRIBUTES |
        FILE_NOTIFY_CHANGE_DIR_NAME |
        FILE_NOTIFY_CHANGE_FILE_NAME;

	if (cFileSystemWatcher::Open(root_path,FILTER,true))
		log << _T("[Startup] Start watching : ") << root_path << _T("\n");
}
void netwatcher::StopWatch()
{
	cFileSystemWatcher::Close();
}