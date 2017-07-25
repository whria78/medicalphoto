// PictureListDialog.cpp : implementation file
//

#include "stdafx.h"
#include "WhriaView.h"
#include "PictureListDialog.h"
#include ".\picturelistdialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPictureListDialog dialog


CPictureListDialog::CPictureListDialog(CWhriaClient& w,client_config& c,gxListCtrl& m_c,CWnd* pParent /*=NULL*/)
	: CDialog(CPictureListDialog::IDD, pParent),
	WhriaClient(w),
	config_(c),
	m_CommentList(m_c)
{
	//{{AFX_DATA_INIT(CPictureListDialog)
	//}}AFX_DATA_INIT
}


void CPictureListDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPictureListDialog)
	DDX_Control(pDX, IDC_PROGRESS_STATUS, m_Progress);
	DDX_Control(pDX, IDC_LIST_PICTURELIST, m_PictureList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPictureListDialog, CDialog)
	//{{AFX_MSG_MAP(CPictureListDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PICTURELIST, OnDblclkListPicturelist)
	ON_WM_DESTROY()
//	ON_MESSAGE(WM_LOADPICTURE,LoadPictureByMsg)
	ON_WM_CLOSE()
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST_PICTURELIST, OnBegindragListPicturelist)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
//	ON_NOTIFY(HDN_ITEMCLICK, 0, OnHdnItemclickListPicturelist)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PICTURELIST, OnNMClickListPicturelist)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_PICTURELIST, OnNMCustomdrawListPicturelist)
//	ON_WM_LBUTTONUP()
//ON_NOTIFY(LVN_BEGINSCROLL, IDC_LIST_PICTURELIST, OnLvnBeginScrollListPicturelist)
//ON_NOTIFY(LVN_BEGINSCROLL, IDC_LIST_PICTURELIST, OnLvnBeginScrollListPicturelist)
//ON_NOTIFY(LVN_ENDSCROLL, IDC_LIST_PICTURELIST, OnLvnEndScrollListPicturelist)
//ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_PICTURELIST, OnLvnKeydownListPicturelist)
//ON_WM_LBUTTONDOWN()
//ON_NOTIFY(LVN_BEGINSCROLL, IDC_LIST_PICTURELIST, OnLvnBeginScrollListPicturelist)
ON_COMMAND(ID_POPUP_TREE_COPY, OnPopupCopy)
ON_COMMAND(ID_POPUP_TREE_TOEXCELFILE, OnPopupToexcelfile)
ON_COMMAND(ID_POPUP_TREE_DELETE, &CPictureListDialog::OnPopupDelete)
ON_NOTIFY(NM_RCLICK, IDC_LIST_PICTURELIST, OnNMRclickListPicturelist)
ON_WM_SIZE()
ON_NOTIFY(LVN_BEGINSCROLL, IDC_LIST_PICTURELIST, &CPictureListDialog::OnLvnBeginScrollListPicturelist)
ON_NOTIFY(LVN_ENDSCROLL, IDC_LIST_PICTURELIST, &CPictureListDialog::OnLvnEndScrollListPicturelist)
//ON_WM_DROPFILES()
ON_WM_DROPFILES()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPictureListDialog message handlers

BOOL CPictureListDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	// 툴팁 초기화
/*
	m_tooltip.Create(this);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_INITIAL,10);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_AUTOPOP,100000);
	m_tooltip.SetBehaviour(PPTOOLTIP_MULTIPLE_SHOW);

	m_tooltip.SetCssStyles(_T("h2 {font-size: 13pt; color:#ff9900; font-family:Verdana; font-weight:bold}"));
*/

	// picturelist 초기화

	RECT listRect;
	m_PictureList.GetClientRect(&listRect);
	int nListWidth = (listRect.right - listRect.left);
	int nVScrollBarWidth = ::GetSystemMetrics(SM_CXVSCROLL); 
	
//	int nCol1Width = nListWidth * 0.6;
//	int nCol2Width = nListWidth - nCol1Width - nVScrollBarWidth;

	m_PictureList.InsertColumn(0, _T("CLinical Pictures"), LVCFMT_LEFT,nListWidth);

	//
	// Set full row selection and an image list
	//
	m_PictureList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

	m_ImageListThumb.Create(config_.server_config.GetInt(THUMB_WIDTH),config_.server_config.GetInt(THUMB_HEIGHT), ILC_COLOR24, 0, 1);

	m_PictureList.SetImageList(&m_ImageListThumb, LVSIL_NORMAL);

	m_PictureList.SetIconSpacing(config_.server_config.GetInt(THUMB_WIDTH)+5,config_.server_config.GetInt(THUMB_HEIGHT)+25);

//	CoInitialize(NULL);
//	m_PictureList.SetBkImage("c:\\11.bmp",FALSE);

	CMonitors monitors;
	iMonitorCount=monitors.GetCount();
	if (iMonitorCount>5) iMonitorCount=5;

	CMonitor dumy = CMonitors::GetNearestMonitor();

	for ( int i = 0; i < iMonitorCount; i++ )
	{
		
		monitor[i] = monitors.GetMonitor( i );
		bZoom[i]=false;
		bImageOn[i]=false;

		// ImageDisplay Initiation

		ImageDisplay[i].Create(IDD_DIALOG_IMAGEDISPLAY);
		ImageDisplay[i].m_parent=this;

		ImageDisplay[i].monitor=monitor[i];
		
		CRect rect;
		ImageDisplay[i].monitor.GetMonitorRect( &rect );
		ImageDisplay[i].MoveWindow(0,0,rect.Width(),rect.Height());
//		ImageDisplay[i].monitor.CenterWindowToMonitor(&ImageDisplay[i]);

		if (dumy==monitor[i]) iPrimaryMonitor=i;
	}

	// Icon

	m_Img.Create(16,16,ILC_COLOR32,2,1);
	CWhriaViewApp *App=(CWhriaViewApp*)AfxGetApp();
	m_Img.Add(App->LoadIcon(IDI_ICON_RED));

	// Checkmark
	
	m_ImageListCheck.Create(16,16,ILC_COLOR24|ILC_MASK,4,4);

	CBitmap bm;
	bm.LoadBitmap(IDB_BITMAP_CHECKMARK);
	m_ImageListCheck.Add(&bm,RGB(255,0,255));

	// font 생성

	//Create the Font
	LOGFONT lf = {0};
	lf.lfHeight = -11;
	lf.lfWeight = FW_NORMAL;
	
	_tcscpy(lf.lfFaceName,_T("Tahoma"));
	m_font.CreateFontIndirect(&lf);
    

	// ToolTipListCtrl
	m_PictureList.EnableToolTips(TRUE);

	
	// Initiate Thread
	bTerminateLoadingThread=FALSE;

	// blank_image blank_bitmap 제작

	HBITMAP bitmap = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_INVALID));

	blank_image.CreateFromHBITMAP(bitmap);

	RGBQUAD border;
	border.rgbBlue=255;
	border.rgbGreen=255;
	border.rgbRed=255;

	blank_image.Thumbnail(config_.server_config.GetInt(THUMB_WIDTH),config_.server_config.GetInt(THUMB_HEIGHT),border);

	HBITMAP hBitmap=blank_image.MakeBitmap();
	blank_bitmap.Attach(hBitmap);


	//

	bCtrlOn=false;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPictureListDialog::OnDblclkListPicturelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	OnNMClickListPicturelist(pNMHDR,pResult);

	*pResult = 0;

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	unsigned int iSelected=pNMListView->iItem;

	if (iSelected>=m_SelectedImage.size() || iSelected==-1) return;


	// 다중 모니터

	int iCurrentMonitor;
	
