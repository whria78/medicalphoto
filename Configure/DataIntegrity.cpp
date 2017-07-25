// DataIntegrity.cpp : implementation file
//

#include "stdafx.h"
#include "Configure.h"
#include "DataIntegrity.h"


// CDataIntegrity dialog

IMPLEMENT_DYNAMIC(CDataIntegrity, CDialog)

CDataIntegrity::CDataIntegrity(config& c,CWnd* pParent /*=NULL*/)
	: CDialog(CDataIntegrity::IDD, pParent)
//	, m_BackupFolder(_T(""))
//	, m_CheckDB_Start(FALSE)
	,config_(c)

	, m_BackupFolder(MCodeChanger::_CCL(c.Get(BACKUP_PATH)).c_str())
	, m_CheckDB_Start(c.GetInt(STARTUP_CHECK_DB))
	, iSchedule1(c.GetInt(SCHEDULE_BUILD_DATE))
	, iSchedule2(c.GetInt(SCHEDULE_BUILD_TIME))
	, iCheck1(c.GetInt(SCHEDULE_CHECK_DATE))
	, iCheck2(c.GetInt(SCHEDULE_CHECK_TIME))
	, iBackupTime1(c.GetInt(BACKUP_DATE))
	, iBackupTime2(c.GetInt(BACKUP_TIME))
{

}

CDataIntegrity::~CDataIntegrity()
{
}

void CDataIntegrity::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_B_FOLDER, m_BackupFolder);
	DDX_Control(pDX, IDC_COMBO_B_DATE, m_BackupTime1);
	DDX_Control(pDX, IDC_COMBO_B_TIME, m_BackupTime2);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE1, m_Schedule1);
	DDX_Control(pDX, IDC_COMBO_SCHEDULE2, m_Schedule2);
	DDX_Control(pDX, IDC_COMBO_CHECKDATA1, m_Check1);
	DDX_Control(pDX, IDC_COMBO_CHECKDATA2, m_Check2);
	DDX_Check(pDX, IDC_CHECK_BUILDATSTART, m_CheckDB_Start);
}


BEGIN_MESSAGE_MAP(CDataIntegrity, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_B_SELECT, &CDataIntegrity::OnBnClickedButtonBSelect)
	ON_CBN_SELCHANGE(IDC_COMBO_B_DATE, &CDataIntegrity::OnCbnSelchangeComboBDate)
	ON_CBN_SELCHANGE(IDC_COMBO_SCHEDULE1, &CDataIntegrity::OnCbnSelchangeComboSchedule1)
	ON_CBN_SELCHANGE(IDC_COMBO_CHECKDATA1, &CDataIntegrity::OnCbnSelchangeComboCheckdata1)
END_MESSAGE_MAP()


// CDataIntegrity message handlers

void CDataIntegrity::OnBnClickedButtonBSelect()
{
	// TODO: Add your control notification handler code here
	CString cstFolder=ChooseFolder();
	if (cstFolder!=_T(""))
	{
		m_BackupFolder=cstFolder;
		UpdateData(FALSE);
	}

}

void CDataIntegrity::OnCbnSelchangeComboBDate()
{
	// TODO: Add your control notification handler code here
	UpdateStatus();
}

void CDataIntegrity::OnCbnSelchangeComboSchedule1()
{
	// TODO: Add your control notification handler code here
	UpdateStatus();
}

void CDataIntegrity::OnCbnSelchangeComboCheckdata1()
{
	// TODO: Add your control notification handler code here
	UpdateStatus();
}

BOOL CDataIntegrity::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

