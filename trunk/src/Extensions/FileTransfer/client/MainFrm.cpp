// MainFrm.cpp : implementation of the CMainFrame class
//
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#include "stdafx.h"
#include "client.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//extern afx_msg LRESULT ontwo(WPARAM wParam,LPARAM lParam);
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_MESSAGE(CLT_ON,on)
	ON_MESSAGE(CLT_ONSETWO,OnSetwo)
	ON_MESSAGE(CLT_ONSE,OnClient)
	ON_MESSAGE(AA,Onright)
	ON_MESSAGE(BB,Onclick)
	//	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	for(int i=0;i<10;i++)
		down[i]=NULL;

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	//add begin
	//创建用来显示“在线文件列表”的子窗口。
	if (!m_wndOnline.Create(this, IDD_DIALOG1, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,IDD_DIALOG1))
	{
		TRACE0("Failed to create Dialog bar\n");
		return -1;      // fail to create
	}
	//创建用来显示“文件下载进度”的子窗口。
	if (!m_work.Create(this, IDD_DIALOG3, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,IDD_DIALOG3))
	{
		TRACE0("Failed to create Dialog bar\n");
		return -1;      // fail to create
	}
	//创建用来跟服务器聊天的子窗口。
	if (!m_wndSend.Create(this, IDD_DIALOG4, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,IDD_DIALOG4))
	{
		TRACE0("Failed to create Dialog bar\n");
		return -1;      // fail to create
	}

	int i,j;

	static struct
	{
		LPSTR psztext;
		int ui;
	} columns[] = 
	{
		_T("文件名"), LVCFMT_LEFT,
			_T("大小")	, LVCFMT_CENTER,
			_T("时间")	, LVCFMT_CENTER,
	};

	//	for( i=0,j=260;i<sizeof(columns)/sizeof(columns[0])-1;i++,j-=10)
	//向“在线文件列表”窗口中的List控件中插入3个columns，对应于columns结构体数组的3个元素。
	for( i=0,j=260;i<sizeof(columns)/sizeof(columns[0]);i++,j-=10)//added by yjk
		m_wndOnline.m_ListCtrl->InsertColumn(i,columns[i].psztext,columns[i].ui,j);//最后一个参数表示：这一栏的宽度。

	m_wndOnline.m_ListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_wndOnline.m_ListCtrl->ModifyStyleEx(0, WS_EX_CLIENTEDGE);

	static struct
	{
		LPSTR psztext;
		int ui;
	} columns1[]=
	{
		_T("下载文件")	, LVCFMT_LEFT,
			_T("|0%                          |50%                         |100%"), LVCFMT_LEFT,
			_T("速率 k/s")	, LVCFMT_CENTER,
			_T("已下载/k")	, LVCFMT_LEFT,
			_T("状态")		, LVCFMT_CENTER,
	};

	//向“文件下载进度”窗口中的List控件中插入5个columns，对应于columns1结构体数组的5个元素。
	for( i=0,j=254;i<sizeof(columns1)/sizeof(columns1[0]);i++,j-=5)
	{
		if(i>1)	
			m_work.m_ListCtrl->InsertColumn(i,columns1[i].psztext,columns1[i].ui,80);//最后一个参数表示：这一栏的宽度。
		else
			m_work.m_ListCtrl->InsertColumn(i,columns1[i].psztext,columns1[i].ui,j);//最后一个参数表示：这一栏的宽度。
	}

	m_work.	m_ListCtrl->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	//add end

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//add begin
	m_wndOnline.EnableDocking(CBRS_ALIGN_TOP);
	DockControlBar(&m_wndOnline, AFX_IDW_DOCKBAR_TOP);
	m_wndOnline.SetWindowText(_TEXT("在线列表"));

	m_work.EnableDocking(CBRS_ALIGN_TOP);
	DockControlBar(&m_work, AFX_IDW_DOCKBAR_TOP);
	m_work.SetWindowText(_TEXT("文件下载进度"));

