#if !defined(AFX_VICONTROLGLOBAL_H__1482E660_2563_11D3_BAE5_00A0C9CC72C3__INCLUDED_)
#define AFX_VICONTROLGLOBAL_H__1482E660_2563_11D3_BAE5_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VICONTROLGLOBAL.h : header file
//

#ifdef VI_CONTROL_API
#define VI_CONTROL_EXPORT __declspec(dllexport) 
#else
#define VI_CONTROL_EXPORT __declspec(dllimport) 
#endif

VI_CONTROL_EXPORT void InitVIControls();
VI_CONTROL_EXPORT void InitVIControlsForDll();

VI_CONTROL_EXPORT void VICtlSetDefaultFont(CFont *font);
VI_CONTROL_EXPORT CFont *VICtlGetDefaultFont();

VI_CONTROL_EXPORT void VICtlSetDefaultBoldFont(CFont *font);
VI_CONTROL_EXPORT CFont *VICtlGetDefaultBoldFont();

VI_CONTROL_EXPORT void VICtlSetDefaultTextColor(COLORREF clr);
VI_CONTROL_EXPORT COLORREF VICtlGetDefaultTextColor();

VI_CONTROL_EXPORT void VICtlSetDefaultBackColor(COLORREF clr);
VI_CONTROL_EXPORT COLORREF VICtlGetDefaultBackColor();

VI_CONTROL_EXPORT void VICtlSetDefaultEditColor(COLORREF clr);
VI_CONTROL_EXPORT COLORREF VICtlGetDefaultEditColor();

VI_CONTROL_EXPORT void VICtlSetDefaultBorderColor(COLORREF clr);
VI_CONTROL_EXPORT COLORREF VICtlGetDefaultBorderColor();

VI_CONTROL_EXPORT void VICtlSetDefaultBrush(CBrush* clr);
VI_CONTROL_EXPORT CBrush *VICtlGetDefaultBrush();

VI_CONTROL_EXPORT void VICtlSetDefaultEditBrush(CBrush* clr);
VI_CONTROL_EXPORT CBrush *VICtlGetDefaultEditBrush();

VI_CONTROL_EXPORT void VICtlTransparentBlt(HDC dest,int x,int y,int w, int h,
			HDC src,int sx,int sy,COLORREF tc);

VI_CONTROL_EXPORT void VICtlAlphaBlend(HDC dest,int x,int y,int w, int h, HDC src,int sx,int sy, int a);

VI_CONTROL_EXPORT void VICtlModifyFlags(DWORD& flags,DWORD fRemove,DWORD fAdd);

VI_CONTROL_EXPORT HBITMAP VICtlCreateBitmap(int w,int h,int bpp);

//GDI wrapping / managment
VI_CONTROL_EXPORT CFont *GetVIFont(int VIFontIndex);
VI_CONTROL_EXPORT CBrush *GetVIBrush(COLORREF clr);
VI_CONTROL_EXPORT CBrush *GetVIBrush(int VIColorIndex);
VI_CONTROL_EXPORT COLORREF GetVIColor(int VIColorIndex);
VI_CONTROL_EXPORT VIInterfaceData * GetVIInterfaceData();
VI_CONTROL_EXPORT COLORREF SetVIBrush(int VIColorIndex,COLORREF newColor);
VI_CONTROL_EXPORT COLORREF SetVIColor(int VIColorIndex,COLORREF newColor);
//return value : color index
VI_CONTROL_EXPORT int RegisterVIColor(COLORREF clr);
//return value : brush index
VI_CONTROL_EXPORT int RegisterVIBrush(COLORREF clr);
//return value : font index
VI_CONTROL_EXPORT int RegisterVIFont(int nHeight=12,
							int nWidth=5,
							int nEscapement=0,
							int nOrientation=0,
							int nWeight=0,
							BYTE bItalic=0,
							BYTE bUnderline=0,
							BYTE cStrikeOut=0,
							BYTE nCharSet=0,
							BYTE nOutPrecision=OUT_DEFAULT_PRECIS,
							BYTE nClipPrecision=CLIP_DEFAULT_PRECIS,
							BYTE nQuality=DEFAULT_QUALITY,
							BYTE nPitchAndFamily=DEFAULT_PITCH,
							LPCTSTR lpszFacename="Arial");


//Return windows version
typedef enum {
	WVER_WIN311		=	0x00000001,
	WVER_WIN95		=	0x00000002,
	WVER_WIN98		=	0x00000004,
	WVER_WINNT		=	0x00000008,
	WVER_WIN2000	=	0x00000010,
}WVER;
VI_CONTROL_EXPORT int GetWindowVersion();
//Detect window version
VI_CONTROL_EXPORT void DetectWindowVersion();

#endif
