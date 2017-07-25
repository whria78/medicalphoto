#include "stdafx.h"
#include "logcommand.h"


tstring CLogCommand::WriteCommand(const std::string& user_id,int iOrderCode,const std::string& param1,const std::string& param2)
{
	tstring string=CMyCout::WriteCommand(user_id,iOrderCode,param1,param2);
	if (bStartLog)
	m_Log.InsertItem(0,string.c_str(),0);
	return string;
}
tstring CLogCommand::WriteError(const error_message& err)
{
	tstring string=CMyCout::WriteError(err);
	if (bStartLog)
	m_Log.InsertItem(0,string.c_str(),1);
	return string;
}
void CLogCommand::WriteString(const tstring& str)
{
	if (bStartLog)
	m_Log.InsertItem(0,str.c_str(),0);
	CMyCout::WriteString(str);
}

void CLogCommand::InitiateCtrl()
	{
		m_Img.Create(16,16,ILC_COLOR32,2,1);
		m_Img.Add(AfxGetApp()->LoadIcon(IDI_ICON_SUBDX));
		m_Img.Add(AfxGetApp()->LoadIcon(IDI_ICON_RED));

		m_Log.SetImageList(&m_Img, LVSIL_SMALL);

		RECT listRect;
		m_Log.GetClientRect(&listRect);
		int nListWidth = (listRect.right - listRect.left);

		m_Log.InsertColumn(0,_T("Message"),LVCFMT_LEFT, nListWidth );
		m_Log.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0);
		bStartLog=true;
	}
