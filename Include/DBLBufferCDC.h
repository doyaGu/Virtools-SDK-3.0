// DBLBufferCDC.h: interface for the DBLBufferCDC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBLBUFFERCDC_H__FE580C22_9C0C_11D3_BA37_00105A669BB5__INCLUDED_)
#define AFX_DBLBUFFERCDC_H__FE580C22_9C0C_11D3_BA37_00105A669BB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS DBLBufferCDC  : public CDC
{
public:
	DBLBufferCDC();
	virtual ~DBLBufferCDC();
	
	HRESULT Create(CDC *cdc,RECT& r);
	HRESULT Render(CRgn *rgn = NULL);

protected:

	CDC *m_cdc;
	CBitmap m_curBitmap; 
	CBitmap *m_prevBitmap; 
	RECT m_Rect;

};

#endif // !defined(AFX_DBLBUFFERCDC_H__FE580C22_9C0C_11D3_BA37_00105A669BB5__INCLUDED_)
