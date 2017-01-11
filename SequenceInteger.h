// SequenceInteger.h: interface for the SequenceInteger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEQUENCEINTEGER_H__6763D9E4_BF17_11D6_90E7_8EE39F7F9591__INCLUDED_)
#define AFX_SEQUENCEINTEGER_H__6763D9E4_BF17_11D6_90E7_8EE39F7F9591__INCLUDED_

#include "SamplesGridInteger.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SequenceInteger  
{
public:
	void Copy(SequenceInteger SeqCopy);
	void ClearAll();
	SequenceInteger();
	virtual ~SequenceInteger();
	SamplesGridInteger sample[12];
	int pidc_cycles;
	BOOL pidc[6];
	int sectionAcycles;
	int sectionBcycles;

};

#endif // !defined(AFX_SEQUENCEINTEGER_H__6763D9E4_BF17_11D6_90E7_8EE39F7F9591__INCLUDED_)
