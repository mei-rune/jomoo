// Online.cpp: implementation of the COnline class.
//
//////////////////////////////////////////////////////////////////////
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#include "stdafx.h"
#include "client.h"
#include "Online.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COnLine::COnLine()
{
}

COnLine::~COnLine()
{
	delete m_ListCtrl;
}

BEGIN_MESSAGE_MAP(COnLine, CDialogBar)
	//{{AFX_MSG_MAP(COnLine)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnLine message handlers
int COnLine::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	//获得窗口客户区的大小。
	GetClientRect(&rect);

	//左边留出了8个单位的空余。
	rect.left += 8;
	//上边留出了15个单位的空余。
	rect.top += 15;
	//右边留出了8个单位的空余。
	rect.right -= 8;
	//底边留出了8个单位的空余。
	rect.bottom -= 8;
	
	m_ListCtrl = new COnlineList;
	//创建一个List控件子窗口。
	if (!m_ListCtrl->Create(WS_CHILD |WS_VISIBLE|LVS_REPORT,rect,this,IDC_LIST1))
	{
		TRACE0("Failed to create view for CMyBarLeft\n");
		return -1;
	}

	//由于此类被用于两个不同的对话框，其中的List控件有不同的columns，所以，
	//向List控件中插入columns的代码不能放在这里。

	return 0;
}





void COnLine::OnSize(UINT nType, int cx, int cy) 
{
//	CDialogBar::OnSize(nType, cx, cy);

	//下面的这两句代码有什么用？
	//答：根据我的观察，我发现执行了下面的代码后，List控件发生了移位，向右下角移动了几个像素。
	//可是，当我改变了坐标值后，没有任何的变化。我去掉了SWP_NOZORDER后，发现外观变了，所以，
	//我断定，四个坐标值是没有用的，其作用的是SWP_NOZORDER这个Flag。
	//SWP_NOZORDER   Retains current ordering (ignores pWndInsertAfter).
	//A window can be moved to the top of the Z-order either by setting the pWndInsertAfter 
	//parameter to &wndTopMost and ensuring that the SWP_NOZORDER flag is not set or by 
	//setting a window's Z-order so that it is above any existing topmost windows. When a 
	//nontopmost window is made topmost, its owned windows are also made topmost. Its 
	//owners are not changed. 
	//如果不设定上SWP_NOZORDER标记，那么List控件内部的子窗口就会向左上角偏移几个像素，不知是
	//为什么。这个问题牵扯到List控件内部的显示、布局问题，有待考证。
	//有一个办法可以研究一下这个问题，就是建立一个对话框项目，然后在对话框模板上添加一个
	//List控件，调整它的属性，达到你想要的外观。然后，你就可以用记事本之类的软件打开.rc文件，
	//找到List控件的部分，研究一下它的窗口属性的Flags就可以了。这样就会发现SWP_NOZORDER的
	//用法了。
//	if(m_ListCtrl->m_hWnd)
//		m_ListCtrl->SetWindowPos(this,0,0,cx-15,cy-25,SWP_NOZORDER|SWP_NOMOVE);
//		m_ListCtrl->SetWindowPos(this,99,99,cx-10,cy-20,0);
}
