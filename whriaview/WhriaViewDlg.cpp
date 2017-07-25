// WhriaViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WhriaView.h"
#include "WhriaViewDlg.h"
#include ".\whriaviewdlg.h"
#include "afxwin.h"
#include <tlhelp32.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg(const CString& stVersion);

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnStnClickedStaticCredit();
	virtual BOOL OnInitDialog();
	CHyperlinkStatic m_About;
	CStatic m_StaticVersion;
	CString stVersionString;
	CHyperlinkStatic m_WhriaNet;
};

CAboutDlg::CAboutDlg(const CString& stVersion) : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	stVersionString=stVersion;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_STATIC_CREDIT, m_About);
	DDX_Control(pDX, IDC_STATIC_VERSION, m_StaticVersion);
	DDX_Control(pDX, IDC_STATIC_HAN, m_WhriaNet);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
//	ON_BN_CLICKED(IDC_BUTTON_ABOUT_OK, OnBnClickedButtonAboutOk)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWhriaViewDlg dialog

CWhriaViewDlg::CWhriaViewDlg(CMyCout&l,CWhriaCacheClient&w,CWnd* pParent /*=NULL*/)
	: CDialog(CWhriaViewDlg::IDD, pParent)
	, WhriaClient(w)
	, m_Dx(_T(""))
	, m_ID(_T(""))
	, m_Name(_T(""))
	, m_Date(_T(""))
	, m_ICD(_T(""))
	, m_Input(_T(""))
	, config_(l)
	, m_dlg_inputserver(config_)
	, version_(l)
	, bTreeLeftClick(false)
	, bExitFlag(false)
	,bMutexCheck_thread(true)
	,bMutexCheck_comment(true)
	,bMutexCheck_browse(true)
	,bMutexCheck_processimage(true)
	,bMutexCheck_dxdb(true)
	,bMutexCheck_connection(true)
	,bMutexCheck_picturelist(true)
	,bCheck_idleprocess(true)
	,bCheckControl(false)
	,bTerminateLoadingThread(false)
	,bTerminateBrowseThread(false)
	,bTerminateDxDBThread(false)
	,bTerminateConnectionThread(false)
	,old_cx(0)
	,old_cy(0)
	,iCurrentLoadingIndex(0)
	,bColorState(false)
	,bIdleDoModal(false)
	,bIdle(false)
	,iLastDisplay(0)
	, m_ViewDlg(config_)
	, bRunAssist(false)
//	, server_(NULL)
{
	//{{AFX_DATA_INIT(CWhriaViewDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	border.rgbBlue=0;
	border.rgbGreen=0;
	border.rgbRed=0;

//	m_ImageListThumb_Org=new CImageList;
}

void CWhriaViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWhriaViewDlg)
	DDX_Control(pDX, IDC_TREE_REMOTE, m_FolderTree);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_Input);
	//}}AFX_DATA_MAP
	//	DDX_Text(pDX, IDC_EDIT_DX, m_Dx);
	DDX_Text(pDX, IDC_EDIT_DLG_ID, m_ID);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_DATE, m_Date);
	DDX_Text(pDX, IDC_EDIT_ICD, m_ICD);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_stop_button);
	DDX_Control(pDX, IDC_BUTTON_SUBMITTAG, m_submit_ctrl);
	DDX_Control(pDX, IDC_LIST_COMMENT, m_CommentList);
	DDX_Control(pDX, IDC_LIST_PHOTO, m_PictureList);
	DDX_Control(pDX, IDC_PROGRESS_MAIN, m_Progress);
	DDX_Control(pDX, IDC_STATIC_F12, m_StaticF12);
	DDX_Control(pDX, IDC_LIST_CHECKLIST, m_CheckList);
	DDX_Control(pDX, IDC_EDIT_DX, m_DxListCtrl);
	DDX_Control(pDX, IDC_EDIT_NAME, m_CEditName);
	DDX_Control(pDX, IDC_EDIT_DLG_ID, m_CEditID);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_CEditSearch);
	DDX_Control(pDX, IDC_EDIT_DATE, m_CEditDate);
	DDX_Control(pDX, IDC_EDIT_ICD, m_CEditICD10);
}

BEGIN_MESSAGE_MAP(CWhriaViewDlg, CDialog)
	//{{AFX_MSG_MAP(CWhriaViewDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_EN_SETFOCUS(IDC_EDIT_INPUT, OnSetfocusEditInput)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_REMOTE, OnSelchangedTreeRemote)
//	ON_MESSAGE(UM_MESSAGE, OnFolderLoadEnd)
	//}}AFX_MSG_MAP
ON_EN_KILLFOCUS(IDC_EDIT_DX, OnEnKillfocusEditDx)
ON_BN_CLICKED(IDC_BUTTON_SUBMITTAG, OnBnClickedButtonSubmittag)
ON_NOTIFY(NM_RCLICK, IDC_TREE_REMOTE, OnNMRclickTreeRemote)
ON_COMMAND(ID_POPUP_TREE_COPY, OnPopupCopy)
ON_COMMAND(ID_POPUP_TREE_TOEXCELFILE, OnPopupToexcelfile)
ON_WM_SIZE()
//ON_NOTIFY(NM_DBLCLK, IDC_LIST_COMMENT, &CWhriaViewDlg::OnNMDblclkListComment)
ON_COMMAND(ID_ABOUT_UPDATE, &CWhriaViewDlg::OnAboutUpdate)
ON_COMMAND(ID_VIEW_ADVANCED, &CWhriaViewDlg::OnViewAdvanced)
ON_COMMAND(ID_VIEW_BASIC, &CWhriaViewDlg::OnViewBasic)
ON_COMMAND(ID_PREFERENCE_PREFERENCE, &CWhriaViewDlg::OnPreferencePreference)
ON_COMMAND(ID_ABOUT_ABOUT, &CWhriaViewDlg::OnAboutAbout)
ON_NOTIFY(NM_KILLFOCUS, IDC_LIST_COMMENT, &CWhriaViewDlg::OnNMKillfocusListComment)


ON_NOTIFY(NM_DBLCLK, IDC_LIST_PHOTO, OnDblclkListPicturelist)

ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST_PHOTO, OnBegindragListPicturelist)
ON_NOTIFY(NM_CLICK, IDC_LIST_PHOTO, OnNMClickListPicturelist)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_PHOTO, OnNMCustomdrawListPicturelist)
ON_NOTIFY(NM_RCLICK, IDC_LIST_PHOTO, OnNMRclickListPicturelist)
ON_NOTIFY(LVN_BEGINSCROLL, IDC_LIST_PHOTO, &CWhriaViewDlg::OnLvnBeginScrollListPicturelist)
ON_NOTIFY(LVN_ENDSCROLL, IDC_LIST_PHOTO, &CWhriaViewDlg::OnLvnEndScrollListPicturelist)
//ON_WM_DROPFILES()
ON_WM_DROPFILES()


ON_COMMAND(ID_POPUP_LIST_COPY, &CWhriaViewDlg::OnPopupListCopy)
ON_COMMAND(ID_POPUP_LIST_TOEXCELFILE, &CWhriaViewDlg::OnPopupListToexcelfile)
ON_COMMAND(ID_POPUP_LIST_DELETE, &CWhriaViewDlg::OnPopupListDelete)
ON_WM_DESTROY()
ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_COMMENT, &CWhriaViewDlg::OnLvnEndlabeleditListComment)
ON_COMMAND(ID_POPUP_TREE_CREATE, &CWhriaViewDlg::OnPopupTreeCreate)
ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE_REMOTE, &CWhriaViewDlg::OnTvnEndlabeleditTreeRemote)
ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREE_REMOTE, &CWhriaViewDlg::OnTvnBeginlabeleditTreeRemote)
ON_COMMAND(ID_POPUP_RENAME, &CWhriaViewDlg::OnPopupRename)
ON_COMMAND(ID_POPUP_DELETE, &CWhriaViewDlg::OnPopupDelete)
ON_COMMAND(ID_POPUP_TOPOWERPOINT_TREE, &CWhriaViewDlg::OnPopupTopowerpointTree)
ON_COMMAND(ID_POPUP_TOPOWERPOINT_LIST, &CWhriaViewDlg::OnPopupTopowerpointList)
ON_WM_COPYDATA()
ON_COMMAND(ID_POPUP_LIST_RENAME, &CWhriaViewDlg::OnPopupListRename)
ON_COMMAND(ID_POPUP_TREE_UPLOAD, &CWhriaViewDlg::OnPopupTreeUpload)
ON_COMMAND(ID_POPUP_LIST_UPLOAD, &CWhriaViewDlg::OnPopupListUpload)
ON_NOTIFY(NM_CLICK, IDC_TREE_REMOTE, &CWhriaViewDlg::OnNMClickTreeRemote)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_COMMENT, &CWhriaViewDlg::OnHdnItemchangedListComment)
ON_COMMAND(ID_DIAGNOSIS_USERDIAGNOSIS, &CWhriaViewDlg::OnDiagnosisUserdiagnosis)
ON_COMMAND(ID_UPLOAD_UPLOADEX, &CWhriaViewDlg::OnUploadUploadex)
ON_STN_CLICKED(IDC_STATIC_F12, &CWhriaViewDlg::OnStnClickedStaticF12)
ON_EN_KILLFOCUS(IDC_EDIT_INPUT, &CWhriaViewDlg::OnEnKillfocusEditInput)
ON_COMMAND(ID_POPUP_DISSELECTALL, &CWhriaViewDlg::OnPopupDisselectall)
ON_LBN_DBLCLK(IDC_LIST_CHECKLIST, &CWhriaViewDlg::OnLbnDblclkListChecklist)
ON_COMMAND(ID_TOOL_REPORT, &CWhriaViewDlg::OnToolReport)
ON_COMMAND(ID_POPUP_TREE_REPORT, &CWhriaViewDlg::OnPopupTreeReport)
ON_WM_CTLCOLOR()
//ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWhriaViewDlg message handlers
BOOL CWhriaViewDlg::GetProcess(CString name)
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //현재 모든 프로세스들의 상태를 스냅
	PROCESSENTRY32 pe32;

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		exit(EXIT_FAILURE);
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap);
		exit(EXIT_FAILURE);
	}

	do {
		if (name.Compare(pe32.szExeFile) == 0)     //실행중인 프로세스가 있다면 
		{
			//MessageBox(pe32.szExeFile);
			return TRUE;
		}
	} while (Process32Next(hProcessSnap, &pe32));

	return FALSE;
}
BOOL CWhriaViewDlg::TerminateProcess(CString name)
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //현재 모든 프로세스들의 상태를 스냅
	PROCESSENTRY32 pe32;

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		exit(EXIT_FAILURE);
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap);
		exit(EXIT_FAILURE);
	}

	do {
		if (name.Compare(pe32.szExeFile) == 0)     //실행중인 프로세스가 있다면 
		{
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
			if (hProcess)
			{
				if (::TerminateProcess(hProcess, 0))
				{
					unsigned long nCode; //프로세스 종료 상태
					GetExitCodeProcess(hProcess, &nCode);
					CloseHandle(hProcess);
					return TRUE;
				}
				CloseHandle(hProcess);
			}
			return FALSE;

		}
	} while (Process32Next(hProcessSnap, &pe32));

	return FALSE;
}
BOOL CWhriaViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	// TODO: Add extra initialization here


	m_ViewDlg.Create(IDD_DIALOG_VIEWLOGO);
	m_ViewDlg.ShowWindow(SW_SHOW);

	// controls

	if (!AfxOleInit())
	{
		AfxMessageBox(_T("AfxOleInit Error!"));
		return FALSE;
	}

	m_DxListCtrl.Init();
	m_DxListCtrl.SetMode(); // default = _MODE_STANDARD_


	// Load Config

	config_.load();

#ifdef _DEBUG
	version_.increase_version(CLIENT_VERSION);
#endif


	// LOAD Assist

	if (config_.GetInt(RUN_ASSIST) == 1)
	{
		if (GetProcess(_T(ASSIST_APPLICATIONNAME)) == false)
		{
			if (MFile::ExistsL(_T(ASSIST_APPLICATIONNAME)))
			{
				ShellExecute(NULL, _T("open"), _T(ASSIST_APPLICATIONNAME), NULL, NULL, SW_MINIMIZE);
				bRunAssist = true;
			}
		}
	}

	// monitor


	CMonitors monitors;
	iMonitorCount=monitors.GetCount();
	if (iMonitorCount>5) iMonitorCount=5;

	CMonitor dumy = CMonitors::GetNearestMonitor(this);

	for ( int i = 0; i < iMonitorCount; i++ )
	{
		CIMAGEDISPLAY* imagedisplay_ptr;
		imagedisplay_ptr=new CIMAGEDISPLAY;
		ImageDisplay.push_back(imagedisplay_ptr);

		ImageDisplay[i]->bZoom=false;

		// ImageDisplay Initiation

		ImageDisplay[i]->Create(IDD_DIALOG_IMAGEDISPLAY);
		ImageDisplay[i]->m_parent=this;

		ImageDisplay[i]->monitor=monitors.GetMonitor( i );
		
		CRect rect;
		ImageDisplay[i]->monitor.GetMonitorRect( &rect );
		ImageDisplay[i]->MoveWindow(0,0,rect.Width(),rect.Height());


		ImageDisplay[i]->m_Zoom.MoveWindow(rect.Width()/2+90,rect.Height()-50,34,34);
		ImageDisplay[i]->m_Rotate.MoveWindow(rect.Width()/2+30,rect.Height()-50,34,34);
		ImageDisplay[i]->m_RotateReverse.MoveWindow(rect.Width()/2-10,rect.Height()-50,34,34);

		ImageDisplay[i]->m_Right.MoveWindow(rect.Width()/2-70,rect.Height()-50,34,34);
		ImageDisplay[i]->m_Left.MoveWindow(rect.Width()/2-110,rect.Height()-50,34,34);

		ImageDisplay[i]->m_NextBtn.MoveWindow(rect.Width()-100,10,34,34);
		ImageDisplay[i]->m_PrevBtn.MoveWindow(rect.Width()-140,10,34,34);

		ImageDisplay[i]->m_ClosedBtn.MoveWindow(rect.Width()-50, 10,34,34);

		if (iMonitorCount>1)
		{
			ImageDisplay[i]->m_PrevBtn.EnableWindow(true);
			ImageDisplay[i]->m_PrevBtn.ShowWindow(SW_SHOW);
			ImageDisplay[i]->m_NextBtn.EnableWindow(true);
			ImageDisplay[i]->m_NextBtn.ShowWindow(SW_SHOW);
		}
		else
		{
			ImageDisplay[i]->m_PrevBtn.EnableWindow(false);
			ImageDisplay[i]->m_PrevBtn.ShowWindow(SW_HIDE);
			ImageDisplay[i]->m_NextBtn.EnableWindow(false);
			ImageDisplay[i]->m_NextBtn.ShowWindow(SW_HIDE);
		}

	}


	// Checkmark
	
	m_ImageListCheck.Create(16,16,ILC_COLOR24|ILC_MASK,4,4);

	CBitmap bm;
	bm.LoadBitmap(IDB_BITMAP_CHECKMARK);
	m_ImageListCheck.Add(&bm,RGB(255,0,255));

	// m_picturelist 폰트 설정 font 생성

	//Create the Font
	LOGFONT lf = {0};
	lf.lfHeight = 17;
	lf.lfWeight = FW_NORMAL;
	
	_tcscpy(lf.lfFaceName,_T("Tahoma"));
	m_font.CreateFontIndirect(&lf);

	pListDC    = m_PictureList.GetDC();
	CFont *pOldFont = NULL;
	pOldFont = pListDC->SelectObject(&m_font);


	// ToolTipListCtrl
	m_PictureList.EnableToolTips(TRUE);
	m_PictureList.SetRedraw(TRUE);


	// 최대화

	CRect rect;
	CMonitor current_monitor= CMonitors::GetNearestMonitor(this);
	current_monitor.GetWorkAreaRect(&rect);
	MoveWindow(rect,0);
	ShowWindow(SW_MAXIMIZE);

	// thumbnail size process
	ProcessThumbnailSize();

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

	// View
	if (config_.Compare(VIEW_MODE,0))
		OnViewAdvanced();
	if (config_.Compare(VIEW_MODE,1))
		OnViewBasic();


	// CommentList 초기화
	
	RECT listRect;
	m_CommentList.GetClientRect(&listRect);
	int nListWidth = (listRect.right - listRect.left);
	int nVScrollBarWidth = ::GetSystemMetrics(SM_CXVSCROLL); 

	if (config_.server_config.Compare(MULTIUSER_SUPPORT,1))
	{
		m_CommentList.InsertColumn(0,_T(""),LVCFMT_LEFT, 25);
		m_CommentList.InsertColumn(1,_T("User"),LVCFMT_LEFT, 100);
		m_CommentList.InsertColumn(2,_T("Comment"),LVCFMT_LEFT, nListWidth-nVScrollBarWidth-125);
	}
	else
	{
		m_CommentList.InsertColumn(0,_T(""),LVCFMT_LEFT, 25);
		m_CommentList.InsertColumn(1,_T("User"),LVCFMT_LEFT, 0);
		m_CommentList.InsertColumn(2,_T("Comment"),LVCFMT_LEFT, nListWidth-nVScrollBarWidth-25);
	}

	m_CommentList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
    m_CommentList.SetExtendedStyle (LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);


	// 시작 초기화를 위한 타이머 작동

	SetTimer(1,500,NULL);

	// tooltip
	m_tooltip.Create(this);

	// Generated by XSuperTooltipTest on 2008 May 19

	{
	SUPER_TOOLTIP_INFO sti;

	sti.bSuperTooltip     = TRUE;
//	sti.nVirtualKeyCode   = VK_F1;						// zero if none
//	sti.nKeyCodeId        = <insert key code id here>;	// can be anything you want
	sti.nIDTool           = IDC_EDIT_INPUT;				// can be anything you want
	sti.nSizeX            = 212;
	sti.pWnd              = GetDlgItem(IDC_EDIT_INPUT);
	sti.strHeader         = _T("Search Box  [F12]");
	sti.bLineAfterHeader  = FALSE;
	sti.strBody           = 
		TransMsg(IDS_TOOLTIP1)
		;
	sti.rgbBegin          = RGB(255, 255, 255);
	sti.rgbMid            = RGB(242, 246, 251);
	sti.rgbEnd            = RGB(202, 218, 239);
	sti.rgbText           = RGB(76, 76, 76);

	CString strHtml = m_tooltip.AddTool(&sti);
	}

	// Generated by XSuperTooltipTest on 2008 May 19

	{
	SUPER_TOOLTIP_INFO sti;

	sti.bSuperTooltip     = TRUE;
//	sti.nVirtualKeyCode   = VK_F1;						// zero if none
//	sti.nKeyCodeId        = <insert key code id here>;	// can be anything you want
	sti.nIDTool           = IDC_EDIT_DX;				// can be anything you want
	sti.nSizeX            = 212;
	sti.pWnd              = GetDlgItem(IDC_EDIT_DX);
	sti.strHeader         = _T("Diagnosis");
	sti.bLineAfterHeader  = FALSE;
	sti.strBody           = 
		TransMsg(IDS_TOOLTIP2)
//		_T("[Diagnosis Keyword] + [Enter] will reteive the list of related diagnosises\n")
		;
	sti.rgbBegin          = RGB(255, 255, 255);
	sti.rgbMid            = RGB(242, 246, 251);
	sti.rgbEnd            = RGB(202, 218, 239);
	sti.rgbText           = RGB(76, 76, 76);

	CString strHtml = m_tooltip.AddTool(&sti);
	}

	// Generated by XSuperTooltipTest on 2008 May 19

	{
	SUPER_TOOLTIP_INFO sti;

	sti.bSuperTooltip     = TRUE;
//	sti.nVirtualKeyCode   = VK_F1;						// zero if none
//	sti.nKeyCodeId        = <insert key code id here>;	// can be anything you want
	sti.nIDTool           = IDC_LIST_COMMENT;				// can be anything you want
	sti.nSizeX            = 212;
	sti.pWnd              = GetDlgItem(IDC_LIST_COMMENT);
	sti.strHeader         = _T("Comment Box");
	sti.bLineAfterHeader  = FALSE;
	sti.strBody           = 
		TransMsg(IDS_TOOLTIP3)
//		_T("Comment box can store a list of comments. Comments will be saved and loaded as soon as you click photographies. The check box means [all selected]. If all the selected images have the same comment, then check box  will be checked\n")
		;
	sti.rgbBegin          = RGB(255, 255, 255);
	sti.rgbMid            = RGB(242, 246, 251);
	sti.rgbEnd            = RGB(202, 218, 239);
	sti.rgbText           = RGB(76, 76, 76);

	CString strHtml = m_tooltip.AddTool(&sti);
	}

	// Generated by XSuperTooltipTest on 2008 May 19

	{
	SUPER_TOOLTIP_INFO sti;

	sti.bSuperTooltip     = TRUE;
//	sti.nVirtualKeyCode   = VK_F1;						// zero if none
//	sti.nKeyCodeId        = <insert key code id here>;	// can be anything you want
	sti.nIDTool           = IDC_BUTTON_SUBMITTAG;				// can be anything you want
	sti.nSizeX            = 212;
	sti.pWnd              = GetDlgItem(IDC_BUTTON_SUBMITTAG);
	sti.strHeader         = _T("Submit Button");
	sti.bLineAfterHeader  = FALSE;
	sti.strBody           = 
		TransMsg(IDS_TOOLTIP4)
//		_T("To submit a diagnosis, patient ID, name and ICD code, click the button. It will rename the filename of all the selected image in respect of file informations. If you dont want to rename, go to [Preference] and uncheck [Automation]\n")
		;
	sti.rgbBegin          = RGB(255, 255, 255);
	sti.rgbMid            = RGB(242, 246, 251);
	sti.rgbEnd            = RGB(202, 218, 239);
	sti.rgbText           = RGB(76, 76, 76);

	CString strHtml = m_tooltip.AddTool(&sti);
	}


	{
	
	// Generated by XSuperTooltipTest on 2008 May 19

	SUPER_TOOLTIP_INFO sti;

	sti.bSuperTooltip     = TRUE;
//	sti.nVirtualKeyCode   = VK_F1;						// zero if none
//	sti.nKeyCodeId        = <insert key code id here>;	// can be anything you want
	sti.nIDTool           = IDC_EDIT_DATE;				// can be anything you want
	sti.nSizeX            = 212;
	sti.pWnd              = GetDlgItem(IDC_EDIT_DATE);
	sti.strHeader         = _T("Date of Photography");
	sti.bLineAfterHeader  = FALSE;
	sti.strBody           = 
		TransMsg(IDS_TOOLTIP5)
//		_T("EXIF metadata information of the date taken, It can not be edited\n")
		;
	sti.rgbBegin          = RGB(255, 255, 255);
	sti.rgbMid            = RGB(242, 246, 251);
	sti.rgbEnd            = RGB(202, 218, 239);
	sti.rgbText           = RGB(76, 76, 76);

	CString strHtml = m_tooltip.AddTool(&sti);

	}

	// F12 위치 조절
	CRect loc_, loc2_, newloc;
	GetDlgItem(IDC_EDIT_INPUT)->GetWindowRect(loc_);
	m_StaticF12.GetWindowRect(loc2_);
	newloc.left = loc_.left + loc_.Width() / 2 - loc2_.Width() / 2;
	newloc.right = newloc.left + loc2_.Width();
	newloc.top = 4;
	newloc.bottom = newloc.top + loc2_.Height()-4;
	m_StaticF12.MoveWindow(newloc);

	// Tree font
	cTreeFont.CreateFont(16,                     // 글자높이
		0,                     // 글자너비
		0,                      // 출력각도
		0,                      // 기준 선에서의각도
		FW_DONTCARE,              // 글자굵기
		FALSE,                  // Italic 적용여부
		FALSE,                  // 밑줄적용여부
		FALSE,                  // 취소선적용여부
		DEFAULT_CHARSET,       // 문자셋종류
		OUT_DEFAULT_PRECIS,    // 출력정밀도
		CLIP_DEFAULT_PRECIS,   // 클리핑정밀도
		DEFAULT_QUALITY,       // 출력문자품질
		DEFAULT_PITCH,         // 글꼴Pitch
		_T("Tahoma")           // 글꼴
	);
	m_FolderTree.SetFont(&cTreeFont);
