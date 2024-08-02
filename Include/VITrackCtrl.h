#if !defined(AFX_VITRACKCTRL_H__C49BB5B0_2ED1_11D3_BAF9_00105A669BB5__INCLUDED_)
#define AFX_VITRACKCTRL_H__C49BB5B0_2ED1_11D3_BAF9_00105A669BB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VITrackCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VITrackCtrl window
#include <XArray.h>

typedef enum {
	VI_CTRL_TRACK_LDOWN			= 0x00000001,
	VI_CTRL_TRACK_MDOWN			= 0x00000002,
	VI_CTRL_TRACK_RDOWN			= 0x00000004,
	VI_CTRL_TRACK_DRAGGING		= 0x00000008,
}VI_CTRL_TRACK_FLAGS;

#define NTHT_NOWHERE			0
#define NTHT_ITEMARROW			1
#define NTHT_ITEMLABEL			2
#define NTHT_ITEMSUBLABEL		3
#define NTHT_ITEMSUB			4

#define NTS_REDRAW				1
#define NTS_SELECT				2
#define NTS_UNSELECT			4
#define NTS_ADD					8

#define NT_EXPANDED		0x00000001
#define NT_SELECTED		0x00000002
#define NT_FOCUSED		0x00000004

#define NTE_EXPAND		0x00000001
#define NTE_COLLAPSE	0x00000002
#define NTE_TOGGLE		0x00000004
#define NTE_REDRAW		0x00000008


class VITrackCtrl;

typedef void (*VITRACKSUBITEMDRAWFN)(VITrackCtrl *Ctrl,int item,int sub,CDC *dc,RECT r,void *data);

typedef struct VITRACKNMHDR
{
	NMHDR hdr;
	int item;
	int subitem;
	POINT point;
	POINT subitempoint;
} VITRACKNMHDR;

typedef struct VITRACKSUBITEM
{
	char *name;
	void* data;
	DWORD flags;
	void *dfndata;

	VITRACKSUBITEMDRAWFN dfn;

	VITRACKSUBITEM()
	{
		name = NULL;
		data = NULL;
		flags = 0;
		dfn = NULL;
		dfndata = NULL;

	}

	~VITRACKSUBITEM()
	{
		if(name)
		{
			delete [] name;
			name = NULL;
		}
	}
}VITRACKSUBITEM;

typedef XArray<VITRACKSUBITEM*> VITRACKSUBITEMARRAY;


typedef struct VITRACKITEM
{
	char *name;
	VITRACKSUBITEMARRAY subs;
	void*  data;
	DWORD flags;
	VITRACKITEM()
	{
		name = NULL;
		data = NULL;
		flags = NT_EXPANDED;
	}

	~VITRACKITEM()
	{
		delete [] name;

		int i;
		for(i = 0; i < subs.Size();i++)
			delete subs[i];

	}

} VITRACKITEM;

typedef XArray<VITRACKITEM*> VITRACKITEMARRAY;

class AFX_EXT_CLASS VITrackCtrl : public CWnd, public VIControl
{
// Construction
public:
	VITrackCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VITrackCtrl)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VITrackCtrl();

	BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );

	int GetItemHeight();
	void SetItemHeight(int h);

	int GetSubItemHeight();
	void SetSubItemHeight(int h);

	int GetItemCount();

	void DeleteAllItem();

	int AddItem(char *item, void * data = NULL);
	void RemoveItem(int pos);	
	char *GetItemText(int pos);	
	void SetItemData(int pos,void * data);
	void * GetItemData(int pos);

	int GetSubItemCount(int Item);

	int AddSubItem(int item,char *sub,void *data = NULL);
	void RemoveSubItem(int item,int pos);
	char *GetSubItemText(int item,int pos);
	void SetSubItemData(int item,int pos,void * data);
	void * GetSubItemData(int item,int pos);

	int FindItem(char *name, void *data, int startat = 0);
	int FindSubItem(int item,char *name, void *data, int startat = 0);

	void SwapItems(int item1,int item2);
	void MoveItem(int oldpos,int newpos);

	void SwapSubItems(int item,int item1,int item2);
	void MoveSubItem(int item,int oldsubpos,int newsubpos);
	
	// Starts the item rename process
	void EditItemName(int item);
	
	// Starts the subitem rename process
	void EditSubItemName(int item,int sub);

	void SetSubItemHOffset(int offset);
	int GetSubItemHOffset();

	// Sets the Owner supplied function used to draw right part of subitems
	void SetSubItemDrawFunction(int item,int pos,VITRACKSUBITEMDRAWFN fn,void *data);
	void SetSubItemDefaultDrawFunction(VITRACKSUBITEMDRAWFN fn,void *data);

	// Performs a hit test, returns the index of the hitted item if any
	// Check the flags to knows what was hitten
	int HitTest(POINT point,UINT* flags,int* sub,RECT *itemrect);

	// Expands / Collapses / Toggles an Item 
	void Expand(int pos, UINT flags);

	// Selects / UnSelects an Item 
	void SelectItem(int pos, UINT flags);
	
	// Selects / UnSelects a subitem 
	void SelectSubItem(int pos, int sub, UINT flags);

	// Sets / Gets the control split bar position
	void SetSplitBarPosition(int pos);
	int GetSplitBarPosition();

	// Returns the control split bar
	VISplitBar *GetSplitBar();

	void SetFont( CFont* pFont, BOOL bRedraw = TRUE );

	// Generated message map functions
protected:
	//{{AFX_MSG(VITrackCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnTtnNeedText( UINT id, NMHDR * pNotifyStruct, LRESULT * result );


	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void DrawItem(CDC *dc,RECT lr,RECT rr,int i);
	void RecalcSB();

	void OnClick(UINT nFlags, CPoint point,int Button);
	void OnDblClick(UINT nFlags, CPoint point,int Button);

	void BeginDrag(UINT nFlags, CPoint point,int Button);
	void Drag(UINT nFlags, CPoint point,int Button);
	void EndDrag(UINT nFlags, CPoint point,int Button);

	void FillNotifyParentHeader(VITRACKNMHDR* hdr,int item,int sub,POINT point,RECT ir);

	virtual int OnToolHitTest( CPoint point, TOOLINFO* pTI );
	
	VISplitBar m_SplitBar;

	int m_CellSize;
	int m_SubCellSize;

	VITRACKITEMARRAY m_ItemArray;
	
	CScrollBar m_lvs;

	int m_sx;
	int m_sy;

	int m_Size;
	int m_vScroll;

	DWORD m_DragState;
	
	void *m_DefaultDfnData;

	int m_hOffset;

	VITRACKSUBITEMDRAWFN m_DefaultDfn;

	int m_FocusedItem;
	int m_FocusedSubItem;

	POINT m_lp;

	VIEdit m_Edit;

	int m_EditedItem;
	int m_EditedSubItem;	
};




/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VITRACKCTRL_H__C49BB5B0_2ED1_11D3_BAF9_00105A669BB5__INCLUDED_)
