// OnlineList.cpp : implementation file
//
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#include "stdafx.h"
#include "client.h"
#include "OnlineList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COnlineList

COnlineList::COnlineList()
{
}

COnlineList::~COnlineList()
{
}


BEGIN_MESSAGE_MAP(COnlineList, CListCtrl)
	//{{AFX_MSG_MAP(COnlineList)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
//	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnlineList message handlers

int COnlineList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void COnlineList::AddItem(filesendinfo * seinfo)
{
	LVITEM			lvi;

	lvi.mask = LVIF_TEXT | LVIF_IMAGE;
	lvi.iItem = GetItemCount();
  //  lvi.iImage = i;
	lvi.iSubItem = 0;
//	lvi.s=0;
	lvi.pszText = "";
	lvi.cchTextMax = 64;
	InsertItem(&lvi);
	SetItemText(lvi.iItem,0,seinfo->name);
CString aaa;
aaa.Format("%d k",seinfo->length/1000);
SetItemText(lvi.iItem,1,aaa.GetBuffer(0));

//SetItemText(lvi.iItem,2,seinfo->date);
aaa.ReleaseBuffer();
//	SetItemText(lvi.iItem,2,name);
//	SetItemText(lvi.iItem,3,(char *)m_csPath);
//	SetItemText(lvi.iItem,4,(char *)m_csAttrib);
SetHotItem(lvi.iItem);			//标注当前项目
	EnsureVisible(lvi.iItem,true);	//滚动影响的卷轴
	Update(lvi.iItem);
//strcpy(name1[lvi.iItem],name2);
//strcpy(name1[lvi.iItem+1],"none");
//strcpy(nameph[lvi.iItem],namepath);
//AfxMessageBox(name1[lvi.iItem]);
}

//
void COnlineList::AddItemtwo(int fileno,int now,int byes,int type,int speed,int threadno)
{
LVITEM			lvi;

	lvi.mask = LVIF_TEXT ;
	lvi.iItem = GetItemCount();
	itemtoitem[lvi.iItem]=threadno;
	filedono[fileno]=lvi.iItem;
  // lvi.iImage = threadno;
	lvi.iSubItem = 0;
//	lvi.s=0;
	lvi.pszText = "";
	lvi.cchTextMax = 64;
	InsertItem(&lvi);
	SetItemText(lvi.iItem,0,zmfile[fileno].name);
CString aaa;
while(now>0)
{
aaa=aaa+'|';
now-=2;
}

SetItemText(lvi.iItem,1,aaa.GetBuffer(0));
aaa.Format("%d k",byes/1000);
SetItemText(lvi.iItem,3,aaa.GetBuffer(0));
aaa.Format("%d k/s",speed);
SetItemText(lvi.iItem,2,aaa.GetBuffer(0));
switch(type)
{
case 0:
	aaa="下载中";
	break;
case 1:
	aaa="下载中";
	break;
case 2:
	aaa="已完成";
break;
}
SetItemText(lvi.iItem,4,aaa.GetBuffer(0));
//SetItemText(lvi.iItem,2,seinfo->date);
aaa.ReleaseBuffer();
//	SetItemText(lvi.iItem,2,name);
//	SetItemText(lvi.iItem,3,(char *)m_csPath);
//	SetItemText(lvi.iItem,4,(char *)m_csAttrib);
SetHotItem(lvi.iItem);			//标注当前项目
	EnsureVisible(lvi.iItem,true);	//滚动影响的卷轴
	Update(lvi.iItem);
//strcpy(name1[lvi.iItem],name2);
//strcpy(name1[lvi.iItem+1],"none");
//strcpy(nameph[lvi.iItem],namepath);
//AfxMessageBox(name1[lvi.iItem]);
}

void COnlineList::Remove(char *name)
{
	CString str;
	for(int i = 0; i < GetItemCount(); i++)
	{
		str = GetItemText(i,0);
		if(strcmp(str, name) == 0)
		{
			DeleteItem(i);
			break;
		}
	}
}