//	if (iMonitorCount==1)
        iCurrentMonitor=GetCurrentMonitor();
/*	else
	{
		int i;
		for (i=0;i<iMonitorCount;i++)
		{
			if (i != GetCurrentMonitor())
			{
				iCurrentMonitor=i;break;
			}
		}
	}
*/


//		CNetFileInfo nfi=WhriaClient.nfia_db.m_SelectedImage.GetAt(iSelected);


		if (ImageLoad(m_SelectedImage[iSelected].stNetPath.c_str(),&CxImageList[iCurrentMonitor],false)==false)
	{
		m_Progress.SetWindowText(_T("File not exists"));
		return;
	}

	ImageDisplay[iCurrentMonitor].fileinfo_=m_SelectedImage[iSelected];
	bZoom[iCurrentMonitor]=false;
	ShowPictureMultiMon(iCurrentMonitor);

//	m_Progress.SetWindowText("Double click any thumbnail for enlarging");
	
}

void CPictureListDialog::OnDestroy() 
{

	CDialog::OnDestroy();
	// TODO: Add your message handler code here
}

int CPictureListDialog::GetCurrentMonitor()
{
	CRect rect;
	CMonitor current_monitor= CMonitors::GetNearestMonitor();

	int i;
	for (i=0;i<iMonitorCount;i++)
	{
		if (monitor[i]==current_monitor) return i;
	}
	return -1;
}

BOOL CPictureListDialog::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

//	m_tooltip.RelayEvent(pMsg);
	
    if( pMsg->message == WM_MOUSEWHEEL )    //스크롤 메세지가 발생했다면
    {
		m_PictureList.SetRedraw(TRUE);
		m_PictureList.SendMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
		return TRUE;
	}

	if(pMsg->message == WM_KEYUP)   // 키보드가 안눌렸을 처리
	{
        if(pMsg->wParam == VK_CONTROL)
		{
			bCtrlOn=false;
            return TRUE;
		}
	}

	if(pMsg->message == WM_KEYDOWN)   // 키보드가 눌렸을때 처리
    {
        if(pMsg->wParam == VK_CONTROL)
		{
			bCtrlOn=true;
            return TRUE;
		}

        if(pMsg->wParam == 65) // 'a' 키
		{
			int i;
			for (i=0;i<m_PictureList.GetItemCount();i++)
			{
				m_PictureList.SetCheck(i,true);
			}
		}

        if(pMsg->wParam == 67) // 'c' 키
		{
			OnPopupCopy();
		}

        if(pMsg->wParam == VK_ESCAPE)
		{
			int iCurrentMonitor=GetCurrentMonitor();

			ImageDisplay[iCurrentMonitor].ShowWindow(SW_HIDE);
			bImageOn[iCurrentMonitor]=false;

			Unselectall();

            return TRUE;
		}
        
		if(pMsg->wParam == VK_SPACE)
		{
//			ImageDisplay[0].monitor=ImageDisplay[1].monitor;
//			ImageDisplay[0].monitor.CenterWindowToMonitor(&ImageDisplay[0]);
			

			int iCurrentMonitor=GetCurrentMonitor();

			if (bImageOn[iCurrentMonitor]==false) return TRUE;

			ImageDisplay[iCurrentMonitor].bZoom=!ImageDisplay[iCurrentMonitor].bZoom;

//			POINT rCurPos;
			GetCursorPos(&ImageDisplay[iCurrentMonitor].pZoomPoint);
			ImageDisplay[iCurrentMonitor].ScreenToClient(&ImageDisplay[iCurrentMonitor].pZoomPoint);

			ImageDisplay[iCurrentMonitor].Invalidate(FALSE);

			return TRUE;

		}

        if(pMsg->wParam == VK_PRIOR)
		{
			int iCurrentMonitor=GetCurrentMonitor();
			int iMoveToMonitor;

			if (bImageOn[iCurrentMonitor]==false || iMonitorCount<2) return TRUE;
			
			iMoveToMonitor=iCurrentMonitor+1;
			if (iMoveToMonitor>=iMonitorCount) iMoveToMonitor=0;

			bZoom[iMoveToMonitor]=bZoom[iCurrentMonitor];
			ZoomPoint[iMoveToMonitor]=ZoomPoint[iCurrentMonitor];
			CxImageList[iMoveToMonitor]=CxImageList[iCurrentMonitor];
			ImageDisplay[iMoveToMonitor].fileinfo_=ImageDisplay[iCurrentMonitor].fileinfo_;

			// 현재 모니터 지우고

			ImageDisplay[iCurrentMonitor].ShowWindow(SW_HIDE);
			bImageOn[iCurrentMonitor]=false;
		
			// 새 모니터 그리고

			ShowPictureMultiMon(iMoveToMonitor);

			
            return TRUE;
		}

        if(pMsg->wParam == VK_NEXT)
		{
			CMonitor current_monitor= CMonitors::GetNearestMonitor();

			int iCurrentMonitor;
			int iMoveToMonitor;
			int i;
		
			for (i=0;i<iMonitorCount;i++)
			{
				if (monitor[i]==current_monitor) iCurrentMonitor=i;
			}

			if (bImageOn[iCurrentMonitor]==false || iMonitorCount<2) return TRUE;
	
			iMoveToMonitor=iCurrentMonitor-1;
			if (iMoveToMonitor<0) iMoveToMonitor=iMonitorCount-1;

			bImageOn[iMoveToMonitor]=TRUE;
			bImageOn[iCurrentMonitor]=FALSE;

			bZoom[iMoveToMonitor]=bZoom[iCurrentMonitor];
			ZoomPoint[iMoveToMonitor]=ZoomPoint[iCurrentMonitor];
			CxImageList[iMoveToMonitor]=CxImageList[iCurrentMonitor];
			ImageDisplay[iMoveToMonitor].fileinfo_=ImageDisplay[iCurrentMonitor].fileinfo_;

			// 현재 모니터 지우고
		
			ImageDisplay[iCurrentMonitor].ShowWindow(SW_HIDE);
			bImageOn[iCurrentMonitor]=false;

			// 새 모니터 그리고

			ShowPictureMultiMon(iMoveToMonitor);

			
            return TRUE;
		}

		if (pMsg->wParam == VK_LEFT)
		{
			int iCurrentMonitor=GetCurrentMonitor();

			if (bImageOn[iCurrentMonitor]==false) return TRUE;

			ImageDisplay[iCurrentMonitor].image.RotateLeft();

			ImageDisplay[iCurrentMonitor].Invalidate(FALSE);

			return TRUE;
		}


		if (pMsg->wParam == VK_RIGHT)
		{
			int iCurrentMonitor=GetCurrentMonitor();

			if (bImageOn[iCurrentMonitor]==false) return TRUE;

			ImageDisplay[iCurrentMonitor].image.RotateRight();

			ImageDisplay[iCurrentMonitor].Invalidate(FALSE);

			return TRUE;
		}

		if (pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN)
		{
			int iCurrentMonitor=GetCurrentMonitor();

			if (bImageOn[iCurrentMonitor]==false) return TRUE;

			ImageDisplay[iCurrentMonitor].image.Rotate180();

			ImageDisplay[iCurrentMonitor].Invalidate(FALSE);

			return TRUE;
		}

        if(pMsg->wParam == VK_F12)
		{
			(GetParent()->GetDlgItem(IDC_EDIT_INPUT))->SetFocus();
            return TRUE;
		}

        if(pMsg->wParam == VK_TAB)
		{
			(GetParent()->GetDlgItem(IDC_EDIT_DLG_ID))->SetFocus();
            return TRUE;
		}

        if(pMsg->wParam == VK_F11)
		{
			GetParent()->PostMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
            return TRUE;
		}
    }
	
	return CDialog::PreTranslateMessage(pMsg);
}


