#ifndef __LINKCTRL_H__
#define __LINKCTRL_H__
/////////////////////////// Classes /////////////////////////////////
//*************************************************************
//作者：赵明
//EMAIL:zmpapaya@hotmail.com;papaya_zm@sina.com
//主页：http://h2osky.126.com
/********************************************************/
class CLinkCtrl : public CStatic
{
public:
	//Constructors / Destructors
	CLinkCtrl();
	virtual ~CLinkCtrl();
	//Set or get the link string to use
	void SetLinkString(const CString& sLinkString);
	CString GetLinkString() const { return m_sLinkString; };
    //Set or get the link string description (really just the static's window text)
    void SetLinkStringDescription(const CString& sDescription);
    CString GetLinkStringDescription() const;
	//Set or get the hyperlink color 
	void SetLinkColor(const COLORREF& color);
	COLORREF GetLinkColor() { return m_Color; };
	//Set or get the hyperlink color for visited links
	void SetVisitedLinkColor(const COLORREF& color);
	COLORREF GetVisitedLinkColor() { return m_VisitedColor; };
	//Set or get the hyperlink color for highlighted links
	void SetPointLinkColor(const COLORREF& color);
	COLORREF GetPointLinkColor() { return m_PointColor; };
    //Connects to the URL
    BOOL Open() const;
protected:
  enum State
  {
    SL_NOT_VISITED,
    SL_VISITED,
    SL_POINT
  };
	//{{AFX_MSG(CLinkCtrl)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	void HighLight(BOOL state);
	CString  m_sLinkDescription;
	CString  m_sLinkString;
	HCURSOR  m_hLinkCursor;
    HCURSOR  m_hArrowCursor;
	COLORREF m_Color;
	COLORREF m_VisitedColor;
    COLORREF m_PointColor;
    State    m_State;
    State    m_OldState;
    CFont   m_font;
	DECLARE_MESSAGE_MAP()
};

#endif //__LINKCTRL_H__

