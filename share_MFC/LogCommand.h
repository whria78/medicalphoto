#ifndef MEDIEYE_MFC_LOG_H
#define MEDIEYE_MFC_LOG_H

#include "../share/cmycout.h"
#include <afxcmn.h>
#include "resource.h"

#define LOGCTRL_MAX 300

class CLogCommand 
	: public CMyCout
{
public:
	CLogCommand(CListCtrl& l)
		: CMyCout(_tcout)
		,m_Log(l)
		,bStartLog(false)
	{
	}

	void InitiateCtrl();
	void CloseCtrl(){bStartLog=false;}
//	void SetFlag(bool bSet) {bSetFlag=bSet;}

	tstring WriteCommand(const std::string& user_id,int iOrderCode,const std::string& param1,const std::string& param2="");
	tstring WriteCommand(const std::string& user_id,int iOrderCode,const std::string& param1,int param2)
	{
	   boost::format fmt("%d");fmt % param2;
	   return WriteCommand(user_id,iOrderCode,param1,fmt.str());
    }
	tstring WriteError(const error_message& err);
	void WriteString(const tstring& str);

private:
	CListCtrl& m_Log;
	CImageList m_Img;
	bool bStartLog;
};
#endif