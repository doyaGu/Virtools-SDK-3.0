#if !defined(AFX_VICOMBOBOX_H__295405A6_24C4_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
#define AFX_VICOMBOBOX_H__295405A6_24C4_11D3_BAE2_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIcombobox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIComboBox window
typedef enum {
	VI_CTRL_COMBOBOX_NOREDRAW					=	0x00000001,
	VI_CTRL_COMBOBOX_NOLINE						=	0x00000002,
	VI_CTRL_COMBOBOX_UPBORDER					=	0x00000004,
	VI_CTRL_COMBOBOX_DOWNBORDER					=	0x00000008,
	VI_CTRL_COMBOBOX_LEFTBORDER					=	0x00000010,
	VI_CTRL_COMBOBOX_RIGHTBORDER				=	0x00000020,
	VI_CTRL_COMBOBOX_ALLBORDER					=	0x0000003c,
	VI_CTRL_COMBOBOX_EDITABLE					=	0x00000040,	//see CKObjectComboBox

//non user flags
	VI_CTRL_FOCUS						=	0x40000000,
	VI_CTRL_DRAWITEMDONE				=	0x80000000,
}VI_CTRL_COMBOBOX_FLAGS;


class AFX_EXT_CLASS VIComboBox : public CComboBox, public VIControl
{
// Construction
public:
	VIComboBox();

	VIEdit *	GetEditBox() {return &m_VIEdit;}
	CListBox *	GetListBox() {return (CListBox *) CWnd::FromHandle(m_ListBox);}
	//the height is set according to the font. Except when in owner draw mode, where u can set
	//the height manually, without taking the font's size into account
	void SetOwnerDrawHeight(int h);
	void SetListBoxWidth(int w);

	void AddStringAndData(char* String,DWORD AppData);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIComboBox)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIComboBox();
	virtual void SetControlFont(CFont *fnt);
	virtual void SetControlBrush(CBrush * br);
	void SetRedraw( BOOL bRedraw = TRUE );

	virtual int CompareItem( LPCOMPAREITEMSTRUCT lpCompareItemStruct );
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );

	// Generated message map functions
protected:
	//{{AFX_MSG(VIComboBox)
	//}}AFX_MSG
/*
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);	
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
*/
	virtual void DoOnPaint(CDC* pDC=NULL,BOOL forceDraw=FALSE);
	BOOL DoOnEraseBkgnd(CDC* pDC);

	VIEdit m_VIEdit;
	HWND m_Edit;
	HWND m_ListBox;
	HWND m_Static;

	int m_ownerDrawHeight;
	int	m_ListBoxWidth;
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VICOMBOBOX_H__295405A6_24C4_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
