// IpBar1.cpp: implementation of the IpBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "client.h"
#include "IpBar1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void IpBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTest4Dlg)
DDX_Control(pDX, IDC_IPADDRESS1, m_ip);

	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(IpBar, CDialogBar)
	//{{AFX_MSG_MAP(IpBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
IpBar::IpBar()
{
//m_ip.SetWindowText("zm");
}

IpBar::~IpBar()
{

}
int IpBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;	
	GetClientRect(&rect);
	rect.left += 30;
	rect.top += 120;
	rect.right -= 30;
	rect.bottom -= 60;
	
	//m_ListCtrl = new COnlineList;
	if (!m_ip.Create(WS_CHILD | WS_VISIBLE | LVS_ICON|LVS_AUTOARRANGE,
		rect, this, IDC_IPADDRESS1))
	{
		TRACE0("Failed to create view for CMyBarLeft\n");
		return -1;
	}


	//m_ip.SetWindowText("zm");
	return 0;
}





void IpBar::OnSize(UINT nType, int cx, int cy) 
{
	//CDialogBar::OnSize(nType, cx, cy);
//	if(m_ListCtrl->m_hWnd)
//		m_ListCtrl->SetWindowPos(this,0,0,cx-15,cy-25,SWP_NOZORDER|SWP_NOMOVE);
	// TODO: Add your message handler code here
	
}