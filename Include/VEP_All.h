/*
 * Project:                Virtools Interface Plugin SDK
 * File:                   VEP_All.h
 * Author:                 Thomas Vissieres
 * Last check date:        11/19/2003 
 * optimized for Tab Size: 4	
 * Quick file summary:     all headers
 */

/*
 *	VEP_ALL.h
 *  
 *  use this generic include for external plugin if you do not want to manage manually includes
 *  contains all necessary references to Virtools External Plugin
 *  
 *  -defines, types, enum, class declaration
 *  -CUIKEntitySet				: container of CUIKCKObjectDescription send while user is using drag & drop in Virtools
 *  -CUIKCKObjectDescription	: generic container of data (may be a CKObject,a Virtools Object, a resource, ...
 *  -CUIKNotification.h			: list of notification + description
 *  -DllEditorDlg				: base dialog class for external editor
 *  -DllToolbarDlg				: base dialog class for external editor toolbar
 *  -PluginInfo					: contains necessary data to load a plugin in Virtools
 *  -EditorInfo					: contains necessary data to create an plugin editor in Virtools
 *  -VersionControlInfo			: contains necessary data to load or use a Version Control Plugin in Virtools or in external plugins
 *  -PluginInterface			: contains functions pointers to interact with Virtools
 *  
 */

#pragma once

#include "VEP_DllEditorLibDefines.h"

#include "CUIKEntitySet.h"
#include "CUIKCKObjectDescription.h"
#include "CUIKNotifications.h"

#include "VEP_DllEditorDlg.h"
#include "VEP_PluginInfo.h"
#include "VEP_PluginInterface.h"

/*
 *
 * The following includes may be included in your plugin if you plan to use 
 * -the Keyboard shortcut manager (have keyboard shortcuts without coding your own manager or having fixed shortcuts
 * -VSL actions
 *
 * #include "VEP_KeyboardShortcutManager.h"
 * #include "VEP_ScriptActionMenu.h"
 *
 *
 */



using namespace VirtoolsExternalPlugin;