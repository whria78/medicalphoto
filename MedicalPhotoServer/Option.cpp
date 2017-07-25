// Option.cpp : implementation file
//

#include "stdafx.h"
#include "MedicalPhotoServer.h"
#include "Option.h"


// COption dialog

IMPLEMENT_DYNAMIC(COption, CDialog)

COption::COption(config& c,CWnd* pParent /*=NULL*/)
	: CDialog(COption::IDD, pParent)
	,config_(c)
	, m_SuperAdminPasswd(MCodeChanger::_CCL(c.Get(SUPERADMIN_ID)).c_str())
	, m_HospitalName(MCodeChanger::_CCL(c.Get(HOSPITAL_NAME)).c_str())
	, m_bAutostart(c.GetInt(AUTO_START))
	, m_bMinimize(c.GetInt(MINIMIZE))
	, m_ThumbnailPath(MCodeChanger::_CCL(c.Get(THUMB_PATH)).c_str())
	, m_Thumb_Height(c.GetInt(THUMB_HEIGHT))
	, m_Thumb_Width(c.GetInt(THUMB_WIDTH))
	, m_CheckDB_Start(c.GetInt(STARTUP_CHECK_DB))
	, iSchedule1(c.GetInt(SCHEDULE_BUILD_DATE))
	, iSchedule2(c.GetInt(SCHEDULE_BUILD_TIME))
	, iCheck1(c.GetInt(SCHEDULE_CHECK_DATE))
	, iCheck2(c.GetInt(SCHEDULE_CHECK_TIME))
{

}

COption::~COption()
{
}

void COption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASS, m_SuperAdminPasswd);
	DDX_Text(pDX, IDC_EDIT_HOSPITAL, m_HospitalName);
	DDX_Check(pDX, IDC_CHECK_AUTOSTART, m_bAutostart);
	DDX_Check(pDX, IDC_CHECK_MINIMIZE, m_bMinimize);
	DDX_Text(pDX, IDC_EDIT_THUMBNAILPATH, m_ThumbnailPath);
	DDX_Text(pDX, IDC_EDIT_THUMBNAILHEIGHT, m_Thumb_Height);
	DDX_Text(pDX, IDC_EDIT_THUMBNAILWIDTH, m_Thumb_Width);
	DDX_Control(pDX, IDC_COMBO_BACKUP1, m_Backup1);
	DDX_Control(pDX, IDC_COMBO_BACKUP2, m_Backup2);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE1, m_Schedule1);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE2, m_Schedule2);
	DDX_Check(pDX, IDC_CHECK_CHECKDB, m_CheckDB_Start);
	DDX_Control(pDX, IDC_COMBO_CHECK1, m_Check1);
	DDX_Control(pDX, IDC_COMBO_CHECK2, m_Check2);
}


BEGIN_MESSAGE_MAP(COption, CDialog)
	ON_BN_CLICKED(IDOK, &COption::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_THUMB_FOLDER, &COption::OnBnClickedButtonChooseThumbFolder)
	ON_CBN_SELCHANGE(IDC_COMBO_SCHEDULE1, &COption::OnCbnSelchangeComboSchedule1)
	ON_CBN_SELCHANGE(IDC_COMBO_CHECK1, &COption::OnCbnSelchangeComboCheck1)
END_MESSAGE_MAP()


// COption message handlers

void COption::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (MessageBox(_T("Are you sure to save?"),_T("Save"),MB_YESNO)==IDYES)
	{
		UpdateData(TRUE);
		config_.Set(ADMIN_PASS,MCodeChanger::_CCU((LPCTSTR)m_SuperAdminPasswd));
		config_.Set(HOSPITAL_NAME,MCodeChanger::_CCU((LPCTSTR)m_HospitalName));
		config_.Set(AUTO_START,m_bAutostart);
		config_.Set(MINIMIZE,m_bMinimize);

		config_.Set(THUMB_HEIGHT,m_Thumb_Height);
		config_.Set(THUMB_WIDTH,m_Thumb_Width);

		config_.Set(THUMB_PATH,MCodeChanger::_CCU((LPCTSTR)m_ThumbnailPath));

		config_.Set(STARTUP_CHECK_DB,m_CheckDB_Start);

		config_.Set(SCHEDULE_BUILD_DATE,iSchedule1);
		config_.Set(SCHEDULE_BUILD_TIME,iSchedule2);
		config_.Set(SCHEDULE_CHECK_DATE,iCheck1);
		config_.Set(SCHEDULE_CHECK_TIME,iCheck2);

		config_.save();
		MessageBox(_T("Restart the application to take a effect"));
		OnOK();
	}
}


void COption::OnBnClickedButtonChooseThumbFolder()
{
	// TODO: Add your control notification handler code here
	CString cstFolder=ChooseFolder();
	if (cstFolder!=_T(""))
	{
		m_ThumbnailPath=cstFolder;
		UpdateData(FALSE);
	}

}
CString COption::ChooseFolder()
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

