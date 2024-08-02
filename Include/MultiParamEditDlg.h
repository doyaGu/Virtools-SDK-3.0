#pragma once

/*sends 
WM_NOTIFY with code
VI_CTRL_NM_ENDDIALOGCANCEL:
VI_CTRL_NM_ENDDIALOGOK:
VI_CTRL_NM_DIALOGAPPLY
on close
*/

#ifdef CKCONTROLS_API
   #define CKCONTROLS_CLASS_DECL  __declspec(dllexport)
#else
   #define CKCONTROLS_CLASS_DECL  __declspec(dllimport)
#endif

namespace CKControl	//----------------------------------------
{

//used class
class ScrollWnd;
class ParamWnd;

class CKCONTROLS_CLASS_DECL MultiParamEditDlg : public VIDialog
{
// Construction
public:
	MultiParamEditDlg(CKContext* context,CWnd* parent = NULL);
	BOOL ModelessCreate(CWnd* parent);

	enum   {MODELESSEDIT			= 0x00000001,	//modeless edit, send notification on close, no auto DestroyWindow on ok/cancel
			CREATEPARAM				= 0x00000002,
			EDITSETTINGS			= 0x00000004,
			TARGET					= 0x00000008,
			MODAL					= 0x00000010,
			AUTOCLOSE_WHEN_MODELESS	= 0x00000020,
	}MODE;

	//set what you want to edit : a beh / op / some parameters
	void	SetBehavior(CK_ID behID,CK_ID ownerID,CK_ID parentBehID=0);
	void	SetParameterOperation(CK_ID opID,DWORD parentBehID=0);
	void	AddParameter(CKParameter * param);

	void	SetMode(int mode);
	int		GetMode();
	int		ModifyMode(int added,int removed=0);
	BOOL	HasMode(int mode);

	//multi parameter edit

	//custom title
	void	SetTitle(char *title);

//FUNCS
protected:
	void	UpdateCKWnds();
	void	SetCKWndsMargins(int margin);
	void	InitSubWnds();
	void	UpdateWindowSize(RECT bigrect,BOOL updatePos=TRUE);

	BOOL	EditParameters(int &maxmargin);	//edit all parameter in m_ParameterArray.

	BOOL	EditBehavior();					//prepare m_ParameterArray for behavior edition
	BOOL	EditBehaviorSettings();			//prepare m_ParameterArray for behavior settings edition
	BOOL	EditParameterOperation();		//prepare m_ParameterArray for parameter operation edition

	CKParameter*	GetSourceForPin(CKParameterIn* pin);
	BOOL			CheckSource(CKParameter* &source);

//DATAS
protected:
//to edit parameters (and not a behavior)
	XArray<CKParameter*>		m_ParameterArray;
	XArray<CKParameterLocal*>	m_AddedLocalParameterArray;

//CUSTOM TITLE
	XString m_Title;

//CK DATA
	CK_ID	m_ID;				//behavior
	CK_ID	m_OwnerID;			//owner
	CK_ID	m_ParentBehID;		//parent behavior

//GRAPHIC DATA
	int		m_targetAltitude;
	BOOL	m_bInitDialogComplete;

//CK2UI windows
	HWND*	m_WndList;			//list of ck2ui hwnd
	int		m_WndCount;			//count of ck2ui wnd

//MODE
	int		m_Mode; 

	
//PARENT WINDOW
	CWnd*		m_ParentWnd;

//SUB WINDOWS
	ScrollWnd*		m_ScrollWnd;
	ParamWnd*		m_ParamWnd;

//CKContext
	CKContext*		m_Context;




//MFC
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MultiParamEditDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MultiParamEditDlg)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};	//MultiParamEditDlg class declaration

}	//namespace CKControl
