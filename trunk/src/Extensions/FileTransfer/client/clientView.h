// clientView.h : interface of the CClientView class
//
/////////////////////////////////////////////////////////////////////////////
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#if !defined(AFX_CLIENT1VIEW_H__FD5BCE7E_8202_430D_BB49_CAB1CD2B5946__INCLUDED_)
#define AFX_CLIENT1VIEW_H__FD5BCE7E_8202_430D_BB49_CAB1CD2B5946__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "cdownload.h"
#include "mysocket.h"
#include "clientDoc.h"
class CClient1CntrItem;

class CClientView : public CRichEditView
{
protected: // create from serialization only
	CClientView();
	DECLARE_DYNCREATE(CClientView)
 
// Attributes
public:
	CHARFORMAT cfm;
void Message(LPCTSTR lpszMessage,COLORREF clr);
	CClientDoc* GetDocument();
	CString m_csIP;//IP地址
	cdownload* m_down[1];//只有一个元素，何必要定义成数组呢？
	mysocket* m_chatsocket;
	BOOL chattrue;//此变量的值为true的时候，表示：聊天socket还没有接好；这种设计方法是反着的。
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CClientView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnDestroy();
	afx_msg void OnConnect();
	afx_msg void OnSend();
	afx_msg LRESULT OnKSend(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT addmessage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in clientView.cpp
inline CClientDoc* CClientView::GetDocument()
   { return (CClientDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT1VIEW_H__FD5BCE7E_8202_430D_BB49_CAB1CD2B5946__INCLUDED_)