BOOL COption::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	m_Schedule1.AddString(_T("-"));
	m_Schedule1.AddString(_T("Every Day"));
	m_Schedule1.AddString(_T("Sun"));
	m_Schedule1.AddString(_T("Mon"));
	m_Schedule1.AddString(_T("Tue"));
	m_Schedule1.AddString(_T("Wed"));
	m_Schedule1.AddString(_T("Thu"));
	m_Schedule1.AddString(_T("Fri"));
	m_Schedule1.AddString(_T("Sat"));
	m_Schedule1.SetCurSel(iSchedule1+2);

	m_Schedule2.AddString(_T("-"));
	m_Schedule2.AddString(_T("0"));
	m_Schedule2.AddString(_T("1"));
	m_Schedule2.AddString(_T("2"));
	m_Schedule2.AddString(_T("3"));
	m_Schedule2.AddString(_T("4"));
	m_Schedule2.AddString(_T("5"));
	m_Schedule2.AddString(_T("6"));
	m_Schedule2.AddString(_T("7"));
	m_Schedule2.AddString(_T("8"));
	m_Schedule2.AddString(_T("9"));
	m_Schedule2.AddString(_T("10"));
	m_Schedule2.AddString(_T("11"));
	m_Schedule2.AddString(_T("12"));
	m_Schedule2.AddString(_T("13"));
	m_Schedule2.AddString(_T("14"));
	m_Schedule2.AddString(_T("15"));
	m_Schedule2.AddString(_T("16"));
	m_Schedule2.AddString(_T("17"));
	m_Schedule2.AddString(_T("18"));
	m_Schedule2.AddString(_T("19"));
	m_Schedule2.AddString(_T("20"));
	m_Schedule2.AddString(_T("21"));
	m_Schedule2.AddString(_T("22"));
	m_Schedule2.AddString(_T("23"));

	m_Schedule2.SetCurSel(iSchedule2+1);

	m_Check1.AddString(_T("-"));
	m_Check1.AddString(_T("Every Day"));
	m_Check1.AddString(_T("Sun"));
	m_Check1.AddString(_T("Mon"));
	m_Check1.AddString(_T("Tue"));
	m_Check1.AddString(_T("Wed"));
	m_Check1.AddString(_T("Thu"));
	m_Check1.AddString(_T("Fri"));
	m_Check1.AddString(_T("Sat"));
	m_Check1.SetCurSel(iCheck1+2);

	m_Check2.AddString(_T("-"));
	m_Check2.AddString(_T("0"));
	m_Check2.AddString(_T("1"));
	m_Check2.AddString(_T("2"));
	m_Check2.AddString(_T("3"));
	m_Check2.AddString(_T("4"));
	m_Check2.AddString(_T("5"));
	m_Check2.AddString(_T("6"));
	m_Check2.AddString(_T("7"));
	m_Check2.AddString(_T("8"));
	m_Check2.AddString(_T("9"));
	m_Check2.AddString(_T("10"));
	m_Check2.AddString(_T("11"));
	m_Check2.AddString(_T("12"));
	m_Check2.AddString(_T("13"));
	m_Check2.AddString(_T("14"));
	m_Check2.AddString(_T("15"));
	m_Check2.AddString(_T("16"));
	m_Check2.AddString(_T("17"));
	m_Check2.AddString(_T("18"));
	m_Check2.AddString(_T("19"));
	m_Check2.AddString(_T("20"));
	m_Check2.AddString(_T("21"));
	m_Check2.AddString(_T("22"));
	m_Check2.AddString(_T("23"));

	m_Check2.SetCurSel(iCheck2+1);

	UpdateStatus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL COption::UpdateData(BOOL bSaveAndValidate)
{
	if (bSaveAndValidate)
	{
		if (m_Schedule1.GetCurSel()!= CB_ERR)
			iSchedule1=m_Schedule1.GetCurSel()-2;
		if (m_Schedule2.GetCurSel()!= CB_ERR)
			iSchedule2=m_Schedule2.GetCurSel()-1;
		if (m_Check1.GetCurSel()!= CB_ERR)
			iCheck1=m_Check1.GetCurSel()-2;
		if (m_Check2.GetCurSel()!= CB_ERR)
			iCheck2=m_Check2.GetCurSel()-1;
	}
	else
	{
		if (iSchedule1>-3 && iSchedule1<6)
			m_Schedule1.SetCurSel(iSchedule1+2);
		if (iSchedule2>-2 && iSchedule2<23)
			m_Schedule2.SetCurSel(iSchedule2+1);

		if (iCheck1>-3 && iCheck1<6)
			m_Check1.SetCurSel(iCheck1+2);
		if (iCheck2>-2 && iCheck2<23)
			m_Check2.SetCurSel(iCheck2+1);
	}

	return CDialog::UpdateData(bSaveAndValidate);
}

void COption::OnCbnSelchangeComboSchedule1()
{
	// TODO: Add your control notification handler code here
	UpdateStatus();
}

void COption::OnCbnSelchangeComboCheck1()
{
	// TODO: Add your control notification handler code here
	UpdateStatus();
}

void COption::UpdateStatus()
{
	UpdateData(TRUE);
	if (iSchedule1==-2)
		m_Schedule2.EnableWindow(FALSE);
	else
		m_Schedule2.EnableWindow(TRUE);

	if (iCheck1==-2)
		m_Check2.EnableWindow(FALSE);
	else
		m_Check2.EnableWindow(TRUE);
}
