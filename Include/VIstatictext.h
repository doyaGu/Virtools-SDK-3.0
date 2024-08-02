#if !defined(AFX_VISTATICTEXT_H__C97F2520_A0C9_11D3_BA37_00105A669BB5__INCLUDED_)
#define AFX_VISTATICTEXT_H__C97F2520_A0C9_11D3_BA37_00105A669BB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIstatictext.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIStaticText window

class AFX_EXT_CLASS VIStaticText : public CStatic, public VIControl
{
// Construction
public:
	VIStaticText();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIStaticText)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIStaticText();

	// Generated message map functions
protected:
	//{{AFX_MSG(VIStaticText)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISTATICTEXT_H__C97F2520_A0C9_11D3_BA37_00105A669BB5__INCLUDED_)
