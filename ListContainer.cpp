#include <stdlib.h>

#include "ListContainer.h"


//==============================================================================
template <typename ListElem, typename Data>
wchar_t* CListContainer<ListElem, Data>::GetName(ListElem &e)
{
	Data* pData = (Data*)e::*m_data_ptr;
	return *pData::*m_name;
}

