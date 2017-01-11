// MotorSpeed.cpp : implementation file
//

#include "stdafx.h"
#include "READ Test.h"
#include "MotorSpeed.h"
#include "nidaq.h"
#include "nidaqex.h"
#include <time.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMotorSpeed dialog

IMPLEMENT_DYNCREATE(CMotorSpeed, CPropertyPage)


CMotorSpeed::CMotorSpeed() : CPropertyPage(CMotorSpeed::IDD)
{
	m_MotorSpeed = 0.0;//3.300000;
	//{{AFX_DATA_INIT(CMotorSpeed)
	m_MotorspeedInches = 0.0f;//10.87f;
	m_MotorspeedRPM = 0.0f;//8.4507f;
	//}}AFX_DATA_INIT
}

CMotorSpeed::~CMotorSpeed()
{
}


void CMotorSpeed::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMotorSpeed)
	DDX_Control(pDX, IDC_PROGRESSOFTABLECREATION, m_progress_of_table_creation);
	DDX_Text(pDX, IDC_MOTORSPEED, m_MotorspeedInches);
	DDX_Text(pDX, IDC_MOTORSPEEDRPM, m_MotorspeedRPM);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMotorSpeed, CDialog)
	//{{AFX_MSG_MAP(CMotorSpeed)
	ON_BN_CLICKED(IDC_CREATETABLES, OnCreatetables)
	ON_BN_CLICKED(IDC_CONVERTTORPM, OnConverttorpm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMotorSpeed message handlers

// This function loads up a lookup table from a file.  It matches the given
// lookup value with a value on the table and returns the value from the 
// table.  
float CMotorSpeed::LookUpAndConvert(CString lookupfile, float m_lookup)
{
	FILE* instream;  // pointer to file

	const int arraySize = 47;  // array size
	float tempArray [arraySize] [2];	// array to store look up table values that are read in from file

	// index variable
	int i = 0;	
	
	// open file for reading, check if file is null
	if((instream = fopen(lookupfile,"r"))!=NULL){
		/* read in look up table values and store to float array */
		while (i < arraySize)
		{
			fscanf(instream,"%f %f", &tempArray [i] [1], &tempArray [i] [0]);
			i++;
		}

		fclose(instream);	// close file
		i = 0;	// reset index

		/* browse through the table up till the point where m_lookup is not greater
		   than the [i] value in the look up table. If m_lookup is less than the average
		   of the [i] value and the [i-1] value - assign m_lookup to the [i-1] value. 
		   Otherwise assign m_lookup to the [i] value. */
		if (m_lookup != 0){
			while ((m_lookup > tempArray [i] [0]) && (i < (arraySize - 1))){i++;}

			if (m_lookup < ((tempArray [i-1] [0] + tempArray [i] [0]) / 2))
				m_lookup = tempArray [i-1] [1];
			else
				m_lookup = tempArray [i] [1];
		}

		// return matched value
		return (m_lookup);
	}
	// if the file is null alert user that the function is unable to open up the file
	else{
		lookupfile = "Unable to open " + lookupfile;
		MessageBox(lookupfile);
		return 0;
	}


}


// this function is called when the user presses create table button
// it creates the lookup tables for the rpm lookup and the analog voltage output look up
// the function starts the motor at a specific analog output value, takes a start time and runs the motor for a number of cycles
// when the cycles finish the motor takes a stop time and calculates the average time that 
// it takes for the motor to complete a cycle 
void CMotorSpeed::OnCreatetables() 
{

	float motorspeed = 0.5;  // analog voltage output value of motorspeed
	float increment = 0.2;  // value by which the analog voltage value shall increase
	u32 ulCounterValue = 0; // value of the counter
	i16 iStatus = 0; // status value of NI function calls
	i16 iRetVal = 0; // null returned value
	int cycles_per_applied_voltage = 10; // number of cycles that the motor shall run for a specific analog voltage output value
	int holes_in_cycles = BELT_ENCODER_HOLES * cycles_per_applied_voltage * 512; // number of holes to be covered in all of the cycles combined - this because the counter monitors the holes.
	float length = BELT_LENGTH_INCHES; // length of the belt in inches, used to correspond inches per sec to RPM
	clock_t start, finish; // variables to hold the start and finish times
	float duration; // holds the duration of time between start and finish
	float rpm; // holds the calculated RPM value
	float inches_per_sec; // holds the calculated inches per sec value
	int position = 0; // position handle = value of the progress indicator
	FILE *outstream1; // pointer to output file
	FILE *outstream2; // pointer to output file
	FILE *outstream3; // pointer to output file
	int messageoption;

	
	messageoption = MessageBox("Do you wish to create tables?\nThis will take approximately an hour.", "Motor Speed Control", MB_YESNO | MB_ICONSTOP);

	if (messageoption == IDYES){

		// open the motorspeed.csv file and check whether it is null
		// motorspeed.csv holds the duration and cycles value
		if ((outstream1 = fopen("motorspeed.csv", "w")) != NULL){
			// open the rpm_lookup.rsi file and check whether it is null
			// rpm_lookup.rsi file holds the calculated rpm and inches per sec value
			if ((outstream2 = fopen("rpm_lookup.rsi", "w")) != NULL){
				// open the analog_lookup.rsi file and check whether it is null
				//  analog_lookup holds the analog voltage output value and it's corresponding rpm
				if ((outstream3 = fopen("analog_lookup.rsi", "w")) != NULL){

					// set the progress bar
					m_progress_of_table_creation.SetRange(0,47);

					// continue the test while analog value for motorspeed is less than 9.8 V - the board doesn't exceed the 10 V range
					while (motorspeed < 9.8){

						ulCounterValue = 0;  // reset the counter value
						// calibrate the on board NI counter 0 to do simple event counting by tracking signals on i/o connecter PFI 8
						// reset the counter 0
						iStatus = GPCTR_Control(1, ND_COUNTER_0, ND_RESET);	iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/RESET", 0);
						// set the counter 0 to do simple event counting
						iStatus = GPCTR_Set_Application(1, ND_COUNTER_0, ND_SIMPLE_EVENT_CNT); 	iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Set_Application", 0);
						// specify the source for the counter as i/o connector PFI 8
						iStatus = GPCTR_Change_Parameter(1, ND_COUNTER_0, ND_SOURCE, ND_PFI_1);		iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Change_Parameter/SOURCE", 0);
						// set the initial value on the counter
						iStatus = GPCTR_Change_Parameter(1, ND_COUNTER_0, ND_INITIAL_COUNT, ulCounterValue);		iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Change_Parameter/INITCOUNT", 0);	

						// start the motor by writing the analog output voltage contained in motorspeed
						AO_VWrite (4, 8, motorspeed);
						// start the counter
						iStatus = GPCTR_Control(1, ND_COUNTER_0, ND_PROGRAM);		iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/PROGRAM", 0);
						// assign the current cpu clock time to the variable start
						start = clock();
						do {
							// poll the counter 0 and assign the counter value to ulCounterValue
							iStatus = GPCTR_Watch(1, ND_COUNTER_0, ND_COUNT, &ulCounterValue);			iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Watch/COUNT", 0);	
							// yield for other devices
							iRetVal = NIDAQYield(1);
							// assign current cpu clock time to the variable finish
							finish = clock();

						// continue this as long as the number of cycles hasn't been exceed and no problems occured
						} while (( (int)ulCounterValue <= holes_in_cycles) && (iStatus == 0));
						// the time duration in seconds is the time difference between the start time and finish time
						duration = (float) ((finish-start)/CLOCKS_PER_SEC);
						// rpm is the number of cycles divided by the time duration in seconds multiplied by 60 seconds per minute
						rpm = (cycles_per_applied_voltage / duration) * 60;
						// inches per second is the rpm multiplied by the length of the belt divided by 60 seconds per minute
						inches_per_sec = rpm * length / 60;
						// print to the output files
						fprintf(outstream1,"%f, %d \n", duration, cycles_per_applied_voltage);
						fprintf(outstream2,"%f %f \n", rpm, inches_per_sec);
						fprintf(outstream3,"%f %f \n", motorspeed, rpm);
				
						// increment the motorspeed - if you change the increment it affects the file size of the lookup table thus
						// ensure to modify the LookupAndConvert function to appropriately handle the new tables
						motorspeed = motorspeed + increment;
						// increment position handle
						position++;
						// indicate progress of the test on the progress control
						m_progress_of_table_creation.SetPos(position);
				
					}

					// close the file analog_lookup.rsi
					fclose(outstream3);
					// stop the motor by write an analog output value of 0 volts
					AO_VWrite(4, 8, 7.0);
					NIDAQDelay(2);
					AO_VWrite(4, 8, 6.0);
					NIDAQDelay(2);
					AO_VWrite(4, 8, 5.0);
					NIDAQDelay(2);
					AO_VWrite(4, 8, 3.0);
					NIDAQDelay(2);
					AO_VWrite(4, 8, 2.0);
					NIDAQDelay(2);
					AO_VWrite(4, 8, 0.0);
				}
				// if the file analog_lookup.rsi is null inform the user that the file could not be opened
				else
					MessageBox("Could not open the analog out look up table file.");

				// close the file rpm_lookup.rsi
				fclose(outstream2);
			}
			// if the file rpm_lookup.rsi is null inform the user that the file could not be opened
			else
				MessageBox("Could not open the RPM look up table file.");

			// close the file motorspeed.csv
			fclose(outstream1);
		}
		// if the file motorspeed.csv is null inform the user that the file could not be opened
		else
			MessageBox("Could not open the General Results file.");
	}
}

// this function is called when the user presses the Convert button
// it looks up the rpm value based on the user input for the inches per sec value
void CMotorSpeed::OnConverttorpm() 
{
	// update variables associated with the dialog box
	UpdateData(TRUE);
	// look up rpm and assign it to m_MotorspeedRPM
	m_MotorspeedRPM = LookUpAndConvert("rpm_lookup.rsi", m_MotorspeedInches);
	// update the dialog box
	UpdateData(FALSE);
}


void CMotorSpeed::Load(CString filename)
{
	FILE* instream;
	if ((instream = fopen(filename, "r")) != NULL) {
		fscanf(instream, "%f %f %f", &m_MotorSpeed, &m_MotorspeedInches, &m_MotorspeedRPM);
		fclose(instream);
	}
	else{
		filename = filename + " missing or corrupted.";
		MessageBox(filename);
	}
}

void CMotorSpeed::Save(CString filename)
{
	FILE* outstream;
	if ((outstream = fopen(filename, "w")) != NULL) {
		fprintf(outstream, "%f\n%f\n%f\n", m_MotorSpeed, m_MotorspeedInches, m_MotorspeedRPM);
		fclose(outstream);
	}
	else{
		filename = filename + " missing or corrupted.";
		MessageBox(filename);
	}


}

