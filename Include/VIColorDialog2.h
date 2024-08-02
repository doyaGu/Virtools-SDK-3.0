#if !defined(AFX_VICOLORDIALOG2_H__6257AE21_B308_11D3_B6C8_00902752C68E__INCLUDED_)
#define AFX_VICOLORDIALOG2_H__6257AE21_B308_11D3_B6C8_00902752C68E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIColorDialog.h : header file
//

#define PREDEFINEDCOLORCOUNT 39

class AFX_EXT_CLASS VIColorDialog2 : public VIColorDialog
{
public:

	VIColorDialog2(CWnd* pParent = NULL);						// standard constructor
	VIColorDialog2(UINT nIDTemplate,CWnd* pParent = NULL);	//for derived class

	COLORREF	m_colors[PREDEFINEDCOLORCOUNT];
	COLORREF	m_colorsSaved[PREDEFINEDCOLORCOUNT];
	VIStaticRectangle	m_c[PREDEFINEDCOLORCOUNT];

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDialog();

	virtual void SetCurrentColorHLS(float H,float L,float S);

	BOOL Create(CWnd* pParentWnd = NULL,UINT nIDTemplate = NULL);

	BOOL LoadColors();
	BOOL SaveColors();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	int m_previousSelectedColorIndex;

	DECLARE_MESSAGE_MAP()
};

#endif