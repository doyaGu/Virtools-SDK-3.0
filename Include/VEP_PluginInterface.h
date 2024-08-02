/*
 * Project:                Virtools Interface Plugin SDK
 * File:                   VEP_PluginInterface.h
 * Author:                 Thomas Vissieres
 * Last check date:        11/19/2003 
 * optimized for Tab Size: 4	
 * Quick file summary:     class used for communication between Virtools Interface Plugins, and Virtools Dev
 */





#pragma once

#include "VEP_DllEditorLibDefines.h"





namespace VirtoolsExternalPlugin	//-----------------------------------------
{

class KeyboardShortcutManager;


	
/*
 *	PluginInterface
 *  this structure is send to Virtools External Plugin with
 *  PluginInfo::m_PluginCallback callback
 *  and can be accessed from DllEditorDlg and DllToolbarDlg (see VEP_DllEditorDlg.h)
 *  It can be used to interact with Virtools Interface. You have acces to :
 *
 *  -rendering functions
 *  -manipulation of selection in 3DEditor
 *  -launch object setups / know if an object is edited
 *  -Status Bar tools functions
 *  -CK centralized functions for copy and deletion (you should use them instead of using directly CK
 *   in order to Virtools Interface being aware of your action
 *  -an interface parameter pool: for better memory management, and instead of creating your own CKParameters,
 *   just ask for a parameter and free it when you want, or even forget about it, it will be deleted when you 
 *   leave Virtools
 *  -Virtools Directories
 *  -Project Modified Flags Access
 *  -Drag and Drop
 *  -user menu added to Virtools main menu with user menu callback
 *  -Virtools Load and save functionalities
 *  -Exiting function
 *  -last notification send by Virtools Interface
 *  -a CKContext for CK access (see CK SDK)
 *  -a VersionControlInfo structure if a version control plugin is loaded and available.
 *   Thus you can use some Version Control in your plugin too
 *
 */
class DLLEDITORLIB_CLASS_DECL PluginInterface
{
public:

	enum DELETION_MODE {
		DELETECKOBJECT_ASK		= 1,
		DELETECKOBJECT_CURRENT	= 2,
		DELETECKOBJECT_DEFAULT	= 3,
		DELETECKOBJECT_NODEP	= 4,
		DELETECKOBJECT_FULLDEP	= 5,
	};

	
	
	
	
//-----------------------------------------------------------------------------
//UTILITIES FUNCTION FOR INTERFACE

///////////////////////////////////////////////////////////////////////////////
//rendering functions

	//Render the 3d content in the 3dLayout at the next timer tic (internal to Virtools Dev)
	void				DoOneRender();
	//Render the 3d content in the 3dLayout immediatly
	void				DoOneRenderNow();
	//Blits the back buffer to the front bufferRender in the 3dLayout at the next timer tic (internal to Virtools Dev)
	void				DoOneBlit();


///////////////////////////////////////////////////////////////////////////////
//manipulation of selection in 3DEditor

	//Clears 3dLayout selection
	void				Clear3dSelection(BOOL messages=TRUE,BOOL force=FALSE);
	//Gets the number of selected items in the 3dLayout
	int					Get3dSelectionCount();
	//Gets the selection in the 3dLayout
	CKObjectArray*		Get3dSelection();
	
	//Adds an object
	void				AddTo3dSelection(CKObject* o,BOOL force=FALSE);
	void				AddTo3dSelection(CKObjectArray* o,BOOL force=FALSE);

	void				RemoveFrom3dSelection(CKObject* o,BOOL force=FALSE);

	void				Lock3dSelection(BOOL lock);
	BOOL				Is3dSelectionLocked();

	void				Notify3dSelectionChanged(void* sender=NULL);	//set sender to DllEditorDlg::m_InterfaceOwner


///////////////////////////////////////////////////////////////////////////////
//object setups & editors

	void				OpenEditor(DWORD* guid,void* data);	//param1 = & DWORD[2], param2 = optional data
	void				LaunchObjectSetup(CKObject* o);
	BOOL				IsObjectBeingEdited(CKObject* o);


///////////////////////////////////////////////////////////////////////////////
// Status Bar tools functions

	void				ShowLog();
	void				FlashBomb();

