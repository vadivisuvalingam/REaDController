// SamplesGridInteger.cpp: implementation of the SamplesGridInteger class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "READ Test.h"
#include "SamplesGridInteger.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SamplesGridInteger::SamplesGridInteger()
{

}

SamplesGridInteger::~SamplesGridInteger()
{

}

void SamplesGridInteger::AddCycles(int addvalue)
{
	cycles = addvalue;
}

void SamplesGridInteger::AddErase(int index, int addvalue)
{
	erase[index] = addvalue;
}

void SamplesGridInteger::AddExpose(int index, int addvalue)
{
	expose[index] = addvalue;
}

void SamplesGridInteger::AddGrid(int index, int addvalue)
{
	grid[index] = addvalue;
}

void SamplesGridInteger::AddPin(int index, int addvalue)
{
	pin[index] = addvalue;
}

void SamplesGridInteger::AddErase2(int index, int addvalue)
{
	erase2[index] = addvalue;
}

void SamplesGridInteger::AddExpose2(int index, int addvalue)
{
	expose2[index] = addvalue;
}

void SamplesGridInteger::AddGrid2(int index, int addvalue)
{
	grid2[index] = addvalue;
}

void SamplesGridInteger::AddPin2(int index, int addvalue)
{
	pin2[index] = addvalue;
}

int SamplesGridInteger::GetCycles()
{
	return cycles;
}


int SamplesGridInteger::GetErase(int index)
{
	return erase[index];
}

int SamplesGridInteger::GetExpose(int index)
{
	return expose[index];
}

int SamplesGridInteger::GetGrid(int index)
{
	return grid[index];
}

int SamplesGridInteger::GetPin(int index)
{
	return pin[index];
}

int SamplesGridInteger::GetErase2(int index)
{
	return erase2[index];
}

int SamplesGridInteger::GetExpose2(int index)
{
	return expose2[index];
}

int SamplesGridInteger::GetGrid2(int index)
{
	return grid2[index];
}

int SamplesGridInteger::GetPin2(int index)
{
	return pin2[index];
}

