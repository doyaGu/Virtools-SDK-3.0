// CUIKGDIManager.h: interface for the CUIKFontManager class.
//////////////////////////////////////////////////////////////////////

#ifndef _VICONTROLGDIMANAGER_H_
#define _VICONTROLGDIMANAGER_H_

#include "XArray.h"






//GDI defines
#define VIFONT_NORMAL				0
#define VIFONT_BOLD				1
#define VIFONT_BOLDUNDERLINED		2
#define VIFONT_ITALIC				3
#define VIFONT_UNDERLINED			4
#define VIFONT_ITALICUNDERLINED	5
#define VIFONT_BIGUNDERLINED		6
#define VIFONT_SMALL				7

/*
#define COLOR_WHITE				"color_white"
#define COLOR_WHITEGREY			"color_whitegrey"
#define COLOR_LTLTGREY			"color_ltltgrey"
#define COLOR_LTGREY			"color_ltgrey"
#define COLOR_MEDGREY			"color_medgrey"
#define COLOR_DKGREY			"color_dkgrey"
#define COLOR_GREY				"color_grey"
#define COLOR_BLACKGREY			"color_blackgrey"
#define COLOR_LTLTBLACK			"color_ltltblack"
#define COLOR_LTBLACK			"color_ltblack"
#define COLOR_BLACK				"color_black"
#define COLOR_RED				"color_red"
#define COLOR_HALFRED			"color_halfred"
#define COLOR_DYN				"color_dynamic"
#define COLOR_DYNGRAYED			"color_dynamic_grayed"
#define COLOR_DYNSELECT			"color_dynamic_selected"
*/

/*
#define VICOLOR_WHITE				0
#define VICOLOR_WHITEGREY			1
#define VICOLOR_LTLTGREY			2
#define VICOLOR_LTGREY			3
#define VICOLOR_MEDGREY			4
#define VICOLOR_DKGREY			5
#define VICOLOR_GREY				6
#define VICOLOR_BLACKGREY			7
#define VICOLOR_LTLTBLACK			8
#define VICOLOR_LTBLACK			9
#define VICOLOR_BLACK				10
#define VICOLOR_RED				11
#define VICOLOR_HALFRED			12
#define VICOLOR_DYN				13
#define VICOLOR_DYNGRAYED			14
#define VICOLOR_DYNSELECT			15
*/

/*
color_white				= 255 255 255
color_whitegrey			= 225 225 225
color_ltltgrey			= 200 200 200
color_ltgrey			= 176 176 176
color_medgrey			= 152 152 152
color_dkgrey			= 128 128 128
color_grey				= 96 96 96
color_blackgrey			= 75 75 75
color_ltltblack			= 64 64 64
color_ltblack			= 32 32 32
color_black				= 0 0 0
color_red				= 255 0 0
color_halfred			= 128 0 0
color_dynamic			= 207 169 169
color_dynamic_grayed	= 212 190 190
color_dynamic_selected	= 173 109 109
*/

#define VICOLOR_BLACK				0
#define VICOLOR_51					1
#define VICOLOR_65					2
#define VICOLOR_100					3
#define VICOLOR_128					4
#define VICOLOR_152					5
#define VICOLOR_176					6
#define VICOLOR_200					7
#define VICOLOR_230					8
#define VICOLOR_WHITE				9
#define VICOLOR_RED					10
#define VICOLOR_HALFRED				11
#define VICOLOR_DYN					12
#define VICOLOR_DYNGRAYED			13
#define VICOLOR_DYNSELECT			14

#define VICOLOR_COUNT				15

#ifdef VI_CONTROL_API
	#define VI_CONTROL_EXPORT __declspec(dllexport)
#else
	#define VI_CONTROL_EXPORT __declspec(dllimport)
#endif


VI_CONTROL_EXPORT extern int ZC_MENUBACK;										
VI_CONTROL_EXPORT extern int ZC_MENUBORDER;				
VI_CONTROL_EXPORT extern int ZC_MENUTEXT;					

VI_CONTROL_EXPORT extern int ZC_MAINBACK;					

