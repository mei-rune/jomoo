// Online.cpp: implementation of the IpBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "client.h"
#include "IpBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IpBar::IpBar()
{
}

IpBar::~IpBar()
{
	delete m_ListCtrl;
}

BEGIN_MESSAGE_MAP(IpBar, CDialogBar)
	//{{AFX_MSG_MAP(IpBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IpBar message handlers
int IpBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(&rect);
	rect.left += 8;
	rect.top += 15;
	rect.right -= 8;
	rect.bottom -= 8;
	
	m_ListCtrl = new 	CIPAddressCtrl;
	if (!m_ListCtrl->Create(WS_CHILD |WS_VISIBLE|LVS_REPORT,
		rect, this, IDC_LIST1))
	{
		TRACE0("Failed to create view for CMyBarLeft\n");
		return -1;
	}
	m_ListCtrl->ModifyStyleEx(0, WS_EX_CLIENTEDGE);

//int i,j;

	
	return 0;
}





void IpBar::OnSize(UINT nType, int cx, int cy) 
{
	//CDialogBar::OnSize(nType, cx, cy);
	if(m_ListCtrl->m_hWnd)
		m_ListCtrl->SetWindowPos(this,0,0,cx-15,cy-25,SWP_NOZORDER|SWP_NOMOVE);
	// TODO: Add your message handler code here
	
}
