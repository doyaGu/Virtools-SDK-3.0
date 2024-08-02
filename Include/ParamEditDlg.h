#pragma once

#include "resource.h"

#ifdef CKCONTROLS_API
   #define CKCONTROLS_CLASS_DECL  __declspec(dllexport)
#else
   #define CKCONTROLS_CLASS_DECL  __declspec(dllimport)
#endif

namespace CKControl	//----------------------------------------
{

//class ParamEditDlg
//used to edit one CK parameter only.
//name, type and value can be shown (edit/read only/hidden)
//
//to use : call SetParameter() then call either DoModal or ModelessCreate

class CKCONTROLS_CLASS_DECL ParamEditDlg : public VIDialog
{
// Construction
public:
	ParamEditDlg(CKContext* context,CWnd* pParent = NULL);   // standard constructor
	BOOL ModelessCreate(CWnd* parent);

	enum   {MODELESSEDIT			= 0x00000001,	//modeless edit, send notification on close, no auto DestroyWindow on ok/cancel
			CAN_EDIT_NAME			= 0x00000002,
			CAN_EDIT_TYPE			= 0x00000004,
			CAN_EDIT_VALUE			= 0x00000008,
			HIDE_NAME				= 0x00000010,
			HIDE_TYPE				= 0x00000020,
			HIDE_VALUE				= 0x00000040,
			HIDE_VALUE_STATICTEXT	= 0x00000080,
			HIDE_NAMESECTION		= 0x00000100,	//unused
			UPDATE_WNDS				= 0x00000200,
			UPDATEING_WNDS			= 0x00000400,
			MODAL					= 0x00000800,
			AUTOCLOSE_WHEN_MODELESS	= 0x00001000,
	}MODE;

	//change title of dialog
	void SetTitle(char *title);

	//Mode Modification
	void	SetMode(int mode);
	int		GetMode(int mode);
	int		ModifyMode(int added,int removed=0);
	BOOL	HasMode(int mode);


	//Mode Modification, obsolete
	void EditName(BOOL b = TRUE);
	void EditType(BOOL b = TRUE);
	void EditValue(BOOL b = TRUE);
	void HideName(BOOL b = TRUE);
	void HideType(BOOL b = TRUE);
	void HideValue(BOOL b = TRUE);
	void HideValueStaticText(BOOL b = TRUE);
	void HideNameSection(BOOL b = TRUE);	

	//Set parameter to edit
	void SetParameter(CKParameterIn *pin);
	void SetParameter(CKParameter *param);
	//multi parameter edit
	void AddParameter(CKParameter *pout);

	//Get parameter datas after edition
	int GetType();
	char * GetName();


	void UpdateWindowsSize(BOOL typeHasChanged=TRUE,BOOL redraw=TRUE);
	void CreateWindows();
	void CreateCKWnd();
	void OnParameterTypeChange();
	void PlaceWindow(BOOL updatePos=TRUE);

	typedef void	(*ApplyCB)(void* iArg);
	void	SetApplyCallback(ParamEditDlg::ApplyCB iCallback, void* iArg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ParamEditDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	CKContext*			m_Context;	//CKContext
	XArray<CKParameter*>	m_parameterArray;

	CKParameterIn *		m_pin;
	CKParameter*		m_pout;

	CString				m_Title;
	CString				m_name;
	int					m_type;
	HWND				m_wnd;
	RECT				m_wndRect;
	int					m_wndY;

	VIEdit			m_wndNameEdit;
	VIComboBox		m_wndTypeComboBox;
	VIStaticText		m_wndNameTextStatic;
	VIStaticText		m_wndTypeTextStatic;
	VIStaticText		m_wndValueTextStatic;
	VIStaticText		m_wndNameStatic;
	VIStaticText		m_wndTypeStatic;
	VIStaticText		m_wndValueStatic;

//MODE, specific flags for this dlg
	DWORD				m_Mode;

//PARENT WINDOW
	CWnd*				m_pParentWnd;

//apply callback
	void*				m_CallbackArg;
	ApplyCB				m_Callback;

	// Generated message map functions
	//{{AFX_MSG(ParamEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};	//ParamEditDlg class declaration

}	//namespace CKControl
