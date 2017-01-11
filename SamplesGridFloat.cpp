// SamplesGridFloat.cpp: implementation of the SamplesGridFloat class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "READ Test.h"
#include "SamplesGridFloat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SamplesGridFloat::SamplesGridFloat()
{

}

SamplesGridFloat::~SamplesGridFloat()
{

}



void SamplesGridFloat::AddCycles(int addvalue)
{
	cycles = addvalue;
}

void SamplesGridFloat::AddErase(int index, float addvalue)
{
	erase[index] = addvalue;
}

void SamplesGridFloat::AddExpose(int index, float addvalue)
{
	expose[index] = addvalue;
}

void SamplesGridFloat::AddGrid(int index, float addvalue)
{
	grid[index] = addvalue;
}

void SamplesGridFloat::AddPin(int index, float addvalue)
{
	pin[index] = addvalue;
}

void SamplesGridFloat::AddErase2(int index, float addvalue)
{
	erase2[index] = addvalue;
}

void SamplesGridFloat::AddExpose2(int index, float addvalue)
{
	expose2[index] = addvalue;
}

void SamplesGridFloat::AddGrid2(int index, float addvalue)
{
	grid2[index] = addvalue;
}

void SamplesGridFloat::AddPin2(int index, float addvalue)
{
	pin2[index] = addvalue;
}

int SamplesGridFloat::GetCycles()
{
	return cycles;
}


float SamplesGridFloat::GetErase(int index)
{
	return erase[index];
}

float SamplesGridFloat::GetExpose(int index)
{
	return expose[index];
}

float SamplesGridFloat::GetGrid(int index)
{
	return grid[index];
}

float SamplesGridFloat::GetPin(int index)
{
	return pin[index];
}

float SamplesGridFloat::GetErase2(int index)
{
	return erase2[index];
}

float SamplesGridFloat::GetExpose2(int index)
{
	return expose2[index];
}

float SamplesGridFloat::GetGrid2(int index)
{
	return grid2[index];
}

float SamplesGridFloat::GetPin2(int index)
{
	return pin2[index];
}
