#pragma once

#include "XClassArray.h"
// Creation :
//-----------
// 1) create an instance of VITabCtrl 
// 2) call Create() method
// 3) add tabs with one of the InsertTab() methods
// 4) set the flags according to the style you want (up, down, fixed width ..), using SetFlags() or ModifyFlags() methods from VIControl.h
// 5) Activate the tab you want , default activated is 0, with SetActiveTabIndex() method
//
// Functioning :
//--------------
// when the user click on a tab,
// parent windows receives a WM_COMMAND message,
// with in wParam : LOWORD = id of VITabCtrl control in wParam, HIWORD = (activated tab index & 0x0ff) + (old activated index & 0x0ff <<8)
// when the user right click on a tab
// parent windows recieves a WM_NOTIFY message,
// with in wParam : id 
// in lParam : a NMTABACTIVATE*  with code = NM_RCLICK
//
// when a tab switch is done, the control sends a notifcation with a NMTABSWITCH* in lParam
//
// Important note : 255 max tabs allowed, no more, since in activate tab WM_COMMAND, we have just a short to put old and new activated tab index
//

/////////////////////////////////////////////////////////////////////////////
// VITabCtrl window

class AFX_EXT_CLASS VITabCtrl : public CWnd, public VIControl
{
public:

struct NMTABACTIVATE
{
	NMHDR	hdr;
	int		activatedTab;
};

struct NMTABSWITCH
{
	NMHDR	hdr;
	int		index1;
	int		index2;
};

struct VITab
{
	XString		m_Name;
	CWnd*		m_Wnd;
	int			m_Width;
	DWORD		m_Flags;
	DWORD		m_Data;

	enum VITAB_FLAGS
	{
	};

	VITab() {memset(this,0,sizeof(VITab));}
};

enum VITABCTRL_NOTIFICATION{
	VITAB_NM_BEGIN_DRAG			= 0x00001000,
	VITAB_NM_DRAG				= 0x00001001,
	VITAB_NM_END_DRAG			= 0x00001002,
	VITAB_NM_SWITCH				= 0x00001003,
};
	//Flags
enum VITABCTRL_FLAGS{
	VITAB_UP						= 0x00000001,	//tabs are rounded upside
	VITAB_DOWN						= 0x00000002,	//tabs are rounded downside
	VITAB_FIXEDWIDTH				= 0x00000004,	//tabs have a fixed width
	VITAB_BORDER					= 0x00000008,	//tabs have a border on the opposite side of the rounded rect
	VITAB_NEEDARROWBUTTONS			= 0x00000010,	//Used Internally.too much tabs for wnd width=>, so need arrow buttons to scroll
	VITAB_LEFTBUTTON_ROLLOVER		= 0x00000020,	//Used Internally.	rollover on left arrow button info for redraw
	VITAB_RIGHTBUTTON_ROLLOVER		= 0x00000040,	//Used Internally.	rollover on right arrow button info for redraw
	VITAB_LEFTBUTTON_DOWN			= 0x00000080,	//Used Internally.	left arrow button is pushed info for redraw
	VITAB_RIGHTBUTTON_DOWN			= 0x00000100,	//Used Internally.	right arrow button is pushed info for redraw
	VITAB_LEFTBUTTON_AVAILABLE		= 0x00000200,	//Used Internally.	left button is available for clicking
	VITAB_RIGHTBUTTON_AVAILABLE		= 0x00000400,	//Used Internally.	right button is available for clicking
	VITAB_MANAGEWNDS				= 0x00000800,	//if m_Wnd members of VITAb structs exists, then these windows are shown/hidden when tabs are activated/deactivated
	VITAB_MANAGEDRAGNDROPINTERNAL	= 0x00001000,	//tabs can be dragged & dropped to switch their position
	VITAB_MANAGEDRAGNDROPEXTERNAL	= 0x00002000,	//tabs can be dragged & dropped and notify any wnd about current state of drag & drop
	VITAB_MANAGEDRAGNDROP			= 0x00003000,	//global drag & drop management
	VITAB_AUTORESIZETOMINWIDTH		= 0x00004000,	//Not effective yet. according to added / removed tab, the tab control autoresizes to min width maximized by parent client rect width
};

public:
// Construction
	VITabCtrl();
	~VITabCtrl();

	HRESULT		Create(const char* name,DWORD style,RECT &r,CWnd* parent,int id);

	//return value : index or -1 if failed
	int			InsertTab(int index,VITab* tab,BOOL redraw=FALSE);					//-1 => append
	int			InsertTab(int index,const char* name,CWnd* wnd=NULL,BOOL redraw=FALSE);	//-1 => append

// Get index of tab under mouse, -1 if any
	int			GetTabUnderMouse();

// Get index of tab under given client coordinaates
	int			GetTabAt(POINT &clientP);

