#if !defined(AFX_VITOOLBAR_H__C2E329E7_58C3_11D2_A4DC_0040051BC7BF__INCLUDED_)
#define AFX_VITOOLBAR_H__C2E329E7_58C3_11D2_A4DC_0040051BC7BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VIToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIToolBar window

class AFX_EXT_CLASS VIToolBar : public CWnd, public VIControl
{
// Construction
public:
 	VIToolBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
 	virtual ~VIToolBar();
 	BOOL Create(LPCTSTR lpszWindowName, const RECT& rect, CWnd* pParentWnd, UINT nID);
	// Generated message map functions
protected:
	//{{AFX_MSG(VIToolBar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VITOOLBAR_H__C2E329E7_58C3_11D2_A4DC_0040051BC7BF__INCLUDED_)
