#if !defined(AFX_VIRICHEDIT_H__89F06A80_24BC_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
#define AFX_VIRICHEDIT_H__89F06A80_24BC_11D3_BAE2_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIRichedit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIRichEdit window

typedef enum {
	VI_CTRL_RICHEDIT_TEXT							= 0x00000000,
	VI_CTRL_RICHEDIT_FRAMERECT						= 0x00000020,
	VI_CTRL_RICHEDIT_NOREDRAW						= 0x00000040,
	VI_CTRL_RICHEDIT_CREATE_CONTROLS_AFTER_CREATE	= 0x00000080,
	VI_CTRL_RICHEDIT_CTRLSPACECOMPLETION			= 0x00000100,
}VI_CTRL_RICHEDIT_FLAGS;

#include "XHashTable.h"
#include "XClassArray.h"
#include "XDictionnary.h"
#include "XList.h"
#include "XBitArray.h"


typedef struct MarkUpdateData{
	int m_l1;
	int m_l2;
	int m_l3;
	int m_l4;
	int	m_newRangeCpMin;
	int	m_newRangeCpMax;
	BOOL m_noChange;
	MarkUpdateData() : m_l1(-1),m_l2(-1),m_l3(-1),m_l4(-1),m_newRangeCpMin(-1),m_newRangeCpMax(-1) {}
	BOOL IsValid()
	{
		return ((m_l1!=-1) && (m_l2!=-1));
	}
	BOOL NeedToComputeL3L4()
	{
		return ((m_l3==-1) && (m_l4==-1));
	}
}MarkUpdateData;
/******************************************
Class Unit : 
For autocompletion some function, members only applies to 
a specific class. 

*******************************************/
class XClassUnit 
{
public:
	XClassUnit(char* Name = "") {
		m_ClassName = Name;
	}
	XString					m_ClassName;
	XClassArray<XString>	m_ParentClassNames;
	XCharDictionnary		m_AutoCompleteDictionnary;
};

// Hash Tables (keyword <-> color)
typedef XHashTable<DWORD,XString>					XKeyWordColorHashTable;			
typedef XHashTable<DWORD,XString>::Iterator			XKeyWordColorHashTableIt;		

// Hash Tables (keyword <-> class)
typedef XHashTable<XClassUnit*,XString>				XClassHashTable;			
typedef XHashTable<XClassUnit*,XString>::Iterator	XClassHashTableIt;		

// Hash Tables (keyword <-> string)
typedef XHashTable<XString,XString>					XStringHashTable;			
typedef XHashTable<XString,XString>::Iterator		XStringHashTableIt;		





/******************************************
Undo Unit : 
This describes an action taken by the user :
Text (TextReplaced) which was at the given position (TextPosition) was
replaced by the Text (NewText) and now occupies (NewRange) position
*******************************************/
class XUndoUnit {
public:
	XString		TextReplaced;
	CHARRANGE	TextRange;
	XString		NewText;
	CHARRANGE	NewRange;
	BOOL		UndoPreviousUnit;
	BOOL		RedoNextUnit;
};


class XUndoStorage {
public:
	mutable XList<XUndoUnit*>		m_UndoUnits;		// List of undo units
	mutable XList<XUndoUnit*>		m_RedoUnits;		// List of redo units (an undo unit goes to the redo when done  anc vice versa)
	mutable XClassArray<XUndoUnit>	m_UndoUnitsPool;	// A preallocated pool of undo units (~200)
	XBitArray				m_TakenUndoUnits;	// a bit array of each undo unit that is used...
	

	// Warning => this operator transfer data from one structure to another.... 
	XUndoStorage& operator = (const XUndoStorage& a) {
		m_UndoUnits.Swap(a.m_UndoUnits);
		m_RedoUnits.Swap(a.m_RedoUnits);
		m_UndoUnitsPool.Swap(a.m_UndoUnitsPool);
		m_TakenUndoUnits = a.m_TakenUndoUnits;
		return *this;
	}
/*
	XUndoStorage& operator = (const XUndoStorage& a) {
		m_UndoUnits.Swap(a.m_UndoUnits);
		m_RedoUnits.Swap(a.m_RedoUnits);
		m_UndoUnitsPool.Swap(a.m_UndoUnitsPool);
		m_TakenUndoUnits = a.m_TakenUndoUnits;
		return *this;
	}
*/
};


