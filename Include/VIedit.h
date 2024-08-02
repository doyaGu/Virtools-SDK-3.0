#if !defined(AFX_VIEDIT_H__89F06A80_24BC_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
#define AFX_VIEDIT_H__89F06A80_24BC_11D3_BAE2_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIedit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIEdit window

typedef enum {
	VI_CTRL_EDIT_TEXT			= 0x00000000,
	VI_CTRL_EDIT_UINT			= 0x00000001,
	VI_CTRL_EDIT_INT			= 0x00000002,
	VI_CTRL_EDIT_UFLOAT		= 0x00000004,
	VI_CTRL_EDIT_FLOAT		= 0x00000008,
	VI_CTRL_EDIT_VALUE		= 0x0000000f,
	VI_CTRL_EDIT_NOLINE		= 0x00000010,
	VI_CTRL_EDIT_FRAMERECT	= 0x00000020,
	VI_CTRL_EDIT_NOREDRAW		= 0x00000040,
	VI_CTRL_EDIT_RANGED		= 0x0000f000,
}VI_CTRL_EDIT_FLAGS;



class AFX_EXT_CLASS VIEdit : public CEdit,public VIControl
{
// Construction
public:
	VIEdit();
	void SetRedraw( BOOL bRedraw = TRUE );

	// Sets / Gets the Control Font
	virtual void SetControlFont(CFont *fnt);

	// Gets / Sets the Text in the edit control with an int
	void SetIntValue(int i);
	BOOL GetIntValue(int *i);
	
	// Gets / Sets the Text in the edit control with a float
	void SetFloatValue(float f);
	BOOL GetFloatValue(float *f);
	
	// Gets / Sets the Text in the edit control with a string
	void SetStringValue(char *str);
	void GetStringValue(char *str, int nmax);

	// Sets / Gets the Edit style
	void SetEditStyle(int style) {SetFlags(style);}
	int GetEditStyle() {return GetFlags();}

	// Sets / Gets the integer range	
	void SetIntRange(int nmin,int nmax);
	void GetIntRange(int *nmin,int *nmax);
	
	// Sets / Gets the float range	
	void SetFloatRange(float nmin,float nmax);
	void GetFloatRange(float *nmin,float *nmax);

	// Sets / Gets the float precision
	void SetFloatPrecision(int ip,int fp);
	void GetFloatPrecision(int *ip,int *fp);


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIEdit)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIEdit();
	static int DefaultHeight;
	
	// Generated message map functions
protected:
	//{{AFX_MSG(VIEdit)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	int m_MaxInt;
	int m_MinInt;

	float m_MaxFloat;
	float m_MinFloat;

	// Sets / Gets the float precision
	int m_Ip;
	int m_Fp;

	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEDIT_H__89F06A80_24BC_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
