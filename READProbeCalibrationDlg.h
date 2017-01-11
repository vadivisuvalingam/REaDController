#if !defined(AFX_READPROBECALIBRATIONDLG_H__8453F273_1195_44AD_9403_22909AF8F7F0__INCLUDED_)
#define AFX_READPROBECALIBRATIONDLG_H__8453F273_1195_44AD_9403_22909AF8F7F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// READProbeCalibrationDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CREADProbeCalibrationDlg dialog

struct READ_probe
{
	double slope;
	double zero;
	int position;
	int channel;
	int device;
};

class CREADProbeCalibrationDlg : public CDialog
{
// Construction
public:
	void UpdateProbe(int, CString);
	READ_probe probes[12];

	CREADProbeCalibrationDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CREADProbeCalibrationDlg)
	enum { IDD = IDD_READPROBECALIBRATION_DIALOG };
	CString	m_lastprobe;
	float	m_thous;
	float	m_zero;
	double	m_s1_vddp_zero;
	double	m_s1_vddp_slope;
	double	m_s1_vexp_zero;
	double	m_s1_vexp_slope;
	double	m_s2_vddp_zero;
	double	m_s2_vddp_slope;
	double	m_s2_vexp_zero;
	double	m_s2_vexp_slope;
	double	m_s3_vddp_zero;
	double	m_s3_vddp_slope;
	double	m_s3_vexp_zero;
	double	m_s3_vexp_slope;
	double	m_s4_vddp_zero;
	double	m_s4_vddp_slope;
	double	m_s4_vexp_zero;
	double	m_s4_vexp_slope;
	double	m_s5_vddp_zero;
	double	m_s5_vddp_slope;
	double	m_s5_vexp_zero;
	double	m_s5_vexp_slope;
	double	m_s6_vddp_zero;
	double	m_s6_vddp_slope;
	double	m_s6_vexp_zero;
	double	m_s6_vexp_slope;

		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CREADProbeCalibrationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CREADProbeCalibrationDlg)
		// NOTE: the ClassWizard will add member functions here
	afx_msg void OnAuto1a();
	afx_msg void OnCancelMode();
	afx_msg void OnExit();
	afx_msg void OnAuto1b();
	afx_msg void OnAuto2a();
	afx_msg void OnAuto2b();
	afx_msg void OnAuto3a();
	afx_msg void OnAuto3b();
	afx_msg void OnAuto4a();
	afx_msg void OnAuto4b();
	afx_msg void OnAuto5a();
	afx_msg void OnAuto5b();
	afx_msg void OnAuto6a();
	afx_msg void OnAuto6b();
	afx_msg void OnSave();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READPROBECALIBRATIONDLG_H__8453F273_1195_44AD_9403_22909AF8F7F0__INCLUDED_)
