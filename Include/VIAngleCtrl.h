#if !defined(AFX_VIANGLECTRL_H__1482E660_2563_11D3_BAE5_00A0C9CC72C3__INCLUDED_)
#define AFX_VIANGLECTRL_H__1482E660_2563_11D3_BAE5_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIAngleCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIAngleCtrl window

class AFX_EXT_CLASS VIAngleCtrl : public CWnd, public VIControl
{
// Construction
public:
	VIAngleCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIAngleCtrl)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIAngleCtrl();
	BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );

	
	// Gets / Sets the Angle in radians
	void SetAngle(float angle);
	float GetAngle();

	// Sets the minimum and maximum angle accepted 
	void SetRange(float amin,float amax);

	// Sets the use of min and max value on or off
	void UseRange(BOOL b);

	// Generated message map functions
protected:
	//{{AFX_MSG(VIAngleCtrl)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg long OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

	void  DrawSpins();
	void  DrawAngle();
	void  DrawCircle(CDC *dc);
	void  RedrawEdits();
	void  CreateEdits();


	float m_Angle;
	float m_Spins;

	float m_MaxAngle;
	float m_MinAngle;

	BOOL m_UseRange;
	
	VIStaticText	m_StaticTurn;
	VIStaticText	m_StaticDegree;
	VIEdit m_SpinCount;
	VIEdit m_AngleCount;
	RECT m_CircleRect;
	BOOL m_bDragOn;	

	int m_Direction;
	BOOL m_bSkipENUPDATE;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIANGLECTRL_H__1482E660_2563_11D3_BAE5_00A0C9CC72C3__INCLUDED_)
