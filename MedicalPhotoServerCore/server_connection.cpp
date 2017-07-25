#include "stdafx.h"
#include "server_connection.h"

#include "async_connection_manager.hpp"

void server_connection::ExecuteOrder(boost::archive::text_iarchive& archive_in
									 ,boost::archive::text_oarchive& archive_out)
{
      archive_in >> command_;
#ifdef _DEBUG
	  log << _T("Command (") << command_.order_code << _T(") by ") << MCodeChanger::_CCL(CurrentUser.stUserID) << log.endl();
#endif 
	  if (command_.order_code!=LOGIN && bLogin==false)
	  {
		  result_message.Add(NOT_LOGON);
		  serial_out(archive_out,result_message);
		  serial_out(archive_out,blank_);
	  }
	  else
	  {
		  switch (command_.order_code)
		  {
		  case IDLESIGNAL:
			  {
#ifdef _DEBUG
				  log.WriteCommand(stIPAddress,IDLESIGNAL,"");
#endif
				  serial_out(archive_out,result_message);
				  serial_out(archive_out,blank_);
			  }
			  break;
		  case LOGIN:
		  {
			  archive_in >> CurrentUser.stUserID >> CurrentUser.stPasswd;

			  if (!config_.GetInt(MULTIUSER_SUPPORT))
				  CurrentUser.stUserID=config_.Get(SUPERADMIN_ID);

			  if (config_.GetInt(MULTIUSER_SUPPORT))
				  log.WriteCommand(stIPAddress,LOGIN,CurrentUser.stUserID);
			  else
				  log.WriteCommand(stIPAddress,LOGIN);

			  if (config_.GetInt(MULTIUSER_SUPPORT))
			  {
					boost::format fmt("SELECT * FROM %s WHERE %s='%s' AND passwd='%s';");
					fmt 
						% CurrentUser.get_tablename()
						% CurrentUser.get_primary()
						% sql_helper::sql_escape(CurrentUser.stUserID)  // ID
						% sql_helper::sql_escape(CurrentUser.stPasswd); // PASSWD

					std::string kk=fmt.str();

					CppSQLite3Table t=sql.getTable(fmt.str().c_str());

				  if (t.numRows()!=1) 
					{
						result_message.Add(PASSWORD_MISMATCH);

						boost::format fmt("SELECT * FROM %s WHERE %s='%s';");
						fmt 
							% CurrentUser.get_tablename()
							% CurrentUser.get_primary()
							% sql_helper::sql_escape(CurrentUser.stUserID);  // ID
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

			  log.WriteCommand(stIPAddress,PASSWD_CHANGE,stNewID,stNewPass);

			boost::format fmt("UPDATE %s SET %s='%s',passwd='%s' WHERE %s='%s' AND passwd='%s';");
			fmt 
				% CurrentUser.get_tablename()
				% CurrentUser.get_primary()

				% sql_helper::sql_escape(stNewID)  // ID
				% sql_helper::sql_escape(stNewPass)  // PASSWD

				% CurrentUser.get_primary()

				% sql_helper::sql_escape(CurrentUser.stUserID)
				% sql_helper::sql_escape(CurrentUser.stPasswd);

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

 //			  log.WriteCommand(stIPAddress,GETUSERDX,stDiagnosis);
//			  log<<_T("GETUSERDX : ") << MCodeChanger::_CCL(stDiagnosis);


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

  			  log.WriteCommand(stIPAddress,SETUSERDX,diagnosis_from_.sql_set_values(),diagnosis_to_.sql_set_values());

			  if (sql.IsExists(diagnosis_from_))
			  {
				  if (diagnosis_to_.isempty())
				  {
					  if (!sql.Delete(diagnosis_from_))
						  result_message.Add(SQL_ERROR,0,diagnosis_from_.get_unique());
				  }
				  else
				  {
					  // UPDATE
					  if (diagnosis_from_==diagnosis_to_)
					  {
					  }
					  else
					  {
						  if (sql.IsExists(diagnosis_to_))
						  {
							  if (!sql.Delete(diagnosis_from_))
								  result_message.Add(SQL_ERROR,0,diagnosis_from_.get_unique());
						  }
						  else
						  {
							  if (!sql.Update(diagnosis_from_,diagnosis_to_))
								  result_message.Add(SQL_ERROR,0,diagnosis_from_.get_unique());
						  }

					  }
				  }
			  }
			  else
			  {
				  if (!sql.IsExists(diagnosis_to_))
				  {
					  // INSERT
					  if (!sql.Insert(diagnosis_to_))
						  result_message.Add(SQL_ERROR,0,diagnosis_to_.get_unique());
				  }
			  }

			serial_out(archive_out,result_message);
			serial_out(archive_out,blank_);

		  }
		  break;
		  case UPDATEPREVUSERDX:
		  {
			  dx_list dx_from,dx_to;
			  archive_in >> dx_from >> dx_to ;

  			  log.WriteCommand(stIPAddress,UPDATEPREVUSERDX);

			  netpath_.UpdateDiagnosis(dx_from,dx_to);

			  serial_out(archive_out,result_message);
			  serial_out(archive_out,blank_);
		  }
		  break;


		  case GETDX:
		  {
			  std::string stDiagnosis;
			  archive_in >> stDiagnosis ;

  			  log.WriteCommand(stIPAddress,GETDX,stDiagnosis);

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

  			  log.WriteCommand(stIPAddress,UPLOADFILE,stNetPath,lFileSize);

			  _tpath stPath(netpath_.Net_Local(stNetPath));

			  if (MFile::Exists(stPath))
			  {
				  fileinfo_list f_list_;
				  netpath_.FindFile(fileinfo::get_primary(),f_list_,true);
				  if (f_list_.size()>0)
				  {
					  result_message.Add(FILE_DUPLICATE);break;
				  }
				  else
				  {
					  _tpath path=stPath;

						int iRenameCount=0;

						tstring csDumy=Utility::GetNumericName(iRenameCount,path.c_str());
						iRenameCount++;

						while (MFile::ExistsL(csDumy)
							|| netpath_.IsExistsFromPrimary(MCodeChanger::_CCU(csDumy),fileinfo()))
						{
							csDumy=Utility::GetNumericName(iRenameCount,path.c_str());
							iRenameCount++;
						}
						std::string final_path=MCodeChanger::_CCU(csDumy);

//						netpath_.CreateFile(stNetPath,CurrentUser.stUserID,true);

						//reset name
						tstring stLocalName=MCodeChanger::_CCL(final_path);
						stNetPath=netpath_.Local_Net(stLocalName);
						stPath=_tpath(stLocalName);
				  }
			  }

			if (lFileSize<0)
				{result_message.Add(SIZE_ERROR);break;}

			if (!netpath_.CheckRootPriv(stPath,true))
				{result_message.Add(NO_PRIV);break;}

			stLocalPath=stPath.c_str();

			netpath_.CreateFolder(netpath_.Local_Net(stPath.branch_path().c_str())
				,CurrentUser.stUserID);

			net_watcher_.Add(WATCH_CREATE,stLocalPath);
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

//  			  log.WriteCommand(stIPAddress,THUMB_UPLOADFILE,stNetPath,lFileSize);

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

  			  log.WriteCommand(stIPAddress,DELETEFILE,stNetPath);

			  _tpath stPath(netpath_.Net_Local(stNetPath));

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

  			  log.WriteCommand(stIPAddress,RENAMEFOLDER,from,to);

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

  			  log.WriteCommand(stIPAddress,RENAMEFILE,from,to);

			  netpath_.MoveFile(from,to);

			serial_out(archive_out,result_message);
			serial_out(archive_out,blank_);
		  }
		  break;
		  case CREATEFOLDER:
		  {
			  std::string stNetPath;
			  std::string stNetPath_org;
			  archive_in >> stNetPath_org ;

//			  stRootNetPath=Transfer_Format(stRootNetPath_org);
			  stNetPath=Transfer_Format(stNetPath_org);

  			  log.WriteCommand(stIPAddress,CREATEFOLDER,stNetPath);

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

  			  log.WriteCommand(stIPAddress,CREATEFOLDER_AUTO,stRootNetPath);

			  _tpath root_path=_tpath(MCodeChanger::_CCL(stRootNetPath));
			  _tpath path= Utility::refinepath(root_path / Utility::GetToday(iDateType));

				int iRenameCount=0;

				tstring csDumy=Utility::GetNumericName(iRenameCount,path.c_str());
				iRenameCount++;

				while (MFile::ExistsL(csDumy)
					|| netpath_.IsExistsFromPrimary(MCodeChanger::_CCU(csDumy),fileinfo()))
				{
					csDumy=Utility::GetNumericName(iRenameCount,path.c_str());
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

  			  log.WriteCommand(stIPAddress,DELETEFOLDER,stNetPath);

			  netpath_.DeleteFolder(stNetPath);

			serial_out(archive_out,result_message);
			serial_out(archive_out,blank_);
		  }
		  break;
		  case IMAGE_ROTATE:
		  {
			  if (config_.GetInt(SAVE_ROTATEIMAGE))
			  {
				  std::string stNetPath;
				  int iRotate;
				  std::string stNetPath_org;
				  archive_in >> stNetPath_org >> iRotate ;
				  stNetPath=Transfer_Format(stNetPath_org);

  				  log.WriteCommand(stIPAddress,IMAGE_ROTATE,stNetPath,iRotate);

				  netpath_.Image_Rotate(stNetPath,iRotate);
			  }

//			  netpath_.DeleteFolder(stNetPath);
			  serial_out(archive_out,result_message);
			  serial_out(archive_out,blank_);
		  }
		  break;
		  case SETPATHINFO:
		  {
			  connection_basic::InboundBuffer();
			  fileinfo fileinfo_from_,fileinfo_to_;
			  archive_in >> fileinfo_from_ >> fileinfo_to_;

#ifdef _DEBUG
			  log.WriteCommand(stIPAddress,SETPATHINFO
				  ,fileinfo_from_.sql_set_values()
				  ,fileinfo_to_.sql_set_values()
				  );
#endif
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

#ifdef _DEBUG
  			  log.WriteCommand(stIPAddress,DOWNLOADFILE,stNetPath);
#endif
			  if (!MFile::Exists(stPath))
				{result_message.Add(FILE_NOT_EXIST);break;}

			  stLocalPath=stPath.c_str();
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
#ifdef _DEBUG
				  log.WriteCommand(stIPAddress,GET_VERSIONFILE,"","");
#endif
				  serial_out(archive_out,result_message);
				  serial_out(archive_out,config_.version_);
			  }
			  break;
		  case UPDATE:
		  {
			  std::string stVersion;
			  update_struct update_struct_; 
			  archive_in >> update_struct_>> stVersion ;

			  log.WriteCommand(stIPAddress,UPDATE,MCodeChanger::_CCU(MFile::GetFileNameL(MCodeChanger::_CCL(config_.version_.Get(update_struct_.iAppCode,update_struct_.iSubCode)))));

			  if (!config_.version_.NeedUpdate(update_struct_.iAppCode,stVersion))
			  {
				  // No Update now
//				  log << _T("No Update\n");
				  result_message.Add(NO_UPDATE);break;
			  }

			  stLocalPath=MCodeChanger::_CCL(config_.version_.Get(update_struct_.iAppCode,update_struct_.iSubCode));

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
#ifdef _DEBUG
  			  log.WriteCommand(stIPAddress,GETFOLDERLIST,stNetPath);
#endif
			  _tpath stPath(netpath_.Net_Local(stNetPath));

			  path_list pfound;

			  fileinfo_list result;
			  fileinfo_list temp_list;

			  netpath_.FindbyDir(stNetPath,result,true,bFileOnly);

			  serial_out(archive_out,result_message);
			  serial_out(archive_out,result);
		  }
		  break;
		  case GETVOLLIST:
		  {
#ifdef _DEBUG
			  log.WriteCommand(stIPAddress,GETVOLLIST,"");
#endif
			  volname_list vol_list_;

			  for (int i=0;i<netpath_.GetSize();i++)
			  {
				  vol_list_.push_back(MCodeChanger::_CCU(netpath_.Vol(i).GetVolName()));
			  }

			  serial_out(archive_out,result_message);
			  serial_out(archive_out,vol_list_);
		  }
		  break;

		  case SEARCH_QUERY:
		  {
			  std::string stQuery;
			  std::vector<bool> bMask;
			  archive_in >> stQuery >> bMask;
#ifdef _DEBUG
  			  log.WriteCommand(stIPAddress,command_.order_code,stQuery,"");
#endif
//			  unsigned int i;

			  fileinfo_list f_list_;
			  
			  netpath_.FindFile_byQuery(stQuery,bMask,f_list_);

			  if ((int)f_list_.size()>config_.GetInt(MAX_SEARCH_RESULT_NUMBER))
			  {
				  boost::format fmt("Too many results [ %s ]. It should be less than %s as defined in s_config.txt");fmt % f_list_.size() % config_.GetInt(MAX_SEARCH_RESULT_NUMBER);
				  result_message.Add(TOO_MANY_RESULTS,TOO_MANY_RESULTS,fmt.str());break;
			  }
/*
			  fileinfo_list result;
			  for (i=0;i<f_list_.size();i++)
			  {
				  if (netpath_.CheckPriv(f_list_[i],false))
					  result.push_back(f_list_[i]);
			  }
*/
			  serial_out(archive_out,result_message);
			  serial_out(archive_out,f_list_);

		  }
		  break;
		  case SEARCHFILE_EXT:
		  {
			  std::vector<std::string> Keyword_list;
			  std::vector<std::string> Field_list;
			  archive_in >> Field_list >> Keyword_list;
#ifdef _DEBUG
  			  log.WriteCommand(stIPAddress,command_.order_code,"","");
#endif
//			  unsigned int i;

			  fileinfo_list f_list_;
			  
			  netpath_.FindFile(Field_list,Keyword_list,f_list_,false);

			  if ((int)f_list_.size()>config_.GetInt(MAX_SEARCH_RESULT_NUMBER))
			  {
				  boost::format fmt("Too many results [ %s ]. It should be less than %s as defined in s_config.txt");fmt % f_list_.size() % config_.GetInt(MAX_SEARCH_RESULT_NUMBER);
				  result_message.Add(TOO_MANY_RESULTS,TOO_MANY_RESULTS,fmt.str());break;
			  }

/*			  fileinfo_list result;
			  for (i=0;i<f_list_.size();i++)
			  {
				  if (netpath_.CheckPriv(f_list_[i],false))
					  result.push_back(f_list_[i]);
			  }
*/
			  serial_out(archive_out,result_message);
			  serial_out(archive_out,f_list_);

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

#ifdef _DEBUG
  			  log.WriteCommand(stIPAddress,command_.order_code,stKeyword,stField);
#endif

//			  unsigned int i;

			  fileinfo_list f_list_;
			  
			  if (command_.order_code==SEARCH)
				  netpath_.FindFile(stKeyword,f_list_,false);
			  if (command_.order_code==SEARCH_EXACT)
				  netpath_.FindFile(stKeyword,f_list_,true);
			  if (command_.order_code==SEARCH_WITH_PATH)
				  netpath_.FindPath(stKeyword,f_list_,false);
			  if (command_.order_code==SEARCH_WITH_PATH_EXACT)
				  netpath_.FindPath(stKeyword,f_list_,true);

			  if (strcmp(stKeyword.c_str(),fileinfo::get_primary())==0)
			  {
				  for (unsigned int i=(f_list_.size()-1);i>=0;i--)
				  {
					  tstring stPath=netpath_.Net_Local(f_list_[i].GetNetPath());
					  if (!MFile::ExistsL(stPath))
						  f_list_.erase(f_list_.begin()+i);
				  }
			  }

			  if ((int)f_list_.size()>config_.GetInt(MAX_SEARCH_RESULT_NUMBER))
			  {
				  boost::format fmt("Too many results [ %s ]. It should be less than %s as defined in s_config.txt");fmt % f_list_.size() % config_.GetInt(MAX_SEARCH_RESULT_NUMBER);
				  result_message.Add(TOO_MANY_RESULTS,TOO_MANY_RESULTS,fmt.str());break;
			  }

/*			  fileinfo_list result;
			  for (i=0;i<f_list_.size();i++)
			  {
				  if (netpath_.CheckPriv(f_list_[i],false))
					  result.push_back(f_list_[i]);
			  }
*/

			  serial_out(archive_out,result_message);
			  serial_out(archive_out,f_list_);
		  }
		  break;
		  case SEARCH_WITH_DATE:
		  {
			  std::string stFrom;
			  std::string stTo;
			  archive_in >> stFrom >> stTo;

#ifdef _DEBUG
			  log.WriteCommand(stIPAddress,command_.order_code,stFrom,stTo);
#endif

//			  unsigned int i;

			  fileinfo_list f_list_;
			  
			  netpath_.FindFile_by_Date(stFrom,stTo,f_list_);

			  if ((int)f_list_.size()>config_.GetInt(MAX_REPORT_RESULT_NUMBER))
			  {
				  boost::format fmt("Too many results [ %s ]. It should be less than %s as defined in s_config.txt");fmt % f_list_.size() % config_.GetInt(MAX_REPORT_RESULT_NUMBER);

				  result_message.Add(TOO_MANY_RESULTS,TOO_MANY_RESULTS,fmt.str());break;
			  }

/*			  fileinfo_list result;
			  for (i=0;i<f_list_.size();i++)
			  {
				  if (netpath_.CheckPriv(f_list_[i],false))
					  result.push_back(f_list_[i]);
			  }
*/
			  serial_out(archive_out,result_message);
			  serial_out(archive_out,f_list_);

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
			  
			  for (unsigned int i=0;i<list_.size();i++)
			  {
//				  log.WriteCommand(stIPAddress,GETPATHINFO,list_[i]);

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
			  
#ifdef _DEBUG
			  log.WriteCommand(stIPAddress,SEARCHCOMMENT,stComment);
#endif
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
			  {
				  boost::format fmt("Too many results [ %s ]. It should be less than %s as defined in s_config.txt");fmt % result.size() % config_.GetInt(MAX_SEARCH_RESULT_NUMBER);

				  result_message.Add(TOO_MANY_RESULTS,TOO_MANY_RESULTS,fmt.str());break;
			  }

			  serial_out(archive_out,result_message);
			  serial_out(archive_out,result);
		  }
		  break;
		  case GETCOMMENT:
		  {
			  std::vector<std::string> stNetPath_list;
			  archive_in >> stNetPath_list;
			  Transfer_Format(stNetPath_list);

			  comment_list result;

/* performance problem			  
			  for (unsigned int i=0;i<stNetPath_list.size();i++)
			  {
				  log.WriteCommand(stIPAddress,GETCOMMENT,stNetPath_list[i]);
			  }
*/


/*			  fileinfo fileinfo_;
			  netpath_.GetFileInfo(stNetPath,fileinfo_);

			  if (netpath_.CheckPriv(fileinfo_,false)==false)
			  {
				  result_message.Add(NO_PRIV);break;
			  }
*/
			  netpath_.FindComment_by_Path(stNetPath_list,result,true);

			  serial_out(archive_out,result_message);
			  serial_out(archive_out,result);

			  /*
			  std::string stNetPath;
			  std::string stNetPath_org;
			  archive_in >> stNetPath_org;
			  stNetPath=Transfer_Format(stNetPath_org);

			  comment_list result;
			  
			  log.WriteCommand(stIPAddress,GETCOMMENT,stNetPath);

			  fileinfo fileinfo_;
			  netpath_.GetFileInfo(stNetPath,fileinfo_);

			  if (netpath_.CheckPriv(fileinfo_,false)==false)
			  {
				  result_message.Add(NO_PRIV);break;
			  }

			  netpath_.FindComment_by_Path(stNetPath,result,true);

			  serial_out(archive_out,result_message);
			  serial_out(archive_out,result);
			  */
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
				  log.WriteCommand(stIPAddress,SETCOMMENT,comment_list_from_[i].sql_set_values(),comment_list_to_[i].sql_set_values());
			  }

			  for (unsigned int i=0;i<comment_list_from_.size();i++)
			  {
//				  // Priv Check
//				  if (check_netpath_priv(comment_list_from_[i].stNetPath,true))
//				  {
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
//			  }
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
				  log.WriteCommand(stIPAddress,command_.order_code,"");

				  if (!config_.Compare(SUPERADMIN_ID,CurrentUser.stUserID))
				  {
					  result_message.Add(NO_PRIV);
					  break;
				  }
				  log << _T("### Server Quit ###") << log.endl(); 
				  async_connection_manager_.stop_all();
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
			  log.WriteCommand(stIPAddress,RELOADCONFIG,"");

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

			  log.WriteCommand(stIPAddress,SETCONFIG,"");

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
/*
void server_connection::PostExecuteOrder()
{
	switch (command_.order_code)
	{
		case LOGIN:
		{
			std::ostringstream archive_stream_out;
			boost::archive::text_oarchive archive_out(archive_stream_out);

			command cmd_;
			cmd_.order_code=CLIENTSTOP;
			serial_out(archive_out,cmd_);

			connection_basic::OutboundBuffer()= archive_stream_out.str();
			connection_basic::async_write(boost::bind(&async_connection::handle_postexecute_order, this,boost::asio::placeholders::error),


		}
		break;
	}
}
*/
void server_connection::process_socket_error(const boost::system::error_code& e)
{
	if (e!=boost::asio::error::operation_aborted)
	{
		if (e.value()==2)
		{
			if (bLogin)
			log << _T("[Disconnect] ") 
//				<< _T("[ ")
//				<< MCodeChanger::_CCL(CurrentUser.stUserID)
//				<< _T(" / ")
				<< MCodeChanger::_CCL(socket().remote_endpoint().address().to_string())
//				<< _T(" ]")
				<< log.endl();

			async_connection_manager_.stop(shared_from_this());
		}
		else
		{
			error_message err_;
			err_.Add(SOC_ERROR,e.value(),e.message());
			process_error(err_);
			async_connection_manager_.stop(shared_from_this());
		}
	}
}

void server_connection::PostExecuteOrder()
{
/*	switch (command_.order_code)
	{
		case LOGIN:
		{
			SendExit();
		}
		break;
	}
*/
}
