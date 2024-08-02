#if !defined(AFX_HIGHLIGHTBITMAPBUTTON_H__2153160E_C504_11D2_8BB4_00A0C9CC72C3__INCLUDED_)
#define AFX_HIGHLIGHTBITMAPBUTTON_H__2153160E_C504_11D2_8BB4_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HighlightBitmapButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHighlightBitmapButton window

class CHighlightBitmapButton : public CBitmapButton
{
// Construction
public:
	CHighlightBitmapButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHighlightBitmapButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHighlightBitmapButton();
	void LoadBitmaps(LPCTSTR img1,LPCTSTR img2,LPCTSTR img3,LPCTSTR img4 = NULL, COLORREF bgColor = CLR_NONE);
	void LoadBitmaps(UINT img1,UINT img2,UINT img3,UINT img4 = 0, COLORREF bgColor = CLR_NONE);

	void SetCheck(BOOL check);
	BOOL GetCheck();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHighlightBitmapButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	BOOL m_bPushed;
	CImageList *m_pImageList;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIGHLIGHTBITMAPBUTTON_H__2153160E_C504_11D2_8BB4_00A0C9CC72C3__INCLUDED_)
