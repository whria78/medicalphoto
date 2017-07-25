// SelectDiagnosisList.cpp : implementation file
//

#include "stdafx.h"
#include "whriaview.h"
#include "SelectDiagnosisList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectDiagnosisList dialog


CSelectDiagnosisList::CSelectDiagnosisList(CWhriaCacheClient& w,client_config& c,DxDB& dxdb,diagnosis& dx,const CString& s,CWnd* pParent)
	: CDialog(CSelectDiagnosisList::IDD, pParent),
		WhriaClient(w),
	DxDB_(dxdb),
	stSearch(s),
	config_(c),
	diagnosis_(dx)
{
	//{{AFX_DATA_INIT(CSelectDiagnosisList)
	//}}AFX_DATA_INIT
}


void CSelectDiagnosisList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_LIST_DX, m_DxList);
}


BEGIN_MESSAGE_MAP(CSelectDiagnosisList, CDialog)
	//{{AFX_MSG_MAP(CSelectDiagnosisList)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DX, &CSelectDiagnosisList::OnNMDblclkListDx)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectDiagnosisList message handlers

BOOL CSelectDiagnosisList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	stSearch.MakeLower();

	RECT listRect;
	m_DxList.GetClientRect(&listRect);
	int nListWidth = (listRect.right - listRect.left);
	int nVScrollBarWidth = ::GetSystemMetrics(SM_CXVSCROLL); 

	m_DxList.InsertColumn(0,_T("Diagnosis"),LVCFMT_LEFT, nListWidth-nVScrollBarWidth-150);
	m_DxList.InsertColumn(1,_T("ICD10"),LVCFMT_LEFT, 150);

	m_DxList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
    m_DxList.SetExtendedStyle (LVS_EX_GRIDLINES);

	unsigned int i;

	userdx_list dx_list_temp;

	try
	{
		std::string s=MCodeChanger::_CCU(stSearch.GetBuffer(0));
		WhriaClient.getuserdx(s,dx_list_temp);
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

	DxDB_.Find((LPCTSTR)stSearch,dx_list_temp);

	Utility::DeleteDup(dx_list_temp,dx_list_);

	std::sort(dx_list_.begin(),dx_list_.end(),sort_diagnosis());
	
	LV_ITEM LI;
	LI.mask=LVIF_TEXT;
	LI.state=0;
	LI.stateMask=0;
	LI.cchTextMax=255;



	for (i=0;i<dx_list_.size();i++)
	{
		CString string1,string2;
		string1=MCodeChanger::_CCL(dx_list_[i].stDiagnosis).c_str();
		string2=MCodeChanger::_CCL(dx_list_[i].stICD10).c_str();

		if (string1.GetLength()>1)
		{
			CString upper=string1.Left(1);
			upper.MakeUpper();
			string1=upper+string1.Mid(1);
		}

		LI.iImage=0; // Image
		LI.iItem=i;  // 세로

		LI.iSubItem=0;  // 가로
		LI.pszText=(LPTSTR)(LPCTSTR)string1;
		m_DxList.InsertItem(&LI);

		LI.iSubItem=1;  // 가로
		LI.pszText=(LPTSTR)(LPCTSTR)string2;
		m_DxList.SetItem(&LI);

	}

//	if (dx_list_.size()!=0) m_DxList.SetCurSel(0);
 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSelectDiagnosisList::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if( pMsg->message == WM_MOUSEWHEEL )    //스크롤 메세지가 발생했다면
    {
		m_DxList.SendMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
		return TRUE;
	}
	if(pMsg->message == WM_KEYDOWN)   // 키보드가 눌렸을때 처리
    {
        if(pMsg->wParam == VK_ESCAPE)
		{
			OnOK();
		}
        else if(pMsg->wParam == 13)
		{
			POSITION pos = m_DxList.GetFirstSelectedItemPosition();
			while(pos)
			{
				int index = m_DxList.GetNextSelectedItem(pos);
			//do whatever
				if (m_DxList.GetItemState(index,LVIS_SELECTED))
				{
					diagnosis_=dx_list_[index];
					OnOK();
				}
			}
            return TRUE;
		}
    }
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CSelectDiagnosisList::OnNMDblclkListDx(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int iSelected=pNMListView->iItem;

	if (iSelected!=-1)
	{
		diagnosis_=dx_list_[iSelected];
		OnOK();
	}
}
