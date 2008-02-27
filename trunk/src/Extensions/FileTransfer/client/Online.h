// Online.h: interface for the COnline class.
//
//////////////////////////////////////////////////////////////////////
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#if !defined(AFX_ONLINE_H__09748AAC_0BF5_4491_BD73_D7A76109DCC6__INCLUDED_)
#define AFX_ONLINE_H__09748AAC_0BF5_4491_BD73_D7A76109DCC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "OnlineList.h"

//此类对应于“在线文件列表”和“文件下载进度”窗口。其中，都有一个List控件子窗口。
class COnLine : public CDialogBar
{
// Construction
public:
	
	COnlineList* m_ListCtrl;//List控件子窗口
	COnLine();   // standard constructor
	~COnLine();
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COnLine)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
//oid AddExStyle();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_ONLINE_H__09748AAC_0BF5_4491_BD73_D7A76109DCC6__INCLUDED_)
