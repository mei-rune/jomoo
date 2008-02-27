// downonline.cpp : implementation file
//
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#include "stdafx.h"
#include "client.h"
#include "downonline.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// downonline

downonline::downonline()
{
}

downonline::~downonline()
{
}


BEGIN_MESSAGE_MAP(downonline, CListCtrl)
	//{{AFX_MSG_MAP(downonline)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// downonline message handlers

int downonline::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

    //加载脸部图案

	//SetBkColor(RGB(0,128,128));

	return 0;
}

void downonline::AddItem(filesendinfo * seinfo)
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
aaa.Format("%d k",seinfo->length);
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
void downonline::AddItemtwo(char* name,int now,int type)
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

	SetItemText(lvi.iItem,0,name);
CString aaa;
while(now--)
aaa=aaa+'|';
SetItemText(lvi.iItem,1,aaa.GetBuffer(0));
switch(type)
{
case 0:
	aaa="新下载";
	break;
case 1:
	aaa="续下载";
	break;
case 2:
	aaa="已完成";
break;
}
SetItemText(lvi.iItem,2,aaa.GetBuffer(0));
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

void downonline::Remove(char *name)
{
	CString str;
	for(int i = 0; i < GetItemCount(); i++){
		str = GetItemText(i,0);
		if(strcmp(str, name) == 0){
			DeleteItem(i);
			break;
		}
	}
}


void downonline::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	CString str;
	int iSel = pNMListView->iItem;
	str.Format("the no is %d",iSel);

	//AfxMessageBox(str);
/*	if (iSel >= 0 ){
		str = GetItemText(iSel,0);
		CWnd* pParentWnd = GetParent();
		while (pParentWnd != NULL){ 
			if (pParentWnd->IsFrameWnd()){
				break;
			}
			pParentWnd = pParentWnd->GetParent();
		}
		if (pParentWnd != NULL)
	       pParentWnd->SendMessage(WM_CLOSE, 0, (LPARAM)&str);
	}
*///Sleep(300);

	::AfxGetMainWnd()->SendMessage(CLT_ONSETWO,0, (LPARAM)&iSel);
//::PostMessage(::AfxGetApp()->m_pMainWnd->m_hWnd,CLT_ONSE,(WPARAM)this,0);
	*pResult = 0;
}

void downonline::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void downonline::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
