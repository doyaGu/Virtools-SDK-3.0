#if !defined(AFX_BASEPARAMETERDIALOG_H__7E09B74B_A330_11D3_B6C8_00902752C68E__INCLUDED_)
#define AFX_BASEPARAMETERDIALOG_H__7E09B74B_A330_11D3_B6C8_00902752C68E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseParameterDialog.h : header file
//

#include ".\button\HighlightBitmapButton.h"
#include "ParameterDialog.h"
#include "VIControls.h"

#define		BASEPARAM_RESIZABLE	1
#define		BASEPARAM_INITED	2
#define		BASEPARAM_BBRUSHOK	4
#define		BASEPARAM_MAXSIZE	8

// PickFlags => -1 : NoPick
//			 =>  0 : Pick Same Kind of Parameter	
//			 => Valid CK_CLASSID : Pick an object of this type
	
/////////////////////////////////////////////////////////////////////////////
// CBaseParameterDialog dialog
class CBaseParameterDialog : public CDialog
{
// Construction
public:
	CBaseParameterDialog(CParameterDialog* pDlg,UINT Template,PARAMETER_PICK PickFlags=PARAMETER_NOPICK,CK_CLASSID ckcid=0,BOOL Resizable=FALSE);   // standard constructor
	virtual ~CBaseParameterDialog() { m_Context->DestroyObject(m_TempParameter,CK_DESTROY_TEMPOBJECT); }
// Dialog Data
	//{{AFX_DATA(CBaseParameterDialog)
	enum { IDD = IDD_BASEPARAMDIALOG };
	VIBitmapButton	m_ButtonPick;
	VIBitmapButton	m_ButtonSize;
	CStatic				m_StaticName;
	//}}AFX_DATA

	void SizeToContent();	
	CKParameter* UpdateTempParameter(BOOL UpdateValue=TRUE);
	CKObject*	CKGetObject(CK_ID id) { return m_Context->GetObject(id); }
	COLORREF	GetLeftPartColor();
public:
	CParameterDialog*	m_PDialog;
	int					m_PickFlags;
	CK_CLASSID			m_ObjPickCid;
	UINT				m_Template;
	DWORD				m_Flags;
	CK_ID				m_TempParameter;
	CKContext*			m_Context;
	CBrush				m_BackgroundBrush;
	int					m_Margin;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseParameterDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBaseParameterDialog)
	afx_msg void OnButtonpick();
	afx_msg void OnButtonsize();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEPARAMETERDIALOG_H__7E09B74B_A330_11D3_B6C8_00902752C68E__INCLUDED_)
