#pragma once

#define ENCRYPTIONPASS "8972198736328656"
#define ENCRYPTION_LENGTH 16
#define DXLENMAX 256
#define ICDLENMAX 24
#define MEDICALPHOTO_MARKER "medicalphoto"
#define MEDICALPHOTO_MARKER_LEN 12

#include "blowfish.h"
#include <string>
#include "datatype.h"
#include <stdio.h>
#include "unicode.h"
#include <boost/thread/mutex.hpp>
#include "etc.h"

#include "cmycout.h"

class DxDB
{
public:
	DxDB()
		: bTerminate(false)
	{
	}
	
//	void Stop() {bTerminate=true;boost::mutex::scoped_lock lock(dxdb_mutex);}
	void Clear() 
	{
		boost::mutex::scoped_lock lock(dxdb_mutex);
		icd10.clear();
	}
	bool LoadDB(tstring stFilePath)
	{
		ThreadControl ThreadControl_(LOAD_DXDB_THREAD);
		boost::mutex::scoped_lock lock(dxdb_mutex);
		if (!ThreadControl_.Check(&bCheckTerminate)) return true;
		bTerminate=false;

		return LoadDB_s_Mutex(stFilePath);
	}
	static bool IsDBFile(tstring stFilePath)
	{
		FILE* fp;
		
		fp=_tfopen(stFilePath.c_str(),_T("rb"));
		if (fp==NULL) return false;

		char marker[MEDICALPHOTO_MARKER_LEN+1];
		marker[MEDICALPHOTO_MARKER_LEN]=NULL;
		fread(marker,sizeof(char),MEDICALPHOTO_MARKER_LEN,fp);
		if (strcmp(marker,MEDICALPHOTO_MARKER)!=0)
		{
			fclose(fp);
			return false;
		}
		
		char encrypt_pass[ENCRYPTION_LENGTH+1];
		encrypt_pass[ENCRYPTION_LENGTH]=NULL;
		if (fread(encrypt_pass,sizeof(char),ENCRYPTION_LENGTH,fp)!=ENCRYPTION_LENGTH)
		{
			fclose(fp);
			return false;
		}
		fclose(fp);
		return true;
	}

	bool LoadDB_s_Mutex(tstring stFilePath)
	{
		FILE* fp;
		
		fp=_tfopen(stFilePath.c_str(),_T("rb"));
		if (fp==NULL) return false;

		char marker[MEDICALPHOTO_MARKER_LEN+1];
		marker[MEDICALPHOTO_MARKER_LEN]=NULL;
		fread(marker,sizeof(char),MEDICALPHOTO_MARKER_LEN,fp);
		if (strcmp(marker,MEDICALPHOTO_MARKER)!=0)
		{
			fclose(fp);
			return false;
		}
		
		char encrypt_pass[ENCRYPTION_LENGTH+1];
		encrypt_pass[ENCRYPTION_LENGTH]=NULL;
		if (fread(encrypt_pass,sizeof(char),ENCRYPTION_LENGTH,fp)!=ENCRYPTION_LENGTH)
		{
			fclose(fp);
			return false;
		}

		std::string dumy_Dx;
		std::string dumy_ICD;

		char dumy_from[DXLENMAX+1];
		char dumy_to[DXLENMAX+1];
		CBlowFish oBlowFish((unsigned char*)encrypt_pass, 16);
//		icd10.clear();
//		char encrypt_pass[ENCRYPTION_LENGTH+1];
//		strcpy(encrypt_pass,ENCRYPTIONPASS);
//		CBlowFish oBlowFish((unsigned char*)encrypt_pass, 16);

		memset(dumy_from, 0, DXLENMAX+1);
		memset(dumy_to, 0, DXLENMAX+1);

		try
		{
			while (fread(dumy_from,sizeof(char),DXLENMAX,fp)!=NULL)
			{
				diagnosis add_dx;
			
				oBlowFish.Decrypt((unsigned char*)dumy_from,(unsigned char*)dumy_to,DXLENMAX);
				add_dx.stDiagnosis=std::string(dumy_to);
				memset(dumy_from, 0, DXLENMAX+1);
				memset(dumy_to, 0, DXLENMAX+1);

				if (fread(dumy_from,sizeof(char),ICDLENMAX,fp)==NULL) return false;

				oBlowFish.Decrypt((unsigned char*)dumy_from,(unsigned char*)dumy_to,ICDLENMAX);
				add_dx.stICD10=std::string(dumy_to);
				memset(dumy_from, 0, DXLENMAX+1);
				memset(dumy_to, 0, DXLENMAX+1);

				icd10.push_back(add_dx);
				if (bTerminate) 
				{
					fclose(fp);
					return false;
				}
			}
		}
		catch (std::exception& e)
		{
			fclose(fp);
			e.what();
			return false;
		}
		fclose(fp);

//		stFilePath+=_T(".new");
//		SaveDB(stFilePath);

		return true;
	}

