/*
 * Project:                Virtools Interface Plugin SDK
 * File:                   VEP_KeyboardShortcutManager.h
 * Author:                 Thomas Vissieres
 * Last check date:        11/19/2003 
 * optimized for Tab Size: 4	
 * Quick file summary:     Keyboard Shortcut Manager, to store & manage customizable keyboard shortcuts
 */





#pragma once

//#include <wtypes.h>
#include "VEP_DllEditorLibDefines.h"

class CUIKWinApp;
class EditKeyboardShortcutsDlg;

namespace VirtoolsExternalPlugin	//-----------------------------------------
{

class DLLEDITORLIB_CLASS_DECL KeyboardShortcutManager
{
//Types
public:

	enum CHECK_KEYBOARD_SHORTCUT{
		CHECK_NOTHING				= 0x00000000,
		CHECK_NAME					= 0x00000001,
		CHECK_KEY					= 0x00000002,
		CHECK_COMMANDID				= 0x00000004,
		CHECK_ALLOWED				= 0x00000008,
		CHECK_ALL					= 0x0000000f,
	};
	//test with globals KS and local KS of the same cat.
	//set conflict flags on ks that are in conflict
	//Return Value : 1 if ok, 0 if error
	enum CHECKKSRESULT{
		CHKS_OK						= 0x00000000	,
		CHKS_NAME_USED				= 0x00000001	,
		CHKS_KEY_USED				= 0x00000002	,
		CHKS_COMMANDID_USED			= 0x00000004	,
		CHKS_ERROR					= 0x00000008	,
		CHKS_CONFLICT_WITH_GLOBAL	= 0x00000010	,
		CHKS_NOTALLOWED				= 0x00000020	,
	};

	class KSKEY
	{
	public:
		enum {
				NONE		= 0x00000000,
				FIXED		= 0x00000001,
				EDITED		= 0x00000002,
				KS_CONTROL	= 0x00000004,
				KS_ALT		= 0x00000008,
				KS_SHIFT	= 0x00000010,
				KS_MODIFIER	= 0x0000001c,

		}KSTYPE;

		DWORD	key;
		DWORD	flags;
		KSKEY() : key(0),flags(0) {}
		KSKEY(DWORD k,DWORD f) : key(k),flags(f) {}

		friend int operator == (const KSKEY& k1, const KSKEY& k2)
		{
		  return (k1.key==k2.key && k1.flags==k2.flags);
		}
		friend int operator != (const KSKEY& k1, const KSKEY& k2)
		{
			return (k1.key!=k2.key || k1.flags!=k2.flags);
		}
	};
	class KSCategory;
	class KS : public KSKEY
	{
	public:
		XString			name;	//functionality name
		int				commandID;
		KSCategory*		category;
		XArray<KS*>		conflicts;
		XArray<DWORD>	conflictsReasons;

		KS() : commandID(0),category(NULL) {}
		const char*		GetName()
		{
			if (name.Length())
				return name.CStr();
			if (category && category->getksnamefunc)
				return category->getksnamefunc(commandID);
			return NULL;
		}
	};

	typedef XArray<KS*>	KSList;

	class KSCategory
	{
	public:
		enum {
				LOCAL		= 0x00000000,	//default. the window proc of owner should call the TestKS(int catindex,DWORD key) function in its pretranslateMsg to know if there is there is a shortcut called.
				GLOBAL		= 0x00000001,	//if global then callback even if owner has not the focus
				FIXED		= 0x00000002,	//if fixed, then keyboard shortcut cannot be modified by user
				ACTIVE		= 0x00000004,	//if not active then keyboard shortcuts will not be taken into account
				HIDDEN		= 0x00000008,	//hidden in edit keyboard shortcut dialog
		}KSCATTYPE;

		typedef const char*		(*KSGetNameFunc)(int commandID);
		typedef void			(*KSCallbackFunc)(int commandID);

		XString			name;	//category name (ie schematic, ...)
		KSList			list;
		void*			owner;
		DWORD			flags;
		HWND			hwnd;		//if global category, you should fill this member so that the keyboard shortcut is send to your window proc by the main window
		KSCallbackFunc	callback;		//the commandID can be send directly to custom user callback, so that you don't need to have an opened editor
		KSGetNameFunc	getksnamefunc;

		XArray<KSKEY>	allowedKeys;	//allowed keys for ks in this category
		XArray<KSKEY>	notAllowedKeys;	//not allowed keys for ks in this category
		XString			allowedDescriptions;	//put here a description of what is allowed and what is not (for a short description instead of a full list of what is allowed or not.

		KSCategory() : list(0),owner(NULL),flags(0),hwnd(NULL),callback(NULL),getksnamefunc(NULL) {}
		KSCategory(const char* n,void* o=NULL,DWORD f=FIXED,HWND h=NULL,KSCallbackFunc c=NULL,KSGetNameFunc gn=NULL) {name=n;owner=o;flags=f;hwnd=h;callback=c;getksnamefunc=gn;}
	};


public:
	KeyboardShortcutManager();
	~KeyboardShortcutManager();

