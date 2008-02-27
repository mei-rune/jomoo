// Online.h: interface for the IpBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONLINE_H__09748AAC_0BF5_4491_BD73_D7A76109DCC6__INCLUDED_)
#define AFX_ONLINE_H__09748AAC_0BF5_4491_BD73_D7A76109DCC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "OnlineList.h"
class IpBar : public CDialogBar
{
// Construction
public:
	
	CIPAddressCtrl	* m_ListCtrl;
	IpBar();   // standard constructor
	~IpBar();
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(IpBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
//	void AddExStyle();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_ONLINE_H__09748AAC_0BF5_4491_BD73_D7A76109DCC6__INCLUDED_)