//	m_FolderTree.SetAutoscrollInfo(30,5);
	
	m_Progress.SetWindowText(_T("... Log in ..."));


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWhriaViewDlg::InsertTooltip(int iControlID,const CString& stTitle,const CString& stMsg)
{
	SUPER_TOOLTIP_INFO sti;

	sti.bSuperTooltip     = TRUE;
	sti.nIDTool           = iControlID;				// can be anything you want
	sti.nSizeX            = 212;
	sti.pWnd              = GetDlgItem(iControlID);
	sti.strHeader         = stTitle;
	sti.bLineAfterHeader  = FALSE;
	sti.strBody           = stMsg;
	sti.rgbBegin          = RGB(255, 255, 255);
	sti.rgbMid            = RGB(242, 246, 251);
	sti.rgbEnd            = RGB(202, 218, 239);
	sti.rgbText           = RGB(76, 76, 76);
	
	m_tooltip.AddTool(&sti);
}


void CWhriaViewDlg::ProcessThumbnailSize()
{
	if (m_PictureList.GetSafeHwnd()) 
	{
		CRect rect;
		GetWindowRect(&rect);

		// thumnail 크기 계산

		int iNumColumn=1;
		while (((rect.Width()-210)/iNumColumn)>config_.server_config.GetInt(THUMB_WIDTH))
		{
			iNumColumn++;
		}
		iThumb_Width=(rect.Width()-210)/iNumColumn;
		iThumb_Height=iThumb_Width*config_.server_config.GetInt(THUMB_HEIGHT)/config_.server_config.GetInt(THUMB_WIDTH);

		// picturelist thumbnail

		m_PictureList.SetRect(iThumb_Width,iThumb_Height);

		if (m_ImageListThumb.GetSafeHandle())
			m_ImageListThumb.DeleteImageList();
		m_ImageListThumb.Create(iThumb_Width,iThumb_Height, ILC_COLOR24, 0, 1);

		m_PictureList.SetImageList(&m_ImageListThumb, LVSIL_NORMAL);
		// picturelist 아이콘 간격 , windows 10 때문에 width+3 이 없어졌음.
		m_PictureList.SetIconSpacing(iThumb_Width,iThumb_Height+25);


		if (m_PictureList.GetItemCount()>0)
			LoadPicture(m_SelectedImage,stCurrentPath);


	}
}

void CWhriaViewDlg::OnDblclkListPicturelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

//	OnNMClickListPicturelist(pNMHDR,pResult);
	*pResult = 0;

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	unsigned int iSelected=pNMListView->iItem;

	if (iSelected>=m_SelectedImage.size() || iSelected==-1) return;

	m_PictureList.SetCheckEx(iSelected,!m_PictureList.GetCheckEx(iSelected));

	// 다중 모니터

	int iCurrentMonitor=iLastDisplay;

//    iCurrentMonitor=GetCurrentMonitor();
	if (iMonitorCount>1 && ImageDisplay[iCurrentMonitor]->bImageOn)
	{
		int i;
		for (i=0;i<iMonitorCount;i++)
		{
			if (!ImageDisplay[i]->bImageOn)
				iCurrentMonitor=i;
		}
	}

	try
	{
		if (ImageLoad(m_SelectedImage[iSelected].GetNetPath().c_str(),&ImageDisplay[iCurrentMonitor]->image,false)==false)
		{
			m_Progress.SetWindowText(TransMsg(IDS_FILE_NOTEXIST));
			return;
		}
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}

	ImageDisplay[iCurrentMonitor]->Reset();

	ImageDisplay[iCurrentMonitor]->fileinfo_=m_SelectedImage[iSelected];
	ImageDisplay[iCurrentMonitor]->iDisplaySelected=iSelected;

	if (m_SelectedImage.size()>1)
	{
		ImageDisplay[iCurrentMonitor]->m_Left.EnableWindow(true);
		ImageDisplay[iCurrentMonitor]->m_Left.ShowWindow(SW_SHOW);
		ImageDisplay[iCurrentMonitor]->m_Right.EnableWindow(true);
		ImageDisplay[iCurrentMonitor]->m_Right.ShowWindow(SW_SHOW);
	}
	else
	{
		ImageDisplay[iCurrentMonitor]->m_Left.EnableWindow(false);
		ImageDisplay[iCurrentMonitor]->m_Left.ShowWindow(SW_HIDE);
		ImageDisplay[iCurrentMonitor]->m_Right.EnableWindow(false);
		ImageDisplay[iCurrentMonitor]->m_Right.ShowWindow(SW_HIDE);
	}

	ShowPictureMultiMon(iCurrentMonitor);

	ForwardPictureCache(iSelected);
}
void CWhriaViewDlg::ForwardPictureCache(int iIndex)
{
	try
	{
		iIndex++;
		if (iIndex>=(int)m_SelectedImage.size()) iIndex=0;
		WhriaClient.ForwardCache(m_SelectedImage[iIndex].GetNetPath());
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
}

int CWhriaViewDlg::GetCurrentMonitor()
{
	CPoint pt;
	::GetCursorPos(&pt);
	CMonitor current_monitor= CMonitors::GetNearestMonitor(pt);

	int i;
	for (i=0;i<iMonitorCount;i++)
	{
		if (ImageDisplay[i]->monitor==current_monitor) return i;
	}
	return 0;
}


void CWhriaViewDlg::SetAdvancedView()
{
	CMenu* mmenu = GetMenu();
	CMenu* submenu = mmenu->GetSubMenu(0);

	bAdvancedViewMode=true;

	submenu->CheckMenuItem(ID_VIEW_ADVANCED, MF_CHECKED);
	submenu->EnableMenuItem(ID_VIEW_ADVANCED, MF_GRAYED);
	submenu->CheckMenuItem(ID_VIEW_BASIC, MF_UNCHECKED);
	submenu->EnableMenuItem(ID_VIEW_BASIC, MF_ENABLED);

}
void CWhriaViewDlg::SetBasicView()
{
	CMenu* mmenu = GetMenu();
	CMenu* submenu = mmenu->GetSubMenu(0);

	bAdvancedViewMode=false;

	submenu->CheckMenuItem(ID_VIEW_BASIC, MF_CHECKED);
	submenu->EnableMenuItem(ID_VIEW_BASIC, MF_GRAYED);
	submenu->CheckMenuItem(ID_VIEW_ADVANCED, MF_UNCHECKED);
	submenu->EnableMenuItem(ID_VIEW_ADVANCED, MF_ENABLED);

}
void CWhriaViewDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		m_PictureList.StopNoBKDrawOnce();
		CAboutDlg dlgAbout(MCodeChanger::_CCL(config_.server_config.version_.Get(VERSION_FILE_VERSION)).c_str());
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.



// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWhriaViewDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CWhriaViewDlg::ProcessRotate(int iCurrentMonitor)
{
	if (config_.server_config.GetInt(SAVE_ROTATEIMAGE))
		boost::thread BuildThread(boost::bind(&CWhriaViewDlg::ProcessRotateThread,this
			,ImageDisplay[iCurrentMonitor]->iDisplaySelected
			,ImageDisplay[iCurrentMonitor]->iRotateAngle));
}
void CWhriaViewDlg::ProcessRotateThread(int iDisplaySelected,int iRotateAngle_Org)
{
	ThreadControl ThreadControl_(PROCESSIMAGE_THREAD);
	boost::mutex::scoped_lock lock(processimage_mutex);
	ThreadControl_.Check(&bMutexCheck_processimage);

	std::string stNetPath=m_SelectedImage[iDisplaySelected].GetNetPath();
	int iRotateAngle=iRotateAngle_Org % 4;

	if (iRotateAngle>0)
	{
		try
		{
			WhriaClient.image_rotate(stNetPath,iRotateAngle);
			CxImage thumb_image;
			if (ImageLoad(stNetPath,&thumb_image,true))
			{
				thumb_image.Thumbnail(iThumb_Width,iThumb_Height,border);
				HBITMAP hBitmap=thumb_image.MakeBitmap();
				CBitmap pImage;	
				pImage.Attach(hBitmap);
				m_ImageListThumb.Replace(iDisplaySelected, &pImage, NULL);
				m_PictureList.Invalidate(false);
			}
		}
		catch (const client_connection::ConnectionEx& err_)
		{
			ErrorExit(err_);
		}
		catch (const basic_client::ConnectionEx& err_)
		{
			ErrorExit(err_);
		}
	}
}

BOOL CWhriaViewDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (m_tooltip.RelayEvent(pMsg))
		return TRUE;

	
	if (pMsg->message == WM_REMOTESEARCH)
	{
/*		
		COPYDATASTRUCT*cds = (COPYDATASTRUCT*)pMsg->lParam;

		LPCTSTR lpszString = (LPCTSTR)(cds->lpData);
		TCHAR *temp = NULL;
		temp = (TCHAR*)(pMsg->lParam);
		tstring temp_ = temp;
		boost::algorithm::trim(temp_);
		if (_tcslen(temp_.c_str()) == 0) return TRUE;
		m_Input = temp_.c_str();
		UpdateData(FALSE);
		Search();
		return TRUE;
*/
	}

	if (pMsg->message == WM_IDLEPROCESS)
	{
		bIdleDoModal=true;

		for (unsigned int i=0;i<ImageDisplay.size();i++)
		{
			if (ImageDisplay[i]->bImageOn)
			{
				ProcessRotate(i);
				HidePictureMultiMon(i);
			}
		}

		OnPopupDisselectall();
		m_PictureList.ShowWindow(false);
		CViewLogo m_dlg(config_);
		m_dlg.bIdleStart=true;
		m_dlg.DoModal();
		bIdleDoModal=false;
		m_PictureList.ShowWindow(true);
	}

	if (pMsg->message == WM_CLICKPICTURE)
	{
		OnNMClickListPicturelist((unsigned int)pMsg->wParam);
		return TRUE;
	}
	if (pMsg->message == WM_AUTOCOMPLETE)
	{
		UpdateData(TRUE);
		userdx_list dx_list_temp1;
		CString LowerCaseDx=m_Dx;LowerCaseDx.MakeLower();
		DxDB_.Find((LPCTSTR)LowerCaseDx,dx_list_temp1);

		if (dx_list_temp1.size()>0)
		{
			m_ICD=MCodeChanger::_CCL(dx_list_temp1[0].stICD10).c_str();
			CDialog::UpdateData(FALSE);
			return TRUE;
		}

		userdx_list dx_list_temp2;
		try
		{
			WhriaClient.getuserdx(MCodeChanger::_CCU((LPCTSTR)LowerCaseDx),dx_list_temp2);
		}
		catch (const client_connection::ConnectionEx& err_)
		{
			ErrorExit(err_);
		}
		catch (const basic_client::ConnectionEx& err_)
		{
			ErrorExit(err_);
		}
		if (dx_list_temp2.size()>0)
		{
			m_ICD=MCodeChanger::_CCL(dx_list_temp2[0].stICD10).c_str();
			CDialog::UpdateData(FALSE);
			return TRUE;
		}

	}

	// TODO: Add your specialized code here and/or call the base class
	if( pMsg->message == WM_MOUSEWHEEL )    //스크롤 메세지가 발생했다면
	{
		if (GetFocus()==GetDlgItem(IDC_LIST_COMMENT))
		{
			m_CommentList.SendMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
			return TRUE;
		}

		while (bMutexCheck_picturelist==false)
		{
			Sleep(1);
					MSG msg;
					if(::GetMessage(&msg,NULL,NULL,NULL)) 
					{ 
						::TranslateMessage(&msg); 
						  ::DispatchMessage(&msg); 
					} 
		}
		bMutexCheck_picturelist=false;
		m_PictureList.StopNoBKDrawOnce();
		m_PictureList.SetRedraw(TRUE);
		m_PictureList.SendMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
		bMutexCheck_picturelist=true;
		return TRUE;
	}
	if (pMsg->message == WM_VSCROLL)
	{
		m_PictureList.StopNoBKDrawOnce();
		m_PictureList.SetRedraw(TRUE);
	}

	if(pMsg->message == WM_KEYDOWN)   // 키보드가 눌렸을때 처리
	{
		if (GetFocus()==GetDlgItem(IDC_EDIT_DATE))
			return TRUE;
		if(pMsg->wParam == 85 && ::GetKeyState(VK_CONTROL)<0) // 'u' 키
		{
			OnUploadUploadex();
			return TRUE;
		}

		if(pMsg->wParam == 65 && ::GetKeyState(VK_CONTROL)<0) // 'a' 키
		{
			m_PictureList.SetRedraw(FALSE);
			if (GetFocus()==GetDlgItem(IDC_LIST_PHOTO))
			{
				int i;
				for (i=0;i<m_PictureList.GetItemCount();i++)
				{
					SetPictureListCheck(i,true);
					DrawListItem(i,false,true,false);
				}
				UpdateDetails(false);
			}
			m_PictureList.SetRedraw(TRUE);
			return TRUE;
		}
		if(pMsg->wParam == 67 && ::GetKeyState(VK_CONTROL)<0) // ctrl-'c' 키
		{
			if (GetFocus()==GetDlgItem(IDC_TREE_REMOTE))
			{
				OnPopupTreeCreate();
				return TRUE;
			}
		}
		if(pMsg->wParam == 82 && ::GetKeyState(VK_CONTROL)<0) // ctrl-'r' 키
		{
			if (GetFocus()==GetDlgItem(IDC_LIST_PHOTO))
				OnPopupListRename();
			if (GetFocus()==GetDlgItem(IDC_TREE_REMOTE))
				OnPopupRename();
			return TRUE;
		}

		if(pMsg->wParam == 80 && ::GetKeyState(VK_CONTROL)<0) // ctrl-'p' 키
		{
			if (GetFocus()==GetDlgItem(IDC_LIST_PHOTO))
				OnPopupTopowerpointList();
			if (GetFocus()==GetDlgItem(IDC_TREE_REMOTE))
				OnPopupTopowerpointTree();
			return TRUE;
		}

		if(pMsg->wParam == 84 && ::GetKeyState(VK_CONTROL)<0) // ctrl-'t' 키
		{
			if (bAdvancedViewMode)
				OnViewBasic();
			else
				OnViewAdvanced();
			return TRUE;
		}

		if(pMsg->wParam == 68 && ::GetKeyState(VK_CONTROL)<0) // 'd' 키
		{
			if (GetFocus()==GetDlgItem(IDC_LIST_PHOTO))
				OnPopupListCopy();
			if (GetFocus()==GetDlgItem(IDC_TREE_REMOTE))
				OnPopupCopy();
			return TRUE;
		}

		if(pMsg->wParam == 69 && ::GetKeyState(VK_CONTROL)<0 && bAdvancedViewMode) // 'e' 키
		{
			GetDlgItem(IDC_EDIT_DX)->SetFocus();
			return TRUE;
		}

		if(pMsg->wParam == VK_ESCAPE)
		{
			OnPopupDisselectall();
			return TRUE;
		}
        
		if(pMsg->wParam == VK_SPACE)
		{
			int iCurrentMonitor=GetCurrentMonitor();

			int iCount=0;
			int iMonitorOn=iCurrentMonitor;

			for (int i=0;i<iMonitorCount;i++)
			{
				if (ImageDisplay[i]->bImageOn)
				{
					iCount++;
					iMonitorOn=i;
				}
			}

			if (iCount==1 
				&& GetFocus()==GetDlgItem(IDC_LIST_PHOTO)
				)
				iCurrentMonitor=iMonitorOn;

			if (!ImageDisplay[iCurrentMonitor]->bImageOn)
				return CDialog::PreTranslateMessage(pMsg);

			CRect rect;
			ImageDisplay[iCurrentMonitor]->monitor.GetMonitorRect( &rect );
			if ((int)ImageDisplay[iCurrentMonitor]->image.GetWidth() <= rect.Width()
				&& (int)ImageDisplay[iCurrentMonitor]->image.GetHeight() <= rect.Height())
				return CDialog::PreTranslateMessage(pMsg);

			if (ImageDisplay[iCurrentMonitor]->bImageOn==false) 
				return CDialog::PreTranslateMessage(pMsg);

			ImageDisplay[iCurrentMonitor]->bZoom=!ImageDisplay[iCurrentMonitor]->bZoom;

			CRect rect2;
			ImageDisplay[iCurrentMonitor]->monitor.GetMonitorRect( &rect2 );
			int nScreenWidth=rect2.Width();
			int nScreenHeight=rect2.Height();
			ImageDisplay[iCurrentMonitor]->pZoomPoint.x=(int)(nScreenWidth/2);
			ImageDisplay[iCurrentMonitor]->pZoomPoint.y=(int)(nScreenHeight/2);

			ImageDisplay[iCurrentMonitor]->Invalidate(FALSE);

			return CDialog::PreTranslateMessage(pMsg);

		}

		if(pMsg->wParam == VK_PRIOR)
		{
			int iCurrentMonitor=GetCurrentMonitor();
			int iCount=0;
			int iMonitorOn=iCurrentMonitor;

			for (int i=0;i<iMonitorCount;i++)
			{
				if (ImageDisplay[i]->bImageOn)
				{
					iCount++;
					iMonitorOn=i;
				}
			}
			if (iCount==1)
				iCurrentMonitor=iMonitorOn;

			int iMoveToMonitor;

			if (ImageDisplay[iCurrentMonitor]->bImageOn==false || iMonitorCount<2) 
			{
				m_PictureList.SendMessage(WM_VSCROLL,SB_PAGEUP,0);
				return TRUE;
			}
			
			iMoveToMonitor=iCurrentMonitor+1;
			if (iMoveToMonitor>=iMonitorCount) iMoveToMonitor=0;

			ImageDisplay[iMoveToMonitor]->bZoom=ImageDisplay[iCurrentMonitor]->bZoom;
			ImageDisplay[iMoveToMonitor]->pZoomPoint=ImageDisplay[iCurrentMonitor]->pZoomPoint;
			ImageDisplay[iMoveToMonitor]->image=ImageDisplay[iCurrentMonitor]->image;
			ImageDisplay[iMoveToMonitor]->fileinfo_=ImageDisplay[iCurrentMonitor]->fileinfo_;
			ImageDisplay[iMoveToMonitor]->iDisplaySelected=ImageDisplay[iCurrentMonitor]->iDisplaySelected;
			ImageDisplay[iMoveToMonitor]->iRotateAngle=ImageDisplay[iCurrentMonitor]->iRotateAngle;


			// 현재 모니터 지우고

			HidePictureMultiMon(iCurrentMonitor);
	
			// 새 모니터 그리고

			ShowPictureMultiMon(iMoveToMonitor);

			
			return TRUE;
		}

		if(pMsg->wParam == VK_NEXT)
		{

			int iCurrentMonitor=GetCurrentMonitor();
			int iMoveToMonitor;

			int iCount=0;
			int iMonitorOn=iCurrentMonitor;

			for (int i=0;i<iMonitorCount;i++)
			{
				if (ImageDisplay[i]->bImageOn)
				{
					iCount++;
					iMonitorOn=i;
				}
			}
			if (iCount==1)
				iCurrentMonitor=iMonitorOn;


			if (ImageDisplay[iCurrentMonitor]->bImageOn==false || iMonitorCount<2) 
			{
				m_PictureList.SendMessage(WM_VSCROLL,SB_PAGEDOWN,0);
				return TRUE;
			}
	
			iMoveToMonitor=iCurrentMonitor-1;
			if (iMoveToMonitor<0) iMoveToMonitor=iMonitorCount-1;

			ImageDisplay[iMoveToMonitor]->bZoom=ImageDisplay[iCurrentMonitor]->bZoom;
			ImageDisplay[iMoveToMonitor]->pZoomPoint=ImageDisplay[iCurrentMonitor]->pZoomPoint;
			ImageDisplay[iMoveToMonitor]->image=ImageDisplay[iCurrentMonitor]->image;
			ImageDisplay[iMoveToMonitor]->fileinfo_=ImageDisplay[iCurrentMonitor]->fileinfo_;
			ImageDisplay[iMoveToMonitor]->iDisplaySelected=ImageDisplay[iCurrentMonitor]->iDisplaySelected;
			ImageDisplay[iMoveToMonitor]->iRotateAngle=ImageDisplay[iCurrentMonitor]->iRotateAngle;

			// 현재 모니터 지우고
		
			HidePictureMultiMon(iCurrentMonitor);

			// 새 모니터 그리고
			ShowPictureMultiMon(iMoveToMonitor);

			
			return TRUE;
		} 

		if (pMsg->wParam == VK_LEFT)
		{
			int iCurrentMonitor=GetCurrentMonitor();

			int iCount=0;
			int iMonitorOn=iCurrentMonitor;

			for (int i=0;i<iMonitorCount;i++)
			{
				if (ImageDisplay[i]->bImageOn)
				{
					iCount++;
					iMonitorOn=i;
				}
			}
			if (iCount==1)
				iCurrentMonitor=iMonitorOn;


			if (!ImageDisplay[iCurrentMonitor]->bImageOn)
				return CDialog::PreTranslateMessage(pMsg);

			if (m_SelectedImage.size()<2)
				return TRUE;

			int iDisplaySelected=ImageDisplay[iCurrentMonitor]->iDisplaySelected;
			iDisplaySelected--;
			if (iDisplaySelected<0)
				iDisplaySelected=m_SelectedImage.size()-1;

			try
			{
				if (ImageLoad(m_SelectedImage[iDisplaySelected].stNetPath.c_str(),&ImageDisplay[iCurrentMonitor]->image,false)==false)
				{
//					PostMessage(WM_KEYDOWN,VK_LEFT,0);
					return TRUE;
				}
			}
			catch (const client_connection::ConnectionEx& err_)
			{
				ErrorExit(err_);
			}
			catch (const basic_client::ConnectionEx& err_)
			{
				ErrorExit(err_);
			}

			ProcessRotate(iCurrentMonitor);
			ImageDisplay[iCurrentMonitor]->Reset();

			ImageDisplay[iCurrentMonitor]->iDisplaySelected=iDisplaySelected;

			if (m_SelectedImage.size()>1)
			{
				ImageDisplay[iCurrentMonitor]->m_Left.EnableWindow(true);
				ImageDisplay[iCurrentMonitor]->m_Left.ShowWindow(SW_SHOW);
				ImageDisplay[iCurrentMonitor]->m_Right.EnableWindow(true);
				ImageDisplay[iCurrentMonitor]->m_Right.ShowWindow(SW_SHOW);
			}
			else
			{
				ImageDisplay[iCurrentMonitor]->m_Left.EnableWindow(false);
				ImageDisplay[iCurrentMonitor]->m_Left.ShowWindow(SW_HIDE);
				ImageDisplay[iCurrentMonitor]->m_Right.EnableWindow(false);
				ImageDisplay[iCurrentMonitor]->m_Right.ShowWindow(SW_HIDE);
			}

			ImageDisplay[iCurrentMonitor]->fileinfo_=m_SelectedImage[ImageDisplay[iCurrentMonitor]->iDisplaySelected];
			ShowPictureMultiMon2(iCurrentMonitor);

			return TRUE;
		}


		if (pMsg->wParam == VK_RIGHT)
		{
			int iCurrentMonitor=GetCurrentMonitor();

			int iCount=0;
			int iMonitorOn=iCurrentMonitor;

			for (int i=0;i<iMonitorCount;i++)
			{
				if (ImageDisplay[i]->bImageOn)
				{
					iCount++;
					iMonitorOn=i;
				}
			}
			if (iCount==1)
				iCurrentMonitor=iMonitorOn;

			if (!ImageDisplay[iCurrentMonitor]->bImageOn)
				return CDialog::PreTranslateMessage(pMsg);

			if (m_SelectedImage.size()<2)
				return TRUE;

			int iDisplaySelected=ImageDisplay[iCurrentMonitor]->iDisplaySelected;
			iDisplaySelected++;
			if (iDisplaySelected>=(int)m_SelectedImage.size())
				iDisplaySelected=0;

			try
			{
				if (ImageLoad(m_SelectedImage[iDisplaySelected].stNetPath.c_str(),&ImageDisplay[iCurrentMonitor]->image,false)==false)
				{
//					PostMessage(WM_KEYDOWN,VK_LEFT,0);
					return TRUE;
				}
			}
			catch (const client_connection::ConnectionEx& err_)
			{
				ErrorExit(err_);
			}
			catch (const basic_client::ConnectionEx& err_)
			{
				ErrorExit(err_);
			}

			ProcessRotate(iCurrentMonitor);
			ImageDisplay[iCurrentMonitor]->Reset();

			ImageDisplay[iCurrentMonitor]->iDisplaySelected=iDisplaySelected;

			if (m_SelectedImage.size()>1)
			{
				ImageDisplay[iCurrentMonitor]->m_Left.EnableWindow(true);
				ImageDisplay[iCurrentMonitor]->m_Left.ShowWindow(SW_SHOW);
				ImageDisplay[iCurrentMonitor]->m_Right.EnableWindow(true);
				ImageDisplay[iCurrentMonitor]->m_Right.ShowWindow(SW_SHOW);
			}
			else
			{
				ImageDisplay[iCurrentMonitor]->m_Left.EnableWindow(false);
				ImageDisplay[iCurrentMonitor]->m_Left.ShowWindow(SW_HIDE);
				ImageDisplay[iCurrentMonitor]->m_Right.EnableWindow(false);
				ImageDisplay[iCurrentMonitor]->m_Right.ShowWindow(SW_HIDE);
			}

			ImageDisplay[iCurrentMonitor]->fileinfo_=m_SelectedImage[ImageDisplay[iCurrentMonitor]->iDisplaySelected];
			ShowPictureMultiMon2(iCurrentMonitor);

			ForwardPictureCache(ImageDisplay[iCurrentMonitor]->iDisplaySelected);

			return TRUE;
		}

		if(pMsg->wParam == 13) // VK_ENTER
		{
			if (GetFocus()==GetDlgItem(IDC_EDIT_INPUT))
			{
				Search();
				return TRUE;
			}

			else if (GetFocus()==GetDlgItem(IDC_EDIT_DX))
			{
				UpdateData(TRUE);

				if (m_Dx.GetLength()<4)
					return TRUE;

				diagnosis diagnosis_;
				CSelectDiagnosisList m_dlg(WhriaClient,config_,DxDB_,diagnosis_,m_Dx);
				m_PictureList.StopNoBKDrawOnce();
				m_dlg.DoModal();

				m_ICD=MCodeChanger::_CCL(diagnosis_.stICD10).c_str();

				CString cstDxTemp=MCodeChanger::_CCL(diagnosis_.stDiagnosis).c_str();
				if (cstDxTemp.GetLength()>0)
				{
					CString dumy=cstDxTemp.Left(1);
					dumy.MakeUpper();
					m_Dx=dumy+cstDxTemp.Mid(1);

				}

				UpdateData(FALSE);
				return TRUE;
			}

			return TRUE;
		}
		if(pMsg->wParam == VK_F12)
		{
			UpdateData(TRUE);
			m_Input=_T("");
			UpdateData(FALSE);
			GetDlgItem(IDC_EDIT_INPUT)->SetFocus();
			return TRUE;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CWhriaViewDlg::Search()
{
	UpdateData(true);
	stSearch=m_Input;
//	m_CEditSearch.AddSearchString(stSearch);
	 
	if (stSearch.IsEmpty())
		return false;
		// 영문 2문자 이상 입력
	if (stSearch.GetLength()<2) 
	{
		m_Progress.SetWindowText(TransMsg(IDS_SHORT_KEYWORD));
///		MessageBeep(MB_ICONASTERISK); // 따랑
//		MessageBeep(MB_ICONEXCLAMATION); // 확인
		MessageBeep(MB_ICONHAND); // 정말 에러
//		MessageBeep(MB_OK); // 종료
		return FALSE;
	}

	// 단축어
	std::vector<tstring> split_vec;
	tstring temp = stSearch;
	boost::split(split_vec, temp, boost::is_any_of(_T(" ")));
	stSearch = _T("");
	for (int i = 0; i < split_vec.size(); i++)
	{
		tstring org_str = split_vec[i];
		boost::algorithm::to_lower(split_vec[i]);
		if (_tcscmp(split_vec[i].c_str(),_T("1y"))==0)
		{
			boost::gregorian::date from(boost::gregorian::day_clock::local_day());
			stSearch.Format(_T("%s %d[<]"), stSearch, from.year() - 1);
		}
		else if (_tcscmp(split_vec[i].c_str(), _T("2y")) == 0)
		{
			boost::gregorian::date from(boost::gregorian::day_clock::local_day());
			stSearch.Format(_T("%s %d[<]"), stSearch, from.year() - 2);
		}
		else if (_tcscmp(split_vec[i].c_str(), _T("3y")) == 0)
		{
			boost::gregorian::date from(boost::gregorian::day_clock::local_day());
			stSearch.Format(_T("%s %d[<]"), stSearch, from.year() - 3);
		}
		if (_tcscmp(split_vec[i].c_str(), _T("4y")) == 0)
		{
			boost::gregorian::date from(boost::gregorian::day_clock::local_day());
			stSearch.Format(_T("%s %d[<]"), stSearch, from.year() - 4);
		}
		if (_tcscmp(split_vec[i].c_str(), _T("5y")) == 0)
		{
			boost::gregorian::date from(boost::gregorian::day_clock::local_day());
			stSearch.Format(_T("%s %d[<]"), stSearch, from.year() - 5);
		}
		else if (_tcscmp(split_vec[i].c_str(), _T("and")) == 0)
		{
			stSearch += _T(" AND");
		}
		else if (_tcscmp(split_vec[i].c_str(), _T("or")) == 0)
		{
			stSearch += _T(" OR");
		}
		else
		{
			stSearch += _T(" ");
			stSearch += org_str.c_str();
		}
	}
	stSearch.Trim();



	stPrevSearch=stSearch;

	fileinfo_list result_fileinfo,result_comment;

	if (!config_.Compare(SEARCH_ID,1) &&
		!config_.Compare(SEARCH_NAME,1) &&
		!config_.Compare(SEARCH_PATH,1) &&
		!config_.Compare(SEARCH_DIAGNOSIS,1) &&
		!config_.Compare(SEARCH_COMMENT,1) &&
		!config_.Compare(SEARCH_ICD10,1))
		config_.Set(SEARCH_PATH,1);

	try
	{

		std::vector<bool> bMask;
	  bMask.push_back((bool)config_.Compare(SEARCH_PATH,1));
	  bMask.push_back((bool)config_.Compare(SEARCH_ID,1));
	  bMask.push_back((bool)config_.Compare(SEARCH_NAME,1));
	  bMask.push_back((bool)config_.Compare(SEARCH_DIAGNOSIS,1));
	  bMask.push_back((bool)config_.Compare(SEARCH_ICD10,1));
		std::string stKeyword=MCodeChanger::_CCU((LPCTSTR)stSearch);

		WhriaClient.searchfile_by_query(stKeyword,bMask,result_fileinfo);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}

	if ((result_fileinfo.size()+result_comment.size())==0) 
	{
		m_Progress.SetWindowText(_T("No Result : Keyword[ ")+stSearch+_T(" ] "));
		m_Progress.Invalidate(false);
//		UpdateData(false);
//		MessageBeep(MB_ICONASTERISK); // 따랑
//		MessageBeep(MB_ICONEXCLAMATION); // 확인
//		MessageBeep(MB_ICONHAND); // 정말 에러
//		MessageBeep(MB_OK); // 종료
		return FALSE;
	}

	// 중복되는것 지우기
	fileinfo_list fileinfo_final;
	Utility::DeleteDup_by_NetPath(result_fileinfo,result_comment,fileinfo_final);

	UpdateData_FileInfo(fileinfo(),false);

	std::sort(fileinfo_final.begin(),fileinfo_final.end(),sort_fileinfo_by_Time());

	LoadPicture(fileinfo_final,"");
	return true;
}


void CWhriaViewDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

//		MessageBeep(MB_ICONASTERISK); // 따랑
	MessageBeep(MB_ICONEXCLAMATION); // 확인
//		MessageBeep(MB_ICONHAND); // 정말 에러
//		MessageBeep(MB_OK); // 종료
 
//	OnButtonStop();
//	DxDB_.Stop();

	if (MessageBox(TransMsg(IDS_EXIT),_T("Exit"),MB_YESNO)!=IDYES)
		return;
	Exit();
//	CDialog::OnClose();
}
void CWhriaViewDlg::ErrorExit(const client_connection::ConnectionEx& err_)
{
	MessageBeep(MB_ICONHAND); // 확인

	// 다운되어서 다른 방식으로 종료
//	Exit();

	bExitFlag=true;
	AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());

	config_.save();

	if (pListDC->GetSafeHdc())
		ReleaseDC(pListDC);

	if (GetSafeHwnd())
		EndDialog(0); 
}
void CWhriaViewDlg::ErrorExit(const basic_client::ConnectionEx& err_)
{
	MessageBeep(MB_ICONHAND); // 확인

	m_Progress.SetWindowText(MCodeChanger::_CCW(err_.stMessage).c_str());
}

void CWhriaViewDlg::Exit()
{
	bExitFlag=true;

	StopAll();

	// Comment
//	boost::mutex::scoped_lock lock(comment_mutex);


	// Server
//	if (server_!=NULL)
//		server_->stop();

	// DxDB
//	DxDB_.Stop();

	config_.save();

	if (pListDC->GetSafeHdc())
		ReleaseDC(pListDC);

	if (GetSafeHwnd())
		EndDialog(0); 
}

void CWhriaViewDlg::SetButtonStopStatus()
{
//	if (bTerminateLoadingThread)
//		GetDlgItem(IDC_BUTTON_STOP)->SetWindowText(_T("&Resume"));
//	else
		GetDlgItem(IDC_BUTTON_STOP)->SetWindowText(_T("&Stop"));
}

void CWhriaViewDlg::StopThread(bool* bStopSign,bool* bMutexCheck)
{
	*bStopSign=true;
	StopThread(bMutexCheck);
	*bStopSign=false;
}
void CWhriaViewDlg::StopThread(bool* bMutexCheck)
{
	int iCount=0;
	while (*bMutexCheck==false && iCount<50)
	{
		MSG msg;
		if(::GetMessage(&msg,NULL,NULL,NULL)) 
		{ 
			::TranslateMessage(&msg);
			::DispatchMessage(&msg); 
		} 
		iCount++;
		Sleep(10);
	}
}
void CWhriaViewDlg::StopLoadingThread()
{
	StopThread(&bTerminateLoadingThread,&bMutexCheck_thread);

/*	bTerminateLoadingThread=true;
	while (bMutexCheck_thread==false)
	{
		MSG msg;
		if(::GetMessage(&msg,NULL,NULL,NULL)) 
		{ 
			::TranslateMessage(&msg); 
			  ::DispatchMessage(&msg); 
		} 
	}*/
}
void CWhriaViewDlg::StopBrowseThread()
{
	StopThread(&bTerminateBrowseThread,&bMutexCheck_browse);
/*
	bTerminateBrowseThread=true;
	while (bMutexCheck_browse==false)
	{
		MSG msg;
		if(::GetMessage(&msg,NULL,NULL,NULL)) 
		{ 
			::TranslateMessage(&msg); 
			  ::DispatchMessage(&msg); 
		} 
	}
	*/
}

void CWhriaViewDlg::StopDxDBThread()
{
	StopThread(&DxDB_.bTerminate,&DxDB_.bCheckTerminate);
	StopThread(&bTerminateDxDBThread,&bMutexCheck_dxdb);
}
void CWhriaViewDlg::StopImageProcessThread()
{
	StopThread(&bMutexCheck_processimage);

/*	while (bMutexCheck_comment==false)
	{
		MSG msg;
		if(::GetMessage(&msg,NULL,NULL,NULL)) 
		{ 
			::TranslateMessage(&msg); 
			  ::DispatchMessage(&msg); 
		} 
	}*/
}
void CWhriaViewDlg::StopCommentThread()
{
	StopThread(&bMutexCheck_comment);
}
void CWhriaViewDlg::StopIdleSignalThread()
{
	StopThread(&bTerminateConnectionThread,&bMutexCheck_connection);
}


void CWhriaViewDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	StopLoadingThread();

	//	SetButtonStopStatus(); 
//	WhriaClient.stop();
//	boost::mutex::scoped_lock lock(thread_mutex);
}

