// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
//#include "Online1.h"
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#if !defined(AFX_MAINFRM_H__6CBF07C4_FE86_40B8_8388_ABC560BDB613__INCLUDED_)
#define AFX_MAINFRM_H__6CBF07C4_FE86_40B8_8388_ABC560BDB613__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "Online1.h"
#include "Online.h"
#include "cdownload.h"
#include "chatbar.h"
//#include "ipbar1.h"
extern char name1[10][255];
extern DWORD WINAPI downthread(LPVOID lpparam);
extern DWORD WINAPI notify(LPVOID lpparam);
//class Online1;
//extern name1[10][255];
class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CIPAddressCtrl m_ip1;//用来输入IP地址用的控件，此控件被创建为工具条的子窗口。
	int end;

	//用“可下载文件列表”List控件中当前列表项的索引，做为此数组的下标。其实，filedono，zmfile，down这三个数组的下标值都是对应的，可互用。
	cdownload* down[10];//显然了，这个数组对应于“可下载文件列表”中的可下载的文件。因为服务器被设计成最多可提供10个可下载的文件，所以，这个数组的大小就设定为10。
	int now;//当前的时间，以毫秒为计时单位。
	int clno;//用户用鼠标双击的List控件中的当前项的在List控件中的索引值。
	chatbar  m_wndSend;
	//	int threadno;
	//IpBar m_ipbar;
	COnLine  m_wndOnline;	//对应于那个显示“服务器上可下载文件列表”的List控件。
	COnLine m_work;			//对应于那个显示“文件下载进度”的List控件。

	//第一维：可容纳10个下载文件；第二维：因为每一个文件可以分为BLOCK个线程同时下载，所以，对应于每一个线程都有一个事件对象，就存在这第二维中。
	HANDLE m_thread[10][BLOCK];

	CStatusBar  m_wndStatusBar;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void createthread(int threadno);
	DWORD finish();

	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members

	CToolBar    m_wndToolBar;

// Generated message map functions
protected:

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT on(WPARAM wParam,LPARAM lParam);
	afx_msg	LRESULT OnSetwo(WPARAM wParam,LPARAM lParam);
	//afx_msg	int OnClient(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnClient(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT Onright(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT Onclick(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__6CBF07C4_FE86_40B8_8388_ABC560BDB613__INCLUDED_)
