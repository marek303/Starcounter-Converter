#pragma once

#include <string>
#include "pg_list.h"

using namespace std;

#define ERR_MSG(text) { fprintf(stdout,"Error: %s\n", text); }
#define WARNING_MSG(text) { fprintf(stdout,"Warning: %s\n", text); }

class CListEmulator
{
public:
	CListEmulator();
	virtual ~CListEmulator();

	ListCell* CreateCell(const wchar_t* name);
	bool AddCell(ListCell* const pCell);
	bool ClearList(List& inpList);
	bool ClearList();
	ListCell* GetListHead(){ return m_List.head; };

	wstring GetConcatenatedCells(const List& inpList);
	wstring GetConcatenatedCells();

protected:
	Ident* CreateIdent(const wchar_t* name);
	bool FindCell(ListCell* const pCell);

private:
	List m_List;
};

