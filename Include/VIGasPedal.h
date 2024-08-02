#if !defined(AFX_VIGASPEDAL_H__6CB3E4D0_27D6_11D3_BAE7_00A0C9CC72C3__INCLUDED_)
#define AFX_VIGASPEDAL_H__6CB3E4D0_27D6_11D3_BAE7_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIGasPedal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIGasPedal window

typedef enum {
	VI_CTRL_GASPEDAL_LDOWN			= 0x00000001,
	VI_CTRL_GASPEDAL_MDOWN			= 0x00000002,
	VI_CTRL_GASPEDAL_RDOWN			= 0x00000004,
	VI_CTRL_GASPEDAL_DRAGGING			= 0x00000008,
}VI_CTRL_GASPEDAL_FLAGS;

class AFX_EXT_CLASS VIGasPedal : public VIProgressBar
{
// Construction
public:
	VIGasPedal();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIGasPedal)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIGasPedal();

	// Generated message map functions
protected:
	//{{AFX_MSG(VIGasPedal)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIGASPEDAL_H__6CB3E4D0_27D6_11D3_BAE7_00A0C9CC72C3__INCLUDED_)