#define BUTTON_INDEX 2
	//CToolBar::SetButtonInfo  Call this member function to set the button's command ID, style, and image number.
	//将工具条上的第2个按钮(从0开始计数)设定为一个TBBS_SEPARATOR，并且将其宽度设定为160。
	m_wndToolBar.SetButtonInfo(BUTTON_INDEX,ID_IP,TBBS_SEPARATOR,160);
	CRect rect=NULL;
	m_wndToolBar.GetItemRect(BUTTON_INDEX,&rect);//(top=0,bottom=39,left=72,right=232)
	//调用下面的这一句代码，在工具条上的第2个(从0开始计数)按钮的位置处，创建了一个属于
	//工具条窗口的子窗口，这样
	//就把工具条上的第二个按钮给盖住了。并且由于这是一个子窗口(WS_CHILD)，所以，能随着父窗口
	//一起移动。
	if(!m_ip1.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP,rect,&m_wndToolBar,ID_IP))
		return -1;
	m_ip1.SetWindowText("127.0.0.1");//设定一个缺省的IP地址，省得我每次都要输入了。

	m_wndSend.EnableDocking(CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_wndSend, AFX_IDW_DOCKBAR_BOTTOM);
	m_wndSend.SetWindowText(_TEXT("发送窗口"));
	//CFrameWnd::ShowControlBar  Call this member function to show or hide the control bar.
	//显示那个聊天用的子窗口(属于主框架窗口的)。
	ShowControlBar(&m_wndSend,TRUE,TRUE);
	//add end

	return 0;
}

//处理CLT_ONSETWO消息用的函数。
//用来刷新“文件下载进度”窗口中的List控件的内容。
//参数1：filedono数组的下标；参数2：指向一个字符数组的指针。
LRESULT CMainFrame::OnSetwo(WPARAM wParam, LPARAM lParam)
{
	//更新进度
	char* dat2;
	int * dat;
	dat=(int *)wParam;
	dat2=(char*)lParam;
	int noth;//数组的下标。
	noth=*dat;
	//获取字符数组中的头20个元素中存的那个串，其内容的是：已下载的字节数。
	//CListCtrl::SetItemText  Changes the text of a list view item or subitem.
	//参数1：nItem  Index of the item whose text is to be set. 
	m_work.m_ListCtrl->SetItemText(filedono[noth],3,dat2);
	//获取字符数组中的从第21个元素开始往后存的串，其内容的是：下载的速率。
	m_work.m_ListCtrl->SetItemText(filedono[noth],2,&dat2[20]);

	//果不出我的所料，"zm"的确是一个暗号。
	//'|'字符的ASCII码值是124，大于'z'字符的ASCII码值122，所以，如果串“|||...”要比
	//串“zm”大，这样，strcmp就会返回一个大于0的值。
	//如果字符数组中的从第41个元素开始往后存的串，其内容不是"zm"，则
	if(strcmp(&dat2[40],"zm"))
		//设置List控件的第1column的内容，就是那个表示下载百分比的串“||||||...”
		m_work.m_ListCtrl->SetItemText(filedono[noth],1,&dat2[40]);
	return 1;
}