//双击List控件中的某一项，就可以导致“下载文件”的代码被执行。
void COnlineList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//NMLISTVIEW  Contains information about a list-view notification message. This structure is the same as the NM_LISTVIEW structure but has been renamed to fit standard naming conventions. 
	//NMHDR  Contains information about a notification message. 
	//NMLISTVIEW结构的第一个数据成员是NMHDR   hdr;所以，下面的这个强制数据类型转换还是有
	//一点点的道理的。不过，只能访问NMHDR部分，才算是安全的！但是，作者的用法超出了安全的
	//范围，而是访问了iItem成员。看来，pNMHDR指针原来就应该是指向NMLISTVIEW类型的变量的！！！
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//List控件的父窗口就是“在线文件列表”对话框窗口。
	CWnd* pParentWnd = GetParent();

	//此变量用来保存获得的对话框窗口的ID。
	int aa;

	if(pParentWnd != NULL)
	{ 
		//CWnd::GetDlgCtrlID  Returns the window or control ID value for any child window, not only that of a control in a dialog box.
		//获得对话框窗口的ID
		aa=pParentWnd->GetDlgCtrlID();
	}

	//之所以要加上这个判断条件，是因为COnlineList不仅仅用于“在线文件列表”对话框窗口，还用于
	//“文件下载进度”对话框窗口。很显然了，作者的设计是：希望下面的代码只在对“在线文件列表”
	//对话框窗口进行操作的时候被执行，所以，就有了下面的这一句判断代码。

	//如果对话框窗口的ID是IDD_DIALOG1，则
	if(aa==IDD_DIALOG1)
	{
		CString str;
		//获得List控件的当前被选中的项。
		int iSel = pNMListView->iItem;
		//如果List控件的当前被选中的项，是有效的，则
		if(iSel>=0)
		{
			//The SendMessage function sends the specified message to a window or windows. 
			//It calls the window procedure for the specified window and does not return 
			//until the window procedure has processed the message. 
			//这里用的是SendMessage，所以，消息发出之后不会立即返回，而是非得要等消息
			//被处理完了才能返回。
			//向主框架窗口发送CLT_ONSE消息，按照MFC的消息传递机制，首先处理此消息的窗口应该
			//是主框架中的当前活动的视。不过，在视类中并没有添加处理此消息的代码，所以，
			//实际上是CMainFrame::OnClient函数处理了此消息。
			::AfxGetMainWnd()->SendMessage(CLT_ONSE,0, (LPARAM)&iSel);
		}
	}
	*pResult = 0;
}

void COnlineList::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	::MessageBox(NULL,"COnlineList::OnRclick的代码被暂时注释掉了，等以后再补上。","",0);
/*	//不知为什么，这里的代码一执行就出错，只好先注释掉了。

	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CWnd* pParentWnd = GetParent();
	int aa;
	if	(pParentWnd != NULL)
	{ 
		aa	=pParentWnd->GetDlgCtrlID();
	}
	int iSel = pNMListView->iItem;
	if(iSel>=0)
	{
		::AfxGetMainWnd()->SendMessage(AA,0, (LPARAM)&itemtoitem[iSel]);
	}
	*pResult = 0;
*/
}

void COnlineList::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CWnd* pParentWnd = GetParent();
int aa;
if	(pParentWnd != NULL){ 
			
	aa	=pParentWnd->GetDlgCtrlID();
		}

//CString aaa;
//aaa.Format("%d",aa);
//AfxMessageBox(aaa);
if(aa==IDD_DIALOG3){
//	CString str;

	int iSel = pNMListView->iItem;
//	str.Format("the no is %d",iSel);

//	AfxMessageBox(str);
	if(iSel>=0){
 
	::AfxGetMainWnd()->SendMessage(BB,0, (LPARAM)&itemtoitem[iSel]);
	}
}
	*pResult = 0;
}
