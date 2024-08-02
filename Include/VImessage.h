#if !defined(AFX_VIMESSAGE_H__9E2695E0_357D_11D4_A3C9_00105AA2BBF3__INCLUDED_)
#define AFX_VIMESSAGE_H__9E2695E0_357D_11D4_A3C9_00105AA2BBF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIMessage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIMessage dialog
#ifndef VIMESSAGE_ENUMS
typedef enum {NMM_OKCANCEL=0,NMM_YESNO=1,NMM_OKAPPLYCANCEL=2,NMM_OK=3,NMM_YESNOCANCEL=4,NMM_CUSTOM=5}VIMESSAGE_MODE;
typedef enum {NMI_NONE=0,NMI_VI=1,NMI_QUESTION=2,NMI_STOP=3,NMI_EXCLAMATION=4,NMI_ERROR=5,NMI_WARNING=6}VIMESSAGE_ICON;
typedef enum {NMALIGN_LEFT=0,NMALIGN_RIGHT=1,NMALIGN_CENTERED=2,NMALIGN_JUSTIFIED=3}VIMESSAGE_ALIGNEMENT;
#endif


class VIMessage : public VIDialog
{
// Construction
public:
	VIMessage(CWnd* pParent = NULL);   // standard constructor
	VIMessage(char * text,char * title=NULL,VIMESSAGE_MODE mode=NMM_OK,VIMESSAGE_ICON icon=NMI_NONE,CWnd* pParent = NULL);   // standard constructor
	VIMessage(char * text,VIMESSAGE_MODE mode,VIMESSAGE_ICON icon=NMI_NONE,CWnd* pParent = NULL);   // standard constructor
	void SetTitle(char * title);
	void SetText(char * text);
	void SetIcon(VIMESSAGE_ICON icon);
	void SetMode(VIMESSAGE_MODE mode);
	void SetAlignement(VIMESSAGE_ALIGNEMENT align);

private:
	void InitData();
	void UpdateMode();
	void UpdateSize();
	LRESULT DoEraseBackground(HDC hdc);

	XString				m_text;
	XString				m_title;
	VIMESSAGE_ICON	m_iconType;
	VIMESSAGE_MODE	m_mode;
	VIMESSAGE_ALIGNEMENT	m_alignement;
	int					m_textMargin;
	int					m_textYOffset;


// Dialog Data
	//{{AFX_DATA(VIMessage)
	enum { IDD = IDD_VIMESSAGE };
	CStatic		m_icon;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIMessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(VIMessage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIMESSAGE_H__9E2695E0_357D_11D4_A3C9_00105AA2BBF3__INCLUDED_)