	bool SaveDB(tstring stFilePath)
	{
//		boost::mutex::scoped_lock lock(dxdb_mutex);
		bTerminate=false;

		for (unsigned int i=0;i<icd10.size();i++)
		{
			boost::algorithm::to_lower(icd10[i].stDiagnosis);
			if (bTerminate) 
			{
				return false;
			}
		}

		FILE* fp;
		fp=_tfopen(stFilePath.c_str(),_T("wb"));
		if (fp==NULL) return false;

		std::string marker=MEDICALPHOTO_MARKER;
		fwrite(marker.c_str(),1,marker.length(),fp);

		srand( (unsigned)time( NULL ) );
		boost::format fmt("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d");
		fmt % (((double) rand() / (double) RAND_MAX) * 9)
			% (((double) rand() / (double) RAND_MAX) * 9)
			% (((double) rand() / (double) RAND_MAX) * 9)
			% (((double) rand() / (double) RAND_MAX) * 9)
			% (((double) rand() / (double) RAND_MAX) * 9)
			% (((double) rand() / (double) RAND_MAX) * 9)
			% (((double) rand() / (double) RAND_MAX) * 9)
			% (((double) rand() / (double) RAND_MAX) * 9)
			% (((double) rand() / (double) RAND_MAX) * 9)
			% (((double) rand() / (double) RAND_MAX) * 9)
			% (((double) rand() / (double) RAND_MAX) * 9)
			% (((double) rand() / (double) RAND_MAX) * 9)
			% (((double) rand() / (double) RAND_MAX) * 9)
			% (((double) rand() / (double) RAND_MAX) * 9)
			% (((double) rand() / (double) RAND_MAX) * 9)
			% (((double) rand() / (double) RAND_MAX) * 9);

//		unsigned int i;
		
		if (fmt.str().length()<ENCRYPTION_LENGTH)
		{
			fclose(fp);
			return false;
		}

		fwrite(fmt.str().c_str(),1,ENCRYPTION_LENGTH,fp);
		CBlowFish oBlowFish((unsigned char*)fmt.str().c_str(), ENCRYPTION_LENGTH);
		char dumy_from[DXLENMAX+1];
		char dumy_to[DXLENMAX+1];

		for (unsigned int i=0;i<icd10.size();i++)
		{
			diagnosis diagnosis_=icd10[i];

			if (strcmp(diagnosis_.stDiagnosis.c_str(),"")!=0)
			{
				memset(dumy_from, 0, DXLENMAX+1);
				memset(dumy_to, 0, DXLENMAX+1);
				strcpy(dumy_from,diagnosis_.stDiagnosis.c_str());
					
				oBlowFish.Encrypt((unsigned char*)dumy_from,(unsigned char*)dumy_to,DXLENMAX);

				fwrite(dumy_to,sizeof(char),DXLENMAX,fp);

				oBlowFish.ResetChain();
		
				memset(dumy_from, 0, DXLENMAX+1);
				memset(dumy_to, 0, DXLENMAX+1);
				strcpy(dumy_from,diagnosis_.stICD10.c_str());

				oBlowFish.Encrypt((unsigned char*)dumy_from,(unsigned char*)dumy_to,ICDLENMAX);

				fwrite(dumy_to,sizeof(char),ICDLENMAX,fp);
			}
		}

		fclose(fp);
		return TRUE;
	}

	size_t GetSize()
	{
		boost::mutex::scoped_lock lock(dxdb_mutex);
		return icd10.size();
	}
	diagnosis GetAt(int iIndex) 
	{
		boost::mutex::scoped_lock lock(dxdb_mutex);
		return icd10[iIndex];
	}
	void Find(const tstring& stKeyword,dx_list& dx_list_)
	{
//		dx_list.clear();
		try
		{
			std::string stUniKeyword=MCodeChanger::_CCU(stKeyword);
//			boost::algorithm::to_lower(stUniKeyword);  -- for performance
			unsigned int i;
			for (i=0;i<icd10.size();i++)
			{
//				std::string icd_lower=icd10[i].stDiagnosis;
//				boost::algorithm::to_lower(icd_lower);
				if (icd10[i].stDiagnosis.find(stUniKeyword) != std::string::npos)
				{
					dx_list_.push_back(icd10[i]);
				}
			}
		}
		catch (std::exception& e)
		{
			e.what();
		}
	}

	bool IsExistExact(const tstring& stKeyword)
	{
		try
		{
			std::string stUniKeyword=MCodeChanger::_CCU(stKeyword);
			boost::algorithm::to_lower(stUniKeyword);
			unsigned int i;
			for (i=0;i<icd10.size();i++)
			{
//				if (icd10[i].stDiagnosis.find(stUniKeyword) != std::string::npos)
				if (strcmp(icd10[i].stDiagnosis.c_str(),stUniKeyword.c_str())==0)
				{
					return true;
				}
			}
		}
		catch (std::exception& e)
		{
			e.what();
		}
		return false;
	}


	bool bCheckTerminate;
	bool bTerminate;
private:
	static boost::mutex dxdb_mutex;
	dx_list icd10;
//	localdx_list Local_ICD10;
};

