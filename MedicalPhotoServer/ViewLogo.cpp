// ViewLogo.cpp : implementation file
//

#include "stdafx.h"
#include "MedicalPhotoServer.h"
#include "ViewLogo.h"


// CViewLogo dialog

IMPLEMENT_DYNAMIC(CViewLogo, CDialog)

CViewLogo::CViewLogo(CWnd* pParent /*=NULL*/)
	: CDialog(CViewLogo::IDD, pParent)
{

}

CViewLogo::~CViewLogo()
{
}

void CViewLogo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_LOGO, m_Logo);
}


BEGIN_MESSAGE_MAP(CViewLogo, CDialog)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CViewLogo message handlers

BOOL CViewLogo::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
//	return CDialog::OnEraseBkgnd(pDC);
}
