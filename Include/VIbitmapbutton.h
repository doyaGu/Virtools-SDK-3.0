#if !defined(AFX_VIBITMAPBUTTON_H__EDBA2E76_24C3_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
#define AFX_VIBITMAPBUTTON_H__EDBA2E76_24C3_11D3_BAE2_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIbitmapbutton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIBitmapButton window
#define NMBB_PUSHED 0x00000001
#define NMBB_DBLCLK 0x00000002

class AFX_EXT_CLASS VIBitmapButton : public VIButton
{
// Construction
public:
	VIBitmapButton();
	void DrawItem(LPDRAWITEMSTRUCT dis);
	BOOL IsPushed();
	void SetPushed(BOOL b);

	// Sets / Get the color used as transparent color 
	COLORREF GetTransparentColor();
	void SetTransparentColor(COLORREF clr);
	
	// sets the Bitmaps used to draw the different button states
	void SetBitmaps(CBitmap *Normal,CBitmap *NormalHighlighted,
		CBitmap *Pushed,
		CBitmap *PushedHighlighted,
		CBitmap *Disabled,BOOL ReleaseBitmaps = TRUE);

	// sets the Bitmaps used to draw the different button states
	void SetBitmaps(UINT iNormal,UINT iNormalHighlighted,
		UINT iPushed,UINT iPushedHighlighted,UINT iDisabled);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIBitmapButton)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIBitmapButton();
	

	// Generated message map functions
protected:
	//{{AFX_MSG(VIBitmapButton)
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	CBitmap *m_NormalBitmap;
	CBitmap *m_NormalHighlightedBitmap;
	CBitmap *m_PushedBitmap;
	CBitmap *m_PushedHighlightedBitmap;
	CBitmap *m_DisabledBitmap;
	
	COLORREF m_TransparentColor;

	BOOL m_ReleaseBitmaps;
	void ReleaseBitmaps();
	void SizeToBitmap();

	DWORD m_flags;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIBITMAPBUTTON_H__EDBA2E76_24C3_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
