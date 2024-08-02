#if !defined(AFX_VISPINBUTTON_H__EB0DA3F0_27E9_11D3_BAE7_00A0C9CC72C3__INCLUDED_)
#define AFX_VISPINBUTTON_H__EB0DA3F0_27E9_11D3_BAE7_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIspinbutton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VISpinButton window

class AFX_EXT_CLASS VISpinButton : public VIProgressBar
{
// Construction
public:
	VISpinButton();
	BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );
	
	// Sets / Gets the max and min angle of the button
	void SetAngles(float min,float max);
	void GetAngles(float *min,float *max);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VISpinButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VISpinButton();
	
	void SetFont( CFont* pFont, BOOL bRedraw = TRUE);

	
	// Generated message map functions
protected:
	//{{AFX_MSG(VISpinButton)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void DrawButton(CDC *dc);
	BOOL m_bDragOn;

	float m_MaxAngle;
	float m_MinAngle;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISPINBUTTON_H__EB0DA3F0_27E9_11D3_BAE7_00A0C9CC72C3__INCLUDED_)
