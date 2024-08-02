#if !defined(AFX_VIHIGHLIGHTBUTTON_H__8128DB01_58BC_11D2_A4DC_0040051BC7BF__INCLUDED_)
#define AFX_VIHIGHLIGHTBUTTON_H__8128DB01_58BC_11D2_A4DC_0040051BC7BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VIHighlightButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIHighlightButton window

class AFX_EXT_CLASS VIHighlightButton : public CButton, public VIControl
{
// Construction
public:
	VIHighlightButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIHighlightButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIHighlightButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(VIHighlightButton)
		afx_msg UINT OnNcHitTest(CPoint point);
		afx_msg void OnDestroy();
		afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()


public:

	void SetPushed(BOOL pushed);
	BOOL GetPushed();
	
	BOOL GetHighlight();
	
private:

	UINT m_Timer;
	DWORD m_State;
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIHIGHLIGHTBUTTON_H__8128DB01_58BC_11D2_A4DC_0040051BC7BF__INCLUDED_)
