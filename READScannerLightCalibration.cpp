// READScannerLightCalibration.cpp : implementation file
//

#include "stdafx.h"
#include "direct.h"
#include "READ Test.h"
#include "READ TestDlg.h"
#include "READScannerLightCalibration.h"
#include "nidaq.h"
#include "nidaqex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// READScannerLightCalibration property page

IMPLEMENT_DYNCREATE(READScannerLightCalibration, CPropertyPage)

READScannerLightCalibration::READScannerLightCalibration() : CPropertyPage(READScannerLightCalibration::IDD)
{
	//{{AFX_DATA_INIT(READScannerLightCalibration)
		// NOTE: the ClassWizard will add member initialization here
	m_int_aichan = 0;
	m_int_aochan = 0;
	m_int_aodev = 0;
	m_int_aidev = 0;
	m_scaling = 0.0;
	m_int_wait = 0;

	//}}AFX_DATA_INIT
}

READScannerLightCalibration::~READScannerLightCalibration()
{
}

void READScannerLightCalibration::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(READScannerLightCalibration)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, ID_AI_CHANNEL, m_int_aichan);
	DDX_Text(pDX, ID_AO_CHANNEL, m_int_aochan);
	DDX_Text(pDX, ID_AO_DEVICE, m_int_aodev);
	DDX_Text(pDX, ID_AI_DEVICE, m_int_aidev);
	DDX_Text(pDX, ID_SCALE, m_scaling);
	DDX_Text(pDX, ID_WAIT, m_int_wait);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(READScannerLightCalibration, CPropertyPage)
	//{{AFX_MSG_MAP(READScannerLightCalibration)
	ON_BN_CLICKED(ID_RUN, OnRun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// READScannerLightCalibration message handlers

void READScannerLightCalibration::OnRun() 
{
	/* The run button has been pressed */
	
	// Declare constants
	const int max_bit_setting = BIPOLAR_PRECISION - 1;	// Maximum setting of the analog output card (in bits)
	char currentDirectory[ _MAX_PATH ]; // character buffer to hold the directory path
	// Declare variables
	FILE *filehandle;			// Pointer to open file
	CString filename;			// Name of the data file
	// Object to describe the file and path
	CFileDialog filetoopen(FALSE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Light Calibration Files (*.rsi)|*.rsi|All Files (*.*)|*.*||");

	int istatus;				// Status variable for functions to return
	int bitsetting;				// Setting in bits, to be set to the analog ouput channel DAC
	
	u32 delaycount;				// Counter value at the beginning of the delay period
	u32 cnt = 0;

	f64 reading[1];				// Present voltage measurement
	f64 lightoutput;			// Amount of light measured by the detector


	// Read the settings specified by the user.  (On the interface)
	UpdateData(true);

	// get the current working directory - this ensure the program returns to the 
	// proper working directory after the user makes their selection of a directory path for the test files
	_getcwd( currentDirectory, _MAX_PATH );
	

	// Display the dialog to get the user to specify a destination file for the data
	if ( filetoopen.DoModal() == IDOK )
	{
		// change back to the current working directory
		_chdir( currentDirectory );

		// Get the user to specify a file name for the calibration data - use the standard windows dialog
		filename = filetoopen.GetPathName();
		
		// Build the name of the data file - include the rsi extension if there is no rsi extension
		if (filename.Right(3) != "rsi")
			filename = filename + ".rsi";
	

		// Check the scaling to avoid divide by zero errors
		if (m_scaling == 0)
		{
			// The scaling was left blank or set to zero
			// Set the scaling to pass through exactly the voltage read
			m_scaling = 1;
			// Send a message stating that there was a problem with the scaling
			MessageBox("The scaling was either not entered or was set to zero.  The data file will contain only the voltages read.");
		}
	

		// Open the file for writing
		filehandle = fopen( filename, "w");

	
		if (m_int_wait == 0)
				// Set the delay to 1 ms as a default
				m_int_wait = 100;
			else
				// Scale the delay to the proper number of ms
						/* Because the user specifies the number of ms to wait, and the board will be configured for a 
						100 kHz clock, we must convert the specified wait time to the number of clocks to wait*/
				m_int_wait = m_int_wait * 100;

		/* Set up the counter for the delay	*/
		// Reset the counter
		istatus = GPCTR_Control(m_int_aidev, ND_COUNTER_0, ND_RESET);
		// Set the counter to count
		istatus = GPCTR_Set_Application(m_int_aidev, ND_COUNTER_0, ND_SIMPLE_EVENT_CNT);
		// Set the counter for 100kHz on-board clock
		istatus = GPCTR_Change_Parameter(m_int_aidev, ND_COUNTER_0, ND_SOURCE, ND_INTERNAL_100_KHZ);
	
		istatus = GPCTR_Change_Parameter(m_int_aidev, ND_COUNTER_0, ND_INITIAL_COUNT, cnt);
		// Set the counter to increment on high to low transitions
		istatus = GPCTR_Change_Parameter(m_int_aidev, ND_COUNTER_0, ND_SOURCE_POLARITY, ND_HIGH_TO_LOW);
		// Set the counter to count up
		istatus = GPCTR_Change_Parameter(m_int_aidev, ND_COUNTER_0, ND_UP_DOWN, ND_COUNT_UP);



		for (bitsetting = 0; bitsetting <= max_bit_setting ; bitsetting++)
		{
			// Update the progress indicator

		
			// Output analog setting to device
			istatus = AO_Write(m_int_aodev, m_int_aochan,bitsetting);


			// Wait - read the amount of delay from the interface
					/*	status = CTR_Pulse (deviceNumber, ctr, timebase, delay, pulseWidth)
						m_int_aidev is the device number of the DAQ board
						1 is the number of the counter channel
						timebase 3 is the 10kHz on-board clock
						5 is delay before the pulse(in .1ms)
						5 is the width of the pulse (in .1ms)
					*/

			GPCTR_Control(m_int_aidev, ND_COUNTER_0, ND_PROGRAM);
			// Record the value of the counter - to count the delay later
			GPCTR_Watch(m_int_aidev, ND_COUNTER_0, ND_COUNT, &delaycount);

			// Set the current delay to zero
			cnt = 0;

			// Wait
			while (cnt <= m_int_wait)
			{
				GPCTR_Watch(m_int_aidev, ND_COUNTER_0, ND_COUNT, &cnt);
				cnt = cnt - delaycount;
			}



			// Read the voltage input for the calibration channel
					/*	status = AI_VRead (deviceNumber, chan, gain, voltage)
						m_int_aidev is the device number of the DAQ board
						m_int_aichan is the channel number where the meter is connected
						1 is the gain setting - unity gain
						reading is the location of the data returned
					*/
			istatus = AI_VRead(m_int_aidev, m_int_aichan, 1, reading);
			
			// Scale the reading - light = Vmeasured/Scaling
			lightoutput = reading[0] / m_scaling;

			// Record the bit setting and the calibration reading to a data file
			fprintf(filehandle, "%d\t%2.4f\n", bitsetting, lightoutput);
		


		}	// End of loop


		// Set the light device back to zero
		istatus = AO_Write(m_int_aodev, m_int_aochan,0);

		// Close the file
		fclose( filehandle );

		// Let the user know that execution is complete
		MessageBox("The calibration is complete.");

	}	// End of cancel condition	


}

// this function is called by the framework when the property page becomes active
// it overrides the default implementation CPropertyPage::OnSetActive() by adding some extra functionality
BOOL READScannerLightCalibration::OnSetActive() 
{
	// update values from the dialog box
	UpdateData(TRUE);
	CREADTestApp* pApp = (CREADTestApp*) AfxGetApp(); // pointer to the main CWinApp object
	CREADTestDlg* dlg = (CREADTestDlg*) pApp->m_pMainWnd; // pointer to the main window
	// if the scaling value is not zero assign the value to m_scaling
	if (dlg->tab3Modified_LightMeterScalingCalculator.m_scale_factor != 0) 
		m_scaling = dlg->tab3Modified_LightMeterScalingCalculator.m_scale_factor;
	// update the dialog box
	UpdateData(FALSE);
	// set the current page active
	return CPropertyPage::OnSetActive();
}
