// clientDoc.h : interface of the CClientDoc class
//
/////////////////////////////////////////////////////////////////////////////
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#if !defined(AFX_CLIENT1DOC_H__7670AF71_3030_4C95_BF86_747B879A7DB4__INCLUDED_)
#define AFX_CLIENT1DOC_H__7670AF71_3030_4C95_BF86_747B879A7DB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CClientDoc : public CRichEditDoc
{
protected: // create from serialization only
	CClientDoc();
	DECLARE_DYNCREATE(CClientDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
virtual BOOL SaveModified();
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CClientDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT1DOC_H__7670AF71_3030_4C95_BF86_747B879A7DB4__INCLUDED_)
