#if !defined(AFX_TESTRUNENGINE_H__69738A61_DB66_11D6_90F5_C16D554D9891__INCLUDED_)
#define AFX_TESTRUNENGINE_H__69738A61_DB66_11D6_90F5_C16D554D9891__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestRunEngine.h : header file
//
#include "NIBoard.h"
#include "TestProgressIndicator.h"

/////////////////////////////////////////////////////////////////////////////
// CTestRunEngine window

class CTestRunEngine : public CWnd
{
// Construction
public:

	CTestRunEngine();
	CTestRunEngine(CString name, float motor_speed_value, int cycles, int seqNumber, int sectionAcyc, int sectionBcyc);

private:
	int sectionA;
	int sectionB;
	int sequenceNumber;
	int revolutions;
	float motorSpeed;
	CString filename;
	CString hole_countFilename;

// Attributes
public:
	void TimeCalculate(double time, int cycles, CTestProgressIndicator* m_ProgressIndicator);
	bool BufferedMode();
	bool NonBufferedMode();


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestRunEngine)
	//}}AFX_VIRTUAL

// Implementation
public:
	bool NonBufferedDynamicMode();
	virtual ~CTestRunEngine();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTestRunEngine)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTRUNENGINE_H__69738A61_DB66_11D6_90F5_C16D554D9891__INCLUDED_)