BOOL CWhriaViewDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

//	OnSysCommand(IDM_ABOUTBOX,0);
	return CDialog::DestroyWindow();
}

int CWhriaViewDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	return 0;
}
void CWhriaViewDlg::LoadDxDB()
{
	m_Progress.SetWindowText(_T("Loading... : Diagnosis Codes"));
	boost::thread LoadDxDBThread(boost::bind(&CWhriaViewDlg::LoadDxDBThread,this));
}
void CWhriaViewDlg::ReLoadDxDB()
{
	m_Progress.SetWindowText(_T("ReLoading... : Diagnosis Codes"));
	boost::thread ReLoadDxDBThread(boost::bind(&CWhriaViewDlg::ReLoadDxDBThread,this));
}
void CWhriaViewDlg::LoadDxDBThread()
{
	ThreadControl ThreadControl_(LOAD_DXDB_THREAD_WRAPPER);
	boost::mutex::scoped_lock lock(dxdb_mutex);
	if (!ThreadControl_.Check(&bMutexCheck_dxdb)) return;
	bTerminateDxDBThread=false;

	param_list param_list_;
	config_.SplitParams(LOAD_DXCODE_LIST,param_list_);
	for (unsigned int i=0;i<param_list_.size();i++)
	{
		_tpath db_path=bfs::initial_path<_tpath>();
		db_path = Utility::refinepath(db_path / _T("diagnosis") / MCodeChanger::_CCL(param_list_[i]));
		if (!DxDB_.LoadDB(db_path.c_str()))
		{
			if (m_Progress.GetSafeHwnd())
			m_Progress.SetWindowText(_T("Fail to load dignosis code database : ") + CString(db_path.c_str()));
		}
	}
	
	userdx_list userdx_list_;
	try
	{
		WhriaClient.getuserdx("",userdx_list_);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}

	for (unsigned int i=0;i<userdx_list_.size();i++)
	{
		CString cstDiagnosis=MCodeChanger::_CCL(userdx_list_[i].stDiagnosis).c_str();
		if (!cstDiagnosis.IsEmpty())
		{
			CString temp=cstDiagnosis.Left(1);temp.MakeUpper();
			cstDiagnosis=temp+cstDiagnosis.Mid(1);
			m_DxListCtrl.AddSearchString(cstDiagnosis);
		}
		if (bTerminateDxDBThread) 
			return;
	}
	for (unsigned int i=0;i<DxDB_.GetSize();i++)
	{
		CString cstDiagnosis=MCodeChanger::_CCL(DxDB_.GetAt(i).stDiagnosis).c_str();
		if (!cstDiagnosis.IsEmpty())
		{
			CString temp=cstDiagnosis.Left(1);temp.MakeUpper();
			cstDiagnosis=temp+cstDiagnosis.Mid(1);
			m_DxListCtrl.AddSearchString(cstDiagnosis);
		}

		if (bTerminateDxDBThread) 
			return;
	}
	

	if (m_Progress.GetSafeHwnd())
	m_Progress.SetWindowText(_T("Finished to Load Diagnosis Database"));
}
void CWhriaViewDlg::ReLoadDxDBThread()
{
	ThreadControl ThreadControl_(LOAD_DXDB_THREAD_WRAPPER);
	boost::mutex::scoped_lock lock(dxdb_mutex);
	if (!ThreadControl_.Check(&bMutexCheck_dxdb)) return;
	bTerminateDxDBThread=false;

	param_list param_list_;
	config_.SplitParams(LOAD_DXCODE_LIST,param_list_);
	DxDB_.Clear();
	for (unsigned int i=0;i<param_list_.size();i++)
	{
		_tpath db_path=bfs::initial_path<_tpath>();
		db_path = Utility::refinepath(db_path / _T("diagnosis") / MCodeChanger::_CCL(param_list_[i]));
		if (!DxDB_.LoadDB(db_path.c_str()))
		{
			if (m_Progress.GetSafeHwnd())
			m_Progress.SetWindowText(_T("Fail to reload diagnosis code database : ") + CString(db_path.c_str()));
		}
	}

	userdx_list userdx_list_;
	try
	{
		WhriaClient.getuserdx("",userdx_list_);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}

	m_DxListCtrl.ResetContent();
	for (unsigned int i=0;i<userdx_list_.size();i++)
	{
		CString cstDiagnosis=MCodeChanger::_CCL(userdx_list_[i].stDiagnosis).c_str();
		if (!cstDiagnosis.IsEmpty())
		{
			CString temp=cstDiagnosis.Left(1);temp.MakeUpper();
			cstDiagnosis=temp+cstDiagnosis.Mid(1);
			m_DxListCtrl.AddSearchString(cstDiagnosis);
		}
		if (bTerminateDxDBThread) 
			return;
	}
	for (unsigned int i=0;i<DxDB_.GetSize();i++)
	{
		CString cstDiagnosis=MCodeChanger::_CCL(DxDB_.GetAt(i).stDiagnosis).c_str();
		if (!cstDiagnosis.IsEmpty())
		{
			CString temp=cstDiagnosis.Left(1);temp.MakeUpper();
			cstDiagnosis=temp+cstDiagnosis.Mid(1);
			m_DxListCtrl.AddSearchString(cstDiagnosis);
		}

		if (bTerminateDxDBThread) 
			return;
	}	
	if (m_Progress.GetSafeHwnd())
	m_Progress.SetWindowText(_T("Finished to ReLoad Diagnosis Database"));
}



void CWhriaViewDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	switch (nIDEvent)
	{
	case 1:

	// 중복 시작 막기 위해서
	
	KillTimer(1);

	GetDlgItem(IDC_EDIT_INPUT)->SetFocus();


	// Configuration Loading

	TCHAR dumy[300];
	GetCurrentDirectory(300,dumy);

	CString text=_T("Trying to login : ");
	text+=config_.Get(LAST_HOST_ADDRESS).c_str();
	m_Progress.SetWindowText(text);

	int iCount=0;
	while (Login(config_.Get(LAST_HOST_ADDRESS),config_.Get(CLIENT_PORT),config_.Get(LAST_USER_ID),config_.Get(LAST_USER_PASSWD))==false)
	{
		m_ViewDlg.ShowWindow(SW_HIDE);

		iCount++;

		if (iCount>1)
		{
			MessageBox(TransMsg(IDS_SERVERNONRESPONSE));
		}
		if (iCount>3)
		{
			KillTimer(1);
			Exit();
			return;
		}
		if (m_dlg_inputserver.DoModal()==IDCANCEL)
		{
			KillTimer(1);
			Exit();
			return;
		}
	}

	CurrentUser.stUserID=config_.Get(LAST_USER_ID);

	// SetCurrentDirectory

	CString stPath=GetCommandLine();
	_tpath temp_path((LPCTSTR)stPath);
	SetCurrentDirectory(temp_path.parent_path().c_str());

	// Update Check

	version_.load();



	bool bSucceedUpdate=true;
	bool bNeedRestart=false;

	try
	{

		version_checker version_new_(config_.log);
		WhriaClient.get_version(version_new_);

		bool bSame=true;

		for (int i=0;i<version_new_.GetSize();i++)
		{
			if(strcmp(version_.Get(i).c_str(),version_new_.Get(i).c_str())!=0)
			{
				bSame=false;
				break;
			}
		}
#ifndef _DEBUG
		if (!bSame)
		{
			CProgressDialog m_dlg(WhriaClient,config_);
			m_dlg.UpdateApp(version_,version_new_,bNeedRestart,bSucceedUpdate);
			m_dlg.DoModal();

//			if (!bSucceedUpdate)
//				version_.save();
			if (!bSucceedUpdate)
			{
				version_.save();
				Exit();return;
			}

			if (bNeedRestart)
			{
				m_Progress.SetWindowText(_T("Update complete. Restarting Application"));
				ShellExecute(NULL, _T("open"), MCodeChanger::_CCL(config_.server_config.version_.Get(CLIENT_APP_NAME)).c_str(), NULL, NULL, SW_SHOWNORMAL);
				Exit();
				return;
			}
		}
#endif

	}
	catch (const client_connection::ConnectionEx& err_)
	{
		MessageBeep(MB_ICONHAND);
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
		Exit();return;
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		MessageBeep(MB_ICONHAND);
		AfxMessageBox(MCodeChanger::_CCW(err_.stMessage).c_str());
		Exit();return;
	}
	catch(...)
	{
		MessageBeep(MB_ICONHAND);
		Exit();return;
	}
	
	// Loading DxDB 
	LoadDxDB();

	// 트리 이미지 로딩

	CWhriaViewApp *App=(CWhriaViewApp*)AfxGetApp();

	m_smTreeImg.Create(16,16,ILC_COLOR8,0,0);
	m_smTreeImg.Add(App->LoadIcon(IDI_ICON_OPEN));
	m_smTreeImg.Add(App->LoadIcon(IDI_ICON_CLOSED));

	// 트리 아이콘 없애고 대신 크게...
//	m_FolderTree.SetImageList(&m_smTreeImg,TVSIL_NORMAL);

	// TreeImage 로딩

	m_Progress.SetWindowText(_T("Loading... : Trying to get the list of files"));
	

	try
	{
		WhriaClient.getvollist(vol_list_);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		m_ViewDlg.ShowWindow(SW_HIDE);
		ErrorExit(err_);
		return;
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		m_ViewDlg.ShowWindow(SW_HIDE);
		ErrorExit(err_);
		return;
	}


	HTREEITEM pTree;
	for (unsigned int i=0;i<vol_list_.size();i++)
	{
		TV_INSERTSTRUCT TI;
		TI.hInsertAfter=TVI_SORT;
		TI.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;

		TI.hParent=0;
		TI.item.iImage=1;
		TI.item.iSelectedImage=0;

		TCHAR buff[256];
		_tcscpy_s(buff,255,MCodeChanger::_CCL(vol_list_[i]).c_str());
		TI.item.pszText=buff;

		pTree=m_FolderTree.InsertItem(&TI);
	}

	if (vol_list_.size()==0)
	{
		m_Progress.SetWindowText(_T("No Files."));
	}
	else
	{
		UpdateData_FileInfo(fileinfo(),false);
		bTerminateBrowseThread=true;
		bTerminateLoadingThread=true;
		boost::thread LoadThread(boost::bind(&CWhriaViewDlg::BrowseTree,this,pTree));
	}
	KillTimer(1);


	boost::thread BuildThread(boost::bind(&CWhriaViewDlg::Hide_Logo_Thread_Delay,this));
	break;
	}

	boost::thread LoadThread(boost::bind(&CWhriaViewDlg::CheckIdleThread,this));

	CDialog::OnTimer(nIDEvent);
}


void CWhriaViewDlg::ConnectionThread()
{
	ThreadControl ThreadControl_(IDLESIGNAL_THREAD);
	boost::mutex::scoped_lock lock(connection_mutex);
	if (!ThreadControl_.Check(&bMutexCheck_connection))
		return;
	bMutexCheck_connection=false;

	while (bTerminateConnectionThread==false)
	{
		Sleep(600000);
		try
		{
			if (bTerminateConnectionThread==false)
				WhriaClient.idlesignal();
		}
		catch (const client_connection::ConnectionEx& err_)
		{
			ErrorExit(err_);
			return;
		}
		catch (const basic_client::ConnectionEx& err_)
		{
			ErrorExit(err_);
			return;
		}
	}
}


BOOL CWhriaViewDlg::Login(const std::string&stIP,const std::string&stPort,const std::string& stID,const std::string& stPasswd)
{
	try
	{
		WhriaClient.connect(stIP,stPort);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		if (err_.iErrorCode==6)
			return false;
		ErrorExit(err_);
		exit(1);
		return false;
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		if (err_.iErrorCode==TIMEOUT)
		{
			m_Progress.SetWindowText(_T("Setup Login Information"));
		}
		else
		{
			ErrorExit(err_);
			exit(1);
		}
		return false;
	}
    catch (std::exception& e)
    {
        // Unable to decode data.
		m_Progress.SetWindowText(MCodeChanger::_CCW(e.what()).c_str());
		return false;
	}

	try
	{
		WhriaClient.login(stID,stPasswd,config_.server_config);
//		std::string aa=config_.server_config.Get(DATA_PATH);
		
		StopIdleSignalThread();
		boost::thread BuildThread(boost::bind(&CWhriaViewDlg::ConnectionThread,this));

		m_PictureList.SetRect(iThumb_Width,iThumb_Height);
		ProcessThumbnailSize();
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		WhriaClient.disconnect();

		if (err_.iErrorCode==6)
			return false;
		ErrorExit(err_);
		exit(1);
		return false;
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		WhriaClient.disconnect();

		if (err_.iErrorCode==TIMEOUT)
		{
			m_Progress.SetWindowText(_T("Setup Login Information"));
		}
		else
		{
			ErrorExit(err_);
			exit(1);
		}
		return false;
	}
    catch (std::exception& e)
    {
		WhriaClient.disconnect();

		// Unable to decode data.
		m_Progress.SetWindowText(MCodeChanger::_CCW(e.what()).c_str());
		return false;
	}
	return true;
}


CString CWhriaViewDlg::GetFilePathFromTree(HTREEITEM pTree)
{
	CString csResultPath=_T("");

	HTREEITEM dumy=pTree;

//	HTREEITEM GetParentItem( HTREEITEM hItem );
	while (dumy!=0)
	{
		CString dumy2=csResultPath;
		csResultPath.Format(_T("%s/%s"),m_FolderTree.GetItemText(dumy),dumy2);
		dumy=m_FolderTree.GetParentItem(dumy);
	}

//	if (csResultPath.Left(2)==_T("//")) csResultPath=csResultPath.Mid(1);
	if (csResultPath.Right(1)==_T("/")) 
		csResultPath=csResultPath.Left(csResultPath.GetLength()-1);
	return csResultPath;
/*
	if (csResultPath=="//") 
		return "/";
	else
		return csResultPath;
		*/
}

void CWhriaViewDlg::BrowseTree(HTREEITEM pTree)
{
//	Sleep(iListInterval);

	ThreadControl ThreadControl_(BROWSE_THREAD);
	boost::mutex::scoped_lock lock(browse_mutex);
	if (!ThreadControl_.Check(&bMutexCheck_browse))
		return;
	bTerminateBrowseThread=false;

	CString stNetPath=GetFilePathFromTree(pTree);

	m_Progress.SetPos(0);
	m_Progress.SetWindowText(TransMsg(IDS_RECEIVE_LIST));

	fileinfo_list path_list,dir_list,dir_list_copy;
	fileinfo_list file_list;

	try
	{
		WhriaClient.getfolderlist(MCodeChanger::_CCU((LPCTSTR)stNetPath),false,path_list);

		if (bTerminateBrowseThread)
			return;

		unsigned int i;

		TV_INSERTSTRUCT TI;
		TI.hInsertAfter=TVI_FIRST;
		TI.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
		TI.item.iImage=1;
		TI.item.iSelectedImage=0;

		for (i=0;i<path_list.size();i++)
		{
			if (path_list[i].IsDir())
				dir_list.push_back(path_list[i]);
			else
				file_list.push_back(path_list[i]);
		}

		HTREEITEM htree_pos=m_FolderTree.GetChildItem(pTree);
		int iSiblingCount=0;
		int iDirCount=(int)dir_list.size();

		std::vector<tstring> leaf_list;
		for (i=0;i<dir_list.size();i++)
		{
			leaf_list.push_back(MFile::leaf(_tpath(MCodeChanger::_CCL(dir_list[i].GetNetPath()))));
		}
		while (htree_pos!=NULL)
		{
			tstring item_text=(LPCTSTR)m_FolderTree.GetItemText(htree_pos);
			for (i=0;i<leaf_list.size();i++)
			{
				if (_tcscmp(leaf_list[i].c_str(),item_text.c_str())==0)
				{
					leaf_list.erase(leaf_list.begin()+i);
					break;
				}
			}
			htree_pos=m_FolderTree.GetNextSiblingItem(htree_pos);
			iSiblingCount++;
		}

		if (iDirCount!=iSiblingCount || leaf_list.size()!=0)
		{
			if (iSiblingCount>0)
			{
				HTREEITEM htree_pos=m_FolderTree.GetChildItem(pTree);
				while (htree_pos!=NULL)
				{
					HTREEITEM htree_pos_old=htree_pos;
					htree_pos=m_FolderTree.GetNextSiblingItem(htree_pos);
					m_FolderTree.DeleteItem(htree_pos_old);
				}
			}
			for (i=0;i<dir_list.size();i++)
			{
				TI.hParent=pTree;

				_tpath dumy=MCodeChanger::_CCL(dir_list[i].GetNetPath());

				TCHAR dumy_string[255];
				_tcscpy_s(dumy_string,255,MFile::leaf(dumy).c_str());
				TI.item.pszText=dumy_string;
				HTREEITEM pTree_Add=m_FolderTree.InsertItem(&TI);
			}
		}
	}
	catch (const client_connection::ConnectionEx& err_)
	{
//		bMutexCheck_browse=true;
		ErrorExit(err_);
//		return false;
		return;
	}
	catch (const basic_client::ConnectionEx& err_)
	{
//		bMutexCheck_browse=true;
		ErrorExit(err_);
		return;
//		return false;
	}

	m_FolderTree.Expand(pTree,TVE_EXPAND);

	if (bTerminateBrowseThread) 
		return;
//	{bMutexCheck_browse=true;return;}

	LoadPicture(file_list,MCodeChanger::_CCU((LPCTSTR)stNetPath));

//	bMutexCheck_browse=true;

//	return true;
}

void CWhriaViewDlg::OnSelchangedTreeRemote(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	if (bTreeLeftClick && pNMTreeView->action==1)
	{
		bTreeLeftClick=false;
		HTREEITEM hItem = pNMTreeView->itemNew.hItem;

//		pTree=hItem;
		BOOL bTreeExpand=!m_FolderTree.ItemHasChildren(hItem);
//		BrowseTree(hItem);

		UpdateData_FileInfo(fileinfo(),false);
		bTerminateBrowseThread=true;
		bTerminateLoadingThread=true;
		boost::thread LoadThread(boost::bind(&CWhriaViewDlg::BrowseTree,this,hItem));

	}

	*pResult = 0;
}

void CWhriaViewDlg::OnEnKillfocusEditDx()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString dumy=m_Dx;
	UpdateData(TRUE);
	if (dumy==m_Dx) return;

	CString csFileName=m_ID+_T("_")+m_Name+_T("_")+	m_Dx+_T("_")+m_ICD+_T(".jpg");

	POSITION pos = m_PictureList.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;
	else
	{
	  while (pos)
		{
		int nItem = m_PictureList.GetNextSelectedItem(pos);
//		WhriaClient.nfia_db.m_SelectedImage.GetNetPathAt(nItem);
		}
	}
}


BOOL CWhriaViewDlg::UpdateData(BOOL bSaveAndValidate)
{
	BOOL bResult;

	if (bSaveAndValidate)
	{
		CString dumy=m_Date;
		bResult=CDialog::UpdateData(bSaveAndValidate);
		m_Date=dumy;
		m_DxListCtrl.GetWindowText(m_Dx);
		m_Dx.Trim();
	}
	else
	{
//		m_CommentCtrl.SetWindowText(m_Comment);
		m_DxListCtrl.SetTemporaryDisable();
		m_DxListCtrl.SetWindowText(m_Dx);

		bResult=CDialog::UpdateData(bSaveAndValidate);
	}

	return bResult;
}

void CWhriaViewDlg::OnBnClickedButtonSubmittag()
{
	// TODO: Add your control notification handler code here


	fileinfo fileinfo_update;
	UpdateData_FileInfo(fileinfo_update,true);
	// 진단 입력

	try
	{
		if (fileinfo_update.Diagnosis==diagnosis() 
			&& fileinfo_update.stPatientID.empty()
			&& fileinfo_update.stPatientName.empty())
		{
			return;
		}
		else
		{
			CProgressDialog m_dlg(WhriaClient,config_);
			m_dlg.ModifyPath(m_SelectedImage,m_PictureList,fileinfo_update);

			m_PictureList.SetRedraw(false);
			m_dlg.DoModal();
		}

		if (!DxDB_.IsExistExact((LPCTSTR)m_Dx) && !m_Dx.IsEmpty())
		{
			diagnosis diagnosis_;
			diagnosis_.stDiagnosis=MCodeChanger::_CCU((LPCTSTR)m_Dx);
			diagnosis_.stICD10=MCodeChanger::_CCU((LPCTSTR)m_ICD);
			WhriaClient.setuserdx(diagnosis(),diagnosis_);

			CString cstDiagnosis=MCodeChanger::_CCL(diagnosis_.stDiagnosis).c_str();
			CString temp=cstDiagnosis.Left(1);temp.MakeUpper();
			cstDiagnosis=temp+cstDiagnosis.Mid(1);
			m_DxListCtrl.AddSearchString(cstDiagnosis);
		}
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const std::exception& e)
	{
		m_Progress.SetWindowText(MCodeChanger::_CCW(e.what()).c_str());
	}
	UpdateTooltip();
	UpdateCheckList();
	m_PictureList.SetRedraw(true);
	m_PictureList.StopNoBKDrawOnce();
}
int CWhriaViewDlg::GetCheckedListCount()
{
	int iCount=0;
	for (int i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			iCount++;
		}
	}
	return iCount;
}

fileinfo_list CWhriaViewDlg::GetCheckedList()
{
	fileinfo_list result;
	if ((int)m_SelectedImage.size()!=m_PictureList.GetItemCount())
	{
		m_Progress.SetWindowText(TransMsg(IDS_ERROR_GET_INFO));
		return result;
	}
	for (int i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			result.push_back(m_SelectedImage[i]);
		}
	}
	return result;
}


BOOL CAboutDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return CDialog::OnEraseBkgnd(pDC);
}

BOOL CAboutDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)   // 키보드가 눌렸을때 처리
	{
		OnOK();
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CAboutDlg::OnStnClickedStaticCredit()
{

	OnOK();
	// TODO: Add your control notification handler code here
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	
	m_About.SetHyperlink(_T("Http://medicalphoto.org"));
	m_About.SetCaption(_T("http://medicalphoto.org"));

	m_WhriaNet.SetHyperlink(_T("Http://whria.net"));
	m_WhriaNet.SetCaption(_T("M.D., Ph.D. Han Seung Seog"));

	m_StaticVersion.SetWindowText(stVersionString);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CWhriaViewDlg::OnNMRclickTreeRemote(NMHDR *pNMHDR, LRESULT *pResult)
{
*pResult = 0;
bTreeLeftClick=false;
CPoint point, pt;
::GetCursorPos(&point);

pt = point; // 커서 포지션을 pt에 저장..
m_FolderTree.ScreenToClient(&point); // 트리아이템을 찾기위해 크라이언트 좌표로 변환..

UINT flags = 0;
HTREEITEM hItem = m_FolderTree.HitTest(point, &flags);
if (!hItem) return; // 아이템이 선택이 안되었음으로 리턴한다..

m_FolderTree.SelectItem(hItem);
//stRightCurrentDir=GetFilePathFromTree(hItem);

CPoint pCurPos;
GetCursorPos(&pCurPos);

CMenu popup;
CMenu *MyMenu;
popup.LoadMenu(IDR_MENU_POPUP_TREE);
MyMenu=popup.GetSubMenu(0);

if (m_FolderTree.GetParentItem(m_FolderTree.GetSelectedItem())==NULL)
{
	MyMenu->EnableMenuItem(ID_POPUP_RENAME,MF_GRAYED);
	MyMenu->EnableMenuItem(ID_POPUP_DELETE,MF_GRAYED);
}
else
{
	MyMenu->EnableMenuItem(ID_POPUP_RENAME,MF_ENABLED);
	MyMenu->EnableMenuItem(ID_POPUP_DELETE,MF_ENABLED);
}


MyMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,pCurPos.x,pCurPos.y,this);
m_PictureList.StopNoBKDrawOnce();

}



void CWhriaViewDlg::OnPopupToexcelfile()
{
	// TODO: Add your command handler code here
	CString path=GetFilePathFromTree(m_FolderTree.GetSelectedItem());

	fileinfo_list f_list;

	try
	{
		WhriaClient.getfolderlist(MCodeChanger::_CCU(path.GetBuffer(0)).c_str(),true,f_list);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}

	CString stDestFolder=ChooseFolder();
	if (stDestFolder=="") return;

}

CString CWhriaViewDlg::ChooseFolder(const CString& stTitle)
{
	TCHAR szFolder[MAX_PATH*2];
	szFolder[0] = _T('\0');
	CString csResult;

	TCHAR szPath[MAX_PATH*2];
	SHGetSpecialFolderPath(NULL, szPath, CSIDL_DRIVES, FALSE);
	
	BOOL bRet = XBrowseForFolder(m_hWnd
		,szPath
		,NULL
		,stTitle
		,szFolder
		,sizeof(szFolder)/sizeof(TCHAR)-2
		,FALSE);
	if (bRet) csResult.Format(_T("%s"),szFolder);
	else
		csResult=_T("");
//	csResult.Replace(_T("\\"),_T("/"));
	return csResult;
}



void CWhriaViewDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if ((old_cx!=cx || old_cy!=cy) && nType!=SIZE_MINIMIZED)
	{
		old_cx=cx;
		old_cy=cy;
		ResizeWindow(cx,cy);
		ProcessThumbnailSize();
	}
 

	// TODO: Add your message handler code here
}
void CWhriaViewDlg::SetPictureListCheck(int iIndex,bool bCheck)
{
	m_PictureList.SetCheck(iIndex,bCheck);
	bool bExist=false;

	tstring stPath=MFile::GetFileNamesExtL(MCodeChanger::_CCL(m_SelectedImage[iIndex].GetNetPath()));

	if (bCheck)
	{
		bool bExist=false;
		for (int i=0;i<m_CheckList.GetCount();i++)
		{
			fileinfo* temp=(fileinfo*)m_CheckList.GetItemDataPtr(i);
			if (strcmp(temp->GetNetPath().c_str(),m_SelectedImage[iIndex].GetNetPath().c_str())==0)
				return;
		}

		int iAddIndex=m_CheckList.AddString(stPath.c_str());
		m_CheckList.SetItemDataPtr(iAddIndex,&m_SelectedImage[iIndex]);

//		if (bColorState)
		m_CheckList.SetItemColorData(iAddIndex,bColorState);

//		m_CheckList.AddString(stPath.c_str(),RGB(255,255,0));
//		m_Checked_PathList.push_back(m_SelectedImage[iIndex].GetNetPath());
//		std::sort(m_Checked_PathList.begin(),m_Checked_PathList.end());
	}
	else
	{
		UINT iSearchIndex=m_CheckList.FindStringExact(0,stPath.c_str());
		if (iSearchIndex!=LB_ERR)
		{
			m_CheckList.DeleteString(iSearchIndex);
//			m_Checked_PathList.erase(m_Checked_PathList.begin()+iSearchIndex);
//			std::sort(m_Checked_PathList.begin(),m_Checked_PathList.end());
		}
	}
}
void CWhriaViewDlg::UpdateCheckList()
{
	m_CheckList.ResetContent();

	for (unsigned int i=0;i<m_SelectedImage.size();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			tstring stPath=MFile::GetFileNamesExtL(MCodeChanger::_CCL(m_SelectedImage[i].GetNetPath()));
			m_CheckList.SetItemDataPtr(m_CheckList.AddString(stPath.c_str()),&m_SelectedImage[i]);
		}
	}
}

void CWhriaViewDlg::ResizeWindow(int cx,int cy)
{

	if (config_.GetInt(VIEW_MODE)==0)
	{
		MoveCtrl(IDC_EDIT_INPUT,3,3,145,20);
		MoveCtrl(IDC_BUTTON_STOP,3,25,145,40);
		MoveCtrl(IDC_TREE_REMOTE,3,68,145,(cy-74)*3/4);
		MoveCtrl(IDC_LIST_CHECKLIST,3,68+ (cy-74)*3/4,145,(cy-74)/4);

		MoveCtrl(IDC_STATIC_DX,150,8,70,20);
		MoveCtrl(IDC_STATIC_ID,150,30,70,20);
		MoveCtrl(IDC_STATIC_NAME,150,52,70,20);
		MoveCtrl(IDC_STATIC_DATE,150,74,70,20);

		MoveCtrl(IDC_EDIT_DX,230,5,410,20);
		MoveCtrl(IDC_EDIT_DLG_ID,230,27,270,20);
		MoveCtrl(IDC_EDIT_NAME,230,49,270,20);
		MoveCtrl(IDC_EDIT_DATE,230,71,270,20);

		MoveCtrl(IDC_BUTTON_SUBMITTAG,520,50,120,40);

		MoveCtrl(IDC_EDIT_ICD,590,27,50,20);

		MoveCtrl(IDC_LIST_COMMENT,645,3,cx-651,88);
		MoveCtrl(IDC_PROGRESS_MAIN,150,95,cx-156,25);
		MoveCtrl(IDC_LIST_PHOTO,150,122,cx-156,cy-128);

		if (m_PictureList.GetSafeHwnd())
		{
			m_PictureList.ModifyStyle(0,LVS_NOSCROLL);
			m_PictureList.ModifyStyle(LVS_NOSCROLL, 0);
		}
	}
	if (config_.GetInt(VIEW_MODE)==1)
	{
		MoveCtrl(IDC_EDIT_INPUT,3,3,145,20);
		MoveCtrl(IDC_BUTTON_STOP,3,25,145,40);
		MoveCtrl(IDC_TREE_REMOTE,3,68,145,(cy-74)*3/4);
		MoveCtrl(IDC_LIST_CHECKLIST,3,68+ (cy-74)*3/4,145,(cy-74)/4);

		MoveCtrl(IDC_PROGRESS_MAIN,150,3,cx-156,25);
		MoveCtrl(IDC_LIST_PHOTO,150,30,cx-156,cy-35);

		if (m_PictureList.GetSafeHwnd())
		{
			m_PictureList.ModifyStyle(0,LVS_NOSCROLL);
			m_PictureList.ModifyStyle(LVS_NOSCROLL, 0);
		}
	}
}
void CWhriaViewDlg::MoveCtrl(int iID,int a,int b,int c,int d)
{
	if (GetDlgItem(iID)->GetSafeHwnd())
		GetDlgItem(iID)->MoveWindow(a,b,c,d,true);
}