/*******************************************
Not used : a marker of scope 
*********************************************/
class XScope{
public:
	XScope() {}
	XScope(char* StartMarker,char* EndMarker,DWORD Color):m_StartScopeMarker(StartMarker),m_EndScopeMarker(EndMarker),m_Color(Color) {
		m_StartMarkerLength = StartMarker ? strlen(StartMarker) : 0;
		m_EndMarkerLength = EndMarker ? strlen(EndMarker) : 0;
	}
	
	bool IsStartMarker(char* text) {
		for (int i=0;i<m_StartMarkerLength;++i) if (text[i] != m_StartScopeMarker[i]) return FALSE;
		return TRUE;
	}
	bool IsEndMarker(char* text) {
		for (int i=0;i<m_EndMarkerLength;++i) if (text[i] != m_EndScopeMarker[i]) return FALSE;
		return TRUE;
	}	
	int ScopeEnum(int en) {
		return (en << Index*3);
	}

	int	  Index;
	char* m_StartScopeMarker;
	int   m_StartMarkerLength;
	char* m_EndScopeMarker;
	int   m_EndMarkerLength;
	DWORD	m_Color;
	XArray<CHARRANGE> m_Ranges;
};

struct DescAndRealName {
	char* Description;
	char* RealName;
	~DescAndRealName() {
		free(Description);
		free(RealName);
	}
};



class AFX_EXT_CLASS VIRichEdit : public CRichEditCtrl,public VIControl
{
// Construction
public:
	VIRichEdit();
	void SetRedraw( BOOL bRedraw = TRUE );

	BOOL GetOverTypeMode();

	BOOL DoRedo(int* ls=NULL,int* le=NULL);
	BOOL DoUndo(int* ls=NULL,int* le=NULL);
	BOOL DoCut();
	BOOL DoPaste();

//---find & replace
	BOOL DoFindText();
	BOOL DoReplaceText();
	BOOL DoGotoLine();

	XUndoUnit* ReplaceNext();
	BOOL FindNext(CHARRANGE &range,BOOL down=TRUE,BOOL select=FALSE);
private:
	XString	m_findStr;
	XString m_replaceStr;
	int		m_findTextMatchCase;
	BOOL	m_findBackward;
//----

public:
	void GetRangeString(XString& string,int cpMin,int cpMax);
	void GetCurSelString(XString& string);

//---- icon, breakpoint, any kind of mark, managment & margin management too
	//SetMarkImageList: computes margin for richedit where icon will be drawn
	//call UpdateSizeForMarks after that so that new margin takes effect
	void SetMarkImageList(CImageList *list);
	void AddMarkToLine(int indexInImageList,int line);
	void RemoveMarkFromLine(int indexInImageList,int line);
	void RemoveAllMarksFromLine(int line);
	void RemoveAllMarks();
	void RemoveMarkFromAllLine(int indexInImageList);
	void UpdateSizeForMarks();
	void SetLineHeight();
	void UpdateMarks(MarkUpdateData &data);
	XHashTable<DWORD,int>::Iterator	GetMarkList() {return m_markList.Begin();}
	void GetMarkLines(int indexInImageList, XArray <int> &oLines) const;
	void SetMargin(int m);	//set margin size where no text will be drawn, marin is on the left
	int	 GetMargin() const;	//get margin size


//----- Must be called by the owner PreTranslateMessage function
// if it returns TRUE no more processing should be done...
	BOOL	TranslateKeyMessages(MSG* pMsg);

//---- Updates the complete edit colors...
	void UpdateColors(BOOL iOnlyVisible = FALSE);

//--- Sets / Gets the Control Font ----------
	virtual void SetControlFont(CFont *fnt);
	virtual void SetBackColor(COLORREF clr);

//--- Fullscreen----------------------------------------------------
	void	ToggleFullscreen();

//--- Tab Size ----------------------------------------------------
	int GetTabSize() { return m_TabSize; }
	void SetTabSize(int TabSize);

//--- Word Separators ----------------------------------------------------
	BOOL IsSeparator(char a) { return m_WordSeparator[a]; }
	void SetSeparator(char a,BOOL Separator=TRUE) { m_WordSeparator[a] = Separator; }

