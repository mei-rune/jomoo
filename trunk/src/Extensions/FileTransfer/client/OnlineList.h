#if !defined(AFX_ONLINELIST_H__1565D1D2_7C79_490C_BDCE_BAC50504BEDA__INCLUDED_)
#define AFX_ONLINELIST_H__1565D1D2_7C79_490C_BDCE_BAC50504BEDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OnlineList.h : header file
//
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#define WM_DBCLICKITEM WM_USER+1
/////////////////////////////////////////////////////////////////////////////
// COnlineList window
extern char name1[10][255];
//extern char nameph[10][255];

//自定义的List控件类的派生类。
class COnlineList : public CListCtrl
{
// Construction
public:
	int itemtoitem[10];
	COnlineList();
	CImageList m_imgList;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnlineList)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Remove(char* name);
	void AddItem(filesendinfo * seinfo);
void AddItemtwo(int fileno,int now,int byes,int type,int speed,int threadno);
	virtual ~COnlineList();

	// Generated message map functions
protected:
	//{{AFX_MSG(COnlineList)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
//afx_msg void OnRblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONLINELIST_H__1565D1D2_7C79_490C_BDCE_BAC50504BEDA__INCLUDED_)
