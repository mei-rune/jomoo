
/*
Create Date:2002-2-13
Author:bailange
Email:bailange@cmmail.com

using it information:
please copy link.ico to res-tree,and import cursor resource.the name is IDC_CURSOR_LINK
*/
/////////////////////////////////  Includes  //////////////////////////////////

#include "stdafx.h"

#ifndef LINK_NOOLE
#define INITGUID
#endif
#include "resource.h"
#include "linkctrl.h"
#ifndef LINK_NOOLE
#include <initguid.h>
#endif
#include <winnetwk.h>
#include <winnls.h>
#include <shlobj.h>
#ifndef LINK_NOOLE
#include <intshcut.h>
#endif


/////////////////////////////////  Macros & Statics ///////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


///////////////////////////////// Implementation //////////////////////////////


BEGIN_MESSAGE_MAP(CLinkCtrl, CStatic)
	//{{AFX_MSG_MAP(CLinkCtrl)
  ON_WM_SETCURSOR()
  ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()


CLinkCtrl::CLinkCtrl()
{
	m_Color = RGB(0, 0, 255);
	m_VisitedColor = RGB(128, 0, 128);
	m_PointColor = RGB(255, 0, 0);
	m_State = SL_NOT_VISITED;
    m_OldState = SL_NOT_VISITED;
 	//Load up the cursors
    m_hLinkCursor = AfxGetApp()->LoadCursor(IDC_CURSOR2);
    m_hArrowCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
}


CLinkCtrl::~CLinkCtrl()
{
}


void CLinkCtrl::SetLinkString(const CString& sLinkString)
{
	m_sLinkString = sLinkString;
}


void CLinkCtrl::SetLinkStringDescription(const CString& sDescription)
{
    SetWindowText(sDescription);
}


CString CLinkCtrl::GetLinkStringDescription() const
{
  CString sDescription;
  GetWindowText(sDescription);
  return sDescription;
}



BOOL CLinkCtrl::OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/) 
{
   	::SetCursor(m_hLinkCursor);
	return TRUE;
}


void CLinkCtrl::OnLButtonDown(UINT /*nFlags*/, CPoint /*point*/) 
{
  	if (Open())
	  m_State = SL_VISITED;
}


void CLinkCtrl::SetLinkColor(const COLORREF& color) 
{ 
	m_Color = color; 
	UpdateWindow(); 
}


void CLinkCtrl::SetVisitedLinkColor(const COLORREF& color) 
{ 
	m_VisitedColor = color; 
	UpdateWindow(); 
}


void CLinkCtrl::SetPointLinkColor(const COLORREF& color) 
{ 
	m_PointColor = color; 
	UpdateWindow(); 
}


void CLinkCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect rc;
	GetClientRect(rc);
	if (rc.PtInRect(point))
	{
		if (m_State != SL_POINT)
		{
			SetCapture();
			HighLight(TRUE);
		} 
	}
	else
	{
		if (m_State == SL_POINT)
		{
			HighLight(FALSE);
			ReleaseCapture();
		}
	}	
	CStatic::OnMouseMove(nFlags, point);
}

void CLinkCtrl::HighLight(BOOL state)
{
	if (state)
	{
		if (m_State != SL_POINT)
		{
			m_OldState = m_State;
			m_State = SL_POINT;
			Invalidate();
		}
	}
	else
	{
		if (m_State == SL_POINT)
		{
			m_State = m_OldState;
			Invalidate();
		}
	}
}

BOOL CLinkCtrl::Open() const
{
	CWaitCursor cursor;
    HINSTANCE hRun = ShellExecute(GetParent()->GetSafeHwnd(), _T("open"), m_sLinkString, NULL, NULL, SW_SHOW);
    if ((int) hRun <= 32)
	{
       TRACE("Failed to invoke URL using ShellExecute\n");
       return FALSE;
	}
    return TRUE;
}

#ifdef _DEBUG
HBRUSH CLinkCtrl::CtlColor(CDC* pDC, UINT nCtlColor) 
#else
HBRUSH CLinkCtrl::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
#endif
{
	ASSERT(nCtlColor == CTLCOLOR_STATIC);
	DWORD dwStyle = GetStyle();
	if (!(dwStyle & SS_NOTIFY)) 
	{
		::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle | SS_NOTIFY);
	}
	HBRUSH hbr = NULL;
	if ((dwStyle & 0xFF) <= SS_RIGHT) 
	{
		// Modify the font to be underline
        if (!(HFONT)m_font)
		{
			LOGFONT lf;
		    GetFont()->GetObject(sizeof(lf), &lf);
			lf.lfUnderline = TRUE;
		    m_font.CreateFontIndirect(&lf);
		}
	    pDC->SelectObject(&m_font);
        //set the text colors
        switch (m_State)
		{
		case SL_NOT_VISITED:	pDC->SetTextColor(m_Color); break;
		case SL_VISITED:	  	pDC->SetTextColor(m_VisitedColor); break;
		case SL_POINT:      	pDC->SetTextColor(m_PointColor); break;
        default: ASSERT(FALSE);
		}
		pDC->SetBkMode(TRANSPARENT);
		// return hollow brush to preserve parent background color
		hbr = (HBRUSH)::GetStockObject(HOLLOW_BRUSH);
	}
	return hbr;
}

