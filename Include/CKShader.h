/*************************************************************************/
/*	File : CKShader.h													 */
/*	Author : Laurent Mascherpa											 */	
/*																		 */	
/*	Virtools SDK 														 */	 
/*	Copyright (c) Virtools 2003, All Rights Reserved.					 */	
/*************************************************************************/
#ifndef CKShader_H

#define CKShader_H "$Id:$"

#include "CKBeObject.h"

#ifdef _XBOX
	#undef CompileShader
#endif


#define ShaderManagerGUID	CKGUID(0xBA495345,0x5252B45F)


#define	SHADERMANAGER_CHUNKID		1

#define	FIRSTSHADER_CHUNKID			2

#define	SHADERMANAGER_SAVE_VERSION	2

#define	SHADERMANAGER_FLAGS			0

//-----------------------------------------------------------------------------
// Parameters GUID

#define CKPGUID_SHADER		CKGUID(0x66a07e01,0xe5c468d)

#define CKPGUID_TECHNIQUE	CKGUID(0x44af1e63,0x3c2c0d3e)

#define CKPGUID_PASS		CKGUID(0x2d0168dd,0x1622074f)


#define CKPGUID_TECHENUM	CKGUID(0x177b5e3c,0x248c262a)


class	CKShader;


typedef void (*CK_PROCESSCALLBACK)( void *Argument );

//-----------------------------------------------------------------------------
// Callback Struct


class CallbackStruct {
public:
	CallbackStruct(){};
	CallbackStruct( CK_PROCESSCALLBACK iCallBack, void* iArgument ){
		callBack = iCallBack;
		arg = iArgument;
	}
	CK_PROCESSCALLBACK callBack;
	void* arg;
};


/********************************************************************
Summary: Parameters that are automatically set when using a shader.

Remarks:
	When writing an Shader there are certains parameters that do not need to be set explicitly 
but are rather set automatically by the render engine. This enumeration gives the list of these
parameters.
See Also:CKShaderManager
********************************************************************/
enum	ShaderAutomaticParameter
{
	//--- Warning: If you want to add some SHARED automatics, put them above the
	///// the FXAP_WORLDVIEW enum, as this one is also use as the limit for shared
	///// automatics 
	FXAP_WVP,			// The World View Projection matrix 
	FXAP_WORLD,			// The World matrix
	FXAP_VIEW,			// The View matrix
	FXAP_PROJECTION,	// The Projection matrix
	FXAP_EYEPOS,		// The Position of the Eye 
	FXAP_WORLDVIEW,		// The World View matrix
	FXAP_VIEWPROJ,		// The View Projection matrix
	
	FXAP_TWVP,			// The Transposed World View Projection matrix 
	FXAP_TWORLD,		// The Transposed World matrix
	FXAP_TVIEW,			// The Transposed View matrix
	FXAP_TPROJECTION,	// The Transposed Projection matrix
	FXAP_TWORLDVIEW,	// The Transposed World View matrix
	FXAP_TVIEWPROJ,		// The Transposed View Projection matrix
	
	//--- Warning: Don't add anything here before making sure the 
	///// corresponding ShaderAutomaticInfo has been registered at
	///// begining of the ShaderManager (implementation).

	FXAP_DIFFUSE,		// The material diffuse color
	FXAP_EMISSIVE,		// The material emissive color
	FXAP_SPECULAR,		// The material specular color
	FXAP_AMBIENT,		// The material ambient color
	FXAP_POWER,			// The material specular power

	FXAP_TEXTURE,		// The material texture

	FXAP_TEXTURE0,		// The channel0 texture
	FXAP_TEXTURE1,		// The channel1 texture
	FXAP_TEXTURE2,		// The channel2 texture
	FXAP_TEXTURE3,		// The channel3 texture
	FXAP_TEXTURE4,		// The channel4 texture
	FXAP_TEXTURE5,		// The channel5 texture
	FXAP_TEXTURE6,		// The channel6 texture
	FXAP_TEXTURE7,		// The channel7 texture

	FXAP_OBJECTPOS,		// The entity 3d position	

	FXAP_TIME,			// The current time	in seconds

	FXAP_PASSCOUNT,		// The shader's pass count
	FXAP_PASSINDEX,		// The current rendering pass index

	FXAP_BONES,			// The Bones Matrices
	FXAP_TBONES,		// The Transposed Bones Matrices
	FXAP_BONESPERVERTEX,// The Max Bones per Vertex
	FXAP_BONESINDEXCONSTANT, // DX8 Reserved vertex shader constant  
	FXAP_MAXSIZE
};

