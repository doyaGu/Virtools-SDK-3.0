/***************************************************************************
File: Ge2Virtools.h

Author:  Romain Sididris - Virtools 2000 

Class Definition

This file defines a set of helper classes that can be use when dealing with 
exporter/importer to Virtools Format. 

The Export2Virtools class contains methods to help you generate Virtools objects
and store them in a database. Each created can be assigned a key (void*)
to retrieve it afterward.

+ The Virtools mesh format has some constraints about vertex format :
one normal,color/uv per vertex and use triangle faces only, so you may also
find useful the VirtoolsTransitionMesh class which can be used to construct
a mesh without these limitations (Any number of normals/colors/uv per vertex)
and polygon face.

  Virtools SDK 														 	 
  Copyright (c) Virtools 2000, All Rights Reserved.					 	
***************************************************************************/
#ifndef GENERICEXPORT_H
#define GENERICEXPORT_H

// Declare the generic structures for Import/Export.
#include "CKAll.h"


#define MAX_UVCHANNEL_COUNT 8

//------------- Type Definitions ---------------------

typedef XArray<int> IntArray;
class Export2Virtools;
// Hash table definitions

// Hash Tables (Key -> Object )
typedef XHashTable<CKObject*,void*> XObjectHashTable;			
typedef XHashTable<CKObject*,void*>::Iterator XObjectHashTableIt;		
typedef XHashTable<CKObject*,void*>::Pair XObjectHashTablePair;	
// Hash Tables (Key -> int)
typedef XHashTable<int,void*> XIntHashTable;			
typedef XHashTable<int,void*>::Iterator XIntHashTableIt;		
typedef XHashTable<int,void*>::Pair XIntHashTablePair;	
// Hash Tables (texture filename -> texture)
typedef XHashTable<CKTexture*,XString> XTextureHashTable;			
typedef XHashTable<CKTexture*,XString>::Iterator XTextureHashTableIt;		
typedef XHashTable<CKTexture*,XString>::Pair XTextureHashTablePair;

// Triangle indices
class TriIndices {
public:
	int idx[3];
	TriIndices() { idx[0]=idx[1]=idx[2]=0; }
	TriIndices(int a,int b,int c) {	idx[0]=a;	idx[1]=b; 	idx[2]=c; }
};

// The same with a pointer to the CKMaterial which gives
// the color/lighting properties of the face
class TriFace: public TriIndices {
public:
	CKMaterial* material;
	TriFace():material(NULL) { }
	TriFace(int a,int b,int c,CKMaterial* mat):TriIndices(a,b,c),material(mat) {}
};

/***************************************************************************
VirtoolsVertex
 Transition class for constructing vertices.
 This class is used internally by the exporter when generating meshes but 
 can be useful when dealing with morph animations.
***************************************************************************/
class VirtoolsVertex {
public:
	VxVector Pos;						// Vertex Position
	VxVector Norm;						// Vertex Normal
	VxColor  Col;						// Vertex Color
	VxUV	 Uvs[MAX_UVCHANNEL_COUNT];	// Vertex Texture coordinates

// These are different indices of the position,normal and color in 
// the source format (that is in the m_Vertices,m_Normals,m_VertexColors
// array sof VirtoolsTransitionMesh class)
	int	OriginalPosIndex;						// -1 if invalid	
	int	OriginalNormIndex;						//  " "     "
	int OriginalColIndex;						//  " "     "
	int OriginalUvIndex[MAX_UVCHANNEL_COUNT];	//  " "     "
// This is the index of the vertice in NbFace*3 array (used internally)
	int FlatIndex;
// If this vertex is equal to an existing vertex => Index of the this 
// vertex or -1 (used internally)
	int ReAssign;
};


