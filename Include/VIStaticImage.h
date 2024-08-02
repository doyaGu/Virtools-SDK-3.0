#if !defined(AFX_VIStaticImage_H__C97F2521_A0C9_11D3_BA37_00105A669BB5__INCLUDED_)
#define AFX_VIStaticImage_H__C97F2521_A0C9_11D3_BA37_00105A669BB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIStaticImage.h : header file
//

#include "VxMath.h"

#define VI_STATICIMAGE_ZOOMIN			1
#define VI_STATICIMAGE_ZOOMOUT		2
#define VI_STATICIMAGE_ZOOMONEONE		3
#define VI_STATICIMAGE_ZOOMBEST		4
#define VI_STATICIMAGE_ZOOMUPDATE		5


typedef BOOL (*VI_STATICIMAGE_POSTCALLBACK)(HBITMAP bitmap,void* arg);


/////////////////////////////////////////////////////////////////////////////
// VIStaticImage window
class AFX_EXT_CLASS VIStaticImage : public CWnd, public VIControl
{
// Construction
public:
	VIStaticImage();

	void		SetAlphaControl(VIStaticImage* alpha);
	void		SetAttachedControl(VIStaticImage* control);

	void		SetImage(const VxImageDescEx& desc, CKObject *ckObject);
	void		SetBorder(BOOL Border);
	BOOL		ManageZoom(char op);
	void		SetZoom(float zoom);
	float		GetZoom();
	void		CalculateBestFit();
	COLORREF	GetPixelColor(int x,int y);
	BOOL		CanDo(int op);
	BOOL		IsInImage(int x,int y);
	void		ToClient(RECT& rect);

	BOOL		Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	void		InitializeBitmap();

	void		SetPostCallback(VI_STATICIMAGE_POSTCALLBACK Function,void* Argument);
	void		GetConvertValuesFromMask(DWORD mask,int& shift,int& bytepos,int& multoalign);

	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIStaticImage)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIStaticImage();
	// Generated message map functions

protected:
	//{{AFX_MSG(VIStaticImage)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	void UpdateBitmapInfo();
	void RecenterBitmapInfo();
	void CopySettingsToAttached();
	
	void CheckImageDesc();


	HBITMAP				m_Bitmap;
	BITMAP				m_BitmapInfo;


	// may be an alpha channel or the source image if this is the alpha
	VIStaticImage*	m_AttachedImage;
	BOOL				m_IsAlpha;

		
	VxImageDescEx		m_ImageDesc;
	void*				m_SurfPtr;
	BOOL				m_Border;

	float				m_Zoom;

	int					m_DestPosX,m_DestPosY,m_DestSizeX,m_DestSizeY,m_DestWidth,m_DestHeight;
	int					m_SrcPosX,m_SrcPosY,m_SrcSizeX,m_SrcSizeY;
	int					m_SrcWidth,m_SrcHeight;
	int					m_SrcBitsPerPixel,m_SrcBytesPerLine,m_SrcBytesPerPixel;

	int					m_NbZoomValues;
	float				*m_ZoomValue;

	VI_STATICIMAGE_POSTCALLBACK m_Callback;
	void*				m_Argument;

	CKObject			*m_ckObject;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIStaticImage_H__C97F2521_A0C9_11D3_BA37_00105A669BB5__INCLUDED_)
