#if !defined(AFX_VITREECTRL_H__C18F39B0_2562_11D3_BAE5_00A0C9CC72C3__INCLUDED_)
#define AFX_VITREECTRL_H__C18F39B0_2562_11D3_BAE5_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VItreectrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VITreeCtrl window

class AFX_EXT_CLASS VITreeCtrl : public CTreeCtrl, public VIControl
{
// Construction
public:
	VITreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VITreeCtrl)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VITreeCtrl();

	virtual void SetTextColor(COLORREF clr);
	virtual void SetBackColor(COLORREF clr);
	
	HTREEITEM __fastcall DataFind(DWORD data, HTREEITEM startat=NULL,BOOL goBack=FALSE,HTREEITEM blocker=NULL,int maxDepth=-1);

	// Generated message map functions
protected:
	//{{AFX_MSG(VITreeCtrl)
	afx_msg BOOL OnCustomDraw( NMHDR * pNotifyStruct, LRESULT* result );
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VITREECTRL_H__C18F39B0_2562_11D3_BAE5_00A0C9CC72C3__INCLUDED_)
