// ParameterDialog.h: interface for the CParameterDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARAMETERDIALOG_H__7E09B741_A330_11D3_B6C8_00902752C68E__INCLUDED_)
#define AFX_PARAMETERDIALOG_H__7E09B741_A330_11D3_B6C8_00902752C68E__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum {
	PARAMETER_NOPICK	 =	0,
	PARAMETER_PICKPARAM	 =  1,
	PARAMETER_PICKOBJECT =	2,
	PARAMETER_PICKALL	 =	3,
} PARAMETER_PICK;


#define PARAMETER_RESIZE	 TRUE
#define PARAMETER_NORESIZE	 FALSE

class CParameterDialog;
class CBaseParameterDialog;
class CKeyParameterDialog;

__declspec(dllexport) HWND CreateParameterDialog(HWND parent,CParameterDialog* Dlg,UINT Template,PARAMETER_PICK PickFlags=PARAMETER_NOPICK,CK_CLASSID ckcid=0,BOOL Size=FALSE);
__declspec(dllexport) CKeyParameterDialog* CreateKeyDialog(HWND parent,CKParameter* param);



/////////////////////////////////////////////////////////////////////////////
// CParameterDialog dialog

class AFX_EXT_CLASS CParameterDialog : public CDialog
{
// Construction
public:
	CParameterDialog(CKParameter* Parameter,CK_CLASSID Cid=CKCID_OBJECT);   // standard constructor
	virtual ~CParameterDialog() {}
// Dialog Data
	//{{AFX_DATA(CParameterDialog)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	virtual CKBOOL On_Init()									{ return TRUE; }
	virtual CKBOOL On_Cancel()									{ return TRUE; }
	virtual CKBOOL On_UpdateFromParameter(CKParameter* Param){ return TRUE; }
	virtual CKBOOL On_UpdateToParameter(CKParameter* Param)	{ return TRUE; }
	virtual CKBOOL ChangeSize(CKBOOL Max)						{ return TRUE; }
	virtual CK_ID  On_Pick(LPPOINT ClientPoint,int ClassID)				{ return 0; }		
	virtual CK_ID  On_ParameterPick(LPPOINT ScreenPoint,int ParameterType)	{ return 0; }		
// Pre Implemented methods
	virtual CKBOOL On_Ok()										{ return On_UpdateToParameter(NULL); }
	virtual CKBOOL On_PickResult(CK_ID picked,HWND Control,CKBOOL Clicked = FALSE);		
	
	void	StartPick(int PickFilter,CK_CLASSID ckcid, HWND Control,BOOL start=TRUE);
	CKBOOL	NotifyParameterModification(HWND wnd);

	CKObject* CKGetObject(CK_ID id) { return m_Context->GetObject(id); }

public:
	CK_ID					m_EditedParameter;
	CK_CLASSID				m_EditedClassID;
	CKBOOL					m_PickActive;
	CKDWORD					m_PickFilter;
	CK_CLASSID				m_ObjPickCid;
	
	HWND					m_PickControl;
	BOOL					m_PickResult;
	BOOL					m_Maximized;
	CBaseParameterDialog*	m_Owner;
	CWnd*					m_FocusWindow;
	CKContext*				m_Context;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParameterDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CParameterDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



#endif // !defined(AFX_PARAMETERDIALOG_H__7E09B741_A330_11D3_B6C8_00902752C68E__INCLUDED_)
