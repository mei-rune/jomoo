#if !defined(AFX_CHATBAR_H__4A9C79AC_8148_412D_8890_05A0B705311C__INCLUDED_)
#define AFX_CHATBAR_H__4A9C79AC_8148_412D_8890_05A0B705311C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/// _MSC_VER > 1000
// chatbar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// chatbar window

class chatbar : public CDialogBar
{
// Construction
public:
	chatbar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(chatbar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~chatbar();

	// Generated message map functions
protected:
	//{{AFX_MSG(chatbar)
		// NOTE - the ClassWizard will add and remove member functions here.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATBAR_H__4A9C79AC_8148_412D_8890_05A0B705311C__INCLUDED_)
