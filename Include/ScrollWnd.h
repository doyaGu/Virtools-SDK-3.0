#pragma once

#ifdef CKCONTROLS_API
#define CKCONTROLS_CLASS_DECL  __declspec(dllexport)
#else
#define CKCONTROLS_CLASS_DECL  __declspec(dllimport)
#endif

//ScrollWnd class
//manage scrollbars according to child size
//and manage child position automatically

namespace CKControl	//----------------------------------------
{

class CKCONTROLS_CLASS_DECL ScrollWnd : public CDialog
{
	// Construction
public:
	ScrollWnd();
	virtual ~ScrollWnd();
	
	enum {	NONE			= 0x00000000,
		SCROLLBAR_HORZ	= 0x00000001,
		SCROLLBAR_VERT	= 0x00000002,
		ROUNDED			= 0x00000004,
	}FLAGS;
	
	// Attributes
public:
	void	SetScrollbar(BOOL enable,int sb=SB_BOTH,int max=0,int page=0);
	
	DWORD	GetFlags() {return m_Flags;};
	void	ModifyFlags(DWORD added,DWORD removed=0);
	void	SetBackColor(COLORREF color);
	
protected:
	DWORD		m_Flags;
	COLORREF	m_BackColor;
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GreyCwnd)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	
	// Implementation
	
	// Generated message map functions
protected:
	//{{AFX_MSG(GreyCwnd)
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};	//ScrollWnd class declaration

CKCONTROLS_CLASS_DECL ScrollWnd* CreateScrollWnd(CWnd* parent);

}	//CKControl namespace