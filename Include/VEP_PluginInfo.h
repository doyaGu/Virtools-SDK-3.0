/*
 * Project:                Virtools Interface Plugin SDK
 * File:                   VEP_PluginInfo.h
 * Author:                 Thomas Vissieres
 * Last check date:        11/19/2003 
 * optimized for Tab Size: 4	
 * Quick file summary:     structure that describes a Virtools Interface Plugin
 */





#pragma once


//Includes---------------------------------------------------------------------
#include "VEP_EditorInfo.h"
#include "VEP_VersionControlInfo.h"





namespace VirtoolsExternalPlugin	//-----------------------------------------
{





//used types declaration-------------------------------------------------------
struct	PluginInfo;
class	PluginInterface;


//type declaration--------------------------------------------------------------
typedef int				(*GetVirtoolsPluginInfoCountFunc)();
typedef PluginInfo*		(*GetVirtoolsPluginInfoFunc)(int index);

/* IMPORTANT : FUNCTION TO EXPORT IN PLUGINS
->These functions must exist and be exported in Dll Editor Plugins
GetVirtoolsPluginInfoCountFunc	GetVirtoolsPluginInfoCount;
GetVirtoolsPluginInfoFunc		GetVirtoolsPluginInfo;
*/






/*
 *	PluginInfo
 *  this structure contains plugin information for Virtools Interface
 *
 *  -m_PluginType		: specify plugin type there (use PLUGIN_TYPE enum). You can combine it with flags.
 *						  for instance, if PT_EDITOR | PTF_RECEIVENOTIFICATION is set and m_PluginCallback not NULL,
 *						  your editor will have it m_PluginCallback called when a notification occured in Virtools Interface
 *						  see CUIKNotification.h for notification
 *
 *						  Note that you can create a no-graphic-interface plugin with PT_UNKNOWN and just use
 *						  m_PluginCallback to get called by Virtools Interface. Then you can listen to notification with
 *						  this callback, and use VEP_PluginInterface function to interact with Virtools
 *						  (for instance, create just a plugin menu)
 *						  see VEP_PluginInterface.h
 *
 *  -m_Name				: specify plugin name here
 *  -m_PluginCallback	: callback called by Virtools Interface for a CALLBACK_REASON
 *  -m_EditorInfo		: fill this structure if your editor is of PT_EDITOR type
 *  -m_VersionControl	: fill this structure if you are doing a Version Control plugin
 */
struct PluginInfo
{
//Defines----------------------------------------------------------------------
#define NAME_LENGTH	80


//-----------------------------------------------------------------------------
//enums
	enum PLUGIN_TYPE {
			PT_UNKNOWN				= 0x00000000,	//unknow type, allowed (for instance if you just need callbacks)
			PT_VERSIONCONTROL		= 0x00000001,	//version control plugin, only one allowed, last one registered is taken into account
			PT_EDITOR				= 0x00000002,	//editor plugin
			PT_SETUP				= 0x00000003,	//setup plugin, not supported yet.

													//16 plugin types allowed, flags are stored after
			PTF_RECEIVENOTIFICATION	= 0x00000010,	//FLAG: notification will be send to this plugin via m_PluginCallback if available
	};

	enum  CALLBACK_REASON {
			CR_NONE,
			CR_LOAD,				//plugin has been loaded
			CR_UNLOAD,				//plugin has been unloaded
			CR_NEWCOMPOSITIONNAME,	//current composition name has changed, for saving / loading / new composition reason. Used by source control plugin
			CR_NOTIFICATION,		//plugin receives notification 
	};

//-----------------------------------------------------------------------------
//typedef function ptr
	typedef void			(*PluginCallbackFunc)(CALLBACK_REASON reason,PluginInterface* plugininterface);
	
//-----------------------------------------------------------------------------
//DATA
	PLUGIN_TYPE				m_PluginType;		//type of plugin (editor, version control ...

	char					m_Name[NAME_LENGTH];//name of plugin

	PluginCallbackFunc		m_PluginCallback;	//if specified, is called by virtools plugin manager with a CALLBACK_REASON

	union
	{
		EditorInfo			m_EditorInfo;		//Editor Info
		VersionControlInfo	m_VersionControl;	//Version Control Info
	};

//-----------------------------------------------------------------------------
//constructor
	PluginInfo(){memset(this,0,sizeof(PluginInfo));}
};





}//namespace VirtoolsExternalPlugin