/****************************************************************
Summary: The shader/Shader manager:

Remarks:
+ The Shader shader manages the list of available Shaders which can be retrieve by name or index
(GetShaderByName,GetShader,GetNumShaders)
+ The BeginShaders/EndShaders methods must be called to setup the default render states (GetDefaultShader)
before any rendering using Shaders take place.
+ Finally the Shader manager also returns whether the currently set rasterizer supports
drawing object with Shaders (IsSupported,GetVSPSVersion) 
See Also:CKShader,CKMaterial 
****************************************************************/
class CKShaderManager :	public	CKBaseManager
{
public:
	
	CKShaderManager(CKContext *Context,CKGUID guid,CKSTRING Name)
		: CKBaseManager(Context,guid,Name),	m_DefaultShader(0)
#ifndef _XBOX		
		,	m_SavePreProcessed(false) 
#endif
	{}
	
	virtual ~CKShaderManager(){}

// Inherited From BaseManager
//---  Called before behavioral processing
	virtual CKERROR PreProcess();

//---  Called after behavioral processing
	virtual CKERROR PostProcess();

	virtual CKERROR PreClearAll();

//---  Returns list of functions implemented by the manager.
	virtual CKDWORD	GetValidFunctionsMask()	{
		return 	CKBaseManager::GetValidFunctionsMask() | 
			CKMANAGER_FUNC_PreProcess|
			CKMANAGER_FUNC_PostProcess|
			CKMANAGER_FUNC_PreClearAll;
	}	

	
/******************************************************************
Summary: Returns whether current rasterizer support Shaders.
Remarks:
	Currently only DX9 rasterizer is Shader capable.
*******************************************************************/	
	virtual	CKBOOL		IsSupported() const = 0;
	virtual	CKBOOL		IsSupportedAndWarnIfNot()=0;
	
/*******************************************************************
Summary: Returns a CKShader given its name.
*******************************************************************/
	virtual CKShader*	GetShaderByName(const XBaseString& name) = 0;
/*******************************************************************
Summary: Returns the default CKShader.
Remarks:
	The default CKShader contains the list of default render states to 
set on the rasterizer before rendering any object using Shaders.
*******************************************************************/
	virtual	CKShader*	GetDefaultShader() = 0;
/********************************************************************
Summary:Setups the default renderstates before rendering objects with Shaders.
*********************************************************************/
	virtual void		BeginShaders( CKRenderContext* rc ) = 0;

	virtual void		EndShaders( CKRenderContext* rc ) = 0;
/********************************************************************
Summary:Gets the version of the Vertex Shader(vs) and Pixel Shader(ps) support.
*********************************************************************/
	virtual	void		GetVSPSVersion(float& vs, float& ps) const = 0;
/********************************************************************
Summary:Returns the number of existing Shaders.
*********************************************************************/
	virtual int			GetNumShaders() const = 0;
/********************************************************************
Summary:Returns an Shader given its index.
*********************************************************************/
	virtual CKShader*	GetShader(int pos) = 0;


	virtual CKShader*	CreateShader(
		const XString* name = NULL, 
		const XString* text = NULL, 
		BOOL uniqueName		= TRUE )=0;

	virtual	void		DeleteShader(CKShader* fx)=0;
	virtual CKShader*	CreateShaderFromFile(const CKSTRING filename)=0;
	virtual void		SaveShaderToFile(const XString& filename, CKShader* fx)=0;
	virtual bool		CompileShader(CKShader* fx, XClassArray<XString> &output)=0;
	virtual bool		CompileShaderOutput(CKShader* fx, const CKSTRING funcname, 
		const CKSTRING target, XClassArray<XString> &output, XString& text)=0;

	

/*******************************************************************
Summary: Set/Get a registered automatic name.
Remarks: index must be smaller than FXAP_MAXSIZE and greater 
         or equal to 0.
		 The SetRegAutomaticName method should be called to define 
		 the name of all registered automatic params at init of the
		 shader manager.
*******************************************************************/
	virtual void SetRegAutomaticName( ShaderAutomaticParameter index, const XString& iName ) = 0;
	virtual XString& GetRegAutomaticName( ShaderAutomaticParameter index ) = 0;
	virtual XString& GetRegAutomaticDesc( ShaderAutomaticParameter index ) = 0;

/*******************************************************************
Summary: Called when a RenderContext gets created or destroyed
		 to update the Shader Manager's inner list of render contexts		
*******************************************************************/
	virtual void OnRenderContextCreated( CKRenderContext* rc ){};
	virtual void OnRenderContextDestroyed( CKRenderContext* rc ){};


/*******************************************************************
Summary: Allows to perform preprocessing on the fx text before saving
*******************************************************************/
#ifndef _XBOX
	virtual void SetSavePreProcessed(bool preProc);
	virtual void SetSavePreprocessOptions(const char* preProcOptions);
#endif

/*******************************************************************
Summary: Add temporary post/pre render callback (used by shader BBs)
*******************************************************************/
	void AddTemporaryPreProcessCallBack( CK_PROCESSCALLBACK Function,void *Argument);
	void AddTemporaryPostProcessCallBack( CK_PROCESSCALLBACK Function,void *Argument);
	
/*******************************************************************
Summary: Manage the Technique Enum Type
*******************************************************************/
	void	RebuildTechniqueEnum( CKShader* shader );

/*******************************************************************
Summary: Parse all materials and update params if it use the shader
*******************************************************************/
	void MakeParamsUpToDateForAllConcernedMaterials( CKShader* shader );
	
public:
	CKShader*				m_DefaultShader;
	XArray<CKShader*>		m_AllShaders;
	XClassArray<XString>	m_Output;

#ifndef _XBOX
	bool				m_SavePreProcessed;
	XString				m_SavePreprocessedOptions;
#endif

protected:
	
