// READProbeCalibrationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "READ Test.h"
#include "READProbeCalibrationDlg.h"
#include "nidaq.h"
#include "nidaqex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CREADProbeCalibrationDlg dialog


CREADProbeCalibrationDlg::CREADProbeCalibrationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CREADProbeCalibrationDlg::IDD, pParent)
{

	//{{AFX_DATA_INIT(CREADProbeCalibrationDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_lastprobe = _T("");
	m_thous = 0.0f;
	m_zero = 0.0f;
	m_s1_vddp_zero = 0.0;
	m_s1_vddp_slope = 0.0;
	m_s1_vexp_zero = 0.0;
	m_s1_vexp_slope = 0.0;
	m_s2_vddp_zero = 0.0;
	m_s2_vddp_slope = 0.0;
	m_s2_vexp_zero = 0.0;
	m_s2_vexp_slope = 0.0;
	m_s3_vddp_zero = 0.0;
	m_s3_vddp_slope = 0.0;
	m_s3_vexp_zero = 0.0;
	m_s3_vexp_slope = 0.0;
	m_s4_vddp_zero = 0.0;
	m_s4_vddp_slope = 0.0;
	m_s4_vexp_zero = 0.0;
	m_s4_vexp_slope = 0.0;
	m_s5_vddp_zero = 0.0;
	m_s5_vddp_slope = 0.0;
	m_s5_vexp_zero = 0.0;
	m_s5_vexp_slope = 0.0;
	m_s6_vddp_zero = 0.0;
	m_s6_vddp_slope = 0.0;
	m_s6_vexp_zero = 0.0;
	m_s6_vexp_slope = 0.0;
	//}}AFX_DATA_INIT
}


void CREADProbeCalibrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CREADProbeCalibrationDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_LASTPROBE, m_lastprobe);
	DDX_Text(pDX, IDC_LASTTHOUSAND, m_thous);
	DDX_Text(pDX, IDC_LASTZERO, m_zero);
	DDX_Text(pDX, IDC_S1VDDP_B, m_s1_vddp_zero);
	DDX_Text(pDX, IDC_S1VDDP_M, m_s1_vddp_slope);
	DDX_Text(pDX, IDC_S1VEXP_B, m_s1_vexp_zero);
	DDX_Text(pDX, IDC_S1VEXP_M, m_s1_vexp_slope);
	DDX_Text(pDX, IDC_S2VDDP_B, m_s2_vddp_zero);
	DDX_Text(pDX, IDC_S2VDDP_M, m_s2_vddp_slope);
	DDX_Text(pDX, IDC_S2VEXP_B, m_s2_vexp_zero);
	DDX_Text(pDX, IDC_S2VEXP_M, m_s2_vexp_slope);
	DDX_Text(pDX, IDC_S3VDDP_B, m_s3_vddp_zero);
	DDX_Text(pDX, IDC_S3VDDP_M, m_s3_vddp_slope);
	DDX_Text(pDX, IDC_S3VEXP_B, m_s3_vexp_zero);
	DDX_Text(pDX, IDC_S3VEXP_M, m_s3_vexp_slope);
	DDX_Text(pDX, IDC_S4VDDP_B, m_s4_vddp_zero);
	DDX_Text(pDX, IDC_S4VDDP_M, m_s4_vddp_slope);
	DDX_Text(pDX, IDC_S4VEXP_B, m_s4_vexp_zero);
	DDX_Text(pDX, IDC_S4VEXP_M, m_s4_vexp_slope);
	DDX_Text(pDX, IDC_S5VDDP_B, m_s5_vddp_zero);
	DDX_Text(pDX, IDC_S5VDDP_M, m_s5_vddp_slope);
	DDX_Text(pDX, IDC_S5VEXP_B, m_s5_vexp_zero);
	DDX_Text(pDX, IDC_S5VEXP_M, m_s5_vexp_slope);
	DDX_Text(pDX, IDC_S6VDDP_B, m_s6_vddp_zero);
	DDX_Text(pDX, IDC_S6VDDP_M, m_s6_vddp_slope);
	DDX_Text(pDX, IDC_S6VEXP_B, m_s6_vexp_zero);
	DDX_Text(pDX, IDC_S6VEXP_M, m_s6_vexp_slope);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CREADProbeCalibrationDlg, CDialog)
	//{{AFX_MSG_MAP(CREADProbeCalibrationDlg)
		// NOTE: the ClassWizard will add message map macros here
	ON_BN_CLICKED(IDC_AUTO1A, OnAuto1a)
	ON_BN_CLICKED(ID_EXIT, OnExit)
	ON_BN_CLICKED(IDC_AUTO1B, OnAuto1b)
	ON_BN_CLICKED(IDC_AUTO2A, OnAuto2a)
	ON_BN_CLICKED(IDC_AUTO2B, OnAuto2b)
	ON_BN_CLICKED(IDC_AUTO3A, OnAuto3a)
	ON_BN_CLICKED(IDC_AUTO3B, OnAuto3b)
	ON_BN_CLICKED(IDC_AUTO4A, OnAuto4a)
	ON_BN_CLICKED(IDC_AUTO4B, OnAuto4b)
	ON_BN_CLICKED(IDC_AUTO5A, OnAuto5a)
	ON_BN_CLICKED(IDC_AUTO5B, OnAuto5b)
	ON_BN_CLICKED(IDC_AUTO6A, OnAuto6a)
	ON_BN_CLICKED(IDC_AUTO6B, OnAuto6b)
	ON_BN_CLICKED(ID_SAVE, OnSave)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CREADProbeCalibrationDlg message handlers


