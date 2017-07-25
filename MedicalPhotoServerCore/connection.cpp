#include "stdafx.h"

#include "connection.h"
#include "connection_manager.hpp"

#include <boost/enable_shared_from_this.hpp>

void connection::process_error(const error_message& err) 	
  {
	  log.WriteError(err);
  }

void connection::process_socket_error(const boost::system::error_code& e)
{
	if (e!=boost::asio::error::operation_aborted)
	{
		if (e.value()==2)
		{
			log << _T("# Log Out ") 
				<< _T("[ ")
				<< MCodeChanger::_CCL(CurrentUser.stUserID)
				<< _T(" / ")
				<< MCodeChanger::_CCL(socket().remote_endpoint().address().to_string())
				<< _T(" ]")
				<< log.endl();
			connection_manager_.stop(shared_from_this());
		}
		else
		{
			error_message err_;
			err_.Add(SOC_ERROR,e.value(),e.message());
			process_error(err_);
			connection_manager_.stop(shared_from_this());
		}
	}
}



    void connection::handle_execute_order(const boost::system::error_code& e)
  {
	  if (e) {
		  process_socket_error(e);
		  return;
	  }

#ifdef _DEBUG
	  log<<_T("connection::handle_execute_order\n");
#endif

	  error_message result_message;
	  __int64 blank_=0;

	  clear();

	  bool bFileTransfer=false;
	  tstring stLocalPath;
	  __int64 lFileSize;
	  FILE *fp=NULL;

	  std::istringstream archive_stream_in(connection_basic::InboundBuffer());
      boost::archive::text_iarchive archive_in(archive_stream_in);

	  std::ostringstream archive_stream_out;
	  boost::archive::text_oarchive archive_out(archive_stream_out);

	  try{

      archive_in >> command_;

//	  log << _T("Command (") << command_.order_code << _T(") by ") << MCodeChanger::_CCL(CurrentUser.stUserID) << log.endl();

	  if (command_.order_code!=LOGIN && bLogin==false)
		  result_message.Add(NOT_LOGON);
	  else
	  {
		  switch (command_.order_code)
		  {
		  case LOGIN:
		  {
			  archive_in >> CurrentUser.stUserID >> CurrentUser.stPasswd;

			  if (!config_.GetInt(MULTIUSER_SUPPORT))
				  CurrentUser.stUserID=config_.Get(SUPERADMIN_ID);

			  log.WriteCommand(CurrentUser.stUserID,LOGIN,CurrentUser.stUserID,CurrentUser.stPasswd);

			  if (config_.GetInt(MULTIUSER_SUPPORT))
			  {
					boost::format fmt("SELECT * FROM %s WHERE %s='%s' AND passwd='%s';");
					fmt 
						% CurrentUser.get_tablename()
						% CurrentUser.get_primary()
						% CurrentUser.stUserID  // ID
						% CurrentUser.stPasswd; // PASSWD

					std::string kk=fmt.str();

					CppSQLite3Table t=sql.getTable(fmt.str().c_str());

				  if (t.numRows()!=1) 
					{
						result_message.Add(PASSWORD_MISMATCH);

						boost::format fmt("SELECT * FROM %s WHERE %s='%s';");
						fmt 
							% CurrentUser.get_tablename()
							% CurrentUser.get_primary()
							% CurrentUser.stUserID;  // ID
						if (sql.execScalar(fmt.str().c_str())!=1) 
						{
							result_message.Add(ID_NOTEXIST);
							break;
						}
						break;
					}
				int index=0;
				CurrentUser=user(t,&index);

			  }

			  bLogin=true;
			  netpath_.Open(CurrentUser.stUserID);

			  serial_out(archive_out,result_message);
			  serial_out(archive_out,config_);

		  }
		  break;

		  case PASSWD_CHANGE:
		  {
			  std::string stNewID,stNewPass;
			  archive_in >> stNewID >> stNewPass;

			  log.WriteCommand(CurrentUser.stUserID,PASSWD_CHANGE,stNewID,stNewPass);

			boost::format fmt("UPDATE %s SET %s='%s',passwd='%s' WHERE %s='%s' AND passwd='%s';");
			fmt 
				% CurrentUser.get_tablename()
				% CurrentUser.get_primary()

				% stNewID  // ID
				% stNewPass  // PASSWD

				% CurrentUser.get_primary()

				% CurrentUser.stUserID
				% CurrentUser.stPasswd;

			int bResult=sql.execDML(fmt.str().c_str());
			if (bResult!=1) result_message.Add(SQL_ERROR,0,fmt.str().c_str());

			serial_out(archive_out,result_message);
			serial_out(archive_out,blank_);
		  }
		  break;

		  case ADD_FAVORATE:
		  {

		  }
		  break;
		  case DELETE_FAVORATE:
		  {

		  }
		  break;
		  case GETUSERDX:
		  {
			  std::string stDiagnosis;
			  archive_in >> stDiagnosis ;

  			  log.WriteCommand(CurrentUser.stUserID,GETUSERDX,stDiagnosis);

			  log<<_T("GETUSERDX : ") << MCodeChanger::_CCL(stDiagnosis);


			  userdx_list result;

			  if (strcmp(stDiagnosis.c_str(),"")==0)
			  {
				  sql.GetTable(userdx::get_tablename(),result,userdx());
			  }
			  else
			  {
				  sql.Find(stDiagnosis,result,userdx());
			  }

			  serial_out(archive_out,result_message);
			  serial_out(archive_out,result);
		  }
		  break;
		  case SETUSERDX:
		  {
			  userdx diagnosis_from_,diagnosis_to_;
			  archive_in >> diagnosis_from_ >> diagnosis_to_ ;

  			  log.WriteCommand(CurrentUser.stUserID,SETUSERDX,diagnosis_from_.sql_set_values(),diagnosis_to_.sql_set_values());

			  if (sql.IsExists(diagnosis_from_))
			  {
				  if (diagnosis_to_.isempty())
					  sql.Delete(diagnosis_to_);
				  // UPDATE
				  if (!sql.Update(diagnosis_from_,diagnosis_to_))
					  result_message.Add(SQL_ERROR,0,diagnosis_from_.get_unique());
			  }
			  else
			  {
				  // INSERT
				  if (!sql.Insert(diagnosis_to_))
					  result_message.Add(SQL_ERROR,0,diagnosis_from_.get_unique());
			  }

			serial_out(archive_out,result_message);
			serial_out(archive_out,blank_);

		  }
		  break;
		  case GETDX:
		  {
			  std::string stDiagnosis;
			  archive_in >> stDiagnosis ;

  			  log.WriteCommand(CurrentUser.stUserID,GETDX,stDiagnosis);

			  dx_list result;
			  sql.Find("icd10","diagnosis",
				  stDiagnosis,  // Diagnosis
				  result,diagnosis());


			  serial_out(archive_out,result_message);
			  serial_out(archive_out,result);
		  }
		  break;
		  case UPLOADFILE:
		  {
			  std::string stNetPath_org,stNetPath;
 
			  archive_in >> stNetPath_org >> lFileSize;
			  stNetPath=Transfer_Format(stNetPath_org);

  			  log.WriteCommand(CurrentUser.stUserID,UPLOADFILE,stNetPath,lFileSize);

			  _tpath stPath(netpath_.Net_Local(stNetPath));

			  if (MFile::Exists(stPath))
				{result_message.Add(FILE_DUPLICATE);break;}

			if (lFileSize<0)
				{result_message.Add(SIZE_ERROR);break;}

			if (!netpath_.CheckRootPriv(stPath,true))
				{result_message.Add(NO_PRIV);break;}

			stLocalPath=stPath.native_directory_string();

			MFile::CreateFolder(stPath.branch_path());

			fp=_tfopen(stLocalPath.c_str(),_T("wb"));

			  if (fp==NULL) 
			  {result_message.Add(FILE_WRITE_OPEN);break;}

			  bFileTransfer=true;
  			serial_out(archive_out,result_message);
//			serial_out(archive_out,blank_);
		  }
		  break;
		  case THUMB_UPLOADFILE:
		  {
			  std::string stNetPath,stNetPath_org;
			  archive_in >> stNetPath_org >> lFileSize ;
			  stNetPath=Transfer_Format(stNetPath_org);

  			  log.WriteCommand(CurrentUser.stUserID,THUMB_UPLOADFILE,stNetPath,lFileSize);

			  _tpath stPath(netpath_.Net_Local(stNetPath));

			if (!MFile::Exists(stPath))
				{result_message.Add(FILE_NOT_EXIST);break;}

			if (lFileSize<0)
				{result_message.Add(SIZE_ERROR);break;}

			if (!netpath_.CheckRootPriv(stPath,false))
				{result_message.Add(NO_PRIV);break;}

			stLocalPath=netpath_.Net_Thumb(stNetPath);

			_tpath stThumbPath(stLocalPath);
//			bfs::create_directory(stThumbPath.branch_path());
			MFile::CreateFolder(stThumbPath.branch_path());

			  fp=_tfopen(stLocalPath.c_str(),_T("wb"));

			  if (fp==NULL) 
			  {result_message.Add(FILE_WRITE_OPEN);break;}

			  bFileTransfer=true;
			serial_out(archive_out,result_message);
//			serial_out(archive_out,blank_);

		  }
		  break;

		  case DELETEFILE:
		  {
			  std::string stNetPath_org,stNetPath;
			  archive_in >> stNetPath_org ;
			  stNetPath=Transfer_Format(stNetPath_org);

  			  log.WriteCommand(CurrentUser.stUserID,DELETEFILE,stNetPath);

			  // Priv Check
			  if (!check_netpath_priv(stNetPath,true))
				{result_message.Add(NO_PRIV);break;}

			  _tpath stPath(netpath_.Net_Local(stNetPath));

/*			  bool bResult=MFile::Delete(stPath);
			  if (!bResult)
			  {
				boost::format fmt("File Delete Error : %s");fmt % stNetPath;
				process_file_error(fmt.str());
				result_message.Add(FILE_DELETE,0,fmt.str());
			  }

			  // thumbnail
			  MFile::Delete(netpath_.Net_Thumb(stNetPath));
			  // sql

			  netpath_.BeginTransaction();
			  netpath_.DeleteFile(stNetPath);
			  netpath_.DeleteComment(stNetPath);
			  netpath_.CommitTransaction();
*/
			  netpath_.DeleteFile(stNetPath);
			  // thumbnail
			  MFile::Delete(netpath_.Net_Thumb(stNetPath));

			serial_out(archive_out,result_message);
			serial_out(archive_out,blank_);
		  }
		  break;
		  case RENAMEFOLDER:
		  {
			  std::string from_org,from;
			  std::string to_org,to;

			  archive_in >> from_org >> to_org;

			  from=Transfer_Format(from_org);
			  to=Transfer_Format(to_org);

  			  log.WriteCommand(CurrentUser.stUserID,RENAMEFOLDER,from,to);

			  // Priv Check
			  if (!check_netpath_priv(from,true))
				{result_message.Add(NO_PRIV);break;}

			  netpath_.MoveFolder(from,to);

			  serial_out(archive_out,result_message);
			  serial_out(archive_out,blank_);
		  }
		  break;
		  case RENAMEFILE:
		  {
			  std::string from_org,from;
			  std::string to_org,to;

			  archive_in >> from_org >> to_org;

			  from=Transfer_Format(from_org);
			  to=Transfer_Format(to_org);

  			  log.WriteCommand(CurrentUser.stUserID,RENAMEFILE,from,to);

			  // Priv Check
			  if (!check_netpath_priv(from,true))
				{result_message.Add(NO_PRIV);break;}

			  netpath_.MoveFile(from,to);

/*
			  // original file
			  _tpath stPathFrom(netpath_.Net_Local(from));
			  _tpath stPathTo(netpath_.Net_Local(to));

			  bool bResult=MFile::Rename(stPathFrom,stPathTo);
			  if (!bResult)
			  {
				boost::format fmt("Path Rename Error : %s %s");fmt % from % to;
				process_file_error(fmt.str());
				result_message.Add(PATH_RENAME,0,fmt.str());
			  }
			  
			  // thumbnail file
			  MFile::Rename(netpath_.Net_Thumb(from),netpath_.Net_Thumb(to));

			  // sql data

			  fileinfo fileinfo_from_,fileinfo_to_,dumy;
			  if (netpath_.GetFileInfo(from,fileinfo_from_)==false)
				  break;  // SQL need reload 

			  fileinfo_to_=fileinfo_from_;
			  dumy=netpath_.CreateFileInfoL(stPathTo.string());
			  fileinfo_to_.stNetDir=dumy.stNetDir;
			  fileinfo_to_.stNetPath=dumy.stNetPath;
			  
			  netpath_.BeginTransaction();

			  netpath_.Update(fileinfo_from_,fileinfo_to_);
			  comment_list comment_list_;
			  netpath_.FindComment_by_Path(from,comment_list_,true);
			  for (unsigned int i=0;i<comment_list_.size();i++)
			  {
				  comment comment_to_=comment_list_[i];
				  comment_to_.stNetPath=to;
				  netpath_.Update(comment_list_[i],comment_to_);
			  }

			  netpath_.CommitTransaction();
*/
			serial_out(archive_out,result_message);
			serial_out(archive_out,blank_);
		  }
		  break;
		  case CREATEFOLDER:
		  {
			  std::string stRootNetPath,stNetPath;
			  std::string stRootNetPath_org,stNetPath_org;
			  archive_in >> stRootNetPath_org >> stNetPath_org ;

			  stRootNetPath=Transfer_Format(stRootNetPath_org);
			  stNetPath=Transfer_Format(stNetPath_org);

  			  log.WriteCommand(CurrentUser.stUserID,CREATEFOLDER,stNetPath);

			  // Priv Check
			  if (!check_netpath_priv(stRootNetPath,true))
				{result_message.Add(NO_PRIV);break;}

			  netpath_.CreateFolder(stNetPath,CurrentUser.stUserID);

			  serial_out(archive_out,result_message);
			  serial_out(archive_out,blank_);
		  }
		  break;
		  case CREATEFOLDER_AUTO:
		  {
			  std::string stRootNetPath,stNetPath;
			  std::string stRootNetPath_org;
			  int iDateType;
			  archive_in >> stRootNetPath_org >> iDateType;

			  stRootNetPath=Transfer_Format(stRootNetPath_org);

  			  log.WriteCommand(CurrentUser.stUserID,CREATEFOLDER_AUTO,stRootNetPath);

			  // Priv Check
			  if (!check_netpath_priv(stRootNetPath,true))
				{result_message.Add(NO_PRIV);break;}

			  _tpath root_path=_tpath(MCodeChanger::_CCL(stRootNetPath));
			  _tpath path=root_path / Utility::GetToday(iDateType);

				int iRenameCount=0;

				tstring csDumy=Utility::GetNumericName(iRenameCount,path.string());
				iRenameCount++;

				while (MFile::ExistsL(csDumy)
					|| netpath_.IsExistsFromPrimary(MCodeChanger::_CCU(csDumy),fileinfo()))
				{
					csDumy=Utility::GetNumericName(iRenameCount,path.string());
					iRenameCount++;
				}
				std::string final_path=MCodeChanger::_CCU(csDumy);

				netpath_.CreateFolder(final_path,CurrentUser.stUserID);

				serial_out(archive_out,result_message);
				serial_out(archive_out,final_path);
		  }
		  break;		  
		  case DELETEFOLDER:
		  {
			  std::string stNetPath;
			  std::string stNetPath_org;
			  archive_in >> stNetPath_org ;
			  stNetPath=Transfer_Format(stNetPath_org);

  			  log.WriteCommand(CurrentUser.stUserID,DELETEFOLDER,stNetPath);

			  // Priv Check
			  if (!check_netpath_priv(stNetPath,true))
				{result_message.Add(NO_PRIV);break;}

			  netpath_.DeleteFolder(stNetPath);

/*			  _tpath stPath(netpath_.Net_Local(stNetPath));

			  bool bResult=MFile::DeleteAll(stPath);
			  if (!bResult)
			  {
				boost::format fmt("Folder Delete Error : %s");fmt % stNetPath;
				process_file_error(fmt.str());
				result_message.Add(FOLDER_DELETE,0,fmt.str());
			  }

			  // thumbnail
			  MFile::DeleteAll(netpath_.Net_Thumb(stNetPath));

			  //sql

			  netpath_.BeginTransaction();
			  netpath_.DeleteFolder(stNetPath);
			  netpath_.CommitTransaction();
*/
			serial_out(archive_out,result_message);
			serial_out(archive_out,blank_);
		  }
		  break;
		  case SETPATHINFO:
		  {
			  connection_basic::InboundBuffer();
			  fileinfo fileinfo_from_,fileinfo_to_;
			  archive_in >> fileinfo_from_ >> fileinfo_to_;

  			  log.WriteCommand(CurrentUser.stUserID,SETPATHINFO
				  ,fileinfo_from_.sql_set_values()
				  ,fileinfo_to_.sql_set_values()
				  );

			  // Priv Check
			  if (!check_netpath_priv(fileinfo_to_.GetNetPath(),true))
				{result_message.Add(NO_PRIV);break;}

//			  fileinfo_list f_list;
//			  netpath_.FindFile(fileinfo_.GetNetPath(),f_list,true);
			  if (netpath_.IsExists(fileinfo_from_) && 
				  strcmp(fileinfo_from_.GetNetPath().c_str(),"")!=0)
			  {
				  // UPDATE
				  if (!netpath_.Update(fileinfo_from_,fileinfo_to_))
				  {
					  result_message.Add(SQL_ERROR,0,fileinfo_from_.GetNetPath());
					  break;
				  }
			  }
			  else
			  {
				  // INSERT
				  if (!netpath_.Insert(fileinfo_to_))
				  {
					  result_message.Add(SQL_ERROR,0,fileinfo_to_.GetNetPath());
					  break;
				  }
			  }

			serial_out(archive_out,result_message);
			serial_out(archive_out,blank_);
		  }
		  break;
		  case DOWNLOADFILE:
		  {
			  std::string stNetPath;
			  std::string stNetPath_org;
			  archive_in >> stNetPath_org ;
			  stNetPath=Transfer_Format(stNetPath_org);

			  _tpath stPath(netpath_.Net_Local(stNetPath));

  			  log.WriteCommand(CurrentUser.stUserID,DOWNLOADFILE,stNetPath);

			  // Priv Check
			  if (!check_netpath_priv(stNetPath,false))
				{result_message.Add(NO_PRIV);break;}

			  if (!MFile::Exists(stPath))
				{result_message.Add(FILE_NOT_EXIST);break;}

			  stLocalPath=stPath.native_directory_string();
			  fp=_tfopen(stLocalPath.c_str(),_T("rb"));


			  if (fp==NULL) 
			  {result_message.Add(FILE_READ_OPEN);break;}

			  lFileSize=MFile::FileSize(stPath);
			  if (lFileSize<0)
			  {result_message.Add(SIZE_ERROR);break;}

			  bFileTransfer=true;
			serial_out(archive_out,result_message);
			  serial_out(archive_out,lFileSize);
		  }
		  break;
		  case GET_VERSIONFILE:
			  {
				  log.WriteCommand(CurrentUser.stUserID,GET_VERSIONFILE,"","");

				  serial_out(archive_out,result_message);
				  serial_out(archive_out,config_.version_);
//				  serial_out(archive_out,lFileSize);
			  }
			  break;
		  case UPDATE:
		  {
			  std::string stVersion;
			  update_struct update_struct_; 
			  archive_in >> update_struct_>> stVersion ;

			  log.WriteCommand(CurrentUser.stUserID,UPDATE,MCodeChanger::_CCU(config_.version_.GetText(update_struct_.iAppCode)),stVersion);

			  if (!config_.version_.NeedUpdate(update_struct_.iAppCode,stVersion))
			  {
				  // No Update now
				  result_message.Add(NO_UPDATE);break;
			  }

			  stLocalPath=MCodeChanger::_CCW(config_.version_.Get(update_struct_.iAppCode,update_struct_.iSubCode));

			  if (!MFile::ExistsL(stLocalPath))
				{result_message.Add(FILE_NOT_EXIST);break;}

			  fp=_tfopen(stLocalPath.c_str(),_T("rb"));

			  if (fp==NULL) 
			  {result_message.Add(FILE_READ_OPEN);break;}

			  lFileSize=MFile::FileSizeL(stLocalPath);
			  if (lFileSize<0)
			  {result_message.Add(SIZE_ERROR);break;}

			  bFileTransfer=true;
			  serial_out(archive_out,result_message);
			  serial_out(archive_out,lFileSize);
		  }
		  break;		  
		  case THUMB_DOWNLOADFILE:
		  {
			  std::string stNetPath;
			  std::string stNetPath_org;
			  archive_in >> stNetPath_org ;
			  stNetPath=Transfer_Format(stNetPath_org);

// 			  log.WriteCommand(CurrentUser.stUserID,THUMB_DOWNLOADFILE,stNetPath);

			  // Priv Check
			  if (!check_netpath_priv(stNetPath,false))
				{result_message.Add(NO_PRIV);break;}

			  _tpath stPath(netpath_.Net_Local(stNetPath));
			  stLocalPath=netpath_.Net_Thumb(stNetPath);

			  if (!MFile::ExistsL(stLocalPath))
				{result_message.Add(FILE_NOT_EXIST);break;}

			  fp=_tfopen(stLocalPath.c_str(),_T("rb"));

			  if (fp==NULL) 
			  {result_message.Add(FILE_READ_OPEN);break;}

			  lFileSize=MFile::FileSizeL(stLocalPath);
  			  if (lFileSize<0)
			  {result_message.Add(SIZE_ERROR);break;}

			  bFileTransfer=true;

			  serial_out(archive_out,result_message);
			  serial_out(archive_out,lFileSize);

		  }
		  break;
		  case GETFOLDERLIST:
		  {
			  std::string stNetPath;
			  std::string stNetPath_org;
			  bool bFileOnly;
			  archive_in >> stNetPath_org >> bFileOnly;
			  stNetPath=Transfer_Format(stNetPath_org);

  			  log.WriteCommand(CurrentUser.stUserID,GETFOLDERLIST,stNetPath,(int)bFileOnly);

			  // Priv Check
			  if (!check_netpath_priv(stNetPath,false))
				{result_message.Add(NO_PRIV);break;}

			  _tpath stPath(netpath_.Net_Local(stNetPath));

			  path_list pfound;

			  fileinfo_list result;
			  fileinfo_list temp_list;

//			  if (!MFile::List(stPath,pfound))
//			  {result_message.Add(FILE_LIST);serial_out(archive_out,result);break;}

			  netpath_.FindbyDir(stNetPath,result,true,bFileOnly);

/*			  unsigned int i=0;
			  for (i=0;i<temp_list.size();i++)
			  {
				  if (strcmp(stNetPath.c_str(),temp_list[i].GetNetPath().c_str())!=0)
				  {
					  if (!MFile::IsDirL(netpath_.Net_Local(temp_list[i].GetNetPath()))
						  || bFileOnly==false)
						  result.push_back(temp_list[i]);
				  }
			  }
*/
			  serial_out(archive_out,result_message);
			  serial_out(archive_out,result);
		  }
		  break;
		  case GETVOLLIST:
		  {
//			  archive_in >> stNetPath_org >> bFileOnly;

  			  log.WriteCommand(CurrentUser.stUserID,GETVOLLIST,"");

			  volname_list vol_list_;

//			  vol_list_.push_back(netpath_.GetFavorateRoot());

			  for (int i=0;i<netpath_.GetSize();i++)
			  {
				  vol_list_.push_back(MCodeChanger::_CCU(netpath_.Vol(i).GetVolName()));
			  }

			  serial_out(archive_out,result_message);
			  serial_out(archive_out,vol_list_);
		  }
		  break;
		  case SEARCHFILE_EXT:
		  {
			  std::vector<std::string> Keyword_list;
			  std::vector<std::string> Field_list;
			  archive_in >> Field_list >> Keyword_list;

  			  log.WriteCommand(CurrentUser.stUserID,command_.order_code,"","");

			  unsigned int i;

			  fileinfo_list f_list_;
			  
			  netpath_.FindFile(Field_list,Keyword_list,f_list_,false);

			  if ((int)f_list_.size()>config_.GetInt(MAX_SEARCH_RESULT_NUMBER))
			  {result_message.Add(TOO_MANY_RESULTS,f_list_.size(),"");break;}

			  fileinfo_list result;
			  for (i=0;i<f_list_.size();i++)
			  {
				  if (netpath_.CheckPriv(f_list_[i],false))
					  result.push_back(f_list_[i]);
			  }

			  serial_out(archive_out,result_message);
			  serial_out(archive_out,result);

		  }
		  break;
		  case SEARCH:
		  case SEARCH_EXACT:
		  case SEARCH_WITH_PATH:
		  case SEARCH_WITH_PATH_EXACT:
		  {
			  std::string stKeyword;
			  std::string stField;
			  archive_in >> stKeyword >> stField;

  			  log.WriteCommand(CurrentUser.stUserID,command_.order_code,stKeyword,stField);


			  unsigned int i;

			  fileinfo_list f_list_;
			  
			  if (command_.order_code==SEARCH)
				  netpath_.FindFile(stKeyword,f_list_,false);
			  if (command_.order_code==SEARCH_EXACT)
				  netpath_.FindFile(stKeyword,f_list_,true);
			  if (command_.order_code==SEARCH_WITH_PATH)
				  netpath_.FindPath(stKeyword,f_list_,false);
			  if (command_.order_code==SEARCH_WITH_PATH_EXACT)
				  netpath_.FindPath(stKeyword,f_list_,true);

			  if ((int)f_list_.size()>config_.GetInt(MAX_SEARCH_RESULT_NUMBER))
			  {result_message.Add(TOO_MANY_RESULTS,f_list_.size(),"");break;}

			  fileinfo_list result;
			  for (i=0;i<f_list_.size();i++)
			  {
				  if (netpath_.CheckPriv(f_list_[i],false))
					  result.push_back(f_list_[i]);
			  }


			  serial_out(archive_out,result_message);
			  serial_out(archive_out,result);
		  }
		  break;
		  case GETPATHINFO:
		  {
			  filepath_list list_org;
			  filepath_list list_;
			  archive_in >> list_org;

			  for (unsigned int i=0;i<list_org.size();i++)
			  {
				  list_.push_back(Transfer_Format(list_org[i]));
			  }

			  fileinfo_list result;
			  
			  unsigned int i;
			  for (i=0;i<list_.size();i++)
			  {

				  log.WriteCommand(CurrentUser.stUserID,GETPATHINFO,list_[i]);

				  fileinfo fileinfo_;
				  netpath_.GetFileInfo(list_[i],fileinfo_);

				  if (netpath_.CheckPriv(fileinfo_,false))
					  result.push_back(fileinfo_);
			  }
			  serial_out(archive_out,result_message);
			  serial_out(archive_out,result);
		  }
		  break;
		  case SEARCHCOMMENT:
		  {
			  std::string stComment;
			  archive_in >> stComment;

			  comment_list comment_list_;
			  
			  log.WriteCommand(CurrentUser.stUserID,SEARCHCOMMENT,stComment);

			  netpath_.FindComment_by_Comment(stComment,comment_list_,false);

			  filepath_list filepath_list_;
			  fileinfo_list result;
			  for (unsigned int i=0;i<comment_list_.size();i++)
			  {
				  bool bExist=false;
				  for (unsigned int j=0;j<filepath_list_.size();j++)
				  {
					  if (strcmp(comment_list_[i].GetNetPath().c_str(),filepath_list_[j].c_str())==0)
					  {bExist=true;break;}
				  }
				  if (!bExist)
				  {
					  fileinfo temp;
					  netpath_.GetFileInfo(comment_list_[i].GetNetPath(),temp);
					  result.push_back(temp);
				  }
			  }
			  if ((int)comment_list_.size()>config_.GetInt(MAX_SEARCH_RESULT_NUMBER))
			  {result_message.Add(TOO_MANY_RESULTS,result.size(),"");break;}

			  serial_out(archive_out,result_message);
			  serial_out(archive_out,result);
		  }
		  break;
		  case GETCOMMENT:
		  {
			  std::string stNetPath;
			  std::string stNetPath_org;
			  archive_in >> stNetPath_org;
			  stNetPath=Transfer_Format(stNetPath_org);

			  comment_list result;
			  
			  log.WriteCommand(CurrentUser.stUserID,GETCOMMENT,stNetPath);

			  // Priv Check
			  if (!check_netpath_priv(stNetPath,false))
				{result_message.Add(NO_PRIV);break;}

			  fileinfo fileinfo_;
			  netpath_.GetFileInfo(stNetPath,fileinfo_);

			  if (netpath_.CheckPriv(fileinfo_,false)==false)
			  {
				  result_message.Add(NO_PRIV);break;
			  }

			  netpath_.FindComment_by_Path(stNetPath,result,true);

			  serial_out(archive_out,result_message);
			  serial_out(archive_out,result);
		  }
		  break;
		  case SETCOMMENT:
		  {
			  comment_list comment_list_from_,comment_list_to_;
			  archive_in >> comment_list_from_ >> comment_list_to_;

			  if (comment_list_from_.size()!=comment_list_to_.size())
			  {
				  result_message.Add(INVALID_PARAM);break;
			  }

			  for (unsigned int i=0;i<comment_list_from_.size();i++)
			  {
				  log.WriteCommand(CurrentUser.stUserID,SETCOMMENT,comment_list_from_[i].sql_set_values(),comment_list_to_[i].sql_set_values());
			  }

			  for (unsigned int i=0;i<comment_list_from_.size();i++)
			  {
				  // Priv Check
				  if (check_netpath_priv(comment_list_from_[i].stNetPath,true))
				  {
					  if (netpath_.IsExists(comment_list_from_[i]) 
						  && strcmp(comment_list_from_[i].stNetPath.c_str(),"")!=0)
					{
						if (strcmp(comment_list_to_[i].stDetail.c_str(),"")==0)
						{
							// DELETE
							netpath_.Delete(comment_list_from_[i]);
						}
						else
						{
							  // UPDATE
							  if (!netpath_.Update(comment_list_from_[i],comment_list_to_[i]))
								  result_message.Add(SQL_ERROR,0,comment_list_from_[i].stNetPath);
						}
					}
					else
					{
						if (strcmp(comment_list_to_[i].stDetail.c_str(),"")!=0)
						{
						  // INSERT
						  if (!netpath_.Insert(comment_list_to_[i]))
							  result_message.Add(SQL_ERROR,0,comment_list_to_[i].stNetPath);
						}
					}
				  }
			  }

			serial_out(archive_out,result_message);
			serial_out(archive_out,blank_);
		  }
		  break;
		  case SERVERSTOP:
		  {

		  }
		  break;
		  case SERVERSTART:
		  {

		  }
		  break;
		  case SERVERQUIT:
			  {
				  log.WriteCommand(CurrentUser.stUserID,command_.order_code,"");

				  if (!config_.Compare(SUPERADMIN_ID,CurrentUser.stUserID))
				  {
					  result_message.Add(NO_PRIV);
					  break;
				  }
				  log << _T("### Server Quit ###") << log.endl(); 
				  connection_manager_.stop_all();
				  exit(1);
			  }
			  break;
		  case CHECKSQLINFO:
			  {
			  }
			  break;
		  case CHECKTHUMBNAIL:
			  {
			  }
			  break;

		  case RELOADCONFIG:
		  {
			  log.WriteCommand(CurrentUser.stUserID,RELOADCONFIG,"");

//				  if (config_.GetInt(MULTIUSER_SUPPORT) && 

			  if (!config_.Compare(SUPERADMIN_ID,CurrentUser.stUserID))
			  {
				  result_message.Add(NO_PRIV);
				  break;
			  }
			  config_.load();
			serial_out(archive_out,result_message);
			serial_out(archive_out,blank_);
		  }
		  break;
		  case SETCONFIG:
		  {
			  archive_in >> config_;

			  log.WriteCommand(CurrentUser.stUserID,SETCONFIG,"");

//			  if (config_.GetInt(MULTIUSER_SUPPORT) && 
			  if (!config_.Compare(SUPERADMIN_ID,CurrentUser.stUserID))
			  {
				  result_message.Add(NO_PRIV);
				  break;
			  }

		  config_.save();
			serial_out(archive_out,result_message);
			serial_out(archive_out,blank_);
		  }
		  break;
		  case RELOADLIST:
		  {

		  }
		  break;
		  case ADDUSER:
		  {

		  }
		  break;
		  default:
		  {
			  result_message.Add(INVALID_COMMAND);

			  log.WriteError(result_message);
			  _tcout << _T("### INVALID COMMAND ###");
		  }
		  break;
		}
	}

	}
	catch (CppSQLite3Exception& e)
	{
//		log << log.endl();

		connection_basic::free_InboundBuffer();
		if (fp!=NULL) {fclose(fp);fp=NULL;}

		result_message.Add(SQL_ERROR,e.errorCode(),e.errorMessage());
		process_error(result_message);
	}
    catch (std::exception& e)
    {
        // Unable to decode data.
//		log << log.endl();

		connection_basic::free_InboundBuffer();
		if (fp!=NULL) {fclose(fp);fp=NULL;}

		result_message.Add(DECODING_DATA,0,e.what());
		process_error(result_message);
	}

	if (result_message.CheckError())
		serial_out(archive_out,result_message);

	connection_basic::OutboundBuffer()= archive_stream_out.str();

	if (command_.order_code==LOGIN && result_message.CheckError())
	{
		connection_basic::async_write(boost::bind(&connection::handle_logoff, this),
		boost::posix_time::seconds(STREAMING_TIMEOUT));
		return;
	}


	if (bFileTransfer)
	{
		connection_basic::async_write(boost::bind(&connection::handle_filetransfer, this,
		  boost::asio::placeholders::error,
		  fp,
		  stLocalPath,lFileSize),
		  boost::posix_time::seconds(STREAMING_TIMEOUT));
	}
	else
	{
		connection_basic::async_write(boost::bind(&connection::handle_waiting_order, this,boost::asio::placeholders::error),
		boost::posix_time::seconds(STREAMING_TIMEOUT));
	}
  }

  void connection::handle_logoff()
  {
	  connection_manager_.stop(shared_from_this());
  }

  
  void connection::handle_waiting_order(const boost::system::error_code& e)
  {
	if (e) {process_socket_error(e);return;}
	
	handle_waiting_order();
  }


  void connection::handle_waiting_order()
  {
#ifdef _DEBUG
	  log<<_T("connection::handle_waiting_order\n");
#endif

	  clear();

	  connection_basic::async_read(boost::bind(&connection::handle_execute_order,this,boost::asio::placeholders::error),
		  boost::posix_time::hours(ORDER_WAITING_TIMEOUT));
  }

  void connection::handle_filetransfer(const boost::system::error_code& e,FILE* fp,const tstring& stLocalPath,__int64 lFileSize)
{
	if (e) 
	{
		process_socket_error(e);
		if (fp!=NULL) {fclose(fp);fp=NULL;}
		return;
	}

#ifdef _DEBUG
	  log<<_T("connection::handle_filetransfer\n");
#endif

	switch (command_.order_code)
	{

		case UPLOADFILE:
			{
				connection_basic::async_download_file(fp,
					stLocalPath,
					lFileSize,
					boost::bind(&connection::handle_uploadprocess, this,boost::asio::placeholders::error,stLocalPath));
			}
			break;
		case THUMB_UPLOADFILE:
			{
				connection_basic::async_download_file(fp,
					stLocalPath,
					lFileSize,
					boost::bind(&connection::handle_waiting_order, this,boost::asio::placeholders::error));
			}
			break;

		case UPDATE:
		case DOWNLOADFILE:
		case THUMB_DOWNLOADFILE:
			{
				connection_basic::async_upload_file(fp,
					stLocalPath,
					lFileSize,
					boost::bind(&connection::handle_waiting_order, this,boost::asio::placeholders::error));
			}
			break;

	}

}
void connection::handle_uploadprocess(const boost::system::error_code& e,const tstring& stLocalPath)
{
	if (e) 
	{
		process_socket_error(e);
		return;
	}

	  // update sql

	error_message result_message;
	try
	{
	  fileinfo fileinfo_=netpath_.CreateFileInfoL(stLocalPath);
	  netpath_.LoadMetatag(fileinfo_);
	  netpath_.Insert(fileinfo_);
	}
	catch (CppSQLite3Exception& e)
	{
		result_message.Add(SQL_ERROR,e.errorCode(),e.errorMessage());
		process_error(result_message);
	}
    catch (std::exception& e)
    {
		result_message.Add(DECODING_DATA,0,e.what());
		process_error(result_message);
	}

	handle_waiting_order();
}
