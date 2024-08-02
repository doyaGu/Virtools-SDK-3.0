/*************************************************************************/
/*	File : CK3dPointCloud.h												 */
/*	Author : Romain Sididris											 */	
/*																		 */	
/*	Virtools SDK 														 */	 
/*	Copyright (c) Virtools 2003, All Rights Reserved.					 */	
/*************************************************************************/
#if (!defined(CK3DPOINTCLOUD_H) || defined(CK_3DIMPLEMENTATION))

#define CK3DPOINTCLOUD_H "$Id:$"
// When included from the implementation side the
// sub includes,  PURE definition and class  statement must to be removed


#ifndef CK_3DIMPLEMENTATION


/***********************************************************
Summary: An iterator to iterate on a cloud of points.
{filename:CloudIterator}
Remarks:
An iterator can be returned by different CK3dPointCloud methods:

It can be used to iterate the octree that is used to store the data. 
This tree is made up of node that contain up to 8 children nodes  

+ For simple iteration in the tree, One can ask an iterator from the tree root node (See CK3dPointCloud::GetRootIterator)
and then iterate using Depth first (NextNode) or custom (ToChildByIndex) iteration.

+ A selection of points can be computed using CK3dPointCloud::SelectSphere , CK3dPointCloud::SelectBox,etc. methods. 
These methods returns an iterator which can then be used with NextPoint to iterate on all the selected points.

Warning: Only a single iterator should be created at a time on a single CK3dPointCloud.

See Also:CK3dPointCloud
************************************************************/
class CloudIterator {
public:
//Summary: Return TRUE if the iterator is on a tree node.
//
	virtual XBOOL IsNode() = 0;	
//Summary: Return TRUE if the iterator is on a tree leaf.
//
	virtual XBOOL IsLeaf() = 0;	
//Summary: Return the current node bounding box in cloud local coordinates (as visible in the 3D view).
//
	virtual void  GetBox(VxBbox& oBox) = 0;	
//Summary: Return the current node bounding box in cloud local coordinates (as in the original .asc file).
//
	virtual void  GetRealBox(VxBbox& oBox) = 0;	

//--- Linear iteration (depth first or width first)

//Summary: Advance the iterator to the next element (node or leaf) in a Depth First order.
//
	virtual XBOOL NextNode() = 0;	
//Summary: Advance the iterator to the next point
//
	virtual XBOOL NextPoint() = 0;

//--- Node iteration

//Summary: Move this iterator back the parent node
//Return Value: TRUE if sucessful, FALSE if there the iterator is on tree root.
//
	virtual XBOOL	ToParent() = 0;	
//Summary: Return the number of children of the current node
//
	virtual int		GetChildrenCount() = 0;	
//Summary: Advance the iterator down to the iChildIndex children
//Return Value: TRUE if sucessful, FALSE if no child exist.
//
	virtual XBOOL	ToChildByIndex(int iChildIndex) = 0;	
	
//Summary: Return if a child exists for one of the 8 possible branches of a node.
//
	virtual XBOOL IsChildHere(int iBranchIndex) = 0;	
//Summary: Advance the iterator down to a children given its position in the 8 possible branches.
//Return Value: TRUE if sucessful, FALSE if no child exist.
//
	virtual XBOOL ToChildByBranch(int iBranchIndex) = 0;	

//Summary: Returns the position of the currently iterated point (as visible in the 3D view).
//
	virtual VxVector GetCurrentPointPosition() = 0;	
//Summary: Returns the position of the currently iterated point (as it was stored in the .asc file).
//
	virtual VxVector GetCurrentPointRealPosition() = 0;	
//Summary: Returns the global index of the currently iterated point.
//
	virtual int      GetCurrentPointIndex() = 0;	

};

/*******************************************************
Summary: Point Cloud rendering group.
Remarks:
The rendering of a point cloud can be partionned into
several rendering group to make selections appear differents.
The default is to place all the points in the same group (0).
The number of render group should be kept low for best perfomances.
See Also:CK3dPointCloud::GetRenderGroup,CK3dPointCloud::SetRenderGroup
*******************************************************/
struct CloudRenderGroup {
	CloudRenderGroup():Material(0),Visible(TRUE),UseSpriteRendering(FALSE),SpriteSize(1.0f),UseMaterialColor(FALSE) {}