	void _ExecuteAndRemoveTemporaryCallBacks( XArray<CallbackStruct>& cbs );
	
	XArray<CallbackStruct>	m_PreProcessCallBackStruct;
	XArray<CallbackStruct>	m_PostProcessCallBackStruct;

};

/***********************************************************************
Summary: Shader Class.

Remarks:
	The CKShader class holds the description of an Shader 

See also: CKShaderManager
***********************************************************************/
class	CKShader
{
public:
	CKShader(){
		m_ShaderText = "// Shader";
	};
	
	virtual ~CKShader(){}
	
	/********************************************************
	Summary: Pass Description
	Remarks:
	  A technique can be using several passes to 
	*********************************************************/
	class	Pass
	{
	public:
		Pass(){}
		Pass( int rcCount ){
			handle.Resize( rcCount );
			handle.Fill( NULL );
		}
		XString			name;			// Name given to this pass
		XString			desc;			// Description of the pass
		DWORD			options;		// 
		XArray<void*>	handle;			// Implementation specifichandle per render context
	};

	/*********************************************
	Summary:Description of a technique
	***********************************************/
	class	Technique
	{
	public:
		Technique(){}
		Technique( int rcCount ){
			handle.Resize( rcCount );
			handle.Fill( NULL );
		}
		XString				name;		// Name of the technique
		XString				desc;		// Description
		DWORD				options;		
		XArray<void*>		handle;		// Implementation specific Handle per render context
		XClassArray<Pass>	passes;		// Array of passes required to achieve this technique
		XArray<DWORD>		pubpasses;	
	};
	

/****************************************************************
Summary:Applies a Shader settings before rendering an object using the currently  set technique.
*****************************************************************/
	virtual int		Begin( CKRenderContext* rc ) = 0;
/****************************************************************
Summary:Applies the settings of a given pass of a technique.
Remarks:
	This method is intented to be used iteratively for each pass of a technique. If only a
single pass is to be used SetPassDirect should be preferred.
See Also:SetPassDirect
*****************************************************************/
	virtual void	SetPass( CKDWORD Num, CKRenderContext* rc ) = 0;
/****************************************************************
Summary:Applies the settings of a given pass of a technique.
Remarks:
	This method is intented to be used when only a single pass of a technique is to be called.
See Also:SetPass
*****************************************************************/
	virtual void	SetPassDirect( CKDWORD Num, CKRenderContext* rc ) = 0;
/****************************************************************
Summary:Ends the application of a technique .
*****************************************************************/
	virtual void	End( CKRenderContext* rc ) = 0;

/****************************************************************
Summary:Sets the technique to use when applying this Shader.
*****************************************************************/
	virtual void	SetTechnique(const XString &str) = 0;
	virtual void	SetTechnique(const Technique* tech) = 0;

	virtual bool	FindNextValidTechnique(XString& tech) const = 0;
	virtual bool	IsTechniqueOf(const XString &str) const = 0;
	virtual CKBOOL	IsSupported() const = 0;
	
	// Techniques/Pass enumeration
//	virtual	CKGUID			GetTechniqueEnum() const = 0;
	virtual int				GetTechniqueEnumValue(const XString& name) const = 0;
	virtual const XString&	GetTechniqueEnumString(int num) const = 0;
	virtual bool	GetPass(const Technique* tech, const char* name, int& pos) const = 0;

	// Parameters creation
	virtual void	SetParameters(const XArray<CKParameterLocal*>& params) = 0;
	// Returns true if it has changed the technique.
	virtual bool	LinkTechnique(int& CompID, const XString& tech, BOOL fnvt, Technique*& outtech) = 0;
	// Returns true if it has changed the parameters.
	virtual bool	LinkParameters(int& CompID, XArray<CKParameterLocal*>& params, CKBOOL cleanup = FALSE) = 0;


