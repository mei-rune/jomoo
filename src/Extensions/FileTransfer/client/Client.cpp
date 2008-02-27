// client.cpp : Defines the class behaviors for the application.
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#include "stdafx.h"
#include "client.h"
#include "MainFrm.h"
#include "clientDoc.h"
#include "clientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClient1App

BEGIN_MESSAGE_MAP(CClient1App, CWinApp)
	//{{AFX_MSG_MAP(CClient1App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClient1App construction

CClient1App::CClient1App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CClient1App object

CClient1App theApp;

//这仅仅是一个过渡性的线程函数。
DWORD WINAPI notify(LPVOID lpparam)
{
	CMainFrame* pthis=(CMainFrame*)lpparam;

	//文件的下载操作完成之后的处理。
	return pthis->finish();
}

//
DWORD WINAPI timethread(LPVOID lpparam)
{
	//记录的明明是cdownload类的数据的this指针嘛。
	cdownload* pthis=(cdownload*)lpparam;
	//真正的代码在cdownload类的成员函数finish1中。之所以要用timethread函数来作为中间的过渡，
	//是因为线程函数只能使用普通函数，而不能使用类的成员函数，所以，就只好这么设计了。
	return pthis->finish1();
}

//参数1：连接socket；参数2：接受数据的缓冲区；参数3：要下载的字节数。
//从服务器端接受一定数量的数据。
int readn(SOCKET fd,char *bp,int len)
{
	int cnt;//用来保存剩余的字节数。
	int rc;
	cnt=len;
	while(cnt>0)
	{
		//Return Values  If no error occurs, recv returns the number of bytes received. If the connection has been gracefully closed, the return value is zero. Otherwise, a value of SOCKET_ERROR is returned, and a specific error code can be retrieved by calling WSAGetLastError.
		rc=recv(fd,bp,cnt,0);
		//如果出错了，则
		if(rc==SOCKET_ERROR)
		{
			CString aaa;
			aaa="接收错误\n";
			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
			aaa.ReleaseBuffer();
			return SOCKET_ERROR;
		}
		//如果连接has been gracefully closed，则
		if(rc==0)
			return len-cnt;//返回的是已经成功下载了的字节数。
		bp+=rc;
		cnt-=rc;
	}
	return len;
}

//发送数据给socket连接的另一端。
int sendn(SOCKET fd,char *bp,int len)
{
	int cnt;
	int rc;
	cnt=len;//要发送的字节数，即Length of the data in buf. 
	//用下面的这个while循环来保证，要发送的数据全部都被发送出去了。
	while(cnt>0)
	{
		rc=send(fd,bp,cnt,0);
		if(rc<0)
		{
			CString aaa;
			aaa="发送错误\n";
			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
			aaa.ReleaseBuffer();
			return -1;
		}
		if(rc==0)
			return len-cnt;
		//发送完一批数据后，缓冲区指针要改变，
		bp+=rc;
		//Length of the data in buf也要变。
		cnt-=rc;
	}
	return len;
}

CString g_csIP;


//过渡性的线程函数。
//参数：是一个指向down[threadno]的指针。
DWORD WINAPI downthread(LPVOID lpparam)
{
	cdownload* pthis=(cdownload*)lpparam;
	//The InterlockedIncrement function increments (increases by one) the value of the specified variable and checks the resulting value. The function prevents more than one thread from using the same variable simultaneously. 
	//使pthis->m_index的值增1。经过搜索后发现，能使此m_index成员变量的值改变的地方只有这
	//一处！所以，我猜，这个变量是用来作为下载文件的线程的编号，有效编号是从0开始的，所以，
	//在类的构造函数中，此变量被初始化为-1。
	InterlockedIncrement(&pthis->m_index);

	//cdownload类的m_index成员，将此变量用作两个数组的索引。
	//真正执行下载文件操作的函数。
	pthis->threadfunc(pthis->m_index);
	return 1;
}

//“可下载文件列表”List控件中当前列表项的索引，做为此数组的下标。其实，filedono，zmfile，down这三个数组的下标值都是对应的，可互用。
//此数组保存的是：“文件下载进度”List控件中的items的索引值。
int filedono[10];//这也是一个全局变量。

//“可下载文件列表”List控件中当前列表项的索引，做为此数组的下标。其实，filedono，zmfile，down这三个数组的下标值都是对应的，可互用。
//这个数组中存放的是：可下载文件列表的全部信息。其值是从服务器端的读取的，是服务器端的同名数组中的值。
filesendinfo zmfile[10];//这是一个全局变量。
 

BOOL CClient1App::InitInstance()
{
	//在下面的这个函数中，调用了WSAStartup函数初始化了WinSock。至于对应的WSACleanup函数，
	//也许不必调用了吧。因为由AppWizard自动生成的支持WinSock的程序框架中，根本就没有
	//对WSACleanup函数的调用。
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CClientDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CClientView));
	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.

	//add begin
	m_pMainWnd->MoveWindow(0,0,800,600,true);//added by yjk
	m_pMainWnd->CenterWindow();
	m_pMainWnd->SetWindowText("传圣 ---- 客户端未启动");

	m_pMainWnd->ShowWindow(SW_SHOW);	//这句代码不是作者添加了，是AppWizard自动生成的。
	m_pMainWnd->UpdateWindow();			//这句代码不是作者添加了，是AppWizard自动生成的。

	/*
	//这一部分代码被我注释掉了，因为在上面的AfxSocketInit()函数中已经调用过WSAStartup函数了。
	//pList.RemoveAll();
	WORD wVersionRequested;
	WSADATA wsaData;
	// char name[255];
	//PHOSTENT hostinfo;
	wVersionRequested = MAKEWORD( 2, 0 );

	if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
	{
		WSACleanup();
	} 
	*/
	//add end

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	//CLinkCtrl Class  This class wraps the functionality of the SysLink common control.
	//A "link control" provides a convenient way to embed hypertext links in a window. The actual control is a window that renders marked-up text and launches appropriate applications when the user clicks an embedded link. Multiple links are supported within one control and can be accessed by a zero-based index.
	//The CLinkCtrl class provides the functionality of the Windows common SysLink control. 
	//MSDN中说，这种超链接只用于WinXP及后续版本，可是我试过了，在Win98下也能实现正常链接！看来，MSDN的资料中存在着很多的错误！This control (and therefore the CLinkCtrl class) is available only to programs running under Windows XP and later.
	CLinkCtrl	m_mail;
	CLinkCtrl	m_http;

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	virtual BOOL OnInitDialog();
	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIL, m_mail);
	DDX_Control(pDX, IDC_HTTP, m_http);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//m_mail.SetLinkString("http://211.152.147.97/bbs/");
	//m_http.SetLinkString("http://www.sarahclub.com/");
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
// App command to run the dialog
void CClient1App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CClient1App message handlers

