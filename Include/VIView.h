#if !defined(AFX_VIVIEW_H__C8C1AB01_99ED_11D2_A4DC_0040051BC7BF__INCLUDED_)
#define AFX_VIVIEW_H__C8C1AB01_99ED_11D2_A4DC_0040051BC7BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VIView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIView window

class VILeftBar;
class VIToolBar;

class AFX_EXT_CLASS VIView : public CWnd, public VIControl
{
// Construction
public:
	VIView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIView)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIView();

	void ShowLeftBar(BOOL show = TRUE);
	void ShowToolBar(BOOL show = TRUE);

	VILeftBar *GetLeftBar();
	VIToolBar *GetToolBar();
	
	CWnd *GetManagedWnd();
	void SetManagedWnd(CWnd *wnd);

	int GetLeftBarSize();
	int GetToolBarSize();

	void SetLeftBarSize(int sz);
	void SetToolBarSize(int sz);

	// Generated message map functions
protected:
	//{{AFX_MSG(VIView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	VILeftBar *m_LeftBar;
	VIToolBar *m_ToolBar;

	CWnd *m_ClientWnd;
	
	BOOL m_ToolBarOn;
	BOOL m_LeftBarOn;
	
	int m_ToolSize;
	int m_LeftSize;

	void UpdateWindows();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIVIEW_H__C8C1AB01_99ED_11D2_A4DC_0040051BC7BF__INCLUDED_)
