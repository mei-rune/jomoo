#if !defined(AFX_MYCSOCKET_H__9C2B9157_1131_4A15_AF4A_FE486B6A670D__INCLUDED_)
#define AFX_MYCSOCKET_H__9C2B9157_1131_4A15_AF4A_FE486B6A670D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// mycsocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// mycsocket command target

class mycsocket : public CSocket
{
// Attributes
public:

// Operations
public:
	mycsocket();
	virtual ~mycsocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(mycsocket)
	//}}AFX_VIRTUAL
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	// Generated message map functions
	//{{AFX_MSG(mycsocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCSOCKET_H__9C2B9157_1131_4A15_AF4A_FE486B6A670D__INCLUDED_)
