#pragma once


// COthers dialog
#include "../share/config.h"

class COthers : public CDialog
{
	DECLARE_DYNAMIC(COthers)

public:
	COthers(config& c_,CWnd* pParent = NULL);   // standard constructor
	virtual ~COthers();

// Dialog Data
	enum { IDD = IDD_DIALOG_OTHERS };

protected:
	config& config_;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_Thumb_Height;
	int m_Thumb_Width;
	CString m_HospitalName;
	BOOL m_bMinimize;
	BOOL m_bNTService;
public:
	virtual BOOL OnInitDialog();
};
