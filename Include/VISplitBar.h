#if !defined(AFX_VISPLITBAR_H__C2E329E8_58C3_11D2_A4DC_0040051BC7BF__INCLUDED_)
#define AFX_VISPLITBAR_H__C2E329E8_58C3_11D2_A4DC_0040051BC7BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VISplitBar.h : header file
//

typedef enum {
	VI_CTRL_SPLITBAR_LDOWN			= 0x00000001,
	VI_CTRL_SPLITBAR_MDOWN			= 0x00000002,
	VI_CTRL_SPLITBAR_RDOWN			= 0x00000004,
	VI_CTRL_SPLITBAR_DRAGGING			= 0x00000008,
}VI_CTRL_SPLITBAR_FLAGS;

#define VI_SPLIT_VERT			0x00000001
#define VI_SPLIT_HORZ			0x00000002
#define VI_SPLIT_SHADOW_DRAG	0x00000000
#define VI_SPLIT_FULL_DRAG	0x00000004
#define VI_SPLIT_STYLE2		0x00000008
	//style2	=>
	//first line		m_BorderColor	default color VICOLOR_65
	//middle line		m_EditColor		default color VICOLOR_152
	//last line			m_TextColor		default color VICOLOR_65
	//no style2 => use m_BackColor only


#define	VI_NM_BEGIN_DRAG_SPLITTER	0x00000001
#define	VI_NM_DRAG_SPLITTER		0x00000002
#define	VI_NM_END_DRAG_SPLITTER	0x00000003

/////////////////////////////////////////////////////////////////////////////
// VISplitBar window

class AFX_EXT_CLASS VISplitBar : public CWnd, public VIControl
{
// Construction
public:
	VISplitBar(DWORD style = (VI_SPLIT_VERT | VI_SPLIT_SHADOW_DRAG ));

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VISplitBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VISplitBar();
	BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );

	// Sets the Drag style fulldrag or shadow drag
	void SetDragStyle(int style);
	int GetDragStyle();

	// Sets / Gets the Split bar size
	int GetSize();
	void SetSize(int size);

	
	// Generated message map functions
protected:
	//{{AFX_MSG(VISplitBar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void StartDrag();
	void Drag(CPoint point);
	void EndDrag(CPoint point);

	DWORD m_Style;
	int m_Size;

	RECT m_DragRect;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISPLITBAR_H__C2E329E8_58C3_11D2_A4DC_0040051BC7BF__INCLUDED_)