void CWhriaViewDlg::HidePictureMultiMon(int iMonitor)
{
//	ProcessRotate(iMonitor);
	if (ImageDisplay[iMonitor]->bImageOn)
		iLastDisplay=iMonitor;
	ImageDisplay[iMonitor]->image=blank_image;
	ImageDisplay[iMonitor]->Reset();
	ImageDisplay[iMonitor]->ShowWindow(SW_HIDE);

//	ImageDisplay[iMonitor]->image=blank_image;
//	ImageDisplay[iMonitor]->bImageOn=false;
//	ImageDisplay[iMonitor]->image=blank_image;
}

BOOL CWhriaViewDlg::ShowPictureMultiMon(int iMonitor)
{
//	HidePictureMultiMon(iMonitor);
//	bImageOn[iMonitor]=true;
	ImageDisplay[iMonitor]->bImageOn=true;
//	ImageDisplay[iMonitor]->bZoom=bZoom[iMonitor];
//	ImageDisplay[iMonitor]->image=&ImageDisplay[iMonitor]->image;
	ImageDisplay[iMonitor]->ResetToolTip();
	ImageDisplay[iMonitor]->monitor.CenterWindowToMonitor(ImageDisplay[iMonitor]);

	CRect rect;
	ImageDisplay[iMonitor]->monitor.GetMonitorRect( &rect );

	ImageDisplay[iMonitor]->MoveWindow(rect.left,rect.top,rect.right,rect.bottom);

	if ((int)ImageDisplay[iMonitor]->image.GetWidth() <= rect.Width()
		&& (int)ImageDisplay[iMonitor]->image.GetHeight() <= rect.Height())
		ImageDisplay[iMonitor]->m_Zoom.ShowWindow(SW_HIDE);
	else
		ImageDisplay[iMonitor]->m_Zoom.ShowWindow(SW_SHOW);

	if (m_SelectedImage.size()>1)
	{
		ImageDisplay[iMonitor]->m_Left.EnableWindow(true);
		ImageDisplay[iMonitor]->m_Left.ShowWindow(SW_SHOW);
		ImageDisplay[iMonitor]->m_Right.EnableWindow(true);
		ImageDisplay[iMonitor]->m_Right.ShowWindow(SW_SHOW);
	}
	else
	{
		ImageDisplay[iMonitor]->m_Left.EnableWindow(false);
		ImageDisplay[iMonitor]->m_Left.ShowWindow(SW_HIDE);
		ImageDisplay[iMonitor]->m_Right.EnableWindow(false);
		ImageDisplay[iMonitor]->m_Right.ShowWindow(SW_HIDE);
	}

//	ImageDisplay[iMonitor]->ShowWindow(SW_HIDE);
//	ImageDisplay[iMonitor]->Invalidate(false);
	ImageDisplay[iMonitor]->ShowWindow(SW_SHOW);
	ImageDisplay[iMonitor]->Invalidate(false);
	ImageDisplay[iMonitor]->ResetButtons();
	return TRUE;
}

BOOL CWhriaViewDlg::ShowPictureMultiMon2(int iMonitor)
{
	ImageDisplay[iMonitor]->bImageOn=true;
//	ImageDisplay[iMonitor]->bZoom=bZoom[iMonitor];
//	ImageDisplay[iMonitor]->image=&ImageDisplay[iMonitor]->image;
	ImageDisplay[iMonitor]->ResetToolTip();

	CRect rect;
	ImageDisplay[iMonitor]->monitor.GetMonitorRect( &rect );

	if ((int)ImageDisplay[iMonitor]->image.GetWidth() <= rect.Width()
		&& (int)ImageDisplay[iMonitor]->image.GetHeight() <= rect.Height())
		ImageDisplay[iMonitor]->m_Zoom.ShowWindow(SW_HIDE);
	else
		ImageDisplay[iMonitor]->m_Zoom.ShowWindow(SW_SHOW);

	if (m_SelectedImage.size()>1)
	{
		ImageDisplay[iMonitor]->m_Left.EnableWindow(true);
		ImageDisplay[iMonitor]->m_Left.ShowWindow(SW_SHOW);
		ImageDisplay[iMonitor]->m_Right.EnableWindow(true);
		ImageDisplay[iMonitor]->m_Right.ShowWindow(SW_SHOW);
	}
	else
	{
		ImageDisplay[iMonitor]->m_Left.EnableWindow(false);
		ImageDisplay[iMonitor]->m_Left.ShowWindow(SW_HIDE);
		ImageDisplay[iMonitor]->m_Right.EnableWindow(false);
		ImageDisplay[iMonitor]->m_Right.ShowWindow(SW_HIDE);
	}

	ImageDisplay[iMonitor]->Invalidate(false);
	ImageDisplay[iMonitor]->ShowWindow(SW_SHOW);
	ImageDisplay[iMonitor]->ResetButtons();
	return TRUE;
}


void CWhriaViewDlg::OnBegindragListPicturelist(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CWhriaViewDlg::GetCommentThread(const std::vector<std::string>& stNetPath_list)
{
	// mutex
	if (bExitFlag) return;

	ThreadControl ThreadControl_(COMMENT_THREAD);
	boost::mutex::scoped_lock lock3(comment_mutex);
	if (!ThreadControl_.Check(&bMutexCheck_comment)) 
		return;

	if (m_CommentList.GetSafeHwnd()) 
		m_CommentList.EnableWindow(FALSE);
	else
		return;

//	bMutexCheck_comment=false;

	active_comment_list_.clear();
	m_CommentList.DeleteAllItems();

	try{

		comment_list comment_temp;
//		std::vector<int> number_list;
		WhriaClient.getcomment(stNetPath_list,comment_temp);

		for (int i=0;i<(int)(comment_temp.size());i++)
		{
			comment_cluster comment_cluster_;
			comment_cluster_.set(comment_temp[i]);
			comment_cluster_.add(comment_temp[i]);
			active_comment_list_.push_back(comment_cluster_);

			for (int j=(int)(comment_temp.size()-1);j>i;j--)
			{
				if (comment::compare_details(comment_temp[i],comment_temp[j]))
				{
					active_comment_list_[i].add(comment_temp[j]);
					comment_temp.erase(comment_temp.begin()+j);
				}
			}
		}

		LV_ITEM LI;
		LI.mask=LVIF_TEXT;
//		LI.state=0;
		LI.stateMask=0;
		LI.state=0;
		LI.cchTextMax=255;

		for (unsigned int i=0;i<active_comment_list_.size();i++)
		{
//			m_CommentList.SetItemText(i,1,
//			MCodeChanger::_CCL(active_comment_list_[i].Owner.stUserID).c_str());
//			m_CommentList.SetItemText(i,2,
//			MCodeChanger::_CCL(active_comment_list_[i].stDetail).c_str());

			CString string1,string2;
			string1=MCodeChanger::_CCL(active_comment_list_[i].comment_.Owner.stUserID).c_str();
			string2=MCodeChanger::_CCL(active_comment_list_[i].comment_.stDetail).c_str();

			LI.iImage=0; // Image
			LI.iItem=i;  // 세로

			LI.iSubItem=0;  // 가로
			LI.pszText=_T("");
			m_CommentList.InsertItem(&LI);

			LI.iSubItem=1;  // 가로
			LI.pszText=(LPTSTR)(LPCTSTR)string1;
			m_CommentList.SetItem(&LI);

			LI.iSubItem=2;  // 가로
			LI.pszText=(LPTSTR)(LPCTSTR)string2;
			m_CommentList.SetItem(&LI);

			if (active_comment_list_[i].size()==stNetPath_list.size())
				m_CommentList.SetCheck(i,true);

		}
		if (m_CommentList.GetSafeHwnd()) m_CommentList.EnableWindow(TRUE);
		m_CommentList.InsertItemEx(m_CommentList.GetItemCount());
	}
	catch (...)
	{
	}
//	bMutexCheck_comment=true;
}

void CWhriaViewDlg::AddCheckedComment(int iListIndex)
{
	if ((int)active_comment_list_.size()<=iListIndex)
		return;
	
	comment_list comment_list_from_,comment_list_to_; 

	for (int i=0;i<(int)m_SelectedImage.size();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			bool bExist=false;
			for (int j=0;j<active_comment_list_[iListIndex].size();j++)
			{
				if (strcmp(active_comment_list_[iListIndex].stNetPath_list[j].c_str()
					,m_SelectedImage[i].GetNetPath().c_str())==0)
					{bExist=true;break;}
			}
			if (!bExist)
			{
				// Insert
				comment comment_=active_comment_list_[iListIndex].comment_;
				comment_.stNetPath=m_SelectedImage[i].GetNetPath();
				comment_list_to_.push_back(comment_);

				comment_list_from_.push_back(comment());
			}
		}
	}
	try
	{
		WhriaClient.setcomment(comment_list_from_,comment_list_to_);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
}

void CWhriaViewDlg::UndoAddCheckedComment(int iListIndex)
{

	if ((int)active_comment_list_.size()<=iListIndex)
		return;

	comment_list comment_list_from_,comment_list_to_; 

	for (int i=0;i<(int)m_SelectedImage.size();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			bool bExist=false;
			for (int j=0;j<active_comment_list_[iListIndex].size();j++)
			{
				if (strcmp(active_comment_list_[iListIndex].stNetPath_list[j].c_str()
					,m_SelectedImage[i].GetNetPath().c_str())==0)
					{bExist=true;break;}
			}
			if (!bExist)
			{
				// Delete
				comment comment_=active_comment_list_[iListIndex].comment_;
				comment_.stNetPath=m_SelectedImage[i].GetNetPath();
				comment_list_from_.push_back(comment_);

				comment_list_to_.push_back(comment());
			}
		}
	}
	try
	{
		WhriaClient.setcomment(comment_list_from_,comment_list_to_);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
}

void CWhriaViewDlg::SaveComment(int iListIndex,const CString& stComment)
{
//	modified_log modified_log_; 
//	m_CommentList.GetLog(modified_log_);
//	if (modified_log_.size()==0) return;
//	m_CommentList.ResetLog();

//	int i;
/*	int iChecked=-1;

	for (i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			iChecked=i;break;
		}
	} 
	if (iChecked==-1) return;
*/
//	if (iIndex>=(int)m_SelectedImage.size()) return;

	std::string stNewComment=MCodeChanger::_CCU((LPCTSTR)stComment);

	if ((int)active_comment_list_.size()>iListIndex)
	{
		if (strcmp(active_comment_list_[iListIndex].comment_.stDetail.c_str(),stNewComment.c_str())==0)
			return;
	}
	
	comment_list comment_list_from_,comment_list_to_; 

	if (m_CommentList.GetCheck(iListIndex))
	{
		if ((int)active_comment_list_.size()<=iListIndex)
		{
			for (int i=0;i<(int)m_SelectedImage.size();i++)
			{
				if (m_PictureList.GetCheck(i))
				{
					// insert
					comment_list_from_.push_back(comment());

					comment comment_(m_SelectedImage[i].GetNetPath()
						,CurrentUser.stUserID
						,stNewComment);
					comment_list_to_.push_back(comment_);
				}
			}
		}
		else
		{
			for (int i=0;i<(int)m_SelectedImage.size();i++)
			{
				if (m_PictureList.GetCheck(i))
				{
					// update
					comment comment_from_=active_comment_list_[iListIndex].comment_;
					comment_from_.stNetPath=m_SelectedImage[i].GetNetPath();
					comment_list_from_.push_back(comment_from_);

					comment comment_(m_SelectedImage[i].GetNetPath()
					,CurrentUser.stUserID
					,stNewComment);
					comment_list_to_.push_back(comment_);
				}
				
			}
		}
	}
	else
	{
		if ((int)active_comment_list_.size()<=iListIndex)
		{
			comment_cluster comment_cluster_;bool bSet=false;

			for (int i=0;i<(int)m_SelectedImage.size();i++)
			{
				if (m_PictureList.GetCheck(i))
				{
					// insert
					comment_list_from_.push_back(comment());

					comment comment_(m_SelectedImage[i].GetNetPath()
						,CurrentUser.stUserID
						,stNewComment);
					comment_list_to_.push_back(comment_);

					if (!bSet)
						{comment_cluster_.set(comment_);bSet=true;}
					comment_cluster_.add(comment_);
				}
			}
			active_comment_list_.push_back(comment_cluster_);
		}
		else
		{
			for (int i=0;i<active_comment_list_[iListIndex].size();i++)
			{

				// update
				comment comment_(active_comment_list_[iListIndex].stNetPath_list[i]
				,CurrentUser.stUserID
				,stNewComment);
				comment_list_to_.push_back(comment_);
				
				comment comment_from_=active_comment_list_[iListIndex].comment_;
				comment_from_.stNetPath=active_comment_list_[iListIndex].stNetPath_list[i];
				comment_list_from_.push_back(comment_from_);
			}
		}
	}

	try
	{
		WhriaClient.setcomment(comment_list_from_,comment_list_to_);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
}

void CWhriaViewDlg::OnNMKillfocusListComment(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

//	SaveComment();

}


void CWhriaViewDlg::UpdateData_FileInfo(fileinfo& fileinfo_,bool bSaveAndValidate)
{
	if (bSaveAndValidate)
	{
		UpdateData(true);
		fileinfo_.Diagnosis.stDiagnosis=MCodeChanger::_CCU((LPCTSTR)m_Dx);
		fileinfo_.Diagnosis.stICD10=MCodeChanger::_CCU((LPCTSTR)m_ICD);
		fileinfo_.stPatientID=MCodeChanger::_CCU((LPCTSTR)m_ID);
		fileinfo_.stPatientName=MCodeChanger::_CCU((LPCTSTR)m_Name);
	}
	else
	{
		m_Dx=MCodeChanger::_CCL(fileinfo_.Diagnosis.stDiagnosis).c_str();
		m_ID=MCodeChanger::_CCL(fileinfo_.stPatientID).c_str();
		m_Name=MCodeChanger::_CCL(fileinfo_.stPatientName).c_str();
		m_Date=MCodeChanger::_CCL(fileinfo_.GetDateString()).c_str();
		m_ICD=MCodeChanger::_CCL(fileinfo_.Diagnosis.stICD10).c_str();
		UpdateData(false);
	}
}

void CWhriaViewDlg::UpdateDetails(bool bSkipRetrieve)
{
	int iCheckedCount=0;
	int iChecked;
	bool bAllSameInfo=true;
	bool bAllSamePatient=true;
	std::string stID,stName; 
	diagnosis diagnosis_;

	std::vector<std::string> stNetPathChecked_list;

	std::string stOldID;
	std::string stOldName;
	fileinfo_list f_list;

	for (int i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			f_list.push_back(m_SelectedImage[i]);

			if (!bSkipRetrieve)
			{
				if (strcmp(f_list[f_list.size()-1].stPatientID.c_str(),"")==0 
					&&
					strcmp(f_list[f_list.size()-1].stPatientName.c_str(),"")==0)
				{

					// 순위별로 분리
					std::string stFilename=MCodeChanger::_CCU(MFile::GetFileNamesExtL(MCodeChanger::_CCL(f_list[f_list.size()-1].GetNetPath())));
					std::vector<std::string> split_vec;
					boost::split(split_vec
						,stFilename
						,boost::is_any_of(config_.server_config.Get(SMART_RETRIEVE_IDNAME_SEPARATOR)));

					std::string stRemoveSymbol="(){}~!@#$%^&()_+[]:;',.`";
					std::string stRemoveNumeric="0123456789";

					if (split_vec.size()>=2)
					{
						std::vector<bool> bNameFormat;

						for (unsigned int j=0;j<split_vec.size();j++)
						{
							// 숫자로만 되어 있거나 기호들어가면 제외
							bool bNumeric=true;
							bool bSymbol=false;

							for (unsigned int k=0;k<split_vec[j].size();k++)
							{
								for (unsigned int l=0;l<stRemoveSymbol.length();l++)
								{
									if (stRemoveSymbol[l]==split_vec[j][k])
									{
										bSymbol=true;
										break;
									}
								}
							}

							for (unsigned int k=0;k<split_vec[j].size();k++)
							{
								bool bNumber=false;
								for (unsigned int l=0;l<stRemoveNumeric.length();l++)
								{
									if (stRemoveNumeric[l]==split_vec[j][k])
										bNumber=true;
								}
								if (!bNumber)
									bNumeric=false;
							}
							if (bNumeric==false && bSymbol==false)
								bNameFormat.push_back(true);
							else
								bNameFormat.push_back(false);
						}


						for (unsigned int j=split_vec.size()-1;j>=1;j--)
						{
							if (stFilename[stFilename.length()-split_vec[j].length()-1]==' ')
							{
								if (bNameFormat[j] && bNameFormat[j-1])
								{
									split_vec[j-1]+=" ";
									split_vec[j-1]+=split_vec[j];
									split_vec.erase(split_vec.begin()+j);
								}

							}
						}
					}

					if (split_vec.size()>=2)
					{
						int iFirst=atoi(split_vec[0].c_str());
						int iSecond=atoi(split_vec[1].c_str());
						if (iFirst>9999 && iSecond==0   
							&& split_vec[1].length()>3)
						{
							f_list[f_list.size()-1].stPatientID=split_vec[0];
							f_list[f_list.size()-1].stPatientName=split_vec[1];

							break;
						}
						if (iFirst==0 && iSecond>9999 
							&& split_vec[0].length()>3)
						{
							f_list[f_list.size()-1].stPatientID=split_vec[1];
							f_list[f_list.size()-1].stPatientName=split_vec[0];
							break;
						}
					}
				}
				if ((strcmp(stOldID.c_str(),f_list[f_list.size()-1].stPatientID.c_str())!=0
					||
					strcmp(stOldName.c_str(),f_list[f_list.size()-1].stPatientName.c_str())!=0)
					&& i>0)
				{
					bSkipRetrieve=true;
				}

				stOldID=f_list[f_list.size()-1].stPatientID;
				stOldName=f_list[f_list.size()-1].stPatientName;
			}
		}
	}

	for (unsigned int i=0;i<f_list.size();i++)
	{
		if (iCheckedCount==0)
		{
			diagnosis_=f_list[i].Diagnosis;
			stID=f_list[i].stPatientID;
			stName=f_list[i].stPatientName;
		}
		else
		{
			if (diagnosis_==f_list[i].Diagnosis)
			{
			}
			else
			{
				bAllSameInfo=false;
			}
			if (stID==f_list[i].stPatientID
				&& stName==f_list[i].stPatientName)
			{
			}
			else
			{
				bAllSamePatient=false;
			}

		}
		iCheckedCount++;
		iChecked=i;
		stNetPathChecked_list.push_back(f_list[i].GetNetPath());
	}

	// 안보이더라도 update 는 필요
//	if (config_.GetInt(VIEW_MODE)==0)
	{
		if ((bAllSameInfo || bAllSamePatient) && iCheckedCount>=1)
		{
//			fileinfo temp=m_SelectedImage[iChecked];
			fileinfo temp=f_list[iChecked];
			if (iCheckedCount>1)
				temp.Time=boost::posix_time::ptime();
			if (bAllSameInfo)
				temp.Diagnosis=f_list[0].Diagnosis;
			if (bAllSamePatient)
			{
				temp.stPatientName=f_list[0].stPatientName;
				temp.stPatientID=f_list[0].stPatientID;
			}

			UpdateData_FileInfo(temp,false);
		}
		else
		{
			StopCommentThread();
			active_comment_list_.clear();
			UpdateData_FileInfo(fileinfo(),false);
		}

		if (iCheckedCount>0)
		{
			GetDlgItem(IDC_BUTTON_SUBMITTAG)->EnableWindow(true);
			boost::thread GetCommentThread(boost::bind(&CWhriaViewDlg::GetCommentThread,this
			,stNetPathChecked_list));
		}
		else
		{
			GetDlgItem(IDC_BUTTON_SUBMITTAG)->EnableWindow(false);
			m_CommentList.DeleteAllItems();
			m_CommentList.EnableWindow(FALSE);
		}
		 
	}

/*
	for (int i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			if (iCheckedCount==0)
			{
				diagnosis_=m_SelectedImage[i].Diagnosis;
				stID=m_SelectedImage[i].stPatientID;
				stName=m_SelectedImage[i].stPatientName;
			}
			else
			{
				if (diagnosis_==m_SelectedImage[i].Diagnosis 
					&& stID==m_SelectedImage[i].stPatientID
					&& stName==m_SelectedImage[i].stPatientName)
				{
				}
				else
				{
					bAllSameInfo=false;
				}

			}
			iCheckedCount++;
			iChecked=i;
			stNetPathChecked_list.push_back(m_SelectedImage[i].GetNetPath());
		}
	}
	*/
}

void CWhriaViewDlg::OnNMClickListPicturelist(unsigned int iSelected)
{
	if (iSelected>=iCurrentLoadingIndex)
		return;

	if (iSelected>=m_SelectedImage.size() || iSelected==-1) return;
	m_PictureList.SetRedraw(FALSE);

	bColorState=(::GetKeyState(VK_CONTROL)<0);
	SetPictureListCheck(iSelected,!m_PictureList.GetCheck(iSelected));

	DrawListItem(iSelected,false,true,false);

	CString output;
	if (m_PictureList.GetCheck(iSelected))
	{
		CString stFormat;
		output+=MCodeChanger::_CCL(m_SelectedImage[iSelected].GetNetPath()).c_str();
		output+=stFormat;
	}
	else
	{
		output=_T(" ");
	}
	m_Progress.SetWindowText(output);

	// InteliCheck
	if (::GetKeyState(VK_CONTROL)<0 && m_SelectedImage.size()>1)
	{

		int i;CString csMessage;
		int iCount;
		iCount=m_PictureList.GetItemCount();

		bool bCheckState=m_PictureList.GetCheck(iSelected);
	
		// 파일명 비슷한 것을 선택
		CString cstFileNameClue=MFile::GetFileNamesExtL(MCodeChanger::_CCL(m_SelectedImage[iSelected].GetNetPath())).c_str();
		cstFileNameClue=cstFileNameClue.Left(config_.server_config.GetInt(HOSPITAL_ID_LENGTH));
		CString cstFileDir=MFile::GetFileDirL(MCodeChanger::_CCL(m_SelectedImage[iSelected].GetNetPath())).c_str();
		int iInteliCount=0;
		for (i=0;i<iCount;i++)
		{
			CString tempClue=MFile::GetFileNamesExtL(MCodeChanger::_CCL(m_SelectedImage[i].GetNetPath())).c_str();
			tempClue=tempClue.Left(config_.server_config.GetInt(HOSPITAL_ID_LENGTH));

			CString tempDir=MFile::GetFileDirL(MCodeChanger::_CCL(m_SelectedImage[i].GetNetPath())).c_str();

			if (tempClue==cstFileNameClue && tempDir==cstFileDir)
			{
					if (bCheckState)
						bColorState=true;
					else
						bColorState=false;

				SetPictureListCheck(i,bCheckState);

				DrawListItem(i,false,true,false);
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
//					m_CheckList.SetColorState(true);
					if (bCheckState)
						bColorState=true;
					else
						bColorState=false;
					SetPictureListCheck(iIndex_dumy[i],bCheckState);
//					m_CheckList.SetColorState(false);
					DrawListItem(iIndex_dumy[i],false,true,false);
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

	if (::GetKeyState(VK_CONTROL)<0 && m_SelectedImage.size()>1)
	{
		UpdateDetails(true);
	}
	else
	{
		UpdateDetails(false);
	}
	UpdateTooltip();

	m_PictureList.NoBKDrawOnce();
	m_PictureList.SetRedraw(TRUE);
//	m_PictureList.Invalidate(FALSE);
}
void CWhriaViewDlg::OnNMClickListPicturelistThread(unsigned int iIndex)
{
	boost::mutex::scoped_lock lock(click_mutex);
	bool bOldCheck=m_PictureList.GetCheckEx(iIndex);
	Utility::sleep(100);
	if (bOldCheck==m_PictureList.GetCheckEx(iIndex))
	{
		PostMessage(WM_CLICKPICTURE,(WPARAM)iIndex,NULL);
	}
}
void CWhriaViewDlg::OnNMClickListPicturelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = CDRF_SKIPDEFAULT;

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	unsigned int iSelected=pNMListView->iItem;

	if (iSelected==-1) return;

	if (::GetKeyState(VK_CONTROL)<0)
	{
		OnNMClickListPicturelist(iSelected);
	}
	else
	{
		m_PictureList.SetCheckEx(iSelected,!m_PictureList.GetCheckEx(iSelected));
		boost::thread BuildThread(boost::bind(&CWhriaViewDlg::OnNMClickListPicturelistThread,this
			,iSelected));
	}
}


void CWhriaViewDlg::UpdateTooltip()
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
CNetFileInfo CWhriaViewDlg::GetCheckedListByOrder(fileinfo_list* f_list)
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

CString CWhriaViewDlg::GetCheckedListByOrder(CStringArray* s_array,int* iItemNb,CString* iItem)
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

void CWhriaViewDlg::OnNMCustomdrawListPicturelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	*pResult = CDRF_DODEFAULT;
	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
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

		DrawListItem(nItem,true,true,true);

		*pResult = CDRF_SKIPDEFAULT;
	//        *pResult = CDRF_NOTIFYPOSTPAINT;
	//        *pResult = CDDS_SUBITEM|CDDS_ITEM|CDDS_PREPAINT ;

    }
	else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_SKIPDEFAULT;
	}
	else
	{
        *pResult = CDRF_SKIPDEFAULT;
	}
}

