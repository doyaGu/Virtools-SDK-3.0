#pragma once

#define MAX_SPLITBAR_COUNT	1000
/////////////////////////////////////////////////////////////////////////////
// VISplitBar window
//takes care to call DestroyWindow on child, but do not deleted them, it is at user charge
class VISplitBar;

class AFX_EXT_CLASS VISplitterWnd : public CWnd, public VIControl
{
//-----------------------------------------------------------------------------
//TOOL Class
public:
	struct VIPane
	{
		enum {
			FIXED_SIZE	= 0x00000001,		//fixed size => auto scrollbar to manage child wnd
			MIN_SIZE	= 0x00000002,		//min size member to take into account
			MAX_SIZE	= 0x00000004,		//max size member to take into account
		}VIPANE_FLAGS;
		
		CWnd*	m_Wnd;
		DWORD	m_Flags;
		CSize	m_MinSize;
		CSize	m_MaxSize;

		VIPane() {memset(this,0,sizeof(VIPane));}
	};
	
//-----------------------------------------------------------------------------
//enums
	enum {
		DRAW_BORDER					= 0x00000001,	//draw border with VIControl::border color if set
		ERASE_BKGND					= 0x00000002,	//erase background if set with VIControl::background color (and border if border is set)
		SPLITBAR_CONSTRAINT			= 0x00000004,	//if set, then splitbar cannot be dropped further than its neighbors
		SPLITBAR_STATE_INITIALIZED	= 0x00000008,	//SplitBar positions have been set & initialized
	}VISplitBar_FLAGS;
	
//-----------------------------------------------------------------------------
//construction
	VISplitterWnd(int columnCount=2,int rowCount=1);
	virtual ~VISplitterWnd();
	//usefull styles
	//WS_VISIBLE | WS_CHILD | WS_TABSTOP and maybe WS_CLIPSIBLINGS (avoid this one for shadow splitbar to be visible) | WS_CLIPCHILDREN
	//if dwStyle==-1 => usefull styles are put into dwStyle
	//please call LoadState before calling create if you need to restore SplitBar positions.
	BOOL	Create(DWORD dwStyle,const RECT& rect,CWnd* pParentWnd,UINT nID);
	
//-----------------------------------------------------------------------------
//using
	BOOL	SetColumnCount(int columnCount);
	BOOL	SetRowCount(int rowCount);
	BOOL	RemoveColumns(int startingIndex,int count=1);
	BOOL	RemoveRows(int startingIndex,int count=1);
	BOOL	InsertColumns(int insertAt=-1,int count=1);			//insertAt==-1 => append
	BOOL	InsertRows(int insertAt=-1,int count=1);			//insertAt==-1 => append

	int		GetRowCount() const;
	int		GetColumnCount() const;

	VIPane*	SetWindowToPane(int x,int y,CWnd* wnd,DWORD* flags=NULL,CSize* minSize=NULL,CSize* maxSize=NULL,BOOL redraw=FALSE);
	void	SetPane(int x,int y,VIPane &pane,BOOL redraw=FALSE);
	void	SwitchPanes(int x1,int y1,int x2,int y2,BOOL redraw=TRUE);
	VIPane*	GetPane(int x,int y);

	//refresh selected pane window RECT. if index==-1 or <0, all panes are refreshed,
	//+show child window if they are not yet visible
	//return value : TRUE if successfull
	BOOL	RefreshPane(int index=-1,BOOL redraw=TRUE);

	//refresh selected SplitBars, all if index ==-1 or <0 
	//return value : TRUE if successfull
	BOOL	RefreshSplitBar(int index=-1,BOOL redraw=TRUE);
	
	//if x==y==-1, size of pane array is returned
	int		GetArrayIndex(int x=-1,int y=-1);

	void	SetSplitBarSize(int size,BOOL redraw=FALSE);
	int		GetSplitBarSize();

	/*buffer format
		int								: column count
		int								: row count
		int								: width of window RECT at saving time
		int								: height of window RECT at saving time
		array of int (column count-1)	: SplitBars X positions (in pixel or percentage if percent==TRUE)
		array of int (row count-1)		: SplitBars Y positions (in pixel or percentage if percent==TRUE)
	*/
	BOOL	SaveState(XArray<int> &buffer);
	BOOL	LoadState(XArray<int> &buffer);
	
