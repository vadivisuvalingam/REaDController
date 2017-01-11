#if !defined(AFX_JAZPATH_H__D323F4C1_45A2_11D6_B509_00C04FAD7388__INCLUDED_)
#define AFX_JAZPATH_H__D323F4C1_45A2_11D6_B509_00C04FAD7388__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JazPath.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CJazPath dialog

class CJazPath : public CDialog
{
// Construction
public:
	CJazPath(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CJazPath)
	enum { IDD = IDD_JAZPATH };
	CString	m_JazDirectory;
	CString	m_JazProjectName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJazPath)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CJazPath)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JAZPATH_H__D323F4C1_45A2_11D6_B509_00C04FAD7388__INCLUDED_)
