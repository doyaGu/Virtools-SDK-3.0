/*
 * Project:                Virtools Interface Plugin SDK
 * File:                   VEP_VersionControlInfo.h
 * Author:                 Thomas Vissieres
 * Last check date:        11/19/2003 
 * optimized for Tab Size: 4	
 * Quick file summary:     structure that describes a Source Control Plugin
 */




#pragma once





namespace VirtoolsExternalPlugin	//-----------------------------------------
{




	
/*
 *	VersionControlInfo
 *  if your plugin is a version control plugin (using NxNAlienBrain, Microsoft Visual Source Safe for instance)
 *  This structure contains all callback function pointer necessary for version control, you must then fill
 *  these callback ptrs.
 *
 *  If your plugin is something else, you may just want to access to version control tools.
 *  just call these functions in fitting place of your loading/saving/opening/closing code:
 *  m_OnPreOpen, m_OnPostOpen, m_OnPreSave, m_OnPostSave, m_OnPreClose
 *  and use other functions according to your needs
 *  a VersionControlInfo* is available with PluginInterface::GetVersionControl()
 *  
 */
struct VersionControlInfo
{																	//note : item may be a file,folder or project
//-----------------------------------------------------------------------------
//enums
	enum NODE_TYPE{
		NT_NONE,		//unknow  node type in managed source control database
		NT_FILE,		//file    node type in managed source control database
		NT_FOLDER,		//folder  node type in managed source control database
		NT_PROJECT,		//project node type in managed source control database
		NT_FILE_NS,		//file    node type manageable by source control but exists only in client computer (not synchronised)
		NT_FOLDER_NS,	//folder  node type manageable by source control but exists only in client computer (not synchronised)
	};

	enum CHECKOUT_TYPE{
		CT_UNDEFINED=-1,
		CT_NONE=0,			//file not checked out
		CT_USER,			//file checked out by user
		CT_ANOTHERUSER,		//file checked out by another user
		CT_FOLDER_FULLY,	//folder with all files /sub files checked out, by current user
		CT_FOLDER_PARTIALLY,//folder with some files checked out but some not, by current user
	};

	enum MENU_FLAGS
	{
		MF_GETLATESTVERSION				= 0x00000001,
		MF_CHECKOUT						= 0x00000002,
		MF_CHECKIN						= 0x00000004,
		MF_UNDOCHECKOUT					= 0x00000008,
		MF_IMPORT						= 0x00000010,
		MF_SHOWHISTORY					= 0x00000020,
		MF_SHOWDIFFERENCES				= 0x00000040,
		MF_SHOWPROPERTIES				= 0x00000080,
		MF_SHOWDATABASEEXPLORER			= 0x00000100,
		MF_SHOWSETTINGS					= 0x00000200,
		MF_DISABLE						= 0000000400,
		MF_ADDTOSOURCECONTROL			= 0x00000800,
		MF_REMOVEFROMSOURCECONTROL		= 0x00001000,

		MF_BASIC						= MF_GETLATESTVERSION+		//GETLATESTVERSION->IMPORT)
										  MF_CHECKOUT+
										  MF_CHECKIN+
										  MF_UNDOCHECKOUT+
										  MF_IMPORT,

		MF_EXTENTED						= MF_ADDTOSOURCECONTROL+		//SHOWHISTORY->SHOWPROPERTIES)
										  MF_REMOVEFROMSOURCECONTROL+
										  MF_SHOWHISTORY+
										  MF_SHOWDIFFERENCES+
										  MF_SHOWPROPERTIES,

		MF_TOOLS						= MF_SHOWDATABASEEXPLORER+	//SHOWDATABASEEXPLORER->DISABLE)
										  MF_SHOWSETTINGS+
										  MF_DISABLE,

		MF_BASIC_EXTENDED				= MF_BASIC+MF_EXTENTED,
		MF_BASIC_EXTENDED_TOOLS			= MF_BASIC_EXTENDED+MF_BASIC_EXTENDED+MF_TOOLS,
		MF_BASIC_TOOLS					= MF_BASIC_EXTENDED+MF_TOOLS,
		MF_EXTENDED_TOOLS				= MF_BASIC_EXTENDED+MF_TOOLS,
	};

	enum IMAGE_INDEX					//image index in image list obtained with m_GetImageList function ptr
	{
		II_FOLDER_NS,					//folder	not	synchronised with database
		II_FOLDER_S,					//folder		synchronised with database
		II_FILE_NS,						//file		not	synchronised with database
		II_FILE_S,						//file			synchronised with database
		II_FILE_CHECKOUT,				//file checked out by			user
		II_FILE_CHECKOUTANOTHER,		//file checked out by another	user
		II_FOLDER_NS_SPEC,				//folder	not	synchronised with database	with source control specific icon
		II_FOLDER_S_SPEC,				//folder		synchronised with database	with source control specific icon
		II_PROJECT,						//project
		II_PROJECT_SPEC,				//project									with source control specific icon
	};
//-----------------------------------------------------------------------------
//typedef function ptr
	typedef BOOL (*InitializeFunc)						();