	XString		Name;					// Name of the render group
	CKMaterial* Material;				// Material to use when rendering the points (color,texture and render states when using point sprite)
	BOOL		Visible;				// Is point belonging to this render group should be rendered
	BOOL		UseSpriteRendering;		// Render points as a single pixel point (FALSE) or as sprites (TRUE)
	float		SpriteSize;				// Summary: Size of the sprite in world coordinates.
										// Remarks: When displayed in sprite mode, this value will be scaled by the cloud global point size (CK3dPointCloud::GetGlobalPointSize)
	BOOL		UseMaterialColor;		// This can be use to force all the points to be displayed with the same color (Material diffuse)
};


/*******************************************************
Summary: Attributes on points
Remarks:
Every points can store attributes on it. By default 4 types of attribute are defined
(not necessarily used): A color , normal , intensity and render group.	
This attributes can be integer or float values. For integer the number of bits used to store
the value can be specified in the BitsPerValue member thus allowing efficient storage.
See Also:CK3dPointCloud
*******************************************************/
struct CloudAttributeDescription {
	
	CloudAttributeDescription():ValueType(ATTRIBUT_INT),BitsPerValue(0),ForAllPoints(TRUE) {}
	enum AttValueType {
		ATTRIBUT_INT	= 0,	// A int (with n bit per value) will be stored for each point		
		ATTRIBUT_FLOAT	,		// A float (32 bit)  will be stored for each point	
		ATTRIBUT_ENUM	,		// A enum (an integer) will be stored for each point, a string is associated with each value	
	};
	AttValueType	ValueType;			// Type of the value stored (integer,float or enum).
	XString			Name;				// Name of the attribute	
	XString			EnumDescription;	// Summary:Description for an enum type.
										// Remarks:When creating an "enum" or a "flag attribute (ATTRIBUT_ENUM), a string (eg. "Monday=1,Tuesday=2" ) that identifies the enumeration values as used in CKParameterManager::RegisterNewEnum
	int				BitsPerValue;		// Summary:Number of bits taken by the value
										// Remarks:This value is only used when using an ATTRIBUT_INT or ATTRIBUT_ENUM storage. If this not given (0) 32 bits will be used for each value.
	BOOL			ForAllPoints;		// TRUE : the attribut will be valid for all the cloud points , FALSE : the attribut is only valid for specific points... 
};

#include "CK3dEntity.h"


#undef CK_PURE

#define CK_PURE = 0


