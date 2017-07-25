// PicLoadingThread.cpp : implementation file
//

#include "stdafx.h"
#include "WhriaView.h"
#include "PicLoadingThread.h"
#include "PictureListDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicLoadingThread

IMPLEMENT_DYNCREATE(CPicLoadingThread, CWinThread)

CPicLoadingThread::CPicLoadingThread(CWhriaClient& w)
: WhriaClient(w)
{
}

CPicLoadingThread::~CPicLoadingThread()
{
}

BOOL CPicLoadingThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	bTerminate=FALSE;
	bCheckTerminate=TRUE;
	bNext=FALSE;

	pListDC    = m_PictureList->GetDC();

	// blank_image blank_bitmap 제작

	HBITMAP bitmap = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_INVALID));

	blank_image.CreateFromHBITMAP(bitmap);

	RGBQUAD border;
	border.rgbBlue=255;
	border.rgbGreen=255;
	border.rgbRed=255;

	blank_image.Thumbnail(Config.iThumbWidth,Config.iThumbHeight,border);

	HBITMAP hBitmap=blank_image.MakeBitmap();
	blank_bitmap.Attach(hBitmap);

	return TRUE;
}

int CPicLoadingThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here

	m_Progress->SetPos(0);

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPicLoadingThread, CWinThread)
	//{{AFX_MSG_MAP(CPicLoadingThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicLoadingThread message handlers

int CPicLoadingThread::PrepareLoad()
{
	bNext=FALSE;
	bTerminate=FALSE;
	bCheckTerminate=FALSE;

	int i;
	int iMaxPicture=m_SelectedImage.size();

	if (iMaxPicture>MAX_CHECK)
	{
		CString dumy;
		dumy.Format(_T("Too Many Results : %d"),iMaxPicture);
		m_Progress->SetWindowText(dumy);
		m_Progress->SetRange(0,1);
		m_Progress->SetPos(1);
		m_PictureList->DeleteAllItems();
		m_PictureList->ModifyStyle(LVS_NOSCROLL, 0);
		m_PictureList->ModifyStyle(0,LVS_NOSCROLL);
		bCheckTerminate=TRUE;
		return 0;
	}

	if (iMaxPicture==0)
	{
		m_Progress->SetWindowText(_T("No result"));
		m_Progress->SetRange(0,1);
		m_Progress->SetPos(1);
		m_PictureList->DeleteAllItems();
		m_PictureList->ModifyStyle(LVS_NOSCROLL, 0);
		m_PictureList->ModifyStyle(0,LVS_NOSCROLL);
		bCheckTerminate=TRUE;
		return 0;
	}

	m_ImageListThumb->SetImageCount(iMaxPicture);

	m_Progress->SetRange(0,iMaxPicture);
	m_Progress->SetPos(0);
	m_Progress->SetWindowText(_T("Loading...."));

	m_PictureList->DeleteAllItems();
	m_PictureList->ModifyStyle(LVS_NOSCROLL, 0);

	m_PictureList->SetRedraw(FALSE);

	
	for (i=0;i<iMaxPicture;i++) 
	{
		// add bitmap to our image list
		m_ImageListThumb->Replace(i, &blank_bitmap, NULL);

		CString stNetPath=m_SelectedImage[i].stNetPath.c_str();
		CString stColumn=stNetPath;
		stColumn=stColumn.Left(stColumn.ReverseFind(_T('.')));
		m_PictureList->InsertItem(i,stNetPath, i);
		m_PictureList->SetItemText(i,0,stColumn);
		m_PictureList->SetCheck(i,0);
		if (i==0)
			m_PictureList->EnsureVisible(0,FALSE);
	}

	m_PictureList->SetRedraw(TRUE);
	m_PictureList->ModifyStyle(0,LVS_NOSCROLL);

	return iMaxPicture;
}

__int64 CPicLoadingThread::ImageLoad (const std::string& stNetPath,CxImage  *image)
{
	unsigned char* buffer=NULL;
	try
	{
		__int64 iFileSize=WhriaClient.cmd_tdownload(stNetPath,buffer);

		if (iFileSize==0) return 0;

		CxMemFile memfile((BYTE*)buffer,iFileSize);
		image->Decode(&memfile,CXIMAGE_FORMAT_UNKNOWN);

		if (buffer!=NULL) delete [] buffer;
		return iFileSize;

	}
	catch (const connection::ConnectionEx& err_)
	{
		if (buffer!=NULL) delete [] buffer;
		AfxMessageBox(err_.stMessage.c_str());
		return 0;
	}
}
long CPicLoadingThread::GenerateThumb(const fileinfo& fileinfo_,CxImage& image)  // iIndex 는 m_Selected_Image 에서
{
	RGBQUAD border;
	border.rgbBlue=0;
	border.rgbGreen=0;
	border.rgbRed=0;

	ImageLoad (fileinfo_.stNetPath,&image);
	image.Thumbnail(Config.iThumbWidth-2,Config.iThumbHeight-2,border);
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
		free(buffer);
		AfxMessageBox(err_.stMessage.c_str());
	}
	free(buffer);

	return size;
}

