#include "stdafx.h"
#include "config.h"

void config_common::RefinePath(int iIndex)
{
	_tpath OrgPath;

	try
	{
		std::vector<_tpath> dir_list;
		_tdirectory_iterator end_iter;

		std::string temp = Get(iIndex);
		boost::replace_all(temp, "\\", "/");
		while (temp.find_last_of("/") == (temp.length() - 1) && temp.length()!=0)
		{
			temp = temp.substr(0, temp.length() - 1);
		}
		Set(iIndex, temp);

		

		if (_tcscmp((boost::filesystem::path(Get(iIndex)).branch_path()).c_str(),_T(""))==0)
			return;

		OrgPath=_tpath(MCodeChanger::_CCL(Get(iIndex)));
		tstring temp2=OrgPath.c_str();boost::algorithm::to_lower(temp2);

		if (!MFile::Exists(OrgPath))
			MFile::CreateFolder(OrgPath);

		for ( _tdirectory_iterator dir_itr(OrgPath.parent_path());
		  dir_itr != end_iter;
		  ++dir_itr )
		{
			_tpath temp = MFile::refinepath(*dir_itr);

			tstring stPath=_tpath(temp).c_str();
			tstring temp1=stPath;
			boost::algorithm::to_lower(temp1);
			if (_tcscmp(temp1.c_str(),temp2.c_str())==0)
			{
				boost::replace_all(stPath, _T("\\"), _T("/"));
				Set(iIndex,MCodeChanger::_CCU(stPath));
				return;
			}
		}
	}
	catch (std::exception& e)
	{
		log << OrgPath.c_str() << MCodeChanger::_CCL(e.what()) << _T("\n");
	}
}


int config_common::GetSize() {return MAX_CONFIG;}
void config_common::Insert(int iIndex,const tstring& text,const std::string& default_value)
{
	data_[iIndex]=boost::tuples::make_tuple(text,default_value,default_value);iSize++;
}
std::string config_common::Get(int iIndex) 
{
	return data_[iIndex].get<2>();
}
std::string config_common::Get(int iIndex,int iSubIndex)
{
	param_list param_list_;
	SplitParams(iIndex,param_list_);
	if ((int)param_list_.size()>iSubIndex)
	{
		return param_list_[iSubIndex];
	}
	else
	{
		throw std::logic_error("Index Overflow");
		return "";
	}
}

int config_common::GetInt(int iIndex)
{
	return atoi(Get(iIndex).c_str());
}
std::string config_common::GetDefault(int iIndex)
{
	return data_[iIndex].get<1>();
}
void config_common::LoadDefault(int iIndex)
{
	Set(iIndex,GetDefault(iIndex));
}
void config_common::Set(int iIndex,const int value) 
{
	Set(iIndex,to_string(value));
}
void config_common::Set(int iIndex,const bool value) 
{
	if (value)
		Set(iIndex,std::string("1"));
	else
		Set(iIndex,std::string("0"));
}
void config_common::Set(int iIndex,const std::string& value) 
{
	data_[iIndex]=boost::tuples::make_tuple(GetText(iIndex),GetDefault(iIndex),value);
}
void config_common::Add(int iIndex,const int value)
{
	Add(iIndex,to_string(value));
}
void config_common::Add(int iIndex,const std::string& value)
{
	if (strcmp(value.c_str(),"")==0) return;
	std::string set_value=Get(iIndex);
	if (strcmp(set_value.c_str(),"")==0) 
	{Set(iIndex,value);return;}
	set_value+=",";
	set_value+=value;
	Set(iIndex,set_value);
}