	void				SetSBSelectionInfo(const char* text);
	void				SetSBSBActionInfo(const char* text);
	void				SetSBXInfo(const char* text);
	void				SetSBYInfo(const char* text);
	void				SetSBZInfo(const char* text);
	void				SetSBErrorInfo(const char* text,BOOL beep=TRUE);
	void				SetSBInfoBar(const char* text);
	void				SetSBFpsInfo(const char* text);
	void				SetSBPlayCheck(BOOL check);
	void				SetSBRewindCheck(BOOL check);


///////////////////////////////////////////////////////////////////////////////
//CK centralized functions
	
	BOOL				DeleteCKObject(CK_ID id,DELETION_MODE mode,DWORD flags=0);
	BOOL				DeleteCKObject(CKObject* obj,DELETION_MODE mode,DWORD flags=0);
	BOOL				DeleteCKObjects(CKObjectArray* array,DELETION_MODE mode,DWORD flags=0);
	BOOL				DeleteCKObjects(XObjectArray* array,DELETION_MODE mode,DWORD flags=0);

	void				CopyCKObjects(XObjectArray* ToCopy, XObjectArray* Copy);
	void				CopyCKObjects(CKObjectArray* ToCopy, CKObjectArray* Copy);
	void				CopyCKObject(CKObject* ToCopy, CKObjectArray* Copy);

///////////////////////////////////////////////////////////////////////////////
//INTERFACE PARAMETER : management of a pool of parameter to prevent ck_id overuse

	CKParameterIn*		GetInterfaceParameterIn(char* name=NULL,CKGUID guid=CKPGUID_NONE);
	CKParameter*		GetInterfaceParameter(char* name=NULL,CKGUID guid=CKPGUID_NONE);
	CKParameterOut*		GetInterfaceParameterOut(char* name=NULL,CKGUID guid=CKPGUID_NONE);
	void				FreeInterfaceParameterIn(CK_ID id);
	void				FreeInterfaceParameterOut(CK_ID id);
	void				FreeInterfaceParameter(CK_ID id);
	void				FreeInterfaceParameterIn(CKParameterIn * pin);
	void				FreeInterfaceParameterOut(CKParameterOut * pout);
	void				FreeInterfaceParameter(CKParameter * pout);
	BOOL				IsInterfaceParameter(CK_ID id);


///////////////////////////////////////////////////////////////////////////////
//Virtools Directories

	const char*			GetImportDirectory();
	const char*			GetImportPlaceDirectory();
	const char*			GetImportCharacterDirectory();
	const char*			GetBehaviorSaveLoadDirectory();
	const char*			GetLevelSaveLoadDirectory();
	const char*			GetBitmapSaveLoadDirectory();
	const char*			GetVirtoolsDirectory();

///////////////////////////////////////////////////////////////////////////////
//Project Modified Flags Access

	BOOL				SetProjectModified(BOOL b);
	BOOL				IsProjectModified();
	BOOL				TestProjectModified();


///////////////////////////////////////////////////////////////////////////////
//DRAG & DROP
	
	void				BeginDrag(CUIKEntitySet * set,CImageList * img,POINT* hotspot,void *ownerfrom);
	void				DragStop();
	void				DragCont();
	BOOL				IsDragActive();


///////////////////////////////////////////////////////////////////////////////
//MENU MODIFICATION & USER MENU CALLBACK

	CMenu*				AddPluginMenu(LPCTSTR name,int maxIDs,HWND callbackHWND,VoidFunc1Param callback=NULL);
	void				RemovePluginMenu(CMenu* menu);
	void				ClearPluginMenu(CMenu* menu);

	CMenu*				AddPluginMenuItem(CMenu* menu,int commandID,LPCTSTR name,BOOL sep=FALSE,BOOL sub=FALSE);
	void				RemovePluginMenuItem(CMenu* menu,int commandID,BOOL bypos=FALSE);

	void				UpdatePluginMenu(CMenu* menu);


///////////////////////////////////////////////////////////////////////////////
//LOAD & SAVE
	enum {
			LOADAS_NORMAL		= 1,
			LOADAS_PLACE		= 2,
			LOADAS_CHARACTER	= 3,
			LOADAS_SCENE		= 4,
	}LOADAS;

	BOOL				NewComposition();
	BOOL				LoadComposition(const char* filename);
	BOOL				ImportFile(const char* filename,DWORD loadas=LOADAS_NORMAL);
	BOOL				SaveCurrentComposition();
	BOOL				SaveCurrentCompositionAs(const char* filename);
	BOOL				SaveCurrentCompositionAsVersion();
	BOOL				SaveFile(const char* filename,XObjectArray* array);


///////////////////////////////////////////////////////////////////////////////
//PAUSE

