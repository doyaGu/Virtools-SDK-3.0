#if !defined(AFX_CKOBJECTCOMBOBOX_H__295405A6_24C4_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
#define AFX_CKOBJECTCOMBOBOX_H__295405A6_24C4_11D3_BAE2_00A0C9CC72C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VIcombobox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VIComboBox window

//item data = CK_ID
class AFX_EXT_CLASS CKObjectComboBox : public VIComboBox
{
public:
	CKObjectComboBox() {m_pContext=NULL;m_ownerDrawHeight=6;}

	void SetContext(CKContext * ctxt);
	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
	virtual void DoOnPaint(CDC* pDC=NULL,BOOL forceDraw=FALSE);

private:
	CKContext * m_pContext;
	static XArray<HICON>	m_IconArray;
	static BOOL				m_IconInit;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CKOBJECTCOMBOBOX_H__295405A6_24C4_11D3_BAE2_00A0C9CC72C3__INCLUDED_)
