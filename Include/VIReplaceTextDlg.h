#if !defined(AFX_VIREPLACETEXTDLG_H__DB4801F8_4CA4_4747_B6F9_31A85BAC3845__INCLUDED_)
#define AFX_VIREPLACETEXTDLG_H__DB4801F8_4CA4_4747_B6F9_31A85BAC3845__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIReplaceTextDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIReplaceTextDlg dialog

class AFX_EXT_CLASS VIReplaceTextDlg : public VIDialog
{
// Construction
public:
	VIReplaceTextDlg(CWnd* pParent = NULL);   // standard constructor

	BOOL GetFindText(XString &str);
	BOOL GetReplaceText(XString &str);
	BOOL GetMatchCase();
	BOOL GetWholeFile();
	void SetMatchCase(BOOL match);
	void SetWholeFile(BOOL b);
	void SetFindText(XString &str);
	void SetReplaceText(XString &str);
	void SetFullScreenRichEdit(VIRichEdit* edit);


// Dialog Data
	//{{AFX_DATA(VIReplaceTextDlg)
	enum { IDD = IDD_REPLACE };
	VICheckButton	m_wholefile;
	VICheckButton	m_selection;
	VIEdit		m_replace;
	VICheckButton	m_matchcase;
	VIEdit		m_find;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIReplaceTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(VIReplaceTextDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	XString	m_findStr;
	XString	m_replaceStr;
	BOOL	m_match;
	BOOL	m_whole;
	VIRichEdit*	m_fullScreenRichEdit;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIREPLACETEXTDLG_H__DB4801F8_4CA4_4747_B6F9_31A85BAC3845__INCLUDED_)
