#include <stdlib.h>
#include <atlconv.h>
#include <atlbase.h> 
#include <atlstr.h>
#include "ListEmulator.h"
#include "ListContainer.h"

//==============================================================================
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stdout, "Usage: %s [list of identifiers separated by spaces]\n", argv[0]);
		return 1;
	}

	//PostgreSQL parser data representation
	CListEmulator postgreListEmul;

	//We can use CListContainer for different input structs implemented as list.
	//CListContainer is parametrized by:
	//- list element struct (ListCell for PostgreSQL parser)
	//- data element struct (Ident for PostgreSQL parser)
	//Following data should be put as argument of CListContainer object:
	//- list element's member: "pointer to the next list element" ('ListCell::next' for PostgreSQL parser)
	//- function that returns void* pointer to data element of given list element ('ListCell::data::ptr_value' for PostgreSQL parser)
	//- data element's member: "pointer to the name" ('Ident::name' for PostgreSQL parser)

	//CListContainer for PostgreSQL parser data
	CListContainer<ListCell, Ident> postgreListCont(
		&ListCell::next, 
		[](ListCell& lc){return lc.data.ptr_value; }, 
		&Ident::name);

	//The good question is: 
	// why do we use function instead of list element's member?
	//It's because we can't deliver pointer to union subfield, when union is defined in struct.
	//There is the same problem with structs nested in struct.
	//So, the better solution would be to use functions instead of pointers to struct members.
	//But let's leave it as it is now (for educational purposes).


	//read program input names
	string argStr = "";
	ListCell* pCurrCell = NULL;
	for (int i = 1; i < argc; i++)
	{
		argStr = argv[i];
		if (argStr.length() == 0)
		{
			continue;
		}

		//create new cell with name
		pCurrCell = postgreListEmul.CreateCell(CA2W(argStr.c_str()));
		//add cell to list
		postgreListEmul.AddCell(pCurrCell);
		//postgreListCont.add(*pCurrCell);
	}

	//out original list
	wstring cellsStr = postgreListEmul.GetConcatenatedCells();
	fwprintf(stdout, L"\nCELLS:\n===>%ls\n", cellsStr.c_str());

	//wrap original list with container
	postgreListCont.AttachToList(postgreListEmul.GetListHead());

	//out identifiers as reverse list
	wstring identStr = postgreListCont.GetReversedIdentifiersString();
	fwprintf(stdout, L"REVERSED IDENTIFIERS:\n===>%ls\n", identStr.c_str());


	postgreListEmul.ClearList();
	return 0;
}


