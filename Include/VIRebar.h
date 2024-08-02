#if !defined(AFX_VIREBAR_H__3D0575C1_5E23_11D2_A4DC_0040051BC7BF__INCLUDED_)
#define AFX_VIREBAR_H__3D0575C1_5E23_11D2_A4DC_0040051BC7BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VIRebar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIRebar window

class AFX_EXT_CLASS VIRebar : public CWnd, public VIControl
{
// Construction
public:
	VIRebar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIRebar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIRebar();
	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL); 

	// Generated message map functions
protected:
	//{{AFX_MSG(VIRebar)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIREBAR_H__3D0575C1_5E23_11D2_A4DC_0040051BC7BF__INCLUDED_)
