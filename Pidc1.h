#if !defined(AFX_PIDC1_H__BC0B8454_4C58_439A_920F_638F370721AA__INCLUDED_)
#define AFX_PIDC1_H__BC0B8454_4C58_439A_920F_638F370721AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pidc1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPidc dialog

class CPidc : public CPropertyPage
{
	DECLARE_DYNCREATE(CPidc)

// Construction
public:
	int b_erase;
	int b_expose;
	int b_grid;
	int b_pin;
	float	m_expose;
	void ConvertFloatToBinary();
	void Load(CString loadfilename);
	int LightDevice_LookUpAndConvert(CString lookupfile, float m_lookup);
	int ChargingDevice_LookUpAndConvert(CString lookupfile, float m_lookup);
	CString array_filenames[24];
	int m_erase_station;
	void Save(CString savefilename);
	CPidc();
	~CPidc();

// Dialog Data
	//{{AFX_DATA(CPidc)
	enum { IDD = IDD_PIDC };
	int		m_cycles;
	float	m_erase;
	float	m_grid;
	float	m_pin;
	BOOL	m_s1;
	BOOL	m_s2;
	BOOL	m_s3;
	BOOL	m_s4;
	BOOL	m_s5;
	BOOL	m_s6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPidc)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPidc)
	afx_msg void OnCheckS1Erase();
	afx_msg void OnCheckS2Erase();
	afx_msg void OnCheckS3Erase();
	afx_msg void OnCheckS4Erase();
	afx_msg void OnCheckS5Erase();
	afx_msg void OnCheckS6Erase();
	afx_msg void OnLoadPidc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIDC1_H__BC0B8454_4C58_439A_920F_638F370721AA__INCLUDED_)