void CPictureListDialog::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
//	CDialog::OnClose();
}

BOOL CPictureListDialog::ShowPictureMultiMon(int iMonitor)
{

		ImageDisplay[iMonitor].monitor.CenterWindowToMonitor(&ImageDisplay[iMonitor]);

		bImageOn[iMonitor]=true;

		ImageDisplay[iMonitor].bZoom=bZoom[iMonitor];
		ImageDisplay[iMonitor].image=CxImageList[iMonitor];
		ImageDisplay[iMonitor].ResetToolTip();

		CRect rect;
		ImageDisplay[iMonitor].monitor.GetMonitorRect( &rect );

		ImageDisplay[iMonitor].MoveWindow(rect.left,rect.top,rect.right,rect.bottom);

		ImageDisplay[iMonitor].ShowWindow(SW_SHOW);

		return TRUE;
}


void CPictureListDialog::OnBegindragListPicturelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	
	// 사용 안하기로
	*pResult = 0;return;

/*


	BOOL bInCheck=false;
	POSITION pos = m_PictureList.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;
	else
	{
	  while (pos)
		{
		int nItem = m_PictureList.GetNextSelectedItem(pos);
		if (m_PictureList.GetCheck(nItem)) bInCheck=true;
		}
	}
	if (!bInCheck) return;

	int i;int iCount=0;
	CStringArray csaDropList;

	for (i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
			csaDropList.Add(m_SelectedImage[i].csFilePath);
	}
	if (csaDropList.GetSize()==0) return;

	WhriaClient.OleDropFile(&csaDropList,&m_Progress);
*/
	*pResult = 0;
}

void CPictureListDialog::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

//	SetTimer(1,500,NULL);


	CDialog::OnTimer(nIDEvent);
}

void CPictureListDialog::GetCommentThread(const std::string& stNetPath)
{
	// mutex

	comment_list comment_list_;

	try{

		WhriaClient.getcomment(stNetPath,comment_list_);

		for (unsigned int i=0;i<comment_list_.size();i++)
		{
			m_CommentList.DeleteAllItems();

			m_CommentList.SetItemText(i,0,MCodeChanger::_CCL(stNetPath).c_str());
			m_CommentList.SetItemText(i,1,MCodeChanger::_CCL(comment_list_[i].Owner.stUserID).c_str());
			m_CommentList.SetItemText(i,2,MCodeChanger::_CCL(comment_list_[i].stDetail).c_str());

//			user user_;
//			WhriaClient.getu
//          need to know ID & name & priv 
		}


	}
	catch (const connection::ConnectionEx& err_)
	{
		m_Progress.SetWindowText(MCodeChanger::_CCW(err_.stMessage).c_str());
		return;
	}


}

