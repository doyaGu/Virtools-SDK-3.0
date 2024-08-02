#if !defined(AFX_VICOLORDIALOG_H__6257AE21_B308_11D3_B6C8_00902752C68E__INCLUDED_)
#define AFX_VICOLORDIALOG_H__6257AE21_B308_11D3_B6C8_00902752C68E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIColorDialog.h : header file
//

#include "VIEdit.h"
#include "VIButton.h"
#include "VIStaticText.h"
#include "VIStaticRectangle.h"


/////////////////////////////////////////////////////////////////////////////
// VIColorDialog dialog

class AFX_EXT_CLASS VIColorDialog : public VIDialog
{
// Construction
public:
	VIColorDialog(CWnd* pParent = NULL);   // standard constructor
	VIColorDialog(UINT nIDTemplate,CWnd* pParent = NULL);	//for derived class
	virtual ~VIColorDialog();
	BOOL Create(CWnd* pParentWnd = NULL,UINT nIDTemplate = NULL);


	virtual void SetStartColor(float R,float G,float B,float A=1.0f);
	virtual void SetCurrentColorHLS(float H,float L,float S);
	virtual void SetCurrentColor(float R,float G,float B,float A=1.0f);

	

	DWORD GetCurrentColor();
	void  GetStartColor(float& R,float& G,float& B);
	void  GetStartColor(float& R,float& G,float& B,float& _A);

	void GetCurrentColor(float& R,float& G,float& B);
	void GetCurrentColor(float& R,float& G,float& B,float& A);
	void GetCurrentColorHLS(float& H,float& L,float& S);


	void ShowAlpha(BOOL Show=TRUE);

// Dialog Data
	//{{AFX_DATA(VIColorDialog)
	CStatic	m_GradientWin;
	CStatic	m_HueBar;
	CStatic	m_AlphaBar;
	CStatic	m_OldColorBar;
	CStatic	m_NewColorBar;

	VIStaticRectangle	m_MainRect;

	VIStaticText	m_StaticAlpha;
	VIStaticText	m_StaticL;
	VIStaticText	m_StaticS;
	VIStaticText	m_StaticR;
	VIStaticText	m_StaticH;
	VIStaticText	m_StaticG;
	VIStaticText	m_StaticB;
	VISlider	m_SliderS;
	VISlider	m_SliderR;
	VISlider	m_SliderL;
	VISlider	m_SliderH;
	VISlider	m_SliderG;
	VISlider	m_SliderB;
	VIEdit	m_EditS;
	VIEdit	m_EditR;
	VIEdit	m_EditL;
	VIEdit	m_EditH;
	VIEdit	m_EditG;
	VIEdit	m_EditB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIColorDialog)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	float H,S,L;
	float R,G,B,A;
	float exH,exS,exL;
	float exR,exG,exB,exA;
	float sR,sG,sB,sA;	
	BOOL  Modal;
	BOOL  ShowA;
	BOOL  InUpdate;
	CWnd* StartingView;	// Window from which a pick operation has began
	CWnd* FromControl;	// Edit box which has been modify

	int	m_dialogResource;	//index of resource (IDD_XXX)

	void RedrawGradient();
	void RedrawHueBar();
	void RedrawColor();
	void RedrawOldColor();
	void RedrawAlphaBar();
	
	void StoreCurrent();
	void CheckIfChanges(BOOL Force = FALSE);

	CBrush DarkGreyBrush;
	CBrush BlackBrush;
	// Generated message map functions
	//{{AFX_MSG(VIColorDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditb();
	afx_msg void OnChangeEditg();
	afx_msg void OnChangeEdith();
	afx_msg void OnChangeEditl();
	afx_msg void OnChangeEditr();
	afx_msg void OnChangeEdits();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VICOLORDIALOG_H__6257AE21_B308_11D3_B6C8_00902752C68E__INCLUDED_)
