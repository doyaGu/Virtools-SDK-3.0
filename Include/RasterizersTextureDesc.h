/*************************************************************
Common to all rasterizer :
*************************************************************/


/*************************************************************************************
Texture Flags (pixel format, hints, special)	
*************************************************************************************/
typedef enum CKRST_TEXTUREFLAGS {
	CKRST_TEXTURE_VALID				= 0x00000001,	
	CKRST_TEXTURE_COMPRESSION		= 0x00000004,	// Compressed (DXTn ) texture
	CKRST_TEXTURE_MANAGED			= 0x00000080,	// Rasterizer handle memory managment of the texture (system - agp - video)
	CKRST_TEXTURE_HINTPROCEDURAL	= 0x00000100,	// Hint : This texture is likely to be frequently changed and loaded to video memory
	CKRST_TEXTURE_HINTSTATIC		= 0x00000200,	// Hint : This texture is likely to stay the same for a long time
	CKRST_TEXTURE_SPRITE			= 0x00000400,	// Not a texture => sprite (not pow2 conditionnal)
	
	CKRST_TEXTURE_RGB				= 0x00000800,	// Color Texture 
	CKRST_TEXTURE_ALPHA				= 0x00001000,	// Alpha information

	CKRST_TEXTURE_CUBEMAP			= 0x00002000,	// Cube map texture 
	CKRST_TEXTURE_BUMPDUDV			= 0x00004000,	// Bump map texture 
	CKRST_TEXTURE_FORCEPOW2			= 0x00008000,	// {secret} software rasterizer : Force Pow2 condition
	CKRST_TEXTURE_HINTCOLORKEY		= 0x00010000,	// {secret} software rasterizer : Hint : This sprite/texture is using color key
	CKRST_TEXTURE_HINTALPHAONE	    = 0x00020000,	// {secret} software rasterizer : Hint : This sprite/texture alpha is all white
	CKRST_TEXTURE_RLESPRITE		    = 0x00040000,	// {secret} software rasterizer : This sprite/texture transparent part are compressed (RLE)
	

	CKRST_TEXTURE_RENDERTARGET		= 0x10000000	// This texture is used as render target, format is forced by its render context 
} CKRST_TEXTUREFLAGS;

/**************************************************************
//--- Texture Object description structure
***************************************************************/
struct CKTextureDesc : public VxPoolObject
{
	CKDWORD			Flags;				// CKRST_TEXTUREFLAGS
	VxImageDescEx	Format;				// Width/Height/bpp etc...
	CKDWORD			MipMapCount;		// Number of mipmap level in the texture
	CKTextureDesc():Flags(0),MipMapCount(0) {}
	virtual ~CKTextureDesc() {}
};

/*******************************************************************
Sprites can be implemented as a set of square sub textures
This structure holds the position and size of such a sub texture
*******************************************************************/
struct CKSPRTextInfo {
	CKDWORD IndexTexture; // Texture object
	short int x;		//	Position
	short int y;		//		"
	short int w;		//	Size in the sprite
	short int h;		//  "    "
	short int sw;		//	Real texture size
	short int sh;		//   "    "
};


/*************************************************************
Sprite description structure
A sprite is in fact a set of pow2 textures...
************************************************************/
struct CKSpriteDesc: public CKTextureDesc {
	XArray<CKSPRTextInfo>	Textures;	// Sub textures making this sprite and their placement
	CKRasterizer*			Owner;		// 	
	DWORD					ModulateColor;		// New : Sprites that support modulation
	virtual ~CKSpriteDesc();
};

/***********************************************************
DIRECTX 8.1
************************************************************/
/*******************************************
 A texture object for DX8 : contains the
 texture surface pointer
*********************************************/
typedef struct CKDX8TextureDesc : public CKTextureDesc 
{
public:
	union {
		LPDIRECT3DTEXTURE8		DxTexture;
		LPDIRECT3DCUBETEXTURE8	DxCubeTexture;
	};
//----- For render target textures...
	LPDIRECT3DTEXTURE8		DxRenderTexture;
//----- For non managed surface to be locked (DX8 does not support direct locking anymore)
	LPDIRECT3DSURFACE8		DxLockedSurface;
	DWORD					LockedFlags;
public:
	CKDX8TextureDesc() { DxTexture=NULL; DxRenderTexture=NULL; DxLockedSurface = NULL;}
	~CKDX8TextureDesc() { 
		SAFERELEASE(DxTexture);
		SAFERELEASE(DxRenderTexture);
		SAFERELEASE(DxLockedSurface);
	}
} CKDX8TextureDesc;