void CREADProbeCalibrationDlg::UpdateProbe(int pn, CString name)
{
	
	// Declare variables
	int istatus;				// NI status check
	f64 reading[1] = {0.0};				// Present voltage measurement
	double calc;					// Variable for the calculation of the slope
	

	// Save all of the information on the interface - in case the user has modified any of it manually
	UpdateData(TRUE);
	probes[0].zero = m_s1_vddp_zero;
	probes[0].slope = m_s1_vddp_slope;
	probes[1].zero = m_s1_vexp_zero;
	probes[1].slope = m_s1_vexp_slope;

	probes[2].zero = m_s2_vddp_zero;
	probes[2].slope = m_s2_vddp_slope;
	probes[3].zero = m_s2_vexp_zero;
	probes[3].slope = m_s2_vexp_slope;

	probes[4].zero = m_s3_vddp_zero;
	probes[4].slope = m_s3_vddp_slope;
	probes[5].zero = m_s3_vexp_zero;
	probes[5].slope = m_s3_vexp_slope;

	probes[6].zero = m_s4_vddp_zero;
	probes[6].slope = m_s4_vddp_slope;
	probes[7].zero = m_s4_vexp_zero;
	probes[7].slope = m_s4_vexp_slope;

	probes[8].zero = m_s5_vddp_zero;
	probes[8].slope = m_s5_vddp_slope;
	probes[9].zero = m_s5_vexp_zero;
	probes[9].slope = m_s5_vexp_slope;

	probes[10].zero = m_s6_vddp_zero;
	probes[10].slope = m_s6_vddp_slope;
	probes[11].zero = m_s6_vexp_zero;
	probes[11].slope = m_s6_vexp_slope;

	// Place the name of the probe specified into the spot for the last probe calibrated
	m_lastprobe = name;
	m_zero = 0;
	m_thous = 0;
	UpdateData(FALSE);

	// Add the word - "Calibration" to the name for display
	name = name + " Calibration";

	// Instruct the user to place the probe over the calibration device set to zero volts
	MessageBox("Place the probe over a Zero Volts source for calibration.", name);

	// Read the voltage input for the probe channel
		/*	status = AI_VRead (deviceNumber, chan, gain, voltage)
			first parameter is the device number of the DAQ board
			second parameter is the channel number where the probe is connected
			1 is the gain setting - unity gain
			reading is the location of the data returned
		*/
	istatus = AI_VRead(probes[pn].device, probes[pn].channel, 1, reading);
	
	// Check the range of the voltage read
	if (reading[0] < -10)
		reading[0] = -10;
	if (reading[0] > 10)
		reading[0] = 10;
	
	// Store the voltage read
	probes[pn].zero = reading[0];
	m_zero = reading[0];
	UpdateData(FALSE);


	// Instruct the user to place the probe over the calibration device set to zero volts
	MessageBox("Place the probe over a -900 Volts source for calibration.", name);

	// Read the voltage input for the probe channel
	istatus = AI_VRead(probes[pn].device, probes[pn].channel, 1, reading);
	
	// Check the range of the voltage read
	if (reading[0] < -10)
		reading[0] = -10;
	if (reading[0] > 10)
		reading[0] = 10;
	
	// Store the voltage read
	calc = reading[0];
	m_thous = reading[0];

	if (calc != probes[pn].zero)
		probes[pn].slope = (-900)/(calc - probes[pn].zero);
	else
		probes[pn].slope = 0;			// Avoid divide by zero errors


	// Update the information on all of the probes for the interface
	m_s1_vddp_zero = probes[0].zero;
	m_s1_vddp_slope = probes[0].slope;
	m_s1_vexp_zero = probes[1].zero;
	m_s1_vexp_slope = probes[1].slope;

	m_s2_vddp_zero = probes[2].zero;
	m_s2_vddp_slope = probes[2].slope;
	m_s2_vexp_zero = probes[3].zero;
	m_s2_vexp_slope = probes[3].slope;

	m_s3_vddp_zero = probes[4].zero;
	m_s3_vddp_slope = probes[4].slope;
	m_s3_vexp_zero = probes[5].zero;
	m_s3_vexp_slope = probes[5].slope;

	m_s4_vddp_zero = probes[6].zero;
	m_s4_vddp_slope = probes[6].slope;
	m_s4_vexp_zero = probes[7].zero;
	m_s4_vexp_slope = probes[7].slope;

	m_s5_vddp_zero = probes[8].zero;
	m_s5_vddp_slope = probes[8].slope;
	m_s5_vexp_zero = probes[9].zero;
	m_s5_vexp_slope = probes[9].slope;

	m_s6_vddp_zero = probes[10].zero;
	m_s6_vddp_slope = probes[10].slope;
	m_s6_vexp_zero = probes[11].zero;
	m_s6_vexp_slope = probes[11].slope;

	// Update the interface
	UpdateData(FALSE);
}




