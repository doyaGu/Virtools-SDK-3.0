#if !defined(AFX_VIPROGRESSBAR_H__6060F590_259F_11D3_BAE5_00A0C9CC72C3__INCLUDED_)
#define AFX_VIPROGRESSBAR_H__6060F590_259F_11D3_BAE5_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIprogressbar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIProgressBar window


#define NPBS_HORIZONTAL	0x00000000
#define NPBS_SMOOTH		0x00000001
#define NPBS_BORDER		0x00000002
#define NPBS_VERTICAL	0x00000004
#define NPBS_BITMAP		0x00000008

class AFX_EXT_CLASS VIProgressBar : public CWnd, public VIControl
{
// Construction
public:
	VIProgressBar();
	BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );
	void SetImageList(VIImageList *il);

	
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIProgressBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIProgressBar();

	// sets / gets the range of the progress bar
	virtual void GetRange(int& imin, int& imax);
	virtual void SetRange(int imin, int imax);

	// sets / gets the curent value displayes by the progress bar
	virtual void SetPos(int pos);
	virtual int GetPos();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(VIProgressBar)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	void DrawProgress(CDC *cdc);

	int m_Min;
	int m_Max;
	int m_Pos;

	DWORD m_Style;

	VIImageList *m_IL;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIPROGRESSBAR_H__6060F590_259F_11D3_BAE5_00A0C9CC72C3__INCLUDED_)