/*****************************************************************************
VirtoolsTransitionMesh
 Helper class for building geometry mesh. Virtools forces the mesh to have only
 1 texture coordinate and  1 normal or color per vertex and triangle faces.
 This class will help you convert from other formats where a vertex can have 
 more than one normal per vertex or polygon faces.

 Usage :
 - Create a VirtoolsTransitionMesh with a pointer to the Export2Virtools interface
   and specify if it should be prelit (vertex color ) or not (using normals)
  
 - Fill information about geometry using the 
   AddPosition,AddNormal,AddVertexColor and AddUv methods

 - Fill face data. A face is a set of 3 or more indices to the previous tables.
   If the incoming format is similar to Virtools and already ensures one 
   normal/color/uv per vertex use the same indices for AddFace and AddUVFace/
   AddNormalFace/AddColorFace. 

 - Call GenerateVirtoolsData which will generate the m_VirtoolsVertices and m_VirtoolsFaces
   arrays. In the general cases you won't have to access these arrays.

 - You can add the generated mesh to the exporter database with the 
   Export2Virtools::AddMesh(...) method

 - When dealing with morph animations you may avoid to regenerate a transition mesh
   for a morph key by only updating the source arrays (m_Vertices,m_Normals)
   and call RefreshVirtoolsVerticesPosition(...) which will update the
   m_VirtoolsVertices array accordingly to the new positions.
  
/********************************************************************************/
class VirtoolsTransitionMesh {
public:
// Constructor
	VirtoolsTransitionMesh(Export2Virtools* exporter=NULL,BOOL PrelitMesh=FALSE):Exporter(exporter),m_ChannelCount(0),m_PrelitMesh(PrelitMesh) {}

//-- Reset all datas. Prelit Mode doesn't change
	void Reset();

//-- Filling geometry
	void AddPosition(VxVector& p)		{ m_Vertices.PushBack(p); }
	void AddNormal(VxVector& n)			{ m_Normals.PushBack(n); }
	void AddVertexColor(VxColor& c)		{ m_VertexColors.PushBack(c); }
	void AddUv(VxUV& uv,int channel=0)	{ m_Uvs[channel].PushBack(uv); }
//-- Faces...
	void AddFace(int* indices,int indexcount,CKMaterial* m);
	void AddFace(int index1,int index2,int index3,CKMaterial* m);
	void SetFaceMaterial(int index,CKMaterial* m) { m_Faces[index].material = m; }

	void AddUVFace(int* indices,int indexcount,int channel=0);
	void AddUVFace(int index1,int index2,int index3,int channel=0);
	void AddColorFace(int* indices,int indexcount);
	void AddColorFace(int index1,int index2,int index3);
	void AddNormalFace(int* indices,int indexcount);
	void AddNormalFace(int index1,int index2,int index3);


//-- Additionnal Materials (Multi-texture)
	void AddChannelMaterial(CKMaterial* m) { m_Channels.PushBack(m); }

// Construct arrays of Virtools Faces and Vertices
	BOOL GenerateVirtoolsData();
// Only recomputes vertices and normals ( GenerateVirtoolsData must have been called at least once...)
	BOOL RefreshVirtoolsVerticesPosition();
//
	const IntArray& GetGeneratedIndices(int OriginalVertexIndex) { return m_RemapIndices[OriginalVertexIndex]; }

//-- Source Data
	XArray<VxVector>	m_Vertices;					// List of Vertex positions
	XArray<VxVector>	m_Normals;					// List of normals
	XArray<VxColor>		m_VertexColors;				// List of vertex colors
	XArray<VxUV>		m_Uvs[MAX_UVCHANNEL_COUNT]; // List of texture coordinates per channel

	XArray<TriFace>		m_Faces;		// List of triangle faces
	XArray<TriIndices>	m_NormalFaces;	// There must be an equal number face for normals,uv and colors or none if not used;	
	XArray<TriIndices>	m_ColorFaces;	// ""
	XArray<TriIndices>	m_UVFaces[MAX_UVCHANNEL_COUNT];	
	
	XArray<CKMaterial*> m_Channels;
	
	BOOL				m_PrelitMesh;

//-- Generated Data
	XClassArray<IntArray>			m_RemapIndices;		// This array has the size of the given m_Vertices, 
														// and contains the list of generated indices for a given
														// original vertex.
	XClassArray<VirtoolsVertex>		m_VirtoolsVertices; // Array of vertex as used in Virtools (Pos,Normal,UV) 
	XArray<TriFace>					m_VirtoolsFaces;
	int								m_ChannelCount;

protected:
	BOOL CompVtx(const VirtoolsVertex& v1,const VirtoolsVertex& v2);
	Export2Virtools* Exporter;
};