tstring config_common::GetText(int iIndex)
{
	return data_[iIndex].get<0>();
}
/*
void config_common::SplitParams(int iIndex,std::vector<std::string>& param_list)
{
	param_list.clear();
	std::vector<std::string> split_vec;
	std::string temp_string=Get(iIndex);
	boost::split(split_vec,temp_string,boost::is_any_of(","));

	unsigned int i;
	for (i=0;i<split_vec.size();i++)
	{
		boost::algorithm::trim(split_vec[i]);
		param_list.push_back(split_vec[i]);
	}
}
*/
bool config_common::Compare(int iIndex,int value) {return Compare(iIndex,to_string(value));}
bool config_common::Compare(int iIndex,const std::string& value)
{
	std::vector<tstring> split_vec_ext;
	std::string temp_string=Get(iIndex);
	boost::split(split_vec_ext,temp_string,boost::is_any_of(_T(",")));
	unsigned int i;

	std::string temp2=value;
	boost::algorithm::to_upper(temp2);
	boost::algorithm::trim(temp2);

	for (i=0;i<split_vec_ext.size();i++)
	{
		boost::algorithm::trim(split_vec_ext[i]);

		std::string temp1=MCodeChanger::_CCU(split_vec_ext[i]);
		boost::algorithm::to_upper(temp1);

		if (strcmp(temp1.c_str(),temp2.c_str())==0) return true;
	}
	return false;
}


std::string config_common::to_string(int interger)
{
	boost::format fmt("%d");
	fmt % interger;
	return fmt.str();
}

bool config_common::Exist(const tstring& command,const tstring& param_name)
{
	if (_tcscmp(param_name.c_str(),_T(""))==0) return false;
	if (_tcscmp(command.c_str(),param_name.c_str())==0)
		return true;
	else
		return false;
}
void config_common::SetParam(std::string& param,std::string value) {param=value;}
void config_common::Update(const tstring& command, const tstring& param_name,const std::string& param_data,FILE* fp)
{
	if (_tcscmp(param_name.c_str(),_T(""))==0) return;
	if (_tcscmp(command.c_str(),param_name.c_str())==0)
		fputs(MCodeChanger::_CCN(join(param_name,param_data)).c_str(),fp);
}
void config_common::Merge(const std::vector<tstring>& command_list,const tstring& param_name,const std::string& param_data,FILE* fp)
{
	if (_tcscmp(param_name.c_str(),_T(""))==0) return;
	bool bExist=false;
	for (unsigned int i=0;i<command_list.size();i++)
	{
		if (_tcscmp(command_list[i].c_str(),param_name.c_str())==0)
			bExist=true;
	}
	if (!bExist)
		Insert(param_name,param_data,fp);
}
void config_common::Insert(const tstring& param_name,const int param_data,FILE* fp)
{
	Insert(param_name,to_string(param_data),fp);
}
void config_common::Insert(const tstring& param_name,const std::string& param_data,FILE* fp)
{
	if (_tcscmp(param_name.c_str(),_T(""))==0) return;
	std::string write_string=MCodeChanger::_CCN(join(param_name,param_data));
	fputs(write_string.c_str(),fp);
//	_fputts(dumy,fp);
}

