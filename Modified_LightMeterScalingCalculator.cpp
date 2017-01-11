// Modified_LightMeterScalingCalculator.cpp : implementation file
//

#include "stdafx.h"
#include "READ Test.h"
#include "Modified_LightMeterScalingCalculator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModified_LightMeterScalingCalculator property page

IMPLEMENT_DYNCREATE(CModified_LightMeterScalingCalculator, CPropertyPage)

CModified_LightMeterScalingCalculator::CModified_LightMeterScalingCalculator() : CPropertyPage(CModified_LightMeterScalingCalculator::IDD)
{
	//{{AFX_DATA_INIT(CModified_LightMeterScalingCalculator)
	m_d_calib_value = 0.0f;
	m_d_slit_width = 0.0f;
	m_belt_velocity = 0.0f;
	m_scale_factor = 0.0;
	m_pico_analog_output = 0.0f;
	m_pico_setting = 0.0f;
	//}}AFX_DATA_INIT
}

CModified_LightMeterScalingCalculator::~CModified_LightMeterScalingCalculator()
{
}

void CModified_LightMeterScalingCalculator::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModified_LightMeterScalingCalculator)
	DDX_Text(pDX, ID_DETECTOR_CALIBRATION_VALUE, m_d_calib_value);
	DDX_Text(pDX, ID_DETECTOR_SLIT_WIDTH, m_d_slit_width);
	DDX_Text(pDX, IDC_VELOCITY_OF_BELT, m_belt_velocity);
	DDX_Text(pDX, ID_SCALE_FACTOR, m_scale_factor);
	DDX_Text(pDX, ID_PICOAMMETER_ANALOG_OUTPUT, m_pico_analog_output);
	DDX_Text(pDX, ID_PICOAMMETER_SETTING, m_pico_setting);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModified_LightMeterScalingCalculator, CPropertyPage)
	//{{AFX_MSG_MAP(CModified_LightMeterScalingCalculator)
	ON_BN_CLICKED(ID_CALCULATE_SCALE_FACTOR, OnCalculateScaleFactor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModified_LightMeterScalingCalculator message handlers

// this function is called when the user presses on calculate scale factor.
void CModified_LightMeterScalingCalculator::OnCalculateScaleFactor() 
{
	// Detector Calibration Value * Velocity of Belt * Detector Slit Width 
	// * Picoammeter Setting / Picoammeter Analog Output * (1/10) (Erg/ (sec * uW)) 
	// = Scale Factor
	const double constValue = 0.1;
	double value;
	UpdateData(TRUE);
	value = m_d_calib_value * m_belt_velocity;
	value *= m_d_slit_width;
	value *= m_pico_setting; 
	value /= m_pico_analog_output;
	value *= constValue;
	m_scale_factor = value; 
	UpdateData(FALSE);
		
}
