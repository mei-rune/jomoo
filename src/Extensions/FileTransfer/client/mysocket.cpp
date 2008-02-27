// mysocket.cpp: implementation of the mysocket class.
//
//////////////////////////////////////////////////////////////////////
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#include "stdafx.h"
#include "client.h"
#include "mysocket.h"
#include "clientView.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 
mysocket::mysocket(CClientView* view2)
{
view=view2;
}

mysocket::~mysocket()
{

}
void mysocket::OnReceive(int nErrorCode) 
{
	
	this->Receive(&m_buf,255);

	CString aaa;
	aaa.Format("%s",m_buf);
//AfxMessageBox(aaa);
view->Message((LPCTSTR)aaa,RGB(255,0,0));
	//this->getpa

}
void mysocket::OnSend(int nErrorCode) 
{

}
