// CustomDiagnosisList.cpp : implementation file
//

#include "stdafx.h"
#include "WhriaView.h"
#include "CustomDiagnosisList.h"
#include <functional>


// CCustomDiagnosisList dialog

IMPLEMENT_DYNAMIC(CCustomDiagnosisList, CDialog)
CCustomDiagnosisList::CCustomDiagnosisList(CWhriaCacheClient&w,CACEdit& m_edit,fileinfo_list& f_list,CWnd* pParent /*=NULL*/)
	: CDialog(CCustomDiagnosisList::IDD, pParent)
	, WhriaClient(w)
	, m_DxListCtrl(m_edit)
	, m_SelectedImage(f_list)
{
}

CCustomDiagnosisList::~CCustomDiagnosisList()
{
}

void CCustomDiagnosisList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CUSTOMDX, m_CustomList);
}


BEGIN_MESSAGE_MAP(CCustomDiagnosisList, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CUSTOMDX, OnNMDblclkListCustomdx)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CUSTOMDX, &CCustomDiagnosisList::OnNMClickListCustomdx)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_CUSTOMDX, &CCustomDiagnosisList::OnLvnEndlabeleditListCustomdx)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CCustomDiagnosisList::OnBnClickedButtonExit)
END_MESSAGE_MAP()


// CCustomDiagnosisList message handlers

BOOL CCustomDiagnosisList::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
//    if (!m_ListCtrl.Create (WS_VISIBLE | LVS_REPORT | /*LVS_SINGLESEL | */ LVS_EDITLABELS, ClientRect, this, LISTCTRLID))
//		return;



	RECT listRect;
	m_CustomList.GetClientRect(&listRect);
	int nListWidth = (listRect.right - listRect.left);
	int nVScrollBarWidth = ::GetSystemMetrics(SM_CXVSCROLL); 

	m_CustomList.InsertColumn(0,_T(""),LVCFMT_LEFT, 0);
	m_CustomList.InsertColumn(1,_T("Diagnosis"),LVCFMT_LEFT, nListWidth-nVScrollBarWidth-60);
	m_CustomList.InsertColumn(2,_T("ICD 10"),LVCFMT_LEFT, 60);
	m_CustomList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
    m_CustomList.SetExtendedStyle (LVS_EX_GRIDLINES);