/********************************************************************************
VirtoolsMaterial

 + Structure that hold all the available parameters for a CKMaterial
 Exporter can either use this structure to store all their parameters or
 directly used the appropriate CKMaterial methods. The default constructor
 sets all the members to their default value in Virtools so you can only setup your specific needs.
*******************************************************************************/
class VirtoolsMaterial {
public:
	VxColor		m_Diffuse;
	VxColor		m_Specular;
	VxColor		m_Ambient;
	VxColor		m_Emissive;
	float		m_SpecularPower;
	CKTexture*  m_Texture;
	
	BOOL			m_TwoSided;

	VXFILL_MODE		m_FillMode;
	VXSHADE_MODE	m_ShadeMode;

	BOOL			m_AlphaBlending;
	VXBLEND_MODE	m_SrcBlendFactor;
	VXBLEND_MODE	m_DstBlendFactor;
	BOOL			m_PerspectiveCorrection;

	VXTEXTURE_FILTERMODE	m_MinFilterMode;
	VXTEXTURE_FILTERMODE	m_MagFilterMode;
	VXTEXTURE_BLENDMODE		m_TextureBlendMode;

	VXCMPFUNC				m_ZFunc;
	BOOL					m_ZWriteEnable;

	VirtoolsMaterial();
};

//-----------------------------------------------//
#define FINDHASH(list,type)\
XObjectHashTableIt it=list.Find(Key);\
return  (it==list.End()) ? NULL : (type)*it;\

/********************************************************************************
Export2Virtools

This is the main utility class used to generate your data to Virtools format.

Usage:
   - Create your mesh,entity,material,etc...  using the Add(Object) methods. You
   may assign a key (a void* pointer) to the created object so you can access it later
   using the Get(Object)ByKey methods

   - You can create a global animation that will contain all the objects animations
   with CreateGlobalAnimation. 

   - Once all the objects have been createdyou can fill a CKObjectArray of objects
   to load/save with the GenerateObjects methods.

TODO : Utility functions for PatchMesh & Skin creation.
********************************************************************************/
class Export2Virtools {
friend class  VirtoolsTransitionMesh;
public:
	Export2Virtools(CKContext* context);
	BOOL				GenerateObjects(CKObjectArray* array,BOOL AnimationsOnly=FALSE);

//--- Geometry
	CKMesh*				AddMesh(VirtoolsTransitionMesh* mesh,const char* Name=NULL,void* Key=NULL,CKBOOL KeepTM=TRUE);
//--- TODO A transition Patch (with autosmooth)  to avoid giving the Edges and 	Vec control points
	CKPatchMesh*			AddPatchMesh(const char* Name=NULL,void* Key=NULL);

//--- Material & Textures
	CKMaterial*			AddMaterial(VirtoolsMaterial* mat,const char* Name=NULL,void* Key=NULL);
	CKTexture*			AddTexture(const char* TextureFileName,const char* Name=NULL,void* Key=NULL);
	CKTexture*			AddTexture(int Width,int Height,const char* Name=NULL,void* Key=NULL);

//--- 3D Entities
	CK3dEntity*			AddDummyObject(const char* Name=NULL,void* Key=NULL);
	CK3dEntity*			RegisterDummyObject(CK3dEntity* Dummy, void* Key=NULL);
	CKPlace*			AddPlace(const char* Name=NULL,void* Key=NULL);
	CK3dObject*			Add3dObject(const char* Name=NULL,void* Key=NULL);
	CKBodyPart*			AddCharacterBodyPart(const char* Name=NULL,void* Key=NULL);

	CKLight*			AddLight(BOOL Target,VXLIGHT_TYPE Type,const char* Name=NULL,void* Key=NULL, BOOL iCreateTarget=TRUE);
	CKCamera*			AddCamera(BOOL Target,const char* Name=NULL,void* Key=NULL, BOOL iCreateTarget=TRUE);