VI_CONTROL_EXPORT extern int ZC_CONTROLBACK;									
VI_CONTROL_EXPORT extern int ZC_CONTROLBORDER;				
VI_CONTROL_EXPORT extern int ZC_CONTROLTEXT;				

VI_CONTROL_EXPORT extern int ZC_CONTROLBACKSELECT;							
VI_CONTROL_EXPORT extern int ZC_CONTROLBORDERSELECT;		
VI_CONTROL_EXPORT extern int ZC_CONTROLTEXTSELECT;			
VI_CONTROL_EXPORT extern int ZC_CONTROLBACKFOCUS;								
VI_CONTROL_EXPORT extern int ZC_CONTROLBORDERFOCUS;		
VI_CONTROL_EXPORT extern int ZC_CONTROLTEXTFOCUS;			

//buttons
VI_CONTROL_EXPORT extern int ZC_N_BUTTONBACK;					
VI_CONTROL_EXPORT extern int ZC_N_BUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_N_BUTTONBORDER;			
VI_CONTROL_EXPORT extern int ZC_P_BUTTONBACK;				
VI_CONTROL_EXPORT extern int ZC_P_BUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_P_BUTTONBORDER;			
VI_CONTROL_EXPORT extern int ZC_F_BUTTONBACK;				
VI_CONTROL_EXPORT extern int ZC_F_BUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_F_BUTTONBORDER;			
VI_CONTROL_EXPORT extern int ZC_NR_BUTTONBACK;			
VI_CONTROL_EXPORT extern int ZC_NR_BUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_NR_BUTTONBORDER;			
VI_CONTROL_EXPORT extern int ZC_PR_BUTTONBACK;			
VI_CONTROL_EXPORT extern int ZC_PR_BUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_PR_BUTTONBORDER;			
VI_CONTROL_EXPORT extern int ZC_D_BUTTONBACK;				
VI_CONTROL_EXPORT extern int ZC_D_BUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_D_BUTTONBORDER;			

VI_CONTROL_EXPORT extern int ZC_N_DIALOGBUTTONBACK;					
VI_CONTROL_EXPORT extern int ZC_N_DIALOGBUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_N_DIALOGBUTTONBORDER;			
VI_CONTROL_EXPORT extern int ZC_P_DIALOGBUTTONBACK;				
VI_CONTROL_EXPORT extern int ZC_P_DIALOGBUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_P_DIALOGBUTTONBORDER;			
VI_CONTROL_EXPORT extern int ZC_F_DIALOGBUTTONBACK;				
VI_CONTROL_EXPORT extern int ZC_F_DIALOGBUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_F_DIALOGBUTTONBORDER;			
VI_CONTROL_EXPORT extern int ZC_NR_DIALOGBUTTONBACK;			
VI_CONTROL_EXPORT extern int ZC_NR_DIALOGBUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_NR_DIALOGBUTTONBORDER;			
VI_CONTROL_EXPORT extern int ZC_PR_DIALOGBUTTONBACK;			
VI_CONTROL_EXPORT extern int ZC_PR_DIALOGBUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_PR_DIALOGBUTTONBORDER;			
VI_CONTROL_EXPORT extern int ZC_D_DIALOGBUTTONBACK;				
VI_CONTROL_EXPORT extern int ZC_D_DIALOGBUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_D_DIALOGBUTTONBORDER;			

VI_CONTROL_EXPORT extern int ZC_N_TOOLBARBUTTONBACK;					
VI_CONTROL_EXPORT extern int ZC_N_TOOLBARBUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_N_TOOLBARBUTTONBORDER;			
VI_CONTROL_EXPORT extern int ZC_P_TOOLBARBUTTONBACK;				
VI_CONTROL_EXPORT extern int ZC_P_TOOLBARBUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_P_TOOLBARBUTTONBORDER;			
VI_CONTROL_EXPORT extern int ZC_F_TOOLBARBUTTONBACK;				
VI_CONTROL_EXPORT extern int ZC_F_TOOLBARBUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_F_TOOLBARBUTTONBORDER;			
VI_CONTROL_EXPORT extern int ZC_NR_TOOLBARBUTTONBACK;			
VI_CONTROL_EXPORT extern int ZC_NR_TOOLBARBUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_NR_TOOLBARBUTTONBORDER;			
VI_CONTROL_EXPORT extern int ZC_PR_TOOLBARBUTTONBACK;			
VI_CONTROL_EXPORT extern int ZC_PR_TOOLBARBUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_PR_TOOLBARBUTTONBORDER;			
VI_CONTROL_EXPORT extern int ZC_D_TOOLBARBUTTONBACK;				
VI_CONTROL_EXPORT extern int ZC_D_TOOLBARBUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_D_TOOLBARBUTTONBORDER;			
//end buttons
VI_CONTROL_EXPORT extern int ZC_TABBUTTONBACK;				
VI_CONTROL_EXPORT extern int ZC_TABBUTTONTEXT;				
VI_CONTROL_EXPORT extern int ZC_TABBUTTONBORDER;			

