#if !defined(AFX_VICHECKLISTBOX_H__8373EBB0_24C0_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
#define AFX_VICHECKLISTBOX_H__8373EBB0_24C0_11D3_BAE2_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VICheckListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VICheckListBox window

class AFX_EXT_CLASS VICheckListBox : public CCheckListBox, public VIControl
{
// Construction
public:
	VICheckListBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VICheckListBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpdis);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VICheckListBox();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(VICheckListBox)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);	
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VICHECKLISTBOX_H__8373EBB0_24C0_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