	//get tab struct ptr, to change on the fly
	int			GetTabCount() const;
	VITab*		GetTab(int index);

	//update tab after having modified a VITab struct
	int			UpdateTab(int index,BOOL recomputeWidth=TRUE);
	
	//remove a tab
	int			RemoveTab(int index,BOOL redraw=TRUE);

	//remove all tabs
	int			RemoveAllTabs(BOOL redraw=TRUE);

	//set active tab. -1 means no activate tab
	int			SetActiveTab(int index=-1,BOOL redraw=TRUE,BOOL sendMessageToParent=FALSE);
	
	//switch tabs
	int			SwitchTabs(int index1,int index2);


// Data access
	int			GetTabMargin()		{return m_TabMargin;}
	int			SetTabMargin(int m);	//free space around text in tabs

	int			GetTabSeparationSpace()	{return m_TabSeparationSpace;}
	int			SetTabSeparationSpace(int s);	//space in pixel between end of textof 1st tab and drawing of next tab

	int			GetActiveTabIndex()	{return m_ActiveTabIndex;}

	int			GetTabFixedWidth()	{return m_TabFixedWidth;}
	int			SetTabFixedWidth(int width);

	COLORREF	GetActiveTabColor()	{return m_ActiveTabColor;}
	int			SetActiveTabColor(COLORREF c);

	CImageList*	CreateDragImage(int index);

	//compute total max width
	int			ComputeTotalTabWidth();

	//get maximum width (to use width flag VITAB_AUTORESIZETOMINWIDTH)
	int			GetMaximumWidth();

	//set maximum width (to use width flag VITAB_AUTORESIZETOMINWIDTH)
	void		SetMaximumWidth(int newmaxwidth);

protected:
//DATAS
	//array of string / tabs
	XClassArray<VITab>	m_Tabs;

	//free space around text in tabs (so x2, margin added to text width left and right)
	int						m_TabMargin;

	//separation between two tabs, after the end of text of the 1st tab
	int						m_TabSeparationSpace;

	//fixed width
	int						m_TabFixedWidth;

	//active tab backcolor
	COLORREF				m_ActiveTabColor;

	//index of first visible tab
	int						m_FirstVisibleTab;

	//image list for internal drag & drop
	CImageList*				m_DragNDropImageList;

	//drag & drop hot spot
	POINT					m_DragNDropHotspot;

	//maximum width, to use with flag VITAB_AUTORESIZETOMINWIDTH.
	int						m_MaximumWidth;

//FUNCS
	//callbacks
	int			DoOnPaint();
	int			DoOnLButtonDown(int x,int y,int dblclk=0);
	int			DoOnLButtonUp(int x,int y);
	int			DoOnRButtonUp(int x,int y);
	int			DoOnMouseMove(int x,int y);
	int			DoOnSize(int width,int height);
	int			OnClickLeftArrowButton();
	int			OnClickRightArrowButton();
	int			OnClickOnTab(int index);

	//draw a tab button
	int			DrawTab(VITab* tab,CDC* dc,int xoffset=-1,int active = 0);

	//draw arrow buttons. Return Value : new available width left. If rollover==1 draws only left button filled, if ==2, draws only right button filled, ==3, left is down, ==4 right is down
	int			DrawArrowButtons(CDC* dc,int rollover=0);

	//test available arrow buttons. Modify m_CtrlFlags in consequence
	int			TestAvailableArrowButtons();
	
	//add/remove VITAB_NEEDARROWBUTTONS flag according to total tab width (ComputeTotalTabWidth()) and client rect .Returns total width
	int			CheckForArrowButtons();

	//get arrow buttons rect.Return Value : new available width left
	int			GetArrowButtonsRect(RECT* oR1=NULL,RECT* oR2=NULL);

	//compute tab width (after insertion, or if need update)
	int			ComputeTabWidth(VITab* tab);

	//return 1 if is 1st visible tab and tabindex!=0, otherwise 0
	int			IsFirstVisibleTab(int tabIndex);

	//return 1 if is last visible tab, otherwise 0
	int			IsLastVisibleTab(int tabIndex);

	//Manage wnds
	int			ActivatedTabChange(int oldActivatedIndex,int newActivatedIndex);

	//return x position of tab, fill oRect
	int			GetTabRect(int index,RECT* oRect=NULL);

	//drag & drop
	int			BeginDrag(POINT &hotspot);
	int			DragStop();
	int			DragCont();
	int			IsDragActive();
	int			DragMove();
	int			EndDrag();
	
private:
	//active tab. Must be set only via SetActiveTab func
	int						m_ActiveTabIndex;

//---------------------------------------------------------------------------
//----------WINDOWS----------------------------------------------------------
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VITabCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(VITabCtrl)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//----------WINDOWS----------------------------------------------------------
//---------------------------------------------------------------------------
};
