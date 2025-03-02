// ProgressDialog.cpp : implementation file
//

#include "stdafx.h"
#include "WhriaView.h"
#include "ProgressDialog.h"
#include <boost/thread/mutex.hpp>

#include "../share/json.hpp"
struct JsonInfo {
	std::string Filename;
	std::string Name;
	std::string ID;
};

// CProgressDialog dialog

IMPLEMENT_DYNAMIC(CProgressDialog, CDialog)

CProgressDialog::CProgressDialog(CWhriaCacheClient& w,client_config& c,CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDialog::IDD, pParent)
	,WhriaClient(w)
	,config_(c)
	,bStopThread(false)
	,bStartThread(false)
{

}

CProgressDialog::~CProgressDialog()
{
}


void CProgressDialog::UpdateApp(version_checker& version_,version_checker& version_new_,bool& bUpdateResult,bool& bSucceedUpdate)
{
	boost::thread BuildThread(boost::bind(&CProgressDialog::UpdateAppThread,this
		,boost::ref(version_)
		,boost::ref(version_new_)
		,boost::ref(bUpdateResult)
		,boost::ref(bSucceedUpdate)

));
}


void CProgressDialog::DownloadFolder(const std::string& stNetPathFrom,const tstring& stFolderTo)
{
	boost::thread BuildThread(boost::bind(&CProgressDialog::DownloadFolderThread,this
		,stNetPathFrom,stFolderTo));
}
void CProgressDialog::DownloadFile(const fileinfo_list& f_list,const tstring& stFolderTo)
{
	boost::thread BuildThread(boost::bind(&CProgressDialog::DownloadFileThread,this
		,f_list,stFolderTo));
}
void CProgressDialog::ModifyPath(fileinfo_list& f_list,CToolTipListCtrl& m_PictureList,fileinfo& fileinfo_update)
{
	
	boost::thread BuildThread(boost::bind(&CProgressDialog::ModifyPathThread,this
		,boost::ref(f_list)
		,boost::ref(m_PictureList)
		,boost::ref(fileinfo_update)));

}


