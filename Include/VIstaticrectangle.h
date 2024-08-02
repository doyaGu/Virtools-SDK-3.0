#if !defined(AFX_VISTATICRECTANGLE_H__C97F2521_A0C9_11D3_BA37_00105A669BB5__INCLUDED_)
#define AFX_VISTATICRECTANGLE_H__C97F2521_A0C9_11D3_BA37_00105A669BB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIstaticrectangle.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIStaticRectangle window

class AFX_EXT_CLASS VIStaticRectangle : public CStatic, public VIControl
{
// Construction
public:
	VIStaticRectangle();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIStaticRectangle)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIStaticRectangle();
	// Generated message map functions
protected:
	//{{AFX_MSG(VIStaticRectangle)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISTATICRECTANGLE_H__C97F2521_A0C9_11D3_BA37_00105A669BB5__INCLUDED_)