	void	SelectRow(int iRow);

//--- Auto complete -----------------------------------------------
	void AddKeyWord(char* Owner,char* KeyWord,char* Description = NULL);
	void RemoveKeyWord(char* Owner,char* KeyWord);
	// Add '.' ,'->' 	
	void AddOwnerSeparator(char* SeparatorString);	
	// A type (as a class ) 
	void AddOwnerType(char* Type, char* ParentType);	

	// for global variables that are not visible in the rich edit 
	// text : an association (object and its type )
	void AddGlobalAssociation(char* Object,char* Type);	
	void RemoveGlobalAssociation(char* Object);	

	// search in the text and the global association table if 
	// we find the type of an object
	char* GetTypeOf(char* Object);	

	void ResetAutoComplete();

	BOOL GetAutoComplete() { return m_AutoComplete; }
	void SetAutoComplete(BOOL Auto = TRUE) { m_AutoComplete = Auto;	}
	
//--- Auto complete list Tool Tip -----------------------------------
	void InsertAutoCompletion(int SuggestionIndex);

	void ValidateAutoCompleteList();
	BOOL IsAutoCompleteListVisible();
	void HideAutoCompleteList();
	void ShowAutoCompleteList();

	COLORREF GetToolTipColor() { return m_ToolTipColor; }
	void SetToolTipColor(COLORREF col);
	void SetToolTipFont(CFont *fnt);

//--- Colored Keywords ------------------------------------------
	void AddColorKeyWord(char* KeyWord,DWORD Color);
	void AddColorScope(char* StartKeyWord,char* EndKeyWord,DWORD Color);

	void RemoveColorKeyWord(char* KeyWord);
	void RemoveAllColorKeyWords() {
		m_SingleWordHash.Clear();
		m_Scopes.Clear();
	}

//--- Streaming.... ---------------------------------------------
	BOOL Load(char* FileName);	
	BOOL Save(char* FileName);


//------ Undo ------------
	void SaveUndoData(XUndoStorage& data);
	void LoadUndoData(const XUndoStorage& data);
	void ClearUndo();
	int GetUndoLimit() { return m_UndoUnitsPool.Size(); }
	void SetUndoLimit(int NbUndo);


	BOOL ProposeAutoComplete();


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VIRichEdit)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~VIRichEdit();
	static int DefaultHeight;
	BOOL m_ShowAutoCompleteListOnNextChar;
	void		DoOnPaint(int pos=-1);
protected:
	void InsertTabulation(BOOL Remove);
	void FormatLineRange(int StartLine,int EndLine,BOOL redraw = TRUE);
	
//---- undo	
	void		ReplaceSelection(char* newtext,BOOL Backspace = FALSE,BOOL Suppr = FALSE);
	void		CurrentSelectionIsBeingReplaced(BOOL Backspace,BOOL Suppr,char* newtext,MarkUpdateData *data = NULL);
	void		ClearRedoUnits();
	XUndoUnit*	GetNewUndoUnit();
	void		CheckWordUnit();
//-- Autocomplete	
	void	FindWordUnderCursor();
	void	ComputeAutoCompleteSuggestions();
	void	ScrollAutoCompleteList(int Dir);

//-- get the appropriate class description (Dictionnary)
	XClassUnit* GetClass(char* Owner);
	XClassUnit* GetClassAndConstruct(char* Owner);
	int BackwardSearch(int Pos,char* Object,BOOL matchcase=TRUE,CHARRANGE *range=NULL);


	int		GetToolTipSel();
	int		GetToolTipItemCount();
	void	SetToolTipSel(int index);

	void	CompleteClassHierarchy(char* Type, const XString& WordUnderCursor);
	bool	ShowDescriptionHierarchy(char* Type, const XString& WordUnderCursor);

	void GetTextBuffer();