/*	if (config_.GetInt(APP_TYPE)==0)
	{
		GetDlgItem(IDC_EDIT_B_FOLDER)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_B_SELECT)->EnableWindow(false);
		GetDlgItem(IDC_COMBO_B_DATE)->EnableWindow(false);
		GetDlgItem(IDC_COMBO_SCHEDULE1)->EnableWindow(false);
		GetDlgItem(IDC_COMBO_CHECKDATA1)->EnableWindow(false);
		GetDlgItem(IDC_COMBO_B_TIME)->EnableWindow(false);
		GetDlgItem(IDC_COMBO_SCHEDULE2)->EnableWindow(false);
		GetDlgItem(IDC_COMBO_CHECKDATA2)->EnableWindow(false);
	}
*/

	m_BackupTime1.AddString(_T("-"));
	m_BackupTime1.AddString(_T("Every Day"));
	m_BackupTime1.AddString(_T("Sun"));
	m_BackupTime1.AddString(_T("Mon"));
	m_BackupTime1.AddString(_T("Tue"));
	m_BackupTime1.AddString(_T("Wed"));
	m_BackupTime1.AddString(_T("Thu"));
	m_BackupTime1.AddString(_T("Fri"));
	m_BackupTime1.AddString(_T("Sat"));
	m_BackupTime1.SetCurSel(iBackupTime1+2);

	m_BackupTime2.AddString(_T("-"));
	m_BackupTime2.AddString(_T("0 AM"));
	m_BackupTime2.AddString(_T("1 AM"));
	m_BackupTime2.AddString(_T("2 AM"));
	m_BackupTime2.AddString(_T("3 AM"));
	m_BackupTime2.AddString(_T("4 AM"));
	m_BackupTime2.AddString(_T("5 AM"));
	m_BackupTime2.AddString(_T("6 AM"));
	m_BackupTime2.AddString(_T("7 AM"));
	m_BackupTime2.AddString(_T("8 AM"));
	m_BackupTime2.AddString(_T("9 AM"));
	m_BackupTime2.AddString(_T("10 AM"));
	m_BackupTime2.AddString(_T("11 AM"));
	m_BackupTime2.AddString(_T("12 AM"));
	m_BackupTime2.AddString(_T("1 PM"));
	m_BackupTime2.AddString(_T("2 PM"));
	m_BackupTime2.AddString(_T("3 PM"));
	m_BackupTime2.AddString(_T("4 PM"));
	m_BackupTime2.AddString(_T("5 PM"));
	m_BackupTime2.AddString(_T("6 PM"));
	m_BackupTime2.AddString(_T("7 PM"));
	m_BackupTime2.AddString(_T("8 PM"));
	m_BackupTime2.AddString(_T("9 PM"));
	m_BackupTime2.AddString(_T("10 PM"));
	m_BackupTime2.AddString(_T("11 PM"));

	m_BackupTime2.SetCurSel(iBackupTime2+1);


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
	m_Schedule2.AddString(_T("0 AM"));
	m_Schedule2.AddString(_T("1 AM"));
	m_Schedule2.AddString(_T("2 AM"));
	m_Schedule2.AddString(_T("3 AM"));
	m_Schedule2.AddString(_T("4 AM"));
	m_Schedule2.AddString(_T("5 AM"));
	m_Schedule2.AddString(_T("6 AM"));
	m_Schedule2.AddString(_T("7 AM"));
	m_Schedule2.AddString(_T("8 AM"));
	m_Schedule2.AddString(_T("9 AM"));
	m_Schedule2.AddString(_T("10 AM"));
	m_Schedule2.AddString(_T("11 AM"));
	m_Schedule2.AddString(_T("12 AM"));
	m_Schedule2.AddString(_T("1 PM"));
	m_Schedule2.AddString(_T("2 PM"));
	m_Schedule2.AddString(_T("3 PM"));
	m_Schedule2.AddString(_T("4 PM"));
	m_Schedule2.AddString(_T("5 PM"));
	m_Schedule2.AddString(_T("6 PM"));
	m_Schedule2.AddString(_T("7 PM"));
	m_Schedule2.AddString(_T("8 PM"));
	m_Schedule2.AddString(_T("9 PM"));
	m_Schedule2.AddString(_T("10 PM"));
	m_Schedule2.AddString(_T("11 PM"));

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
	m_Check2.AddString(_T("0 AM"));
	m_Check2.AddString(_T("1 AM"));
	m_Check2.AddString(_T("2 AM"));
	m_Check2.AddString(_T("3 AM"));
	m_Check2.AddString(_T("4 AM"));
	m_Check2.AddString(_T("5 AM"));
	m_Check2.AddString(_T("6 AM"));
	m_Check2.AddString(_T("7 AM"));
	m_Check2.AddString(_T("8 AM"));
	m_Check2.AddString(_T("9 AM"));
	m_Check2.AddString(_T("10 AM"));
	m_Check2.AddString(_T("11 AM"));
	m_Check2.AddString(_T("12 AM"));
	m_Check2.AddString(_T("1 PM"));
	m_Check2.AddString(_T("2 PM"));
	m_Check2.AddString(_T("3 PM"));
	m_Check2.AddString(_T("4 PM"));
	m_Check2.AddString(_T("5 PM"));
	m_Check2.AddString(_T("6 PM"));
	m_Check2.AddString(_T("7 PM"));
	m_Check2.AddString(_T("8 PM"));
	m_Check2.AddString(_T("9 PM"));
	m_Check2.AddString(_T("10 PM"));
	m_Check2.AddString(_T("11 PM"));

	m_Check2.SetCurSel(iCheck2+1);

	UpdateStatus();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDataIntegrity::UpdateData(BOOL bSaveAndValidate)
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
		if (m_BackupTime1.GetCurSel()!= CB_ERR)
			iBackupTime1=m_BackupTime1.GetCurSel()-2;
		if (m_BackupTime2.GetCurSel()!= CB_ERR)
			iBackupTime2=m_BackupTime2.GetCurSel()-1;
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

		if (iBackupTime1>-3 && iBackupTime1<6)
			m_BackupTime1.SetCurSel(iBackupTime1+2);
		if (iBackupTime2>-2 && iBackupTime2<23)
			m_BackupTime2.SetCurSel(iBackupTime2+1);

	}

	return CDialog::UpdateData(bSaveAndValidate);
}


CString CDataIntegrity::ChooseFolder()
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


void CDataIntegrity::UpdateStatus()
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
/*
	if (iBackupTime1==-2)
		m_BackupTime2.EnableWindow(FALSE);
	else
		m_BackupTime2.EnableWindow(TRUE);
*/
}