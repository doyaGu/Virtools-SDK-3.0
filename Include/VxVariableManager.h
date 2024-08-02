
/*************************************************************************/
/*	File : VxVariableManager.h											*/
/*	Author :  Aymeric BARD												*/	
/*																		*/	
/*	Virtools SDK 														*/	 
/*	Copyright (c) Virtools 2002, All Rights Reserved.					*/	
/*************************************************************************/

#ifndef VXVARIABLEMANAGER_H

#define VXVARIABLEMANAGER_H

#ifdef RUNTIME

#define VARDESCRIPTION(a) NULL
#else
#define VARDESCRIPTION(a) a
#endif

class VxVariableManager
{
public:
	friend class CKVariableManager;
	friend class CKParameterVariable;

	///
	// Types
	enum RestoreMode {
		ALL					= 1,
		COMPOSITION			= 2,
		NATIVECOMPOSITION	= 3
	};

	/************************************************************************
	Summary: This class represent a bound variable, accessing by its name 
	with the VariableManager. You can't instantiate Variable directly but either 
	their simple derived classes for existing types VariableInt, VariableFloat or
	VariableString either one specific class you will derive from one of the 
	preceding class, to override some of the virtual functions presenting its
	functionality.

	
	See Also: CKVariableManager
	*************************************************************************/
	class Variable
	{
	friend class VxVariableManager;
	public:
		// Types
		enum  Type {
			INT		= 1,
			FLOAT	= 2,
			STRING	= 3
		};

		// Flags
		enum Flags {
			READONLY				= 0x0001,
			HIDDEN					= 0x0002,
			COMPOSITIONBOUND		= 0x0004,
			NATIVEONLY				= 0x0008,
			NATIVECOMPOSITIONBOUND	= 0x000c, // (0x0008 == native)

		};

		// Dtor
		virtual ~Variable() {}

		/************************************************************************
		Summary: Returns the description of the variable. Can be NULL.

		
		See Also: CKVariableManager
		*************************************************************************/
		virtual const char* GetDescription() const {
#ifndef RUNTIME
			return m_Description;
#else
			return NULL;
#endif
		}

		/************************************************************************
		Summary: This function modifies the flags of the variable.

		
		See Also: CKVariableManager
		*************************************************************************/
		virtual void ModifyFlags(XDWORD iAdd, XDWORD iRemove)
		{
			m_Flags |= iAdd;
			m_Flags &= ~iRemove;
		}

		/************************************************************************
		Summary: This function gets the flags of the variable.

		
		See Also: CKVariableManager
		*************************************************************************/
		virtual XDWORD GetFlags()
		{
			return m_Flags;
		}

		/************************************************************************
		Summary: This function tells if the variable is different from its 
		default value.

		
		See Also: CKVariableManager
		*************************************************************************/
		virtual XBOOL IsDifferentFromDefault() const = 0;

		/************************************************************************
		Summary: This function restore the variable to its default value.

		
		See Also: CKVariableManager
		*************************************************************************/
		virtual void Restore() = 0;

		/************************************************************************
		Summary: This function gives the type of the variable. It can be any type
		of the VariableType enum : Variable::INT, Variable::FLOAT or 
		Variable::STRING.

		
		See Also: CKVariableManager
		*************************************************************************/
		virtual Type GetType() const = 0;

		/************************************************************************
		Summary: sets a variable from its string representation of a value.

		
		See Also: CKVariableManager
		*************************************************************************/
		virtual void SetStringValue(const char* iValue) = 0;

		/************************************************************************
		Summary: Fills a string with the string representation of the variable.

		
		See Also: CKVariableManager
		*************************************************************************/
		virtual void GetStringValue(XString& oValue) const = 0;

		/************************************************************************
		Summary: This function gives the representation (ie the input format) of
		a variable type. By default this string is NULL, saying that the format 
		is standard (int edited as an int, float as a float, etc.), but you can 
		give a complex format for your customized types.
		3 different formats are supported :

			- "range:s=min;e=max;t=step" range from s to e, with an optional 
			step of t (default is 1) and an optionnal description in parenthesis.
			
			- "enum:a=toto;b=titi;c=tutu;..."  list of possible value a,b,c, 
			with optional names in parenthesis

			- "flag:a=toto;b=titi;c=tutu;..."  same as enum. but represented 
			as a flag
			
		
		See Also: CKVariableManager
		*************************************************************************/
		virtual const char*  GetRepresentation() const {
			return NULL;
		}