	void				Pause(BOOL b = TRUE);


///////////////////////////////////////////////////////////////////////////////
//NOTIFICATIONS

	//call this function to be able to receive a notification from main Virtools Dev Interface
	//works only after the call of OnInterfaceInit
	void			ObserveNotification(int notification,void* owner);
	//send notification to interface
	//works only after the call of OnInterfaceInit
	HRESULT			SendNotification(void* owner,UINT MsgID,DWORD Param1=0,DWORD Param2=0,CKScene* Context=NULL);

///////////////////////////////////////////////////////////////////////////////
//Get last notification message
	
	struct Notification
	{
		int				messageID;
		DWORD			param1;
		DWORD			param2;
		CKScene*		scene;
	};
	
	const Notification*	GetLastNotification() const;
	const char*			GetLastCompositionName();
	
	
///////////////////////////////////////////////////////////////////////////////
//CKContext

	CKContext*			GetCKContext();
	
///////////////////////////////////////////////////////////////////////////////
//Version control

	VersionControlInfo*	GetVersionControlInfo();

///////////////////////////////////////////////////////////////////////////////
//Keyboard shortcut manager
	KeyboardShortcutManager* GetKeyboardShortcutManager();
	void				EditKeyboardShortcuts(const char* registeredCategoryName=NULL,const char* registeredShortcutName=NULL);

	
//-----------------------------------------------------------------------------
// functions ptrs
private:

///////////////////////////////////////////////////////////////////////////////
//rendering functions

	VoidFunc0Param		m_CuikDoOneRender;
	VoidFunc0Param		m_CuikDoOneRenderNow;
	VoidFunc0Param		m_CuikDoOneBlit;


///////////////////////////////////////////////////////////////////////////////
//manipulation of selection in 3DEditor

	VoidFunc2Param		m_CuikClearSelection;
	DWORDFunc0Param		m_CuikGetSelectionCount;
	DWORDFunc0Param		m_CuikGetSelection;
	VoidFunc2Param		m_CuikAddToSelection;
	VoidFunc2Param		m_CuikAddToSelection2;
	VoidFunc2Param		m_CuikRemoveFromSelection;
	VoidFunc1Param		m_CuikLockSelection;
	DWORDFunc0Param		m_CuikIsSelectionLocked;
	VoidFunc1Param		m_CuikNotifySelectionChanged;


///////////////////////////////////////////////////////////////////////////////
//object setups

	DWORDFunc1Param		m_CuikIsObjectBeingEdited;

	
///////////////////////////////////////////////////////////////////////////////
// Status Bar tools functions

	VoidFunc0Param		m_CUIKShowLog;
	VoidFunc0Param		m_CUIKFlashBomb;

	VoidFunc1Param		m_SetSBSelectionInfo;
	VoidFunc1Param		m_SetSBSBActionInfo;
	VoidFunc1Param		m_SetSBXInfo;
	VoidFunc1Param		m_SetSBYInfo;
	VoidFunc1Param		m_SetSBZInfo;
	VoidFunc2Param		m_SetSBErrorInfo;
	VoidFunc1Param		m_SetSBInfoBar;
	VoidFunc1Param		m_SetSBFpsInfo;
	VoidFunc1Param		m_SetSBPlayCheck;
	VoidFunc1Param		m_SetSBRewindCheck;


///////////////////////////////////////////////////////////////////////////////
//CK centralized functions

	DWORDFunc3Param		m_CUIKDeleteCKObject1;
	DWORDFunc3Param		m_CUIKDeleteCKObject2;
	DWORDFunc3Param		m_CUIKDeleteCKObject3;
	DWORDFunc3Param		m_CUIKDeleteCKObject4;

	VoidFunc2Param		m_CUIKCopyCKObject1;
	VoidFunc2Param		m_CUIKCopyCKObject2;
	VoidFunc2Param		m_CUIKCopyCKObject3;


///////////////////////////////////////////////////////////////////////////////
//INTERFACE PARAMETER : management of a pool of parameter to prevent ck_id overuse

