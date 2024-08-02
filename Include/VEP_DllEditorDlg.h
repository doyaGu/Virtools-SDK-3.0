/*
 * Project:                Virtools Interface Plugin SDK
 * File:                   VEP_DllEditorDlg.h
 * Author:                 Thomas Vissieres
 * Last check date:        11/19/2003 
 * optimized for Tab Size: 4	
 * Quick file summary:     base class for dialogs for editor & toolbar
 */

#pragma once

#include "VEP_DllEditorLibDefines.h"
#include "CUIKEntitySet.h"			//CUIKEntity set & CUIKCKObjectDescription
#include "VEP_PluginInterface.h"

class VIBitmapButton;


namespace VirtoolsExternalPlugin	//-----------------------------------------
{





/*
 *	Important Note :
 *  in editor dlg or toolbar dlg functions
 *  do not forget to call
 *  AFX_MANAGE_STATE(AfxGetStaticModuleState());
 *  before using some code using internal resources to your plugin dll
 *
 */

/*
 *
 * in external dll, user should define
 * -a CreateEditorDlg func,
 * -a CreateToolbarDlg func (if toolbar needed)

//the following variables should be defined in whatever .cpp file you want
extern MyEditorDlg*		g_Editor;
extern MyToolbarDlg*	g_Toolbar;

DllEditorDlg* fCreateEditorDlg(HWND parent)
{
	HRESULT r = CreateDllDialog(parent,IDD_EDITOR,&g_Editor);
	return (DllEditorDlg*)g_Editor;
}

DllToolbarDlg*	fCreateToolbarDlg(HWND parent)
{
	HRESULT r = CreateDllDialog(parent,IDD_TOOLBAR,&g_Toolbar);
	return (DllToolbarDlg*)g_Toolbar;
}


 * IDD_EDITOR is the resource ID for the Editor Dialog and IDD_TOOLBAR for the Toolbar Dialog
 */











/*
 *	DllDialogInterface
 *  base for editor and toolbar dialog
 *  
 *  user should create / initialise controls in OnInterfaceInit() callback instead of OnInitialDialog()
 *  if those controls need access to a CKContext, because in OnInitialDialog() callback, the CKContext is not available
 *  Those CK-dependant controls should be de-initialized & destroyed in OnInterfaceEnd()
 *  Do not forget to use AFX_MANAGE_STATE(AfxGetStaticModuleState()); at the beginning of these callbacks
 *  
 *  OnDrop(), CanDrop() and DropExit() are called by Virtools Interface to ask whether the Plugin Editor want to manage
 *  the dragged selection.
 *  
 *	Notification use :-----------------
 *
 *  all notifications are listed in CUIKNotifications.h. Parameters are described too.
 *
 *  -first of all you must tell (register) which notifications you want to listen to
 *   call ObserveNotification(index_of_notification_you_want_to_listen_to); for all notifications needed
 *  -When a registered notification is send by Virtools Interface, 
 *   DllEditorDlg::ReceiveNotification is called : override this function to analyse the notification parameters
 *  -to send notification, use DllDialogInterface::SendNotification
 *
 */
class DLLEDITORLIB_CLASS_DECL DllDialogInterface
{
public:
//FLAGS, see protected var: m_Flags********************************************
	enum {	NONE=0,			//editor & toolbar do not have the focus
			ACTIVE=1,		//editor & toolbar have focus
	}DLLDIALOGINTERFACEFLAGS;

//TOOL FUNCTIONS***************************************************************
	//modify flags of dialog
	//can be overridden if you want to cach flag modification
	virtual DWORD	ModifyFlags(DWORD added,DWORD removed=0);

//CALLBACKS********************************************************************
	//called when activated / deactivated, can be overridden
	virtual void	OnActivate(BOOL b);
	//called after interface data has been set. DllToolbarDlg::OnInterfaceInit is called before DllEditorDlg::OnInterfaceInit
	virtual void	OnInterfaceInit();
	//called just before the dlg is destroyed and deleted. You should put deinitialisation code & delete here
	virtual void	OnInterfaceEnd();


	//callback called by interface when something is dropped on dialog
	//return value not taken into accout for now
	virtual HRESULT OnDrop(POINT &clientP,CUIKEntitySet * set);
	//callback called by interface when something is dragged over the dialog.
	//return TRUE if the dragged item can be dropped on dialog, otherwise return FALSE
	virtual BOOL CanDrop(POINT &clientP,CUIKEntitySet * set);
	//callback called by interface during a drag & drop when the mouse leaves the dialog
	//return value not taken into accout for now
	virtual HRESULT DropExit();

//NOTIFICATION with interface**************************************************
	//call this function to be able to receive a notification from main Virtools Dev Interface
	//works only after the call of OnInterfaceInit
	void			ObserveNotification(int notification);
	//send notification to interface
	//works only after the call of OnInterfaceInit
	HRESULT			SendNotification(UINT MsgID,DWORD Param1=0,DWORD Param2=0,CKScene* Context=NULL);
	//receive notifaction : needs to be overridden
	virtual HRESULT ReceiveNotification(UINT MsgID,DWORD Param1=0,DWORD Param2=0,CKScene* Context=NULL);

//DATA*************************************************************************
public:
	virtual PluginInterface*	GetInterface()=0;		//returns CUIK (Virtools Dev's) interface
	virtual void*				GetOwner()=0;			//get interface owner
	virtual CKContext*			GetCKContext()=0;		//returns CK Context

