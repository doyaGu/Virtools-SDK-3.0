#if !defined(AFX_VIRADIOBUTTON_H__91B26F16_24C4_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
#define AFX_VIRADIOBUTTON_H__91B26F16_24C4_11D3_BAE2_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIradiobutton.h : header file
//

#define VI_RADIOBUTTON_CHECKBOX	0x00000001

#define VI_RADIOBUTTON_FLAGS		0x00000001

/////////////////////////////////////////////////////////////////////////////
// VIRadioButton window

class AFX_EXT_CLASS VIRadioButton : public CButton, public VIControl
{
// Construction
public:
	VIRadioButton();
	//void DrawItem(LPDRAWITEMSTRUCT);

	void SetRadioStyle(int style);
	int GetRadioStyle();

// Attributes
public:

	DWORD m_old_wParam;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIRadioButton)
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIRadioButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(VIRadioButton)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);	
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIRADIOBUTTON_H__91B26F16_24C4_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
