// CntrItem.cpp : implementation of the CClient1CntrItem class
//
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
#include "stdafx.h"
#include "client.h"

#include "clientDoc.h"
#include "clientView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClient1CntrItem implementation

IMPLEMENT_SERIAL(CClient1CntrItem, CRichEditCntrItem, 0)

CClient1CntrItem::CClient1CntrItem(REOBJECT* preo, CClientDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CClient1CntrItem::~CClient1CntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CClient1CntrItem diagnostics

#ifdef _DEBUG
void CClient1CntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CClient1CntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
