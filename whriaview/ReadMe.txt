	if (!AfxOleInit())
	{
		AfxMessageBox("AfxOleInit Error!");
		return FALSE;
	}

	m_List.InsertItem(0,"hihi",0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDragDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
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

void CDragDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDragDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDragDlg::OnBegindragList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY * phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	
	CDropFiles DropFiles;

	DropFiles.AddFile("c:\\11.jpg");
	DropFiles.CreateBuffer();
	
	COleDropSource DropSource;
	COleDataSource DropData;

	HGLOBAL hMem = ::GlobalAlloc(GMEM_ZEROINIT|GMEM_MOVEABLE|GMEM_DDESHARE, DropFiles.GetBuffSize());		
	memcpy( (char*)::GlobalLock(hMem), DropFiles.GetBuffer(), DropFiles.GetBuffSize() );
	::GlobalUnlock(hMem);

	DropData.CacheGlobalData( CF_HDROP, hMem );
	DROPEFFECT de = DropData.DoDragDrop(DROPEFFECT_COPY,NULL);

	*pResult = 0;
}
