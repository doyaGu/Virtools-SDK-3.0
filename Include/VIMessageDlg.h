#pragma once

// VIMessageDlg.h : header file
//

class AFX_EXT_CLASS VIMessageDlg : public VIDialog
{
// Construction
public:

enum VIM_MODE{
	VIMM_OKCANCEL			,
	VIMM_YESNO				,
	VIMM_OKAPPLYCANCEL		,
	VIMM_OK					,
	VIMM_YESNOCANCEL		,
	VIMM_CUSTOM				,
};

enum VIM_ICON{
	VIMI_NONE				,
	VIMI_NEMO				,
	VIMI_QUESTION			,
	VIMI_STOP				,
	VIMI_EXCLAMATION		,
	VIMI_ERROR				,
	VIMI_WARNING			,
};

enum VIM_ALIGNEMENT{
	VIMA_LEFT			,
	VIMA_RIGHT			,
	VIMA_CENTERED		,
	VIMA_JUSTIFIED		,
};

	VIMessageDlg(CWnd* pParent = NULL);   // standard constructor
	VIMessageDlg(char * text,char * title=NULL,VIM_MODE mode=VIMM_OK,VIM_ICON icon=VIMI_NONE,CWnd* pParent = NULL);   // standard constructor
	VIMessageDlg(char * text,VIM_MODE mode,VIM_ICON icon=VIMI_NONE,CWnd* pParent = NULL);   // standard constructor
	BOOL Create(CWnd* pParentWnd = NULL);
	void SetTitle(char * title);
	void SetText(char * text);
	void SetIcon(VIM_ICON icon);
	void SetMode(VIM_MODE mode);
	void SetAlignement(VIM_ALIGNEMENT align);

private:
	void InitData();
	void UpdateMode();
	void UpdateSize();
	LRESULT DoEraseBackground(HDC hdc);

	XString				m_text;
	XString				m_title;
	VIM_ICON			m_iconType;
	VIM_MODE			m_mode;
	VIM_ALIGNEMENT		m_alignement;
	int					m_textMargin;
	int					m_textYOffset;
	BOOL				m_Modal;

	CStatic		m_icon;

public:
	virtual int DoModal();
/*
// Dialog Data
	//{{AFX_DATA(VIMessageDlg)
	enum { IDD = IDD_VIMESSAGE };
	//}}AFX_DATA
*/

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIMessageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(VIMessageDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

int AFX_EXT_CLASS VIMessageBox(CWnd* pParent);
int AFX_EXT_CLASS VIMessageBox(char * text,char * title,VIMessageDlg::VIM_MODE mode=VIMessageDlg::VIMM_OK,VIMessageDlg::VIM_ICON icon=VIMessageDlg::VIMI_NONE,CWnd* pParent=NULL);
int AFX_EXT_CLASS VIMessageBox(char * text,VIMessageDlg::VIM_MODE mode=VIMessageDlg::VIMM_OK,VIMessageDlg::VIM_ICON icon=VIMessageDlg::VIMI_NONE,CWnd* pParent=NULL);
