// SequenceFloat.h: interface for the SequenceFloat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEQUENCEFLOAT_H__6763D9E3_BF17_11D6_90E7_8EE39F7F9591__INCLUDED_)
#define AFX_SEQUENCEFLOAT_H__6763D9E3_BF17_11D6_90E7_8EE39F7F9591__INCLUDED_

#include "SamplesGridFloat.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SequenceFloat  
{
public:
	void Copy(SequenceFloat SeqCopy);
	void ClearAll();
	SequenceFloat();
	virtual ~SequenceFloat();


	SamplesGridFloat sample[12];
	int pidc_cycles;
	BOOL pidc[6];
	int sectionAcycles;
	int sectionBcycles;


};

#endif // !defined(AFX_SEQUENCEFLOAT_H__6763D9E3_BF17_11D6_90E7_8EE39F7F9591__INCLUDED_)
