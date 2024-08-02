#ifndef __TOOLBARBUTTON_H_
#define __TOOLBARBUTTON_H_


// VItoolbarbutton.h : header file

/////////////////////////////////////////////////////////////////////////////
// VIToolbarButton window

class AFX_EXT_CLASS VIToolbarButton : public VIButton
{
public:
	VIToolbarButton();

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