#if !defined(AFX_VILISTBOX_H__AE27A597_24BF_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
#define AFX_VILISTBOX_H__AE27A597_24BF_11D3_BAE2_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIlistbox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIListBox window

class AFX_EXT_CLASS VIListBox : public CListBox, public VIControl
{
// Construction
public:
	VIListBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIListBox)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(VIListBox)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VILISTBOX_H__AE27A597_24BF_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
