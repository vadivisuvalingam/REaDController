#if !defined(AFX_LIGHTMETERSCALINGCALCULATOR_H__F999FD2D_90F3_4618_BA97_03DC51DE276A__INCLUDED_)
#define AFX_LIGHTMETERSCALINGCALCULATOR_H__F999FD2D_90F3_4618_BA97_03DC51DE276A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LightMeterScalingCalculator.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LightMeterScalingCalculator dialog

class LightMeterScalingCalculator : public CPropertyPage
{
	DECLARE_DYNCREATE(LightMeterScalingCalculator)

// Construction
public:
	LightMeterScalingCalculator();
	~LightMeterScalingCalculator();

// Dialog Data
	//{{AFX_DATA(LightMeterScalingCalculator)
	enum { IDD = IDD_LIGHTMETERSCALINGCALCULATOR_DIALOG };
		// NOTE - ClassWizard will add data members here.
	double	m_dbl_da;
	double	m_dbl_dcv;
	long	m_lng_pao;
	long	m_lng_ps;
	double	m_dbl_sf;

		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(LightMeterScalingCalculator)
	public:
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(LightMeterScalingCalculator)
	afx_msg void OnCalcSf();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTMETERSCALINGCALCULATOR_H__F999FD2D_90F3_4618_BA97_03DC51DE276A__INCLUDED_)