VI_CONTROL_EXPORT extern int ZC_TABBUTTONBACKSELECTED;		
VI_CONTROL_EXPORT extern int ZC_TABBUTTONTEXTSELECTED;		
VI_CONTROL_EXPORT extern int ZC_TABBUTTONBORDERSELECTED;	

VI_CONTROL_EXPORT extern int ZC_TABBUTTONBACKFOCUS;		
VI_CONTROL_EXPORT extern int ZC_TABBUTTONTEXTFOCUS;		
VI_CONTROL_EXPORT extern int ZC_TABBUTTONBORDERFOCUS;		

VI_CONTROL_EXPORT extern int ZC_TOOLBARBACK;				
VI_CONTROL_EXPORT extern int ZC_TOOLBARBORDER;				

VI_CONTROL_EXPORT extern int ZC_EDITORVIEWBORDER;			
VI_CONTROL_EXPORT extern int ZC_EDITORVIEWBORDERFOCUS;		

VI_CONTROL_EXPORT extern int ZC_EDITORLEFTBARBACK;			

VI_CONTROL_EXPORT extern int ZC_EDITORVIEWBACKLIGHT;		
VI_CONTROL_EXPORT extern int ZC_EDITORVIEWBACKDARK;		


VI_CONTROL_EXPORT extern int ZC_DIALOGTITLETEXTCOLOR;			
VI_CONTROL_EXPORT extern int ZC_DIALOGTITLEBACKCOLOR;		

VI_CONTROL_EXPORT extern int ZC_DIALOGTITLETEXTCOLORFOCUS;	
VI_CONTROL_EXPORT extern int ZC_DIALOGTITLEBACKCOLORFOCUS;	

VI_CONTROL_EXPORT extern int ZC_DIALOGTITLEBORDER;			
VI_CONTROL_EXPORT extern int ZC_DIALOGTITLEBORDERFOCUS;	

VI_CONTROL_EXPORT extern int ZC_DIALOGBORDER;				
VI_CONTROL_EXPORT extern int ZC_DIALOGBORDERFOCUS;			

VI_CONTROL_EXPORT extern int ZC_DIALOGBACKLIGHT;			
VI_CONTROL_EXPORT extern int ZC_DIALOGBACKDARK;			

VI_CONTROL_EXPORT extern int ZC_STATUSBARBACK;			

VI_CONTROL_EXPORT extern int ZC_SEPARATORCOLOR;			
VI_CONTROL_EXPORT extern int ZC_MAINTEXTCOLOR	;							

VI_CONTROL_EXPORT extern int ZC_VERTICALLINECOLOR;			

////////////////////////////////////////////////////////MACROS/////////////////////
#define CZC_BLACK			GetVIColor(VICOLOR_BLACK	)
#define CZC_51				GetVIColor(VICOLOR_51		)
#define CZC_65				GetVIColor(VICOLOR_65		)
#define CZC_100				GetVIColor(VICOLOR_100		)
#define CZC_128				GetVIColor(VICOLOR_128		)
#define CZC_152				GetVIColor(VICOLOR_152		)
#define CZC_176				GetVIColor(VICOLOR_176		)
#define CZC_200				GetVIColor(VICOLOR_200		)
#define CZC_230				GetVIColor(VICOLOR_230		)
#define CZC_WHITE			GetVIColor(VICOLOR_WHITE	)
#define CZC_RED				GetVIColor(VICOLOR_RED		)
#define CZC_HALFRED			GetVIColor(VICOLOR_HALFRED	)
#define CZC_DYN				GetVIColor(VICOLOR_DYN		)
#define CZC_DYNGRAYED		GetVIColor(VICOLOR_DYNGRAYED)
#define CZC_DYNSELECT		GetVIColor(VICOLOR_DYNSELECT)



