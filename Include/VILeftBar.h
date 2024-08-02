#if !defined(AFX_VILEFTBAR_H__C2E329E5_58C3_11D2_A4DC_0040051BC7BF__INCLUDED_)
#define AFX_VILEFTBAR_H__C2E329E5_58C3_11D2_A4DC_0040051BC7BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VILeftBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VILeftBar window

class AFX_EXT_CLASS VILeftBar : public CWnd, public VIControl
{
// Construction
public:
	VILeftBar();
	

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VILeftBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VILeftBar();
	BOOL Create(LPCTSTR lpszWindowName, const RECT& rect, CWnd* pParentWnd, UINT nID);
	// Generated message map functions
protected:
	//{{AFX_MSG(VILeftBar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VILEFTBAR_H__C2E329E5_58C3_11D2_A4DC_0040051BC7BF__INCLUDED_)