		/************************************************************************
		Summary: This function tells if the variable can be written from the 
		VariableManager. Default is false.

		
		See Also: CKVariableManager
		*************************************************************************/
		XBOOL IsReadOnly() const {
			return m_Flags&READONLY;
		}

		/************************************************************************
		Summary: This function tells if the variable must be saved with the current 
		composition. Default is true.

		
		See Also: CKVariableManager
		*************************************************************************/
		XBOOL IsCompositionDepending() const {
			return (m_Flags&COMPOSITIONBOUND);
		}

		/************************************************************************
		Summary: This function tells if the variable must be saved with the current 
		composition. Default is true.

		
		See Also: CKVariableManager
		*************************************************************************/
		XBOOL IsNativeCompositionDepending() const {
			return (m_Flags&NATIVEONLY);
		}

		/************************************************************************
		Summary: This function tells if the variable must be hidden in the interface
		of the application. Default is false.

		
		See Also: CKVariableManager
		*************************************************************************/
		XBOOL IsHidden() const {
			return m_Flags&HIDDEN;
		}

#ifndef RUNTIME
		/************************************************************************
		Summary: This function sets the description of the variable.

		
		See Also: CKVariableManager
		*************************************************************************/
		void SetDescription(const char* iDescription)
		{
			m_Description = iDescription;
		}
#endif

	protected:
		// Ctor 
		Variable():
			 m_Flags(0)
#ifndef RUNTIME
			,m_Description(NULL)
#endif
			{}

		///
		// Members

		// Flags
		XDWORD		m_Flags;
#ifndef RUNTIME
		// description
		const char*	m_Description;
#endif
	};


/************************************************************************
Summary: Variable modification watching class.
Remarks:
This clas is used to watch a variable and detect when it is written to 
or read from (by the use of the VariableManager only)


See Also: VxVariableManager
*************************************************************************/
	class Watcher
	{
	public:
		virtual ~Watcher() {};
	
/************************************************************************
Summary: Called before a variable is read by manager.
Remarks:
This function is called when a variable is read by the interface of the CKVariableManager, to let the owner of the variable be
notified and react accordingly.
To use this functionality, you'll have to derive a new class for your
specific variable and implement what has to be done in the update 
function.


See Also: CKVariableManager, PostWrite
*************************************************************************/
		virtual void PreRead(const char* iName) {
		}

/************************************************************************
Summary:  Called after a variable is written by manager.
Remarks:
This function is called when a variable is modified by the interface of the CKVariableManager, to let the owner of the variable be
notified and react accordingly.
To use this functionality, you'll have to derive a new class for your
specific variable and implement what has to be done in the update 
function.


See Also: CKVariableManager, PreRead
*************************************************************************/
		virtual void PostWrite(const char* iName) {
		}
	};

	// Add a watcher
	VX_EXPORT void		RegisterWatcher(const char* iName, Watcher* iWatcher);
	
	// Removes a watcher
	VX_EXPORT Watcher*	UnRegisterWatcher(const char* iName);

	// types
	typedef XHashTable<Variable*,const char*> HashName2Var;

	/************************************************************************
	Summary: This is the class that allow iteration on all variables registered 
	in the variable manager.
	*************************************************************************/
	class Iterator
	{
		friend class VxVariableManager;
	public:
		// Accessors to variable members

		/************************************************************************
		Summary: returns the unique name of the variable pointed by the iterator. 

		Return Value: a constant string on the variable name
		*************************************************************************/
		const char*		GetName() {
			return iterator.GetKey();
		}

		/************************************************************************
		Summary: returns the variable pointed to by the iterator. 

		Return Value: a pointer on a CKVariable.
		*************************************************************************/
		Variable*		GetVariable() {
			return (*iterator);
		}

		// Iteration management
		
		/************************************************************************
		Summary: iterates to the next variable. 
		*************************************************************************/
		Iterator&		operator++(int) { 
			++iterator;
			return *this;
		}

		/************************************************************************
		Summary: tells if the iteration is over. 

		Return Value: TRUE if the iteration is at its end, FALSE otherwise.
		*************************************************************************/
		XBOOL End() {
			return (iterator == iterator.m_Table->End());
		}

	private:
		Iterator(HashName2Var::Iterator iIterator):iterator(iIterator) {}

		// the iterator
		HashName2Var::Iterator iterator;
	};

	///////////////////////////////
	// Methods

