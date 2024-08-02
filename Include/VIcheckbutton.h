#if !defined(AFX_VICHECKBUTTON_H__A21500CC_24C4_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
#define AFX_VICHECKBUTTON_H__A21500CC_24C4_11D3_BAE2_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIcheckbutton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VICheckButton window

class AFX_EXT_CLASS VICheckButton : public CButton, public VIControl
{
// Construction
public:
	VICheckButton();
	void DrawItem(LPDRAWITEMSTRUCT dis);
	void SetBitmaps(CBitmap * normal=NULL,CBitmap * pushed=NULL,BOOL release=FALSE,int sizex=0,int sizey=0);

// Attributes
protected:
	CBitmap*	m_normalBitmap;
	CBitmap*	m_pushedBitmap;
	BOOL		m_bReleaseBitmaps;
	int			m_bitmapSizeX;
	int			m_bitmapSizeY;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VICheckButton)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VICheckButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(VICheckButton)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VICHECKBUTTON_H__A21500CC_24C4_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
