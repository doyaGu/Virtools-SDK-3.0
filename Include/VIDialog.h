#if !defined(AFX_VIDIALOG_H__4E8F2ADA_9E64_11D3_BA37_00105A669BB5__INCLUDED_)
#define AFX_VIDIALOG_H__4E8F2ADA_9E64_11D3_BA37_00105A669BB5__INCLUDED_


#ifdef VI_CONTROL_API
   #define CLASS_DECL  __declspec(dllexport)
#else
   #define CLASS_DECL  __declspec(dllimport)
#endif



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIDialog dialog
#include "XString.h"

#define IDAPPLY 99

typedef enum VIDLG_FLAG{
	VIDLG_FLAG_ACTIVE				= 0x00000001,		// DEFAULT : window is active
	VIDLG_FLAG_BUTTONSINITIALIZED	= 0x00000002,		// PRIVATE : Buttons have been initialized
	VIDLG_FLAG_SHOWBUTTONOK		= 0x00000004,		// DEFAULT : button ok is shown
	VIDLG_FLAG_SHOWBUTTONAPPLY	= 0x00000008,		// button apply is shown
	VIDLG_FLAG_SHOWBUTTONCANCEL	= 0x00000010,		// DEFAULT : button cancel is shown
	VIDLG_FLAG_INSIDEMARGIN		= 0x00000020,		// DEFAULT : add inside margin
	VIDLG_FLAG_CLOSINGOK			= 0x00000040,		// DEFAULT : ok is a closing dialog button
	VIDLG_FLAG_CLOSINGAPPLY		= 0x00000080,		// apply is a closing dialog button
	VIDLG_FLAG_CLOSINGCANCEL		= 0x00000100,		// DEFAULT : cancel is a closing dialog button
	VIDLG_FLAG_CHILD				= 0x00000200,		// not a popup, not ncpaint nor erasebkground will be called
	VIDLG_FLAG_NOREDRAW			= 0x00000400,		// if flag set, then anything is drawn
	VIDLG_FLAG_ROUNDBORDER		= 0x00000800,		// DEFAULT if flag set, border rounded (default for dialog)
	VIDLG_FLAG_ROUNDINSIDEBORDER	= 0x00001000,		// DEFAULT if flag set, inside border rounded (default for dialog)
	VIDLG_FLAG_KEYBOARDSHORTCUTS	= 0x00002000,		// if flag set, first letter of buttons are taken as shortcuts

	VIDLG_FLAG_USER1				= 0x10000000,		// user flag 1
	VIDLG_FLAG_USER2				= 0x20000000,		// user flag 2
	VIDLG_FLAG_USER3				= 0x40000000,		// user flag 3
	VIDLG_FLAG_USER4				= 0x80000000,		// user flag 4
} VIDLG_FLAG;

typedef enum BUTTONPOSITION{
	BPOS_LEFT			= 0x00000001,
	BPOS_MIDDLE			= 0x00000002,
	BPOS_RIGHT			= 0x00000004,
	BPOS_POSITIONFLAG	= 0x00000007,
	BPOS_AUTO			= 0x00000008,
	BPOS_LEFTALIGNED	= 0x00000010,
	BPOS_CENTERED		= 0x00000020,
	BPOS_RIGHTALIGNED	= 0x00000040,
	BPOS_JUSTIFIED		= 0x00000080,
	BPOS_ALIGNEMENTFLAG	= 0x000000f0,
}BUTTONPOSITION;

class CLASS_DECL VIDialog : public CDialog,public VIControl
{
// Construction
public:

	// standard constructors
	VIDialog();
	VIDialog(UINT nIDTemplate,CWnd* pParent = NULL);
	VIDialog(LPCTSTR lpszTemplateName,CWnd* pParent =NULL);

	//place window in screen if not fully in screen
	void PlaceInWorkArea(BOOL redraw=TRUE);
	//set custom button names.
	//if a name is null, then the button will be hidden
	void SetCustomButtons(char * ok=NULL,char * apply=NULL,char * cancel=NULL);
	//set custom buttons position 0 <=> left, 1 <=> middle, 2<=> right)
	void SetCustomButtonPositions(
		int okpos=BPOS_AUTO|BPOS_RIGHTALIGNED,
		int applypos=BPOS_AUTO|BPOS_RIGHTALIGNED,
		int cancelpos=BPOS_AUTO|BPOS_RIGHTALIGNED);
	//show custom buttons
	void ShowCustomButtons(BOOL ok=TRUE,BOOL apply=FALSE,BOOL cancel=TRUE);