void CProgressDialog::UpdateAppThread(version_checker& version_,version_checker& version_new_,bool& bUpdateResult,bool& bSucceedUpdate)
{
	while (!bStartThread)
	{
		Utility::sleep(100);
	}
	boost::mutex::scoped_lock lock(thread_mutex);


	try
	{
		m_Progress.SetRange(0,4);
		m_Progress.SetPos(0);
		m_Progress.SetWindowText(_T("Update client ( 0/4 )"));

//		bool bSucceedUpdate=true;
		bool bNeedRestart=false;
//		bool bUpdateDone=false;
	//		int type = (false) ? MOVEFILE_DELAY_UNTIL_REBOOT : MOVEFILE_COPY_ALLOWED;

		if (version_new_.NeedUpdate(VERSION_FILE,version_.Get(VERSION_FILE_VERSION)))
		{
//			bUpdateDone=true;

			CString output=_T("Updating... : ");
			output+=MFile::GetFileNameL(MCodeChanger::_CCL(version_.Get(VERSION_FILE))).c_str();
			m_Progress.SetWindowText(output);

			update_struct update_struct_;
			update_struct_.iAppCode=VERSION_FILE;
			update_struct_.iSubCode=0;
			WhriaClient.update(update_struct_
				,version_.Get(VERSION_FILE)
				,version_.Get(VERSION_FILE_VERSION));

			bSucceedUpdate&=Switch(
				MCodeChanger::_CCL(version_.Get(VERSION_FILE)).c_str()
				, version_checker::GetTemp(version_.Get(VERSION_FILE)).c_str());

		}

		if (bStopThread) 
		{
			bSucceedUpdate=false;
			Utility::sleep(100);
			PostMessage(WM_CLOSE,0,0);
			return;
		}
		m_Progress.SetPos(1);
		m_Progress.SetWindowText(_T("Update client ( 1/4 )"));

		if (config_.server_config.version_.NeedUpdate(CLIENT_APP_NAME,version_.Get(CLIENT_VERSION)))
		{
			bNeedRestart=true;

			param_list param_list_;
			config_.server_config.version_.SplitParams(CLIENT_APP_NAME,param_list_);

			for (unsigned int i=0;i<param_list_.size();i++)
			{
				CString output=_T("Updating... : ");
				output+=MFile::GetFileNameL(MCodeChanger::_CCL(version_.Get(CLIENT_APP_NAME,i))).c_str();
				m_Progress.SetWindowText(output);

				update_struct update_struct_;
				update_struct_.iAppCode=CLIENT_APP_NAME;
				update_struct_.iSubCode=i;
				WhriaClient.update(update_struct_
					,version_.Get(CLIENT_APP_NAME,i)
					,version_.Get(CLIENT_VERSION));

				bSucceedUpdate&=Switch(
					MCodeChanger::_CCL(version_.Get(CLIENT_APP_NAME,i)).c_str()
					, version_checker::GetTemp(version_.Get(CLIENT_APP_NAME,i)).c_str());
			}

		}

		if (bStopThread) 
		{
			bSucceedUpdate=false;
			Utility::sleep(100);
			PostMessage(WM_CLOSE,0,0);
			return;
		}
		m_Progress.SetPos(2);
		m_Progress.SetWindowText(_T("Update client ( 2/4 )"));

		if (config_.server_config.version_.NeedUpdate(ICD10_FILE_NAME,version_.Get(ICD10_FILE_VERSION)))
		{
			param_list param_list_;
			config_.server_config.version_.SplitParams(ICD10_FILE_NAME,param_list_);

			for (unsigned int i=0;i<param_list_.size();i++)
			{
				CString output=_T("Updating... : ");
				output+=MFile::GetFileNameL(MCodeChanger::_CCL(version_.Get(ICD10_FILE_NAME,i))).c_str();
				m_Progress.SetWindowText(output);

				update_struct update_struct_;
				update_struct_.iAppCode=ICD10_FILE_NAME;
				update_struct_.iSubCode=i;
				WhriaClient.update(update_struct_
					,version_.Get(ICD10_FILE_NAME,i)
					,version_.Get(ICD10_FILE_VERSION));

				bSucceedUpdate&=Switch(
					MCodeChanger::_CCL(version_.Get(ICD10_FILE_NAME,i)).c_str()
					, version_checker::GetTemp(version_.Get(ICD10_FILE_NAME,i)).c_str());
			}
		}
		else
		{
			param_list param_list_;
			version_new_.SplitParams(ICD10_FILE_NAME,param_list_);
			for (unsigned int i=0;i<param_list_.size();i++)
			{
				if (!MFile::ExistsL(MCodeChanger::_CCL(param_list_[i]).c_str()) && !param_list_[i].empty())
				{
					CString output=_T("Updating... : ");
					output+=MFile::GetFileNameL(MCodeChanger::_CCL(version_.Get(ICD10_FILE_NAME,i))).c_str();
					m_Progress.SetWindowText(output);

					update_struct update_struct_;
					update_struct_.iAppCode=ICD10_FILE_NAME;
					update_struct_.iSubCode=i;
					WhriaClient.update(update_struct_
						,version_.Get(ICD10_FILE_NAME,i)
						,"0.0.0.0");

					bSucceedUpdate&=Switch(
						MCodeChanger::_CCL(version_.Get(ICD10_FILE_NAME,i)).c_str()
						, version_checker::GetTemp(version_.Get(ICD10_FILE_NAME,i)).c_str());
				}
			}
		}

		if (bStopThread) 
		{
			bSucceedUpdate=false;
			Utility::sleep(100);
			PostMessage(WM_CLOSE,0,0);
			return;
		}
		m_Progress.SetPos(3);
		m_Progress.SetWindowText(_T("Update client ( 3/4 )"));

		if (config_.server_config.version_.NeedUpdate(DATA_FILE_NAME,version_.Get(DATA_FILE_VERSION)))
		{
			param_list param_list_;
			config_.server_config.version_.SplitParams(DATA_FILE_NAME,param_list_);

			for (unsigned int i=0;i<param_list_.size();i++)
			{
				CString output=_T("Updating... : ");
				output+=MFile::GetFileNameL(MCodeChanger::_CCL(version_.Get(DATA_FILE_NAME,i))).c_str();
				m_Progress.SetWindowText(output);

				update_struct update_struct_;
				update_struct_.iAppCode=DATA_FILE_NAME;
				update_struct_.iSubCode=i;
				WhriaClient.update(update_struct_
					,version_.Get(DATA_FILE_NAME,i)
					,version_.Get(DATA_FILE_VERSION));

				bSucceedUpdate&=Switch(
					MCodeChanger::_CCL(version_.Get(DATA_FILE_NAME,i)).c_str()
					, version_checker::GetTemp(version_.Get(DATA_FILE_NAME,i)).c_str());
			}
		}
		else
		{
			param_list param_list_;
			version_new_.SplitParams(DATA_FILE_NAME,param_list_);

			for (unsigned int i=0;i<param_list_.size();i++)
			{
				if (!MFile::ExistsL(MCodeChanger::_CCL(param_list_[i]).c_str()) && !param_list_[i].empty())
				{
					CString output=_T("Updating... : ");
					output+=MFile::GetFileNameL(MCodeChanger::_CCL(version_.Get(DATA_FILE_NAME,i))).c_str();
					m_Progress.SetWindowText(output);

					update_struct update_struct_;
					update_struct_.iAppCode=DATA_FILE_NAME;
					update_struct_.iSubCode=i;
					WhriaClient.update(update_struct_
						,version_.Get(DATA_FILE_NAME,i)
						,"0.0.0.0");

					bSucceedUpdate&=Switch(
						MCodeChanger::_CCL(version_.Get(DATA_FILE_NAME,i)).c_str()
						, version_checker::GetTemp(version_.Get(DATA_FILE_NAME,i)).c_str());
				}
			}
		}

		m_Progress.SetPos(4);
		m_Progress.SetWindowText(_T("Update client ( 4/4 )"));

		if (bNeedRestart)
			bUpdateResult=true;

//		if (bUpdateDone)
		m_Progress.SetWindowText(_T("Update complete."));
	}


	catch (const client_connection::ConnectionEx& err_)
	{
		MessageBeep(MB_ICONHAND);
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
		bSucceedUpdate=false;
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		MessageBeep(MB_ICONHAND);
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
		bSucceedUpdate=false;
	}
	catch(...)
	{
		MessageBeep(MB_ICONHAND);
		bSucceedUpdate=false;
	}


	Utility::sleep(100);
	PostMessage(WM_CLOSE,0,0);
}
void CProgressDialog::ModifyPathThread(fileinfo_list& m_SelectedImage,CToolTipListCtrl& m_PictureList,fileinfo& fileinfo_update)
{
	try
	{
		int iRenameCount=0;

		int iSelectedCount=0;
		int iModifiedCount=0;
		for (int i=0;i<m_PictureList.GetItemCount();i++)
		{
			if (m_PictureList.GetCheck(i))
				iSelectedCount++;
		}

		m_Progress.SetRange(0,iSelectedCount);
		m_Progress.SetPos(0);
		m_Progress.SetWindowText(_T("Start Modifying Files..."));

		for (int i=0;i<m_PictureList.GetItemCount();i++)
		{
			if (m_PictureList.GetCheck(i))
			{
				fileinfo old=m_SelectedImage[i];
				m_SelectedImage[i].Diagnosis=fileinfo_update.Diagnosis;
				m_SelectedImage[i].stPatientName=fileinfo_update.stPatientName;
				m_SelectedImage[i].stPatientID=fileinfo_update.stPatientID;

				
				WhriaClient.setpathinfo(old,m_SelectedImage[i]);

				// filename change

				CString text=_T("Update ");
				text+=MCodeChanger::_CCL(m_SelectedImage[i].stNetPath).c_str();
				m_Progress.SetWindowText(text);
				iModifiedCount++;
				m_Progress.SetPos(iModifiedCount);
 
				if (config_.GetInt(SUBMIT_AUTOCHANGE_FILENAME))
				{
					_tpath oldpath(MCodeChanger::_CCL(m_SelectedImage[i].GetNetPath()));
					_tpath olddir=_tpath(oldpath.parent_path());

					tstring oldext=MFile::GetFileExtL(MCodeChanger::_CCL(m_SelectedImage[i].GetNetPath())).c_str();
					tstring oldname=MFile::GetFileNameL(MCodeChanger::_CCL(m_SelectedImage[i].GetNetPath())).c_str();

					tstring newname;
					if (strcmp(m_SelectedImage[i].stPatientID.c_str(),"")!=0)
					{newname+=MCodeChanger::_CCL(m_SelectedImage[i].stPatientID).c_str();newname+=_T("_");}
					if (strcmp(m_SelectedImage[i].stPatientName.c_str(),"")!=0)
					{newname+=MCodeChanger::_CCL(m_SelectedImage[i].stPatientName).c_str();newname+=_T("_");}

					tstring stDate=Utility::GetDateString(m_SelectedImage[i].Time.date()
						,2);
					if (!stDate.empty())
					{newname+=stDate.c_str();newname+=_T("_");}

					if (strcmp(m_SelectedImage[i].Diagnosis.stDiagnosis.c_str(),"")!=0)
					{newname+=MCodeChanger::_CCL(m_SelectedImage[i].Diagnosis.stDiagnosis).c_str();newname+=_T("_");}
					if (strcmp(m_SelectedImage[i].Diagnosis.stICD10.c_str(),"")!=0)
					{newname+=MCodeChanger::_CCL(m_SelectedImage[i].Diagnosis.stICD10).c_str();newname+=_T("_");}

					if (_tcscmp(newname.c_str(),_T(""))==0)
						newname=oldname;
					else
						boost::algorithm::replace_last(newname,_T("_"),"");

					newname+=oldext;

					newname=Utility::GetFilename(newname);

					_tpath newpath;
					newpath=olddir / newname;
					newpath = Utility::refinepath(newpath);
					
					if (oldpath!=newpath)
					{
						tstring csDumy=newpath.c_str();
						csDumy=Utility::GetNumericName(iRenameCount,newpath.c_str());

						iRenameCount++;

						fileinfo_list result;
						WhriaClient.searchfile_by_path_exact(MCodeChanger::_CCU(csDumy),result);

						while (result.size()!=0)
						{
							csDumy=Utility::GetNumericName(iRenameCount,newpath.c_str());
							iRenameCount++;

							result.clear();

							WhriaClient.searchfile_by_path_exact(MCodeChanger::_CCU(csDumy),result);
						}

						tstring final_path=csDumy;

						WhriaClient.renamefile(m_SelectedImage[i].GetNetPath(),MCodeChanger::_CCU(final_path));


						CString stColumn=Utility::GetDateString(m_SelectedImage[i].Time.date()
							,config_.GetInt(DISPLAY_FOLDER_FORMAT)).c_str();
						if (stColumn!=_T(""))
							stColumn+=_T(" : ");
						stColumn+=MFile::GetFileNamesExtL(final_path).c_str();

						m_PictureList.SetItemText(i,0,stColumn);
						m_PictureList.Invalidate(false);
						m_PictureList.SetItemToolTipText(i,0,final_path.c_str());

						filepath_list path_list;
						fileinfo_list result_temp;
						path_list.push_back(MCodeChanger::_CCU(final_path));
						WhriaClient.getpathinfo(path_list,result_temp);
						if (result_temp.size()==1)
						{
							m_SelectedImage[i]=result_temp[0];
						}
						
	//					DrawListCheck(i);
					}
				}
			}
			if (bStopThread) break;
		}
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
	}
	catch(...)
	{
		MessageBeep(MB_ICONHAND);
	}

	Utility::sleep(100);
	PostMessage(WM_CLOSE,0,0);
}