//处理CLT_ON消息用的函数。
//作用是：把从服务器端获取的可下载的文件的信息列表显示到List控件中。
//参数：根本就没用到！
LRESULT CMainFrame::on(WPARAM wParam,LPARAM lParam)
{
	//显示文件
	m_wndOnline.m_ListCtrl->DeleteAllItems();
	int i;
	i=0;
	//如果zmfile[i].name的内容不是"none"，则循环就继续执行
	while(strcmp(zmfile[i].name,"none"))
	{
		//作者根本就没用到参数，这里是在使用全局数组zmfile直接传递数据。
		//向“可下载文件列表”List控件中添加一个item.
		m_wndOnline.m_ListCtrl->AddItem(&zmfile[i]);
		i++;
	}
	return 1;
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	//add begin
	cs.cx=GetSystemMetrics(SM_CXSCREEN);
	cs.cy=GetSystemMetrics(SM_CYSCREEN);
	//add end

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

//文件的下载操作完成之后的处理工作，由本函数来完成。
DWORD CMainFrame::finish()
{
	int thno;
	thno=clno;
	CString aaa;
	aaa=zmfile[thno].name;
	aaa=aaa+"　文件下载正在下载。。。。\n";
	AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
	aaa.ReleaseBuffer();
	now=GetTickCount();

	/*
	DWORD WaitForMultipleObjects(
	DWORD nCount,             // number of handles in array
	CONST HANDLE *lpHandles,  // object-handle array
	BOOL bWaitAll,            // wait option
	DWORD dwMilliseconds      // time-out interval
	);
	//第三个参数设为true，那么the function returns when the state of all objects in the lpHandles array is signaled.
	*/
	//详细的解释，参见Jeffrey Richter的书《Programming Application for Microsoft Windows》
	//等待多个事件对象，这样，流程执行到这里后就被阻塞了，直至所有的下载线程都完成了下载任务之后。
	HRESULT ret=WaitForMultipleObjects(BLOCK,m_thread[thno],TRUE,INFINITE);

	int i;
	i=0;
	for(int j=0;j<BLOCK;j++)
		i+=down[thno]->good[j];
	//由于此文件已经被下载完了，所以需要把对应的down数组元素置为NULL，表示“非正在下载中”。
	down[thno]=NULL;
	end=GetTickCount();

	if(i==BLOCK)
	{
		aaa=zmfile[thno].name;
		aaa=aaa+"　文件下载完毕！\n";
		AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
		aaa.ReleaseBuffer();
		CString temp;
		m_work.m_ListCtrl->SetItemText(filedono[thno],1,"|||||||||||||||||||||||||||||||||||||||||||||||||||");
		m_work.m_ListCtrl->SetItemText(filedono[thno],4,"已完成");
		temp.Format("文件下载完毕，用时  %d  秒\n",((end-now)/1000));
		temp=zmfile[thno].name+temp;
		AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)temp.GetBuffer(0),1);
		temp.ReleaseBuffer();
		for(j=0;j<BLOCK;j++)
		{
			CString bbb;
			bbb.Format("%s.down%d",zmfile[thno].name,j);
			//The DeleteFile function deletes an existing file. 
			//删除辅助文件。
			DeleteFile(bbb.GetBuffer(0));
			bbb.ReleaseBuffer();
		}

		//我觉得，成功地下载完了之后，那个XX.down文件也可以删除了。
		temp.Format("%s.down",zmfile[thno].name);
		DeleteFile(temp);//added by yjk 
	}
	return 1;
}

//建立各下载文件的线程，参数是：用户用鼠标双击的List控件中的当前item的索引值。
void CMainFrame::createthread(int threadno)
{
	DWORD dwthread;
	//建立BLOCK个线程，同时下载一个文件的不同片段。
	for(int i=0;i<BLOCK;i++)
	{
		//
		m_thread[threadno][i]=::CreateThread(NULL,0,downthread,(LPVOID)down[threadno],0,&dwthread);
		//The SetThreadPriority function sets the priority value for the specified thread. This value, together with the priority class of the thread's process, determines the thread's base priority level. 
		::SetThreadPriority(m_thread[threadno][i],THREAD_PRIORITY_HIGHEST);
	}

	//
	::CreateThread(NULL,0,notify,(LPVOID)this,0,&dwthread);
}

