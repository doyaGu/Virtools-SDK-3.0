#if !defined(AFX_VILISTCTRL_H__B0137D80_2562_11D3_BAE5_00A0C9CC72C3__INCLUDED_)
#define AFX_VILISTCTRL_H__B0137D80_2562_11D3_BAE5_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIlistctrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIListCtrl window
typedef COLORREF (*NMListGetTextColorFunc)		(DWORD param);
typedef COLORREF (*NMListGetTextBackColorFunc)	(DWORD param);

class AFX_EXT_CLASS VIListCtrl : public CListCtrl, public VIControl
{
// Construction
public:
	VIListCtrl();

	virtual void SetTextColor(COLORREF clr);
	virtual void SetBackColor(COLORREF clr);
	virtual void SetSelectedTextColor(COLORREF clr);
	virtual void SetSelectedBackColor(COLORREF clr);
	
	CImageList * VICreateDragImage(int item);

	void SetColorCallbacks(NMListGetTextColorFunc getTextColorFunc,NMListGetTextBackColorFunc getTextBackColorFunc);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIListCtrl)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(VIListCtrl)
	afx_msg BOOL OnCustomDraw( NMHDR * pNotifyStruct, LRESULT* result );
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	NMListGetTextColorFunc		m_getTextColorFunc;
	NMListGetTextBackColorFunc	m_getTextBackColorFunc;

	COLORREF					m_selectedTextColor;
	COLORREF					m_selectedBackColor;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VILISTCTRL_H__B0137D80_2562_11D3_BAE5_00A0C9CC72C3__INCLUDED_)
