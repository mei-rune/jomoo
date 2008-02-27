// clientDoc.cpp : implementation of the CClientDoc class
//
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#include "stdafx.h"
#include "client.h"

#include "clientDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientDoc

IMPLEMENT_DYNCREATE(CClientDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CClientDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CClientDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDoc construction/destruction

CClientDoc::CClientDoc()
{
	// TODO: add one-time construction code here

}
BOOL CClientDoc::SaveModified() 
{
	// TODO: Add your specialized code here and/or call the base class
    return 1;//作者添加的这一句代码，这样，就不会在退出程序的时候，询问是否要存盘了。
//	return CRichEditDoc::SaveModified();
}
CClientDoc::~CClientDoc()
{
}

BOOL CClientDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CClientDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CClient1CntrItem(preo, (CClientDoc*) this);
}



/////////////////////////////////////////////////////////////////////////////
// CClientDoc serialization

void CClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CClientDoc diagnostics

#ifdef _DEBUG
void CClientDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CClientDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClientDoc commands
