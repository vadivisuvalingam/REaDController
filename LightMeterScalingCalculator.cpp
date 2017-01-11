// LightMeterScalingCalculator.cpp : implementation file
//

#include "stdafx.h"
#include "READ Test.h"
#include "LightMeterScalingCalculator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LightMeterScalingCalculator property page

IMPLEMENT_DYNCREATE(LightMeterScalingCalculator, CPropertyPage)

LightMeterScalingCalculator::LightMeterScalingCalculator() : CPropertyPage(LightMeterScalingCalculator::IDD)
{
	//{{AFX_DATA_INIT(LightMeterScalingCalculator)
		// NOTE: the ClassWizard will add member initialization here
	m_dbl_da = 0.0;
	m_dbl_dcv = 0.0;
	m_lng_pao = 0;
	m_lng_ps = 0;
	m_dbl_sf = 0.0;
	//}}AFX_DATA_INIT
}

LightMeterScalingCalculator::~LightMeterScalingCalculator()
{
}

void LightMeterScalingCalculator::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LightMeterScalingCalculator)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, ID_DA, m_dbl_da);
	DDX_Text(pDX, ID_DCV, m_dbl_dcv);
	DDX_Text(pDX, ID_PAO, m_lng_pao);
	DDX_Text(pDX, ID_PS, m_lng_ps);
	DDX_Text(pDX, ID_SF, m_dbl_sf);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LightMeterScalingCalculator, CPropertyPage)
	//{{AFX_MSG_MAP(LightMeterScalingCalculator)
	ON_BN_CLICKED(ID_CALC_SF, OnCalcSf)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LightMeterScalingCalculator message handlers

void LightMeterScalingCalculator::OnCalcSf() 
{
	// The user has pressed the button to calculate the scale factor

	// Declare constants and variables
	const double PCF = 0.1;	// Power Conversion Factor (uW to Ergs / sec)
	
	double value;		// Result of the calculations


	// Read all values from the interface
	UpdateData( TRUE );
	

	// Check to make sure that the analog output setting was not left to zero
	// This would cause a divide by zero error
	if ( m_lng_pao == 0 )
	{
		MessageBox("No value was set for the Picoammeter Analog Output Setting");
		m_lng_pao = 1;
	}

	// Check the rest of the values to make sure they were input as well
	if ( m_dbl_dcv == 0 )
		MessageBox("No value was entered for the Detector Calibration Value");
	if ( m_dbl_da == 0 )
		MessageBox("No value was entered for the Detector Area");
	if ( m_lng_ps == 0 )
		MessageBox("No value was entered for the Picoammeter Setting");


	// Begin the calculation
		// SF = DCV * PCF * DA * PS / PAO
	value = m_dbl_dcv * PCF;
	value = value * m_dbl_da;
	value = value * m_lng_ps;
	value = value / m_lng_pao;

	m_dbl_sf = value;

	// Write the calculated values to the interface
	UpdateData( FALSE );
	
	
}

// the function is called when the page becomes inactive
BOOL LightMeterScalingCalculator::OnKillActive() 
{
	// update the values on the dialog box
	UpdateData(FALSE);
	return CPropertyPage::OnKillActive();
}
