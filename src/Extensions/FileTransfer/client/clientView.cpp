// clientView.cpp : implementation of the CClientView class
//
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#include "stdafx.h"
#include "client.h"
#include "MainFrm.h"
#include "clientDoc.h"
#include "CntrItem.h"
#include "clientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CClientView * CCview;
/////////////////////////////////////////////////////////////////////////////
// CClientView

IMPLEMENT_DYNCREATE(CClientView, CRichEditView)

BEGIN_MESSAGE_MAP(CClientView, CRichEditView)
	//{{AFX_MSG_MAP(CClientView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	ON_MESSAGE(WM_AGE1, addmessage)
	ON_MESSAGE(WM_KSEND,OnKSend)
	//}}AFX_MSG_MAP
	// Standard printing commands
ON_COMMAND(ID_CONNECT, OnConnect)
ON_COMMAND(IDC_SEND, OnSend)
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientView construction/destruction

CClientView::CClientView()
{
	// TODO: add construction code here
	chattrue=TRUE;
	//CCview=this;
}

CClientView::~CClientView()
{
}

BOOL CClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}
void CClientView::Message(LPCTSTR lpszMessage,COLORREF clr)
{
	//在窗口中显示聊天信息
	cfm.cbSize=sizeof(cfm);
	cfm.crTextColor=clr;
	cfm.dwMask=CFM_COLOR;
	CString strTemp = lpszMessage;
	
	int len = GetWindowTextLength();
	GetRichEditCtrl().SetSel(len,len);
	
	GetRichEditCtrl().SetSelectionCharFormat(cfm);
	GetRichEditCtrl().ReplaceSel(strTemp);
}
void CClientView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	//add begin
	cfm.cbSize=sizeof(cfm);
	cfm.bCharSet=GB2312_CHARSET;
	cfm.crTextColor=RGB(0,0,0);
	cfm.dwMask=CFM_CHARSET | CFM_COLOR ;
	cfm.dwEffects=0;
	//CRichEditView::GetRichEditCtrl  Call this function to retrieve the CRichEditCtrl object associated with the CRichEditView object.
	//此函数的原型是：CRichEditCtrl& GetRichEditCtrl( ) const; 我对此函数比较熟悉，在微软的WordPad程序中经常用到此函数。
	//CRichEditCtrl::SetDefaultCharFormat  Sets the character formatting attributes for new text in this CRichEditCtrl object.
	GetRichEditCtrl().SetDefaultCharFormat(cfm);
	//add end

	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));
}

/////////////////////////////////////////////////////////////////////////////
// CClientView printing

BOOL CClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}
void CClientView::OnSend() 
{//发消息
     CMainFrame* pWnd=(CMainFrame*)AfxGetMainWnd();
	CEdit* pEdit=(CEdit*)pWnd->m_wndSend.GetDlgItem(IDC_EDIT1);
	CString temp;
	pEdit->GetWindowText(temp);
	if(temp.IsEmpty())
	{
		MessageBox("不能发送空信息!!!","警告");
		pEdit->SetFocus();
		return;
	}

//	temp=temp+"\n";
if(chattrue)
{
	MessageBox("没有连上服务器！！！","警告");
		pEdit->SetFocus();
		return;
}
temp="客户端: "+temp;
	temp=temp+"\n";
Message((LPCTSTR)temp,RGB(255,0,0));
m_chatsocket->Send(temp.GetBuffer(0),255);
temp.ReleaseBuffer();
pWnd->m_wndSend.GetDlgItem(IDC_EDIT1)->SetFocus();
	pEdit->SetWindowText("");
}
LRESULT CClientView::OnKSend(WPARAM wParam,LPARAM lParam)
{
	OnSend();
	return 0;
}

//工具条上的“连接”按钮的消息响应函数。
void CClientView::OnConnect() 
{
	//联接服务器
    CMainFrame* pWnd=(CMainFrame*)AfxGetMainWnd();
	CClient1App* pApp=(CClient1App*)AfxGetApp();
	
	CString str;
	int beDownloading;
	beDownloading=0;
	//m_work变量，对应于那个显示“文件下载进度”的List控件。
	//用下面的这个循环来查看是否有文件正在下载。
	for(int i = 0; i<pWnd->m_work.m_ListCtrl->GetItemCount(); i++)
	{
		str =pWnd->m_work.m_ListCtrl->GetItemText(i,4);
		if(strcmp(str, "下载中") == 0)
		{
			beDownloading++;
		}
	}

	if(beDownloading>0)
	{
		AfxMessageBox("有文件正在下载!!!");
	}
	else
	{
		CString aaa;
		//获取在工具条上的“子窗口控件”中设定的IP地址串。
		pWnd->m_ip1.GetWindowText(m_csIP);
		g_csIP=m_csIP;
	
		m_down[0]=new cdownload(0);
		//给服务器发送type=0的命令(所谓的LIST命令)，以获取服务上可下载的文件信息列表。
		int cc=m_down[0]->SendListCmd();
		//如果不是“服务器接不上！”，则
		if(cc!=-1)
		{
			//如果聊天socket还没有接好，则
			if(chattrue)
			{
				m_chatsocket=new mysocket(this);
				m_chatsocket->Create();
				m_chatsocket->Connect(m_csIP,8888);
				chattrue=FALSE;//设为false，表示聊天socket已经连接好了。
			}
			aaa="传圣----客户端已启动";
			pApp->m_pMainWnd->SetWindowText(aaa);
		}
	}
}

LRESULT CClientView::addmessage(WPARAM wParam, LPARAM lParam)
{
	//显示信息
//	MessageBox("aaa");
	LPCTSTR pStr = (LPCTSTR)wParam;

Message(pStr,RGB(0,0,0));
return 1;
}
void CClientView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CRichEditView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// CClientView diagnostics

#ifdef _DEBUG
void CClientView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CClientView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CClientDoc* CClientView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClientDoc)));
	return (CClientDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClientView message handlers
