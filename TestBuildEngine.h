#if !defined(AFX_TESTBUILDENGINE_H__A6C08531_0159_11D7_9117_DA0D0ACF9B91__INCLUDED_)
#define AFX_TESTBUILDENGINE_H__A6C08531_0159_11D7_9117_DA0D0ACF9B91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestBuildEngine.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestBuildEngine window

class CTestBuildEngine : public CWnd
{
// Construction
public:
	CTestBuildEngine();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestBuildEngine)
	//}}AFX_VIRTUAL

// Implementation
public:
	bool exposeIncrement[6];
	bool chargeIncrement[6];
	virtual ~CTestBuildEngine();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTestBuildEngine)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTBUILDENGINE_H__A6C08531_0159_11D7_9117_DA0D0ACF9B91__INCLUDED_)