//--- Find the '(' , ' [' or '{' corresponding to the one under the current curosr
	void FindScope();

//----- Colors
	XKeyWordColorHashTable	m_SingleWordHash;
// Scopes like /* */ and " " 
// number of scopes is limited to 8
	XClassArray<XScope>		m_Scopes;

//--- Settings 
	BYTE					m_WordSeparator[256];
	int						m_TabSize;
	BOOL					m_AutoComplete;
	BOOL					m_IsInFormat;
	XArray<char>			m_TempLine;
	XArray<char>			m_TextBuffer;
	
//----- Mouse drag& drop
	CHARRANGE				m_DragSelection;
	XString					m_DragSelectionString;
	CHARRANGE				m_DropSelection;
	BOOL					m_DragNDropCopyMode;


//---- Auto complete 
	XClassArray<XString>	m_AutoCompleteSuggestion;
	XClassArray<XString>	m_ClassSeparators;
	XStringHashTable		m_GlobalAssociations;
	XClassHashTable			m_DictionnariesPerClass;	// A dictionnary for each registred class 
														// ("" is a generic class which stands for a global scope)	

	
//---- Tool tip list
	XString					m_OwnerWord;
	XString					m_OwnerType;
	XString					m_WordUnderCursor;
	BOOL					m_CursorAtEndOfWord;
	VIListBox				m_List;
	COLORREF				m_ToolTipColor;
	CBrush					m_ToolTipBrush;

//---- undo
	XList<XUndoUnit*>		m_UndoUnits;		// List of undo units
	XList<XUndoUnit*>		m_RedoUnits;		// List of redo units (an undo unit goes to the redo when done  anc vice versa)
	XClassArray<XUndoUnit>	m_UndoUnitsPool;	// A preallocated pool of undo units (~200)
	XBitArray				m_TakenUndoUnits;	// a bit array of each undo unit that is used...
	
//----- Color updating
// Each scope marker use this enum to mark the line 
// (for each new scope the enum value is shifted by 3 so we are limited to 9 type of scopes
	enum {
		INSIDESCOPE				 = 1,	// Line is inside a given scope
		PARTIALLY_INSIDESCOPE	 = 2,	// only part of the line is inside the scope (otherwise the whole line is...)
		START_INSCOPE			 = 4,	// The start of the line is inside the scope but not entirely
			
		SCOPE_MASK				 = INSIDESCOPE|START_INSCOPE|PARTIALLY_INSIDESCOPE,
		MASK					 = 0x7FFFFFFF,
		COLOR_TO_UPDATE			 = 0x80000000,	// this line has been modified in a way that needs its color to be updated
	};
	
	CHARRANGE				m_LastModifiedRange;
// For each line a flags whether line is inside a given scope
	XArray<int>				m_ScopeLines;
	XArray<int>				m_PreviousScopeLines; // Same thing before the user modified the text
	XArray<CHARRANGE>		m_CommentedRanges;

	void					SetSynchronize(XBOOL iSynchro = TRUE) {
		m_Synchronized = iSynchro;
	}
	XBOOL					IsSynchronized() {
		return m_Synchronized;
	}
	XBOOL					m_Synchronized;

	// Description
	void					ShowDescription();
	XArray<DescAndRealName*>	m_Descriptions;
	VIStaticText				m_DescriptionToolTip;

//--Fullscreen
	int		m_bFullscreen;
	CWnd*	m_pParentBeforeFullscreen;
	CWnd*	m_pMainWndBeforeFullscreen;
	RECT	m_rectBeforeFullscreen;

	//{{AFX_MSG(VIRichEdit)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMsgfilter(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDragDropDone(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

//mark drawing & internal managment
	int						m_margin;
	CImageList*				m_pImageList;
	XHashTable<DWORD,int>	m_markList;
	int						m_lineHeight;
	BOOL					m_bMarkLastChangeIsSize;	//hack for richedit resize

	DECLARE_MESSAGE_MAP()

	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIRICHEDIT_H__89F06A80_24BC_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
