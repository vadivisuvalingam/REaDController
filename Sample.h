// Sample.h: interface for the CSample class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMPLE_H__79DD4CD2_F2FB_11D6_910D_9107A6264391__INCLUDED_)
#define AFX_SAMPLE_H__79DD4CD2_F2FB_11D6_910D_9107A6264391__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSample  
{
public:
	char* ID;
	char* comments;
	int EndPos;
	int StartPos;
	CSample();
	virtual ~CSample();

};

#endif // !defined(AFX_SAMPLE_H__79DD4CD2_F2FB_11D6_910D_9107A6264391__INCLUDED_)
