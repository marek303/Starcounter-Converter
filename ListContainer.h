#pragma once

#include <string>
#include <list>
#include "pg_list.h"

using namespace std;


template <typename ListElem, typename Data>
class CListContainer
{
public:
	typedef void*(*ptrOfDataFunction)(ListElem&);

	CListContainer(ListElem* ListElem::*next_ptr, ptrOfDataFunction pF, const wchar_t* Data::*name) 
		: m_next_ptr(next_ptr), GetDataPtr(pF), m_name(name)
	{
		m_list.clear();
	};
	virtual ~CListContainer(){};

	void AttachToList(ListElem* const pHead)
	{
		m_list.clear();

		ListCell* pCurrElem = pHead;
		while (pCurrElem)
		{
			m_list.push_back(pCurrElem);
			pCurrElem = pCurrElem->*m_next_ptr;
		}
	}

	wchar_t* GetName(ListElem &e);

	wstring GetReversedIdentifiersString()
	{
		wstring s = L"";
		for (ListElem* pCurrElem : m_list)
		{
			if (Data* pIdent = (Data*)GetDataPtr(*pCurrElem))
			{
				s.insert(0, pIdent->name);
			}
			if (pCurrElem->*m_next_ptr)
			{
				s.insert(0, L".");
			}
		}
		return s;
	}

private:
	ListElem* ListElem::*m_next_ptr;
	ptrOfDataFunction GetDataPtr;
	const wchar_t* Data::*m_name;

	list<ListElem*> m_list;
};
