#ifndef _VI_CONTROLS_DEFINES_H_
#define _VI_CONTROLS_DEFINES_H_

#ifdef _WINDOWS
	#define VI_CTRL_NOTIFY	WM_NOTIFY 
#endif

//flags for buttons type class
typedef enum {
	VI_CTRL_BUTTON_UNCHECKED 			=	0x00000000,
	VI_CTRL_BUTTON_CHECKED			=	0x00000001,
	VI_CTRL_BUTTON_INDERTERMINATED	=	0x00000002,
	VI_CTRL_BUTTON_HIGHLIGHTED		=	0x00000004,
}VI_CTRL_BUTTON_FLAGS;

#define IsHighLighted() (m_CtrlFlags & VI_CTRL_BUTTON_HIGHLIGHTED)
#define SetHighLight(b) {if(b) m_CtrlFlags |= VI_CTRL_BUTTON_HIGHLIGHTED; else m_CtrlFlags &= ~VI_CTRL_BUTTON_HIGHLIGHTED;}

#define IsChecked() ((BOOL)(m_CtrlFlags & VI_CTRL_BUTTON_CHECKED))
#define SetChecked(b){ m_CtrlFlags &= ~(VI_CTRL_BUTTON_CHECKED | VI_CTRL_BUTTON_INDERTERMINATED); m_CtrlFlags |= b;}
//----------------------------



#define IsFocused() (GetFocus() == this ? TRUE : FALSE)
#define SendMessageToParent(m,w,l) this->GetParent()->SendMessage(m,(WPARAM)w,(LPARAM)l)

//notification messages of VIcontrols
typedef enum {
	VI_CTRL_NM_LCLICK				= 1,
	VI_CTRL_NM_MCLICK				= 2,
	VI_CTRL_NM_RCLICK				= 3,
	VI_CTRL_NM_LDBLCLICK			= 4,
	VI_CTRL_NM_MDBLCLICK			= 5,
	VI_CTRL_NM_RDBLCLICK			= 6,

	VI_CTRL_NM_LDRAGBEGIN			= 7,
	VI_CTRL_NM_LDRAGGING			= 8,
	VI_CTRL_NM_LDRAGEND			= 9,

	VI_CTRL_NM_MDRAGBEGIN			= 10,
	VI_CTRL_NM_MDRAGGING			= 11,
	VI_CTRL_NM_MDRAGEND			= 12,

	VI_CTRL_NM_RDRAGBEGIN			= 13,
	VI_CTRL_NM_RDRAGGING			= 14,
	VI_CTRL_NM_RDRAGEND			= 15,

	VI_CTRL_NM_VALUECHANGING		= 16,
	VI_CTRL_NM_VALUECHANGED		= 17,

	VI_CTRL_NM_BEGINLABELEDIT		= 18,
	VI_CTRL_NM_ENDLABELEDIT		= 19,

	VI_CTRL_NM_ENDDIALOGOK		= 20,
	VI_CTRL_NM_ENDDIALOGCANCEL	= 21,
	VI_CTRL_NM_DIALOGAPPLY		= 22,

}VI_CTRL_NOTIFICATION_MESSAGE;

//messages of VIcontrols (send by)
typedef enum {
	VI_CTRL_MSG_RETURN		= WM_USER+1000,		//send by VIComboBox when return pressed, id in wParam / CKObjectComboBox, when item name has been edited
	VI_CTRL_MSG_EDIT		= WM_USER+1001,		//send by VIComboBox when F2 pressed, id in wParam
	VI_CTRL_MSG_KILLFOCUS	= WM_USER+1002,		//send by VIEdit when it receives WM_KILLFOCUS, add GetDlgCtrlID() in lParam member
	VI_CTRL_MSG_CANCELEDIT	= WM_USER+1003,		//send by VIEdit when esc is pressed, add GetDlgCtrlID() in wParam member
	VI_CTRL_MSG_OUTOFSYNC	= WM_USER+1004,		//send by VIRichEdit when undo cursor is back to origin
	VI_CTRL_MSG_SYNCED		= WM_USER+1005,		//send by VIRichEdit when undo cursor is no more at origin
	VI_CTRL_MSG_FULLSCREEN	= WM_USER+1006,		//send by VIRichEdit when toggled to/from fullscreen. wParam = 1 if to fullscreen, 0 otherwise, lParam is CWnd*
}VI_CTRL_MESSAGE;

#endif