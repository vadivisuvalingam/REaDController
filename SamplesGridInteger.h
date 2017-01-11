// SamplesGridInteger.h: interface for the SamplesGridInteger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMPLESGRIDINTEGER_H__6763D9E2_BF17_11D6_90E7_8EE39F7F9591__INCLUDED_)
#define AFX_SAMPLESGRIDINTEGER_H__6763D9E2_BF17_11D6_90E7_8EE39F7F9591__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SamplesGridInteger  
{
public:
	int GetPin(int index);
	int GetGrid(int index);
	int GetExpose(int index);
	int GetErase(int index);
	int GetPin2(int index);
	int GetGrid2(int index);
	int GetExpose2(int index);
	int GetErase2(int index);
	int GetCycles();
//	int GetSectionACycles();
//	int GetSectionBCycles();
	void AddPin(int index, int addvalue);
	void AddGrid(int index, int addvalue);
	void AddExpose(int index, int addvalue);
	void AddErase(int index, int addvalue);
	void AddPin2(int index, int addvalue);
	void AddGrid2(int index, int addvalue);
	void AddExpose2(int index, int addvalue);
	void AddErase2(int index, int addvalue);
	void AddCycles(int addvalue);
//	void AddSectionACycles(int addvalue);
//	void AddSectionBCycles(int addvalue);
	SamplesGridInteger();
	virtual ~SamplesGridInteger();

private:
	int cycles;
//	int sectionAcycles;
//	int sectionBcycles;
	int erase[6];
	int expose[6];
	int grid[6];
	int pin[6];
	int erase2[6];
	int expose2[6];
	int grid2[6];
	int pin2[6];

};

#endif // !defined(AFX_SAMPLESGRIDINTEGER_H__6763D9E2_BF17_11D6_90E7_8EE39F7F9591__INCLUDED_)
