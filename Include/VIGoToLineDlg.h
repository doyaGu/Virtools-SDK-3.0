#pragma once

// GoToLineDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GoToLineDlg dialog
class VIRichEdit;
class AFX_EXT_CLASS VIGoToLineDlg : public VIDialog
{
// Construction
public:
	VIGoToLineDlg(CWnd* pParent = NULL);   // standard constructor

	void SetFullScreenRichEdit(VIRichEdit* edit);
// Dialog Data
	//{{AFX_DATA(GoToLineDlg)
	enum { IDD = IDD_GOTOLINE };
	CString	m_value;
	VIEdit	m_valueEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GoToLineDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

protected:
	VIRichEdit*	m_fullScreenRichEdit;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GoToLineDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
