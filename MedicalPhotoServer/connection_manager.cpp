#include "stdafx.h"
#include "connection_manager.h"


void CConnection_Manager::InitiateCtrl()
	{
		RECT listRect;
		m_list.GetClientRect(&listRect);
		int nListWidth = (listRect.right - listRect.left);
		int nVScrollBarWidth = ::GetSystemMetrics(SM_CXVSCROLL); 

		m_Img.Create(16,16,ILC_COLOR32,2,1);
		m_Img.Add(AfxGetApp()->LoadIcon(IDI_ICON_SUBDX));
		m_Img.Add(AfxGetApp()->LoadIcon(IDI_ICON_RED));

		m_list.SetImageList(&m_Img, LVSIL_SMALL);

		if (config_.Compare(MULTIUSER_SUPPORT,1))
		{
			m_list.InsertColumn(0,_T(""),LVCFMT_LEFT, 0);
			m_list.InsertColumn(1,_T("User"),LVCFMT_LEFT, 100);
			m_list.InsertColumn(2,_T("Client IP Address"),LVCFMT_LEFT, nListWidth-nVScrollBarWidth-100);
		}
		else
		{

			m_list.InsertColumn(0,_T(""),LVCFMT_LEFT, 0);
			m_list.InsertColumn(1,_T("User"),LVCFMT_LEFT, 0);
			m_list.InsertColumn(2,_T("Client IP Address"),LVCFMT_LEFT, nListWidth-nVScrollBarWidth);
			}
		m_list.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0);

}

void CConnection_Manager::start(server_connection_ptr c)
	{

		Add(c->GetConnectionID()
			,MCodeChanger::_CCL(c->GetUserID())
			,MCodeChanger::_CCL(c->socket().remote_endpoint().address().to_string()));

		async_connection_manager::start(c);
	}

	void CConnection_Manager::stop(server_connection_ptr c)
	{
		int j=0;
		for (unsigned int i=0;i<connection_id_list.size();i++)
		{
			if (connection_id_list[i]==c->GetConnectionID())
			{
				m_list.DeleteItem(i);
				connection_id_list.erase(connection_id_list.begin()+i);
			}
		}
		async_connection_manager::stop(c);
	}

	void CConnection_Manager::stop_all()
	{
		if (m_list.GetSafeHwnd())
		m_list.DeleteAllItems();
		async_connection_manager::stop_all();
		connection_id_list.clear();
	}

	void CConnection_Manager::Add(int connection_id,const tstring& ipaddress,const tstring& stUserID)
	{
		CString str;

		LV_ITEM LI;
		LI.mask=LVIF_TEXT;
		LI.state=0;
		LI.stateMask=0;
		LI.cchTextMax=255;

		LI.iImage=0; // Image
		LI.iItem=m_list.GetItemCount();  // 세로

		LI.iSubItem=0;  // 가로
		LI.pszText=_T("");
		m_list.InsertItem(&LI);

		TCHAR dumy[256];
		LI.iSubItem=1;  // 가로
		_tcscpy_s(dumy,256,stUserID.c_str());
		LI.pszText=dumy;
		m_list.SetItem(&LI);

		LI.iSubItem=2;  // 가로
		_tcscpy_s(dumy,256,ipaddress.c_str());
		LI.pszText=dumy;
		m_list.SetItem(&LI);

		connection_id_list.push_back(connection_id);
	}
	void CConnection_Manager::Del(int connection_id)
	{
		for (unsigned int i=0;i<connection_id_list.size();i++)
		{
			if (connection_id_list[i]==connection_id)
			{
				m_list.DeleteItem(i);
				connection_id_list.erase(connection_id_list.begin()+i);
			}
		}
	}

	void CConnection_Manager::DeleteAll()
	{
		m_list.DeleteAllItems();
		connection_id_list.clear();
	}
