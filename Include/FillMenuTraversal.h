/*
 * Project:                Virtools Interface Plugin SDK
 * File:                   FileMenuTraversal.h
 * Author:                 Thomas Vissieres
 * Last check date:        11/19/2003 
 * optimized for Tab Size: 4	
 * Quick file summary:     class FillMenuTraversal, used to parse VSL script tree and to fill a CMenu
 */

#pragma once


class FillMenuTraversal
{
public:
	FillMenuTraversal(CKVIPopupMenu& iMenu, XHashTable<ScriptInterfaceAction*, int>& iScriptActions, int startID = 0, BOOL emptyMenu = TRUE) :
	m_Menu(iMenu),
	m_ID(startID),
	m_ScriptActions(iScriptActions)
	{		
		if (emptyMenu) 
			iMenu.Empty();
	}

	int	Start(const ScriptTree& iTree,int parentCommandID = 0)
	{
		m_SubMenuStack.Resize(0);
		if (parentCommandID)
			m_SubMenuStack.PushBack(parentCommandID);
		iTree.Traverse(iTree.GetRoots(SCRIPTTREEROOTNAME_ACTIONS),*this);
		return m_ID;
	}

	void TraverseNode(const XString *iFolderName)
	{
		if (m_SubMenuStack.Size()) { // this is a sub menu
			m_Menu.AddItemToSubMenu(m_SubMenuStack.Back(),iFolderName->CStr(),m_ID,TRUE);
		} else {
			// Not in sub menu
			m_Menu.AddItem(iFolderName->CStr(),m_ID,TRUE);
		}

		m_SubMenuStack.PushBack(m_ID);
		++m_ID;
	}

	void TraverseLeaf(const ScriptInterface *iScriptInterface)
	{
		if (m_SubMenuStack.Size()) { // this is a sub menu
			m_Menu.AddItemToSubMenu(m_SubMenuStack.Back(),iScriptInterface->GetName().CStr(),m_ID);
		} else {
			// Not in sub menu
			m_Menu.AddItem(iScriptInterface->GetName().CStr(),m_ID);
		}

		m_ScriptActions.Insert(m_ID++, (ScriptInterfaceAction*)iScriptInterface);
	}

	void ExitNode(const XString *iFolderName) 
	{
		m_SubMenuStack.PopBack();
	}

private:
	CKVIPopupMenu&								m_Menu;
	XArray<CKDWORD>								m_SubMenuStack;
	int											m_ID;
	XHashTable<ScriptInterfaceAction*, int>&	m_ScriptActions;
};

class FillTraversal
{
public:
	FillTraversal(const ScriptTree& iTree,XArray<ScriptInterfaceAction*>& iScriptActions) :
	m_ScriptActions(iScriptActions)
	{
		iTree.Traverse(iTree.GetRoots(SCRIPTTREEROOTNAME_ACTIONS),*this);
	}

	void TraverseNode(const XString *iFolderName)
	{
	}

	void TraverseLeaf(const ScriptInterface *iScriptInterface)
	{
		m_ScriptActions.PushBack((ScriptInterfaceAction*)iScriptInterface);
	}

	void ExitNode(const XString *iFolderName) 
	{
	}

private:
	XArray<ScriptInterfaceAction*>&	m_ScriptActions;
};