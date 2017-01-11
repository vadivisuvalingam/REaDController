#if !defined(AFX_MODIFIED_LIGHTMETERSCALINGCALCULATOR_H__8772B8EF_52B2_4F5F_8293_61D52C44CE76__INCLUDED_)
#define AFX_MODIFIED_LIGHTMETERSCALINGCALCULATOR_H__8772B8EF_52B2_4F5F_8293_61D52C44CE76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Modified_LightMeterScalingCalculator.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModified_LightMeterScalingCalculator dialog

class CModified_LightMeterScalingCalculator : public CPropertyPage
{
	DECLARE_DYNCREATE(CModified_LightMeterScalingCalculator)

// Construction
public:
	CModified_LightMeterScalingCalculator();
	~CModified_LightMeterScalingCalculator();

// Dialog Data
	//{{AFX_DATA(CModified_LightMeterScalingCalculator)
	enum { IDD = IDD_MODIFIED_LIGHTMETERSCALINGCALCULATOR };
	float	m_d_calib_value;
	float	m_d_slit_width;
	float	m_belt_velocity;
	double	m_scale_factor;
	float	m_pico_analog_output;
	float	m_pico_setting;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CModified_LightMeterScalingCalculator)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CModified_LightMeterScalingCalculator)
	afx_msg void OnCalculateScaleFactor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFIED_LIGHTMETERSCALINGCALCULATOR_H__8772B8EF_52B2_4F5F_8293_61D52C44CE76__INCLUDED_)