#define CZC_MENUBACK					GetVIColor(ZC_MENUBACK				)
#define CZC_MENUBORDER					GetVIColor(ZC_MENUBORDER				)
#define CZC_MENUTEXT					GetVIColor(ZC_MENUTEXT				)
#define CZC_MAINBACK					GetVIColor(ZC_MAINBACK				)
#define CZC_CONTROLBACK					GetVIColor(ZC_CONTROLBACK				)
#define CZC_CONTROLBORDER				GetVIColor(ZC_CONTROLBORDER			)
#define CZC_CONTROLTEXT					GetVIColor(ZC_CONTROLTEXT				)
#define CZC_CONTROLBACKSELECT			GetVIColor(ZC_CONTROLBACKSELECT		)
#define CZC_CONTROLBORDERSELECT			GetVIColor(ZC_CONTROLBORDERSELECT		)
#define CZC_CONTROLTEXTSELECT			GetVIColor(ZC_CONTROLTEXTSELECT		)
#define CZC_CONTROLBACKFOCUS			GetVIColor(ZC_CONTROLBACKFOCUS		)
#define CZC_CONTROLBORDERFOCUS			GetVIColor(ZC_CONTROLBORDERFOCUS		)
#define CZC_CONTROLTEXTFOCUS			GetVIColor(ZC_CONTROLTEXTFOCUS		)

#define CZC_N_BUTTONBACK				GetVIColor(ZC_N_BUTTONBACK			)
#define CZC_N_BUTTONTEXT				GetVIColor(ZC_N_BUTTONTEXT			)
#define CZC_N_BUTTONBORDER				GetVIColor(ZC_N_BUTTONBORDER			)
#define CZC_P_BUTTONBACK				GetVIColor(ZC_P_BUTTONBACK			)
#define CZC_P_BUTTONTEXT				GetVIColor(ZC_P_BUTTONTEXT			)
#define CZC_P_BUTTONBORDER				GetVIColor(ZC_P_BUTTONBORDER			)
#define CZC_F_BUTTONBACK				GetVIColor(ZC_F_BUTTONBACK			)
#define CZC_F_BUTTONTEXT				GetVIColor(ZC_F_BUTTONTEXT			)
#define CZC_F_BUTTONBORDER				GetVIColor(ZC_F_BUTTONBORDER			)
#define CZC_NR_BUTTONBACK				GetVIColor(ZC_NR_BUTTONBACK			)
#define CZC_NR_BUTTONTEXT				GetVIColor(ZC_NR_BUTTONTEXT			)
#define CZC_NR_BUTTONBORDER				GetVIColor(ZC_NR_BUTTONBORDER			)
#define CZC_PR_BUTTONBACK				GetVIColor(ZC_PR_BUTTONBACK			)			
#define CZC_PR_BUTTONTEXT				GetVIColor(ZC_PR_BUTTONTEXT			)				
#define CZC_PR_BUTTONBORDER				GetVIColor(ZC_PR_BUTTONBORDER			)			
#define CZC_D_BUTTONBACK				GetVIColor(ZC_D_BUTTONBACK			)				
#define CZC_D_BUTTONTEXT				GetVIColor(ZC_D_BUTTONTEXT			)				
#define CZC_D_BUTTONBORDER				GetVIColor(ZC_D_BUTTONBORDER			)			