void CREADProbeCalibrationDlg::OnExit() 
{
	// The user pressed the exit button
	
	// Update the readings - in case they are out of type - to avoid error messages
	m_zero = 0;
	m_thous = 0;
	UpdateData(FALSE);

	// Exit the program
	OnCancel();
}



void CREADProbeCalibrationDlg::OnAuto1a() 
{
	// The user pressed the button to automatically calibrate the probe for:
		// Station 1 - VDDP
		// This is probe array member #0
	// Call the UpdateProbe function
	UpdateProbe(0, "Station 1 VDDP");		
}

void CREADProbeCalibrationDlg::OnAuto1b() 
{
	// The user pressed the button to automatically calibrate the probe for:
		// Station 1 - VEXP
		// This is probe array member #1
	// Call the UpdateProbe function
	UpdateProbe(1, "Station 1 VEXP");
}

void CREADProbeCalibrationDlg::OnAuto2a() 
{
	// The user pressed the button to automatically calibrate the probe for:
		// Station 2 - VDDP
		// This is probe array member #2
	// Call the UpdateProbe function
	UpdateProbe(2, "Station 2 VDDP");
}

void CREADProbeCalibrationDlg::OnAuto2b() 
{
	// The user pressed the button to automatically calibrate the probe for:
		// Station 2 - VEXP
		// This is probe array member #3
	// Call the UpdateProbe function
	UpdateProbe(3, "Station 2 VEXP");	
}

void CREADProbeCalibrationDlg::OnAuto3a() 
{
	// The user pressed the button to automatically calibrate the probe for:
		// Station 3 - VDDP
		// This is probe array member #4
	// Call the UpdateProbe function
	UpdateProbe(4, "Station 3 VDDP");	
}

