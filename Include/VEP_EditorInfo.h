/*
 * Project:                Virtools Interface Plugin SDK
 * File:                   VEP_EditorInfo.h
 * Author:                 Thomas Vissieres
 * Last check date:        11/19/2003 
 * optimized for Tab Size: 4	
 * Quick file summary:     structure that describes an Editor
 */





#pragma once





namespace VirtoolsExternalPlugin	//-----------------------------------------
{





//-----------------------------------------------------------------------------
//used class declaration
class DllEditorDlg;
class DllToolbarDlg;

/*
 *	EditorInfo struct contains essential data for Virtools Interface to create an editor
 *  the Dll must fill this structure.
 * 
 *  an external dll editor must have :
 *  -a CreateEditorDlg callback that creates the editor dialog
 *	-a unique guid in m_Guid (you can use CKGuidGen.exe in Virtools Dev\Virtools_SDK\Utils if available for instance
 *	-a name in m_EditorName
 *
 *  an external dll editor can have but it is not necessary:
 *  -a CreateToolbarDlg callback that creates the editor toolbar dialog
 *
 *  you can then specify
 *  -m_bUnique			: if your editor is unique and cannot be duplicated by using the "Editors" menu in Virtools Interface
 *  -m_bIndestructible	: if your editor cannot be removed from interface.
 *  -m_bManageScrollbar	: if you want Virtools Interface to manage scrollbars automatically. You then need to fill m_Width and m_Height
 *						  call DllEditorDlg::UpdateEditorSize() if you modify these width and height dynamically after creation
 *  -m_Width			: usefull only if you set m_bManageScrollbar to TRUE
 *  -m_Height			: usefull only if you set m_bManageScrollbar to TRUE
 *  -m_ToolbarHeight	: set a specific toolbar height if you need
 *
 *  See VEP_DllEditorDlg.h for specifications about dialog creation callbacks
 *  
 */
struct EditorInfo
{
//Defines----------------------------------------------------------------------
#define NAME_LENGTH	80

//-----------------------------------------------------------------------------
//typedef function ptr
	typedef DllEditorDlg*		(*CreateEditorDlg)(HWND parent);	//callback used by Virtools to create main Editor
	typedef DllToolbarDlg*		(*CreateToolbarDlg)(HWND parent);	//callback used by Virtools to create Editor Toolbar

//Editors
	DWORD			m_Guid[2];					//unique guid
	char			m_EditorName[NAME_LENGTH];	//editor name

	CreateEditorDlg		m_CreateEditorDlgFunc;	//callback that creates the main dialog of the editor/setup
	CreateToolbarDlg	m_CreateToolbarDlgFunc;	//callback that creates the toolbar dialog of the editor/setup

	int				m_bUnique;					//if set, editor/setup cannot have more than 1 instance in Virtools Interface
	int				m_bIndestructible;			//if set, instance of editor/setup cannot be removed
	int				m_bManageScrollbar;			//if set, Virtools Interface will manager scrollbars,
												//so member m_Width & m_Height will be taken into account.
												//Virtools Interface assume that the editor/setup
												//has a constant size and will automatically create scrollbars
												//according to available room.
												//Otherwise Editor Dialog will be resized to its parent size in Virtools Interface

	int				m_Width;	//m_bManageScrollbar must be 1 for this to be taken into account; constant width  of editor/setup
	int				m_Height;	//m_bManageScrollbar must be 1 for this to be taken into account; constant height of editor/setup
	int				m_ToolbarHeight;	//if 0 then use default height (21 pixels)

	//Setups only
	int				m_SetupClassID;		//Not used yet. Ck class id of objects that are to be edited in this setup.
	
	//custom icon
	CImageList*		m_IconList;		//image list of editor
	int				m_IconIndex;	//index of icon editor that will appear just before its name in Virtools Interface
};





}//namespace VirtoolsExternalPlugin