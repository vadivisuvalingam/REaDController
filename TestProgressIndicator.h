#if !defined(AFX_TESTPROGRESSINDICATOR_H__A3A72C43_0E7E_4FDF_9601_05615111251D__INCLUDED_)
#define AFX_TESTPROGRESSINDICATOR_H__A3A72C43_0E7E_4FDF_9601_05615111251D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestProgressIndicator.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestProgressIndicator dialog

class CTestProgressIndicator : public CDialog
{
// Construction
public:
	BOOL CheckCancelButton();
	void PumpMessages();
	bool m_CancelRecordingData;
	CTestProgressIndicator(CWnd* pParent = NULL);   // standard constructor
	BOOL Create();

// Dialog Data
	//{{AFX_DATA(CTestProgressIndicator)
	enum { IDD = IDD_PROGRESS };
	CEdit	m_ZeroPositionCounter;
	CEdit	m_HoleCounter;
	CEdit	m_TimeLeft;
	CProgressCtrl	m_ProgressOfCycles;
	CEdit	m_CyclesLeft;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestProgressIndicator)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd* m_pParent;
	int	m_nID;


	// Generated message map functions
	//{{AFX_MSG(CTestProgressIndicator)
	afx_msg void OnCancelrecordingdata();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPROGRESSINDICATOR_H__A3A72C43_0E7E_4FDF_9601_05615111251D__INCLUDED_)