void CProgressDialog::DownloadFileThread(const fileinfo_list& f_list,const tstring & stDestFolder)
{
	try
	{
		while (!bStartThread)
		{
			Utility::sleep(100);
		}
		boost::mutex::scoped_lock lock(thread_mutex);

		// 파일 전송
		m_Progress.SetRange(0,f_list.size());
		m_Progress.SetPos(0);
		m_Progress.SetWindowText(_T("Start Downloading Files..."));

		for (unsigned int i=0;i<f_list.size();i++)
		{
			unsigned char* buffer=NULL;

			_tpath stDestPath_Org(stDestFolder);

			CString stColumn=MFile::GetFileNameL(MCodeChanger::_CCL(f_list[i].GetNetPath())).c_str();
/*
			CString stDate=Utility::GetDateString(f_list[i].Time.date()
				,config_.GetInt(DISPLAY_FOLDER_FORMAT)).c_str();
			if (stDate!=_T(""))
				stDate=_T("_")+stDate;
			stColumn+=stDate;
			stColumn+=MFile::GetFileExtL(MCodeChanger::_CCL(f_list[i].GetNetPath())).c_str();*/
			stDestPath_Org/=(LPCTSTR)stColumn;

	//		stDestPath_Org/=MFile::GetFileNameL(MCodeChanger::_CCL(f_list[i].GetNetPath()));

			int iRenameCount=0;

			tstring stDestPath=Utility::GetNumericName(iRenameCount,stDestPath_Org.c_str());
			iRenameCount++;
		
			while (MFile::ExistsL(stDestPath))
			{
				stDestPath=Utility::GetNumericName(iRenameCount,stDestPath_Org.c_str());
				iRenameCount++;
			}

			__int64 iFileSize;
			WhriaClient.cmd_download(f_list[i].stNetPath,&buffer,iFileSize);

			MFile::CreateFolder(_tpath(stDestPath).parent_path());
			CFile file;
			// open destination file
			if (file.Open(stDestPath.c_str(), CFile::modeCreate | CFile::modeWrite, NULL) != FALSE)
			{
				file.Write (buffer, iFileSize);
				file.Close();
			}
			delete [] buffer;

			m_Progress.SetPos(i+1);
			CString output;
			output.Format(_T("Downloading.. :   %s   ( %d / %d )"),MCodeChanger::_CCL(f_list[i].GetNetPath()).c_str(),i+1,f_list.size());
			m_Progress.SetWindowText(output);

			if (bStopThread) break;
		}
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
	}
	catch(...)
	{
		MessageBeep(MB_ICONHAND);
	}
	Utility::sleep(100);
	PostMessage(WM_CLOSE,0,0);
}