	GetInterfaceParameterFunc	m_GetInterfaceParameterIn;
	GetInterfaceParameterFunc	m_GetInterfaceParameter;
	GetInterfaceParameterFunc	m_GetInterfaceParameterOut;
	VoidFunc1Param		m_FreeInterfaceParameterIn;
	VoidFunc1Param		m_FreeInterfaceParameterOut;
	VoidFunc1Param		m_FreeInterfaceParameter;
	VoidFunc1Param		m_FreeInterfaceParameterIn2;
	VoidFunc1Param		m_FreeInterfaceParameterOut2;
	VoidFunc1Param		m_FreeInterfaceParameter2;
	DWORDFunc1Param		m_IsInterfaceParameter;


///////////////////////////////////////////////////////////////////////////////
//IMPORT DIRECTORIES

	GetPathFunc			m_GetImportDirectory;
	GetPathFunc			m_GetImportPlaceDirectory;
	GetPathFunc			m_GetImportCharacterDirectory;
	GetPathFunc			m_GetBehaviorSaveLoadDirectory;
	GetPathFunc			m_GetLevelSaveLoadDirectory;
	GetPathFunc			m_GetBitmapSaveLoadDirectory;
	GetPathFunc			m_GetVirtoolsDirectory;


///////////////////////////////////////////////////////////////////////////////
//PROJECT MODIFIED

	DWORDFunc1Param		m_SetProjectModified;
	DWORDFunc0Param		m_IsProjectModified;
	DWORDFunc0Param		m_TestProjectModified;


///////////////////////////////////////////////////////////////////////////////
//DRAG & DROP

	VoidFunc4Param		m_BeginDrag;
	VoidFunc0Param		m_DragStop;
	VoidFunc0Param		m_DragCont;
	DWORDFunc0Param		m_IsDragActive;


///////////////////////////////////////////////////////////////////////////////
//MENU MODIFICATION & USER MENU CALLBACK

	DWORDFunc4Param		m_AddPluginMenu;
	VoidFunc1Param		m_RemovePluginMenu;
	VoidFunc1Param		m_ClearPluginMenu;

	DWORDFunc5Param		m_AddPluginMenuItem;
	VoidFunc3Param		m_RemovePluginMenuItem;

	VoidFunc1Param		m_UpdatePluginMenu;


///////////////////////////////////////////////////////////////////////////////
//LOAD & SAVE
	
	DWORDFunc0Param		m_NewComposition;
	DWORDFunc1Param		m_LoadComposition;
	DWORDFunc2Param		m_ImportFile;
	DWORDFunc0Param		m_SaveCurrentComposition;
	DWORDFunc1Param		m_SaveCurrentCompositionAs;
	DWORDFunc0Param		m_SaveCurrentCompositionAsVersion;
	DWORDFunc2Param		m_SaveFile;

	
///////////////////////////////////////////////////////////////////////////////
//CK PAUSE

	VoidFunc1Param		m_CuikPause;
	
	
///////////////////////////////////////////////////////////////////////////////
//NOTIFICATIONS

	SendNotificationFunc	m_NotificationFunc;			//send notification callback func ptr from Virtools
	ObserveNotificationFunc	m_ObserveNotificationFunc;	//Observe notification callback func ptr from Virtools

//Get last notification message
	Notification		m_LastNotification;		//last notification send by Virtools Interface
	CString*			m_LastCompositionName;	//last composition name in Virtools Interface

	
///////////////////////////////////////////////////////////////////////////////
//CKContext
	CKContext*			m_CKContext;		//ckcontext

///////////////////////////////////////////////////////////////////////////////
//Version control
	VersionControlInfo*	m_VersionControl;	//version control struct of source control access

///////////////////////////////////////////////////////////////////////////////
//Keyboard Manager
	KeyboardShortcutManager*	m_KeyboardShortcutManager;
	
	
///////////////////////////////////////////////////////////////////////////////
//Private function for Virtools Only, do not use !!
public:
	PluginInterface();
	BOOL	SetFunctions(void** buffer,int count);
	void	SetLastNotification(int message,DWORD param1,DWORD param2,CKScene* scene);
	void	SetLastCompositionName(CString* lastCmoStr);
	void	SetCKContext(CKContext* context);
	void	SetVersionControlInfo(VersionControlInfo* vc);
	void	SetKeyboardShortcutManager(KeyboardShortcutManager* km);
	
	//this function is call when leaving dev, so that windows & some interface related functions are set
	//to null and become 
	//non usable, since plugins receive a CR_UNLOAD on exit, and may try to use these function
	//which may result in a crash if there wasn't this prevention
	void	ClearFunctionsOnExit();
};





}//namespace VirtoolsExternalPlugin