/***************************************************************************
{filename:CK3dPointCloud}
Name: CK3dPointCloud

Summary: Cloud of 3D points.
Remarks:
This class is used to manage and display clouds of 3D points.
These points are stored in a tree structure for efficient memory management and can have 
attribute attached like colors, normal or user defined attributes.

One of these attribute is called the render group (see GetPointRenderGroup). 
Points can be placed in different render group to have different render options 
(rendering as a sprite , size of this sprite , usage of a given material, etc..).

The class id of CK3dPointCloud is CKCID_3DPOINTCLOUD.

See also: CK3dEntity
***************************************************************************/
class CK3dPointCloud : public CK3dEntity {
#endif
public :

/***************************************************************
Summary: Default Point cloud attributes.
Remarks:
	This enumeration represents the attribute type that are always 
created for a 3D point cloud (which does not mean they are used)
*****************************************************************/
enum DefaultCloudAttribute {
	CLOUD_ATTRIBUTE_GROUP		 = 0,	// A render group information stored on 8 bits..
	CLOUD_ATTRIBUTE_COLOR		 = 1,	// Color information is stored as 16 bits color 
	CLOUD_ATTRIBUTE_NORMAL		 = 2,	// Normal information is stored as compressed on 10 bits
	CLOUD_ATTRIBUTE_INTENSITY	 = 3,	// An intensity stored on 8 bits 
};	

/************************************************************
Summary: Create the cloud using a .Asc file.

Remarks:
This method searches for a file named  iFileName.Desc in the same directory
than the iFileName file. 
This *.Desc* file contains the information about the number of points, bounding box, etc...
and its syntax is the following:

		Version 0
		Points 2399432
		Format 6
		Precision (0.110841,0.122853,0.114422)
		BoxMin (503847.437500,78931.140625,19900.824219)
		BoxMax (521581.968750,98587.679688,38208.335938)
		Translate (-512000,-88000,-29000)
		Rescale 0.05

No comments are allowed in a *.Desc* file for the moment....  
This information allows for a quick one-step processing of the .asc file. If the *.Desc* file is not found 
the file is loaded in a two-step process to identify the bounding volumes
The asc file is a text-mode file which contains a list of point and its syntax looks like this:

		10.0	11.0	 5.0
		8.002	13.15	 14.2
		etc...	

The data contained in a .asc file is expected to be in the form :
 X Y Z (floats) [R G B (0..255)] [NX NY NZ (floats)] [I(0..255)]

If the appropriate fields are found (color, normal and/or intensity) the relevant attribute types
are created and marked as used on the point cloud.
See Also: CreateFromPointList
*************************************************************/
virtual CKBOOL CreateFromAscFile(const char* iFileName) CK_PURE;

/************************************************************
Summary: Create the cloud using an array of points.

Arguments:
	iPointCount: Number of points in the iPoints array.
	iPoints: A point to the list of point in the cloud.
	iNormals: (Optionnal, can be NULL) A pointer to an array of VxVector containing the points normals.
	iColors: (Optionnal, can be NULL) A pointer to an array of DWORD containing the points colors (32 bit ARGB).
	iIntensities: (Optionnal, can be NULL) A pointer to an array of Bytes containing the points intensity.
	iPrecision: A vector containing the error that is acceptable between the value given in iPoints and the values that will get stored in the tree. 
Remarks:
This methods creates a new cloud using the data given in the different arrays.
Only the iPointCount, iPoints and iPrecision parameters are mandatory.
See Also: CreateFromAscFile
*************************************************************/
virtual CKBOOL CreateFromPointList(int iPointCount,VxVector* iPoints,VxVector* iNormals,DWORD* iColors,BYTE* iIntensities,VxVector& iPrecision) CK_PURE;

/****************************************************************
Summary: Enables or disables the lighting of the points

Input Arguments:
	iEnable: TRUE to set lighting on , FALSE to set it off.
Remarks:
	If the data set does not contain any normal information the 
lighting can not be enabled.
See Also: IsLightingEnabled,HasNormals
*****************************************************************/
virtual void   EnableLighting(CKBOOL iEnable = TRUE) CK_PURE;

/****************************************************************
Summary: Returns if the point are lit.

Remarks:
	If the data set does not contain any normal information the 
lighting can not be enabled.
See Also: EnableLighting,HasNormals
*****************************************************************/
virtual CKBOOL IsLightingEnabled()  const CK_PURE;

/****************************************************************
Summary: Sets the size factor for points drawn as sprites.

Remarks:
	This value is taken as a multiplication factor of the size of the 
point sprites.
	To be drawn as sprites a point must belong to a render group which rendering
is set to Sprite mode (see CloudRenderGroup).

See Also: SetRenderGroup,GetGlobalPointSize,CloudRenderGroup
*****************************************************************/
virtual void   SetGlobalPointSize(float iPointSize) CK_PURE;

/****************************************************************
Summary: Returns the size factor for points drawn as sprites.

Remarks:
	This value is taken as a multiplication factor of the size of the 
point sprites.
	To be drawn as sprites a point must belong to a render group which rendering
is set to Sprite mode (see CloudRenderGroup).

See Also: SetRenderGroup,SetGlobalPointSize,CloudRenderGroup
*****************************************************************/
virtual float  GetGlobalPointSize()  const CK_PURE;

// Number of points...
/****************************************************************
Summary: Returns the number of points stored.

Remarks:
See Also: GetMemorySize,GetVertexBufferCount,GetVertexBufferMemorySize
*****************************************************************/
virtual CKDWORD   GetPointsCount()  const CK_PURE;
/****************************************************************
Summary: Returns the memory taken to store all the points and their attributes.

Remarks:
See Also: GetPointsCount,GetVertexBufferCount,GetVertexBufferMemorySize
*****************************************************************/
virtual CKDWORD   GetMemorySize()  const CK_PURE;

/****************************************************************
Summary: Returns the number of vertex buffers allocated to display the cloud.

Remarks:
The number of vertex buffer that will be generated depends on the number of 
vertices that can be placed in a single vertex buffer. This value is controled 
by a global variable CK2_3D\CloudVerticesPerVB.
See Also: GetPointsCount,GetMemorySize,GetVertexBufferMemorySize
*****************************************************************/
virtual CKDWORD   GetVertexBufferCount()  const CK_PURE;
/****************************************************************
Summary: Returns the memory taken to store all the vertex buffers.

Remarks:
This method returns the size (in bytes) taken by all the currently allocated
vertex buffers to display the cloud.
See Also: GetPointsCount,GetVertexBufferCount,GetMemorySize
*****************************************************************/
virtual CKDWORD   GetVertexBufferMemorySize() const CK_PURE;


/****************************************************************
Summary: Returns the offset that was applied to all the points when loaded from a .asc file.

Remarks:
When loading from a .asc file an offset and scale factor can be applied to all the points 
if a *.Desc* was used. 
This scale factor and offset can be taken into account when accessing the point position with 
an iterator (see CloudIterator::GetCurrentPointPosition and GetCurrentPointRealPosition )
See Also: CreateFromAscFile, GetLoadScaleFactor
*****************************************************************/
virtual const VxVector&  GetLoadOffset() const CK_PURE;

/****************************************************************
Summary: Returns the scale factor that was applied to all the points when loaded from a .asc file.

Remarks:
When loading from a .asc file an offset and scale factor can be applied to all the points 
if a *.Desc* was used. 
This scale factor and offset can be taken into account when accessing the point position with 
an iterator (see CloudIterator::GetCurrentPointPosition and GetCurrentPointRealPosition )
See Also: CreateFromAscFile, GetLoadOffset
*****************************************************************/
virtual float   GetLoadScaleFactor() const CK_PURE;


//---------- Selection


/****************************************************************
Summary: Sets the position of the referential.

Remarks:
	This methods the referential of the cloud without actually moving the points
themselves. It is different from the CK3dEntity::SetPosition method which moves
the whole cloud.
*****************************************************************/
virtual void SetReferentialPosition(const VxVector& iPosition,CK3dEntity* iRef = NULL) CK_PURE;

/****************************************************************
Summary: Returns an iterator on the root of the tree.

See Also: CloudIterator,SelectSphere,SelectHalfSpace,SelectCylinder,RayPick
*****************************************************************/
virtual CloudIterator* GetRootIterator() CK_PURE;

/****************************************************************
Summary: Selects a list of points within a box.

Arguments:
	iBox: Axis aligned selection box given in the cloud local space.
	iOBox: Oriented selection box given in the cloud local space.
	iPutInRenderGroup: If >= 0 this value gives the render group in which the selected point should be put.	Default is -1, that is do not change the point render group.
Remarks:
	This method returns an iterator which can then be used to acces all the points 
that are inside the given box or NULL if no such point exists.
See Also: CloudIterator,SelectSphere,SelectHalfSpace,SelectCylinder,RayPick
*****************************************************************/
virtual CloudIterator* SelectBox(const VxBbox& iBox,int iPutInRenderGroup = -1) CK_PURE;
virtual CloudIterator* SelectBox(const VxOBB& iOBox,int iPutInRenderGroup = -1) CK_PURE;

/****************************************************************
Summary: Selects a list of points within a sphere.

Arguments:
	iSphere: Selection sphere given in the cloud local space.
	iPutInRenderGroup: If >= 0 this value gives the render group in which the selected point should be put.	Default is -1, that is do not change the point render group.
Remarks:
	This method returns an iterator which can then be used to acces all the points 
that are inside the given sphere or NULL if no such point exists.
See Also: CloudIterator,SelectBox,SelectHalfSpace,SelectCylinder,RayPick
*****************************************************************/
virtual CloudIterator* SelectSphere(const VxSphere& iSphere,int iPutInRenderGroup = -1) CK_PURE;

/****************************************************************
Summary: Selects a list of points on the positive side of a plane.

Arguments:
	iPlane: Selection plane given in the cloud local space.
	iPutInRenderGroup: If >= 0 this value gives the render group in which the selected point should be put.	Default is -1, that is do not change the point render group.
Remarks:
	This method returns an iterator which can then be used to acces all the points 
that are on the positive side of the given plane or NULL if no such point exists.
See Also: CloudIterator,SelectSphere,SelectBox,SelectCylinder,RayPick
*****************************************************************/
virtual CloudIterator* SelectHalfSpace(const VxPlane& iPlane,int iPutInRenderGroup = -1) CK_PURE;

//---------- Base Attributes -------

/****************************************************************
Summary: Returns if a normal is stored per point.

Remarks:
	This method is equivalent to calling IsCloudAttributeUsed(CLOUD_ATTRIBUTE_NORMAL).
	Normals must exist if lighting is to be enabled.
See Also: HasColors,UseNormals,GetPointNormal,IsCloudAttributeUsed
*****************************************************************/
virtual CKBOOL	  HasNormals() const CK_PURE;
/****************************************************************
Summary: Returns if a color is stored per point.

Remarks:
	This method is equivalent to calling IsCloudAttributeUsed(CLOUD_ATTRIBUTE_COLOR).
	If not color is stored per point, the default color is full white.
See Also: HasNormals,UseNormals,GetPointNormal,IsCloudAttributeUsed
*****************************************************************/
virtual CKBOOL	  HasColors() const CK_PURE;

/****************************************************************
Summary: Ensure memory is allocatd to store normals.

Remarks:
	This method is equivalent to calling UseCloudAttribute(CLOUD_ATTRIBUTE_NORMAL).
	This ensures that memory is allocated to store a normal for each point.
	A normal is compressed on 10 bits for efficiency purposes.
See Also: HasNormals,GetPointNormal,UseCloudAttribute
*****************************************************************/
virtual void	  UseNormals(CKBOOL iUseNormals) CK_PURE;

/****************************************************************
Summary: Ensure memory is allocatd to store colors.

Remarks:
	This method is equivalent to calling UseCloudAttribute(CLOUD_ATTRIBUTE_COLOR).
	This ensures that memory is allocated to store a color for each point.
	A color is stored internally as a 16 bit ARGB 1555 color.
See Also: HasColors,GetPointColor,UseCloudAttribute
*****************************************************************/
virtual void	  UseColors(CKBOOL iUseColors) CK_PURE;


/****************************************************************
Summary: Returns the color of a point.

Remarks:
	If there is no color stored in the cloud , the returned value is 0xFFFFFFFF.
See Also: HasColors,UseColor
*****************************************************************/
virtual DWORD	  GetPointColor(int iPointIndex) const CK_PURE;

/****************************************************************
Summary: Returns the normal of a point.

Remarks:
	If there is no normal stored in the cloud, the returned value is the vector (0,0,0) .
See Also: HasNormals,UseNormals
*****************************************************************/
virtual VxVector  GetPointNormal(int iPointIndex) const CK_PURE;

/****************************************************************
Summary: Returns the intensity of a point.

Remarks:
	If there is no intensity stored in the cloud, the returned value is 0.
	The intensity is a information stored on a byte (0..255) that was retrieved when reading 
a .asc file for example.
See Also: GetPointIntAttribute
*****************************************************************/
virtual int		  GetPointIntensity(int iPointIndex) const CK_PURE;

//----------- Render Groups ---------------
/****************************************************************
Summary: Returns the render group to which a point belongs.

Input Arguments:
	iPointIndex: Index of the point.
Remarks:
	A render group identify the rendering options that will be used to display
a point. All the points of a cloud can be dispatched in different groups that can later
be hidden , drawn as sprites, etc. (See the CloudRenderGroup for more details)
See Also: SetPointRenderGroup,GetRenderGroup,CloudRenderGroup
*****************************************************************/
virtual DWORD	  GetPointRenderGroup(int iPointIndex) const CK_PURE;

/****************************************************************
Summary: Sets the render group to which a point belongs.

Input Arguments:
	iPointIndex: Index of the point.
Remarks:
	A render group identify the rendering options that will be used to display
a point. All the points of a cloud can be dispatched in different groups that can later
be hidden , drawn as sprites, etc. (See the CloudRenderGroup for more details)
See Also: GetPointRenderGroup,GetRenderGroup,CloudRenderGroup
*****************************************************************/
virtual void	  SetPointRenderGroup(int iPointIndex,DWORD iRenderGroup) CK_PURE;

/****************************************************************
Summary: Returns the number of render groups on this cloud.

Remarks:
	A render group identify the rendering options that will be used to display
a point. All the points of a cloud can be dispatched in different groups that can later
be hidden , drawn as sprites, etc. (See the CloudRenderGroup for more details)
See Also: SetRenderGroupCount,RemoveRenderGroup,GetRenderGroup,CloudRenderGroup
*****************************************************************/
virtual int		  GetRenderGroupCount()  const CK_PURE;

/****************************************************************
Summary: Sets the number of render groups on this cloud.

Remarks:
	A render group identify the rendering options that will be used to display
a point. All the points of a cloud can be dispatched in different groups that can later
be hidden , drawn as sprites, etc. (See the CloudRenderGroup for more details)
See Also: GetRenderGroupCount,RemoveRenderGroup,GetRenderGroup,CloudRenderGroup
*****************************************************************/
virtual void	  SetRenderGroupCount(int iGroupCount) CK_PURE;

/****************************************************************
Summary: Deletes a render group from this cloud.

Remarks:
	A render group identify the rendering options that will be used to display
a point. All the points of a cloud can be dispatched in different groups that can later
be hidden , drawn as sprites, etc. (See the CloudRenderGroup for more details)
See Also: GetRenderGroupCount,GetRenderGroup,CloudRenderGroup
*****************************************************************/
virtual BOOL	  RemoveRenderGroup(int iGroupIndex) CK_PURE;

/****************************************************************
Summary: Returns the description and options of a render group.

Remarks:
	A render group identify the rendering options that will be used to display
a point. All the points of a cloud can be dispatched in different groups that can later
be hidden , drawn as sprites, etc. (See the CloudRenderGroup for more details)
See Also: GetRenderGroupCount,SetRenderGroup,CloudRenderGroup
*****************************************************************/
virtual const CloudRenderGroup&  GetRenderGroup(int iCode)  const CK_PURE;

/****************************************************************
Summary: Sets the description and options of a render group.

Remarks:
	A render group identify the rendering options that will be used to display
a point. All the points of a cloud can be dispatched in different groups that can later
be hidden , drawn as sprites, etc. (See the CloudRenderGroup for more details)
See Also: GetRenderGroupCount,GetRenderGroup,CloudRenderGroup
*****************************************************************/
virtual void	  SetRenderGroup(int iCode,const CloudRenderGroup& iGroup) CK_PURE;


//---------- User Attributes -------

/********************************************************************
Summary: Register a new type of attribute to use on the cloud. 

Arguments:
	iAttributeDesc: A CloudAttributeDescription that defines the attribute to create.
Remarks:
The CloudAttributeDescription structure identifies the type of data that will be stored (integer or float)
along with a description. 
An attribute can be stored on all points or only on a subset of points.

This function returns an index that can be later used to access data on points.
See Also:UnRegisterCloudAttribute,GetCloudAttributeIndexByName
*********************************************************************/
virtual int  	  RegisterCloudAttribute(const CloudAttributeDescription& iAttributeDesc) CK_PURE;

/********************************************************************
Summary: Removes an attribute type from the cloud. 

Arguments:
	iAttributeIndex: Index of the attribute to remove (Can be returned from a name with GetCloudAttributeIndexByName).
Remarks:
	The default attributes (Color,Normal,Intensity and render group) can not be removed.
Removing an attribute can change the indices that were attributed to all the user attribute.
See Also:RegisterCloudAttribute,GetCloudAttributeIndexByName
*********************************************************************/
virtual void  	  UnRegisterCloudAttribute(int iAttributeIndex) CK_PURE;

/********************************************************************
Summary: Returns an attribute type from the cloud given its name. 

Arguments:
	iName: Name of the attribute type which index should be returned.
Remarks:
See Also:RegisterCloudAttribute,UnRegisterCloudAttribute,GetCloudAttributeCount
*********************************************************************/
virtual int  	  GetCloudAttributeIndexByName(const XBaseString& iName)  const CK_PURE;

/********************************************************************
Summary: Returns the number of attribute types on the cloud. 

Remarks:
The default attributes (Color,Normal,Intensity and render group) can not be removed which means
there should be at least 4 default groups.
See Also:RegisterCloudAttribute,GetCloudAttributeIndexByName
*********************************************************************/
virtual int  	  GetCloudAttributeCount()  const CK_PURE;

/********************************************************************
Summary: Returns the description of an attribute type. 

Input Arguments:
	iAttributeIndex: Index of the attribute which description should be returned (Can be returned from a name with GetCloudAttributeIndexByName).
Remarks:
The 4 first attributes are the Color,Normal,Intensity and render group attributes.
The description of an attribute type gives the type of value stored on the points in the cloud. 
See Also:CloudAttributeDescription,SetCloudAttributeDescription,GetCloudAttributeIndexByName
*********************************************************************/
virtual const CloudAttributeDescription&   GetCloudAttributeDescription(int iAttributeIndex)  const CK_PURE;

/********************************************************************
Summary: Sets the description of an attribute type. 

Input Arguments:
	iAttributeIndex: Index of the attribute which description should be returned (Can be returned from a name with GetCloudAttributeIndexByName).
Remarks:
The 4 first attributes are the Color,Normal,Intensity and render group attributes.
The description of an attribute type gives the type of value stored on the points in the cloud.
See Also:CloudAttributeDescription,GetCloudAttributeDescription,GetCloudAttributeIndexByName
*********************************************************************/
virtual void	  SetCloudAttributeDescription(int iAttributeIndex,const CloudAttributeDescription& iDescription) CK_PURE;

/***********************************************************************
Summary: Returns whether a attribute type is used.

Remarks:
	Having an attribute defined on a cloud does not mean it is used. An attribute type must be marked 
as used with this method before points can hold data for this attribute.
Warning: When an attribute is marked as "non used" all the memory that was
used to store the point data is released, therefore switching back and forth to "used" - "not used"
will not keep the value initially stored on the points.
See Also:UseCloudAttribute
***********************************************************************/
virtual CKBOOL	  IsCloudAttributeUsed(int iAttributeIndex)  const CK_PURE;

/***********************************************************************
Summary: Sets the usage of a given attribute type.

Remarks:
	Having an attribute defined on a cloud does not mean it is used. An attribute type must be marked 
as used with this method before points can hold data for this attribute.
Warning: When an attribute is marked as "non used" all the memory that was
used to store the point data is released, therefore switching back and forth to "used" - "not used"
will not keep the value initially stored on the points.
See Also:IsCloudAttributeUsed
***********************************************************************/
virtual void	  UseCloudAttribute(int iAttributeIndex,BOOL iUse) CK_PURE;


/***********************************************************************
Summary: Returns whether a point is holding a given attribute value.

Input arguments:
	iPointIndex: Index of the point (0..GetPointsCount()).
	iAttributeIndex: Index of the attribute type to check the presence of.
Remarks:
It is useless to use this method or SetAttributeOnPoint for attribute types 
that were described as valid for all points (See CloudAttributeDescription).
An attribute index can be retrieve from its name using GetCloudAttributeIndexByName.
See Also:SetAttributeOnPoint,GetPointIntAttribute,GetPointFloatAttribute,GetCloudAttributeIndexByName
***********************************************************************/
virtual CKBOOL	  IsAttributeOnPoint(int iPointIndex,int iAttributeIndex)  const CK_PURE;

/***********************************************************************
Summary: Ensures an attribute is put on a point.

Input arguments:
	iPointIndex: Index of the point (0..GetPointsCount()).
	iAttributeIndex: Index of the attribute type to set.
Remarks:
It is useless to use this method or GetAttributeOnPoint for attribute types 
that were described as valid for all points (See CloudAttributeDescription).
An attribute index can be retrieve from its name using GetCloudAttributeIndexByName.
See Also:SetAttributeOnPoint,GetPointIntAttribute,GetPointFloatAttribute,GetCloudAttributeIndexByName
***********************************************************************/
virtual void	  SetAttributeOnPoint(int iPointIndex,int iAttributeIndex) CK_PURE;

/***********************************************************************
Summary: Gets the value of an attribute on a point (stored as an integer).

Input arguments:
	iPointIndex: Index of the point (0..GetPointsCount()).
	iAttributeIndex: Index of the attribute to get the value of.
Remarks:
This method should only be used if the value stored by the attribute
is an integer as described in the CloudAttributeDescription.
An attribute index can be retrieve from its name using GetCloudAttributeIndexByName.
See Also:SetAttributeOnPoint,SetPointIntAttribute,GetPointFloatAttribute,GetCloudAttributeIndexByName
***********************************************************************/
virtual int  	  GetPointIntAttribute(int iPointIndex,int iAttributeIndex)  const CK_PURE;

/***********************************************************************
Summary: Gets the value of an attribute on a point (stored as a float).

Input arguments:
	iPointIndex: Index of the point (0..GetPointsCount()).
	iAttributeIndex: Index of the attribute to get the value of.
Remarks:
This method should only be used if the value stored by the attribute
is a float as described in the CloudAttributeDescription.
An attribute index can be retrieve from its name using GetCloudAttributeIndexByName.
See Also:SetAttributeOnPoint,GetPointIntAttribute,SetPointFloatAttribute,GetCloudAttributeIndexByName
***********************************************************************/
virtual float  	  GetPointFloatAttribute(int iPointIndex,int iAttributeIndex)  const CK_PURE;

/***********************************************************************
Summary: Sets the value of an attribute on a point (stored as an integer).

Input arguments:
	iPointIndex: Index of the point (0..GetPointsCount()).
	iAttributeIndex: Index of the attribute to set the value of.
	iValue: integer Value
Remarks:
This method should only be used if the value stored by the attribute
is an integer as described in the CloudAttributeDescription.
An attribute index can be retrieve from its name using GetCloudAttributeIndexByName.
See Also:SetAttributeOnPoint,GetPointIntAttribute,GetPointFloatAttribute,GetCloudAttributeIndexByName
***********************************************************************/
virtual void  	  SetPointIntAttribute(int iPointIndex,int iAttributeIndex, int iValue) CK_PURE;

/***********************************************************************
Summary: Sets the value of an attribute on a point (stored as a float).

Input arguments:
	iPointIndex: Index of the point (0..GetPointsCount()). 
	iAttributeIndex: Index of the attribute to set the value of.
	iValue: float Value
Remarks:
This method should only be used if the value stored by the attribute
is a float as described in the CloudAttributeDescription.
An attribute index can be retrieve from its name using GetCloudAttributeIndexByName.
See Also:SetAttributeOnPoint,SetPointIntAttribute,GetPointFloatAttribute,GetCloudAttributeIndexByName
***********************************************************************/
virtual void  	  SetPointFloatAttribute(int iPointIndex,int iAttributeIndex, float iValue) CK_PURE;

/***********************************************************************
Summary: Returns the number of points using a given attribute.

Input arguments:
	iAttributeIndex: Index of the attribute.
Remarks:
It is useless to use this method or GetIndexOfPointWithAttribute for attribute types 
that were described as valid for all points (See CloudAttributeDescription) as 
the returned value will be equal to GetPointsCount.
An attribute index can be retrieve from its name using GetCloudAttributeIndexByName.
See Also:SetAttributeOnPoint,SetPointIntAttribute,GetPointFloatAttribute,GetCloudAttributeIndexByName
***********************************************************************/
virtual int  	  GetPointWithAttributeCount(int iAttributeIndex)  const CK_PURE;

/***********************************************************************
Summary: Returns the ith point using a given attribute.

Input arguments:
	iAttributeIndex: Index of the attribute.
	iPointIndex: Index of the point (between 0 and GetPointWithAttributeCount)
Remarks:
This method can be used to iterate on all the points using a given attribute when 
this attribute is not valid on all points.
An attribute index can be retrieve from its name using GetCloudAttributeIndexByName.
See Also:SetAttributeOnPoint,SetPointIntAttribute,GetPointFloatAttribute,GetCloudAttributeIndexByName
***********************************************************************/
virtual int  	  GetIndexOfPointWithAttribute(int iAttributeIndex,int iPointIndex)  const CK_PURE;


/*************************************************
Summary: Dynamic cast operator. 
Arguments:
	iO: A pointer to a CKObject to cast.
Return Value:
	iO casted to the appropriate class or NULL if iO is not from the required class .
Example:
	  CKObject* Object;
	  CK3dPointCloud* anim = CK3dPointCloud::Cast(Object);
Remarks:

*************************************************/
static CK3dPointCloud* Cast(CKObject* iO) 
{
	return CKIsChildClassOf(iO,CKCID_3DPOINTCLOUD)?(CK3dPointCloud*)iO:NULL;
}

#ifndef CK_3DIMPLEMENTATION
};

#endif

#endif
