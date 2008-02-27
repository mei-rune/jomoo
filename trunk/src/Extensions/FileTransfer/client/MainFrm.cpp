// MainFrm.cpp : implementation of the CMainFrame class
//
//*************************************************************
//���ߣ�����
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//��ҳ��http://h2osky.126.com
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
	//����������ʾ�������ļ��б����Ӵ��ڡ�
	if (!m_wndOnline.Create(this, IDD_DIALOG1, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,IDD_DIALOG1))
	{
		TRACE0("Failed to create Dialog bar\n");
		return -1;      // fail to create
	}
	//����������ʾ���ļ����ؽ��ȡ����Ӵ��ڡ�
	if (!m_work.Create(this, IDD_DIALOG3, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,IDD_DIALOG3))
	{
		TRACE0("Failed to create Dialog bar\n");
		return -1;      // fail to create
	}
	//����������������������Ӵ��ڡ�
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
		_T("�ļ���"), LVCFMT_LEFT,
			_T("��С")	, LVCFMT_CENTER,
			_T("ʱ��")	, LVCFMT_CENTER,
	};

	//	for( i=0,j=260;i<sizeof(columns)/sizeof(columns[0])-1;i++,j-=10)
	//�������ļ��б������е�List�ؼ��в���3��columns����Ӧ��columns�ṹ�������3��Ԫ�ء�
	for( i=0,j=260;i<sizeof(columns)/sizeof(columns[0]);i++,j-=10)//added by yjk
		m_wndOnline.m_ListCtrl->InsertColumn(i,columns[i].psztext,columns[i].ui,j);//���һ��������ʾ����һ���Ŀ�ȡ�

	m_wndOnline.m_ListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_wndOnline.m_ListCtrl->ModifyStyleEx(0, WS_EX_CLIENTEDGE);

	static struct
	{
		LPSTR psztext;
		int ui;
	} columns1[]=
	{
		_T("�����ļ�")	, LVCFMT_LEFT,
			_T("|0%                          |50%                         |100%"), LVCFMT_LEFT,
			_T("���� k/s")	, LVCFMT_CENTER,
			_T("������/k")	, LVCFMT_LEFT,
			_T("״̬")		, LVCFMT_CENTER,
	};

	//���ļ����ؽ��ȡ������е�List�ؼ��в���5��columns����Ӧ��columns1�ṹ�������5��Ԫ�ء�
	for( i=0,j=254;i<sizeof(columns1)/sizeof(columns1[0]);i++,j-=5)
	{
		if(i>1)	
			m_work.m_ListCtrl->InsertColumn(i,columns1[i].psztext,columns1[i].ui,80);//���һ��������ʾ����һ���Ŀ�ȡ�
		else
			m_work.m_ListCtrl->InsertColumn(i,columns1[i].psztext,columns1[i].ui,j);//���һ��������ʾ����һ���Ŀ�ȡ�
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
	m_wndOnline.SetWindowText(_TEXT("�����б�"));

	m_work.EnableDocking(CBRS_ALIGN_TOP);
	DockControlBar(&m_work, AFX_IDW_DOCKBAR_TOP);
	m_work.SetWindowText(_TEXT("�ļ����ؽ���"));

#define BUTTON_INDEX 2
	//CToolBar::SetButtonInfo  Call this member function to set the button's command ID, style, and image number.
	//���������ϵĵ�2����ť(��0��ʼ����)�趨Ϊһ��TBBS_SEPARATOR�����ҽ������趨Ϊ160��
	m_wndToolBar.SetButtonInfo(BUTTON_INDEX,ID_IP,TBBS_SEPARATOR,160);
	CRect rect=NULL;
	m_wndToolBar.GetItemRect(BUTTON_INDEX,&rect);//(top=0,bottom=39,left=72,right=232)
	//�����������һ����룬�ڹ������ϵĵ�2��(��0��ʼ����)��ť��λ�ô���������һ������
	//���������ڵ��Ӵ��ڣ�����
	//�Ͱѹ������ϵĵڶ�����ť����ס�ˡ�������������һ���Ӵ���(WS_CHILD)�����ԣ������Ÿ�����
	//һ���ƶ���
	if(!m_ip1.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP,rect,&m_wndToolBar,ID_IP))
		return -1;
	m_ip1.SetWindowText("127.0.0.1");//�趨һ��ȱʡ��IP��ַ��ʡ����ÿ�ζ�Ҫ�����ˡ�

	m_wndSend.EnableDocking(CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_wndSend, AFX_IDW_DOCKBAR_BOTTOM);
	m_wndSend.SetWindowText(_TEXT("���ʹ���"));
	//CFrameWnd::ShowControlBar  Call this member function to show or hide the control bar.
	//��ʾ�Ǹ������õ��Ӵ���(��������ܴ��ڵ�)��
	ShowControlBar(&m_wndSend,TRUE,TRUE);
	//add end

	return 0;
}

