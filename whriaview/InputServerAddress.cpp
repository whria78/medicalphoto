// InputServerAddress.cpp : implementation file
//

#include "stdafx.h"
#include "WhriaView.h"
#include "InputServerAddress.h"
#include "../client/whriaclient.h"
#include ".\inputserveraddress.h"
//#include "../autoupdate/autoupdater.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputServerAddress dialog


CInputServerAddress::CInputServerAddress(client_config& c,CWnd* pParent /*=NULL*/)
	: CDialog(CInputServerAddress::IDD, pParent)
	, config_(c)
//	, m_ID(_T(""))
	, bConnected(false)
	, bStop(false)

{
	//{{AFX_DATA_INIT(CInputServerAddress)
//	m_FTP_Pass = _T("");
	//}}AFX_DATA_INIT
}


void CInputServerAddress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputServerAddress)
//	DDX_Text(pDX, IDC_EDIT_PASS, m_FTP_Pass);
	//}}AFX_DATA_MAP
//	DDX_Text(pDX, IDC_EDIT_ID, m_ID);
	DDX_Control(pDX, IDC_EDIT_IP, m_IP);
}


BEGIN_MESSAGE_MAP(CInputServerAddress, CDialog)
	//{{AFX_MSG_MAP(CInputServerAddress)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
//	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnBnClickedButtonUpdate)
ON_WM_CREATE()
ON_BN_CLICKED(IDC_BUTTON_EXIT, &CInputServerAddress::OnBnClickedButtonExit)
ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputServerAddress message handlers

void CInputServerAddress::OnOK() 
{
	// TODO: Add extra validation here
	bStop=true;
	UpdateData(TRUE);

	if (config_.server_config.Compare(MULTIUSER_SUPPORT,1))
	{
//		AfxMessageBox(_T("!"));
		config_.Set(LAST_USER_ID,MCodeChanger::_CCU((LPCTSTR)m_ID));
	}
	else
	{
		config_.LoadDefault(LAST_USER_ID);
	}
	m_IP.GetWindowText(stIPAddress);
	config_.Set(LAST_HOST_ADDRESS,MCodeChanger::_CCU(stIPAddress.GetBuffer(0)));
//	config_.Set(LAST_USER_PASSWD,MCodeChanger::_CCU(m_FTP_Pass.GetBuffer(0)));
	config_.save();

	CDialog::OnOK();
}
bool CInputServerAddress::SearchHost(int iIndex,const std::string& ip,const std::string& port)
{
	if (iIndex<0 || iIndex>255) return false;
	boost::mutex::scoped_lock lock(search_host_mutex[iIndex]);

	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::socket socket_(io_service_);

	client_connection c(io_service_,socket_);
	try
	{
		c.scan(ip,port);
		if (bStop)
			return false;
//		io_service_.stop();
		bConnected=true;
		bStop=true;
		m_IP.SetWindowText(MCodeChanger::_CCL(ip).c_str());
		MessageBeep(MB_ICONASTERISK); // 따랑
//		GetDlgItem(IDC_EDIT_PASS)->SetFocus();
		return true;
	}
	catch (...)
	{
//		m_IP.SetWindowText(MCodeChanger::_CCW(ip).c_str());
		return false;
	}
/*	catch (const client_connection::ConnectionEx& err_)
	{
		return false;
	}
    catch (std::exception& e)
    {
		return false;
	}
*/
}

void CInputServerAddress::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(0);
	
	bStop=true;

//	CDialog::OnOK();
//	CDialog::OnClose();
}

int CInputServerAddress::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}

BOOL CInputServerAddress::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
/*	if (!config_.server_config.Compare(MULTIUSER_SUPPORT,1))
	{
		GetDlgItem(IDC_EDIT_ID)->EnableWindow(false);
		GetDlgItem(IDC_STATIC_ID)->EnableWindow(false);
	}
*/
	tstring old_ip=MCodeChanger::_CCL(config_.Get(LAST_HOST_ADDRESS));

	if (_tcscmp(old_ip.c_str(),_T("localhost"))==0)
		m_IP.SetWindowText(_T(""));
	else
		m_IP.SetWindowText(old_ip.c_str());

/*	if (!config_.server_config.GetInt(MULTIUSER_SUPPORT))
	{
		GetDlgItem(IDC_EDIT_PASS)->EnableWindow(false);
	}
*/
	SetTimer(0,1000,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CInputServerAddress::OnBnClickedButtonExit()
{
	bStop=true;

	CDialog::OnCancel();
	// TODO: Add your control notification handler code here
}

void CInputServerAddress::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent==0)
	{
		KillTimer(0);
		//boost::thread BuildThread(boost::bind(&CInputServerAddress::IPSearch,this));
	}
	CDialog::OnTimer(nIDEvent);
}


