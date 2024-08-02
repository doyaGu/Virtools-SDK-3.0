#if !defined(AFX_VIPAGER_H__F4AA9C65_5A49_11D2_A4DC_0040051BC7BF__INCLUDED_)
#define AFX_VIPAGER_H__F4AA9C65_5A49_11D2_A4DC_0040051BC7BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VIPager.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIPager window

class AFX_EXT_CLASS VIPager : public CWnd, public VIControl
{
// Construction
public:
	VIPager(); 
	
// Attributes
public:

// Operations
public:

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL); 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIPager)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIPager();

	// Generated message map functions
protected:
	//{{AFX_MSG(VIPager)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIPAGER_H__F4AA9C65_5A49_11D2_A4DC_0040051BC7BF__INCLUDED_)
