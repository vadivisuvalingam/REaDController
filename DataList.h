// DataList.h: interface for the CDataList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATALIST_H__941AB490_F0CA_11D6_910A_FD52D1634491__INCLUDED_)
#define AFX_DATALIST_H__941AB490_F0CA_11D6_910A_FD52D1634491__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DOUBLE_TYPE 0
#define SHORT_TYPE 1

class CDataList  
{
public:
	void AttachNode(CDataList* node);
	CDataList* Forward();
	void* GetCurrentStub();
	CDataList(int numberofelements, int type);
	CDataList();
	virtual ~CDataList();

private:

	CDataList* forward;
	void* stub;

};

#endif // !defined(AFX_DATALIST_H__941AB490_F0CA_11D6_910A_FD52D1634491__INCLUDED_)