//����CLT_ONSETWO��Ϣ�õĺ�����
//����ˢ�¡��ļ����ؽ��ȡ������е�List�ؼ������ݡ�
//����1��filedono������±ꣻ����2��ָ��һ���ַ������ָ�롣
LRESULT CMainFrame::OnSetwo(WPARAM wParam, LPARAM lParam)
{
	//���½���
	char* dat2;
	int * dat;
	dat=(int *)wParam;
	dat2=(char*)lParam;
	int noth;//������±ꡣ
	noth=*dat;
	//��ȡ�ַ������е�ͷ20��Ԫ���д���Ǹ����������ݵ��ǣ������ص��ֽ�����
	//CListCtrl::SetItemText  Changes the text of a list view item or subitem.
	//����1��nItem  Index of the item whose text is to be set. 
	m_work.m_ListCtrl->SetItemText(filedono[noth],3,dat2);
	//��ȡ�ַ������еĴӵ�21��Ԫ�ؿ�ʼ�����Ĵ��������ݵ��ǣ����ص����ʡ�
	m_work.m_ListCtrl->SetItemText(filedono[noth],2,&dat2[20]);

	//�������ҵ����ϣ�"zm"��ȷ��һ�����š�
	//'|'�ַ���ASCII��ֵ��124������'z'�ַ���ASCII��ֵ122�����ԣ��������|||...��Ҫ��
	//����zm����������strcmp�ͻ᷵��һ������0��ֵ��
	//����ַ������еĴӵ�41��Ԫ�ؿ�ʼ�����Ĵ��������ݲ���"zm"����
	if(strcmp(&dat2[40],"zm"))
		//����List�ؼ��ĵ�1column�����ݣ������Ǹ���ʾ���ذٷֱȵĴ���||||||...��
		m_work.m_ListCtrl->SetItemText(filedono[noth],1,&dat2[40]);
	return 1;
}

//����CLT_ON��Ϣ�õĺ�����
//�����ǣ��Ѵӷ������˻�ȡ�Ŀ����ص��ļ�����Ϣ�б���ʾ��List�ؼ��С�
//������������û�õ���
LRESULT CMainFrame::on(WPARAM wParam,LPARAM lParam)
{
	//��ʾ�ļ�
	m_wndOnline.m_ListCtrl->DeleteAllItems();
	int i;
	i=0;
	//���zmfile[i].name�����ݲ���"none"����ѭ���ͼ���ִ��
	while(strcmp(zmfile[i].name,"none"))
	{
		//���߸�����û�õ���������������ʹ��ȫ������zmfileֱ�Ӵ������ݡ�
		//�򡰿������ļ��б�List�ؼ������һ��item.
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

//�ļ������ز������֮��Ĵ��������ɱ���������ɡ�
DWORD CMainFrame::finish()
{
	int thno;
	thno=clno;
	CString aaa;
	aaa=zmfile[thno].name;
	aaa=aaa+"���ļ������������ء�������\n";
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
	//������������Ϊtrue����ôthe function returns when the state of all objects in the lpHandles array is signaled.
	*/
	//��ϸ�Ľ��ͣ��μ�Jeffrey Richter���顶Programming Application for Microsoft Windows��
	//�ȴ�����¼���������������ִ�е������ͱ������ˣ�ֱ�����е������̶߳��������������֮��
	HRESULT ret=WaitForMultipleObjects(BLOCK,m_thread[thno],TRUE,INFINITE);

	int i;
	i=0;
	for(int j=0;j<BLOCK;j++)
		i+=down[thno]->good[j];
	//���ڴ��ļ��Ѿ����������ˣ�������Ҫ�Ѷ�Ӧ��down����Ԫ����ΪNULL����ʾ�������������С���
	down[thno]=NULL;
	end=GetTickCount();

	if(i==BLOCK)
	{
		aaa=zmfile[thno].name;
		aaa=aaa+"���ļ�������ϣ�\n";
		AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
		aaa.ReleaseBuffer();
		CString temp;
		m_work.m_ListCtrl->SetItemText(filedono[thno],1,"|||||||||||||||||||||||||||||||||||||||||||||||||||");
		m_work.m_ListCtrl->SetItemText(filedono[thno],4,"�����");
		temp.Format("�ļ�������ϣ���ʱ  %d  ��\n",((end-now)/1000));
		temp=zmfile[thno].name+temp;
		AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)temp.GetBuffer(0),1);
		temp.ReleaseBuffer();
		for(j=0;j<BLOCK;j++)
		{
			CString bbb;
			bbb.Format("%s.down%d",zmfile[thno].name,j);
			//The DeleteFile function deletes an existing file. 
			//ɾ�������ļ���
			DeleteFile(bbb.GetBuffer(0));
			bbb.ReleaseBuffer();
		}

		//�Ҿ��ã��ɹ�����������֮���Ǹ�XX.down�ļ�Ҳ����ɾ���ˡ�
		temp.Format("%s.down",zmfile[thno].name);
		DeleteFile(temp);//added by yjk 
	}
	return 1;
}