	BOOL	SetHorizontalSplitbarPosition(int index,int ypos);
	int		GetHorizontalSplitbarPosition(int index);
	BOOL	SetVerticalSplitbarPosition(int index,int xpos);
	int		GetVerticalSplitbarPosition(int index);
	
	BOOL	GetPaneRect(int x,int y,RECT* rect);
	BOOL	GetPaneRect(int index,RECT* rect);
	BOOL	GetSplitBarRect(int index,RECT* rect);

	void	SetMinSplitBarSeparation(int dist);
	int		GetMinSplitBarSeparation();

	void	SetDefaultSplitBarStyle				(DWORD style);
	void	SetDefaultSplitBarBackground		(COLORREF color);
	void	SetDefaultSplitBarStyle2FirstBorder	(COLORREF color);
	void	SetDefaultSplitBarStyle2Background	(COLORREF color);
	void	SetDefaultSplitBarStyle2LastBorder	(COLORREF color);

//-----------------------------------------------------------------------------
//protected funcs
protected:
	void	ResizeSplitBarsArray(int oldSplitBarCount);
	void	CreateSplitBars();
	void	DestroySplitBars();
	void	BuildSplitBarPositions(const RECT &r);	//fill m_ColumnXPos & m_RowYPos with average positions according to rect
	void	BuildSplitBarPositionsWithPercentage(const RECT &r);	//fill m_ColumnXPos & m_RowYPos with average positions according to rect
	void	SaveWindowSize(const RECT &r);	//save width & height in m_percentModeSavedSize
	void	OnSplitBarDragEnd(int index);
	void	CheckSplitBarPositions();	//check all, for instance after min distance has been change / pane min size / max size changed

	void	CheckVerticalSplitBarPosition(int index);
	void	CheckVerticalBarBoundaries(int &xpos);
	void	CheckVerticalBarConstraint(int index,int &xpos);
	void	CheckVerticalBarNoConstraint(int index,int &xpos);

	void	CheckHorizontalSplitBarPosition(int index);				//need index valid in splitbar array, not row index
	void	CheckHorizontalBarBoundaries(int &ypos);
	void	CheckHorizontalBarConstraint(int index,int &ypos);		//need index valid in splitbar array, not row index
	void	CheckHorizontalBarNoConstraint(int index,int &ypos);	//need index valid in splitbar array, not row index

	void	CheckAllHorizontalSplitbarPositions();
	void	CheckAllVerticalSplitbarPositions();
//-----------------------------------------------------------------------------
//datas
protected:
	XArray<VIPane>				m_Panes;
	XArray<VISplitBar*>			m_SplitBars;

	XArray<int>					m_ColumnXPos;
	XArray<int>					m_RowYPos;

	int							m_RowCount;
	int							m_ColumnCount;

	int							m_SplitBarSize;

	int							m_MinSplitBarSeparation;

	//default style for splitbars:
	//VI_SPLIT_STYLE2 (which is
		//first line	(m_DefaultSplitBarStyle2FirstBorder,	default VICOLOR_65)
		//middle lines	(m_DefaultSplitBarStyle2Background,		default VICOLOR_152)
		//last line		(m_DefaultSplitBarStyle2LastBorder,		default VICOLOR_65)
	//if m_DefaultSplitBarStyle has not VI_SPLIT_STYLE2 then
	//only backgnd color(m_DefaultSplitBarBackground,			default VICOLOR_200

	DWORD						m_DefaultSplitBarStyle;
	COLORREF					m_DefaultSplitBarBackground;
	COLORREF					m_DefaultSplitBarStyle2FirstBorder;
	COLORREF					m_DefaultSplitBarStyle2Background;
	COLORREF					m_DefaultSplitBarStyle2LastBorder;

	//we need to store 
	//int							; width of window RECT at saving time
	//int							; height of window RECT at saving time
	//in this var to update SplitBar position on size
	DWORD						m_percentModeSavedSize;

//-----------------------------------------------------------------------------
//WINDOWS
public:
	virtual LRESULT	WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	afx_msg void	OnPaint();
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	afx_msg void	OnDestroy();
	
	DECLARE_MESSAGE_MAP()
};