	typedef BOOL (*IsSourceControlPluginActiveFunc)		();
	typedef void (*EnableFunc)							(BOOL enable);

	typedef BOOL (*OnPreOpenFunc)						(const char* currentFile, const char* fileToLoad);
	typedef BOOL (*OnPostOpenFunc)						(const char* currentFile);
	typedef BOOL (*OnPreSaveFunc)						(const char* currentFile, const char* fileToSave);
	typedef BOOL (*OnPostSaveFunc)						(const char* currentFile);
	typedef BOOL (*OnPreCloseFunc)						(const char* currentFile);
	typedef BOOL (*CheckOutFunc)						(const char* sFile);
	typedef BOOL (*UndoCheckOutFunc)					(const char* sFile);
	typedef BOOL (*CheckInFunc)							(const char* sFile,BOOL bKeepCheckOut);
	typedef BOOL (*ImportFunc)							(const char* sFile);
	typedef BOOL (*GetLatestVersionFunc)				(const char* sFile,BOOL references=FALSE);
	typedef BOOL (*AddToSourceControlFunc)				(const char* sFile);
	typedef BOOL (*RemoveFromSourceControlFunc)			(const char* sFile);
	typedef const char* (*LoadFileFromSourceControlFunc)();
	typedef NODE_TYPE (*IsNodeInDatabaseFunc)			(const char* sFile,CHECKOUT_TYPE *oCheckOut=NULL);
	typedef BOOL (*ShowDatabaseExplorerFunc)			();
	typedef BOOL (*EditSettingsFunc)					();
	typedef BOOL (*ShowHistoryFunc)						(const char* sFile);
	typedef BOOL (*ShowDifferencesFunc)					(const char* sFile);
	typedef BOOL (*ShowPropertiesFunc)					(const char* sFile);

	typedef BOOL (*AddSourceControlMenuToFunc)			(CMenu* menu,const char* path,int startingCommandID,int* endingCommandID,MENU_FLAGS flags=MF_BASIC_EXTENDED);
	typedef void (*MenuCallbackFunc)					(int commandID);
	
	typedef CImageList*	(*GetImageListFunc)				();

//-----------------------------------------------------------------------------
//function ptr
	InitializeFunc					m_Start;						//to call after loading dll
	InitializeFunc					m_Stop;							//to call before unloading dll

	IsSourceControlPluginActiveFunc	m_IsEnabled;					//is source control plugin active
	EnableFunc						m_Enable;						//enable / disable source control plugin

	OnPreOpenFunc					m_OnPreOpen;					//callback that should be called before opening file
	OnPostOpenFunc					m_OnPostOpen;					//callback that should be called after opening file
	OnPreSaveFunc					m_OnPreSave;					//callback that should be called before saving file
	OnPostSaveFunc					m_OnPostSave;					//callback that should be called after saving file
	OnPreCloseFunc					m_OnPreClose;					//callback that should be called before closing file

	CheckOutFunc					m_CheckOut;						//check out item
	CheckInFunc						m_CheckIn;						//check in item
	ImportFunc						m_Import;						//import item (and add it in alienbrain database
	GetLatestVersionFunc			m_GetLatestVersion;				//get latest version of item
																	//if references==TRUE, then setting
																	//"When opening a file with references" will be used
	UndoCheckOutFunc				m_UndoCheckOut;					//undo check out item

	AddToSourceControlFunc			m_AddToSourceControl;			//add item to source control
	RemoveFromSourceControlFunc		m_RemoveFromSourceControl;		//remove item from source control
	LoadFileFromSourceControlFunc	m_LoadFileFromSourceControl;	//load file from source control

	IsNodeInDatabaseFunc			m_IsNodeInDatabase;				//is item in database, return a NXN_NODE_TYPE
																	//Note that NT_FOLDER_NS & NT_FILE_NS mean
																	//that folder / file is not present in database but only on client computer
																	//and  can be managed by source control
																	//because a parent folder is in database.
	
	ShowDatabaseExplorerFunc		m_ShowDatabaseExplorer;			//show database explorer
	EditSettingsFunc				m_EditSettings;					//edit nxn settings func
	ShowHistoryFunc					m_ShowHistory;					//show history of file if mapped in source control
	ShowDifferencesFunc				m_ShowDifferences;				//show difference of file with previous version (stats comparison)
	ShowPropertiesFunc				m_ShowProperties;				//show file properties if mapped (show statistics)

	AddSourceControlMenuToFunc		m_AddSourceControlMenuTo;		//add to a CMenu* menu item according to file / path state in Source Control database
																	//return value: endingCommandID: you should use that value to determine
																	//if you should callback VersionControl plugin after
	MenuCallbackFunc				m_MenuCallback;					//if you called m_AddSourceControlMenuTo, when your windowProc
																	//returns a menu command between startingCommandID and endingCommandID,
																	//then call this callback with id = returned ID - startingCommandID

	GetImageListFunc				m_GetImageList;					//returns image list, use IMAGE_INDEX to get required image
};





}//namespace VirtoolsExternalPlugin