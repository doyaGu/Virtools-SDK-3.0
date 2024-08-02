#ifndef __DialogButton_H_
#define __DialogButton_H_


// VIDialogButton.h : header file

/////////////////////////////////////////////////////////////////////////////
// VIDialogButton window

class AFX_EXT_CLASS VIDialogButton : public VIButton
{
public:
	VIDialogButton();

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
};

#endif