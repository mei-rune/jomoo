// Online.h: interface for the COnline class.
//
//////////////////////////////////////////////////////////////////////
//*************************************************************
//���ߣ�����
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//��ҳ��http://h2osky.126.com
/********************************************************/
#if !defined(AFX_ONLINE_H__09748AAC_0BF5_4491_BD73_D7A76109DCC6__INCLUDED_)
#define AFX_ONLINE_H__09748AAC_0BF5_4491_BD73_D7A76109DCC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "OnlineList.h"

//�����Ӧ�ڡ������ļ��б��͡��ļ����ؽ��ȡ����ڡ����У�����һ��List�ؼ��Ӵ��ڡ�
class COnLine : public CDialogBar
{
// Construction
public:
	
	COnlineList* m_ListCtrl;//List�ؼ��Ӵ���
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
