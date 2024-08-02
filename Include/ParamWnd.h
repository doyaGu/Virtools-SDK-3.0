#pragma once

#include "resource.h"

#ifdef CKCONTROLS_API
   #define CKCONTROLS_CLASS_DECL  __declspec(dllexport)
#else
   #define CKCONTROLS_CLASS_DECL  __declspec(dllimport)
#endif

namespace CKControl	//----------------------------------------
{

//ParamWnd class
//use for multi parameter edition in classes such as MultiParamEditDlg
//purpose of this class is just to automatically draw background
//ie : lines between wnds that are linked to the edition of one parameter

class CKCONTROLS_CLASS_DECL ParamWnd: public CDialog
{
// Construction
public:
	ParamWnd();
	virtual ~ParamWnd();

	void SetVerticalLineCount(int c);
	void SetVerticalLineAltitude(int index, int altitude);
	void SetFirstVerticalLineThickness(int t);
	void SetMargin(int m);

	void AddCaptureKeyWindow(HWND hwnd);

//DATA
protected:
	int		m_verticalLineCount;
	int *	m_verticalLineTable;
	int		m_firstVerticalLineThickness;
	int		m_verticalLineMargin;

	XArray<HWND>	m_captureKeyWindowList;

//MFC
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BehaviorParameterSubDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(BehaviorParameterSubDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};	//ParamWnd class declaration

CKCONTROLS_CLASS_DECL ParamWnd* CreateParamWnd(CWnd* parent);

}	//CKControl namespace