//�����������ļ����̣߳������ǣ��û������˫����List�ؼ��еĵ�ǰitem������ֵ��
void CMainFrame::createthread(int threadno)
{
	DWORD dwthread;
	//����BLOCK���̣߳�ͬʱ����һ���ļ��Ĳ�ͬƬ�Ρ�
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

//���û������˫���ˡ��������ļ��б�List�ؼ���ʱ�򣬽���ӵ��ô˺�����ִ�������ļ��Ĳ�����
//����1��ֵΪ0��û�ã�����2�����û������˫����List�ؼ��еĵ�ǰ�����List�ؼ��е�����ֵ��
LRESULT CMainFrame::OnClient(WPARAM wParam,LPARAM lParam) 
{
	//�����ļ�
	CString str;
	int jj;//������¼������ͬʱ���ص��ļ����ĸ�����
	jj=0;

	//�����������ص��ļ��ĸ�����
	for(int i = 0; i <m_work.m_ListCtrl-> GetItemCount(); i++)
	{
		str =m_work.m_ListCtrl->GetItemText(i,4 );
		if(strcmp(str, "������") == 0)
		{
			jj++;
		}
	}

	//	if(jj>2)//Ҳ�ԣ�����3��ʱ��Ҳ�������2��������
	if(jj>=3)//����д���룬��������⡣
	{
		AfxMessageBox("���ͬʱֻ������3���ļ���");
		return 0;
	}

	//GetTickCount  The GetTickCount function retrieves the number of milliseconds that have elapsed since the system was started. It is limited to the resolution of the system timer. To obtain the system timer resolution, use the GetSystemTimeAdjustment function. 
	//��ȡ��ǰ��ʱ�䣬�Ժ��������
	now=GetTickCount();

	//�˱����������ǣ������û������˫����List�ؼ��еĵ�ǰ�������ֵ��
	int* dat;
	dat=(int *)lParam;
	//���ڣ�clno(CMainFrame��ĳ�Ա����)��ֵ���ǣ��û������˫����List�ؼ��еĵ�ǰ���
	//����ֵ�ˡ�
	clno=*dat;

	//down�����������洢�����ص��ļ�����Ϣ�õģ����ԣ����ĳ����Ԫ�ز�ΪNULL����˵������ļ�
	//�Ѿ���ʼ�����ˡ�
	if(down[clno]!=NULL)
	{
		AfxMessageBox("���ڱ����أ�");
		return 0;
	}

	CString aaa;//
	//zmfile[clno].name�д�������Ҫ�����ص��ļ����ļ�����
	aaa.Format("���ڳ�ʹ�� %s",zmfile[clno].name);
	aaa=aaa+" ��Ϣ������\n";
	//���ߴ�����ʹ�������������������Ϣ�������ﴰ�ڡ�������ǰ�ɴ�û�ù����������
	AfxGetMainWnd()->SendMessageToDescendants(WM_AGE1,(LPARAM)aaa.GetBuffer(0),1);
	aaa.ReleaseBuffer();

	//����List�ؼ��еĵ�clno���ļ�����Ϊ����һ����cdownload�ࡣ�����ǣ����������ļ��б�List�ؼ��е�ǰ�б����������
	down[clno]=new cdownload(clno);
	//��ʼ���أ�����ʹ����
	int type;

	//����cdownload::startask������Ŀ���ǣ�����һ�������������ڡ��ļ����ؽ��ȡ�List�ؼ���
	//��ʾ�ļ����صĽ��ȣ����ʣ�����ֽ�������Ϣ����������ʾ��Ϣ���ԣ������������ز����޹ء�
	type=down[clno]->startask(clno);

	if(type==2)
	{
		//�û�ѡ��������ش��ļ��ˡ�
		down[clno]=NULL;//added by yjk
		return 0;
	}

	if(type==1)
	{
		AfxMessageBox("�ļ��������꣡");
		down[clno]=NULL;//added by yjk
		return 0;
	}

	//�ļ�����С��0
	if(type==-1)
	{
		AfxMessageBox("���ļ�����Ϊ��򲻿ɶ���");
		return 0;
	}

	if(type==-2)
	{
		AfxMessageBox("���������ϣ�");
		return 0;
	}

	//����BLOCK���������ļ����̡߳��������ǣ��û������˫����List�ؼ��еĵ�ǰitem������ֵ��
	createthread(clno);
	return 1;
}

//
LRESULT CMainFrame::Onright(WPARAM wParam,LPARAM lParam) 
{
	//��ʼ����
	CString str;
	int jj;
	jj=0;
	for(int i = 0; i <m_work.m_ListCtrl-> GetItemCount(); i++){
		str =m_work.m_ListCtrl->GetItemText(i,4 );
		if(strcmp(str, "������") == 0){
			jj++;

		}
	}

	if(jj>2)
	{AfxMessageBox("���ͬʱֻ������3���ļ���");
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
	//ͣ����
	CString str;
	int jj;
	jj=0;
	for(int i = 0; i <m_work.m_ListCtrl-> GetItemCount(); i++){
		str =m_work.m_ListCtrl->GetItemText(i,4 );
		if(strcmp(str, "������") == 0){
			jj++;

		}
	}

	if(jj>2)
	{AfxMessageBox("���ͬʱֻ������3���ļ���");
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