#define CZC_N_TOOLBARBUTTONBACK				GetVIColor(ZC_N_TOOLBARBUTTONBACK			)
#define CZC_N_TOOLBARBUTTONTEXT				GetVIColor(ZC_N_TOOLBARBUTTONTEXT			)
#define CZC_N_TOOLBARBUTTONBORDER				GetVIColor(ZC_N_TOOLBARBUTTONBORDER			)
#define CZC_P_TOOLBARBUTTONBACK				GetVIColor(ZC_P_TOOLBARBUTTONBACK			)
#define CZC_P_TOOLBARBUTTONTEXT				GetVIColor(ZC_P_TOOLBARBUTTONTEXT			)
#define CZC_P_TOOLBARBUTTONBORDER				GetVIColor(ZC_P_TOOLBARBUTTONBORDER			)
#define CZC_F_TOOLBARBUTTONBACK				GetVIColor(ZC_F_TOOLBARBUTTONBACK			)
#define CZC_F_TOOLBARBUTTONTEXT				GetVIColor(ZC_F_TOOLBARBUTTONTEXT			)
#define CZC_F_TOOLBARBUTTONBORDER				GetVIColor(ZC_F_TOOLBARBUTTONBORDER			)
#define CZC_NR_TOOLBARBUTTONBACK				GetVIColor(ZC_NR_TOOLBARBUTTONBACK			)
#define CZC_NR_TOOLBARBUTTONTEXT				GetVIColor(ZC_NR_TOOLBARBUTTONTEXT			)
#define CZC_NR_TOOLBARBUTTONBORDER				GetVIColor(ZC_NR_TOOLBARBUTTONBORDER			)
#define CZC_PR_TOOLBARBUTTONBACK				GetVIColor(ZC_PR_TOOLBARBUTTONBACK			)			
#define CZC_PR_TOOLBARBUTTONTEXT				GetVIColor(ZC_PR_TOOLBARBUTTONTEXT			)				
#define CZC_PR_TOOLBARBUTTONBORDER				GetVIColor(ZC_PR_TOOLBARBUTTONBORDER			)			
#define CZC_D_TOOLBARBUTTONBACK				GetVIColor(ZC_D_TOOLBARBUTTONBACK			)				
#define CZC_D_TOOLBARBUTTONTEXT				GetVIColor(ZC_D_TOOLBARBUTTONTEXT			)				
#define CZC_D_TOOLBARBUTTONBORDER				GetVIColor(ZC_D_TOOLBARBUTTONBORDER			)			

#define CZC_N_DIALOGBUTTONBACK				GetVIColor(ZC_N_DIALOGBUTTONBACK			)
#define CZC_N_DIALOGBUTTONTEXT				GetVIColor(ZC_N_DIALOGBUTTONTEXT			)
#define CZC_N_DIALOGBUTTONBORDER				GetVIColor(ZC_N_DIALOGBUTTONBORDER			)
#define CZC_P_DIALOGBUTTONBACK				GetVIColor(ZC_P_DIALOGBUTTONBACK			)
#define CZC_P_DIALOGBUTTONTEXT				GetVIColor(ZC_P_DIALOGBUTTONTEXT			)
#define CZC_P_DIALOGBUTTONBORDER				GetVIColor(ZC_P_DIALOGBUTTONBORDER			)
#define CZC_F_DIALOGBUTTONBACK				GetVIColor(ZC_F_DIALOGBUTTONBACK			)
#define CZC_F_DIALOGBUTTONTEXT				GetVIColor(ZC_F_DIALOGBUTTONTEXT			)
#define CZC_F_DIALOGBUTTONBORDER				GetVIColor(ZC_F_DIALOGBUTTONBORDER			)
#define CZC_NR_DIALOGBUTTONBACK				GetVIColor(ZC_NR_DIALOGBUTTONBACK			)
#define CZC_NR_DIALOGBUTTONTEXT				GetVIColor(ZC_NR_DIALOGBUTTONTEXT			)
#define CZC_NR_DIALOGBUTTONBORDER				GetVIColor(ZC_NR_DIALOGBUTTONBORDER			)
#define CZC_PR_DIALOGBUTTONBACK				GetVIColor(ZC_PR_DIALOGBUTTONBACK			)			
#define CZC_PR_DIALOGBUTTONTEXT				GetVIColor(ZC_PR_DIALOGBUTTONTEXT			)				
#define CZC_PR_DIALOGBUTTONBORDER				GetVIColor(ZC_PR_DIALOGBUTTONBORDER			)			
#define CZC_D_DIALOGBUTTONBACK				GetVIColor(ZC_D_DIALOGBUTTONBACK			)				
#define CZC_D_DIALOGBUTTONTEXT				GetVIColor(ZC_D_DIALOGBUTTONTEXT			)				
#define CZC_D_DIALOGBUTTONBORDER				GetVIColor(ZC_D_DIALOGBUTTONBORDER			)			