void CPictureListDialog::OnNMClickListPicturelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = CDRF_SKIPDEFAULT;

	m_PictureList.SetRedraw(FALSE);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	unsigned int iSelected=pNMListView->iItem;

	if (iSelected>=m_SelectedImage.size() || iSelected==-1) return;

	m_PictureList.SetCheck(iSelected,!m_PictureList.GetCheck(iSelected));
	DrawListCheck(iSelected);

	if (m_PictureList.GetCheck(iSelected))
	{
		GetCommentThread(m_SelectedImage[iSelected].stNetPath);
	}

	// InteliCheck


	int i;CString csMessage;
	int iCount;
	iCount=m_PictureList.GetItemCount();

	if (m_PictureList.GetCheck(iSelected) && bCtrlOn && m_SelectedImage.size()>1)
	{
// 파일명 비슷한 것을 선택
		CString cstFileNameClue=MFile::GetFileNamesExtL(MCodeChanger::_CCL(m_SelectedImage[iSelected].GetPath())).c_str();
		cstFileNameClue=cstFileNameClue.Left(config_.server_config.GetInt(HOSPITAL_ID_LENGTH));
		CString cstFileDir=MFile::GetFileDirL(MCodeChanger::_CCL(m_SelectedImage[iSelected].GetPath())).c_str();
		int iInteliCount=0;
		for (i=0;i<iCount;i++)
		{
			CString tempClue=MFile::GetFileNamesExtL(MCodeChanger::_CCL(m_SelectedImage[i].GetPath())).c_str();
			tempClue=tempClue.Left(config_.server_config.GetInt(HOSPITAL_ID_LENGTH));

			CString tempDir=MFile::GetFileDirL(MCodeChanger::_CCL(m_SelectedImage[i].GetPath())).c_str();

			if (tempClue==cstFileNameClue && tempDir==cstFileDir)
			{
				m_PictureList.SetCheck(i,TRUE);
				DrawListCheck(i);
				iInteliCount++;
			}
		}

		// 자기자신이 선택되므로 iInteli는 1이 최하
		if (iInteliCount<2)
		{

// 시간이 비슷한 것을 선택
	int* iIndex;
	BOOL* bChecked;
	boost::posix_time::ptime* iDate;

	int* iIndex_dumy;
	BOOL* bChecked_dumy;
	boost::posix_time::ptime* iDate_dumy;

	iIndex=new int[iCount];
	bChecked=new BOOL[iCount];
	iDate=new boost::posix_time::ptime[iCount];

	iIndex_dumy=new int[iCount];
	bChecked_dumy=new BOOL[iCount];
	iDate_dumy=new boost::posix_time::ptime[iCount];

	for (i=0;i<iCount;i++)
	{
		iIndex[i]=i;
		bChecked[i]=m_PictureList.GetCheck(i);
		iDate[i]=m_SelectedImage[i].Time;
	}


	int jCount=0;

	for (i=0;i<iCount;i++)
	{
		int j=0;
		while (j<jCount && iDate[j]<iDate[i])
			j++;

		for (int k=jCount;k>j;k--)
		{
			iDate_dumy[k]=iDate_dumy[k-1];
			bChecked_dumy[k]=bChecked_dumy[k-1];
			iIndex_dumy[k]=iIndex_dumy[k-1];
		}
		iIndex_dumy[j]=iIndex[i];
		bChecked_dumy[j]=bChecked[i];
		iDate_dumy[j]=iDate[i];
		jCount++;
	}

	i=0;

	int iMax,iMin;
	for (i=0;i<iCount;i++)
	{
		if (iIndex_dumy[i]==iSelected) iMax=iMin=i;
	}

	if ((iMax+1)<iCount)
	{
		while ((iDate_dumy[iMax+1]-iDate_dumy[iMax])<boost::posix_time::minutes(2))
		{
			iMax++;
			if (iMax>=(iCount-1)) break;
		}
	}

	if ((iMin-1)>=0)
	{
		while ((iDate_dumy[iMin]-iDate_dumy[iMin-1])<boost::posix_time::minutes(2))
		{
			iMin--;
			if (iMin<=0) break;
		}
	}

	for (i=iMin;i<=iMax;i++)
	{
		bChecked_dumy[i]=true;
		if (iDate_dumy[i]!=boost::posix_time::ptime())
		{
			m_PictureList.SetCheck(iIndex_dumy[i],TRUE);
			DrawListCheck(iIndex_dumy[i]);
		}
	}

	delete [] iIndex_dumy;
	delete [] bChecked_dumy;
	delete [] iDate_dumy;

	delete [] iIndex;
	delete [] bChecked;
	delete [] iDate;

		}

	}


	UpdateTooltip();

	// 마지막에 check 한것만 Tag

/*
	if (m_PictureList.GetCheck(iSelected))
        WhriaClient.ShowTag(WhriaClient.nfia_db.m_SelectedImage.GetAt(iSelected));
	else
		WhriaClient.ResetTag();
*/	

	iCount=0;
	for (i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
//			csMessage+=m_SelectedImage[i].GetFileNamesExt()+", ";
			iCount++;
		}
	}

	m_PictureList.SetRedraw(TRUE);

/*
	if (iCount>0)
	{
		CString dumy;
		if (iCount==1)
			dumy="1 item is selected.";
			else
			dumy.Format("%d items are selected.",iCount);
		m_Progress.SetWindowText(dumy);
	}
	else
		m_Progress.SetWindowText(" ");
*/
}

void CPictureListDialog::UpdateTooltip()
{
// check 된 것 모두 ToolTip 에 넣기
/*
	int i;
	m_tooltip.RemoveAllTools();

	int jCount=0;
	CString csTable;
	csTable=_T("<table border=1><tr><td align=center><h2>FileName</h2></td><td align=center><h2>ID</h2></td><td align=center><h2>Name</h2></td><td colspan=2 align=center><h2>Diagnosis</h2></td><td align=center><h2>Comment</h2></td><td align=center><h2>Date</h2></td></tr>");

	for (i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			csTable+=_T("<tr>");
		
			csTable+=_T("<td>");csTable+=MFile::GetFileNamesExtL(MCodeChanger::_CCL(m_SelectedImage[i].GetPath())).c_str();csTable+=_T("</td>");
			csTable+=_T("<td>");csTable+=MCodeChanger::_CCL(m_SelectedImage[i].stPatientID).c_str();csTable+=_T("</td>");
			csTable+=_T("<td>");csTable+=MCodeChanger::_CCL(m_SelectedImage[i].stPatientName).c_str();csTable+=_T("</td>");
			csTable+=_T("<td>");csTable+=MCodeChanger::_CCL(m_SelectedImage[i].Diagnosis.stDiagnosis).c_str();csTable+=_T("</td>");
			csTable+=_T("<td>");csTable+=MCodeChanger::_CCL(m_SelectedImage[i].Diagnosis.stICD10).c_str();csTable+=_T("</td>");
//			csTable+=_T("<td>");csTable+=MCodeChanger::_CCL(m_SelectedImage[i].stPatientID);csComment;csTable+=_T("</td>");
			csTable+=_T("<td>");csTable+=MCodeChanger::_CCL(boost::posix_time::to_simple_string(m_SelectedImage[i].Time)).c_str();csTable+=_T("</td>");

			csTable+=_T("</tr>");

			jCount++;

		}
	}
	csTable+=_T("</table>");

	if (jCount>0)
		m_tooltip.AddTool(GetDlgItem(IDC_PROGRESS_STATUS),csTable);


	// PictureList tooltip

	for (i=0;i<m_PictureList.GetItemCount();i++)
	{
        SetToolTipText(i);
	}
*/
}