	CKCurve*			AddCurve(const char* Name=NULL,void* Key=NULL);
	CKCurvePoint*		AddCurvePoint(CKCurve* curve,const char* Name=NULL,void* Key=NULL);

//--- Animation	
	CKObjectAnimation*		AddObjectAnimation(CK3dEntity* AnimatedEntity,const char* Name=NULL,void* Key=NULL);
	void				AddObjectAnimation(CKObjectAnimation* anim,void* Key=NULL);


//---- Utilities
	CKGroup*			AddGroup(const char* Name=NULL,void* Key=NULL);
	CKKeyedAnimation*		CreateGlobalAnimation(const char* Name);	
	CKCharacter*			CreateCharacter(const char* Name);	
	void				SetCharacter(CKCharacter* character);	

//---- Created Object access (GetEntityByKey works for bodyparts,3DObjects,places and dummy)
	CK3dEntity* GetEntityByKey	(void* Key)	{  FINDHASH(m_Entities	,CK3dEntity*)	}
	CKMesh*		GetMeshByKey	(void* Key)	{  FINDHASH(m_Meshes	,CKMesh*)		} 
	CKMaterial*	GetMaterialByKey(void* Key) {  FINDHASH(m_Materials	,CKMaterial*)	}
	CKTexture*	GetTextureByKey	(void* Key)	{  FINDHASH(m_Textures	,CKTexture*)	}
	CKLight*	GetLightByKey	(void* Key)	{  FINDHASH(m_Lights	,CKLight*)		}
	CKCamera*	GetCameraByKey	(void* Key)	{  FINDHASH(m_Cameras	,CKCamera*)		}
	CKGroup*	GetGroupByKey	(void* Key)	{  FINDHASH(m_Groups	,CKGroup*)		}
	CKObjectAnimation*	GetObjectAnimByKey(void* Key)	{ FINDHASH(m_ObjectAnimations	,CKObjectAnimation*) }

	CKCharacter*		GetCharacter()					{ return  m_Character; } 
	CKKeyedAnimation*	GetGlobalAnimation()			{ return  m_GlobalAnimation; } 
	
	VirtoolsTransitionMesh*	GetTransitionMesh(void* Key){
		XIntHashTableIt it=m_TransitionMeshIndices.Find(Key);
		return  (it==m_TransitionMeshIndices.End()) ? NULL : &m_VirtoolsTmpMesh[*it];
	}
//---- If the created animations should be applied to existing objects or 
//---- to a specific character 
	void ResolveAnimationsTargets(CKCharacter *carac = NULL);

//----- Call this to set specific creation options
	void SetObjectsCreationOptions(CK_OBJECTCREATION_OPTIONS Options) { m_CreationOptions = Options; }

//---- Functions used to create scripts, add attributes, and modify local params
	BOOL Load( CKContext *ctx, char *fileName, CKObjectArray *m_GeneratedArray );
	BOOL AttachScript( CKBeObject *beo, char *scriptName );
	BOOL SetParam( CKBeObject *beo, char *paramName, char *strValue );
	BOOL SetAttribute( CKBeObject *beo, char *attributeName, char *strValue, char *strType, char *strCategory );

	void DestroyObject(CK_ID id);
	void DestroyObject(CKObject* obj) {DestroyObject(obj->GetID());};
		
protected:
//-- Created Objects
	XObjectHashTable			m_Entities,m_Meshes,m_Materials,m_Textures,
								m_ObjectAnimations,m_Lights,m_Cameras,m_Groups;
	XIntHashTable				m_TransitionMeshIndices;

//-- Hash table by filename
	XTextureHashTable			m_TextureByName;	

//-- Generated character and animation
	CKCharacter*				m_Character;
	CKKeyedAnimation*			m_GlobalAnimation;

//-- Generated List
	XObjectPointerArray			m_AllObjects;

//-- Internal Data
	XArray<VirtoolsVertex>				m_VerticesPool;
	CKContext*							m_Context;
	XObjectPointerArray					m_OAnimations;
	XObjectPointerArray					m_Bodyparts;
	XClassArray<VirtoolsTransitionMesh> m_VirtoolsTmpMesh;
//-- Creation options	
	CK_OBJECTCREATION_OPTIONS			m_CreationOptions;
};




#endif