void CWhriaViewDlg::DrawListItem(int nItem,bool bDrawItem,bool bDrawCheck,bool bDrawSubitem)
{
	if (m_PictureList.GetInsert())
		return;
/*
*/

	LVITEM rItem;

	ZeroMemory ( &rItem, sizeof(LVITEM) );
	rItem.mask  = LVIF_IMAGE | LVIF_STATE;
	rItem.iItem = nItem;
	rItem.stateMask = LVIS_SELECTED;

	m_PictureList.GetItem ( &rItem );

	CRect rcIcon; 

	m_PictureList.GetItemRect ( nItem, &rcIcon, LVIR_BOUNDS );

	// Draw the icon.

	rcIcon.top+=2;
	rcIcon.bottom+=2;
	rcIcon.right+=8;
	rcIcon.left+=8;

	POINT pt;
	pt.x=rcIcon.left;
	pt.y=rcIcon.top+iThumb_Height;
	pt.y+=5;

	CRect crListrect;

	m_PictureList.GetWindowRect(crListrect);

	// subitem 그리기
	
	CRect rc;

	rc.left = rcIcon.left+20;
	rc.right = rcIcon.right;
	rc.top=rcIcon.top+iThumb_Height;
	rc.bottom=rcIcon.top+iThumb_Height;
	rc.bottom+=25;

	if ((pt.y+20)>0 && rcIcon.top<crListrect.Height())
	{
		if (bDrawItem)
		{
			m_ImageListThumb.Draw( pListDC, rItem.iImage, rcIcon.TopLeft(),ILD_TRANSPARENT );
/*
			SIZE thumb_size;
			thumb_size.cx=iThumb_Width;
			thumb_size.cy=iThumb_Height;
			m_ImageListThumb.DrawEx ( pListDC, rItem.iImage, rcIcon.TopLeft(),thumb_size,CLR_DEFAULT,CLR_DEFAULT,ILD_TRANSPARENT );
*/
		}
		if (bDrawCheck
			&& !m_PictureList.GetItemText(nItem,0).IsEmpty()
			)
		{
			m_ImageListCheck.Draw(pListDC,m_PictureList.GetCheck(nItem),pt,ILD_TRANSPARENT);
		}

		if (bDrawSubitem)
		{
			pListDC->DrawText(m_PictureList.GetItemText(nItem,0),&rc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		}

	}
}

void CWhriaViewDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
/*		for (int i=0;i<m_PictureList.GetItemCount();i++)
		{
			DrawListItem(i,true,true,false);
		}
*/

		CDialog::OnPaint();
	}
}
void CWhriaViewDlg::SetToolTipText(int iIndex)
{
	try{
	m_PictureList.SetItemToolTipText(iIndex,0,MCodeChanger::_CCL(m_SelectedImage[iIndex].stNetPath).c_str());
	}
	catch (std::exception& e)
	{
		e.what();
	}
}


void CWhriaViewDlg::Unselectall()
{
	// TODO: Add your control notification handler code here
	int i;
	m_PictureList.SetRedraw(FALSE);
	for (i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			SetPictureListCheck(i,false);
			DrawListItem(i,false,true,false);
		}
	}
	m_PictureList.SetRedraw(TRUE);
	m_Progress.SetWindowText(_T(" "));
	UpdateDetails(false);
	
//	WhriaClient.ShowTag(CNetFileInfo());

//	m_tooltip.RemoveAllTools();
}


void CWhriaViewDlg::OnNMRclickListPicturelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	CPoint pCurPos;
	GetCursorPos(&pCurPos);

	CMenu popup;
	CMenu *MyMenu;
	popup.LoadMenu(IDR_MENU_POPUP_LIST);
	MyMenu=popup.GetSubMenu(0);

	if (GetCheckedListCount()==1)
	{
		MyMenu->EnableMenuItem(ID_POPUP_LIST_RENAME,MF_ENABLED);
		MyMenu->EnableMenuItem(ID_POPUP_LIST_DELETE,MF_ENABLED);
		MyMenu->EnableMenuItem(ID_POPUP_TOPOWERPOINT_LIST,MF_ENABLED);
		MyMenu->EnableMenuItem(ID_POPUP_LIST_COPY,MF_ENABLED);

		MyMenu->EnableMenuItem(ID_POPUP_DISSELECTALL,MF_ENABLED);
	}
	else if (GetCheckedListCount() > 1)
	{
		MyMenu->EnableMenuItem(ID_POPUP_LIST_RENAME,MF_GRAYED);
		MyMenu->EnableMenuItem(ID_POPUP_LIST_DELETE,MF_ENABLED);
		MyMenu->EnableMenuItem(ID_POPUP_TOPOWERPOINT_LIST,MF_ENABLED);
		MyMenu->EnableMenuItem(ID_POPUP_LIST_COPY,MF_ENABLED);

		MyMenu->EnableMenuItem(ID_POPUP_DISSELECTALL,MF_ENABLED);
	}
	else
	{
		MyMenu->EnableMenuItem(ID_POPUP_LIST_RENAME,MF_GRAYED);
		MyMenu->EnableMenuItem(ID_POPUP_LIST_DELETE,MF_GRAYED);
		MyMenu->EnableMenuItem(ID_POPUP_TOPOWERPOINT_LIST,MF_GRAYED);
		MyMenu->EnableMenuItem(ID_POPUP_LIST_COPY,MF_GRAYED);

		MyMenu->EnableMenuItem(ID_POPUP_DISSELECTALL,MF_GRAYED);
		
	}

	MyMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,pCurPos.x,pCurPos.y,this);
	m_PictureList.StopNoBKDrawOnce();

	*pResult = 0;
}


BOOL CWhriaViewDlg::ResetList()
{
	boost::mutex::scoped_lock lock(click_mutex);
	StopCommentThread();

	m_CheckList.ResetContent();
//	m_Checked_PathList.clear();

	m_SelectedImage.clear();
	m_PictureList.DeleteAllItems();
	UpdateTooltip();

	active_comment_list_.clear();
	m_CommentList.DeleteAllItems();
	m_CommentList.EnableWindow(FALSE);

	return TRUE;
}


void CWhriaViewDlg::DisplayFileNumber(int iNum)
{
	CString stMsg;
	if (strcmp(stCurrentPath.c_str(),"")!=0)
	{
		if (iNum==0)
		{
			stMsg.Format(_T("[ %s ]  :  None"),MCodeChanger::_CCL(stCurrentPath).c_str());
			m_Progress.SetWindowText(stMsg);
		}
		else if (iNum==1)
		{
			stMsg.Format(_T("[ %s ]  :  %d file"),MCodeChanger::_CCL(stCurrentPath).c_str(),iNum);
			m_Progress.SetWindowText(stMsg);
		}
		else
		{
			stMsg.Format(_T("[ %s ]  :  %d files"),MCodeChanger::_CCL(stCurrentPath).c_str(),iNum);
			m_Progress.SetWindowText(stMsg);
		}
	}
	else
	{
		if (iNum==0)
		{
			stMsg.Format(_T("Keyword [ %s ]  :  None"),stSearch);
			m_Progress.SetWindowText(stMsg);
		}
		else if (iNum==1)
		{
			stMsg.Format(_T("Keyword [ %s ]  :  %d file"),stSearch,iNum);
			m_Progress.SetWindowText(stMsg);
		}
		else
		{
			stMsg.Format(_T("Keyword [ %s ]  :  %d files"),stSearch,iNum);
			m_Progress.SetWindowText(stMsg);
		}
	}
}

int CWhriaViewDlg::PrepareLoad(const fileinfo_list& m_Next)
{
	if (!m_ImageListThumb.GetSafeHandle())
		return 0;
	int i;
	int iNumPictureList=m_Next.size();

	ResetList();

	if (iNumPictureList>config_.server_config.GetInt(MAX_SEARCH_RESULT_NUMBER))
	{
		CString dumy;
		dumy.Format(TransMsg(IDS_TOO_MANY_PHOTOS),iNumPictureList);

//		if (MessageBox(dumy+_T("  , Are you sure to read all of them ?"),_T("Caution"),MB_YESNO)!=IDYES)
//		{

			m_Progress.SetWindowText(dumy);
			m_Progress.SetRange(0,1);
			m_Progress.SetPos(1);
			m_PictureList.DeleteAllItems();
			m_PictureList.ModifyStyle(LVS_NOSCROLL, 0);
//			m_PictureList.ModifyStyle(0,LVS_NOSCROLL);
			return 0;
//		}
	}

	if (iNumPictureList==0)
	{
		DisplayFileNumber(0);
		m_Progress.SetRange(0,1);
		m_Progress.SetPos(1);
		m_PictureList.DeleteAllItems();
		m_PictureList.ModifyStyle(LVS_NOSCROLL, 0);
//		m_PictureList.ModifyStyle(0,LVS_NOSCROLL);
		return 0;
	}

	m_ImageListThumb.SetImageCount(iNumPictureList);
//	m_ImageListThumb_Org.SetImageCount(iNumPictureList);

	m_Progress.SetRange(0,iNumPictureList);
	m_Progress.SetPos(0);
	m_Progress.SetWindowText(_T("Preparing...."));

	m_SelectedImage=m_Next;

	m_PictureList.ModifyStyle(LVS_NOSCROLL, 0);

//	m_PictureList.EnsureVisible(0,FALSE);

	for (i=0;i<iNumPictureList;i++) 
	{
		m_ImageListThumb.Replace(i, &blank_bitmap, NULL);
	}

	m_PictureList.SetRedraw(FALSE);
	m_PictureList.SetInsert(TRUE);
	for (i=0;i<iNumPictureList;i++) 
	{
		m_PictureList.InsertItem(i,_T(""), i);
	}
	m_PictureList.SetInsert(FALSE);
	m_PictureList.SetRedraw(TRUE);

	m_PictureList.ModifyStyle(0,LVS_NOSCROLL);

	return iNumPictureList;
}


__int64 CWhriaViewDlg::ImageLoad (const std::string& stNetPath,CxImage  *image,bool bThumbnail)
{
	unsigned char* buffer=NULL;
	__int64 iFileSize;

	try
	{
		if (bThumbnail)
		{
			WhriaClient.cmd_tdownload(stNetPath,&buffer,iFileSize);

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
		else
		{
			WhriaClient.cmd_download(stNetPath,*image,iFileSize);
			if (buffer!=NULL) delete [] buffer;
			return iFileSize;
		}
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		if (buffer!=NULL) delete [] buffer;
		if (err_.iErrorCode!=FILE_NOT_EXIST)
			ErrorExit(err_);
		return 0;
	}
}
long CWhriaViewDlg::GenerateThumb(const fileinfo& fileinfo_,CxImage& image)  // iIndex 는 m_Selected_Image 에서
{
	try
	{
		if (ImageLoad (fileinfo_.stNetPath,&image,false)==0) return 0;
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}

	ImageProcess::MakeThumbnail(image,config_.server_config);
	/*
	RGBQUAD border;
	border.rgbBlue=0;
	border.rgbGreen=0;
	border.rgbRed=0;
	image.Thumbnail(config_.server_config.GetInt(THUMB_WIDTH)-2
		,config_.server_config.GetInt(THUMB_HEIGHT)-2,border);
	image.Expand(1,1,1,1,border);
	*/

//	bool Encode(BYTE * &buffer, long &size, DWORD imagetype);
	CxMemFile memfile;
	memfile.Open();
	image.Encode(&memfile,CXIMAGE_FORMAT_JPG);
	BYTE* buffer = memfile.GetBuffer();
	long size = memfile.Size();

	try
	{
		WhriaClient.cmd_tupload(fileinfo_.stNetPath,(unsigned char*)buffer,size);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		free(buffer);
		ErrorExit(err_);
		return size;
	}
	free(buffer);
	return size;
}

void CWhriaViewDlg::LoadPicture(const fileinfo_list& m_Next,const std::string& stRootPath)
{
//	if (m_Next.size()==0) return;
 	stCurrentPath=stRootPath;
	bTerminateLoadingThread=true;
	boost::mutex::scoped_lock lock_process(processimage_mutex);

	boost::thread PictureLoadingThread(boost::bind(&CWhriaViewDlg::Thread_Run,this,m_Next));
//	UpdateData_FileInfo(fileinfo(),false);
}


void CWhriaViewDlg::Thread_Run(fileinfo_list m_Next) 
{
	// TODO: Add your specialized code here and/or call the base class

	int i;
	HBITMAP     hBitmap = NULL;
	int iNumPictureList;


	ThreadControl ThreadControl_(PICTURELOADING_THREAD);
	boost::mutex::scoped_lock lock(thread_mutex);

	try
	{
		if (!ThreadControl_.Check(&bMutexCheck_thread)) 
			return;
		std::sort(m_Next.begin(),m_Next.end(),sort_fileinfo_by_PatientName_Time());

		bTerminateLoadingThread=false;

		iNumPictureList=PrepareLoad(m_Next);
		if (bTerminateLoadingThread) 
			return;

		if (iNumPictureList==0) 
			return;

		m_Progress.SetPos(0);
		m_Progress.SetWindowText(_T("Loading..."));

		iCurrentLoadingIndex=0;
		for (i=0;i<iNumPictureList;i++) 
		{
			CxImage  image;
			__int64 iSize;
			if (m_SelectedImage[i].stNetDir!=m_SelectedImage[i].stNetPath)
			{
				if (ImageLoad(m_SelectedImage[i].stNetPath,&image,true)==0)
				{
					if (bTerminateLoadingThread) 
						return;
					iSize=GenerateThumb(m_SelectedImage[i],image);
					if (iSize==0)
						image=blank_image;
				}

				if (image.IsValid()==FALSE)
					image=blank_image;

				image.Thumbnail(iThumb_Width,iThumb_Height,border);
				hBitmap=image.MakeBitmap();
				CBitmap pImage;	
				pImage.Attach(hBitmap);
				m_ImageListThumb.Replace(i, &pImage, NULL);


				CString stNetPath=MCodeChanger::_CCL(m_SelectedImage[i].stNetPath).c_str();
				CString stColumn=Utility::GetDateString(m_SelectedImage[i].Time.date()
					,config_.GetInt(DISPLAY_FOLDER_FORMAT)).c_str();

				if (stColumn!=_T(""))
					stColumn+=_T(" : ");
				stColumn+=MFile::GetFileNamesExtL((LPCTSTR)stNetPath).c_str();

// Critical Area
				while (bMutexCheck_picturelist==false)
				{
					Sleep(1);
				}

				bMutexCheck_picturelist=false;
				{
					m_PictureList.SetItemText(i,0,stColumn);
					// 직접 display
					if (bTerminateLoadingThread)
					{
						bMutexCheck_picturelist=true;
						return;
					}
					DrawListItem(i,true,true,true);
				}
				bMutexCheck_picturelist=true;
// Critical Area

				CString csProg;
				csProg.Format(_T("Loading... (%d/%d) "),i+1,iNumPictureList);
				m_Progress.SetWindowText(csProg);
				m_Progress.SetPos(i+1);

			}
			iCurrentLoadingIndex++;
		}

		DisplayFileNumber(iNumPictureList);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
//		bMutexCheck_thread=true;
		ErrorExit(err_); 
	}
	catch (const basic_client::ConnectionEx& err_)
	{
//		bMutexCheck_thread=true;
		ErrorExit(err_);
	}
	catch(...)
	{
		MessageBeep(MB_ICONHAND);
	}
//	bMutexCheck_thread=true;

 }

 
void CWhriaViewDlg::OnLvnBeginScrollListPicturelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// This feature requires Internet Explorer 5.5 or greater.
	// The symbol _WIN32_IE must be >= 0x0560.
	LPNMLVSCROLL pStateChanged = reinterpret_cast<LPNMLVSCROLL>(pNMHDR);
	// TODO: Add your control notification handler code here

	//reduce flickering
	m_PictureList.StopNoBKDrawOnce();
	m_PictureList.SetRedraw(TRUE);

	*pResult = 0;
}

void CWhriaViewDlg::OnLvnEndScrollListPicturelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// This feature requires Internet Explorer 5.5 or greater.
	// The symbol _WIN32_IE must be >= 0x0560.
	LPNMLVSCROLL pStateChanged = reinterpret_cast<LPNMLVSCROLL>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CWhriaViewDlg::UploadFolder(const tstring& stLocalPath,HTREEITEM pTree)
{
	std::string stDestNetPath=MCodeChanger::_CCU((LPCTSTR)GetFilePathFromTree(pTree));

	if (!MFile::IsDirL(stLocalPath))
		return;

	try
	{
		CProgressDialog m_dlg(WhriaClient,config_);
		m_dlg.UploadFolder(stLocalPath,stDestNetPath);
		m_PictureList.StopNoBKDrawOnce();
		m_dlg.DoModal();

	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}


//	BrowseTree(pTree);
	UpdateData_FileInfo(fileinfo(),false);
	bTerminateBrowseThread=true;
	bTerminateLoadingThread=true;

	boost::thread LoadThread(boost::bind(&CWhriaViewDlg::BrowseTree,this,pTree));
}

void CWhriaViewDlg::UploadFiles(const filepath_list& path_list)
{
	if (path_list.size()==0)
		return;

	fileinfo_list f_list;
	try
	{
		CProgressDialog m_dlg(WhriaClient,config_);
		m_dlg.UploadFiles(path_list,stCurrentPath);
		m_PictureList.StopNoBKDrawOnce();
		m_dlg.DoModal();

		WhriaClient.getfolderlist(stCurrentPath,true,f_list);

		UpdateData_FileInfo(fileinfo(),false);
		LoadPicture(f_list,stCurrentPath);

	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}


}

void CWhriaViewDlg::OnDropFiles(HDROP hDropInfo)
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
		if (!MFile::IsDirL((LPCTSTR)buf))
			path_list.push_back(MCodeChanger::_CCU((LPCTSTR)buf));
		else
		{
			m_Progress.SetWindowText(TransMsg(IDS_DRAG_FILE_NOT_FOLDER));
		}
    }
	UploadFiles(path_list);

	CDialog::OnDropFiles(hDropInfo);
}