void CProgressDialog::DownloadFolderThread(const std::string & stNetPathFrom,const tstring & stDestPath)
{
	try
	{
		while (!bStartThread)
		{
			Utility::sleep(100);
		}
		boost::mutex::scoped_lock lock(thread_mutex);

		m_Progress.SetRange(0,1);
		m_Progress.SetPos(0);
		m_Progress.SetWindowText(_T("Start Downloading Files..."));

		fileinfo_list f_list;

		WhriaClient.searchfile_by_path(stNetPathFrom,f_list);
		for (int i=(f_list.size()-1);i>=0;i--)
		{
			if (f_list[i].GetNetPath().find(stNetPathFrom)!=0)
				f_list.erase(f_list.begin()+i);
		}

		m_Progress.SetRange(0,f_list.size());
		m_Progress.SetPos(0);
		for (unsigned int i=0;i<f_list.size();i++)
		{
			std::string stPath=f_list[i].GetNetPath();
			_tpath LocalPath(stDestPath);
			boost::algorithm::replace_first(stPath,stNetPathFrom,"");
			LocalPath /= MCodeChanger::_CCL(stPath);//MFile::GetFileNameL(MCodeChanger::_CCL(f_list[i].GetNetPath()));

			unsigned char* buffer=NULL;

			__int64 iFileSize;
			WhriaClient.cmd_download(f_list[i].stNetPath,&buffer,iFileSize);

			MFile::CreateFolder(_tpath(LocalPath).parent_path());
			CFile file;
			// open destination file
			if (file.Open(LocalPath.c_str(), CFile::modeCreate | CFile::modeWrite, NULL) != FALSE)
			{
				file.Write (buffer, iFileSize);
				file.Close();
			}
			delete [] buffer;

			m_Progress.SetPos(i+1);
			CString output;
			output.Format(_T("Downloading.. :   %s   ( %d / %d )"),MCodeChanger::_CCL(f_list[i].GetNetPath()).c_str(),i+1,f_list.size());
			m_Progress.SetWindowText(output);

			if (bStopThread) break;
		}
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
	}
	catch(...)
	{
		MessageBeep(MB_ICONHAND);
	}

	Utility::sleep(100);
	PostMessage(WM_CLOSE,0,0);
}