/*
CNetFileInfo CPictureListDialog::GetCheckedListByOrder(fileinfo_list* f_list)
{
	CString* iItem;
	int* iItemNb;
	int iCount,i;

	iCount=f_list->size();
	iItem=new CString[iCount];
	iItemNb=new int[iCount];

	CStringArray s_array;
	fileinfo result;

	s_array.RemoveAll();
	for (i=0;i<iCount;i++)
	{
		s_array.Add(f_list[i].stNetPath);
	}
	result.stNetPath=GetCheckedListByOrder(&s_array,iItemNb,iItem);

	s_array.RemoveAll();
	for (i=0;i<iCount;i++)
	{
		s_array.Add(nfia->GetAt(i).csComment);
	}
	result.csComment=GetCheckedListByOrder(&s_array,iItemNb,iItem);

	// Date 는 예외
	if (iCount==1)
	{
		result.csDate=nfia->GetAt(0).csDate;
	}
	else
	{
		s_array.RemoveAll();
		for (i=0;i<iCount;i++)
		{
			s_array.Add(nfia->GetAt(i).csDate);
		}

		result.csDate=GetCheckedListByOrder(&s_array,iItemNb,iItem);
		if (iItemNb[1]>0)
			result.csDate=".............";

	}

	s_array.RemoveAll();
	for (i=0;i<iCount;i++)
	{
		s_array.Add(nfia->GetAt(i).csDiagnosis);
	}
	result.csDiagnosis=GetCheckedListByOrder(&s_array,iItemNb,iItem);

	s_array.RemoveAll();
	for (i=0;i<iCount;i++)
	{
		s_array.Add(nfia->GetAt(i).csICD);
	}
	result.csICD=GetCheckedListByOrder(&s_array,iItemNb,iItem);

	s_array.RemoveAll();
	for (i=0;i<iCount;i++)
	{
		s_array.Add(nfia->GetAt(i).csID);
	}
	result.csID=GetCheckedListByOrder(&s_array,iItemNb,iItem);

	s_array.RemoveAll();
	for (i=0;i<iCount;i++)
	{
		s_array.Add(nfia->GetAt(i).csName);
	}
	result.csName=GetCheckedListByOrder(&s_array,iItemNb,iItem);

	delete []iItem;
	delete []iItemNb;

	return result;
}

CString CPictureListDialog::GetCheckedListByOrder(CStringArray* s_array,int* iItemNb,CString* iItem)
{
	int i,j,iCount;

	iCount=s_array->GetSize();

	for (i=0;i<iCount;i++)
	{
		iItemNb[i]=0;iItem[i]="";
	}

	int iItemCount=0;

	int jDupCount;
	for (i=0;i<iCount;i++)
	{
		if (m_PictureList.GetCheck(i)==TRUE) 
		{

				jDupCount=0;
				for (j=0;j<iItemCount;j++)
				{
					if (s_array->GetAt(j)==s_array->GetAt(i))
					{
						jDupCount++;
					}
				}

				if (jDupCount==0)
				{
					iItem[iItemCount]=s_array->GetAt(i);
					iItemNb[iItemCount]++;
					iItemCount++;
				}
				else
				{
					int k;
					for (k=0;k<iItemCount;k++)
					{
						if (iItem[k]==s_array->GetAt(i))
							iItemNb[k]++;

					}
				}

		}
	}

	// sort

	CString* iItem_dumy;
	int* iItemNb_dumy;
	iItem_dumy=new CString[iItemCount];
	iItemNb_dumy=new int[iItemCount];

	int jItemCount=0;
	int jCount=0;

	for (i=0;i<iItemCount;i++)
	{
		j=0;
		while (j<jCount && iItemNb_dumy[j]<iItemNb[i])
			j++;

		for (int k=jCount;k>j;k--)
		{
			iItemNb_dumy[k]=iItemNb_dumy[k-1];
			iItem_dumy[k]=iItem_dumy[k-1];
		}
		iItem_dumy[j]=iItem[i];
		iItemNb_dumy[j]=iItemNb[i];
		jCount++;
	}

	for (i=0;i<iCount;i++)
	{
		iItem[i]="";iItemNb=0;
	}

	CString csResult;
	jCount=0;

	for (i=0;i<iItemCount;i++)
	{
		if (iItem_dumy[i]!="") 
		{
			if (jCount<2)
			{
				csResult+=iItem_dumy[i]+", ";
				jCount++;
			}
			else
			{
				csResult+=".";
			}
		}
	}

	delete []iItem_dumy;
	delete []iItemNb_dumy;

	if (csResult.Right(2)==", ")
        csResult=csResult.Left(csResult.GetLength()-2);

	return csResult;
}
*/

void CPictureListDialog::OnNMCustomdrawListPicturelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = CDRF_DODEFAULT;

	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);


if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	   {
		*pResult = CDRF_NOTIFYITEMDRAW;
//		*pResult = CDRF_NOTIFYPOSTERASE;
        }

	/*	else if(pLVCD->nmcd.dwDrawStage == CDDS_PREERASE )
	{
        *pResult = CDRF_SKIPDEFAULT;
	}
*/
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
        {
        // This is the pre-paint stage for an item.  We need to make another
        // request to be notified during the post-paint stage.


        // If this item is selected, re-draw the icon in its normal
        // color (not blended with the highlight color).

        LVITEM rItem;
        int    nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec );

        // Get the image index and state of this item.  Note that we need to
        // check the selected state manually.  The docs _say_ that the
        // item's state is in pLVCD->nmcd.uItemState, but during my testing
        // it was always equal to 0x0201, which doesn't make sense, since
        // the max CDIS_* constant in commctrl.h is 0x0100.

        ZeroMemory ( &rItem, sizeof(LVITEM) );
        rItem.mask  = LVIF_IMAGE | LVIF_STATE;
        rItem.iItem = nItem;
        rItem.stateMask = LVIS_SELECTED;
        m_PictureList.GetItem ( &rItem );

        // If this item is selected, redraw the icon with its normal colors.
//        if ( rItem.state & LVIS_SELECTED )

		pListDC = CDC::FromHandle ( pLVCD->nmcd.hdc );

		CRect rcIcon;

            // Get the rect that holds the item's icon.

		m_PictureList.GetItemRect ( nItem, &rcIcon, LVIR_BOUNDS );


		// Draw the icon.

		rcIcon.top+=2;
		rcIcon.bottom+=2;
		rcIcon.right+=8;
		rcIcon.left+=8;

		POINT pt;
		pt.x=rcIcon.left;
		pt.y=rcIcon.top+config_.server_config.GetInt(THUMB_HEIGHT);
		pt.y+=5;

		CRect crListrect;
		m_PictureList.GetWindowRect(crListrect);
		
		if ((pt.y+20)>0 && rcIcon.top<crListrect.Height())
		{
		m_ImageListThumb.Draw ( pListDC, rItem.iImage, rcIcon.TopLeft(),ILD_TRANSPARENT );
		m_ImageListCheck.Draw(pListDC,m_PictureList.GetCheck(nItem),pt,ILD_TRANSPARENT);


		// subitem 그리기

		CFont *pOldFont = pListDC->SelectObject(&m_font);
		CRect rc;

		rc.left = rcIcon.left+20;
		rc.right = rcIcon.right;
		rc.top=rcIcon.top+config_.server_config.GetInt(THUMB_HEIGHT);
		rc.bottom=rcIcon.top+config_.server_config.GetInt(THUMB_HEIGHT);
		rc.bottom+=25;

/*		CString dumy;
		dumy.Format("%d",pt.y);
		pListDC->DrawText(dumy,&rc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
*/
		pListDC->DrawText(m_PictureList.GetItemText(nItem,0),&rc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		pListDC->SelectObject(pOldFont);

//		SetToolTipText(nItem);

		}

		// 선택한 것 테두리 그리기
/*
		if (m_PictureList.GetCheck(nItem))
		{
			CPen MyPen(PS_SOLID,4,RGB(255,255,255));
			CPen *pOldPen;
			pOldPen=pListDC->SelectObject(&MyPen);
			pListDC->MoveTo(rcIcon.left+2,rcIcon.top+1);
			pListDC->LineTo(rcIcon.left+THUMBNAIL_WIDTH-3,rcIcon.top+2);

			pListDC->LineTo(rcIcon.left+THUMBNAIL_WIDTH-3,rcIcon.top+THUMBNAIL_HEIGHT-2);

			pListDC->LineTo(rcIcon.left+2,rcIcon.top+THUMBNAIL_HEIGHT-2);
			pListDC->LineTo(rcIcon.left+2,rcIcon.top+2);
			pListDC->SelectObject(pOldPen);

		}
*/

        *pResult = CDRF_SKIPDEFAULT;
//        *pResult = CDRF_NOTIFYPOSTPAINT;
//        *pResult = CDDS_SUBITEM|CDDS_ITEM|CDDS_PREPAINT ;

        }
	else
	{
        *pResult = CDRF_SKIPDEFAULT;
	}
}