	/************************************************************************
	Summary: Registers the variable to the CKVariableManager with an absolute 
	name. If a variable with the same absolute name is already registered, does
	nothing but producing an output error in the console.

	Arguments:
		iContext : a valid CKContext
		iName : the absolute name of the variable, in the form "category/varname"
		iDefaultValue : the default value (and initial value) of the variable
		iDescription: the description of the variable meaning and functionnality.
		For no runtime overhead, you must give your description surrounded by
		the VARDESCRIPTION() macro.

	
	See Also: CKVariableManager
	*************************************************************************/
	VX_EXPORT void Bind(const char* iName, int*	iAddress, int iDefaultValue, XDWORD iFlags, const char* iDescription);
	VX_EXPORT void Bind(const char* iName, int*	iAddress, int iDefaultValue, XDWORD iFlags, const char* Representation, const char* iDescription);
	VX_EXPORT void Bind(const char* iName, float*	iAddress, float iDefaultValue, XDWORD iFlags, const char* iDescription);
	VX_EXPORT void Bind(const char* iName, XString* iAddress, const XString& iDefaultValue, XDWORD iFlags, const char* iDescription);
	VX_EXPORT void UnBind(const char* iName);

	/************************************************************************
	Summary: Gets the value of a variable. 
	

	Arguments:
		iName : the absolute name of the variable, in the form "category/varname"
		oValue : address of data that will contain the variable value

	Return Value: TRUE if the variable was found

	See Also: CKVariableManager
	*************************************************************************/
	VX_EXPORT XBOOL GetValue(const char* iName, int* oValue);

	/************************************************************************
	Summary: Sets the value of a variable. 
	

	Arguments:
		iName : the absolute name of the variable, in the form "category/varname"
		oValue : new value of the variable

	Return Value: TRUE if the variable was found

	See Also: CKVariableManager
	*************************************************************************/
	VX_EXPORT XBOOL SetValue(const char* iName, int iValue);

	// float

	VX_EXPORT XBOOL GetValue(const char* iName, float* oValue);
	VX_EXPORT XBOOL SetValue(const char* iName, float iValue);

	// string

	VX_EXPORT XBOOL GetValue(const char* iName, XString& oValue);
	VX_EXPORT XBOOL SetValue(const char* iName, const char* iValue);

	/************************************************************************
	Summary: Sets the value of a variable as a string. 
	

	Arguments:
		iName : the absolute name of the variable, in the form "category/varname"
		iValue : string representation of the value of the variable

	Return Value: CK_OK if the variable was found

	See Also: CKVariableManager
	*************************************************************************/
	VX_EXPORT XBOOL SetStringValue(const char* iName, const char* iValue);

	/************************************************************************
	Summary: Gets the value of a variable as a string. 
	

	Arguments:
		iName : the absolute name of the variable, in the form "category/varname"
		oValue : string representation of the value of the variable

	Return Value: CK_OK if the variable was found

	See Also: CKVariableManager
	*************************************************************************/
	VX_EXPORT XBOOL GetStringValue(const char* iName,		XString& oValue);

	/************************************************************************
	Summary: Sets a variable that is not composition depending as a depending
	one. This variable will be saved in composition, overriding its application
	settings
	

	Arguments:
		iName : the absolute name of the variable, in the form "category/varname"
		iSaving : TRUE if the variable must be saved with composition, FALSE 
		otherwise.

	Return Value: CK_OK if the variable were existing and application dependent

	See Also: CKVariableManager
	*************************************************************************/
	VX_EXPORT XBOOL		MarkAsCompositionDepending(const char* iName, XBOOL iSaving);

	// Get a bound variable
	VX_EXPORT Variable* GetVariable(const char* iName);
	

	/************************************************************************
	Summary: Restores a variable to its default value. 
	

	Arguments:
		iName : the absolute name of the variable, in the form "category/varname"

	Return Value: CK_OK if the variable was found

	See Also: CKVariableManager
	*************************************************************************/
	VX_EXPORT XBOOL RestoreValue(const char* iName);

	/************************************************************************
	Summary: Restores a defined set of variables to their default value. 
	

	Arguments:
		iMode : the set of variables that must be restored. This can be
		CKVariableManager::ALL : every variables
		CKVariableManager::COMPOSITION : every variables Composition Depending, 
		including the ones marked as so.
		CKVariableManager::NATIVECOMPOSITION : only variables natively Composition 
		Depending

	Return Value: CK_OK if the variable was found

	See Also: CKVariableManager
	*************************************************************************/
	VX_EXPORT void	   RestoreAll(RestoreMode iMode = ALL);

