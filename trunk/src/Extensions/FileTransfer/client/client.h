// client.h : main header file for the CLIENT1 application
////*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#define SIZE 20 
#define BLOCK 4
#if !defined(AFX_CLIENT1_H__7451AFC0_CAF7_4AB3_810E_81CCDFE05A4D__INCLUDED_)
#define AFX_CLIENT1_H__7451AFC0_CAF7_4AB3_810E_81CCDFE05A4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h" 
     extern int filedono[10];

//extern char* chatmessage;
//extern	 afx_msg LRESULT onse(WPARAM wParam,LPARAM lParam);
//extern afx_msg LRESULT onsetwo(WPARAM wParam,LPARAM lParam);// main symbols
struct filesendinfo
{
	//文件信息
	char name[100];//100个字节
	int length;//4个字节
	int date;//4个字节
};//此结构的大小是108个字节

extern struct filesendinfo zmfile[10];
/////////////////////////////////////////////////////////////////////////////
// CClient1App:
// See client.cpp for the implementation of this class
//

class CClient1App : public CWinApp
{
public:
	CClient1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClient1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CClient1App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT1_H__7451AFC0_CAF7_4AB3_810E_81CCDFE05A4D__INCLUDED_)
