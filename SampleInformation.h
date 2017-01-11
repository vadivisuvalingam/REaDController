#if !defined(AFX_SAMPLEINFORMATION_H__91156BB5_E489_4BA8_B81A_076706A3049F__INCLUDED_)
#define AFX_SAMPLEINFORMATION_H__91156BB5_E489_4BA8_B81A_076706A3049F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SampleInformation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SampleInformation dialog

class SampleInformation : public CPropertyPage
{
	DECLARE_DYNCREATE(SampleInformation)

// Construction
public:
	void RecordValues();
	void Load (CString loadfilename);
	void Save (CString savefilename);
	void OnUpdate();
	void OnRecord();
	CString sampleID [12];
	CString comments [12];
	int startHole [12];
	int endHole [12];
	SampleInformation();
	~SampleInformation();

// Dialog Data
	//{{AFX_DATA(SampleInformation)
	enum { IDD = IDD_SAMPLEINFORMATION };
	int		m_sampleNumber;
	CString	m_sampleID;
	int		m_startHole;
	int		m_endHole;
	CString	m_comments;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(SampleInformation)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SampleInformation)
	afx_msg void OnForward();
	afx_msg void OnBack();
	afx_msg void OnLoad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLEINFORMATION_H__91156BB5_E489_4BA8_B81A_076706A3049F__INCLUDED_)
