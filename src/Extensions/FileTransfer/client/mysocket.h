// mysocket.h: interface for the mysocket class.
//
//////////////////////////////////////////////////////////////////////
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#if !defined(AFX_MYSOCKET_H__81129324_3BCD_4730_9FAA_94BBCEADD030__INCLUDED_)
#define AFX_MYSOCKET_H__81129324_3BCD_4730_9FAA_94BBCEADD030__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CClientView;

class mysocket : public CAsyncSocket
{
public:
	CClientView* view;
	char m_buf[255];
	mysocket(CClientView* view2);
	virtual ~mysocket();
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};

#endif // !defined(AFX_MYSOCKET_H__81129324_3BCD_4730_9FAA_94BBCEADD030__INCLUDED_)
