// IpBar1.h: interface for the IpBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPBAR1_H__F895D1EF_44EE_435A_8F66_8DFA50F4BE7B__INCLUDED_)
#define AFX_IPBAR1_H__F895D1EF_44EE_435A_8F66_8DFA50F4BE7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IpBar : public CDialogBar
{
public:
	IpBar();
//	CIPAddressCtrl	* m_ListCtrl;

	virtual ~IpBar();


	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)

	enum { IDD = IDD_DIALOG2};
	CIPAddressCtrl m_ip;
	//}}AFX_DATA
	//}}AFX_VIRTUAL
	// Generated message map functions
	//{{AFX_MSG(IpBar)
	protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

#endif // !defined(AFX_IPBAR1_H__F895D1EF_44EE_435A_8F66_8DFA50F4BE7B__INCLUDED_)
