// VIControl.h: interface for the VIControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VICONTROL_H__FB400450_24BD_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
#define AFX_VICONTROL_H__FB400450_24BD_11D3_BAE2_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS VIControl  
{
public:
	VIControl();
	virtual ~VIControl();

	// Sets / Gets the Control Text Color
	virtual void SetTextColor(COLORREF clr);
	virtual COLORREF GetTextColor();

	// Sets / Gets the Control Back Color
	virtual void SetBackColor(COLORREF clr);
	virtual COLORREF GetBackColor();

	// Sets / Gets the Control Back Color
	virtual void SetEditColor(COLORREF clr);
	virtual COLORREF GetEditColor();

	// Sets / Gets the Controls Brush
	virtual CBrush *GetControlBrush();
	virtual void SetControlBrush(CBrush *br);

	// Sets / Gets the Edit Brush
	virtual CBrush *GetEditBrush();
	virtual void SetEditBrush(CBrush *br);

	// Sets / Gets the Control Border color
	virtual void SetBorderColor(COLORREF clr);
	virtual COLORREF GetBorderColor();

	// Sets / Gets the Control Font
	virtual CFont *GetControlFont();
	virtual void SetControlFont(CFont *fnt);

	//set colors
	virtual void SetColors(COLORREF textColor,COLORREF backColor,COLORREF editColor,COLORREF borderColor,CBrush * editBrush,CBrush * controlBrush);

	//flags access
	DWORD GetFlags(){return m_CtrlFlags;}
	void SetFlags(DWORD f) {m_CtrlFlags=f;}
	void ModifyFlags(DWORD added=0,DWORD removed=0) {m_CtrlFlags&=~removed;m_CtrlFlags|=added;}

protected :
	COLORREF m_TextColor;
	COLORREF m_BackColor;
	COLORREF m_EditColor;
	COLORREF m_BorderColor;

	CBrush *m_Brush;
	CBrush *m_EditBrush;
	CFont *m_Font;

	DWORD m_CtrlFlags;

};

#endif // !defined(AFX_VICONTROL_H__FB400450_24BD_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
