#if !defined(AFX_EXPERIMENTNAME_H__63AA05FF_34FB_4C25_ACCE_CBA085B4A6A5__INCLUDED_)
#define AFX_EXPERIMENTNAME_H__63AA05FF_34FB_4C25_ACCE_CBA085B4A6A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExperimentName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ExperimentName dialog

class ExperimentName : public CPropertyPage
{
	DECLARE_DYNCREATE(ExperimentName)

// Construction
public:
	ExperimentName();
	~ExperimentName();

// Dialog Data
	//{{AFX_DATA(ExperimentName)
	enum { IDD = IDD_EXPERIMENTNAME };
	CString	m_ProjectName;
	int		m_ProjectCounter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(ExperimentName)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(ExperimentName)
	afx_msg void OnChangeProjectname();
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPERIMENTNAME_H__63AA05FF_34FB_4C25_ACCE_CBA085B4A6A5__INCLUDED_)
