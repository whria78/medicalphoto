#include "stdafx.h"
#include "etc.h"

std::vector<boost::tuple<int,int>> ThreadControl::ID_list;
boost::mutex ThreadControl::mutex_;

ThreadControl::ThreadControl(int iType)
{
	boost::mutex::scoped_lock lock(mutex_);

	iThreadType=iType;
	bCheckTerminate=NULL;

	if (ID_list.size()==0)
		iThreadID=0;
	else
		iThreadID=ID_list[ID_list.size()-1].get<1>()+1;

	ID_list.push_back(boost::tuples::make_tuple(iThreadType,iThreadID));
}
ThreadControl::~ThreadControl()
{
	Clear();

	if (bCheckTerminate!=NULL)
		*bCheckTerminate=true;
/*
	boost::mutex::scoped_lock lock(mutex_);

	for (unsigned int i=0;i<ID_list.size();i++)
	{
		if (ID_list[i].get<1>()==iThreadID)
			ID_list.erase(ID_list.begin()+i);
	}
	*/
}
void ThreadControl::Clear()
{
	boost::mutex::scoped_lock lock(mutex_);

	for (unsigned int i=0;i<ID_list.size();i++)
	{
		if (ID_list[i].get<1>()==iThreadID)
			ID_list.erase(ID_list.begin()+i);
	}
}

bool ThreadControl::Check(bool* bCheckTer)
{
	boost::mutex::scoped_lock lock(mutex_);

	bCheckTerminate=bCheckTer;
	if (bCheckTerminate!=NULL)
		*bCheckTerminate=false;

	int iLastID=0;
	for (unsigned int i=0;i<ID_list.size();i++)
	{
		if (ID_list[i].get<0>()==iThreadType)
			iLastID=ID_list[i].get<1>();
	}

	if (iLastID==iThreadID)
		return true;
	else
		return false;
}
tstring Utility::GetNumericName(int iRenameCount,const tstring& stPath)
{
	if (iRenameCount==0)
	{
		return stPath;
	}
	else
	{
		_tpath initial(stPath);
		_tpath dir=_tpath(initial.parent_path());

		_tformat fmt(_T("%s (%d)%s"));
		fmt % MFile::GetFileNamesExtL(stPath)
			% iRenameCount
			% MFile::GetFileExtL(stPath);
		dir/=fmt.str();		dir = refinepath(dir);
		return dir.c_str();
	}
}