void CREADProbeCalibrationDlg::OnAuto3b() 
{
	// The user pressed the button to automatically calibrate the probe for:
		// Station 3 - VEXP
		// This is probe array member #5
	// Call the UpdateProbe function
	UpdateProbe(5, "Station 3 VEXP");	
}

void CREADProbeCalibrationDlg::OnAuto4a() 
{
	// The user pressed the button to automatically calibrate the probe for:
		// Station 4 - VDDP
		// This is probe array member #6
	// Call the UpdateProbe function
	UpdateProbe(6, "Station 4 VDDP");	
}

void CREADProbeCalibrationDlg::OnAuto4b() 
{
	// The user pressed the button to automatically calibrate the probe for:
		// Station 4 - VEXP
		// This is probe array member #7
	// Call the UpdateProbe function
	UpdateProbe(7, "Station 4 VEXP");	
}

void CREADProbeCalibrationDlg::OnAuto5a() 
{
	// The user pressed the button to automatically calibrate the probe for:
		// Station 5 - VDDP
		// This is probe array member #8
	// Call the UpdateProbe function
	UpdateProbe(8, "Station 5 VDDP");	
}

void CREADProbeCalibrationDlg::OnAuto5b() 
{
	// The user pressed the button to automatically calibrate the probe for:
		// Station 5 - VEXP
		// This is probe array member #9
	// Call the UpdateProbe function
	UpdateProbe(9, "Station 5 VEXP");	
}

void CREADProbeCalibrationDlg::OnAuto6a() 
{
	// The user pressed the button to automatically calibrate the probe for:
		// Station 6 - VDDP
		// This is probe array member #10
	// Call the UpdateProbe function
	UpdateProbe(10, "Station 6 VDDP");	
}

void CREADProbeCalibrationDlg::OnAuto6b() 
{
	// The user pressed the button to automatically calibrate the probe for:
		// Station 6 - VEXP
		// This is probe array member #11
	// Call the UpdateProbe function
	UpdateProbe(11, "Station 6 VEXP");	
}

void CREADProbeCalibrationDlg::OnSave() 
{
	// Declare variables
	FILE *filehandle;			// Pointer to open file
	CString filename;			// Name of the data file
	int i;						// Counter to index through the lines of the input files


	// Save all of the information on the interface - in case the user has modified any of it manually
	UpdateData(TRUE);
	probes[0].zero = m_s1_vddp_zero;
	probes[0].slope = m_s1_vddp_slope;
	probes[1].zero = m_s1_vexp_zero;
	probes[1].slope = m_s1_vexp_slope;

	probes[2].zero = m_s2_vddp_zero;
	probes[2].slope = m_s2_vddp_slope;
	probes[3].zero = m_s2_vexp_zero;
	probes[3].slope = m_s2_vexp_slope;

	probes[4].zero = m_s3_vddp_zero;
	probes[4].slope = m_s3_vddp_slope;
	probes[5].zero = m_s3_vexp_zero;
	probes[5].slope = m_s3_vexp_slope;

	probes[6].zero = m_s4_vddp_zero;
	probes[6].slope = m_s4_vddp_slope;
	probes[7].zero = m_s4_vexp_zero;
	probes[7].slope = m_s4_vexp_slope;

	probes[8].zero = m_s5_vddp_zero;
	probes[8].slope = m_s5_vddp_slope;
	probes[9].zero = m_s5_vexp_zero;
	probes[9].slope = m_s5_vexp_slope;

	probes[10].zero = m_s6_vddp_zero;
	probes[10].slope = m_s6_vddp_slope;
	probes[11].zero = m_s6_vexp_zero;
	probes[11].slope = m_s6_vexp_slope;


	// Open the previous calibration file for writing
	filehandle = fopen("read_probes.rcl", "w");
	
	// Write the calibration information to the data file
	for (i=0; i<12; i++)
	{
		// Write the current probe's information
		fprintf(filehandle, "%f\t%f\n", probes[i].zero, probes[i].slope);
	}

	// Close the file
	fclose( filehandle );
	
	// Send the user a message stating that the calibration has been saved
	MessageBox("The calibration has been saved.");
	
}
