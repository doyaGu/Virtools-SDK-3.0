#if !defined(AFX_VILED_H__5C3BBF81_2E2A_11D3_8BB4_00105A669BB5__INCLUDED_)
#define AFX_VILED_H__5C3BBF81_2E2A_11D3_8BB4_00105A669BB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VILed.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VILed window

class AFX_EXT_CLASS VILed : public VIBitmapButton
{
// Construction
public:
	VILed();

	virtual void SetCheck(BOOL check);

	// Time it takes for the led to fade completly in milliseconds
	int GetFadeTime();
	void SetFadeTime(int t);

	// How Many steps (drawings) should be performed, ie a drawing occurs each m_FadeTime / m_FadeSteps ms
	int GetFadeSteps();
	void SetFadeSteps(int s);


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VILed)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VILed();

	// Generated message map functions
protected:
	//{{AFX_MSG(VILed)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int m_BlendFactor;
	DWORD m_Timer;

	int m_FadeTime;
	int m_FadeSteps;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VILED_H__5C3BBF81_2E2A_11D3_8BB4_00105A669BB5__INCLUDED_)
