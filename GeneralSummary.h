#if !defined(AFX_GENERALSUMMARY_H__A981DE9B_C645_49AD_953C_113F3314D61C__INCLUDED_)
#define AFX_GENERALSUMMARY_H__A981DE9B_C645_49AD_953C_113F3314D61C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GeneralSummary.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GeneralSummary dialog

class GeneralSummary : public CPropertyPage
{
	DECLARE_DYNCREATE(GeneralSummary)

// Construction
public:
	void Save(CString savefilename);
	void SetCurrentTime();
	GeneralSummary();
	~GeneralSummary();

// Dialog Data
	//{{AFX_DATA(GeneralSummary)
	enum { IDD = IDD_GENERALSUMMARY };
	CString	m_comments;
	CString	m_DateAndTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(GeneralSummary)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(GeneralSummary)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERALSUMMARY_H__A981DE9B_C645_49AD_953C_113F3314D61C__INCLUDED_)
