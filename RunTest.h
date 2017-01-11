// RunTest.h: interface for the CRunTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RUNTEST_H__5549A913_D9CD_11D6_90F5_C16D554D9891__INCLUDED_)
#define AFX_RUNTEST_H__5549A913_D9CD_11D6_90F5_C16D554D9891__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRunTest  
{
public:
	void AddRevolutions(int value);
	void AddMotorSpeed(int value);
	void AddFileName(CString name);
	void TimeCalculate(double time, int cycles, CTestProgressIndicator* m_ProgressIndicator);
	bool BufferedMode();
	CRunTest();
	virtual ~CRunTest();

private:
	int mode;
	int revolutions;
	int motorSpeed;
	CString filename;
};

#endif // !defined(AFX_RUNTEST_H__5549A913_D9CD_11D6_90F5_C16D554D9891__INCLUDED_)