tstring config_common::join(const tstring& command,const std::string& param)
{
	if (_tcscmp(command.c_str(),_T(""))==0) return _T("\n");
	_tformat fmt(_T("%s=%s\n"));
	fmt % command % MCodeChanger::_CCL(param);
	return fmt.str();
}
tstring config_common::join(const tstring& command,const int& param)
{
	return join(command,to_string(param));
}





	bool config_common::load(const TCHAR* stFilename)
	{
//		CMyCout log(_tcout);
//		log << _T("Loading... ") << stFilename << log.endl();
		FILE* fp;

		fp=_tfopen(stFilename,_T("r"));
		clear();
		if (fp==NULL) 
		{
			log << stFilename << _T(" is not exist. Load default\n");
			tstring org_name=stFilename;
			org_name+=_T(".org");
			if (MFile::ExistsL(org_name))
			{
				MFile::CopyFileL(org_name,stFilename);
			}
			fp=_tfopen(stFilename,_T("r"));
			if (fp==NULL)
				return false;
		}
		char buff[256];
		while (fgets(buff,256,fp)!=NULL)
		{
			tstring str(MCodeChanger::_CCW(buff));
			boost::algorithm::trim(str);
//			std::vector<tstring> split_vec_jusuk;
//			boost::split(split_vec_jusuk,str,boost::is_any_of(_T("//")));
//			Utility::split(str,_T("//"),split_vec_jusuk);

//			int ipos;
			if (str.find(_T("//"))!=tstring::npos)
			{
				int ipos=str.find(_T("//"));
				str=HString::Left(str,ipos);
			}
//			str=split_vec_jusuk[0];

			std::vector<tstring> split_vec;
			boost::split(split_vec,str,boost::is_any_of(_T("=")));

			if (split_vec.size()==2)
			{
				tstring command=split_vec[0];
				std::string param=MCodeChanger::_CCU(split_vec[1]);
				boost::algorithm::trim(param);

				if (strcmp(param.c_str(),"")!=0)
				{
					boost::algorithm::trim(command);boost::algorithm::to_upper(command);

					for (int j=0;j<GetSize();j++)
					{
						if (Exist(command,GetText(j))) Set(j,param);
					}
				}
			}
		}
		fclose(fp);
		return true;
	}

	void config_common::clear()
	{
		for (int i=0;i<GetSize();i++)
		{
			LoadDefault(i);
		}
	}
	void config_common::save(const TCHAR* stFilename)
	{
		log << _T("Saving... ") << stFilename << log.endl();

		FILE* fp=NULL;
		FILE* fp_write=NULL;

		std::vector<std::string> config_txt;
		fp=_tfopen(stFilename,_T("r"));

		if (fp!=NULL)
		{
			char buff[256];
			while (fgets(buff,256,fp)!=NULL)
			{
				config_txt.push_back(buff);
			}
			fclose(fp);

			fp_write=_tfopen(stFilename,_T("w"));
			if (fp_write==NULL) return;

			unsigned int i;
			std::vector<tstring> command_list;
			for (i=0;i<config_txt.size();i++)
			{
				tstring str=MCodeChanger::_CCL(config_txt[i]);
				boost::algorithm::trim(str);

				if (str.length()>0)
				{
					if (boost::algorithm::find_first(str,_T("//")))
//						fputs(MCodeChanger::_CCN(join(str,"\n")).c_str(),fp_write);
					{
						str+=_T("\n");
						fputs(MCodeChanger::_CCN(str).c_str(),fp_write);
					}
					else
					{

						std::vector<tstring> split_vec;
						boost::split(split_vec,str,boost::is_any_of(_T("=")));

						if (split_vec.size()==2)
						{
							tstring command=split_vec[0];
							command_list.push_back(command);
							tstring param=split_vec[1];
							boost::algorithm::trim(command);boost::algorithm::to_upper(command);

							for (int j=0;j<GetSize();j++)
							{
								Update(command,GetText(j),Get(j),fp_write);
							}

						}
					}
				}
				else
				{
					fputs("\n",fp_write);
				}
			}

			for (int j=0;j<GetSize();j++)
			{
				Merge(command_list,GetText(j),Get(j),fp_write);
			}
		}
		else
		{
			fp_write=_tfopen(stFilename,_T("w"));

			if (fp_write==NULL) return;

			fputs("// MedicalPhoto Config : don't remove here\n",fp_write);
			fputs("\n",fp_write);
			fputs("\n",fp_write);

			for (int j=0;j<GetSize();j++)
			{
				Insert(GetText(j),Get(j),fp_write);
			}
		}
		if (fp_write!=NULL) fclose(fp_write);
		
	}


	void version_checker::load()
	{
		config_common::load(_T(VERSION_CONFIG_FILENAME));
		LoadDefault(VERSION_FILE);

//		check_data_exist(ICD10_FILE_NAME);
//		check_data_exist(DATA_FILE_NAME);
	}
	void version_checker::check_data_exist(int iIndex)
	{
		std::vector<std::string> param_list1;
		SplitParams(iIndex,param_list1);
		std::string stFinalParam;
		for (unsigned int i=0;i<param_list1.size();i++)
		{
			if (MFile::ExistsL(MCodeChanger::_CCL(param_list1[i])))
			{
				stFinalParam+=",";
				stFinalParam+=param_list1[i];
			}
		}
		Set(iIndex,HString::Right(stFinalParam,stFinalParam.length()-1));
	}


	void version_checker::increase_version(int iIndex)
	{
#ifdef _DEBUG
		if (config_common::load(_T(VERSION_CONFIG_FILENAME))==false)
			return;

		Set(iIndex,get_increase_version(iIndex));
		Set(VERSION_FILE_VERSION,get_increase_version(VERSION_FILE_VERSION));

		config_common::save(_T(VERSION_CONFIG_FILENAME));


		FILE* fp;
		FILE* fp_w;
		FILE* fp_w2;

		fp=_tfopen(_T("../version.template"),_T("r"));
		if (fp==NULL) return;
		fp_w=_tfopen(_T("../version.rc2"),_T("w"));
		if (fp_w==NULL)
		{
			fclose(fp);
			return;
		}
		fp_w2=_tfopen(_T("../update.txt"),_T("w"));
		if (fp_w2!=NULL)
		{
			std::string stVersion=Get(VERSION_FILE_VERSION);
			fputs(stVersion.c_str(),fp_w2);
			fclose(fp_w2);
		}
		char buff[256];
		while (fgets(buff,256,fp)!=NULL)
		{
			tstring str(MCodeChanger::_CCL(buff));

			std::string stVersion=Get(VERSION_FILE_VERSION);
			boost::algorithm::replace_all(stVersion,".",",");

			boost::algorithm::replace_all(str,_T("%s"),MCodeChanger::_CCL(Get(VERSION_FILE_VERSION)));
			boost::algorithm::replace_all(str,_T("%comma"),stVersion);

			fputs(MCodeChanger::_CCN(str).c_str(),fp_w);
		}
		fclose(fp_w);
		fclose(fp);
#endif
	}
	std::string version_checker::get_increase_version(int iIndex)
	{
		std::string increased_version=Get(iIndex);

		std::vector<std::string> split_vec;
		boost::split(split_vec,increased_version,boost::is_any_of(_T(".")));

		if (split_vec.size()!=4)
		{
			std::logic_error("Invalid Version Format");
			return "";
		}

		boost::format fmt("%d.%d.%d.%d");
		fmt % split_vec[0]
		% split_vec[1]
		% split_vec[2]
		% (atoi(split_vec[3].c_str())+1);
		return fmt.str();
	}

	tstring version_checker::GetTemp(const std::string& stAppName)
	{
		tstring stWAppName=MCodeChanger::_CCL(stAppName);
		_tpath path(stWAppName);
		_tpath dir=path.parent_path();

		tstring temp_file=MFile::GetFileNameL(path.c_str());
		temp_file+=_T(".tmp");

		_tpath final= Utility::refinepath(dir / temp_file);

		return final.c_str();
	}

	bool version_checker::NeedUpdate(int iTarget,const std::string& stVersion) // 0=client / 1=server / 2=data
	{
		std::string str1=stVersion;
		std::string str2;
		switch (iTarget)
		{
		case VERSION_FILE:
			{
				str2=Get(VERSION_FILE_VERSION);
			}
			break;
		case CLIENT_APP_NAME:
			{
				str2=Get(CLIENT_VERSION);
			}
			break;
		case SERVER_APP_NAME:
			{
				str2=Get(SERVER_VERSION);
			}
			break;
		case CONSOLESERVER_APP_NAME:
			{
				str2=Get(CONSOLESERVER_VERSION);
			}
			break;
		case ICD10_FILE_NAME:
			{
				str2=Get(ICD10_FILE_VERSION);
			}
			break;
		case DATA_FILE_NAME:
			{
				str2=Get(DATA_FILE_VERSION);
			}
			break;
		default:
			{
				return false;
			}
			break;
		}
		if (strcmp(str1.c_str(),str2.c_str())==0) return false;

#ifdef _DEBUG
		std::vector<std::string> split_vec1,split_vec2;
		boost::split(split_vec1,str1,boost::is_any_of("."));
		boost::split(split_vec2,str2,boost::is_any_of("."));

		if (split_vec1.size()!=4 || split_vec2.size()!=4)
		{
			std::logic_error("Invalid Version Format");
			return false;
		}

		for (int i=0;i<4;i++)
		{
			if (atoi(split_vec1[i].c_str()) > atoi(split_vec2[i].c_str())) return false;
		}
#endif
		return true;
	}