/*
 * Project:                Virtools Interface Plugin SDK
 * File:                   VEP_ScriptActionMenu.h
 * Author:                 Thomas Vissieres
 * Last check date:        11/19/2003 
 * optimized for Tab Size: 4	
 * Quick file summary:     ScriptInterfaceAction class used to execute VSL actions and to fill CMenu with available actions
 */


/*
 *	class ScriptActionMenu
 *	used to simplify execution of VSL scripts actions
 *	and to fill a popup menu with available actions.
 *	
 */





#pragma once


#include "VEP_DllEditorLibDefines.h"
//class CMenu;
//class CWnd;
class ScriptInterfaceAction;

namespace CKControl	//----------------------------------------
{
class  MultiParamEditDlg;
class CKVIPopupMenu;
}

namespace VirtoolsExternalPlugin	//-----------------------------------------
{

class DLLEDITORLIB_CLASS_DECL PluginInterface;

class DLLEDITORLIB_CLASS_DECL ScriptActionMenu
{
public:
	enum
	{
		ACTIONMENU_STARTID		= 20000 ,
	}IDS;

	ScriptActionMenu();
	ScriptActionMenu(PluginInterface* pinterface);
	~ScriptActionMenu();

	//sets the PluginInterface to communicate with Virtools Dev
	void SetPluginInterface(PluginInterface* pinterface);

	//return Value: last command id, 0 if failed
	int UpdateMenu(CMenu* menu,int firstID=ACTIONMENU_STARTID,int insertIndex=-1,const char* actionSubmenuName=NULL);
	//return Value: nonzero if success, zero if failed
	int ExecuteAction(int commandID,CWnd* parent=NULL,BOOL editParameter=TRUE);
	//return Value: nonzero if success, zero if failed. Specify in params an array if you want to keep parameters and to free them later
	int ExecuteAction(ScriptInterfaceAction* iAction,CWnd* parent=NULL,BOOL editParameter=TRUE,BOOL loopingAction=FALSE);
	//start looping action
	int StartLoopingAction(ScriptInterfaceAction* iAction,CWnd* parent=NULL);
	//looping action edit
	int	EditLoopingAction(ScriptInterfaceAction* iAction,CWnd* parent=NULL);
	//stop looping action (close dialog & release interface parameters
	int StopLoopingAction(ScriptInterfaceAction* iAction);


	//get generated command ids count in menu after a call to UpdateMenu for instance
	int	GetCommandIDsCount();

	//first commandID
	int			m_FirstCommandID;
	//last command id
	int			m_LastCommandID;

	//hash table of commandid->action script so that when a menu command is called, we can find the action
	XHashTable<ScriptInterfaceAction*, int> m_ScriptActions;

protected:
	//the plugin interface to communicate with Virtools Dev
	PluginInterface*	m_PluginInterface;
	
	//struct that contains a looping action (action that is called every <delay> milisecond by the interface
	struct LoopingActionData
	{
		HWND							dlgHwnd;
		CKControl::MultiParamEditDlg*	dlg;
		XArray<CKParameter*>			parameters;
		LoopingActionData() {dlg=NULL;dlgHwnd=NULL;}
	};

	//hash table to retrieve the LoopingData of an action (which is represented by a ScriptInterfaceAction*)
	XHashTable<LoopingActionData*,ScriptInterfaceAction*>	m_LoopingActionMap;
	
	CKControl::CKVIPopupMenu*	m_pPopupMenu;
};

int	DLLEDITORLIB_CLASS_DECL GetScriptActionsArray(XArray<ScriptInterfaceAction*>& scriptActions,PluginInterface* pinterface);


}//namespace VirtoolsExternalPlugin