//当用户用鼠标双击了“可下载文件列表”List控件的时候，将间接调用此函数，执行下载文件的操作。
//参数1：值为0，没用；参数2：是用户用鼠标双击的List控件中的当前项的在List控件中的索引值。
LRESULT CMainFrame::OnClient(WPARAM wParam,LPARAM lParam) 
{
	//下载文件
	CString str;
	int jj;//用来记录“正在同时下载的文件”的个数。
	jj=0;

	//计算正在下载的文件的个数。
	for(int i = 0; i <m_work.m_ListCtrl-> GetItemCount(); i++)
	{
		str =m_work.m_ListCtrl->GetItemText(i,4 );
		if(strcmp(str, "下载中") == 0)
		{
			jj++;
		}
	}

	//	if(jj>2)//也对，等于3的时候，也满足大于2的条件。
	if(jj>=3)//这样写代码，更容易理解。
	{
		AfxMessageBox("最多同时只能下载3个文件！");
		return 0;
	}

	//GetTickCount  The GetTickCount function retrieves the number of milliseconds that have elapsed since the system was started. It is limited to the resolution of the system timer. To obtain the system timer resolution, use the GetSystemTimeAdjustment function. 
	//获取当前的时间，以毫秒计数。
	now=GetTickCount();

	//此变量的作用是：保存用户用鼠标双击的List控件中的当前项的索引值。
	int* dat;
	dat=(int *)lParam;
	//现在，clno(CMainFrame类的成员变量)的值就是：用户用鼠标双击的List控件中的当前项的
	//索引值了。
	clno=*dat;

	//down数组是用来存储被下载的文件的信息用的，所以，如果某数组元素不为NULL，就说明这个文件
	//已经开始下载了。
	if(down[clno]!=NULL)
	{
		AfxMessageBox("正在被下载！");
		return 0;
	}

	CString aaa;//
	//zmfile[clno].name中存贮的是要被下载的文件的文件名。
	aaa.Format("正在初使化 %s",zmfile[clno].name);
	aaa=aaa+" 信息。。。\n";
	//作者大量地使用了这个函数来发送消息给“子孙窗口”。我以前可从没用过这个函数。
	AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
	aaa.ReleaseBuffer();

	//下载List控件中的第clno个文件，并为它建一个新cdownload类。参数是：“可下载文件列表”List控件中当前列表项的索引。
	down[clno]=new cdownload(clno);
	//开始下载，并初使化。
	int type;

	//调用cdownload::startask函数。目的是：启动一个函数，用来在“文件下载进度”List控件中
	//显示文件下载的进度，速率，完成字节数等信息。仅仅是显示信息而以，跟真正的下载操作无关。
	type=down[clno]->startask(clno);

	if(type==2)
	{
		//用户选择放弃下载此文件了。
		down[clno]=NULL;//added by yjk
		return 0;
	}

	if(type==1)
	{
		AfxMessageBox("文件已下载完！");
		down[clno]=NULL;//added by yjk
		return 0;
	}

	//文件长度小于0
	if(type==-1)
	{
		AfxMessageBox("此文件长度为零或不可读！");
		return 0;
	}

	if(type==-2)
	{
		AfxMessageBox("网络联不上！");
		return 0;
	}

	//建立BLOCK个“下载文件的线程”，参数是：用户用鼠标双击的List控件中的当前item的索引值。
	createthread(clno);
	return 1;
}

//
LRESULT CMainFrame::Onright(WPARAM wParam,LPARAM lParam) 
{
	//开始进程
	CString str;
	int jj;
	jj=0;
	for(int i = 0; i <m_work.m_ListCtrl-> GetItemCount(); i++){
		str =m_work.m_ListCtrl->GetItemText(i,4 );
		if(strcmp(str, "下载中") == 0){
			jj++;

		}
	}

	if(jj>2)
	{AfxMessageBox("最多同时只能下载3个文件！");
	return 0;
	}
	now=GetTickCount();

	CString temp1;

	int* dat;
	dat=(int *)lParam;
	CString temp;
	int noth;
	noth=*dat;
	temp.Format("the cleek is %d",noth);

	//	AfxMessageBox(temp);
	clno=noth;

	if(down[clno]==NULL){
		AfxMessageBox("no");
		return 0;
	}
	for( i=0;i<BLOCK;i++)
		::ResumeThread(m_thread[clno][i]);

	return 1;
	// TODO: Add your message handler code here

}
LRESULT CMainFrame::Onclick(WPARAM wParam,LPARAM lParam) 
{
	//停进程
	CString str;
	int jj;
	jj=0;
	for(int i = 0; i <m_work.m_ListCtrl-> GetItemCount(); i++){
		str =m_work.m_ListCtrl->GetItemText(i,4 );
		if(strcmp(str, "下载中") == 0){
			jj++;

		}
	}

	if(jj>2)
	{AfxMessageBox("最多同时只能下载3个文件！");
	return 0;
	}
	now=GetTickCount();

	CString temp1;

	int* dat;
	dat=(int *)lParam;
	CString temp;
	int noth;
	noth=*dat;
	temp.Format("the cleek is %d",noth);

	//	AfxMessageBox(temp);
	clno=noth;

	if(down[clno]==NULL){
		AfxMessageBox("no");
		return 0;
	}
	for( i=0;i<BLOCK;i++)
		::SuspendThread(m_thread[clno][i]);

	return 1;


}