HINTERNET CInputServerAddress::GetSession(CString &URL)
{
	// Canonicalization of the URL converts unsafe characters into escape character equivalents
	TCHAR canonicalURL[1024];
	DWORD nSize = 1024;
	InternetCanonicalizeUrl(URL, canonicalURL, &nSize, ICU_BROWSER_MODE);		
	
	DWORD options = INTERNET_FLAG_NEED_FILE|INTERNET_FLAG_HYPERLINK|INTERNET_FLAG_RESYNCHRONIZE|INTERNET_FLAG_RELOAD;
	HINTERNET hSession = InternetOpenUrl(hInternet, canonicalURL, NULL, NULL, options, 0);
	URL = canonicalURL;

	return hSession;
}

// Download a file into a memory buffer
//
bool CInputServerAddress::DownloadConfig(HINTERNET hSession, BYTE *pBuf, DWORD bufSize)
{	
	DWORD	dwReadSizeOut;
	InternetReadFile(hSession, pBuf, bufSize, &dwReadSizeOut);
	if (dwReadSizeOut <= 0)
	{
		return false;
	}

	
	return true;
}

CString CInputServerAddress::GetLocalIP()

{

    WORD wVersionRequested;

    WSADATA wsaData;

    char name[255];

    CString ip; // 여기에 lcoal ip가 저장됩니다.

    PHOSTENT hostinfo;

    wVersionRequested = MAKEWORD( 2, 0 );

 

    if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )

    {

 

        if( gethostname ( name, sizeof(name)) == 0)

        {

              if((hostinfo = gethostbyname(name)) != NULL)

              {

 

                  ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);

 

                }

 

        }      

 

        WSACleanup( );

    }

  return ip;

}

CString CInputServerAddress::IPListing(CStringArray *csaAddress)
{
csaAddress->RemoveAll();

CStringA strTemp;
struct hostent *host;

struct in_addr *ptr; // To retrieve the IP Address 

DWORD dwScope = RESOURCE_CONTEXT;
NETRESOURCEA *NetResource = NULL;
HANDLE hEnum;
WNetOpenEnumA( dwScope, NULL, NULL, 
             NULL, &hEnum );

WSADATA wsaData;
WSAStartup(MAKEWORD(1,1),&wsaData);

if ( hEnum )
{
    DWORD Count = 0xFFFFFFFF;
    DWORD BufferSize = 2048;
    LPVOID Buffer = new char[2048];
    WNetEnumResourceA( hEnum, &Count, 
        Buffer, &BufferSize );
    NetResource = (NETRESOURCEA*)Buffer;

    char szHostName[200];
    unsigned int i;

    for ( i = 0; 
        i < BufferSize/sizeof(NETRESOURCEA); 
        i++, NetResource++ )
    {
        if ( NetResource->dwUsage == 
            RESOURCEUSAGE_CONTAINER && 
            NetResource->dwType == 
            RESOURCETYPE_ANY )
        {
            if ( NetResource->lpRemoteName )
            {
                CStringA strFullName = 
                    NetResource->lpRemoteName;
                if ( 0 == 
                    strFullName.Left(2).Compare("\\\\") )   
                    strFullName = 
                        strFullName.Right(
                            strFullName.GetLength()-2);

                gethostname( szHostName, 
                    strlen( szHostName ) );
                host = gethostbyname(strFullName);

                if(host == NULL) continue; 
                ptr = (struct in_addr *) 
                    host->h_addr_list[0];                    

                // Eg. 211.40.35.76 split up like this.             
                int a = ptr->S_un.S_un_b.s_b1;  // 211           
                int b = ptr->S_un.S_un_b.s_b2;  // 40
                int c = ptr->S_un.S_un_b.s_b3;  // 35
                int d = ptr->S_un.S_un_b.s_b4;  // 76

				if (strFullName!="LOCALHOST")
				{
                strTemp.Format("%s -->  %d.%d.%d.%d",
                    strFullName,a,b,c,d);
				csaAddress->Add(MCodeChanger::_CCW((LPCSTR)strTemp).c_str());
				}
//                AfxMessageBox(strTemp);
            }
        }
    }

    delete Buffer;
    WNetCloseEnum( hEnum ); 
}

WSACleanup();


	CString csResult;
	int i;
	for (i=0;i<csaAddress->GetSize();i++)
	{
		csResult+=csaAddress->GetAt(i)+_T(", ");
//		csResult+=", ";
	}

	if (csResult==_T("")) 
		return _T("");
	else
		return csResult.Left(csResult.GetLength()-2);
}