/*
	CWhriaViewApp *App=(CWhriaViewApp*)AfxGetApp();
	m_Img.Create(16,16,ILC_COLOR32,2,1);
	m_Img.Add(App->LoadIcon(IDI_ICON_PRIV0));
	m_Img.Add(App->LoadIcon(IDI_ICON_PRIV1));
	m_Img.Add(App->LoadIcon(IDI_ICON_PRIV2));
	m_Img.Add(App->LoadIcon(IDI_ICON_PRIV3));
	m_Img.Add(App->LoadIcon(IDI_ICON_PRIV4));
	m_Img.Add(App->LoadIcon(IDI_ICON_PRIV5));
	m_Img.Add(App->LoadIcon(IDI_ICON_PRIV6));
	m_Img.Add(App->LoadIcon(IDI_ICON_PRIV7));
	m_Img.Add(App->LoadIcon(IDI_ICON_PRIV8));
	m_Img.Add(App->LoadIcon(IDI_ICON_PRIV9));

	m_CustomList.SetImageList(&m_Img, LVSIL_SMALL);
*/

	try
	{
		LoadCustomDx();
	}
	catch(...)
	{
		MessageBeep(MB_ICONHAND);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CCustomDiagnosisList::LoadCustomDx()
{
	userdx_list_.clear();
	m_CustomList.DeleteAllItems();

	WhriaClient.getuserdx("",userdx_list_);

	std::sort(userdx_list_.begin(),userdx_list_.end(),sort_diagnosis());
/*
	LV_ITEM LI;
	LI.mask=LVIF_TEXT | LVIF_IMAGE;
	LI.state=0;
	LI.stateMask=0;
	LI.cchTextMax=255;
*/
	unsigned int i;
	for (i=0;i<userdx_list_.size();i++)
	{
		CString dumy;
		dumy.Format(_T("%d"),i+1);
		m_CustomList.InsertItem(i,_T(""),0);
//		m_CustomList.SetItemText(i,0,dumy);
		m_CustomList.SetItemText(i,1,MCodeChanger::_CCL(userdx_list_[i].stDiagnosis).c_str());
		m_CustomList.SetItemText(i,2,MCodeChanger::_CCL(userdx_list_[i].stICD10).c_str());
		
/*
	LI.iImage=0; // Image
	LI.iItem=i;  // 세로

	LI.iSubItem=0;  // 가로
	LI.pszText=(LPTSTR)(LPCTSTR)userdx_list_[i].stDiagnosis.c_str();
	m_CustomList.InsertItem(&LI);

	LI.iSubItem=1;  // 가로
	LI.pszText=(LPTSTR)(LPCTSTR)userdx_list_[i].stICD10.c_str();
	m_CustomList.SetItem(&LI);
*/
	}
	m_CustomList.InsertItemEx(m_CustomList.GetItemCount()-1);
}

void CCustomDiagnosisList::OnNMDblclkListCustomdx(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int iSelected=pNMListView->iItem;

	if (iSelected==-1) m_CustomList.InsertItemEx(m_CustomList.GetItemCount());
}

void CCustomDiagnosisList::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	// 서버에 정보 보내야함

	modified_log modified_log_;
	m_CustomList.GetLog(modified_log_);

	if (modified_log_.size()==0)
	{
		return;
	}
	if (MessageBox(_T("Are you sure to save?"),_T("Save Custom Dx"),MB_YESNO)!=IDYES)
	return;

	dx_list dx_from,dx_to;

	for (unsigned i=0;i<modified_log_.size();i++)
	{
		userdx diagnosis_;
		diagnosis_.stDiagnosis=MCodeChanger::_CCU((LPCTSTR)m_CustomList.GetItemText(modified_log_[i],1));
		diagnosis_.stICD10=MCodeChanger::_CCU((LPCTSTR)m_CustomList.GetItemText(modified_log_[i],2));

		try
		{
			if (modified_log_[i]<(int)userdx_list_.size())
			{
				WhriaClient.setuserdx(userdx_list_[modified_log_[i]],diagnosis_);

				if (userdx_list_[modified_log_[i]]==diagnosis() || diagnosis_==diagnosis())
				{
				}
				else
				{
					dx_from.push_back(userdx_list_[modified_log_[i]]);
					dx_to.push_back(diagnosis_);
				}
			}
			else
			{
				WhriaClient.setuserdx(diagnosis(),diagnosis_);
			}
			CString cstDiagnosis=MCodeChanger::_CCL(diagnosis_.stDiagnosis).c_str();
			CString temp=cstDiagnosis.Left(1);temp.MakeUpper();
			cstDiagnosis=temp+cstDiagnosis.Mid(1);
			m_DxListCtrl.AddSearchString(cstDiagnosis);
		}
		catch (const client_connection::ConnectionEx& err_)
		{
			AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
			exit(1);
		}
		catch (const basic_client::ConnectionEx& err_)
		{
			AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
		}
	}
	try
	{
		LoadCustomDx();
//		MessageBeep(MB_ICONEXCLAMATION); // 확인
	}
	catch(...)
	{
		MessageBeep(MB_ICONHAND);
	}

	if (dx_from.size()>0)
	{
		if (MessageBox(_T("Do you want to update all previous userdx of photographies?"),_T("Update User Diagnosis"),MB_YESNO)!=IDYES)
			return;

		try
		{
			WhriaClient.updateprevuserdx(dx_from,dx_to);
		}
		catch (const client_connection::ConnectionEx& err_)
		{
			AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
			exit(1);
		}
		catch (const basic_client::ConnectionEx& err_)
		{
			AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
		}
	}

	for (unsigned int i=0;i<m_SelectedImage.size();i++)
	{
		for (unsigned int j=0;j<dx_from.size();j++)
		{
			if (m_SelectedImage[i].Diagnosis==dx_from[j])
//				strcmp(m_SelectedImage[i].stDiagnosis.c_str(),dx_from[j].stDiagnosis.c_str())==0
//				&& strcmp(m_SelectedImage[i].stICD10.c_str(),dx_from[j].stICD10.c_str())==0)
			{
				m_SelectedImage[i].Diagnosis=dx_to[j];
//				stDiagnosis=dx_to[j].stDiagnosis;
//				m_SelectedImage[i].stICD10=dx_to[j].stICD10;
			}
		}
	}
}

void CCustomDiagnosisList::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CCustomDiagnosisList::OnNMClickListCustomdx(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CCustomDiagnosisList::OnLvnEndlabeleditListCustomdx(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	m_CustomList.OnEndLabelEdit(pNMHDR,pResult);

	LV_ITEM	*plvItem = &pDispInfo->item;
	if (_tcscmp(plvItem->pszText,_T(""))!=0)
	{
		if (plvItem->iItem==(m_CustomList.GetItemCount()-1))
		{
			if (m_CustomList.GetItemCount()>0)
			{
				if (!m_CustomList.GetItemText(m_CustomList.GetItemCount()-1,1).IsEmpty()
					|| !m_CustomList.GetItemText(m_CustomList.GetItemCount()-1,2).IsEmpty())
					m_CustomList.InsertItemEx(m_CustomList.GetItemCount());
			}
		}
	}


}

BOOL CCustomDiagnosisList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    if (pMsg->message == WM_KEYDOWN)
    {
		if (pMsg->wParam == VK_ESCAPE)
		{
			OnBnClickedButtonExit();
//			GetParent()->PostMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
			return TRUE;
		}
	}	
	if( pMsg->message == WM_MOUSEWHEEL )    //스크롤 메세지가 발생했다면
    {
		m_CustomList.SendMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
		return TRUE;
	}


	return CDialog::PreTranslateMessage(pMsg);
}

void CCustomDiagnosisList::OnBnClickedButtonExit()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