	//Return Value : 1 if ok, 0 if error
	//owner recommended to be set
	int		RegisterCategory(	const char* catname,
										void* owner=NULL,
										DWORD flags=0, //KSCategory flags
										HWND hwnd=NULL,                             //usefull for GLOBAL flagged category only
										KSCategory::KSCallbackFunc callback=NULL,   //usefull for GLOBAL flagged category only
										KSCategory::KSGetNameFunc getnamefunc=NULL);//callback that returns a name for a commandID, should be used instead of setting a name for keyboard shortcuts directly

	int		GetCategoryIndex(const char* catname);
	int		GetCategoryIndex(void* owner);

	//get category
	KSCategory*	GetCategory(int catindex);

	int		ActivateCategory(int catindex,BOOL activate=TRUE);
	int		ActivateCategory(const char* catname,BOOL activate=TRUE);

	//Return Value : 1 if ok, 0 if error
	int		RegisterKS(const char* catname	,KS& ks,CHECK_KEYBOARD_SHORTCUT check=CHECK_ALL);
	int		RegisterKS(int catindex			,KS& ks,CHECK_KEYBOARD_SHORTCUT check=CHECK_ALL);

	//change registered KS name
	int		ChangeRegisteredKSName(const char* catname	,const char* oldKSName,const char* newKSName);
	int		ChangeRegisteredKSName(const char* catname	,int commandID,const char* newKSName);
	int		ChangeRegisteredKSName(int catindex			,const char* oldKSName,const char* newKSName);
	int		ChangeRegisteredKSName(int catindex			,int commandID,const char* newKSName);

	//add (not) allowed keys specification in category
	int		SetAllowedKey			(const char* catname	,KSKEY &key,BOOL add=TRUE);
	int		SetNotAllowedKey		(const char* catname	,KSKEY &key,BOOL add=TRUE);
	int		SetAllowedKeyDescription(const char* catname	,const char* desc);
	int		SetAllowedKey			(int catindex			,KSKEY &key,BOOL add=TRUE);
	int		SetNotAllowedKey		(int catindex			,KSKEY &key,BOOL add=TRUE);
	int		SetAllowedKeyDescription(int catindex			,const char* desc);

	//Return Value : 1 if ok, 0 if error
	int		UnregisterKS(const char* catname	,const char* ksname);
	int		UnregisterKS(const char* catname	,int commandID);
	int		UnregisterKS(int catindex			,const char* ksname);
	int		UnregisterKS(int catindex			,int commandID);

	//Return Value : 1 if ok, 0 if error
	int		UnregisterCategory(const char* catname);
	int		UnregisterCategory(int catindex);

	//return value : CHECKKSRESULT combination
	DWORD	CheckKSValidity(int catindex,KS* ks,CHECK_KEYBOARD_SHORTCUT check=CHECK_ALL);
	DWORD	CheckKSValidityInList(KS* ks,KSList& kslist,CHECK_KEYBOARD_SHORTCUT check=CHECK_ALL);

	//has to be called by PreTranslateMsg, on WM_KEYDOWN
	//Return Value : commandID
	int		TestKS(const char* catname	,DWORD key);
	int		TestKS(int catindex			,DWORD key);

//key names
	//Get keyboard shortcut name from ks*
	int		GetKSName(KS* ks,XString& ksname,BOOL clearstring=TRUE,BOOL addtabinstring=FALSE);

	//Get keyboard shortcut name key (such as Ctrl+Shift+F10) from name or command ID of KS
	int		GetKSName(const char* catname	,XString registeredName,XString& keyname,BOOL clearstring=TRUE,BOOL addtabinstring=FALSE);
	int		GetKSName(const char* catname	,int commandID,XString& keyname,BOOL clearstring=TRUE,BOOL addtabinstring=FALSE);
	int		GetKSName(int catindex			,XString registeredName,XString& keyname,BOOL clearstring=TRUE,BOOL addtabinstring=FALSE);
	int		GetKSName(int catindex			,int commandID,XString& keyname,BOOL clearstring=TRUE,BOOL addtabinstring=FALSE);

	
//-----------------------------------------------------------------------------
//private for Virtools internal use only

	//has to be called by MainAppWindow : PreTranslateMsg, on WM_KEYDOWN
	//Return Value : commandID
	int		TestGlobalKS(DWORD key);

	XHashTable<int,int> m_KeyData;

	//format:
	//1) category count
	//2) 	cat name
	//3)	cat ks count
	//4) 		ks name
	//5) 		ks key
	//6) 		ks flags
	int		Load(const char* dir,const char* fname=NULL);
	int		Save(const char* dir,const char* fname=NULL);
	
//table from virtual key code to key data--------------------------------------
//It is used once to have a map from Virtual Key->Key data for GetKeyNameText win32 func
//should be called by main Virtools Interface only
	void	LoadKeyData(const char* dir,const char* fname=NULL);
//do not use
	void	SaveKeyData(const char* dir,const char* fname=NULL);

protected:

	XArray<KSCategory*>			m_KSTable;

	XHashTable<int,void*>		m_CategoryOwnerMap;
	XHashTable<int,XString>		m_CategoryNameMap;

friend class CUIKWinApp;
friend class EditKeyboardShortcutsDlg;

private:
	void	RefreshCategoryIndexMaps();
};

}//namespace VirtoolsExternalPlugin