/***********************************************************
DIRECTX 7
************************************************************/

/*******************************************
 A texture object for DX7 : contains the
 texture surface pointer
*********************************************/
typedef struct CKDX7TextureDesc : public CKTextureDesc 
{
public:
	LPDIRECTDRAWSURFACE7 DxSurface;			//
	LPDIRECTDRAWSURFACE7 DxRenderSurface;	// If texture is used to be rendered too...
	CKDX7TextureDesc() { DxSurface=NULL; DxRenderSurface = NULL; }
	~CKDX7TextureDesc() { 
		DetachZBuffer();
		SAFERELEASE(DxSurface); SAFERELEASE(DxRenderSurface);
	}
	void DetachZBuffer() {
		if (DxSurface) DxSurface->DeleteAttachedSurface(0,NULL);
		if (DxRenderSurface) DxRenderSurface->DeleteAttachedSurface(0,NULL);

	}
} CKDX7TextureDesc;

/***********************************************************
DIRECTX 5
************************************************************/


/*************************************************
 Overload of the CKTextureDesc struct for DirectX 5
**************************************************/
typedef struct CKDX5TextureDesc : public CKTextureDesc 
{
public:
	LPDIRECTDRAWSURFACE3 DxSurface;			// Direct Draw Surface 
	LPDIRECTDRAWSURFACE3 DxRenderSurface;	// Direct Draw Surface when rendering to texture
	D3DTEXTUREHANDLE	 DxHandle;			// D3D texture handle
	D3DTEXTUREHANDLE	 DxRenderHandle;	
	CKDX5TextureDesc() { DxHandle=0; DxSurface=NULL; DxRenderHandle=0; DxRenderSurface = NULL; }
	~CKDX5TextureDesc() { 
		if (DxRenderSurface) {
			// In case a Z-buffer was attached to these surfaces...
			DxSurface->DeleteAttachedSurface(0,NULL);
			DxRenderSurface->DeleteAttachedSurface(0,NULL);
		}
		SAFERELEASE(DxSurface);
		SAFERELEASE(DxRenderSurface); }
} CKDX5TextureDesc;

/***********************************************************
OPENGL
************************************************************/

//---------------------------------------------
// Texture parameter as set by glTexParameter()
// that are unique to each texture object 
// need to keep track of these as they may invalidate the 
// texture stage states cache
typedef struct CKGLTexParameter {
	CKDWORD BorderColor;
	CKDWORD MinFilter;
	CKDWORD MagFilter;
	CKDWORD AddressU;
	CKDWORD AddressV;
	CKGLTexParameter() {
		MinFilter = MagFilter = AddressU = AddressV = 0xFFFFFFFF;
		AddressU =  AddressV = 0;
	}
} CKGLTexParameter;

//---------------------------------------------
// Video memory of a texture can not be locked directly 
// instead we can copy it to a system memory surface
// and return the pointer to the user...
typedef struct CKGLTexLockData {
	VxImageDescEx	Image;
	VxMemoryPool	ImageMemory;
	DWORD			LockFlags;
} CKGLTexLockData;

/*******************************************
 A texture object for OpenGL : contains a cache
 for its attribute (Blend,Filter,etc...) and 
 the index the texture is binded to...
*********************************************/
typedef struct CKGLTextureDesc : public CKTextureDesc 
{
public:
	CKGLTexParameter TexParam;
	int	 GlTextureIndex;
	CKGLTexLockData* LockData; 
public:
	CKGLTextureDesc() { LockData = NULL; GlTextureIndex=-1;  }
	~CKGLTextureDesc() { GlTextureIndex=-1; }
} CKGLTextureDesc;