	DWORD			GetFlags();
protected:
	DWORD			m_Flags;			//flags
};










/*
 *	DllToolbarDlg
 *  derived dialog for toolbar
 *  
 ***When OnInterfaceInit() has been called and after that***
 *  
 *  you have access to
 *  -the editor dialog,
 *  -a CKContext to interact with CK
 *  -and a PluginInterface to interact with Virtools Interface (see VEP_PluginInterface.h)
 *  
 */
class DLLEDITORLIB_CLASS_DECL  DllToolbarDlg : public CDialog,public DllDialogInterface
{
public:
	DllToolbarDlg(UINT nIDTemplate,CWnd* pParentWnd = NULL);

	//FLAGS, see protected var: m_Flags
	enum {
		DRAWTOOLBAR	= 2,
		
	}DLLTOOLBARFLAGS;

protected:

	//Show / Hide the Close Button
	void			ActivateClosebutton(BOOL activate=TRUE);

//DATA*************************************************************************
public:
	DllEditorDlg*				GetEditorDlg();		//returns editor dialog
	virtual CKContext*			GetCKContext();		//returns CK Context
	virtual PluginInterface*	GetInterface();		//returns CUIK (Virtools Dev's) interface
	virtual void*				GetOwner();			//get interface owner

protected:
	DllEditorDlg*	m_EditorDlg;		//ptr to editor/setup dlg

private:
//DRAWING TOOL FUNCTIONS*******************************************************
	//drawing toolbar, called when the toolbar needs to be painted and if flags have the DRAWTOOLBAR flag
	virtual void	DrawToolbar(CDC* dc=NULL);

//WINDOWS FUNC*****************************************************************
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DllToolbarDlg)
	public:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	VIBitmapButton*	m_CloseButton;
//-----------------------------------------------------------------------------
//PRIVATE FUNCS
//Specific for communication with Virtools Interface
//Do not use
public:
	void			SetEditorDlg(DllEditorDlg* dlg);
	virtual void	OnActivate(BOOL b);
//-----------------------------------------------------------------------------
};










/*
 *	DllEditorDlg
 *	Dialog class from which plugin editor should derives
 *	Note about overridable functions : do not forget to call original function from DllEditorDlg::
 *	
 ***When OnInterfaceInit() has been called and after that***
 *  
 *  you have access to
 *  -the toolbar dialog if available,
 *  -a CKContext to interact with CK
 *  -and a PluginInterface to interact with Virtools Interface (see VEP_PluginInterface.h)
 *	
 *  
 *  -----------------------------------
 *  
 *  UpdateEditorSize()	: if you specified in the EditorInfo struct that you want Virtools Interface
 *						  to manage scrollbars for your editor, and then you changed the m_Width and/or m_Height
 *						  member of this struct (the one send to Virtools Interface in the PluginInfo structure)
 *						  then call this function to tell Virtools Interface to update scrollbars.
 *						  if you modified EditorInfo::m_bManageScrollbar, you must call this function too
 *  
 *  
 *  LoadData()			: called by Interface when a composition is loaded with a CKInterfaceObjectManager
 *  SaveData()			: called by Interface when a composition is saved with a CKInterfaceObjectManager
 *						  CKInterfaceObjectManager is a CKObject and a container of CKStateChunk
 *						  in which you can store / read data relative to the saved /loaded composition and your editor
 *  
 */
class DLLEDITORLIB_CLASS_DECL  DllEditorDlg : public CDialog,public DllDialogInterface
{
// Construction
public:
	DllEditorDlg(UINT nIDTemplate,CWnd* pParentWnd = NULL);

	void			Close();	//close editor

//custom popup menu************************************************************
	virtual void	OnCustomMenu(CMenu* menu,int startingCommandID,int endingCommandID);	//called to complete menu
																							//when user right click on tab button
	virtual void	OnCustomMenu(int commandID);	//called if a menu item from completed menu has been selected

//misc*************************************************************************
	void UpdateEditorSize();//the EditorInfo's size datas of the dll editor have been changed, then call this callback to notify the interface

//CALLBACK FUNCTIONS CALLED BY INTERFACE WHEN LOADING/SAVING CMO FILES*********
	virtual BOOL LoadData(CKInterfaceObjectManager* iom);
	virtual BOOL SaveData(CKInterfaceObjectManager* iom);

//DATA*************************************************************************
public:
	DllToolbarDlg*				GetToolbarDlg();	//returns Toolbar Dlg
	virtual CKContext*			GetCKContext();		//returns CK Context
	virtual PluginInterface*	GetInterface();		//returns CUIK (Virtools Dev's) interface
	virtual void*				GetOwner();			//get interface owner

protected:
	DllToolbarDlg*			m_ToolbarDlg;		//ptr to editor/setup  toolbar dlg
	PluginInterface*		m_Interface;		//interface class that have function pointers to Virtools Interface utilities

//WINDOWS FUNC*****************************************************************
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DllEditorDlg)
	public:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

//-----------------------------------------------------------------------------
//PRIVATE FUNCS
//Specific for communication with Virtools Interface
//Do not use (unless specified, for instance, m_InterfaceOwner in PluginInterface::Notify3dSelectionChanged)
private:
	void*					m_Owner;			//ptr to owner editor in Virtools
public:
	void			SetOwner(void* owner);
	void			SetToolbarDlg(DllToolbarDlg* dlg);
	void			SetInterface(PluginInterface* pluginInterface);
//-----------------------------------------------------------------------------
};





}//namespace VirtoolsExternalPlugin