#include <stdlib.h>

#include "ListEmulator.h"


//==============================================================================
CListEmulator::CListEmulator()
{
	m_List.head = NULL;
	m_List.tail = NULL;
	m_List.length = 0;
}

//==============================================================================
CListEmulator::~CListEmulator()
{

}

//==============================================================================
Ident* CListEmulator::CreateIdent(const wchar_t* name)
{
	if (!name)
		return NULL;

	unsigned int nameLen = wcslen(name) + 1;

	if (nameLen == 0)
		return NULL;

	Ident* pIdent = new Ident();
	wchar_t* pwch = new wchar_t[nameLen];
	wcscpy_s(pwch, nameLen, name);
	pIdent->name = pwch;

	return pIdent;
}

//==============================================================================
ListCell* CListEmulator::CreateCell(const wchar_t* name/*, ListCell* pPrevCell*/)
{
	Ident* pIdent = CreateIdent(name);
	if (!pIdent)
		return NULL;

	ListCell* pCell = NULL;
	pCell = (ListCell*)new ListCell();
	pCell->data.ptr_value = (void*)pIdent;
	pCell->next = NULL;

	return pCell;
}

//==============================================================================
bool CListEmulator::ClearList(List& inpList)
{
	ListCell* pCurrCell = inpList.head;
	while (pCurrCell)
	{
		if (Ident* pIdent = (Ident*)pCurrCell->data.ptr_value)
		{
			delete pIdent;
			pCurrCell->data.ptr_value = NULL;
		}
		pCurrCell = pCurrCell->next;
	}
	inpList.head = NULL;
	inpList.tail = NULL;
	inpList.length = 0;

	return true;
}

//==============================================================================
bool CListEmulator::ClearList()
{
	return ClearList(m_List);
}

//==============================================================================
bool CListEmulator::AddCell(ListCell* const pCell)
{
	if (!pCell)
	{
		ERR_MSG("AddCell(): null argument");
		return false;
	}

	ListCell* pTail = m_List.tail;
	if (!pTail && m_List.length > 0)
	{
		ERR_MSG("AddCell(): current tail is null (inconsistency)");
		return false;
	}
	if (pCell->next)
	{
		ERR_MSG("AddCell(): cannot add cell with non-null 'next' field");
		return false;
	}
	//pCell cannot exist on list!
	if (FindCell(pCell))
	{
		ERR_MSG("AddCell(): argument already on list");
		return false;
	}

	if (m_List.length == 0)
	{
		m_List.head = pCell;
	}
	if (pTail)
	{
		pTail->next = pCell;
	}

	m_List.tail = pCell;
	m_List.length++;

	return true;
}

//==============================================================================
bool CListEmulator::FindCell(ListCell* const pCell)
{
	if (!pCell)
	{
		WARNING_MSG("FindCell(): null argument");
		return false;
	}

	ListCell* pCurrCell = m_List.head;
	while (pCurrCell)
	{
		if (pCurrCell == pCell)
		{
			return true;
		}
		pCurrCell = pCurrCell->next;
	}
	return false;
}

//==============================================================================
wstring CListEmulator::GetConcatenatedCells(const List& inpList)
{
	wstring s = L"List(";
	ListCell* pCurrCell = inpList.head;
	while (pCurrCell)
	{
		if (Ident* pIdent = (Ident*)pCurrCell->data.ptr_value)
		{
			s.append(L"ListCell(Ident(name:\"");
			s.append(pIdent->name);
			s.append(L"\"))->");
		}
		pCurrCell = pCurrCell->next;
	}
	if (inpList.length > 0)
	{
		s.append(L"null");
	}
	s.append(L")");
	return s;
}

//==============================================================================
wstring CListEmulator::GetConcatenatedCells()
{
	return GetConcatenatedCells(m_List);
}