int CPicLoadingThread::Run() 
{
	// TODO: Add your specialized code here and/or call the base class

	int i;
	CBitmap*    pImage = NULL;	
	HBITMAP     hBitmap = NULL;

	int iMaxPicture=PrepareLoad();
	if (iMaxPicture==0) return CWinThread::Run();

	// Thumbnail Size 알아내기

/*	if (m_SelectedImage_thumb.GetSize()==0)
	{
		CString stPathThumb=THUMBNAILPATH;
		stPathThumb="/"+stPathThumb;

		CNetFileInfo nfi;

		for (i=0;i<iMaxPicture;i++)
		{
			nfi.csFilePath=stPathThumb+m_SelectedImage.GetNetPathAt(i);
			nfi.SetFileSize(WhriaClient.GetFileSize(nfi.csFilePath));
			m_SelectedImage_thumb.Add(nfi);
		}
	}
*/
	for (i=0;i<iMaxPicture;i++) 
	{

		// 사진에 대한 Tag 정보 검색
//		WhriaClient.nfia_db.m_SelectedImage.SetAt(i,WhriaClient.nfia_db.GetTagInfoFromDB(&WhriaClient.nfia_db.m_SelectedImage.GetAt(i)));


		CString csProg;
		csProg.Format(_T("Loading... (%d/%d)"),i,iMaxPicture);
		m_Progress->SetWindowText(csProg);
		m_Progress->SetPos(i);
	
		CxImage  image;
		__int64 iSize;

		if (ImageLoad(m_SelectedImage[i].stNetPath,&image)==0)
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
		m_ImageListThumb->Replace(i, pImage, NULL);

/*		// put item to display
		// set the image file name as item text
		CString stColumn;
		stColumn=m_SelectedImage.GetNetPathAt(i);
		stColumn=stColumn.Left(stColumn.ReverseFind('.'));
		m_PictureList->InsertItem(i,m_SelectedImage.GetNetPathAt(i), i);
		m_PictureList->SetItemText(i,0,stColumn);
		m_PictureList->SetCheck(i,0);
*/

		// 직접 display
		
		DrawListItem(i);

		delete pImage;

		if (bTerminate) 
		{
			if (bNext)
			{
				m_SelectedImage=*m_SelectedImage_Next;
				*m_GlobalSelectedImage=*m_SelectedImage_Next;
				
				iMaxPicture=PrepareLoad();
				if (iMaxPicture==0) 
				{
					m_SelectedImage.clear();
					PostQuitMessage(0);
					return CWinThread::Run();
				}

				i=-1;
			}
			else
			{

				bCheckTerminate=TRUE;

				m_SelectedImage.clear();
				PostQuitMessage(0);
				return CWinThread::Run();
			}
		}
	}


	m_Progress->SetRange(0,1);
	m_Progress->SetPos(1);

	m_Progress->SetWindowText(_T(" "));

	m_PictureList->SetRedraw(TRUE);
	bCheckTerminate=TRUE;

	m_SelectedImage.clear();
	PostQuitMessage(0);
	return CWinThread::Run();
 }


BOOL CPicLoadingThread::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	return CWinThread::PreTranslateMessage(pMsg);
}

void CPicLoadingThread::DrawListItem(int nItem)
{
	LVITEM rItem;

    ZeroMemory ( &rItem, sizeof(LVITEM) );
    rItem.mask  = LVIF_IMAGE | LVIF_STATE;
    rItem.iItem = nItem;
    rItem.stateMask = LVIS_SELECTED;
    m_PictureList->GetItem ( &rItem );

	CRect rcIcon;

	m_PictureList->GetItemRect ( nItem, &rcIcon, LVIR_BOUNDS );

	rcIcon.top+=2;
	rcIcon.bottom+=2;
	rcIcon.right+=8;
	rcIcon.left+=8;

	m_ImageListThumb->Draw ( pListDC, rItem.iImage, rcIcon.TopLeft(),ILD_TRANSPARENT );
}
