#if !defined(AFX_VIFUNCTIONDRAWER_H__69D521A2_71AE_11D3_BA37_00105A669BB5__INCLUDED_)
#define AFX_VIFUNCTIONDRAWER_H__69D521A2_71AE_11D3_BA37_00105A669BB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIFunctionDrawer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIFunctionDrawer window
typedef float (*VIControlFunctionDrawerFct) (float x,void *data);

class AFX_EXT_CLASS VIFunctionDrawer : public CWnd, public VIControl
{
// Construction
public:
	VIFunctionDrawer();
	BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIFunctionDrawer)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIFunctionDrawer();

	void SetFunction(VIControlFunctionDrawerFct fct, void *data = NULL);
	
	VIControlFunctionDrawerFct GetFunction();	
	void *GetFunctionData();
	
	void SetRange(float  xMin,float xMax,float yMin,float yMax);
	void GetRange(float *xMin,float *xMax,float *yMin,float *yMax);

	void ShowHorizontalBar(BOOL show);
	void ShowVerticalBar(BOOL show);

	void SetVerticalBarPosition(float position);
	void SetHorizontalBarPosition(float position);

	void SetVerticalBarColor(COLORREF color);
	void SetHorizontalBarColor(COLORREF color);



protected:
	
	float m_xMin;
	float m_xMax;
	float m_yMin;
	float m_yMax;

	COLORREF m_VBColor;
	COLORREF m_HBColor;

	float m_VBPos;
	float m_HBPos;


	VIControlFunctionDrawerFct m_CalcFct;
	void *m_fctData;

	DWORD m_Flags;

	void DrawHB(CDC *dc,RECT& r, float pos, COLORREF col);
	void DrawVB(CDC *dc,RECT& r, float pos, COLORREF col);

	void DrawCurve(CDC *dc,int minx,int maxx,RECT& r);

	int HBPosFromX(float pos, RECT& r);
	int VBPosFromX(float pos, RECT& r);



	// Generated message map functions
protected:
	//{{AFX_MSG(VIFunctionDrawer)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIFUNCTIONDRAWER_H__69D521A2_71AE_11D3_BA37_00105A669BB5__INCLUDED_)