	//prevent button ok or cancel from leaving , or make middle button close the window
	void SetClosingButtons(BOOL ok=TRUE,BOOL apply=FALSE,BOOL cancel=TRUE);

//FLAGS
	//modify dialog flags
	//return value : final current flags
	DWORD ModifyVIDlgFlags(int added,int removed=0);
	//get flags
	DWORD GetVIDlgFlags();
	//set flags
	//return value : previous flags
	DWORD SetVIDlgFlags(int flags);
	//specified flags are set to value
	//return value : final current flags
	DWORD SetVIDlgFlagsValue(int flags,BOOL value);
	//return True if flags is set. Can use combination of flags.
	BOOL  IsVIDlgFlagSet(int flags);

//COLORS
	COLORREF GetBackColor();
	COLORREF GetInsideBackColor();
	COLORREF GetBorderColor();
	COLORREF GetTitleColor();
	COLORREF GetTitleBackColor();
	void SetBackColor(COLORREF c);
	void SetInsideBackColor(COLORREF c);
	void SetBorderColor(COLORREF c);
	void SetTitleColor(COLORREF c);
	void SetTitleBackColor(COLORREF c);

	//width & height of the ellipse used to draw the rounded corners 
	void SetRoundRect(POINT p);
	void SetRoundRect(int w,int h);

// Implementation
protected:
	//overridden window proc
	virtual LRESULT WindowProc( UINT message, WPARAM wParam, LPARAM lParam );
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//init vars
	void Init();
	//init dialog callback.  Not called by framework, shall be called manually
	//creates custom buttons (ok, apply, cancel)
	//Return value : TRUE if successfull
	BOOL DoInitDialog();
	//ncpaint callback. Not called by framework, shall be called manually
	void DoNcPaint( );
	//ctlcolor callback. Not called by framework, shall be called manually
	//Return value : the value that should be returned by the window proc
	LRESULT DoCtlColor(HDC hdc,int item);
	//erase background callback. Not called by framework, shall be called manually
	//Return value : the value that should be returned by the window proc
	LRESULT DoEraseBackground(HDC hdc);


	//rect must be 0,0,width,height, and all sub child
	//check this rect, and check if all child windows are in that rect
	//then offset all child windows rects
	//and adjust window rect of dialog
	//and place custom buttons
	//Then redraw all
	// Note : r is modified and contains the dialog window rect after that
	//return value :  TRUE if successfull
	BOOL AdjustWindows(RECT * r,BOOL redraw,BOOL offsetWindows=TRUE);
	//Return value : min client width, (wnd client width minus margins that
	//must be at least able to contains all custom buttons
	int GetMinClientWidth();
	//return client rect in which u should move ur child windows
	//margins are taken into account
	void GetVIDialogClientRect(RECT * r);
	//update custom buttons position according to current window size ()
	//Note : func called in AdjustWindows
	void UpdateButtonPositions(BOOL redraw);
	//update custom buttons name
	void UpdateButtonNames();

//DATA
protected:
	//interface data, that is, margins and other vars that should be taken into account
	//initialized in Init function
	VIInterfaceData*	m_interfaceData;
	//flags. Show/hide flags for custom button.
	DWORD		m_flags;

	//ok button (id = IDOK)
	VIDialogButton	m_ok;
	//apply button (id = IDAPPLY)
	VIDialogButton	m_cancel;
	//cancel button (id = IDCANCEL)
	VIDialogButton	m_apply;

	//ok button str
	XString		m_okStr;
	//apply button str
	XString		m_applyStr;
	//cancel button str
	XString		m_cancelStr;

	//ok button position
	int m_okpos;
	//apply button position
	int m_applypos;
	//cancel button position
	int m_cancelpos;

	COLORREF	m_backColor;
	COLORREF	m_insideBackColor;
	COLORREF	m_borderColor;
	COLORREF	m_titleColor;
	COLORREF	m_titleBackColor;
	POINT		m_RoundRect;		//width & height of the ellipse used to draw the rounded corners 

private:

	//return border size
	POINT GetBorderSize();

	//get caption height
	int GetCaptionHeight();

	//returns the buttons size by using CDC::GetTextExtents if possible
	void GetButtonSizes(CSize &oks,CSize &applys,CSize &cancels);

	//test if button positions are different and valid
	void TestCustomButtonPositions();

protected:
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDIALOG_H__4E8F2ADA_9E64_11D3_BA37_00105A669BB5__INCLUDED_)
