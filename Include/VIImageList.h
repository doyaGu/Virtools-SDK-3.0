#ifndef _VI_CTRL_IMAGE_LIST_DEFINES_H_
#define _VI_CTRL_IMAGE_LIST_DEFINES_H_


#include <XArray.h>

typedef XArray<CBitmap *> BITMAPVECTOR;
typedef XArray<COLORREF> COLORVECTOR;


#define NILD_NOMASK				0x00000000
#define NILD_USEIMAGEMASK		0x00000001
#define NILD_USEGLOBALMASK		0x00000002
#define NILD_USEIMAGECLRMASK	0x00000003
#define NILD_USEGLOBALCLRMASK	0x00000004

class AFX_EXT_CLASS VIImageList
{

public:

	VIImageList();
	~VIImageList();

	// Returns the numbers of image present in the image list
	int GetImageCount();

	// Adds an image to the image list at specified position, 
	// an optional bitmap can be used as mask when drawing image using flag NILD_USEIMAGEMASK
	int AddImage(CBitmap *bm,CBitmap *mask = NULL);
	
	// Adds an image to the image list at specified position, 
	// an optional color can be used as color key when drawing image using flag NILD_USEIMAGECLRMASK
	int AddImage(CBitmap *bm,COLORREF clr = CLR_NONE);
	
	// Sets the color used as color key when drawing using the NILD_USEGLOBALCLRMASK
	void SetGlobalClrMask(COLORREF clr);
	
	// Gets the color used as color key when drawing using the NILD_USEGLOBALCLRMASK
	COLORREF GetGlobalClrMask();
	
	// Sets the bitmap used as mask when drawing using the NILD_USEGLOBALMASK
	void SetGlobalBimapMask(CBitmap *b);
	
	// Gets the bitmap used as mask when drawing using the NILD_USEGLOBALMASK
	CBitmap *GetGlobalBitmapMask();
	
	// Remove an image from the image list at specified position
	void RemoveImage(int pos);

	// 
	//Draws the nth image into the specified DC available modes are :
	//	NILD_NOMASK				Draw Without colorkey
	//	NILD_USEIMAGEMASK		Uses image mask 
	//	NILD_USEGLOBALMASK		Uses global image mask
	//	NILD_USEIMAGECLRMASK	Uses image color mask
	//	NILD_USEGLOBALCLRMASK	Uses global color mask
	BOOL Draw(CDC *cdc,int img,POINT p,DWORD mode = NILD_NOMASK);

	// Gets images at specified position
	void GetImages(int pos,CBitmap **bm, CBitmap **mask);
	
	// Sets images at specified position, and returns old images
	void SetImages(int pos,CBitmap *bm, CBitmap *mask,CBitmap **oldbm, CBitmap **oldmask);


	// Gets image color mask at specified position
	COLORREF GetImageClrMask(int pos);
	
	// Sets image color mask at specified position
	void SetImageClrMask(int pos,COLORREF clr);
	

	// Delete every images added with AddImage, after a call to this function the image list is empty, 
	// CBitmap used to in previous calls to addimage have also been destroyed
	void DeleteAllImages();

protected:
	
	BITMAPVECTOR m_BimapArray;
	BITMAPVECTOR m_MaskArray;

	COLORVECTOR m_ColorArray;

	CBitmap *m_GlobalMask;
	COLORREF m_GlobalClrMask;
	
};

#endif