	/***********************************************************
	Summary: Returns the list of techiniques for this Shader.
	***********************************************************/
	const XClassArray<Technique>	&GetTechniques() const
	{ return m_Techniques; }

	
	/***********************************************************
	Summary: Sets the entire Shader text.
	***********************************************************/
	void SetText(const XString& Text){ 
		m_ShaderText = Text; 
	}
	/***********************************************************
	Summary: Gets the entire Shader text.
	***********************************************************/
	const XString& GetText() const{ 
		return m_ShaderText; 
	}


	XClassArray<Technique>	m_Techniques;

	XString			m_ShaderText;


	/************************************************************
	Summary: Annotations
	*************************************************************/
	enum	Options
	{
		FXOPT_NONE			= 0x00000000,
		FXOPT_RESERVED		= 0x00000001,		// On tech, pass
		FXOPT_USAGE2D		= 0x00000002,		// On tech
		FXOPT_ONENTITY		= 0x00000004,		// On param
		FXOPT_SKIPOCCLUSION = 0x00000008,		// On tech
		FXOPT_VALID			= 0x00000010,		// On tech
		FXOPT_ISTEXELSIZE	= 0x00000020,		// On float2 param
		FXOPT_VECTOR4		= 0x00000040		// On float4 param
	};

	/************************************************************
	Summary: Description of the kind of parameter used in a Shader.
	*************************************************************/
	enum	ParamType 
	{
		INVALID=0,
		
		AUTOMATIC,	// Parameter is global and automatically set by the render engine 
		NORMAL,		// Parameter is stored per material (must be set on each material that use the Shader) 	
//		ONENTITY,	// Parameter is stored per entity (must be set on each entity that use the Shader)
		TEXELSIZE,	// Parameter is the texel size of previous texture (just above)

		TYPECOUNT
	};

	/*********************************************************
	Summary: Description of a parameter as used in a Shader.
	***********************************************************/
	struct  ParamInfo
	{
		ParamType 	type;	// Type of parameter (automatic,per material, per entity.)
		XString		name;	// Name of the parameter
		CKGUID		guid;	// Type of data stored (matrix, vector, color, array, etc.)
		CKGUID		guid2;	// Type of data stored in array (matrix, vector, color, etc.)		
	};

	/*********************************************************
	Summary: Returns the number of parameters used in this Shader.
	***********************************************************/
	virtual int		GetParameterCount( CKRenderContext* rc ) = 0;
	/*********************************************************
	Summary: Returns the description of a parameter given its index.
	***********************************************************/
	virtual void	GetParameterInfo( int paramIndex, ParamInfo& paramInfo, CKRenderContext* rc ) = 0;

	/*********************************************************
	Summary: Tells whether a Automatic parameter is used in this shader or not
	***********************************************************/
	virtual BOOL IsAutomaticUsed( ShaderAutomaticParameter index ) = 0;

	/*********************************************************
	Summary: Give a value to one of the shader's automatics
	***********************************************************/
	virtual void SetAutomaticValue( ShaderAutomaticParameter index, const void* valueBuffer, CKRenderContext* rc, CKDWORD iSize = 0) = 0;
	virtual void SetAutomaticValueTexture( ShaderAutomaticParameter index, CKTexture* iTex, CKRenderContext* rc ) = 0;

	virtual void ComputeTexelSizes( CKRenderContext* rc ) = 0;

	/*********************************************************
	Summary: Retrieve Input Stream Format
	***********************************************************/
	enum StreamParamUsage 
	{
		FXINPUTSTREAM_POSITION = 0,
		FXINPUTSTREAM_BLENDWEIGHT,   // 1
		FXINPUTSTREAM_BLENDINDICES,  // 2
		FXINPUTSTREAM_NORMAL,        // 3
		FXINPUTSTREAM_PSIZE,         // 4
		FXINPUTSTREAM_TEXCOORD,      // 5
		FXINPUTSTREAM_TANGENT,       // 6
		FXINPUTSTREAM_BINORMAL,      // 7
		FXINPUTSTREAM_TESSFACTOR,    // 8
		FXINPUTSTREAM_POSITIONT,     // 9
		FXINPUTSTREAM_COLOR,         // 10
		FXINPUTSTREAM_FOG,           // 11
		FXINPUTSTREAM_DEPTH,         // 12
		FXINPUTSTREAM_SAMPLE,        // 13
	};
	struct StreamParam 
	{
		unsigned int usage;				// Stream Param's Usage
		WORD usageIndex;		// Stream Param's Usage Index
		WORD size;				// Stream Param's Size (DWORD count... float=1, uvw=3...)
	};

	inline XArray<StreamParam>& GetInputStreamFormat(){ return m_InputStreamFormat; };

public:
	void SetName(const XString& Name)
	{
		m_ShaderName = Name;
	}
	virtual	const XString&	GetName() const
	{
		return m_ShaderName;
	}

protected:
	XString			m_ShaderName;
	XArray<StreamParam> m_InputStreamFormat;
};

#endif	//	CKShader_H
