// Online.cpp: implementation of the COnline class.
//
//////////////////////////////////////////////////////////////////////
//*************************************************************
//���ߣ�����
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//��ҳ��http://h2osky.126.com
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
	//��ô��ڿͻ����Ĵ�С��
	GetClientRect(&rect);

	//���������8����λ�Ŀ��ࡣ
	rect.left += 8;
	//�ϱ�������15����λ�Ŀ��ࡣ
	rect.top += 15;
	//�ұ�������8����λ�Ŀ��ࡣ
	rect.right -= 8;
	//�ױ�������8����λ�Ŀ��ࡣ
	rect.bottom -= 8;
	
	m_ListCtrl = new COnlineList;
	//����һ��List�ؼ��Ӵ��ڡ�
	if (!m_ListCtrl->Create(WS_CHILD |WS_VISIBLE|LVS_REPORT,rect,this,IDC_LIST1))
	{
		TRACE0("Failed to create view for CMyBarLeft\n");
		return -1;
	}

	//���ڴ��౻����������ͬ�ĶԻ������е�List�ؼ��в�ͬ��columns�����ԣ�
	//��List�ؼ��в���columns�Ĵ��벻�ܷ������

	return 0;
}





void COnLine::OnSize(UINT nType, int cx, int cy) 
{
//	CDialogBar::OnSize(nType, cx, cy);

	//����������������ʲô�ã�
	//�𣺸����ҵĹ۲죬�ҷ���ִ��������Ĵ����List�ؼ���������λ�������½��ƶ��˼������ء�
	//���ǣ����Ҹı�������ֵ��û���κεı仯����ȥ����SWP_NOZORDER�󣬷�����۱��ˣ����ԣ�
	//�Ҷ϶����ĸ�����ֵ��û���õģ������õ���SWP_NOZORDER���Flag��
	//SWP_NOZORDER   Retains current ordering (ignores pWndInsertAfter).
	//A window can be moved to the top of the Z-order either by setting the pWndInsertAfter 
	//parameter to &wndTopMost and ensuring that the SWP_NOZORDER flag is not set or by 
	//setting a window's Z-order so that it is above any existing topmost windows. When a 
	//nontopmost window is made topmost, its owned windows are also made topmost. Its 
	//owners are not changed. 
	//������趨��SWP_NOZORDER��ǣ���ôList�ؼ��ڲ����Ӵ��ھͻ������Ͻ�ƫ�Ƽ������أ���֪��
	//Ϊʲô���������ǣ����List�ؼ��ڲ�����ʾ���������⣬�д���֤��
	//��һ���취�����о�һ��������⣬���ǽ���һ���Ի�����Ŀ��Ȼ���ڶԻ���ģ�������һ��
	//List�ؼ��������������ԣ��ﵽ����Ҫ����ۡ�Ȼ����Ϳ����ü��±�֮��������.rc�ļ���
	//�ҵ�List�ؼ��Ĳ��֣��о�һ�����Ĵ������Ե�Flags�Ϳ����ˡ������ͻᷢ��SWP_NOZORDER��
	//�÷��ˡ�
//	if(m_ListCtrl->m_hWnd)
//		m_ListCtrl->SetWindowPos(this,0,0,cx-15,cy-25,SWP_NOZORDER|SWP_NOMOVE);
//		m_ListCtrl->SetWindowPos(this,99,99,cx-10,cy-20,0);
}