	/************************************************************************
	Summary: Import variables value from a given file. You can specify a set 
	of variables that must be read.
	

	Arguments:
		iFileName : the absolute file name of the variable file.
		iVariables: an array of variable names you want to be read. Specify NULL
		if you want all the variables in the file to be imported.

	Return Value: CK_OK if successfull

	See Also: CKVariableManager, Export
	*************************************************************************/
	VX_EXPORT XBOOL		Import(const char* iFileName, const XArray<const char*>* iVariables);

	/************************************************************************
	Summary: Export variables value from a given file. You can specify a set 
	of variables that must be written.
	

	Arguments:
		iFileName : the absolute file name of the variable file.
		iVariables: an array of variable names you want to be written. Specify NULL
		if you want all the variables in the file to be exported.

	Return Value: CK_OK if successfull

	See Also: CKVariableManager, Import
	*************************************************************************/
	VX_EXPORT XBOOL		Export(const char* iFileName, const XArray<const char*>* iVariables);

	/************************************************************************
	Summary: Gets the count of registered variables. 
	

	Return Value: the number of variables

	See Also: CKVariableManager
	*************************************************************************/
	VX_EXPORT	int			GetVariableCount();

/************************************************************************
Summary: Gets an iterator on all registered variables.

Remarks:
{html:<table width="90%" border="1" align="center" bordercolorlight="#FFFFFF" bordercolordark="#FFFFFF" bgcolor="#FFFFFF" bordercolor="#FFFFFF"><tr bgcolor="#E6E6E6" bordercolor="#000000"><td>}	
{html:<pre>}
{html:	CKVariableManager::Iterator it = vm->GetVariableIterator();}
{html:		for (;!it.End(); it++) {}
{html:			const char* name = it.GetName();}
{html:</pre>}
{html:</td></tr></table>}

Return Value: a CKVariableManager::Iterator

See Also: CKVariableManager
*************************************************************************/
	VX_EXPORT	Iterator	GetVariableIterator();

	/************************************************************************
	Summary: Gets the unique instance of the variable manager.
	See Also: CKVariableManager
	*************************************************************************/
	VX_EXPORT static VxVariableManager& Instance();

	
	~VxVariableManager();

	
	VX_EXPORT void WatcherPreRead(const char* iName);
	
	VX_EXPORT void WatcherPostWrite(const char* iName);

protected:

	// Protected Set Value
	VX_EXPORT XBOOL SetVariableValue(const char* iName, Variable* iVariable, int iValue);
	VX_EXPORT XBOOL SetVariableValue(const char* iName, Variable* iVariable, float iValue);
	VX_EXPORT XBOOL SetVariableValue(const char* iName, Variable* iVariable, const char* iValue);

	// Protected Get Value
	VX_EXPORT XBOOL GetVariableValue(const char* iName, Variable* iVariable, int* oValue);
	VX_EXPORT XBOOL GetVariableValue(const char* iName, Variable* iVariable, float* oValue);
	VX_EXPORT XBOOL GetVariableValue(const char* iName, Variable* iVariable, XString& oValue);

	// registering
	void RegisterVariable(Variable* iVar, const char* iName, XDWORD iFlags, const char* iDescription);

	// Get String Type of a variable
	const char*		GetStringType(const Variable* iVar);

	// All Variables Table
	HashName2Var	m_Variables;

	typedef XHashTable<Watcher*, const char*> HashName2Watcher;
	
	// Watcher table
	HashName2Watcher m_Watchers;

	typedef XHashTable<XString, XString> HashName2Name;
	
	// hash to store the variables not yet registered
	// but for which we have a value
	HashName2Name	m_DeferredVariables;
};

typedef VxVariableManager::Variable VxVar;


#define BIND(name,address,defaultvalue,flags,description) VxVariableManager::Instance().Bind(name,address,defaultvalue,flags,VARDESCRIPTION(description));

#define BINDREP(name,address,defaultvalue,flags,representation,description) VxVariableManager::Instance().Bind(name,(int*)address,defaultvalue,flags,representation,VARDESCRIPTION(description));

#define UNBIND(name) VxVariableManager::Instance().UnBind(name);

#define ADDWATCHER(name,watcher) VxVariableManager::Instance().RegisterWatcher(name,watcher);

#define REMOVEWATCHER(name) delete VxVariableManager::Instance().UnRegisterWatcher(name);

#define REMOVEWATCHERNODELETE(name) VxVariableManager::Instance().UnRegisterWatcher(name);

#endif