void CPictureListDialog::SetToolTipText(int iIndex)
{
	try{
	m_PictureList.SetItemToolTipText(iIndex,0,MCodeChanger::_CCL(m_SelectedImage[iIndex].stNetPath).c_str());
	}
	catch (std::exception& e)
	{
		e.what();
	}
}


void CPictureListDialog::Unselectall()
{
	// TODO: Add your control notification handler code here
	int i;
	m_PictureList.SetRedraw(FALSE);
	for (i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
			m_PictureList.SetCheck(i,false);
	}
	m_PictureList.SetRedraw(TRUE);
	m_Progress.SetWindowText(_T(" "));
	
//	WhriaClient.ShowTag(CNetFileInfo());

//	m_tooltip.RemoveAllTools();
}


void CPictureListDialog::OnPopupCopy()
{
	// TODO: Add your command handler code here
	int iCount,i;

	iCount=0;
	for (i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			iCount++;
		}
	}

	if (iCount==0)
	{
//		MessageBox("No item is selected");
		return;
	}

	CString stDestFolder=ChooseFolder();
	if (stDestFolder==_T("")) return;

	// 중복 파일 체크

	for (i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			CString dumy=stDestFolder+_T("/");
			dumy+=m_SelectedImage[i].GetFileName().c_str();
			CFileStatus status;
			if (CFile::GetStatus(dumy, status))
			{
				if (MessageBox(dumy+_T(" already exists. Are you sure to replace it ?"),_T("File Already Exists !"),MB_YESNO)!=IDYES)
					return;
			}
		}
	}

	// 파일 전송


	for (i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			unsigned char* buffer=NULL;
			CString LocalPath=stDestFolder+MFile::GetFileNameL(MCodeChanger::_CCL(m_SelectedImage[i].GetPath())).c_str();
			try{

				__int64 iFileSize;
				WhriaClient.cmd_download(m_SelectedImage[i].stNetPath,&buffer,iFileSize);

				CFile file;
				// open destination file
				if (file.Open(LocalPath, CFile::modeCreate | CFile::modeWrite, NULL) != FALSE)
				{
					file.Write (buffer, iFileSize);
					file.Close();
				}
				delete [] buffer;
			}
			catch (const connection::ConnectionEx& err_)
			{
				delete [] buffer;
				m_Progress.SetWindowText(MCodeChanger::_CCW(err_.stMessage).c_str());
			}
		}
	}

}

void CPictureListDialog::OnPopupToexcelfile()
{
	// TODO: Add your command handler code here

	int iCount,i;

	iCount=0;
	for (i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			iCount++;
		}
	}

	if (iCount==0)
	{
//		MessageBox("No item is selected");
		return;
	}

	CString stDestFolder=ChooseFolder();
	if (stDestFolder==_T("")) return;

	CSpreadSheet SS(stDestFolder+_T("/Info.xls"), _T("MediEye"));
    CStringArray sampleArray;
/*
	SS.BeginTransaction();

	CNetFileInfo::GetInfoArrayTag(&sampleArray);
	SS.AddHeaders(sampleArray);

	for (i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			if (m_SelectedImage[i].IsExistInfo())
			{
				int j=0;bool bDup=FALSE;
				for (j=0;j<i;j++)
				{
					if (CNetFileInfo::Compare(m_SelectedImage[i]
						,WhriaClient.nfia_db.m_SelectedImage.GetAt(j))
						&& m_PictureList.GetCheck(j))
						bDup=TRUE;
				}
				if (bDup==FALSE)
				{
					m_SelectedImage[i].GetInfoArray(&sampleArray);
			        SS.AddRow(sampleArray);
				}
			}
		}
	}
	SS.Commit();
*/
}

void CPictureListDialog::OnNMRclickListPicturelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	CPoint pCurPos;
	GetCursorPos(&pCurPos);

	CMenu popup;
	CMenu *MyMenu;
	popup.LoadMenu(IDR_MENU_POPUP);
	MyMenu=popup.GetSubMenu(0);
//	ClientToScreen(&pCurPos);
	MyMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,pCurPos.x,pCurPos.y,this);

	*pResult = 0;
}

CString CPictureListDialog::ChooseFolder()
{
	UpdateData(TRUE);
	TCHAR szFolder[MAX_PATH*2];
	szFolder[0] = _T('\0');
	CString csResult;

	BOOL bRet = XBrowseForFolder(m_hWnd,
		NULL,		// start with current directory
								 szFolder,
									sizeof(szFolder)/sizeof(TCHAR)-2);
	if (bRet) csResult.Format(_T("%s"),szFolder);
	else
		csResult=_T("");
	csResult.Replace(_T("\\"),_T("/"));
	return csResult;
}

void CPictureListDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_PictureList.m_hWnd!=NULL)
	{
		m_PictureList.MoveWindow(0,30,cx-2,cy-20,TRUE);
		m_Progress.MoveWindow(0,0,cx-2,30,TRUE);
	}
}


BOOL CPictureListDialog::ResetList()
{
	m_SelectedImage.clear();
//	m_SelectedImage_Next.clear();
//	bTerminateLoadingThread=false;
	m_PictureList.DeleteAllItems();
	UpdateTooltip();
	return TRUE;
}



