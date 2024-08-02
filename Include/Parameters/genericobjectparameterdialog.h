#if !defined(AFX_GENERICOBJECTPARAMETERDIALOG_H__C7D34881_A7DD_11D3_B6C8_00902752C68E__INCLUDED_)
#define AFX_GENERICOBJECTPARAMETERDIALOG_H__C7D34881_A7DD_11D3_B6C8_00902752C68E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// genericobjectparameterdialog.h : header file
//

#include "..\BaseParameterDialog.h"
#include "..\CKObjectComboBox.h"

/////////////////////////////////////////////////////////////////////////////
// CGenericObjectParameterDialog dialog

class CGenericObjectParameterDialog : public CParameterDialog
{
// Construction
public:
	CGenericObjectParameterDialog(CKParameter* Parameter,CK_CLASSID Cid=CKCID_OBJECT) : CParameterDialog(Parameter,Cid),m_Derived(TRUE){}   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGenericObjectParameterDialog)
	enum { IDD = IDD_GENOBJECTDIALOG };
	VIButton		m_ShowSetup;
	VICheckButton	m_Check;
	VIEdit		m_Edit;
	VIStaticText	m_Static3;
	VIStaticText	m_Static2;
	VIStaticText	m_Static1;
	VIComboBox	m_ClassCombo;
	CKObjectComboBox	m_Combo;
	BOOL			m_Derived;
	CString			m_TextFilter;
	//}}AFX_DATA
	CString			m_ComboCurStr; // Add by Araya to the selection name from outside

	virtual CKBOOL On_Init();
	virtual CKBOOL On_UpdateFromParameter(CKParameter* Param);
	virtual CKBOOL On_UpdateToParameter(CKParameter* Param);
	virtual CKBOOL ChangeSize(CKBOOL Max);
	virtual CKBOOL On_PickResult(CK_ID picked,HWND Control,CKBOOL Clicked);		
	void    FillByType();
	void    FillClassCombo();
	void	EnableShowSetup();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenericObjectParameterDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGenericObjectParameterDialog)
	afx_msg void OnSelchangeCombo();
	afx_msg void OnCheckbool();
	afx_msg void OnChangeGenObjectEdit();
	afx_msg void OnSelchangeGenobjectclasscombo();
	afx_msg void OnShowSetup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERICOBJECTPARAMETERDIALOG_H__C7D34881_A7DD_11D3_B6C8_00902752C68E__INCLUDED_)
