#if !defined(AFX_VICOMBOEX_H__90A3BEB7_24CE_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
#define AFX_VICOMBOEX_H__90A3BEB7_24CE_11D3_BAE2_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIcomboex.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIComboEx window

class AFX_EXT_CLASS VIComboEx : public CComboBoxEx, public VIControl
{
// Construction
public:
	VIComboEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIComboEx)
		afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);	
		afx_msg void OnPaint();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIComboEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(VIComboEx)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VICOMBOEX_H__90A3BEB7_24CE_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