int CPictureListDialog::PrepareLoad(const fileinfo_list& m_Next)
{
	int i;
	int iMaxPicture=m_Next.size();

	if (iMaxPicture>MAX_CHECK)
	{
		CString dumy;
		dumy.Format(_T("Too Many Results : %d"),iMaxPicture);

//		if (MessageBox(dumy+_T("  , Are you sure to read all of them ?"),_T("Caution"),MB_YESNO)!=IDYES)
//		{

			m_Progress.SetWindowText(dumy);
			m_Progress.SetRange(0,1);
			m_Progress.SetPos(1);
			m_PictureList.DeleteAllItems();
			m_PictureList.ModifyStyle(LVS_NOSCROLL, 0);
			m_PictureList.ModifyStyle(0,LVS_NOSCROLL);
			return 0;
//		}
	}

	if (iMaxPicture==0)
	{
		m_Progress.SetWindowText(_T("No result"));
		m_Progress.SetRange(0,1);
		m_Progress.SetPos(1);
		m_PictureList.DeleteAllItems();
		m_PictureList.ModifyStyle(LVS_NOSCROLL, 0);
		m_PictureList.ModifyStyle(0,LVS_NOSCROLL);
		return 0;
	}

	m_ImageListThumb.SetImageCount(iMaxPicture);

	m_Progress.SetRange(0,iMaxPicture);
	m_Progress.SetPos(0);
	m_Progress.SetWindowText(_T("Loading...."));

//	m_PictureList.DeleteAllItems();
	ResetList();
	m_SelectedImage=m_Next;

	m_PictureList.ModifyStyle(LVS_NOSCROLL, 0);

	m_PictureList.SetRedraw(FALSE);



	
	for (i=0;i<iMaxPicture;i++) 
	{
		// add bitmap to our image list
		m_ImageListThumb.Replace(i, &blank_bitmap, NULL);

		CString stNetPath=MCodeChanger::_CCL(m_SelectedImage[i].stNetPath).c_str();
		CString stColumn=MFile::GetFileNamesExtL(stNetPath.GetBuffer(0)).c_str();
		m_PictureList.InsertItem(i,stNetPath, i);
		m_PictureList.SetItemText(i,0,stColumn);
		m_PictureList.SetCheck(i,0);
		if (i==0)
			m_PictureList.EnsureVisible(0,FALSE);
	}

	m_PictureList.SetRedraw(TRUE);
	m_PictureList.ModifyStyle(0,LVS_NOSCROLL);

	return iMaxPicture;
}


__int64 CPictureListDialog::ImageLoad (const std::string& stNetPath,CxImage  *image,bool bThumbnail)
{
	unsigned char* buffer=NULL;
	__int64 iFileSize;

	try
	{
		if (bThumbnail)
		{
			WhriaClient.cmd_tdownload(stNetPath,&buffer,iFileSize);
		}
		else
		{
			WhriaClient.cmd_download(stNetPath,&buffer,iFileSize);
		}

		if (iFileSize==0) return 0;

		CxMemFile memfile((BYTE*)buffer,iFileSize);
		if (image->Decode(&memfile,CXIMAGE_FORMAT_UNKNOWN)==false)
		{
			if (buffer!=NULL) delete [] buffer;
			return 0;
		}

		if (buffer!=NULL) delete [] buffer;
		return iFileSize;

	}
	catch (const connection::ConnectionEx& err_)
	{
		if (buffer!=NULL) delete [] buffer;
		if (err_.iErrorCode!=FILE_NOT_EXIST)
			m_Progress.SetWindowText(MCodeChanger::_CCW(err_.stMessage).c_str());
		return 0;
	}
}
long CPictureListDialog::GenerateThumb(const fileinfo& fileinfo_,CxImage& image)  // iIndex 는 m_Selected_Image 에서
{
	RGBQUAD border;
	border.rgbBlue=0;
	border.rgbGreen=0;
	border.rgbRed=0;

	if (ImageLoad (fileinfo_.stNetPath,&image,false)==0) return 0;

	image.Thumbnail(config_.server_config.GetInt(THUMB_WIDTH)-2,config_.server_config.GetInt(THUMB_HEIGHT)-2,border);
	image.Expand(1,1,1,1,border);

	bool Encode(BYTE * &buffer, long &size, DWORD imagetype);
	CxMemFile memfile;
	memfile.Open();
	image.Encode(&memfile,CXIMAGE_FORMAT_JPG);
	BYTE* buffer = memfile.GetBuffer();
	long size = memfile.Size();

	try
	{
		WhriaClient.cmd_tupload(fileinfo_.stNetPath,(unsigned char*)buffer,size);
	}
	catch (const connection::ConnectionEx& err_)
	{
		m_Progress.SetWindowText(MCodeChanger::_CCW(err_.stMessage).c_str());
	}
	free(buffer);
	return size;
}

void CPictureListDialog::LoadPicture(const fileinfo_list& m_Next,const std::string& stRootPath)
{
//	ResetList();

	stCurrentPath=stRootPath;
	bTerminateLoadingThread=true;
	boost::thread PictureLoadingThread(boost::bind(&CPictureListDialog::Thread_Run,this,m_Next));

	
//	main_condition.wait(l);
//	AfxMessageBox("!");
}


void CPictureListDialog::Thread_Run(fileinfo_list m_Next) 
{
	// TODO: Add your specialized code here and/or call the base class

	int i;
	CBitmap*    pImage = NULL;	
	HBITMAP     hBitmap = NULL;
	int iMaxPicture;

//	boost::mutex::scoped_lock l(main_mutex);
//	main_condition.notify_one();

	boost::mutex::scoped_lock lock(thread_mutex);
//	if (bTerminateLoadingThread) return;
	bTerminateLoadingThread=false;

	ResetList();

	iMaxPicture=PrepareLoad(m_Next);

	m_PictureList.SetRedraw(FALSE);

	for (i=0;i<iMaxPicture;i++) 
	{
		CxImage  image;
		__int64 iSize;
		if (m_SelectedImage[i].stNetDir!=m_SelectedImage[i].stNetPath)
		{

		if (ImageLoad(m_SelectedImage[i].stNetPath,&image,true)==0)
		{
			iSize=GenerateThumb(m_SelectedImage[i],image);
			if (iSize==0)
				image=blank_image;
		}

		if (image.IsValid()==FALSE)
			image=blank_image;

		hBitmap=image.MakeBitmap();

		pImage = new CBitmap();		 
		pImage->Attach(hBitmap);

		// add bitmap to our image list
		m_ImageListThumb.Replace(i, pImage, NULL);

		// 직접 display
	
		DrawListItem(i);
		delete pImage;

		CString csProg;
		csProg.Format(_T("Loading... (%d/%d)"),i+1,iMaxPicture);
		m_Progress.SetWindowText(csProg);
		m_Progress.SetPos(i+1);

		if (bTerminateLoadingThread)
		{
			break;
		}
		}
	}
	m_PictureList.SetRedraw(TRUE);

	//	m_Progress.SetRange(0,1);
//	m_Progress.SetPos(1);
//	m_Progress.SetWindowText(_T(" "));

//	bCheckTerminate=TRUE;

//	m_SelectedImage.clear();
//	PostQuitMessage(0);
 }

 
