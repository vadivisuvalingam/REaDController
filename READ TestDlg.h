// READ TestDlg.h : header file
//

#if !defined(AFX_READTESTDLG_H__4229862A_A805_4F60_A145_9CA69B2F34C9__INCLUDED_)
#define AFX_READTESTDLG_H__4229862A_A805_4F60_A145_9CA69B2F34C9__INCLUDED_

#include "ExperimentName.h"	// Added by ClassView
#include "DevicePositions.h"	// Added by ClassView
#include "GeneralSummary.h"	// Added by ClassView
#include "SampleInformation.h"	// Added by ClassView
#include "TestSequence.h"	// Added by ClassView
#include "Modified_LightMeterScalingCalculator.h"
#include "READScannerLightCalibration.h"	// Added by ClassView
#include "LightMeterScalingCalculator.h"	// Added by ClassView
#include "READProbeCalibrationDlg.h"	// Added by ClassView
#include "MotorSpeed.h"	// Added by ClassView
#include "TestProgressIndicator.h"	// Added by ClassView
#include "JazPath.h"	// Added by ClassView
#include "ChargeDeviceIncrement.h"	// Added by ClassView
#include "DevWnd.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CREADTestDlg dialog

class CREADTestDlg : public CDialog
{
// Construction
public:
	CDevWnd m_miscSettings;
	CChargeDeviceIncrement* chrgDevIncr;
	CString returnRootName(CString pathname);
	void LoadSettings();
	void SaveSettings();
	SampleInformation tab3sampleInformation;
	DevicePositions tab2devicePositions;
	CMotorSpeed tab1motorSpeed;
	
	CPropertySheet m_pSettings;
	int* returnPidcExpose(int currentcycle, float* pidc_increment);
	float* returnPidcIncrements(int cycles);
	
	CModified_LightMeterScalingCalculator tab3Modified_LightMeterScalingCalculator;
	bool test_is_PIDC;
	void TimeCalculate(double time, int cycles);
	int m_revolutions;
	void BuildOneTestSequence(SequenceInteger sequenceBinaryForm, int seq_number);
	CTestProgressIndicator* m_ProgressIndicator;
	CREADProbeCalibrationDlg probeCalibration;
	READScannerLightCalibration tab2lightCalibration;
	LightMeterScalingCalculator tab1scaleCalculator;
	CPropertySheet m_pLightCalibration;
	void SaveExperimentInfo();
	ExperimentName Page3ExperimentName;
	void DisplaySummary();
	TestSequence Page2TestSequence;

	
	GeneralSummary Page1GeneralSummary;

	CPropertySheet m_pBuildTestProperties;
	CREADTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CREADTestDlg)
	enum { IDD = IDD_READTEST_DIALOG };
	CListBox	m_TestSummary;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CREADTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CREADTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExit();
	afx_msg void OnBuildtest();
	afx_msg void OnDblclkTestsummary();
	afx_msg void OnRuntest();
	afx_msg void OnLightcalibration();
	afx_msg void OnProbecalibration();
	afx_msg void OnJazsave();
	afx_msg void OnSettings();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL okayToTransferToJaz;
	CJazPath JazPath;
	int global_pidc_expose[6];
	float global_pidc_increment[6];

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READTESTDLG_H__4229862A_A805_4F60_A145_9CA69B2F34C9__INCLUDED_)
