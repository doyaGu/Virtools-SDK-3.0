// class VIPopupMenu
// interface to manipulate easily popup menu

#pragma once
#include "XHashTable.h"

class AFX_EXT_CLASS VIPopupMenu
{
public:
	enum {	VPF_VALID							= 0x00000001,
			VPF_LAST_ADDED_ITEM_IS_SEPARATOR	= 0x00000002,

	}VIPOPUPMENUFLAG;

	VIPopupMenu(CWnd * parent);
	VIPopupMenu(CMenu * menu);
	VIPopupMenu();
	virtual ~VIPopupMenu();

	// Adds an item to the menu
	HRESULT AddItem(CString name,UINT commandID,BOOL subMenu=FALSE,BOOL checked=FALSE,BOOL grayed=FALSE,CMenu** createdmenu=NULL);
	HRESULT AddItemToSubMenu(UINT subMenucommandID,CString name,UINT commandID,BOOL subMenu=FALSE,BOOL checked=FALSE,BOOL grayed=FALSE,CMenu** createdmenu=NULL);

	// Adds a separator
	HRESULT AddSeparator();
	HRESULT AddSeparatorToSubMenu(UINT commandID);

	// Inserts an item to the menu
	HRESULT InsertItem(int pos,CString name,UINT commandID,BOOL subMenu=FALSE,BOOL checked=FALSE,BOOL grayed=FALSE,CMenu** createdmenu=NULL);
	HRESULT InsertItemToSubMenu(UINT subMenucommandID,int pos,CString name,UINT commandID,BOOL subMenu=FALSE,BOOL checked=FALSE,BOOL grayed=FALSE,CMenu** createdmenu=NULL);

	// Inserts a separator
	HRESULT InsertSeparator(int pos);
	HRESULT InsertSeparatorToSubMenu(int pos,UINT commandID);

	// Removes item at the specified position
	HRESULT RemoveItemAt(int pos);

	// Removes all item having the specified name from menu
	HRESULT RemoveItem(CString name);

	// Removes all item having the specified command ID from menu
	HRESULT RemoveItem(UINT commandID);

	// Removes all items
	HRESULT Empty();

	// Attach menu to a window or a menu resource
	HRESULT Attach(CWnd* wnd);
	HRESULT Attach(UINT resourceID);
	HRESULT Attach(CMenu* menu);
	HRESULT	Detach();

	//get main CMenu*
	CMenu*	GetCMenu();
	
	//get sub menu by command id
	CMenu*	GetSubMenu(int commandID);

	//show the menu at the current mouse position
	void	ShowAtMouse();

	//show the menu at the specified position
	//this func is virtual in order to be able to pause something, for instance pause CK engine in a derived class
	virtual	HRESULT Show(long x,long y);

	//get menu item count
	int GetMenuItemCount();

	//get sub menu item count. 
	int GetSubMenuItemCount(UINT subMenucommandID);

	//get menu string. Return value: char copied count,0 means not string / not found
	int GetMenuString(UINT position,CString &str,UINT flags=MF_BYPOSITION);

	//get sub menu string. Return value: char copied count,0 means not string / not found
	int GetSubMenuString(UINT subMenucommandID,UINT position,CString &str,UINT flags=MF_BYPOSITION);

	void DetachAndDeleteAllSubMenu();
	void DestroyAndDeleteAllSubMenu();

	BOOL IsLastItemAddedSeparator();

	//flags access
	DWORD GetFlags(){return m_CtrlFlags;}
	void SetFlags(DWORD f) {m_CtrlFlags=f;}
	void ModifyFlags(DWORD added=0,DWORD removed=0) {m_CtrlFlags&=~removed;m_CtrlFlags|=added;}

protected:

//DATAS
	// the menu
	// if it is to have icons, then must derive from CMenu
	// and must have an image list somewhere (best to have it in CMenu
	// derived class)
	// later
	//MAIN MENU
	CMenu		m_menu;
	CMenu*		m_pMenu;

	//SUB MENU LIST <key> is the commandID
	XHashTable<CMenu*,int> m_subMenuList;

	//the window to which menu is attached
	CWnd*		m_pWnd;

	//last item added was a separator ?
	BOOL		m_bLastAddedItemIsSeparator;

	//Flags
	DWORD		m_CtrlFlags;

//FUNCTIONS
	virtual void	Init();
	void			DestroySubMenuList();
	void			ForceInsertCMenuInMap(CMenu* menu);
};
