#if !defined(AFX_MOTORSPEED_H__193D93FE_58FD_4929_B110_81D227DDA501__INCLUDED_)
#define AFX_MOTORSPEED_H__193D93FE_58FD_4929_B110_81D227DDA501__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MotorSpeed.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMotorSpeed dialog

class CMotorSpeed : public CPropertyPage
{
	DECLARE_DYNCREATE(CMotorSpeed)

// Construction
public:
	void Save(CString filename);
	void Load(CString filename);
	float m_MotorSpeed;
	float LookUpAndConvert(CString lookupfile, float m_lookup);
	CMotorSpeed();   // standard constructor
	~CMotorSpeed();

// Dialog Data
	//{{AFX_DATA(CMotorSpeed)
	enum { IDD = IDD_MOTORSPEED };
	CProgressCtrl	m_progress_of_table_creation;
	float	m_MotorspeedInches;
	float	m_MotorspeedRPM;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMotorSpeed)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMotorSpeed)
	afx_msg void OnCreatetables();
	afx_msg void OnConverttorpm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOTORSPEED_H__193D93FE_58FD_4929_B110_81D227DDA501__INCLUDED_)
