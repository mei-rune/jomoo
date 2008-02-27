// OnlineList.cpp : implementation file
//
//*************************************************************
//���ߣ�����
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//��ҳ��http://h2osky.126.com
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
SetHotItem(lvi.iItem);			//��ע��ǰ��Ŀ
	EnsureVisible(lvi.iItem,true);	//����Ӱ��ľ���
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
	aaa="������";
	break;
case 1:
	aaa="������";
	break;
case 2:
	aaa="�����";
break;
}
SetItemText(lvi.iItem,4,aaa.GetBuffer(0));
//SetItemText(lvi.iItem,2,seinfo->date);
aaa.ReleaseBuffer();
//	SetItemText(lvi.iItem,2,name);
//	SetItemText(lvi.iItem,3,(char *)m_csPath);
//	SetItemText(lvi.iItem,4,(char *)m_csAttrib);
SetHotItem(lvi.iItem);			//��ע��ǰ��Ŀ
	EnsureVisible(lvi.iItem,true);	//����Ӱ��ľ���
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

//˫��List�ؼ��е�ĳһ��Ϳ��Ե��¡������ļ����Ĵ��뱻ִ�С�
void COnlineList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//NMLISTVIEW  Contains information about a list-view notification message. This structure is the same as the NM_LISTVIEW structure but has been renamed to fit standard naming conventions. 
	//NMHDR  Contains information about a notification message. 
	//NMLISTVIEW�ṹ�ĵ�һ�����ݳ�Ա��NMHDR   hdr;���ԣ���������ǿ����������ת��������
	//һ���ĵ���ġ�������ֻ�ܷ���NMHDR���֣������ǰ�ȫ�ģ����ǣ����ߵ��÷������˰�ȫ��
	//��Χ�����Ƿ�����iItem��Ա��������pNMHDRָ��ԭ����Ӧ����ָ��NMLISTVIEW���͵ı����ģ�����
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//List�ؼ��ĸ����ھ��ǡ������ļ��б��Ի��򴰿ڡ�
	CWnd* pParentWnd = GetParent();

	//�˱������������õĶԻ��򴰿ڵ�ID��
	int aa;

	if(pParentWnd != NULL)
	{ 
		//CWnd::GetDlgCtrlID  Returns the window or control ID value for any child window, not only that of a control in a dialog box.
		//��öԻ��򴰿ڵ�ID
		aa=pParentWnd->GetDlgCtrlID();
	}

	//֮����Ҫ��������ж�����������ΪCOnlineList���������ڡ������ļ��б��Ի��򴰿ڣ�������
	//���ļ����ؽ��ȡ��Ի��򴰿ڡ�����Ȼ�ˣ����ߵ�����ǣ�ϣ������Ĵ���ֻ�ڶԡ������ļ��б�
	//�Ի��򴰿ڽ��в�����ʱ��ִ�У����ԣ��������������һ���жϴ��롣

	//����Ի��򴰿ڵ�ID��IDD_DIALOG1����
	if(aa==IDD_DIALOG1)
	{
		CString str;
		//���List�ؼ��ĵ�ǰ��ѡ�е��
		int iSel = pNMListView->iItem;
		//���List�ؼ��ĵ�ǰ��ѡ�е������Ч�ģ���
		if(iSel>=0)
		{
			//The SendMessage function sends the specified message to a window or windows. 
			//It calls the window procedure for the specified window and does not return 
			//until the window procedure has processed the message. 
			//�����õ���SendMessage�����ԣ���Ϣ����֮�󲻻��������أ����Ƿǵ�Ҫ����Ϣ
			//���������˲��ܷ��ء�
			//������ܴ��ڷ���CLT_ONSE��Ϣ������MFC����Ϣ���ݻ��ƣ����ȴ������Ϣ�Ĵ���Ӧ��
			//��������еĵ�ǰ����ӡ��������������в�û����Ӵ������Ϣ�Ĵ��룬���ԣ�
			//ʵ������CMainFrame::OnClient���������˴���Ϣ��
			::AfxGetMainWnd()->SendMessage(CLT_ONSE,0, (LPARAM)&iSel);
		}
	}
	*pResult = 0;
}

void COnlineList::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	::MessageBox(NULL,"COnlineList::OnRclick�Ĵ��뱻��ʱע�͵��ˣ����Ժ��ٲ��ϡ�","",0);
/*	//��֪Ϊʲô������Ĵ���һִ�оͳ���ֻ����ע�͵��ˡ�

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