#define CZC_TABBUTTONBACK				GetVIColor(ZC_TABBUTTONBACK			)				
#define CZC_TABBUTTONTEXT				GetVIColor(ZC_TABBUTTONTEXT			)				
#define CZC_TABBUTTONBORDER				GetVIColor(ZC_TABBUTTONBORDER			)			
#define CZC_TABBUTTONBACKSELECTED		GetVIColor(ZC_TABBUTTONBACKSELECTED	)		
#define CZC_TABBUTTONTEXTSELECTED		GetVIColor(ZC_TABBUTTONTEXTSELECTED	)		
#define CZC_TABBUTTONBORDERSELECTED		GetVIColor(ZC_TABBUTTONBORDERSELECTED	)	
#define CZC_TABBUTTONBACKFOCUS			GetVIColor(ZC_TABBUTTONBACKFOCUS		)		
#define CZC_TABBUTTONTEXTFOCUS			GetVIColor(ZC_TABBUTTONTEXTFOCUS		)		
#define CZC_TABBUTTONBORDERFOCUS		GetVIColor(ZC_TABBUTTONBORDERFOCUS	)		
#define CZC_TOOLBARBACK					GetVIColor(ZC_TOOLBARBACK				)				
#define CZC_TOOLBARBORDER				GetVIColor(ZC_TOOLBARBORDER			)				
#define CZC_EDITORVIEWBORDER			GetVIColor(ZC_EDITORVIEWBORDER		)			
#define CZC_EDITORVIEWBORDERFOCUS		GetVIColor(ZC_EDITORVIEWBORDERFOCUS	)		
#define CZC_EDITORLEFTBARBACK			GetVIColor(ZC_EDITORLEFTBARBACK		)			
#define CZC_EDITORVIEWBACKLIGHT			GetVIColor(ZC_EDITORVIEWBACKLIGHT		)		
#define CZC_EDITORVIEWBACKDARK			GetVIColor(ZC_EDITORVIEWBACKDARK		)		
#define CZC_DIALOGTITLETEXTCOLOR		GetVIColor(ZC_DIALOGTITLETEXTCOLOR	)			
#define CZC_DIALOGTITLEBACKCOLOR		GetVIColor(ZC_DIALOGTITLEBACKCOLOR	)		
#define CZC_DIALOGTITLETEXTCOLORFOCUS	GetVIColor(ZC_DIALOGTITLETEXTCOLORFOCUS)	
#define CZC_DIALOGTITLEBACKCOLORFOCUS	GetVIColor(ZC_DIALOGTITLEBACKCOLORFOCUS)	
#define CZC_DIALOGTITLEBORDER			GetVIColor(ZC_DIALOGTITLEBORDER		)			
#define CZC_DIALOGTITLEBORDERFOCUS		GetVIColor(ZC_DIALOGTITLEBORDERFOCUS	)	
#define CZC_DIALOGBORDER				GetVIColor(ZC_DIALOGBORDER			)				
#define CZC_DIALOGBORDERFOCUS			GetVIColor(ZC_DIALOGBORDERFOCUS		)			
#define CZC_DIALOGBACKLIGHT				GetVIColor(ZC_DIALOGBACKLIGHT			)			
#define CZC_DIALOGBACKDARK				GetVIColor(ZC_DIALOGBACKDARK			)			
#define CZC_STATUSBARBACK				GetVIColor(ZC_STATUSBARBACK			)			
#define CZC_SEPARATORCOLOR				GetVIColor(ZC_SEPARATORCOLOR			)			
#define CZC_MAINTEXTCOLOR				GetVIColor(ZC_MAINTEXTCOLOR			)			
#define CZC_VERTICALLINECOLOR			GetVIColor(ZC_VERTICALLINECOLOR		)			

