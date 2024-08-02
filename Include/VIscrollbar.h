#if !defined(AFX_VISCROLLBAR_H__BEDD2FF0_2970_11D3_BAF0_00105A669BB5__INCLUDED_)
#define AFX_VISCROLLBAR_H__BEDD2FF0_2970_11D3_BAF0_00105A669BB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIscrollbar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIScrollBar window

class AFX_EXT_CLASS VIScrollBar : public CScrollBar,public VIControl
{
// Construction
public:
	VIScrollBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIScrollBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIScrollBar();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(VIScrollBar)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	void  DrawSB(CDC *dc = NULL);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISCROLLBAR_H__BEDD2FF0_2970_11D3_BAF0_00105A669BB5__INCLUDED_)
