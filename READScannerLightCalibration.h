#if !defined(AFX_READSCANNERLIGHTCALIBRATION_H__305ED3B3_B913_4022_BCDB_EE936E553205__INCLUDED_)
#define AFX_READSCANNERLIGHTCALIBRATION_H__305ED3B3_B913_4022_BCDB_EE936E553205__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// READScannerLightCalibration.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// READScannerLightCalibration dialog

class READScannerLightCalibration : public CPropertyPage
{
	DECLARE_DYNCREATE(READScannerLightCalibration)

// Construction
public:
	READScannerLightCalibration();
	~READScannerLightCalibration();

// Dialog Data
	//{{AFX_DATA(READScannerLightCalibration)
	enum { IDD = IDD_READSCANNERLIGHTCALIBRATION_DIALOG };
		// NOTE - ClassWizard will add data members here.
	int		m_int_aichan;
	int		m_int_aochan;
	int		m_int_aodev;
	int		m_int_aidev;
	double	m_scaling;
	UINT	m_int_wait;

		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(READScannerLightCalibration)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(READScannerLightCalibration)
	afx_msg void OnRun();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READSCANNERLIGHTCALIBRATION_H__305ED3B3_B913_4022_BCDB_EE936E553205__INCLUDED_)