void CWhriaViewDlg::OnViewAdvanced()
{
	// TODO: Add your command handler code here
	SetAdvancedView();
	config_.Set(VIEW_MODE,0);

	if (GetDlgItem(IDC_STATIC_DX)->GetSafeHwnd()) GetDlgItem(IDC_STATIC_DX)->ShowWindow(SW_SHOW);
	if (GetDlgItem(IDC_STATIC_ID)->GetSafeHwnd()) GetDlgItem(IDC_STATIC_ID)->ShowWindow(SW_SHOW);
	if (GetDlgItem(IDC_STATIC_NAME)->GetSafeHwnd()) GetDlgItem(IDC_STATIC_NAME)->ShowWindow(SW_SHOW);
	if (GetDlgItem(IDC_STATIC_DATE)->GetSafeHwnd()) GetDlgItem(IDC_STATIC_DATE)->ShowWindow(SW_SHOW);
	if (GetDlgItem(IDC_EDIT_DX)->GetSafeHwnd()) GetDlgItem(IDC_EDIT_DX)->ShowWindow(SW_SHOW);
	if (GetDlgItem(IDC_EDIT_DLG_ID)->GetSafeHwnd()) GetDlgItem(IDC_EDIT_DLG_ID)->ShowWindow(SW_SHOW);
	if (GetDlgItem(IDC_EDIT_NAME)->GetSafeHwnd()) GetDlgItem(IDC_EDIT_NAME)->ShowWindow(SW_SHOW);
	if (GetDlgItem(IDC_EDIT_DATE)->GetSafeHwnd()) GetDlgItem(IDC_EDIT_DATE)->ShowWindow(SW_SHOW);

	if (GetDlgItem(IDC_BUTTON_SUBMITTAG)->GetSafeHwnd()) GetDlgItem(IDC_BUTTON_SUBMITTAG)->ShowWindow(SW_SHOW);
	if (GetDlgItem(IDC_EDIT_ICD)->GetSafeHwnd()) GetDlgItem(IDC_EDIT_ICD)->ShowWindow(SW_SHOW);
	if (GetDlgItem(IDC_LIST_COMMENT)->GetSafeHwnd()) GetDlgItem(IDC_LIST_COMMENT)->ShowWindow(SW_SHOW);

//	RECT listRect;GetClientRect(&listRect);

	RECT listRect;GetClientRect(&listRect);
	ResizeWindow(listRect.right-listRect.left,listRect.bottom-listRect.top);


	m_PictureList.StopNoBKDrawOnce();
//	m_PictureList.SetRedraw(TRUE);
	m_PictureList.RedrawWindow();
	m_FolderTree.RedrawWindow();

//	m_PictureList.ModifyStyle(LVS_NOSCROLL, 0);
//	m_PictureList.ModifyStyle(0,LVS_NOSCROLL);

}


void CWhriaViewDlg::OnViewBasic()
{
	// TODO: Add your command handler code here
	SetBasicView();
	config_.Set(VIEW_MODE,1);


	if (GetDlgItem(IDC_STATIC_DX)->GetSafeHwnd()) GetDlgItem(IDC_STATIC_DX)->ShowWindow(SW_HIDE);
	if (GetDlgItem(IDC_STATIC_ID)->GetSafeHwnd()) GetDlgItem(IDC_STATIC_ID)->ShowWindow(SW_HIDE);
	if (GetDlgItem(IDC_STATIC_NAME)->GetSafeHwnd()) GetDlgItem(IDC_STATIC_NAME)->ShowWindow(SW_HIDE);
	if (GetDlgItem(IDC_STATIC_DATE)->GetSafeHwnd()) GetDlgItem(IDC_STATIC_DATE)->ShowWindow(SW_HIDE);
	if (GetDlgItem(IDC_EDIT_DX)->GetSafeHwnd()) GetDlgItem(IDC_EDIT_DX)->ShowWindow(SW_HIDE);
	if (GetDlgItem(IDC_EDIT_DLG_ID)->GetSafeHwnd()) GetDlgItem(IDC_EDIT_DLG_ID)->ShowWindow(SW_HIDE);
	if (GetDlgItem(IDC_EDIT_NAME)->GetSafeHwnd()) GetDlgItem(IDC_EDIT_NAME)->ShowWindow(SW_HIDE);
	if (GetDlgItem(IDC_EDIT_DATE)->GetSafeHwnd()) GetDlgItem(IDC_EDIT_DATE)->ShowWindow(SW_HIDE);

	if (GetDlgItem(IDC_BUTTON_SUBMITTAG)->GetSafeHwnd()) GetDlgItem(IDC_BUTTON_SUBMITTAG)->ShowWindow(SW_HIDE);
	if (GetDlgItem(IDC_EDIT_ICD)->GetSafeHwnd()) GetDlgItem(IDC_EDIT_ICD)->ShowWindow(SW_HIDE);
	if (GetDlgItem(IDC_LIST_COMMENT)->GetSafeHwnd()) GetDlgItem(IDC_LIST_COMMENT)->ShowWindow(SW_HIDE);

	RECT listRect;GetClientRect(&listRect);
	ResizeWindow(listRect.right-listRect.left,listRect.bottom-listRect.top);

	m_PictureList.StopNoBKDrawOnce();
//	m_PictureList.SetRedraw(TRUE);
	m_PictureList.RedrawWindow();
	m_FolderTree.RedrawWindow();

//	m_PictureList.ModifyStyle(LVS_NOSCROLL, 0);
//	m_PictureList.ModifyStyle(0,LVS_NOSCROLL);
}

void CWhriaViewDlg::OnPreferencePreference()
{
	// TODO: Add your command handler code here

	std::string old_dxcode_list=config_.Get(LOAD_DXCODE_LIST);
	std::string old_data_path=config_.server_config.Get(DATA_PATH);

	CPreference m_dlg(WhriaClient,config_);
	m_PictureList.StopNoBKDrawOnce();
	m_dlg.DoModal();

	if (strcmp(old_dxcode_list.c_str(),config_.Get(LOAD_DXCODE_LIST).c_str())!=0)
	{
		ReLoadDxDB();
	}
}


void CWhriaViewDlg::OnAboutAbout()
{
	// TODO: Add your command handler code here

	OnSysCommand(IDM_ABOUTBOX,0);
}

void CWhriaViewDlg::OnAboutUpdate()
{
	// TODO: Add your command handler code here
}

void CWhriaViewDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

void CWhriaViewDlg::OnLvnEndlabeleditListComment(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int iSelected=-1;
	for (int i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			iSelected=i;break;
		}
	}
	if (iSelected==-1) return;

	m_CommentList.OnEndLabelEdit(pNMHDR,pResult);

	LV_ITEM	*plvItem = &pDispInfo->item;
    if (plvItem->pszText != NULL)
    {
		SaveComment(plvItem->iItem,plvItem->pszText);
    }

	if (_tcscmp(plvItem->pszText,_T(""))==0)
	{
		m_CommentList.DeleteItem(plvItem->iItem);
		if (plvItem->iItem<(int)active_comment_list_.size())
			active_comment_list_.erase(active_comment_list_.begin()+plvItem->iItem);
	}
	else
	{
		if (plvItem->iItem==(m_CommentList.GetItemCount()-1))
		{
			if (m_CommentList.GetItemCount()>0)
			{
				if (!m_CommentList.GetItemText(m_CommentList.GetItemCount()-1,2).IsEmpty())
					m_CommentList.InsertItemEx(m_CommentList.GetItemCount());
			}
		}
	}

}

void CWhriaViewDlg::OnPopupTreeCreate()
{
	// TODO: Add your command handler code here

	HTREEITEM hItem=m_FolderTree.GetSelectedItem();
	if (hItem==NULL) return;

	_tpath root_path=_tpath((LPCTSTR)GetFilePathFromTree(hItem));

	try
	{
		std::string created_path;
		WhriaClient.createfolder_auto(
			MCodeChanger::_CCU(root_path.c_str())
			,config_.GetInt(CREATE_FOLDER_FORMAT)
			,created_path);

		TV_INSERTSTRUCT TI;
		TI.hInsertAfter=TVI_FIRST;
		TI.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
		TI.item.iImage=1;
		TI.item.iSelectedImage=0;

		TI.hParent=hItem;

		TCHAR dumy_string[255];
		_tcscpy(dumy_string,MFile::leaf(_tpath(MCodeChanger::_CCL(created_path))).c_str());

		TI.item.pszText=dumy_string;
		HTREEITEM pTree_Add=m_FolderTree.InsertItem(&TI);

		m_FolderTree.Expand(hItem,TVE_EXPAND);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}

}

void CWhriaViewDlg::OnTvnEndlabeleditTreeRemote(NMHDR *pNMHDR, LRESULT *pResult)
{
/*
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

//	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
//    HTREEITEM hItem = pNMTreeView->itemNew.hItem;

	TVITEM item = pTVDispInfo->item;
	CString newtext=item.pszText;

	HTREEITEM hItem=m_FolderTree.GetSelectedItem();
	CString oldtext=m_FolderTree.GetItemText(hItem);

	CString Tree_RootPath=GetFilePathFromTree(m_FolderTree.GetParentItem(hItem));
	_tpath root_path=_tpath((LPCTSTR)Tree_RootPath);
	_tpath oldpath(root_path),newpath(root_path);

	oldpath/=(LPCTSTR)oldtext;
	newpath/=(LPCTSTR)newtext;

	try
	{
		if (_tcscmp(newpath.string().c_str(),oldpath.string().c_str())!=0 && newtext!=_T(""))
		{
			WhriaClient.renamefolder(MCodeChanger::_CCU(oldpath.string())
				,MCodeChanger::_CCU(newpath.string()));
			m_FolderTree.SetItemText(hItem,newtext);
		}
		m_Progress.SetWindowText(_T("Rename : " + CString(oldpath.string().c_str())
			+ _T(" -> ") + CString(newpath.string().c_str())));
	}
	catch (const client_connection::ConnectionEx& err_)
	{
//		m_FolderTree.SetItemText(hItem,olditemtext);
		ErrorExit(err_);
	}
*/
}

void CWhriaViewDlg::OnTvnBeginlabeleditTreeRemote(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

//	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
  //  HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	
//	Tree_OldPath=GetFilePathFromTree(hItem);
}

void CWhriaViewDlg::OnPopupRename()
{
	// TODO: Add your command handler code here
	HTREEITEM hItem=m_FolderTree.GetSelectedItem();
	CString olditemtext=m_FolderTree.GetItemText(hItem);
	_tpath oldpath((LPCTSTR)GetFilePathFromTree(hItem));
	CString cstFolderName=m_FolderTree.GetItemText(hItem);

	CDialogInput m_dlg(m_FolderTree.GetItemText(hItem));

	try
	{
		m_PictureList.StopNoBKDrawOnce();

		if (m_dlg.DoModal()==IDOK)
		{
			StopAll();

			_tpath rootpath((LPCTSTR)GetFilePathFromTree(m_FolderTree.GetParentItem(hItem)));
			_tpath newpath= Utility::refinepath(rootpath / (LPCTSTR)m_dlg.m_InputBox);
			
			if (_tcscmp(newpath.c_str(),oldpath.c_str())!=0 && m_dlg.m_InputBox!=_T(""))
			{
				WhriaClient.renamefolder(MCodeChanger::_CCU(oldpath.c_str())
					,MCodeChanger::_CCU(newpath.c_str()));
				m_FolderTree.SetItemText(hItem,m_dlg.m_InputBox);
			}

			for (unsigned int i=0;i<m_SelectedImage.size();i++)
			{
				std::string stNetPathFrom=MCodeChanger::_CCU(oldpath.c_str());
				std::string stNetPathTo=MCodeChanger::_CCU(newpath.c_str());

				if (m_SelectedImage[i].GetNetPath().find(std::string(stNetPathFrom+"/"))==0 
					|| strcmp(m_SelectedImage[i].GetNetPath().c_str(),stNetPathFrom.c_str())==0)
				{
					boost::algorithm::replace_first(m_SelectedImage[i].stNetPath,stNetPathFrom,stNetPathTo);
					boost::algorithm::replace_first(m_SelectedImage[i].stNetDir,stNetPathFrom,stNetPathTo);
				}
			}

			m_Progress.SetWindowText(TransMsg(IDS_RENAME_FILE) + CString(oldpath.string().c_str())
				+ _T(" -> ") + CString(newpath.string().c_str()));
			m_Progress.SetRange(0,1);
		}
	}
	catch (const client_connection::ConnectionEx& err_)
	{
//		m_FolderTree.SetItemText(hItem,olditemtext);
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
//		m_FolderTree.SetItemText(hItem,olditemtext);
		ErrorExit(err_);
	}
	UpdateCheckList();
}

void CWhriaViewDlg::OnPopupDelete()
{
	// TODO: Add your command handler code here
	HTREEITEM hItem=m_FolderTree.GetSelectedItem();
	if (hItem == NULL) return;

	CString oldpath=GetFilePathFromTree(hItem);
	CString cstFolderName=m_FolderTree.GetItemText(hItem);

	for (unsigned int i=0;i<vol_list_.size();i++)
	{
		if (strcmp(vol_list_[i].c_str(),MCodeChanger::_CCU((LPCTSTR)oldpath).c_str())==0)
		{
			MessageBox(TransMsg(IDS_NOREMOVEROOT));
			return;
		}
	}

	// subfolder 있는경우 삭제 불가

	fileinfo_list f_list;
	try
	{
		WhriaClient.getfolderlist(MCodeChanger::_CCU((LPCTSTR)oldpath), false, f_list);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}

	if (f_list.size() > 0)
	{
		MessageBeep(MB_ICONEXCLAMATION); // 확인

		CString stMsg(_T("Delete all files in ( "));
		stMsg += oldpath;
		stMsg += _T(" ) first");
		MessageBox(stMsg);
		return;
	}
	/*
	MessageBeep(MB_ICONEXCLAMATION); // 확인
	if (MessageBox(TransMsg(IDS_CONFIRM_DELETE)+oldpath,_T("Delete Folder"),MB_YESNO)!=IDYES)
		return;
	*/

	StopAll();
	HTREEITEM hParentItem=m_FolderTree.GetParentItem(hItem);
	try
	{
		WhriaClient.deletefolder(MCodeChanger::_CCU((LPCTSTR)oldpath));
		m_FolderTree.DeleteItem(hItem);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}

	UpdateData_FileInfo(fileinfo(),false);
	UpdateCheckList();
	bTerminateBrowseThread=true;
	bTerminateLoadingThread=true;
	boost::thread LoadThread(boost::bind(&CWhriaViewDlg::BrowseTree,this,hParentItem));
}

void CWhriaViewDlg::OnPopupListDelete()
{
	// TODO: Add your command handler code here

	fileinfo_list f_list;
	for (int i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			f_list.push_back(m_SelectedImage[i]);
		}
	}
	if (f_list.size()==0) return;

	
	MessageBeep(MB_ICONEXCLAMATION); // 확인
	CSelectCheck m_dlg(f_list);

	m_PictureList.StopNoBKDrawOnce();
	if (m_dlg.DoModal()!=IDOK)
		return;

	StopAll();

	try
	{
		for (unsigned i=0;i<f_list.size();i++)
		{
			WhriaClient.deletefile(f_list[i].GetNetPath());
		}
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	for (int i=m_PictureList.GetItemCount()-1;i>=0;i--)
	{
		if (m_PictureList.GetCheck(i))
		{
			m_SelectedImage.erase(m_SelectedImage.begin()+i);
		}
	}
	UpdateData_FileInfo(fileinfo(),false);
	LoadPicture(m_SelectedImage,stCurrentPath);
}

void CWhriaViewDlg::OnPopupCopy()
{
	// TODO: Add your command handler code here
	HTREEITEM hItem=m_FolderTree.GetSelectedItem();

	if (hItem==NULL) return;

	CString path=GetFilePathFromTree(hItem);
	CString cstFolderName=m_FolderTree.GetItemText(hItem);
//	unsigned int i;

	CString temp_path=ChooseFolder(TransMsg(IDS_DOWN_SELECT_FOLDER));

	if (temp_path==_T("")) return;

	_tpath stDestPath_Org((LPCTSTR)temp_path);
	stDestPath_Org /= (LPCTSTR)cstFolderName;

	int iRenameCount=0;

	tstring stDestPath=Utility::GetNumericName(iRenameCount,stDestPath_Org.c_str());
	iRenameCount++;

	while (MFile::ExistsL(stDestPath))
	{
		stDestPath=Utility::GetNumericName(iRenameCount,stDestPath_Org.c_str());
		iRenameCount++;
	}

	if (MFile::CreateFolderL(stDestPath)==false)
	{
		CString msg=TransMsg(IDS_FAIL_CREATE_FOLDER);
		msg+=stDestPath.c_str();
		MessageBox(msg);
		return;
	}

	try
	{
		CProgressDialog m_dlg(WhriaClient,config_);
		m_dlg.DownloadFolder(MCodeChanger::_CCU((LPCTSTR)path),stDestPath);
		m_PictureList.StopNoBKDrawOnce();
		m_dlg.DoModal();
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}


}
void CWhriaViewDlg::OnPopupListCopy()
{
	// TODO: Add your command handler code here
	int iCount,i;
	iCount=0;
	fileinfo_list f_list;
	for (i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			f_list.push_back(m_SelectedImage[i]);
		}
	}

	if (f_list.size()==0)
		return;

	CString stDestFolder=ChooseFolder(TransMsg(IDS_DOWN_SELECT_FOLDER));
	if (stDestFolder==_T("")) return;

	try
	{
		CProgressDialog m_dlg(WhriaClient,config_);
		m_dlg.DownloadFile(f_list,(LPCTSTR)stDestFolder);
		m_PictureList.StopNoBKDrawOnce();
		m_dlg.DoModal();
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}

}

void CWhriaViewDlg::OnPopupListToexcelfile()
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
		return;
	}

	CString stDestFolder=ChooseFolder();
	if (stDestFolder==_T("")) return;


}

void CWhriaViewDlg::OnPopupTopowerpointTree()
{
	// TODO: Add your command handler code here

	HTREEITEM hItem=m_FolderTree.GetSelectedItem();
	if (hItem==NULL) return;

	CString stNetPath=GetFilePathFromTree(hItem);
	fileinfo_list f_list;
	try
	{
		WhriaClient.getfolderlist(MCodeChanger::_CCU((LPCTSTR)stNetPath),true,f_list);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}

	ExportPPT(f_list);
}

void CWhriaViewDlg::OnPopupTopowerpointList()
{
	// TODO: Add your command handler code here

	fileinfo_list f_list=GetCheckedList();
//	unsigned int i;
	if (f_list.size()==0) return;

	ExportPPT(f_list);
}

