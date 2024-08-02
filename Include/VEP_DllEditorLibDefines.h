/*
 * Project:                Virtools Interface Plugin SDK
 * File:                   VEP_DllEditorLibDefines.h
 * Author:                 Thomas Vissieres
 * Last check date:        11/19/2003 
 * optimized for Tab Size: 4	
 * Quick file summary:     defines & macros
 */

#pragma once

#include "CKObject.h"




#ifdef DLLEDITORLIB
	#define DLLEDITORLIB_CLASS_DECL  __declspec(dllexport)

	#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

	#include <afxwin.h>         // MFC core and standard components
	#include <afxext.h>         // MFC extensions
	#include <afxcmn.h>

//--------------------------------------
//declaration of specific CK types start
/*
struct CKGUID{
	union{
		struct { DWORD d1,d2; };
		DWORD d[2];
	};
	CKGUID() {d[0]=0;d[1]=0;}
};

typedef DWORD CK_ID;
extern CKGUID CKPGUID_NONE;
*/
//declaration of specific CK types end
//--------------------------------------

#else
   #define DLLEDITORLIB_CLASS_DECL  __declspec(dllimport)
#endif





//-----------------------------------------------------------------------------
//Class Declarations start
class XObjectArray;

class CKScene;
class CKContext;
class CKObjectArray;
class CKObject;
class CKParameterIn;
class CKParameter;
class CKParameterOut;
class CKObject;
class CKObjectDeclaration;
class CKInterfaceObjectManager;

class CUIKEntitySet;
class CUIKCKObjectDescription;

namespace VirtoolsExternalPlugin	//-----------------------------------------
{
class DllEditorDlg;
class DllToolbarDlg;

struct PluginInfo;
struct VersionControlInfo;
struct EditorInfo;
class PluginInterface;
}//namespace VirtoolsExternalPlugin
//Class Declarations end
//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------
//typedef for func ptrs start
typedef void	(*VoidFunc0Param)				();
typedef void	(*VoidFunc1Param)				(DWORD param1);
typedef void	(*VoidFunc2Param)				(DWORD param1,DWORD param2);
typedef void	(*VoidFunc3Param)				(DWORD param1,DWORD param2,DWORD param3);
typedef void	(*VoidFunc4Param)				(DWORD param1,DWORD param2,DWORD param3,DWORD param4);
												
typedef DWORD	(*DWORDFunc0Param)				();
typedef DWORD	(*DWORDFunc1Param)				(DWORD param1);
typedef DWORD	(*DWORDFunc2Param)				(DWORD param1,DWORD param2);
typedef DWORD	(*DWORDFunc3Param)				(DWORD param1,DWORD param2,DWORD param3);
typedef DWORD	(*DWORDFunc4Param)				(DWORD param1,DWORD param2,DWORD param3,DWORD param4);
typedef DWORD	(*DWORDFunc5Param)				(DWORD param1,DWORD param2,DWORD param3,DWORD param4,DWORD param5);
typedef DWORD	(*DWORDFunc6Param)				(DWORD param1,DWORD param2,DWORD param3,DWORD param4,DWORD param5,DWORD param6);

typedef DWORD	(*GetInterfaceParameterFunc)	(char* name,CKGUID guid);
typedef const char*	(*GetPathFunc)				();

typedef long (*SendNotificationFunc)	(void* owner,UINT MsgID,DWORD Param1=NULL,DWORD Param2=NULL,CKScene* Context=NULL);
typedef void (*ObserveNotificationFunc)	(int notification,void* owner);
typedef void (*Function0Parameter)		();
//typedef for func ptrs end
//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------
//DEFINES duplicates of internal Virtools Defines
#define CUIK_ENTITYSET_CLASS_ID					0xc0000008
#define CUIK_CKOBJECTDESCRIPTION_CLASS_ID		0xc000000a






//-----------------------------------------------------------------------------
//MACRO for creating a modeless child dialog
//to use in the functions that will create EditorDlg or ToolbarDlg
//and that will set in the EditorInfo struct

template<class T> HRESULT CreateDllDialog(HWND parent,UINT resId,T** rdlg) 
{
	*rdlg = NULL;

	DLGTEMPLATE* pTemplate =NULL;

	HGLOBAL hTemplate = NULL;
	{
		//Load DLGTEMPLATE
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
 		HINSTANCE hInst= AfxFindResourceHandle(MAKEINTRESOURCE(resId),RT_DIALOG);
		
		if (hInst == NULL)
		{ 
			TRACE("Could not find resource in resource chain");
			ASSERT(FALSE);
			return -1;
		}
 
		HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(resId),RT_DIALOG);

		ASSERT(hRsrc != NULL);

		hTemplate = ::LoadResource(hInst, hRsrc);
		ASSERT(hTemplate != NULL);
 
		pTemplate = (DLGTEMPLATE*)::LockResource(hTemplate);
	}

	CWnd* wndparent=CWnd::FromHandle(parent);
	T* dlg	= new T(wndparent);
	BOOL ok = dlg->CreateIndirect(pTemplate ,wndparent);

	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		::UnlockResource(hTemplate);
		::FreeResource(hTemplate);
	}

	if (ok)
	{
		dlg->ModifyStyle(0,WS_CLIPCHILDREN);
		*rdlg = dlg;
		return S_OK;
	}
	
	delete dlg;
	return -1;
}