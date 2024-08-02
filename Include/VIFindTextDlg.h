#if !defined(AFX_VIFINDTEXTDLG_H__F3A960A4_2ECD_42D9_9650_989C49327FE0__INCLUDED_)
#define AFX_VIFINDTEXTDLG_H__F3A960A4_2ECD_42D9_9650_989C49327FE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIFindTextDlg.h : header file
//

class VIRichEdit;
/////////////////////////////////////////////////////////////////////////////
// VIFindTextDlg dialog
class AFX_EXT_CLASS VIFindTextDlg : public VIDialog
{
// Construction
public:
	VIFindTextDlg(CWnd* pParent = NULL);   // standard constructor

	BOOL GetFindText(XString &str);
	BOOL GetMatchCase();
	BOOL GetDirection();
	void SetMatchCase(BOOL match);
	void SetDirection(BOOL backward);
	void SetFindText(XString &str);
	void SetFullScreenRichEdit(VIRichEdit* edit);

// Dialog Data
	//{{AFX_DATA(VIFindTextDlg)
	enum { IDD = IDD_FIND };
	VICheckButton	m_down;
	VICheckButton	m_up;
	VICheckButton	m_matchcase;
	VIEdit		m_find;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIFindTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(VIFindTextDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	XString	m_findStr;
	BOOL	m_match;
	BOOL	m_back;
	VIRichEdit*	m_fullScreenRichEdit;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIFINDTEXTDLG_H__F3A960A4_2ECD_42D9_9650_989C49327FE0__INCLUDED_)