void CProgressDialog::UploadFolder(const tstring& stLocalPath,const std::string& stDestNetPath)
{
	boost::thread BuildThread(boost::bind(&CProgressDialog::UploadFolderThread,this
		,stLocalPath,stDestNetPath));
}
void CProgressDialog::UploadEx(const tstring& stLocalPath)
{
	boost::thread BuildThread(boost::bind(&CProgressDialog::UploadExThread,this
		,stLocalPath));
}
void CProgressDialog::UploadFiles(const filepath_list& path_list,const std::string& stCurrentPath)
{
	boost::thread BuildThread(boost::bind(&CProgressDialog::UploadFilesThread,this
		,path_list,stCurrentPath));
}
filepath_list CProgressDialog::UploadCommon(const std::vector<_tpath>& local_list,filepath_list& net_list,bool bCheck)
{
	filepath_list filepath_list_moved;

	if (local_list.size()!=net_list.size())
	{
		m_Progress.SetWindowText(_T("Internal Error : Size Mismatch"));
		return filepath_list_moved;
	}

//	try
//	{
	m_Progress.SetRange(0,local_list.size());
	m_Progress.SetPos(0);
	m_Progress.SetWindowText(_T("Uploading...... :   Start"));

	CxImage image;
	for (unsigned int i=0;i<local_list.size();i++)
	{
		if (i>508)
		{
			int kk=55;
		}
		CString output;

		tstring stFrom=local_list[i].c_str();
		std::string stTo=net_list[i];
		boost::replace_all(stTo, _T("\\"), _T("/"));

		image.Load(stFrom.c_str(),CXIMAGE_FORMAT_UNKNOWN);
//		tstring stFileExt=MFile::GetFileExtL(stFrom);
//		if (!config_.server_config.Compare(FILE_EXTENSIONS,MCodeChanger::_CCU(stFileExt)))
		if (!image.IsValid())
		{
			Sleep(100);
			output.Format(_T("%s [%d/%d]    : Invalid format, Skipped")
				,_tpath(stFrom).string().c_str(),i,local_list.size());
			m_Progress.SetWindowText(output);
		}
		else
		{
			if (bCheck)
			{
				int iRenameCount=0;
				tstring csDumy=MCodeChanger::_CCL(stTo);
				csDumy=Utility::GetNumericName(iRenameCount,MCodeChanger::_CCL(stTo));

				iRenameCount++;

				fileinfo_list result;
				WhriaClient.searchfile_by_path_exact(MCodeChanger::_CCU(csDumy),result);

				while (result.size()!=0)
				{
					csDumy=Utility::GetNumericName(iRenameCount,MCodeChanger::_CCL(stTo));
					iRenameCount++;

					result.clear();

					WhriaClient.searchfile_by_path_exact(MCodeChanger::_CCU(csDumy),result);
				}

				stTo=MCodeChanger::_CCU(csDumy);
			}

			filepath_list_moved.push_back(stTo);

			ImageProcess::MakeThumbnail(image,config_.server_config);

//			bool Encode(BYTE * &buffer, long &size, DWORD imagetype);
			CxMemFile memfile;
			memfile.Open();
			image.Encode(&memfile,CXIMAGE_FORMAT_JPG);
			BYTE* buffer = memfile.GetBuffer();
			long size = memfile.Size();

			WhriaClient.cmd_upload(stTo,stFrom);

			try
			{
				WhriaClient.cmd_tupload(stTo,(unsigned char*)buffer,size);
			}
			catch (const basic_client::ConnectionEx& err_)
			{
				free(buffer);
				throw basic_client::ConnectionEx(err_);
			}
			free(buffer);
			m_Progress.SetPos(i+1);
//				CString output;
			output.Format(_T("Uploading...... :   %s   ( %d / %d )")
				,local_list[i].filename().c_str(),i+1,local_list.size());
			m_Progress.SetWindowText(output);
		}
//			temp.Destroy();
//			delete temp;
	if (bStopThread) break;
	}
//	}
/*	catch (const client_connection::ConnectionEx& err_)
	{
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
	}
	catch(...)
	{
		MessageBeep(MB_ICONHAND);
	}
*/
	return filepath_list_moved;
}

void CProgressDialog::UploadFolderThread(const tstring& stLocalPath,const std::string& stDestNetPath)
{
	while (!bStartThread)
	{
		Utility::sleep(100);
	}
	boost::mutex::scoped_lock lock(thread_mutex);

	try
	{
		if (!MFile::IsDirL(stLocalPath))
		{
//			Utility::sleep(100);
			PostMessage(WM_CLOSE,0,0);
			return;
		}
		std::vector<_tpath> _tpath_list;
		Utility::GetAllSubFiles(_tpath(stLocalPath),_tpath_list);

		if (_tpath_list.size()==0)
		{
			m_Progress.SetWindowText(_T("Empty folder. No file to upload"));
			Utility::sleep(1000);
			PostMessage(WM_CLOSE,0,0);
			return;
		}

		std::string stLeaf=MCodeChanger::_CCU(MFile::leaf(_tpath(stLocalPath)));

		filepath_list path_list_;
		for (unsigned int i=0;i<_tpath_list.size();i++)
		{
			tstring full=_tpath_list[i].c_str();
			tstring root=_tpath(stLocalPath).c_str();
			tstring dest=full;
			boost::algorithm::replace_first(dest,root,_T(""));
			boost::filesystem::path dest_path(stDestNetPath);
			dest_path /= stLeaf;
			dest_path /= MCodeChanger::_CCU(dest);
			path_list_.push_back(MCodeChanger::_CCU(dest_path.c_str()));
			if (bStopThread) 
			{
				Utility::sleep(100);
				PostMessage(WM_CLOSE,0,0);
				return;
			}
		}
		boost::filesystem::path stNetRoot(stDestNetPath);stNetRoot/=stLeaf;

		fileinfo_list result;
		WhriaClient.search_by_path_exact(MCodeChanger::_CCU(stNetRoot.c_str()),result);
		if (result.size()==0)
			UploadCommon(_tpath_list,path_list_,false);
		else
			UploadCommon(_tpath_list,path_list_,true);

//		BrowseTree(MCodeChanger::_CCL(stDestNetPath).c_str(),TRUE);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
	}
	catch(...)
	{
		MessageBeep(MB_ICONHAND);
	}
	Utility::sleep(100);
	PostMessage(WM_CLOSE,0,0);
}