bool CWhriaViewDlg::ExportPPT(const fileinfo_list& f_list)
{

	if (f_list.empty())
	{
		MessageBox(TransMsg(IDS_EMPTY_FOLDER));
		return false;
	}
	if (f_list.size()>100)
	{
		CString output;
		output.Format(TransMsg(IDS_MANY_FILE),f_list.size());
		if (MessageBox(output,_T("Too Many Photos"),MB_YESNO)!=IDYES)
			return false;
	}

	try
	{
		// PPT

		_tpath prog_path=boost::filesystem::initial_path<_tpath>();
		_tpath temp_path=_tpath(MCodeChanger::_CCL(config_.server_config.Get(TMP_PATH)));
		MFile::CreateFolderL(temp_path.c_str());

		CString dest_path=ChooseFolder(TransMsg(IDS_SELECT_FOLDER4));
		if (dest_path==_T(""))
			return false;

	 
	//	SetWorkingDirectory(_T("./template"));
		static TCHAR BASED_CODE szFilter[] = _T("MS PowerPoint Files(*.ppt)|*.ppt||");
		CFileDialog FileDlg(TRUE,_T("PPT"),NULL,OFN_FILEMUSTEXIST|OFN_NONETWORKBUTTON
					|OFN_PATHMUSTEXIST,szFilter);

		_tpath template_path;
		template_path=prog_path/_T("template");
		CString cstTempPath=template_path.c_str();
		FileDlg.m_ofn.lpstrInitialDir=(LPCTSTR)cstTempPath;
		m_PictureList.StopNoBKDrawOnce();

		template_path/=_T("full.ppt");

		// 파일의 경로와 명을 선택
		CString strFileName;

		if (MFile::Exists(template_path) && config_.GetInt(USE_CUSTOM_TEMPLATE)==0)
		{
			strFileName=template_path.string().c_str();
		}
		else
		{
			FileDlg.DoModal();
			strFileName = FileDlg.GetPathName();
		}

		if (strFileName == _T(""))
			return false;

		_Application app; // app is the PowerPoint _Application object
		Presentations Presentations;
		_Presentation Presentation;
		SlideShowView View;
		SlideShowWindow SlideShowWindow;
		SlideShowSettings slideshow;
		Slides slides; 
		_Slide slide;

		if(!app.CreateDispatch(_T("Powerpoint.Application")))
		{
			AfxMessageBox(TransMsg(IDS_FAIL_LOAD_PPT));
			return false;
		}
		else 
		{
			app.SetVisible(TRUE);
		}


		if(!strFileName.IsEmpty())
		{
			Presentations = app.GetPresentations();
			Presentation = Presentations.Open(strFileName,0,0,1);
		}

		DocumentWindow wdw(app.GetActiveWindow());
		Selection sel(wdw.GetSelection());
		SlideRange range(sel.GetSlideRange());

		m_Progress.SetRange(0,f_list.size());
		m_Progress.SetPos(0);
		m_Progress.SetWindowText(TransMsg(IDS_START_BUILD_PPT));

		for (unsigned int f_index=0;f_index<f_list.size();f_index++)
		{
			CString stMsg=_T("[Build] : ") + CString(MCodeChanger::_CCL(f_list[f_index].GetNetPath()).c_str());
			m_Progress.SetWindowText(stMsg);

			_tpath pic_path;
			pic_path= Utility::refinepath(temp_path / MFile::GetFileNameL(MCodeChanger::_CCL(f_list[f_index].GetNetPath())));

			int iRenameCount=0;

			tstring stDestPath=Utility::GetNumericName(iRenameCount,pic_path.c_str());
			iRenameCount++;
		
			while (MFile::ExistsL(stDestPath))
			{
				stDestPath=Utility::GetNumericName(iRenameCount,pic_path.c_str());
				iRenameCount++;
			}

			unsigned char* buffer=NULL;
			__int64 iFileSize;
			WhriaClient.cmd_download(f_list[f_index].GetNetPath(),&buffer,iFileSize);

			MFile::CreateFolder(_tpath(stDestPath).parent_path());
			CFile file;
			// open destination file
			if (file.Open(stDestPath.c_str(), CFile::modeCreate | CFile::modeWrite, NULL) != FALSE)
			{
				file.Write (buffer, iFileSize);
				file.Close();
			}
			delete [] buffer;


			slides=Presentation.GetSlides();
			slide = slides.Item(COleVariant((long)(f_index+1))); 
			if (f_index!=(f_list.size()-1))
//				range.Duplicate();
			slide.Duplicate();

			Shapes shapes(slide.GetShapes());

			long i, shape_count;

			COleDispatchDriver NotePage=COleDispatchDriver(slide.GetNotesPage());
			LPDISPATCH temp_shapes;
			NotePage.InvokeHelper(0x7d3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&temp_shapes, NULL);
			Shapes NoteShapes(temp_shapes);
			Placeholders place_(NoteShapes.GetPlaceholders());

			long place_count=place_.GetCount();
			if (place_count>1)
			{
				Shape temp(place_.Item(2));
				TextFrame frame(temp.GetTextFrame());
				TextRange range(frame.GetTextRange());

				std::string final="[ ";
				final+=f_list[f_index].GetNetPath();
				if (strcmp(f_list[f_index].GetDateString().c_str(),"")!=0)
				{
					final+=" ]  [ ";
					final+=f_list[f_index].GetDateString();
				}
				if (strcmp(f_list[f_index].stPatientID.c_str(),"")!=0)
				{
					final+=" ]  [ ";
					final+=f_list[f_index].stPatientID;
				}
				if (strcmp(f_list[f_index].stPatientName.c_str(),"")!=0)
				{
					final+=" ]  [ ";
					final+=f_list[f_index].stPatientName;
				}
				if (strcmp(f_list[f_index].Diagnosis.stDiagnosis.c_str(),"")!=0)
				{
					final+=" ]  [ ";
					final+=f_list[f_index].Diagnosis.stDiagnosis;
				}
				if (strcmp(f_list[f_index].Diagnosis.stICD10.c_str(),"")!=0)
				{
					final+=" ]  [ ";
					final+=f_list[f_index].Diagnosis.stICD10;
				}
				final+=" ]";

				range.InsertAfter(MCodeChanger::_CCL(final).c_str());
			}

			shape_count = shapes.GetCount();
 
			Shape* pShape;
			pShape=new Shape[shape_count];
			for (i = 1; i <= shape_count; i++)
			{
				COleVariant varindex(i);
				pShape[i-1]=shapes.Item(varindex);
//				CString alttxt = pShape[i-1].GetAlternativeText();
			}

			

			for (i=0;i<shape_count;i++)
			{
				CString alttxt = pShape[i].GetAlternativeText();
				alttxt.MakeLower();
				if (pShape[i].GetHasTextFrame())
				{
					if (alttxt == _T("picture"))
					{
						float width, height, top, left;

						height = pShape[i].GetHeight();
						left   = pShape[i].GetLeft();
						top    = pShape[i].GetTop();
						width  = pShape[i].GetWidth();
						pShape[i].Delete();  // bye bye

						CxImage image(stDestPath.c_str(),CXIMAGE_FORMAT_UNKNOWN);
						int iHeight=image.GetHeight();
						int iWidth=image.GetWidth();
						
						if (iHeight>0 && iWidth>0 && height>0 && width>0)
						{
							if (width*iHeight <= height*iWidth)
							{
								float old_height=height;
								height=iHeight*width/iWidth;
								top+=(old_height-height)/2;
							}
							else
							{
								float old_width=width;
								width=iWidth*height/iHeight;
								left+=(old_width-width)/2;
							}

							Shape newshape(shapes.AddPicture(stDestPath.c_str(),
															 FALSE,
															 TRUE,
															 left,
															 top,
															 width,
															 height));
						}

//						newshape.SetAlternativeText(MFile::GetFileNameL(stDestPath).c_str());
					}
					if (alttxt == _T("filename"))
					{
						TextFrame txtframe(pShape[i].GetTextFrame());
						TextRange txtrng(txtframe.GetTextRange());
						txtrng.SetText(MCodeChanger::_CCL(f_list[f_index].GetNetPath()).c_str());
//						shape.SetAlternativeText(MCodeChanger::_CCL(f_list[f_index].GetNetPath()).c_str());
					}
					if (alttxt == _T("patientid"))
					{
						TextFrame txtframe(pShape[i].GetTextFrame());
						TextRange txtrng(txtframe.GetTextRange());
						txtrng.SetText(MCodeChanger::_CCL(f_list[f_index].stPatientID).c_str());
//						shape.SetAlternativeText(MCodeChanger::_CCL(f_list[f_index].stPatientID).c_str());
					}
					if (alttxt == _T("patientname"))
					{
						TextFrame txtframe(pShape[i].GetTextFrame());
						TextRange txtrng(txtframe.GetTextRange());
						txtrng.SetText(MCodeChanger::_CCL(f_list[f_index].stPatientName).c_str());
//						shape.SetAlternativeText(MCodeChanger::_CCL(f_list[f_index].stPatientName).c_str());
					}
					if (alttxt == _T("diagnosis"))
					{
						TextFrame txtframe(pShape[i].GetTextFrame());
						TextRange txtrng(txtframe.GetTextRange());
						txtrng.SetText(MCodeChanger::_CCL(f_list[f_index].Diagnosis.stDiagnosis).c_str());
//						shape.SetAlternativeText(MCodeChanger::_CCL(f_list[f_index].stPatientName).c_str());
					}
					if (alttxt == _T("icd10"))
					{
						TextFrame txtframe(pShape[i].GetTextFrame());
						TextRange txtrng(txtframe.GetTextRange());
						txtrng.SetText(MCodeChanger::_CCL(f_list[f_index].Diagnosis.stICD10).c_str());
//						shape.SetAlternativeText(MCodeChanger::_CCL(f_list[f_index].stPatientName).c_str());
					}
					if (alttxt == _T("date"))
					{
						TextFrame txtframe(pShape[i].GetTextFrame());
						TextRange txtrng(txtframe.GetTextRange());
						txtrng.SetText(MCodeChanger::_CCL(f_list[f_index].GetDateString()).c_str());
//						shape.SetAlternativeText(MCodeChanger::_CCL(f_list[f_index].stPatientName).c_str());
					}
				}
			}
			delete [] pShape;

			m_Progress.SetPos(i+1);
			stMsg=_T("[Build] : ") + CString(MCodeChanger::_CCL(f_list[f_index].GetNetPath()).c_str());
			m_Progress.SetWindowText(stMsg);
		}

		_tpath dest_ppt_path((LPCTSTR)dest_path);
		dest_ppt_path/=_T("slide.ppt");

		int iRenameCount=0;

		tstring stDestPath=Utility::GetNumericName(iRenameCount,dest_ppt_path.c_str());
		iRenameCount++;

		while (MFile::ExistsL(stDestPath))
		{
			stDestPath=Utility::GetNumericName(iRenameCount,dest_ppt_path.c_str());
			iRenameCount++;
		}

		Presentation.SaveAs(_tpath(stDestPath).c_str(), 1, FALSE);
//		wdw.Close();
//		app.Quit();
		AfxMessageBox(_tpath(stDestPath).c_str());

		m_Progress.SetWindowText(stDestPath.c_str());
		m_Progress.SetPos(f_list.size());
		MFile::DeleteAllL(temp_path.c_str());
		return true;

	}
	catch(std::exception& e)
	{
		e.what();
//		log << MCodeChanger::_CCW(e.what()) << _T("\n");
		return false;
	}
	catch(...)
	{
		MessageBeep(MB_ICONHAND);
		return false;
	}

}

BOOL CWhriaViewDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

void CWhriaViewDlg::OnPopupListRename()
{
	// TODO: Add your command handler code here

	fileinfo fileinfo_;
	if ((int)m_SelectedImage.size()!=m_PictureList.GetItemCount())
		return;

	int iInsertCount=0;
	int iSelected=-1;
	for (int i=0;i<m_PictureList.GetItemCount();i++)
	{
		if (m_PictureList.GetCheck(i))
		{
			fileinfo_=m_SelectedImage[i];iInsertCount++;
			iSelected=i;
		}
	}

	if (iInsertCount!=1) return;
	if (MFile::IsDirL(MCodeChanger::_CCL(fileinfo_.GetNetPath())))
		return;

	tstring stNetPath=MCodeChanger::_CCL(fileinfo_.GetNetPath());
	tstring oldname(MFile::GetFileNameL(stNetPath));
	_tpath oldpath(stNetPath);
	_tpath rootpath(oldpath.parent_path());

	CDialogInput m_dlg(MFile::GetFileNamesExtL(oldname).c_str());
	try
	{
		m_PictureList.StopNoBKDrawOnce();
		if (m_dlg.DoModal()==IDOK)
		{
			StopAll();

			m_dlg.m_InputBox+=MFile::GetFileExtL(oldname).c_str();

			_tpath newpath= Utility::refinepath(rootpath / (LPCTSTR)m_dlg.m_InputBox);
			
			if (_tcscmp(newpath.c_str(),oldpath.c_str())!=0 
				&& m_dlg.m_InputBox!=_T(""))
			{
				WhriaClient.renamefile(MCodeChanger::_CCU(oldpath.c_str())
					,MCodeChanger::_CCU(newpath.c_str()));

				m_PictureList.SetItemText(iSelected,0,MFile::GetFileNamesExtL(newpath.c_str()).c_str());
				m_PictureList.Invalidate(false);
				m_PictureList.SetItemToolTipText(iSelected,0,newpath.c_str());

				m_Progress.SetWindowText(TransMsg(IDS_RENAME_FILE) + CString(oldpath.c_str())
					+ _T(" -> ") + CString(newpath.c_str()));

				m_SelectedImage[iSelected].stNetPath=MCodeChanger::_CCU(newpath.c_str());
			}
		}
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	UpdateCheckList();

}

void CWhriaViewDlg::OnPopupTreeUpload()
{
	// TODO: Add your command handler code here
	HTREEITEM pTreeUpload=m_FolderTree.GetSelectedItem();
	if (pTreeUpload==NULL) return;
		
	CString dumy=ChooseFolder(TransMsg(IDS_SELECT_FOLDER3));
	if (dumy==_T(""))
		return;

	UploadFolder((LPCTSTR)dumy,pTreeUpload);
}

void CWhriaViewDlg::OnPopupListUpload()
{
	// TODO: Add your command handler code here
	static TCHAR BASED_CODE szFilter[] = _T("Photo Files (*.jpg, *.jpeg, *.tiff)|*.jpg;*.jpeg;*.tiff||");
	CFileDialog FileDlg(TRUE,_T("Photo Files"),NULL
		,OFN_ALLOWMULTISELECT
//		|OFN_FILEMUSTEXIST
		|OFN_NONETWORKBUTTON
//		|OFN_PATHMUSTEXIST
		,szFilter);

//		FileDlg.m_ofn.lpstrInitialDir=(LPCTSTR)cstTempPath;
	filepath_list path_list;
//	FileDlg.DoModal();
	CString tmpBuffer;
    FileDlg.m_ofn.lpstrFile = tmpBuffer.GetBuffer(40960);
    FileDlg.m_ofn.nMaxFile = 40960;


	m_PictureList.StopNoBKDrawOnce();
	if(IDCANCEL != FileDlg.DoModal())
	{
		for(POSITION pos=FileDlg.GetStartPosition(); pos !=NULL;)
			path_list.push_back(MCodeChanger::_CCU((LPCTSTR)FileDlg.GetNextPathName(pos)));
	}

	UploadFiles(path_list);
}

void CWhriaViewDlg::OnNMClickTreeRemote(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
//	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	bTreeLeftClick=true;
	*pResult = 0;
}

void CWhriaViewDlg::OnHdnItemchangedListComment(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (bCheckControl)
	{
		bCheckControl=false;return;
	}

	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    if (pNMListView->uOldState == 0 && pNMListView->uNewState == 0)
        return;    // No change



    // Old check box state

    BOOL bPrevState = (BOOL)(((pNMListView->uOldState & 
                LVIS_STATEIMAGEMASK)>>12)-1);  
    if (bPrevState < 0)    // On startup there's no previous state 
		return;
//        bPrevState = 0; // so assign as false (unchecked)


    // New check box state

    BOOL bChecked = 
            (BOOL)(((pNMListView->uNewState & LVIS_STATEIMAGEMASK)>>12)-1);   
    if (bChecked < 0) // On non-checkbox notifications assume false
		return;
//        bChecked = 0; 
 
    if (bPrevState == bChecked) // No change in check box

        return;

	if (bChecked==FALSE && bPrevState==TRUE && bMutexCheck_comment==true)
	{
		if (pNMListView->iItem!=(int)active_comment_list_.size() && pNMListView->iItem<(int)active_comment_list_.size())
		{
			if (GetCheckedListCount()!=active_comment_list_[pNMListView->iItem].size())
			{
				UndoAddCheckedComment(pNMListView->iItem);
				return;
			}
		}
//		if (pNMListView->iItem!=active_comment_list_.size())
//			return;
		bCheckControl=true;
		m_CommentList.SetCheck(pNMListView->iItem,true);
		return;
	}
	if (bChecked==TRUE && bPrevState==FALSE && bMutexCheck_comment==true)
	{
		if (pNMListView->iItem!=(int)active_comment_list_.size() && pNMListView->iItem<(int)active_comment_list_.size())
		{
			if (GetCheckedListCount()!=active_comment_list_[pNMListView->iItem].size())
			{
				AddCheckedComment(pNMListView->iItem);
				return;
			}
		}
		if (pNMListView->iItem!=active_comment_list_.size())
			return;
		bCheckControl=true;
		m_CommentList.SetCheck(pNMListView->iItem,false);
		return;
	}
    // ....

}

void CWhriaViewDlg::OnDiagnosisUserdiagnosis()
{
	// TODO: Add your command handler code here

	CCustomDiagnosisList m_dlg(WhriaClient,m_DxListCtrl,m_SelectedImage);
	m_PictureList.StopNoBKDrawOnce();
	m_dlg.DoModal();
}

void CWhriaViewDlg::OnUploadUploadex()
{
	// TODO: Add your command handler code here
	CString stDestFolder=ChooseFolder(TransMsg(IDS_UPLOAD_FOLDER));
	if (stDestFolder==_T("")) return;

	try
	{
		CProgressDialog m_dlg(WhriaClient,config_);
		m_dlg.UploadEx((LPCTSTR)stDestFolder);
		m_PictureList.StopNoBKDrawOnce();
		m_dlg.DoModal();
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}

//	BrowseTree(pTree);
	UpdateData_FileInfo(fileinfo(),false);
	bTerminateBrowseThread=true;
	bTerminateLoadingThread=true;

	HTREEITEM pTree=m_FolderTree.GetRootItem();

	boost::thread LoadThread(boost::bind(&CWhriaViewDlg::BrowseTree,this,pTree));

}

void CWhriaViewDlg::OnStnClickedStaticF12()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_DX)->SetFocus();
}

void CWhriaViewDlg::OnEnKillfocusEditInput()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_Input.IsEmpty())
		m_StaticF12.ShowWindow(SW_SHOW);
}

void CWhriaViewDlg::OnSetfocusEditInput() 
{
	// TODO: Add your control notification handler code here
	m_StaticF12.ShowWindow(SW_HIDE);
	UpdateData(TRUE);
	m_Input=_T("");
	UpdateData(FALSE);
}

void CWhriaViewDlg::OnPopupDisselectall()
{
	// TODO: Add your command handler code here

	int iCurrentMonitor=GetCurrentMonitor();
	if (ImageDisplay[iCurrentMonitor]->bImageOn)
	{
		ProcessRotate(iCurrentMonitor);
		HidePictureMultiMon(iCurrentMonitor);
	}
	else
	{
		Unselectall();
		for (int i=0;i<iMonitorCount;i++)
		{
			HidePictureMultiMon(i);
		}
	}

}

void CWhriaViewDlg::OnLbnDblclkListChecklist()
{
	// TODO: Add your control notification handler code here

	UINT iIndex=m_CheckList.GetCurSel();
	if (iIndex!=LB_ERR)
	{
		fileinfo* temp=(fileinfo*)m_CheckList.GetItemDataPtr(iIndex);

		for (unsigned int i=0;i<m_SelectedImage.size();i++)
		{
			if (strcmp(temp->GetNetPath().c_str(),m_SelectedImage[i].GetNetPath().c_str())==0)
			{
				OnNMClickListPicturelist(i);
				return;
			}
		}
	}
}

void CWhriaViewDlg::CheckIdleThread()
{
	while (1)
	{
		Sleep(1000*config_.GetInt(IDLE_HIDE_SCREEN)*60+1000);
		if (!bIdleDoModal && Utility::GetLastInputTime()>=config_.GetInt(IDLE_HIDE_SCREEN)*60)
		{
			bCheck_idleprocess=false;
			if (GetSafeHwnd())
				PostMessage(WM_IDLEPROCESS,NULL,NULL);
			bCheck_idleprocess=true;
		}
	}
}


void CWhriaViewDlg::OnToolReport()
{
	// TODO: Add your command handler code here

	CDatePicker m_dlg;
	m_PictureList.StopNoBKDrawOnce();
	if (m_dlg.DoModal()!=IDOK)
		return;

	std::string stDateFrom=Utility::GetDateString(boost::posix_time::from_time_t(m_dlg.m_DateFrom.GetTime()));
	std::string stDateTo=Utility::GetDateString(boost::posix_time::from_time_t(m_dlg.m_DateTo.GetTime()));

	try
	{
		fileinfo_list f_list;
		WhriaClient.searchfile_by_date(stDateFrom,stDateTo,f_list);
		ExportXLS(f_list,MCodeChanger::_CCL(stDateFrom));
	}
	catch (const client_connection::ConnectionEx& err_)
	{
//		m_FolderTree.SetItemText(hItem,olditemtext);
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}

}

bool CWhriaViewDlg::ExportXLS(fileinfo_list& f_list,const tstring& stSheetName=_T("Report"))
{
	if (f_list.empty())
	{
		MessageBox(TransMsg(IDS_NO_PHOTO_REPORT));
		return false;
	}
	/*
	if (f_list.size()>100)
	{
		CString output;
		output.Format(_T("The number of photos is [ %d ]. Are you sure to export all of them?"),f_list.size());
		if (MessageBox(output,_T("Too Many Photos"),MB_YESNO)!=IDYES)
			return false;
	}
	*/

	_tpath prog_path=boost::filesystem::initial_path<_tpath>();
	_tpath temp_path=_tpath(MCodeChanger::_CCL(config_.server_config.Get(TMP_PATH)));
	MFile::CreateFolderL(temp_path.c_str());

	CString dest_path=ChooseFolder(TransMsg(IDS_SELECT_FOLDER2));
	if (dest_path==_T(""))
		return false;

	std::sort(f_list.begin(),f_list.end(),sort_fileinfo_by_ID());

	std::vector<int> file_number;

	file_number.push_back(1);

	if (f_list.size()>1)
	{
//		bool bErase=false;

		for (unsigned int i=f_list.size()-1;i>0;i--)
		{
			if (f_list[i].Diagnosis==f_list[i-1].Diagnosis &&
				strcmp(f_list[i].stPatientID.c_str(),f_list[i-1].stPatientID.c_str())==0)
			{
				std::string stUpper=Utility::GetDateString(f_list[i-1].Time);
				std::string stLower=Utility::GetDateString(f_list[i].Time);
				if (strcmp(HString::Left(stUpper,10).c_str(),
					HString::Left(stLower,10).c_str())==0)
				{
					f_list.erase(f_list.begin()+i);
					file_number[file_number.size()-1]++;
				}
				else
				{
//					bErase=false;
					file_number.push_back(1);
				}
			}
			else
			{
//				bErase=false;
				file_number.push_back(1);
			}
		}
	}

	using namespace YExcel;
	BasicExcel e;
	e.New(1);
	BasicExcelWorksheet* sheet = e.GetWorksheet("Sheet1");
//	BasicExcelCell* cell;

	if (sheet)
	{
		sheet->Cell(0,0)->SetWString(_T("ID"));
		sheet->Cell(0,1)->SetWString(_T("Name"));
		sheet->Cell(0,2)->SetWString(_T("Diagnosis"));
		sheet->Cell(0,3)->SetWString(_T("ICD10"));
		sheet->Cell(0,4)->SetWString(_T("Date"));
		sheet->Cell(0,5)->SetWString(_T("Number of Photos"));

		for (unsigned int i=0; i<f_list.size(); i++)
		{
			sheet->Cell(i+1,0)->SetWString(MCodeChanger::_CCL(f_list[i].stPatientID).c_str());
			sheet->Cell(i+1,1)->SetWString(MCodeChanger::_CCL(f_list[i].stPatientName).c_str());
			sheet->Cell(i+1,2)->SetWString(MCodeChanger::_CCL(f_list[i].Diagnosis.stDiagnosis).c_str());
			sheet->Cell(i+1,3)->SetWString(MCodeChanger::_CCL(f_list[i].Diagnosis.stICD10).c_str());
			sheet->Cell(i+1,4)->SetWString(HString::Left(MCodeChanger::_CCL(f_list[i].GetDateString()),10).c_str());
			sheet->Cell(i+1,5)->Set(file_number[f_list.size()-i-1]);
		}
	}

//	std::sort(f_list.begin(),f_list.end(),sort_fileinfo_by_Time());
//	e.RenameWorksheet(_T("Sheet1"), stSheetName.c_str());

	_tpath dest_ppt_path((LPCTSTR)dest_path);
	dest_ppt_path/=_T("report.xls");

	int iRenameCount=0;

	tstring stDestPath=Utility::GetNumericName(iRenameCount,dest_ppt_path.c_str());
	iRenameCount++;

	while (MFile::ExistsL(stDestPath))
	{
		stDestPath=Utility::GetNumericName(iRenameCount,dest_ppt_path.c_str());
		iRenameCount++;
	}

	e.SaveAs(_tpath(stDestPath).c_str());

	MessageBox(_tpath(stDestPath).c_str());

	m_Progress.SetWindowText(_tpath(stDestPath).c_str());

	return true;
}
void CWhriaViewDlg::OnPopupTreeReport()
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	HTREEITEM hItem=m_FolderTree.GetSelectedItem();

	if (hItem==NULL) return;

	CString path=GetFilePathFromTree(hItem);
	CString cstFolderName=m_FolderTree.GetItemText(hItem);
	try
	{
		fileinfo_list f_list;

		std::string stNetPath=MCodeChanger::_CCU((LPCTSTR)path);
		WhriaClient.searchfile_by_path(stNetPath,f_list);
		for (int i=(f_list.size()-1);i>=0;i--)
		{
			if (f_list[i].GetNetPath().find(stNetPath)!=0)
				f_list.erase(f_list.begin()+i);
		}
		ExportXLS(f_list,(LPCTSTR)cstFolderName);
	}
	catch (const client_connection::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}
	catch (const basic_client::ConnectionEx& err_)
	{
		ErrorExit(err_);
	}

}


HBRUSH CWhriaViewDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_F12)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
	}
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
