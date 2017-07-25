#pragma once

#include "watcher.h"
#include "etc.h"
#include "config.h"

#define SLEEP_FOR_COPY 2000
//#define SLEEP_FOR_WRITE 100

class netwatcher
	: public cFileSystemWatcher
{
public:
	netwatcher(config& c_,CMyCout& l)
		: log(l)
		,config_(c_)
	{
	}
	~netwatcher()
	{
		StopWatch();
	}

	// watcher
	void StartWatch();
	void StopWatch();
	void Heartbeat(DWORD period)
	{
		if (root_path!=_T(""))
			cFileSystemWatcher::Heartbeat(period);
	}

protected:
	// file watch
	void OnCreate(tstring filename_org);
//	void OnDelete(const tstring& filename_org);
//	void OnChange(const tstring& filename_org);
//  void OnRename(const tstring& oldFileName_org, const tstring& newFileName_org);

protected:
//	net_watcher net_watcher_;
	CMyCout& log;
	config& config_;
	tstring root_path;
};