void CPictureListDialog::DrawListItem(int nItem)
{
	pListDC    = m_PictureList.GetDC();

	LVITEM rItem;

    ZeroMemory ( &rItem, sizeof(LVITEM) );
    rItem.mask  = LVIF_IMAGE | LVIF_STATE;
    rItem.iItem = nItem;
    rItem.stateMask = LVIS_SELECTED;
    m_PictureList.GetItem ( &rItem );

	CRect rcIcon;

	m_PictureList.GetItemRect ( nItem, &rcIcon, LVIR_BOUNDS );
/*
	rcIcon.top+=2;
	rcIcon.bottom+=2;
	rcIcon.right+=8;
	rcIcon.left+=8;

	m_ImageListThumb.Draw ( pListDC, rItem.iImage, rcIcon.TopLeft(),ILD_TRANSPARENT );
//	m_ImageListCheck.Draw (pListDC,m_PictureList.GetCheck(nItem),pt,ILD_TRANSPARENT);
*/
		// Draw the icon.

		rcIcon.top+=2;
		rcIcon.bottom+=2;
		rcIcon.right+=8;
		rcIcon.left+=8;

		POINT pt;
		pt.x=rcIcon.left;
		pt.y=rcIcon.top+config_.server_config.GetInt(THUMB_HEIGHT);
		pt.y+=5;

		CRect crListrect;
		m_PictureList.GetWindowRect(crListrect);
		
		if ((pt.y+20)>0 && rcIcon.top<crListrect.Height())
		{
		m_ImageListThumb.Draw ( pListDC, rItem.iImage, rcIcon.TopLeft(),ILD_TRANSPARENT );
		m_ImageListCheck.Draw(pListDC,m_PictureList.GetCheck(nItem),pt,ILD_TRANSPARENT);
		}

}


void CPictureListDialog::DrawListCheck(int nItem)
{

	pListDC    = m_PictureList.GetDC();

	LVITEM rItem;

    ZeroMemory ( &rItem, sizeof(LVITEM) );
    rItem.mask  = LVIF_IMAGE | LVIF_STATE;
    rItem.iItem = nItem;
    rItem.stateMask = LVIS_SELECTED;
    m_PictureList.GetItem ( &rItem );

	CRect rcIcon;

	m_PictureList.GetItemRect ( nItem, &rcIcon, LVIR_BOUNDS );
/*
	rcIcon.top+=2;
	rcIcon.bottom+=2;
	rcIcon.right+=8;
	rcIcon.left+=8;

	m_ImageListThumb.Draw ( pListDC, rItem.iImage, rcIcon.TopLeft(),ILD_TRANSPARENT );
//	m_ImageListCheck.Draw (pListDC,m_PictureList.GetCheck(nItem),pt,ILD_TRANSPARENT);
*/
		// Draw the icon.

		rcIcon.top+=2;
		rcIcon.bottom+=2;
		rcIcon.right+=8;
		rcIcon.left+=8;

		POINT pt;
		pt.x=rcIcon.left;
		pt.y=rcIcon.top+config_.server_config.GetInt(THUMB_HEIGHT);
		pt.y+=5;

		CRect crListrect;
		m_PictureList.GetWindowRect(crListrect);
		
		if ((pt.y+20)>0 && rcIcon.top<crListrect.Height())
		{
		m_ImageListCheck.Draw(pListDC,m_PictureList.GetCheck(nItem),pt,ILD_TRANSPARENT);
		}

}
void CPictureListDialog::OnLvnBeginScrollListPicturelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// This feature requires Internet Explorer 5.5 or greater.
	// The symbol _WIN32_IE must be >= 0x0560.
	LPNMLVSCROLL pStateChanged = reinterpret_cast<LPNMLVSCROLL>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CPictureListDialog::OnLvnEndScrollListPicturelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// This feature requires Internet Explorer 5.5 or greater.
	// The symbol _WIN32_IE must be >= 0x0560.
	LPNMLVSCROLL pStateChanged = reinterpret_cast<LPNMLVSCROLL>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

//void CPictureListDialog::OnDropFiles(HDROP hDropInfo)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	rjc::RDragDropFiles myFiles (hDropInfo);
//    CString buf;
//
//    int iStat = 0;
//    int iL = 0;
//    while (myFiles ()) {
//        myFiles.sNextFile (buf);
//        iL++;
//        iStat = m_ListControl.InsertItem (iL, buf);
//    }
//
//	CDialog::OnDropFiles(hDropInfo);
//}

void CPictureListDialog::OnDropFiles(HDROP hDropInfo)
{
	// TODO: Add your message handler code here and/or call default

    rjc::RDragDropFiles myFiles (hDropInfo);
    CString buf;

	filepath_list path_list;
    int iStat = 0;
    int iL = 0;
    while (myFiles ()) {
        myFiles.sNextFile (buf);
		buf.MakeLower();
		
		path_list.push_back(MCodeChanger::_CCU((LPCTSTR)buf));
    }

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
				std::string stFileName=f_list[j].GetFileName();
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
				path_list_final.push_back(path_list[i]);
		}

		m_Progress.SetRange(0,path_list_final.size());
		m_Progress.SetPos(0);
		if (path_list_final.size()>0)
		{
			for (unsigned int i=0;i<path_list_final.size();i++)
			{
				tstring stFilepath=MCodeChanger::_CCL(path_list_final[i]);
				boost::format fmt("%s%s");
				fmt % stCurrentPath
					% MCodeChanger::_CCU(MFile::GetFileNameL(stFilepath));			
				WhriaClient.cmd_upload(fmt.str(),stFilepath);

				m_Progress.SetPos(i+1);
				CString output;
				output.Format(_T("Uploading.... :   %s   ( %d / %d )"),stFilepath,i+1,path_list_final.size());
				m_Progress.SetWindowText(output);
			}

			f_list.clear();
			WhriaClient.getfolderlist(stCurrentPath,true,f_list);
			LoadPicture(f_list,stCurrentPath);
		}
	}
	catch (const connection::ConnectionEx& err_)
	{
		m_Progress.SetWindowText(MCodeChanger::_CCW(err_.stMessage).c_str());
	}

	CDialog::OnDropFiles(hDropInfo);
}

void CPictureListDialog::OnPopupDelete()
{
	// TODO: Add your command handler code here

	unsigned int i;
	fileinfo_list f_list;
	for (i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			f_list.push_back(m_SelectedImage[i]);
		}
	}
	if (f_list.size()==0) return;

	if (MessageBox(_T("Are you sure to delete?"),_T("Exit"),MB_YESNO)!=IDYES)
		return;

	try
	{
		for (i=0;i<f_list.size();i++)
		{
			WhriaClient.deletefile(f_list[i].GetNetPath());
		}
	}
	catch (const connection::ConnectionEx& err_)
	{
		m_Progress.SetWindowText(MCodeChanger::_CCW(err_.stMessage).c_str());
	}
	for (int i=m_PictureList.GetItemCount()-1;i>=0;i--)
	{
		if (m_PictureList.GetCheck(i))
		{
			m_SelectedImage.erase(m_SelectedImage.begin()+i);
		}
	}
	LoadPicture(m_SelectedImage,stCurrentPath);
}
