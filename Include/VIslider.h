#if !defined(AFX_VISLIDER_H__17A5DC46_24C4_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
#define AFX_VISLIDER_H__17A5DC46_24C4_11D3_BAE2_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIslider.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VISlider window


class AFX_EXT_CLASS VISlider : public CSliderCtrl, public VIControl
{
// Construction
public:
	VISlider();
	void ShowRange(BOOL s);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VISlider)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VISlider();
	// Generated message map functions
protected:
	//{{AFX_MSG(VISlider)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	void DrawSlider(BOOL enabled);
	void DrawHorzSlider(BOOL enabled);
	void DrawVertSlider(BOOL enabled);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISLIDER_H__17A5DC46_24C4_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
