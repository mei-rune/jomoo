// client.cpp : Defines the class behaviors for the application.
//*************************************************************
//���ߣ�����
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//��ҳ��http://h2osky.126.com
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

//�������һ�������Ե��̺߳�����
DWORD WINAPI notify(LPVOID lpparam)
{
	CMainFrame* pthis=(CMainFrame*)lpparam;

	//�ļ������ز������֮��Ĵ���
	return pthis->finish();
}

//
DWORD WINAPI timethread(LPVOID lpparam)
{
	//��¼��������cdownload������ݵ�thisָ���
	cdownload* pthis=(cdownload*)lpparam;
	//�����Ĵ�����cdownload��ĳ�Ա����finish1�С�֮����Ҫ��timethread��������Ϊ�м�Ĺ��ɣ�
	//����Ϊ�̺߳���ֻ��ʹ����ͨ������������ʹ����ĳ�Ա���������ԣ���ֻ����ô����ˡ�
	return pthis->finish1();
}

//����1������socket������2���������ݵĻ�����������3��Ҫ���ص��ֽ�����
//�ӷ������˽���һ�����������ݡ�
int readn(SOCKET fd,char *bp,int len)
{
	int cnt;//��������ʣ����ֽ�����
	int rc;
	cnt=len;
	while(cnt>0)
	{
		//Return Values  If no error occurs, recv returns the number of bytes received. If the connection has been gracefully closed, the return value is zero. Otherwise, a value of SOCKET_ERROR is returned, and a specific error code can be retrieved by calling WSAGetLastError.
		rc=recv(fd,bp,cnt,0);
		//��������ˣ���
		if(rc==SOCKET_ERROR)
		{
			CString aaa;
			aaa="���մ���\n";
			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
			aaa.ReleaseBuffer();
			return SOCKET_ERROR;
		}
		//�������has been gracefully closed����
		if(rc==0)
			return len-cnt;//���ص����Ѿ��ɹ������˵��ֽ�����
		bp+=rc;
		cnt-=rc;
	}
	return len;
}

//�������ݸ�socket���ӵ���һ�ˡ�
int sendn(SOCKET fd,char *bp,int len)
{
	int cnt;
	int rc;
	cnt=len;//Ҫ���͵��ֽ�������Length of the data in buf. 
	//����������whileѭ������֤��Ҫ���͵�����ȫ���������ͳ�ȥ�ˡ�
	while(cnt>0)
	{
		rc=send(fd,bp,cnt,0);
		if(rc<0)
		{
			CString aaa;
			aaa="���ʹ���\n";
			AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
			aaa.ReleaseBuffer();
			return -1;
		}
		if(rc==0)
			return len-cnt;
		//������һ�����ݺ󣬻�����ָ��Ҫ�ı䣬
		bp+=rc;
		//Length of the data in bufҲҪ�䡣
		cnt-=rc;
	}
	return len;
}

CString g_csIP;


//�����Ե��̺߳�����
//��������һ��ָ��down[threadno]��ָ�롣
DWORD WINAPI downthread(LPVOID lpparam)
{
	cdownload* pthis=(cdownload*)lpparam;
	//The InterlockedIncrement function increments (increases by one) the value of the specified variable and checks the resulting value. The function prevents more than one thread from using the same variable simultaneously. 
	//ʹpthis->m_index��ֵ��1�������������֣���ʹ��m_index��Ա������ֵ�ı�ĵط�ֻ����
	//һ�������ԣ��Ҳ£����������������Ϊ�����ļ����̵߳ı�ţ���Ч����Ǵ�0��ʼ�ģ����ԣ�
	//����Ĺ��캯���У��˱�������ʼ��Ϊ-1��
	InterlockedIncrement(&pthis->m_index);

	//cdownload���m_index��Ա�����˱����������������������
	//����ִ�������ļ������ĺ�����
	pthis->threadfunc(pthis->m_index);
	return 1;
}

//���������ļ��б�List�ؼ��е�ǰ�б������������Ϊ��������±ꡣ��ʵ��filedono��zmfile��down������������±�ֵ���Ƕ�Ӧ�ģ��ɻ��á�
//�����鱣����ǣ����ļ����ؽ��ȡ�List�ؼ��е�items������ֵ��
int filedono[10];//��Ҳ��һ��ȫ�ֱ�����

//���������ļ��б�List�ؼ��е�ǰ�б������������Ϊ��������±ꡣ��ʵ��filedono��zmfile��down������������±�ֵ���Ƕ�Ӧ�ģ��ɻ��á�
//��������д�ŵ��ǣ��������ļ��б��ȫ����Ϣ����ֵ�Ǵӷ������˵Ķ�ȡ�ģ��Ƿ������˵�ͬ�������е�ֵ��
filesendinfo zmfile[10];//����һ��ȫ�ֱ�����
 

BOOL CClient1App::InitInstance()
{
	//���������������У�������WSAStartup������ʼ����WinSock�����ڶ�Ӧ��WSACleanup������
	//Ҳ���ص����˰ɡ���Ϊ��AppWizard�Զ����ɵ�֧��WinSock�ĳ������У�������û��
	//��WSACleanup�����ĵ��á�
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
	m_pMainWnd->SetWindowText("��ʥ ---- �ͻ���δ����");

	m_pMainWnd->ShowWindow(SW_SHOW);	//�����벻����������ˣ���AppWizard�Զ����ɵġ�
	m_pMainWnd->UpdateWindow();			//�����벻����������ˣ���AppWizard�Զ����ɵġ�

	/*
	//��һ���ִ��뱻��ע�͵��ˣ���Ϊ�������AfxSocketInit()�������Ѿ����ù�WSAStartup�����ˡ�
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
	//MSDN��˵�����ֳ�����ֻ����WinXP�������汾���������Թ��ˣ���Win98��Ҳ��ʵ���������ӣ�������MSDN�������д����źܶ�Ĵ���This control (and therefore the CLinkCtrl class) is available only to programs running under Windows XP and later.
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

