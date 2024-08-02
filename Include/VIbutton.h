#if !defined(AFX_VIBUTTON_H__003EC641_392A_11D3_8BB4_00105A669BB5__INCLUDED_)
#define AFX_VIBUTTON_H__003EC641_392A_11D3_8BB4_00105A669BB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIbutton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIButton window

class AFX_EXT_CLASS VIButton : public CButton,public VIControl
{
// Construction
public:

	VIButton();
	void DrawItem(LPDRAWITEMSTRUCT);

	virtual COLORREF GetPushTextColor();
	virtual COLORREF GetPushBackColor();
	virtual COLORREF GetPushBorderColor();
	virtual COLORREF GetPushRollOverTextColor();
	virtual COLORREF GetPushRollOverBackColor();
	virtual COLORREF GetPushRollOverBorderColor();
	virtual COLORREF GetDisabledTextColor();
	virtual COLORREF GetDisabledBackColor();
	virtual COLORREF GetDisabledBorderColor();
	virtual COLORREF GetFocusTextColor();
	virtual COLORREF GetFocusBackColor();
	virtual COLORREF GetFocusBorderColor();
	virtual COLORREF GetRollOverTextColor();
	virtual COLORREF GetRollOverBackColor();
	virtual COLORREF GetRollOverBorderColor();
	virtual COLORREF GetNormalTextColor();
	virtual COLORREF GetNormalBackColor();
	virtual COLORREF GetNormalBorderColor();

// Attributes
public:
	enum {
		VI_CTRL_DRAWPREFIX				=	0x00000010,	//& is used as a prefix caracter and following letter is underlined
		}VI_CTRL_BUTTON_FLAGS;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIButton)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(VIButton)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	UINT m_Timer;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIBUTTON_H__003EC641_392A_11D3_8BB4_00105A669BB5__INCLUDED_)