void CProgressDialog::UploadExThread(const tstring& stLocalPath)
{
	while (!bStartThread)
	{
		Utility::sleep(100);
	}
	boost::mutex::scoped_lock lock(thread_mutex);


	try
	{
		if (!MFile::IsDirL(stLocalPath))
		{
			PostMessage(WM_CLOSE,0,0);
			return;
		}

		m_Progress.SetRange(0,1);
		m_Progress.SetPos(0);
		m_Progress.SetWindowText(_T("Upload...... :   Retrieving a List of Photographic Files"));

		std::vector<_tpath> _tpath_list;
		std::vector<_tpath> _tpath_list_final;
		Utility::GetAllSubFiles(_tpath(stLocalPath),_tpath_list);

		if (_tpath_list.size()==0)
		{
			m_Progress.SetWindowText(_T("Empty folder. No file to upload"));
			Utility::sleep(1000);
			PostMessage(WM_CLOSE,0,0);
			return;
		}




		m_Progress.SetWindowText(_T("Upload...... :   Receiving a List of Volume"));
		volname_list vol_list_;
		WhriaClient.getvollist(vol_list_);
		if (vol_list_.size()==0)
		{
			m_Progress.SetWindowText(_T("Failure : Receiving the list of volume"));
			Utility::sleep(1000);
			PostMessage(WM_CLOSE,0,0);
			return;
		}
		tstring dest_vol_name=MCodeChanger::_CCL(vol_list_[0]);

		filepath_list path_list_;
//		std::vector<std::string> folder_list_;

		m_Progress.SetRange(0,_tpath_list.size());
		m_Progress.SetPos(0);
		m_Progress.SetWindowText(_T("Retrieving the Information"));

		for (unsigned int i=0;i<_tpath_list.size();i++)
		{
			tstring stFileExt=MFile::GetFileExtL(_tpath_list[i].c_str());
			if (config_.server_config.Compare(FILE_EXTENSIONS,MCodeChanger::_CCU(stFileExt)))
			{

				boost::posix_time::ptime Time;
				_tpath dest_path;
				if (Utility::LoadMetatag(_tpath_list[i].c_str(),Time))
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

					dest_path=_tpath(dest_vol_name);
					dest_path/=DatePath_Format.str();
					dest_path/=MFile::leaf(_tpath_list[i]);
				}
				else
				{
					dest_path=_tpath(dest_vol_name);
					dest_path/=_T("date_unknown");
					dest_path/=MFile::leaf(_tpath_list[i]);
				}

				path_list_.push_back(MCodeChanger::_CCU(dest_path.c_str()));
				_tpath_list_final.push_back(_tpath_list[i]);

				CString stMsg;
				stMsg.Format(_T("Retrieving the Information : %d / %d"),i+1,_tpath_list.size());
				m_Progress.SetWindowText(stMsg);
			}
			else
			{
				CString stMsg;
				stMsg.Format(_T("Unsupported File Extension : %d / %d"),i+1,_tpath_list.size());
				m_Progress.SetWindowText(stMsg);
			}
			m_Progress.SetPos(i+1);
			if (bStopThread) 
			{
				Utility::sleep(100);
				PostMessage(WM_CLOSE,0,0);
				return;
			}
		}

		if (bStopThread) 
		{
			Utility::sleep(100);
			PostMessage(WM_CLOSE,0,0);
			return;
		}


		filepath_list filepath_list_moved = UploadCommon(_tpath_list_final,path_list_,true);

		fileinfo_list result_temp;
		WhriaClient.getpathinfo(filepath_list_moved, result_temp);
		if (result_temp.size() == 0) return;


		// JSON LOAD
		std::vector<JsonInfo> json_data;
		tstring normalizedPath = stLocalPath;
		boost::replace_all(normalizedPath, _T("\\"), _T("/"));

		size_t lastSlashPos = normalizedPath.find_last_of(_T('/'));
		tstring lastFolderName;
		if (lastSlashPos != tstring::npos)
		{
			lastFolderName = normalizedPath.substr(lastSlashPos + 1);
		}
		else
		{
			lastFolderName = normalizedPath; // 슬래시가 없으면 전체가 폴더 이름
		}

		tstring jsonFilePath = stLocalPath + _T("/") + lastFolderName + _T(".json");
		boost::replace_all(jsonFilePath, _T("\\"), _T("/"));

		if (boost::filesystem::exists(jsonFilePath))
		{

			FILE* fp = _tfopen(jsonFilePath.c_str(), _T("r"));
			if (fp)
			{
				try
				{
					// 파일 크기 측정
					fseek(fp, 0, SEEK_END);
					long fileSize = ftell(fp);
					rewind(fp);

					// 버퍼에 JSON 데이터 로드
					std::vector<char> buffer(fileSize + 1, 0);
					fread(buffer.data(), 1, fileSize, fp);
					fclose(fp);

					// JSON 파싱
					nlohmann::json jsonObject = nlohmann::json::parse(buffer.data());

					// JSON 데이터 추출
					if (jsonObject.is_array())
					{
						for (const auto& item : jsonObject)
						{


							m_Progress.SetRange(0, _tpath_list_final.size());
							m_Progress.SetPos(0);
							m_Progress.SetWindowText(_T("Retrieving the Json Information"));


							for (unsigned int i = 0; i < _tpath_list_final.size(); i++)
							{
								tstring stUploadPath = _tpath_list_final[i].c_str();
								tstring stJsonPath = MCodeChanger::_CCW(item["Filename"].get<std::string>());
								boost::replace_all(stUploadPath, _T("\\"), _T("/"));
								boost::replace_all(stJsonPath, _T("\\"), _T("/"));
								if (stUploadPath == stJsonPath)
								{
									fileinfo old = result_temp[i];
									fileinfo updated = old;
									updated.stPatientName = item["Name"].get<std::string>();
									updated.stPatientID = item["ID"].get<std::string>();

									WhriaClient.setpathinfo(old, updated);




									_tpath oldpath(filepath_list_moved[i]);
									_tpath olddir = _tpath(oldpath.parent_path());

									tstring oldext = MFile::GetFileExtL(MCodeChanger::_CCL(filepath_list_moved[i].c_str())).c_str();
									tstring oldname = MFile::GetFileNameL(MCodeChanger::_CCL(filepath_list_moved[i].c_str())).c_str();

									tstring newname;
									if (strcmp(updated.stPatientID.c_str(), "") != 0)
									{
										newname += MCodeChanger::_CCL(updated.stPatientID).c_str(); newname += _T("_");
									}
									if (strcmp(updated.stPatientName.c_str(), "") != 0)
									{
										newname += MCodeChanger::_CCL(updated.stPatientName).c_str(); newname += _T("_");
									}

									tstring stDate = Utility::GetDateString(updated.Time.date()
										, 2);
									if (!stDate.empty())
									{
										newname += stDate.c_str(); newname += _T("_");
									}

									if (_tcscmp(newname.c_str(), _T("")) == 0)
										newname = oldname;
									else
										boost::algorithm::replace_last(newname, _T("_"), "");

									newname += oldext;

									newname = Utility::GetFilename(newname);

									_tpath newpath;
									newpath = olddir / newname;
									newpath = Utility::refinepath(newpath);

									int iRenameCount = 0;
									if (oldpath != newpath)
									{
										tstring csDumy = newpath.c_str();
										csDumy = Utility::GetNumericName(iRenameCount, newpath.c_str());
										boost::replace_all(csDumy, _T("\\"), _T("/"));

										iRenameCount++;

										fileinfo_list result;
										WhriaClient.searchfile_by_path_exact(MCodeChanger::_CCU(csDumy), result);

										while (result.size() != 0)
										{
											csDumy = Utility::GetNumericName(iRenameCount, newpath.c_str());
											iRenameCount++;

											result.clear();

											WhriaClient.searchfile_by_path_exact(MCodeChanger::_CCU(csDumy), result);
										}

										tstring final_path = csDumy;

										WhriaClient.renamefile(filepath_list_moved[i].c_str(), MCodeChanger::_CCU(final_path));
									}





									CString stMsg;
									stMsg.Format(_T("Retrieving the Json Information : %d / %d"), i + 1, _tpath_list_final.size());
									m_Progress.SetWindowText(stMsg);


								}
							}


						}
					}
				}
				catch (const std::exception& e)
				{
					tstring errorMsg = _T("Error reading JSON file: ") + MCodeChanger::_CCW(e.what());
					AfxMessageBox(errorMsg.c_str());
				}
			}
			else
			{
				AfxMessageBox(_T("Failed to open JSON file."));
			}

		}






	}
	catch (const client_connection::ConnectionEx& err_)
	{
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
	}
	catch(...)
	{
		MessageBeep(MB_ICONHAND);
	}
	Utility::sleep(100);
	PostMessage(WM_CLOSE,0,0);
}

