// Others.cpp : implementation file
//

#include "stdafx.h"
#include "Configure.h"
#include "Others.h"


// COthers dialog

IMPLEMENT_DYNAMIC(COthers, CDialog)

COthers::COthers(config& c,CWnd* pParent /*=NULL*/)
	: CDialog(COthers::IDD, pParent)
	, m_Thumb_Height(c.GetInt(THUMB_HEIGHT))
	, m_Thumb_Width(c.GetInt(THUMB_WIDTH))
	, m_HospitalName(MCodeChanger::_CCL(c.Get(HOSPITAL_NAME)).c_str())
	, m_bMinimize(c.GetInt(MINIMIZE))
//	, m_bNTService(c.GetInt(NTSERVICE))
	, config_(c)
{

}

COthers::~COthers()
{
}

void COthers::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_THUMB_H, m_Thumb_Height);
	DDX_Text(pDX, IDC_EDIT_THUMB_W, m_Thumb_Width);
	DDX_Text(pDX, IDC_EDIT_HOSPITALNAME, m_HospitalName);
	DDX_Check(pDX, IDC_CHECK_MINIMIZE, m_bMinimize);
	DDX_Check(pDX, IDC_CHECK_NTSERVICE, m_bNTService);
}


BEGIN_MESSAGE_MAP(COthers, CDialog)
END_MESSAGE_MAP()


// COthers message handlers

BOOL COthers::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

/*	if (config_.GetInt(APP_TYPE)==0)
	{
		GetDlgItem(IDC_CHECK_MINIMIZE)->EnableWindow(false);
		GetDlgItem(IDC_CHECK_NTSERVICE)->EnableWindow(false);
	}
*/	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
