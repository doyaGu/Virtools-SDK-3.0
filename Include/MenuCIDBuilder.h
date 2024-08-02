#pragma once

#ifdef CKCONTROLS_API
   #define CKCONTROLS_CLASS_DECL  __declspec(dllexport)
#else
   #define CKCONTROLS_CLASS_DECL  __declspec(dllimport)
#endif

namespace CKControl	//----------------------------------------
{

#define MENUENTRYSTATE_INVALID	-1
#define MENUENTRYSTATE_VALID	0
#define MENUENTRYSTATE_SEP		1

typedef BOOL (*MenuEntryValidateFunc) (XObjectPointerArray* oarray,UINT CommandID);
class CKVIPopupMenu;

class CKCONTROLS_CLASS_DECL MenuCIDBuilder;

typedef struct MenuEntry{
	XString m_Label;
	XBitArray m_Cids;
	UINT m_CommandID;
	UINT m_State;
	MenuCIDBuilder* m_SubMenu; 
	MenuEntryValidateFunc m_ValidateFunc;

	MenuEntry(){
		m_CommandID		= -1;
		m_State			= 0;
		m_ValidateFunc	= NULL;
		m_SubMenu		= NULL;
	}

	MenuEntry& operator = (const MenuEntry& e){
		m_Label			= e.m_Label;
		m_Cids			= e.m_Cids;		
		m_CommandID		= e.m_CommandID;
		m_State			= e.m_State;
		m_ValidateFunc	= e.m_ValidateFunc;		
		m_SubMenu		= e.m_SubMenu;
		return *this;
	}
} MenuEntry;


class MenuCIDBuilder{
public:
	MenuCIDBuilder();
	~MenuCIDBuilder();

	void BuildCIDs(XBitArray& cids,const XArray<CK_CLASSID>& validCID,BOOL derivedValid,const XArray<CK_CLASSID>& InvalidCID,BOOL derivedInvalid);

	void AddEntry(char *label,const XArray<CK_CLASSID>& validCID,BOOL derivedValid,const XArray<CK_CLASSID>& InvalidCID,BOOL derivedInvalid,UINT CommandID,MenuEntryValidateFunc func = NULL);	
	MenuCIDBuilder* AddSubMenu(char *label,const XArray<CK_CLASSID>& validCID,BOOL derivedValid,const XArray<CK_CLASSID>& InvalidCID,BOOL derivedInvalid,UINT CommandID,MenuEntryValidateFunc func = NULL);
	

	void AddSeparator();
	void PrepareMenu(XObjectPointerArray *oarray,CKVIPopupMenu *menu, int submenu = 0);
	
protected:	
	XClassArray<MenuEntry> m_MenuEntries;

};

}	//namespace CKControl