void CProgressDialog::UploadFilesThread(const filepath_list& path_list,const std::string& stCurrentPath)
{
	while (!bStartThread)
	{
		Utility::sleep(100);
	}
	boost::mutex::scoped_lock lock(thread_mutex);

	if (path_list.size()==0)
		return;

	std::vector<_tpath> local_list;
	filepath_list net_list;
//	bool bCheck;

	try
	{
		m_Progress.SetRange(0,path_list.size());
		m_Progress.SetPos(0);
		m_Progress.SetWindowText(_T("Preparing...... :   Start"));
//		m_Progress.SetWindowText(_T("... Prepare to Upload"));

		fileinfo_list f_list;
		WhriaClient.getfolderlist(stCurrentPath,true,f_list);

		bool bSkipAll=false;
		for (unsigned int i=0;i<path_list.size();i++)
		{
			bool bExist=false;
			std::string stFileName_New=MCodeChanger::_CCU(MFile::GetFileNameL(MCodeChanger::_CCL(path_list[i])));
			boost::algorithm::to_lower(stFileName_New);

			for (unsigned int j=0;j<f_list.size();j++)
			{
				std::string stFileName=MCodeChanger::_CCU(MFile::GetFileNameL(MCodeChanger::_CCL(f_list[j].GetNetPath())));
				boost::algorithm::to_lower(stFileName);

				if (strcmp(stFileName_New.c_str()
					,stFileName.c_str())==0)
				{
					if (!bSkipAll)
					{
						CString stMessage;
						stMessage.Format(_T("File already exists. Do you want to skip : %s ?"),MCodeChanger::_CCL(stFileName).c_str());
						int bResult=::XMessageBox(m_hWnd,stMessage,_T(""),MB_SKIPSKIPALLCANCEL);
						if (bResult==IDSKIPALL)
							bSkipAll=true;
						if (bResult==IDCANCEL)
						{
							Utility::sleep(100);
							PostMessage(WM_CLOSE,0,0);
							return;
						}
					}
					bExist=true;break;
				}
			}

			tstring stFilepath=MCodeChanger::_CCL(path_list[i]);

			if (!bExist)
			{
				local_list.push_back(_tpath(stFilepath));
				boost::format fmt("%s/%s");
				fmt % stCurrentPath
					% MCodeChanger::_CCU(MFile::GetFileNameL(stFilepath));			
				net_list.push_back(fmt.str());
			}
			CString output;
			output.Format(_T("Check Duplication.... :   %s   ( %d )")
				,stFilepath.c_str(),i+1);
			m_Progress.SetPos(i+1);
			m_Progress.SetWindowText(output);

			if (bStopThread) 
			{
				Utility::sleep(100);
				PostMessage(WM_CLOSE,0,0);
				return;
			}
		}

		UploadCommon(local_list,net_list,false);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
	}
	catch(...)
	{
		MessageBeep(MB_ICONHAND);
	}

	Utility::sleep(100);
	PostMessage(WM_CLOSE,0,0);

	/*

	try
	{
		fileinfo_list f_list;
		WhriaClient.getfolderlist(stCurrentPath,true,f_list);

		filepath_list path_list_final;
		for (unsigned int i=0;i<path_list.size();i++)
		{
			bool bExist=false;
			for (unsigned int j=0;j<f_list.size();j++)
			{
				std::string stFileName=MCodeChanger::_CCU(MFile::GetFileNameL(MCodeChanger::_CCL(f_list[j].GetNetPath())));
				boost::algorithm::to_lower(stFileName);

				if (strcmp(MCodeChanger::_CCU(MFile::GetFileNameL(MCodeChanger::_CCL(path_list[i]))).c_str()
					,stFileName.c_str())==0)
				{
					CString stMessage;
					stMessage.Format(_T("File already exists : %s"),MCodeChanger::_CCL(stFileName).c_str());
					MessageBox(stMessage);
					bExist=true;
				}
			}
			if (!bExist)
			{
				CxImage temp;
				temp.Load(MCodeChanger::_CCL(path_list[i]).c_str(),CXIMAGE_FORMAT_UNKNOWN);
				if (temp.IsValid())
					path_list_final.push_back(path_list[i]);
				else
				{
					CString stMessage;
					stMessage.Format(_T("Invalid format : %s"),MCodeChanger::_CCL(path_list[i]).c_str());
					MessageBox(stMessage);
				}
			}
		}

		m_Progress.SetRange(0,path_list_final.size());
		m_Progress.SetPos(0);
		if (path_list_final.size()>0)
		{
			for (unsigned int i=0;i<path_list_final.size();i++)
			{
				tstring stFilepath=MCodeChanger::_CCL(path_list_final[i]);
				boost::format fmt("%s/%s");
				fmt % stCurrentPath
					% MCodeChanger::_CCU(MFile::GetFileNameL(stFilepath));			
				WhriaClient.cmd_upload(fmt.str(),stFilepath);

				m_Progress.SetPos(i+1);
				CString output;
				output.Format(_T("Uploading.... :   %s   ( %d / %d )"),stFilepath,i+1,path_list_final.size());
				m_Progress.SetWindowText(output);
			}

			f_list.clear();
//			BrowseFolder(
//			WhriaClient.getfolderlist(stCurrentPath,true,f_list);
//			LoadPicture(f_list,stCurrentPath);
		}
	}
	catch(...)
	{
		MessageBeep(MB_ICONHAND);
	}

	Utility::sleep(100);
	PostMessage(WM_CLOSE,0,0);
	*/
}



void CProgressDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_PROGRESSBAR, m_Progress);
}


BEGIN_MESSAGE_MAP(CProgressDialog, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CProgressDialog::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CProgressDialog message handlers

void CProgressDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	bStopThread=true;
//	boost::mutex::scoped_lock lock(thread_mutex);

//	OnCancel();
}

BOOL CProgressDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	bStartThread=true;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CProgressDialog::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	EndDialog(0);
//	CDialog::OnClose();
}

bool CProgressDialog::Switch(CString executable, CString update)
{

	CString backupFile = executable+_T(".bak");
//	CString directory = executable.Left(executable.ReverseFind(_T('\\')));	
//	CString backupFile = directory + _T('\\') + CString(backup);
	DeleteFile(backupFile);

	if (MFile::ExistsL((LPCTSTR)executable))
	{
		if (!MoveFileEx(executable, backupFile, MOVEFILE_COPY_ALLOWED)) 
		{
			return false;
		}
	}

	if ((MoveFileEx(update, executable, MOVEFILE_COPY_ALLOWED) == TRUE))
	{
		return true;
	}
	if (!MoveFileEx(backupFile,executable, MOVEFILE_COPY_ALLOWED)) 
	{
		return false;
	}
	return false;
}