////////////////////////////////////////////////////////MACROS/////////////////////



// Interface Zones Colors Index


//.ini file
#define INI_FILENAME				"virtools.ini"
//fields names
#define BUTTON_OK_SIZE			"button_ok_size"
#define BUTTON_APPLY_SIZE		"button_apply_size"
#define BUTTON_CANCEL_SIZE		"button_cancel_size"

#define DIALOG_MARGIN_LEFT		"dialog_margin_left"
#define DIALOG_MARGIN_RIGHT		"dialog_margin_right"
#define DIALOG_MARGIN_TOP		"dialog_margin_top"
#define DIALOG_MARGIN_BOTTOM	"dialog_margin_bottom"
#define DIALOG_MARGIN_INSIDE	"dialog_margin_inside"
#define DIALOG_ITEMHEIGHT		"dialog_itemheight"
#define DIALOG_LINEJUMP			"dialog_linejump"
#define DIALOG_BUTTONXFREESPACE "dialog_buttonxfreespace"
#define DIALOG_BUTTONSEPARATION	"dialog_button_separation"

#define COLOR_BLACK				"color_black"
#define COLOR_51				"color_51"
#define COLOR_65				"color_65"
#define COLOR_100				"color_100"
#define COLOR_128				"color_128"
#define COLOR_152				"color_152"
#define COLOR_176				"color_176"
#define COLOR_200				"color_200"
#define COLOR_230				"color_230"
#define COLOR_WHITE				"color_white"
#define COLOR_RED				"color_red"
#define COLOR_HALFRED			"color_halfred"
#define COLOR_DYN				"color_dyn"
#define COLOR_DYNGRAYED			"color_dyngrayed"
#define COLOR_DYNSELECT			"color_dynselect"

typedef struct VIInterfaceData{
	CSize button_ok_size;
	CSize button_apply_size;
	CSize button_cancel_size;

	int dialog_margin_left;
	int dialog_margin_right;
	int dialog_margin_top;
	int dialog_margin_bottom;
	int dialog_margin_inside;
	int dialog_item_height;
	int dialog_line_jump;
	int dialog_button_xfreespace;
	int dialog_button_separation;

//constructor
	VIInterfaceData()
	{
		button_ok_size.cx=60;
		button_ok_size.cy=18;
		button_apply_size.cx=60;
		button_apply_size.cy=18;
		button_cancel_size.cx=60;
		button_cancel_size.cy=18;
		dialog_margin_inside=6;
		dialog_item_height=16;
		dialog_line_jump=5;
		dialog_button_xfreespace=4;	//both side, free space in button
		dialog_button_separation=10;

		dialog_margin_left=10;
		dialog_margin_right=10;
		dialog_margin_top=5;
		dialog_margin_bottom=24;
	}
}VIInterfaceData ;

// End Defines


class VIGDIManager
{
public:

	VIGDIManager();
	~VIGDIManager();
	BOOL InitGDIManager();
	void LoadDefaultInterfaceData();
	void SaveDefaultInterfaceData();

	CFont *GetVIFont(int VIFontIndex);

	CBrush *GetVIBrush(COLORREF clr);
	CBrush *GetVIBrush(int VIColorIndex);
	COLORREF SetVIBrush(int VIColorIndex,COLORREF newColor);

	COLORREF GetVIColor(int VIColorIndex);
	COLORREF SetVIColor(int VIColorIndex,COLORREF newColor);

	VIInterfaceData * GetVIInterfaceData();

	//return value : color index
	int RegisterVIColor(COLORREF clr,BOOL forceCreate=TRUE);
	//return value : brush index
	int RegisterVIBrush(COLORREF clr,BOOL forceCreate=TRUE);
	//return value : font index
	int RegisterVIFont(	int nHeight=12,
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
protected :

	void InitFonts();
	void InitColors();
	void InitBrush();

	VIInterfaceData m_interfaceData;

	XArray<CFont*> m_CFontArray;

	XArray<CBrush*> m_CBrushArray;

	XArray<COLORREF> m_ColorArray;
};

#endif
