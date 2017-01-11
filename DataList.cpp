// DataList.cpp: implementation of the CDataList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "READ Test.h"
#include "DataList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataList::CDataList()
{
	forward = NULL;
	stub = NULL;
}

CDataList::~CDataList()
{
    free(stub);
	if (forward != NULL)
		delete forward;
}

CDataList::CDataList(int numberofelements, int type)
{
	forward = NULL;
	if (type == DOUBLE_TYPE)
		stub = malloc(numberofelements*sizeof(double));
	else if (type == SHORT_TYPE)
		stub = malloc(numberofelements*sizeof(short));
	else
		stub = NULL;

}

void* CDataList::GetCurrentStub()
{
	return stub;

}

CDataList* CDataList::Forward()
{
	return forward;

}

void CDataList::AttachNode(CDataList *node)
{
	forward = node;
}
