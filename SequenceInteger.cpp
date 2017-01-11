// SequenceInteger.cpp: implementation of the SequenceInteger class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "READ Test.h"
#include "SequenceInteger.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SequenceInteger::SequenceInteger()
{

}

SequenceInteger::~SequenceInteger()
{

}

void SequenceInteger::ClearAll()
{
	pidc_cycles = 0;
	for (int l = 0; l < 6; l++)
		pidc[l] = FALSE;
	
	sectionAcycles = 0;
	sectionBcycles = 0;

	for (int i = 0; i < 12; i++){
		sample[i].AddCycles(0);
		for (int j = 0; j < 6; j++){
			sample[i].AddErase(j,0);
			sample[i].AddExpose(j,0);
			sample[i].AddGrid(j,0);
			sample[i].AddPin(j,0);
			sample[i].AddErase2(j,0);
			sample[i].AddExpose2(j,0);
			sample[i].AddGrid2(j,0);
			sample[i].AddPin2(j,0);
		}
	}
}

void SequenceInteger::Copy(SequenceInteger SeqCopy)
{
	pidc_cycles = SeqCopy.pidc_cycles;
	for (int l = 0; l < 6; l++)
		pidc[l] = SeqCopy.pidc[l];

	sectionAcycles = SeqCopy.sectionAcycles;
	sectionBcycles = SeqCopy.sectionBcycles;


	for (int i = 0; i < 12; i++){
		sample[i].AddCycles(SeqCopy.sample[i].GetCycles());
		for (int j = 0; j < 6; j++){
			sample[i].AddErase(j,SeqCopy.sample[i].GetErase(j));
			sample[i].AddExpose(j,SeqCopy.sample[i].GetExpose(j));
			sample[i].AddGrid(j,SeqCopy.sample[i].GetGrid(j));
			sample[i].AddPin(j,SeqCopy.sample[i].GetPin(j));
			sample[i].AddErase2(j,SeqCopy.sample[i].GetErase2(j));
			sample[i].AddExpose2(j,SeqCopy.sample[i].GetExpose2(j));
			sample[i].AddGrid2(j,SeqCopy.sample[i].GetGrid2(j));
			sample[i].AddPin2(j,SeqCopy.sample[i].GetPin2(j));
		}
	}

}
