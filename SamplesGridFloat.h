// SamplesGridFloat.h: interface for the SamplesGridFloat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMPLESGRIDFLOAT_H__6763D9E1_BF17_11D6_90E7_8EE39F7F9591__INCLUDED_)
#define AFX_SAMPLESGRIDFLOAT_H__6763D9E1_BF17_11D6_90E7_8EE39F7F9591__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SamplesGridFloat  
{
public:
	float GetPin(int index);
	float GetGrid(int index);
	float GetExpose(int index);
	float GetErase(int index);
	float GetPin2(int index);
	float GetGrid2(int index);
	float GetExpose2(int index);
	float GetErase2(int index);
	int GetCycles();
//	int GetSectionACycles();
//	int GetSectionBCycles();
	void AddPin(int index, float addvalue);
	void AddGrid(int index, float addvalue);
	void AddExpose(int index, float addvalue);
	void AddErase(int index, float addvalue);
	void AddPin2(int index, float addvalue);
	void AddGrid2(int index, float addvalue);
	void AddExpose2(int index, float addvalue);
	void AddErase2(int index, float addvalue);
	void AddCycles(int addvalue);
//	void AddSectionACycles(int addvalue);
//	void AddSectionBCycles(int addvalue);
	SamplesGridFloat();
	virtual ~SamplesGridFloat();

private:
	int cycles;
//	int sectionAcycles;
//	int sectionBcycles;
	float erase[6];
	float expose[6];
	float grid[6];
	float pin[6];
	float erase2[6];
	float expose2[6];
	float grid2[6];
	float pin2[6];

};

#endif // !defined(AFX_SAMPLESGRIDFLOAT_H__6763D9E1_BF17_11D6_90E7_8EE39F7F9591__INCLUDED_)
