#include "stdafx.h"

#include "datatype.h"
#include "../share/file.h"
/*
std::string fileinfo::stRootPath="";

std::string fileinfo::GetPath() const
{
	std::string result=stRootPath;

	std::string temp_NetPath=stNetPath;
	boost::algorithm::replace_first(temp_NetPath,"root","");
	
	result+=temp_NetPath;
	return result;
}
std::string fileinfo::GetFileName() const
{
	std::string result=stNetPath;
	if (boost::algorithm::find_first(result,stNetDir))
	{
		boost::algorithm::replace_first(result,stNetDir,"");
		return result;
	}
	else
		return "";
}
std::string fileinfo::GetFileExt() const// .jpg
{
	return MCodeChanger::_CCU(MFile::GetFileExtL(MCodeChanger::_CCL(GetPath())));
}
std::string fileinfo::GetFileNamesExt() const//	aa
{
	return MCodeChanger::_CCU(MFile::GetFileNamesExtL(MCodeChanger::_CCL(GetPath())));
}
*/
std::string fileinfo::GetNetPath() const {return stNetPath;} //     /aa/b.jpg
std::string fileinfo::GetNetDir() const {return stNetDir;}  //     /aa/

