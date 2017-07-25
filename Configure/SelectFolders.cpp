// SelectFolders.cpp : implementation file
//

#include "stdafx.h"
#include "Configure.h"
#include "SelectFolders.h"


// CSelectFolders dialog

IMPLEMENT_DYNAMIC(CSelectFolders, CDialog)

CSelectFolders::CSelectFolders(config& c,CWnd* pParent /*=NULL*/)
	: CDialog(CSelectFolders::IDD, pParent)
	, m_PicturePath(MCodeChanger::_CCL(c.Get(DATA_PATH)).c_str())

	, m_DataRootPath(MCodeChanger::_CCL(c.Get(DATA_ROOT_PATH)).c_str())
	, m_FavoratePath(MCodeChanger::_CCL(c.Get(FAVORATE_PATH)).c_str())
	, m_ThumbnailPath(MCodeChanger::_CCL(c.Get(THUMB_PATH)).c_str())
	, m_TmpPath(MCodeChanger::_CCL(c.Get(TMP_PATH)).c_str())
{

}

CSelectFolders::~CSelectFolders()
{
}

void CSelectFolders::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DATAPATH, m_DataRootPath);
	DDX_Text(pDX, IDC_EDIT_PICTUREPATH, m_PicturePath);
	DDX_Text(pDX, IDC_STATIC_F_FOLDER, m_FavoratePath);
	DDX_Text(pDX, IDC_STATIC_T_FOLDER, m_ThumbnailPath);
	DDX_Text(pDX, IDC_STATIC_TMP_FOLDER, m_TmpPath);
}


BEGIN_MESSAGE_MAP(CSelectFolders, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PICTUREFOLDER, &CSelectFolders::OnBnClickedButtonPicturefolder)
	ON_BN_CLICKED(IDC_BUTTON_DATAFOLDER, &CSelectFolders::OnBnClickedButtonDatafolder)
END_MESSAGE_MAP()


// CSelectFolders message handlers

void CSelectFolders::OnBnClickedButtonPicturefolder()
{
	// TODO: Add your control notification handler code here
	CString cstFolder=ChooseFolder();
	CString compare1=_tpath((LPCTSTR)cstFolder).c_str();
	CString compare2=_tpath((LPCTSTR)m_DataRootPath).c_str();
	if (compare2.Find(compare1)==0 && !compare1.IsEmpty() && !compare2.IsEmpty())
	{
		MessageBox(_T("Data folder (") + m_DataRootPath + _T(") must not include the picture folder (")+cstFolder+_T(")"));
		return;
	}

	if (cstFolder!=_T(""))
	{
		tstring stErrorMsg;
		if (!data_manager::CheckValidPicturePath((LPCTSTR)cstFolder,stErrorMsg))
		{
			MessageBox(stErrorMsg.c_str());
			return;
		}

		m_PicturePath=_tpath((LPCTSTR)cstFolder).c_str();
		UpdateData(FALSE);
	}
}

void CSelectFolders::OnBnClickedButtonDatafolder()
{
	// TODO: Add your control notification handler code here
	CString cstFolder=ChooseFolder();
	CString compare1=_tpath((LPCTSTR)m_PicturePath).c_str();
	CString compare2=_tpath((LPCTSTR)cstFolder).c_str();
	if (compare2.Find(compare1)==0 && !compare1.IsEmpty() && !compare2.IsEmpty())
	{
		MessageBox(_T("The data folder (") + cstFolder + _T(") must not include the picture folder (")+m_PicturePath+_T(")"));
		return;
	}

	if (cstFolder!=_T(""))
	{
		m_DataRootPath=_tpath((LPCTSTR)cstFolder).c_str();

		_tpath datapath((LPCTSTR)m_DataRootPath);
		m_FavoratePath=_tpath(datapath/_T("favorate")).c_str();
		m_ThumbnailPath=_tpath(datapath/_T("thumb")).c_str();
		m_TmpPath=_tpath(datapath/_T("tmp")).c_str();

		MFile::CreateFolderL((LPCTSTR)m_DataRootPath);
		MFile::CreateFolderL((LPCTSTR)m_FavoratePath);
		MFile::CreateFolderL((LPCTSTR)m_ThumbnailPath);
		MFile::CreateFolderL((LPCTSTR)m_TmpPath);

		UpdateData(FALSE);
	}
}

CString CSelectFolders::ChooseFolder()
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
//	csResult.Replace(_T("\\"),_T("/"));
	return csResult;
}
