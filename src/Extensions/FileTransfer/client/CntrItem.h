// CntrItem.h : interface of the CClient1CntrItem class
//
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#if !defined(AFX_CNTRITEM_H__6DE5A5D1_3A63_4E20_8465_CEA23FEAF85B__INCLUDED_)
#define AFX_CNTRITEM_H__6DE5A5D1_3A63_4E20_8465_CEA23FEAF85B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CClientDoc;
class CClientView;

class CClient1CntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CClient1CntrItem)

// Constructors
public:
	CClient1CntrItem(REOBJECT* preo = NULL, CClientDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CClientDoc* GetDocument()
		{ return (CClientDoc*)CRichEditCntrItem::GetDocument(); }
	CClientView* GetActiveView()
		{ return (CClientView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClient1CntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CClient1CntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__6DE5A5D1_3A63_4E20_8465_CEA23FEAF85B__INCLUDED_)
