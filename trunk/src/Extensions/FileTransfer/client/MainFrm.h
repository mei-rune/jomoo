// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
//#include "Online1.h"
//*************************************************************
//���ߣ�����
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//��ҳ��http://h2osky.126.com
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
	CIPAddressCtrl m_ip1;//��������IP��ַ�õĿؼ����˿ؼ�������Ϊ���������Ӵ��ڡ�
	int end;

	//�á��������ļ��б�List�ؼ��е�ǰ�б������������Ϊ��������±ꡣ��ʵ��filedono��zmfile��down������������±�ֵ���Ƕ�Ӧ�ģ��ɻ��á�
	cdownload* down[10];//��Ȼ�ˣ���������Ӧ�ڡ��������ļ��б��еĿ����ص��ļ�����Ϊ����������Ƴ������ṩ10�������ص��ļ������ԣ��������Ĵ�С���趨Ϊ10��
	int now;//��ǰ��ʱ�䣬�Ժ���Ϊ��ʱ��λ��
	int clno;//�û������˫����List�ؼ��еĵ�ǰ�����List�ؼ��е�����ֵ��
	chatbar  m_wndSend;
	//	int threadno;
	//IpBar m_ipbar;
	COnLine  m_wndOnline;	//��Ӧ���Ǹ���ʾ���������Ͽ������ļ��б���List�ؼ���
	COnLine m_work;			//��Ӧ���Ǹ���ʾ���ļ����ؽ��ȡ���List�ؼ���

	//��һά��������10�������ļ����ڶ�ά����Ϊÿһ���ļ����Է�ΪBLOCK���߳�ͬʱ���أ����ԣ���Ӧ��ÿһ���̶߳���һ���¼����󣬾ʹ�����ڶ�ά�С�
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
