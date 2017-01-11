// TestRunEngine.cpp : implementation file
//

#include "stdafx.h"
#include "READ Test.h"
#include "TestRunEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestRunEngine

CTestRunEngine::CTestRunEngine()
{
}

CTestRunEngine::CTestRunEngine(CString name, float motor_speed_value, int cycles, int seqNumber, int sectionAcyc, int sectionBcyc){
	filename = name;
	motorSpeed = motor_speed_value;
	revolutions = cycles;
	sequenceNumber = seqNumber;
	sectionA = sectionAcyc;
	sectionB = sectionBcyc;

	hole_countFilename = name;
	hole_countFilename.Right(4);
	hole_countFilename += "counterValues.csv";

}


CTestRunEngine::~CTestRunEngine()
{
}


BEGIN_MESSAGE_MAP(CTestRunEngine, CWnd)
	//{{AFX_MSG_MAP(CTestRunEngine)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTestRunEngine message handlers


bool CTestRunEngine::BufferedMode()
{
	short wfmchavect[] = {0, 1, 2, 3, 4, 5, 6, 7};
	short wfmgainvect[] = {1, 1, 1, 1, 1, 1, 1, 1, 1 , 1};
	short AIchavect[] = {0, 1, 2, 3, 4, 5, 6, 7, 16, 17, 18, 19};
	short AIgainvect[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	short motorchavect[1] = {8};
	short motorgainvect[1] = {1};
	CNIBoard* wfmGenOne = new CNIBoard(2, ISA_BOARD, 8, wfmchavect, wfmgainvect, 5760);
	CNIBoard* wfmGenTwo = new CNIBoard(3, ISA_BOARD, 8, wfmchavect, wfmgainvect, 5760);
	CNIBoard* wfmGenThree = new CNIBoard(4, ISA_BOARD, 8, wfmchavect, wfmgainvect, 5760);
	CNIBoard* AIandCTR = new CNIBoard(1, PCI_BOARD, 12, AIchavect, AIgainvect, 8640);
	CNIBoard* motor = new CNIBoard(4, ISA_BOARD, 1, motorchavect, motorgainvect, 0);
	CTestProgressIndicator* m_ProgressIndicator = new CTestProgressIndicator(this);

	int readvalue;
	bool returnvalue = FALSE;

    CString pzCycleDebugInfo;


	i16 iStatus = 0; // status value of NI function	
	i16 iRetVal = 0; // null returned value	
	i16 iIgnoreWarning = 0; // indicates to the error handler function to not ignore the warning
	int i = 0, j = 0, iDAQ = 0; // index variables
	clock_t start, finish;	// tracks start and finish time of each operation

	BOOL waveformPaused = FALSE;
	int countZeroComparator = 0;
	u32 prevCountZeroValue = 0;
	u32 ulCounterZeroValue = 0;
	u32 ulCounterValue = 0; // counter value of the onboard clock
	u32 positionCount = 0; // holds previous value of ulCounterValue
	u32 software_counter = 0; // increments each time the NI board's onboard clock changes value 

    const u32 ulCountDAQ = 8640; 	// size of the full buffer for double buffered input - 720 points in a cycle by 12 channels
	const u32 ulHalfBufferCount = 4320; // half the size of the full buffer

	// the following variables are set by the DAQ_DB_Transfer and DAQ_DB_HalfReady functions
    i16 iHalfReadyDB = 0; // flag to indicate that a half buffer is ready to transfered to disk

    const u32 ulCount = 5760; // size of the full buffer for double buffered output - 720 points in a cycle by 8 channels
    const u32 ulHalfCount = 2880; // half the size of the full buffer

	// the following variables are set by WFM_DB_HalfReady function
    i16 iHalfReady2 = 0; // flag to indicate that the half buffer for device 2 is ready to read values from disk 
    i16 iHalfReady3 = 0; // flag to indicate that the half buffer for device 3 is ready to read values from disk
    i16 iHalfReady4 = 0; // flag to indicate that the half buffer for device 4 is ready to read values from disk


	FILE* device2; // pointer to input file for device 2
	FILE* device3; // pointer to input file for device 3
	FILE* device4; // pointer to input file for device 4
	FILE* output; // pointer to output file 
	FILE* holecount;


	// ensure that motor speed has a non-zero value and there are cycles to run - otherwise inform the user to enter a non-zero value and/or to create a test
	if ((motorSpeed) && (revolutions)){
		
		
		m_ProgressIndicator->Create();
		// set the range of values on the graphical progress bar from 0 to m_revolutions
		m_ProgressIndicator->m_ProgressOfCycles.SetRange(0, revolutions);	

		// open the input files for reading data for device 2, 3 and 4
		device2 = fopen("device2.out", "r");
		device3 = fopen("device3.out", "r");
		device4 = fopen("device4.out", "r");

		holecount = fopen(hole_countFilename, "w");
		fprintf(holecount,"Counter1,PrevValue,Counter0,PrevValue\n");



		// open the output file for writing data for data recorded from data acquisition
		output = fopen(filename, "w");

		

		AIandCTR->GPCTR_Config(1);

		// start the counter 1
		AIandCTR->GPCTR_Enable(1);

		// Timing and counter configuration end 

	
		// Enable outputs - turn on digital enable 
		// configure the digital ports for output of data
		wfmGenThree->DIG_Port_Config();
		AIandCTR->DIG_Port_Config();
		// output values to the ports with all the bits set to 1
		wfmGenThree->DIG_Port_Enable(FOUR_BITS_ON);
		AIandCTR->DIG_Port_Enable(EIGHT_BITS_ON);

		

		//clear all outputs
		for( i = 0; i<8; i++){
			wfmGenOne->AO(i, 0);
			wfmGenTwo->AO(i, 0);
			wfmGenThree->AO(i, 0);
		}


		// Timing and counter configuration start 
		AIandCTR->GPCTR_Config(0);

		wfmGenOne->RTSI_Connect();
		wfmGenTwo->RTSI_Connect();
		wfmGenThree->RTSI_Connect();
		AIandCTR->RTSI_Connect();

		AIandCTR->GPCTR_Enable(0);

		// Double buffer input configuration start 
		AIandCTR->AI_Buffer_Config();

		// Double buffer input configuration end 

		// read in the initial values for the output buffers for devices 2, 3 and 4
		for (i = 0; i < (int) ulCount; i++){
			fscanf(device2, "%d", &readvalue);
			wfmGenOne->AddFullBufferElement(i, readvalue);

			fscanf(device3, "%d", &readvalue);
			wfmGenTwo->AddFullBufferElement(i, readvalue);

			fscanf(device4, "%d", &readvalue);
			wfmGenThree->AddFullBufferElement(i, readvalue);
		}

		// Double buffer output configuration start
		wfmGenOne->AO_Buffer_Config();
		wfmGenTwo->AO_Buffer_Config();
		wfmGenThree->AO_Buffer_Config();


		// start the motor by writing an analog value to the motor
		motor->AO(0, motorSpeed);
		

		// align the belt
		// wait for the belt to reach zero position by watching to see when the counter tracking the zero position hole switches values
		while ((( (int)ulCounterValue < 2) && (iStatus == 0)) && (!m_ProgressIndicator->CheckCancelButton())) {
			ulCounterValue = AIandCTR->GPCTR_Monitor(1);
			ulCounterZeroValue = AIandCTR->GPCTR_Monitor(0);

		} 


		positionCount = ulCounterValue;
		prevCountZeroValue = ulCounterZeroValue;


		// start wave form generation and start data acquisition
		AIandCTR->AI_Buffer_Start();
		wfmGenOne->AO_Buffer_Start();
		wfmGenTwo->AO_Buffer_Start();
		wfmGenThree->AO_Buffer_Start();

		// assign current cpu clock time to start (required for 
		// estimation of the time it takes for the cycles to be completed -
		// can also be thought of as the start time for the test)
		start = clock();	

		while ((( (int)software_counter < revolutions) && (iStatus == 0)) && (!m_ProgressIndicator->CheckCancelButton())) {

			countZeroComparator = ulCounterZeroValue - prevCountZeroValue;
			if (countZeroComparator >= BELT_ENCODER_HOLES){
				// if more than BELT_ENCODER_HOLES points pause the waveform
				wfmGenOne->AO_Buffer_Pause();
				wfmGenTwo->AO_Buffer_Pause();
				wfmGenThree->AO_Buffer_Pause();

				waveformPaused = TRUE;
				
			}



			// check if the half buffers are ready to be transferred to disk
			AIandCTR->AI_Buffer_Monitor(&iHalfReadyDB);

			if ( ( iHalfReadyDB == 1 ) && ( iStatus == 0 ) ){
				
  				software_counter++;

				// assign current cpu clock time to finish (this is used to 
				// get the time duration of how long the cycles run so far have taken -
				// this value is then used to estimate how long rest of the test will
				// take)
				finish = clock();	


				// transfer the half buffer and convert to voltage values and print to file
				AIandCTR->AI_Buffer_Transfer();
				for (iDAQ = 0; iDAQ < 4320; iDAQ = iDAQ+12){
					fprintf(output, "%d %d", (int) software_counter, ((iDAQ/12)+1));
					for(i = 0; i < 12; i++)
						fprintf(output, " %f", AIandCTR->GetHalfBufferElement(iDAQ+i));
					fprintf(output,"\n");
				}

				// to estimate time and cycles left to complete the test
				TimeCalculate((float)(finish - start) / CLOCKS_PER_SEC,(int) software_counter, m_ProgressIndicator); 
				m_ProgressIndicator->PumpMessages();


			} else 
				iRetVal = NIDAQErrorHandler(iStatus, "DAQ_DB_HalfReady", 0);
				
			if  ( ulCounterValue != positionCount ) {

				fprintf(holecount,"%d,%d,%d,%d,%d,%d\n", ulCounterValue, positionCount, 
					ulCounterZeroValue, prevCountZeroValue, (ulCounterValue - positionCount), 
					(ulCounterZeroValue - prevCountZeroValue));				
				pzCycleDebugInfo.Format("%d",(ulCounterValue - positionCount));
				// select entire edit box
				m_ProgressIndicator->m_ZeroPositionCounter.SetSel(0,-1,FALSE);	
				// replace selection with message
				m_ProgressIndicator->m_ZeroPositionCounter.ReplaceSel(pzCycleDebugInfo,TRUE);	

				pzCycleDebugInfo.Format("%d",(ulCounterZeroValue - prevCountZeroValue));
				// select entire edit box
				m_ProgressIndicator->m_HoleCounter.SetSel(0,-1,FALSE);	
				// replace selection with message
				m_ProgressIndicator->m_HoleCounter.ReplaceSel(pzCycleDebugInfo,TRUE);	
				m_ProgressIndicator->PumpMessages();
				// increment the software counter 
				
				positionCount = ulCounterValue;

				prevCountZeroValue = ulCounterZeroValue;
			
				if (waveformPaused){

					wfmGenOne->AO_Buffer_Continue();
					wfmGenTwo->AO_Buffer_Continue();
					wfmGenThree->AO_Buffer_Continue();
					// if waveform paused resume
					waveformPaused = FALSE;
				

				}


			} 



			// check if the half buffers are ready to be transferred to disk
			wfmGenOne->AO_Buffer_Monitor(&iHalfReady2);

			if ( iHalfReady2 == 1 ){

				// read in new value for the output buffers for device 2 as long as it is not the end of file
				// otherwise assign zeros to all output values
				for (i = 0; i < (int) ulHalfCount; i++){
					if ( !feof(device2) ){
						fscanf(device2, "%d", &readvalue);
						wfmGenOne->AddHalfBufferElement(i, readvalue);
					}
					else{
						wfmGenOne->AddHalfBufferElement(i, 0);
					}
				}
				// load up the new values for the output buffers for device 2
				wfmGenOne->AO_Buffer_Transfer();
			}

			// check if the half buffers are ready to be transferred to disk
			wfmGenTwo->AO_Buffer_Monitor(&iHalfReady3);

			if ( iHalfReady3 == 1 ){
				// read in new value for the output buffers for device 3 as long as it is not the end of file
				// otherwise assign zeros to all output values
				for (i = 0; i < (int) ulHalfCount; i++){
					if ( !feof(device3) ){
						fscanf(device3, "%d", &readvalue);
						wfmGenTwo->AddHalfBufferElement(i, readvalue);
					}
					else{
						wfmGenTwo->AddHalfBufferElement(i, 0);
					}
				}
				// load up the new values for the output buffers for device 3
				wfmGenTwo->AO_Buffer_Transfer();
			} 

			// check if the half buffers are ready to be transferred to disk
			wfmGenThree->AO_Buffer_Monitor(&iHalfReady4);

			if ( iHalfReady4 == 1 ){

				// read in new value for the output buffers for device 4 as long as it is not the end of file
				// otherwise assign zeros to all output values
				for (i = 0; i < (int) ulHalfCount; i++){
					if ( !feof(device4) ){
						fscanf(device4, "%d", &readvalue);
						wfmGenThree->AddHalfBufferElement(i, readvalue);
					}
					else{
						wfmGenThree->AddHalfBufferElement(i, 0);
					}
				}
				// load up the new values for the output buffers for device 4
				wfmGenThree->AO_Buffer_Transfer();
			} 

			// monitor the zero position hole to see what cycle the test is at
			ulCounterZeroValue = AIandCTR->GPCTR_Monitor(0);
			ulCounterValue = AIandCTR->GPCTR_Monitor(1);

			if (ulCounterValue == ND_YES) {
				MessageBox(" Counter reached terminal count! - The count may be incorrect.");
			}

			iRetVal = NIDAQYield(1);	

		} 

		wfmGenOne->AO_Buffer_Reset();
		wfmGenTwo->AO_Buffer_Reset();
		wfmGenThree->AO_Buffer_Reset();

		wfmGenOne->RTSI_Disconnect();
		wfmGenTwo->RTSI_Disconnect();
		wfmGenThree->RTSI_Disconnect();
		AIandCTR->RTSI_Disconnect();

		AIandCTR->AI_Buffer_Reset();

		AIandCTR->GPCTR_Reset(0);
		AIandCTR->GPCTR_Reset(1);
		
		// close files
		fclose(device2);
		fclose(device3);
		fclose(device4);
		fclose(output);
		fclose(holecount);

		// stop motor
		motor->AO(0, 0);

		//clear all outputs
		for( i = 0; i<8; i++){
			wfmGenOne->AO(i, 0);
			wfmGenTwo->AO(i, 0);
			wfmGenThree->AO(i, 0);
		}


		// turn off digital enable
		wfmGenThree->DIG_Port_Disable(BITS_OFF);
		wfmGenThree->DIG_Port_Reset();
		AIandCTR->DIG_Port_Disable(BITS_OFF);
		AIandCTR->DIG_Port_Reset();

		// destroy ModalLess Dialog box to indicate progress;
		m_ProgressIndicator->DestroyWindow();
		m_ProgressIndicator = NULL;

		returnvalue = TRUE;
	}
	// if the user failed to provide proper values
	// display proper messages on what values are missing
	else if ((!motorSpeed) && (!revolutions)){
		MessageBox("Please enter a non-zero value for motor speed and create a test.");

	}
	else if (!motorSpeed){
		MessageBox("Please enter a non-zero value for motor speed.");
	}
	else if (!revolutions){
		MessageBox("Please create a test.");
	}

	delete wfmGenOne;
	delete wfmGenTwo;
	delete wfmGenThree;
	delete AIandCTR;
	delete motor;
	delete m_ProgressIndicator;

	return returnvalue;
}


void CTestRunEngine::TimeCalculate(double time, int cycles, CTestProgressIndicator* m_ProgressIndicator)
{
	// average time per cycle
	float duration = (float)(time/cycles);	

	// cycles left to complete in the test
	int remainingCycles = revolutions - cycles;	

	// estimated time to complete test
	int timeToComplete = (int) (duration * remainingCycles);	

	// seconds to be displayed
	int seconds = (timeToComplete%60);	

	// minutes to be displayed
	int minutes = (((timeToComplete-seconds)/60)%60);	

	// hours to be displayed
	int hours = ((timeToComplete-seconds-(minutes*60))/3600);	

	// message that will be displayed on dialog box */
	CString message = " ";	

	// display hours, minutes and seconds when value for hours is greater than zero
	if (hours>0)	
	{

		message.Format("%d hrs %d min %d sec", hours, minutes, seconds);
		// select entire edit box
		m_ProgressIndicator->m_TimeLeft.SetSel(0,-1,FALSE);	

		// replace selection with message
		m_ProgressIndicator->m_TimeLeft.ReplaceSel(message,TRUE);	

	}
	// else display minutes and seconds when value for minutes is greater than zero
	else if (minutes > 0)	
	{
		message.Format("%d min %d sec", minutes, seconds);
		// select entire edit box
		m_ProgressIndicator->m_TimeLeft.SetSel(0,-1,FALSE);	

		// replace selection with mesage
		m_ProgressIndicator->m_TimeLeft.ReplaceSel(message,TRUE);	
	}
	// else display seconds when value for seconds is greater than zero
	else if (seconds > 0)	
	{
		message.Format("%d sec", seconds);
		// select entire edit box
		m_ProgressIndicator->m_TimeLeft.SetSel(0,-1,FALSE);	

		// replace selection with message
		m_ProgressIndicator->m_TimeLeft.ReplaceSel(message,TRUE);	
	}
	// else display test completion message when value for time left is zero
	else	
	{
		message = "Test completed.";

		// select entire edit box
		m_ProgressIndicator->m_TimeLeft.SetSel(0,-1,FALSE);	

		// replace selection with message
		m_ProgressIndicator->m_TimeLeft.ReplaceSel(message,TRUE);	
	}
		message.Format("%d cycles left.", remainingCycles);

		// select entire edit box
		m_ProgressIndicator->m_CyclesLeft.SetSel(0,-1,FALSE);	

		// replace selection with message
		m_ProgressIndicator->m_CyclesLeft.ReplaceSel(message,TRUE);	

		// increment graphical progress bar by a step
		m_ProgressIndicator->m_ProgressOfCycles.SetPos(cycles);	

}



bool CTestRunEngine::NonBufferedMode()
{

	short AOchavect[] = {0, 1, 2, 3, 4, 5, 6, 7};
	short AOgainvect[] = {1, 1, 1, 1, 1, 1, 1, 1, 1 , 1};
	short AIchavect[] = {0, 1, 2, 3, 4, 5, 6, 7, 16, 17, 18, 19};
	short AIgainvect[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	short motorchavect[] = {8};
	short motorgainvect[] = {1};
	CNIBoard* AOOne = new CNIBoard(2, ISA_BOARD, 8, AOchavect, AOgainvect, 5760);
	CNIBoard* AOTwo = new CNIBoard(3, ISA_BOARD, 8, AOchavect, AOgainvect, 5760);
	CNIBoard* AOThree = new CNIBoard(4, ISA_BOARD, 8, AOchavect, AOgainvect, 5760);
	CNIBoard* AIandCTR = new CNIBoard(1, PCI_BOARD, 12, AIchavect, AIgainvect, 8640);
	CNIBoard* motor = new CNIBoard(4, ISA_BOARD, 1, motorchavect, motorgainvect, 0);
	CTestProgressIndicator* m_ProgressIndicator = new CTestProgressIndicator(this);

	int readvalue;
	int prevComp = -1;
	bool returnvalue = FALSE;

	CString pzCycleDebugInfo;
	

	i16 iStatus = 0; // status value of NI function	
	i16 iRetVal = 0; // null returned value	
	i16 iIgnoreWarning = 0; // indicates to the error handler function to not ignore the warning
	int i = 0, j = 0, iDAQ = 0; // index variables
	clock_t start, finish;	// tracks start and finish time of each operation
	
	int countZeroComparator = 0;
	u32 prevCountZeroValue = 0;
	u32 ulCounterZeroValue = 0;
	u32 ulCounterValue = 0; // counter value of the onboard clock
	u32 positionCount = 0; // holds previous value of ulCounterValue
	u32 software_counter = 0; // increments each time the NI board's onboard clock changes value 


    const u32 ulCountDAQ = 8640; 	// size of the full buffer for double buffered input - 720 points in a cycle by 12 channels
	const u32 ulHalfBufferCount = 4320; // half the size of the full buffer

    const u32 ulCount = 5760; // size of the full buffer for double buffered output - 720 points in a cycle by 8 channels
    const u32 ulHalfCount = 2880; // half the size of the full buffer


	FILE* device2; // pointer to input file for device 2
	FILE* device3; // pointer to input file for device 3
	FILE* device4; // pointer to input file for device 4
	FILE* output; // pointer to output file 
	FILE* holecount;

	// ensure that motor speed has a non-zero value and there are cycles to run - otherwise inform the user to enter a non-zero value and/or to create a test
	if ((motorSpeed) && (revolutions)){
		
		
		m_ProgressIndicator->Create();
		// set the range of values on the graphical progress bar from 0 to m_revolutions
		m_ProgressIndicator->m_ProgressOfCycles.SetRange(0, revolutions);	

		// open the input files for reading data for device 2, 3 and 4
		device2 = fopen("device2.out", "r");
		device3 = fopen("device3.out", "r");
		device4 = fopen("device4.out", "r");

		holecount = fopen(hole_countFilename, "w");
		fprintf(holecount,"Counter1,PrevValue,Counter0,PrevValue\n");

		// open the output file for writing data for data recorded from data acquisition
		output = fopen(filename, "w");
		


		AIandCTR->GPCTR_Config(1);

		// start the counter 1
		AIandCTR->GPCTR_Enable(1);

		// Timing and counter configuration end 

	
		// Enable outputs - turn on digital enable 
		// configure the digital ports for output of data
		AOThree->DIG_Port_Config();
		AIandCTR->DIG_Port_Config();
		// output values to the ports with all the bits set to 1
		AOThree->DIG_Port_Enable(FOUR_BITS_ON);
		AIandCTR->DIG_Port_Enable(EIGHT_BITS_ON);

		

		//clear all outputs
		for( i = 0; i<8; i++){
			AOOne->AO(i, 0);
			AOTwo->AO(i, 0);
			AOThree->AO(i, 0);
		}


		// Timing and counter configuration start 
		AIandCTR->GPCTR_Config(0);

		AIandCTR->GPCTR_Enable(0);

		// read in the initial values for the output buffers for devices 2, 3 and 4
		for (i = 0; i < (int) ulHalfCount; i++){
			fscanf(device2, "%d", &readvalue);
			AOOne->AddHalfBufferElement(i, readvalue);

			fscanf(device3, "%d", &readvalue);
			AOTwo->AddHalfBufferElement(i, readvalue);

			fscanf(device4, "%d", &readvalue);
			AOThree->AddHalfBufferElement(i, readvalue);
		}

		// start the motor by writing an analog value to the motor
		motor->AO(0, motorSpeed);
		

		// align the belt
		// wait for the belt to reach zero position by watching to see when the counter tracking the zero position hole switches values
		while ((( (int)ulCounterValue < 1) && (iStatus == 0)) && (!m_ProgressIndicator->CheckCancelButton())) {
			ulCounterValue = AIandCTR->GPCTR_Monitor(1);
			ulCounterZeroValue = AIandCTR->GPCTR_Monitor(0);

		} 


		positionCount = ulCounterValue;
		prevCountZeroValue = ulCounterZeroValue;


		// assign current cpu clock time to start (required for 
		// estimation of the time it takes for the cycles to be completed -
		// can also be thought of as the start time for the test)
		start = clock();	

		while ((( (int)software_counter < revolutions) && (iStatus == 0)) && (!m_ProgressIndicator->CheckCancelButton())) {

			countZeroComparator = ulCounterZeroValue - prevCountZeroValue;
			if ((countZeroComparator < BELT_ENCODER_HOLES) && (countZeroComparator != prevComp)){
				prevComp = countZeroComparator;
				AOOne->MultiChanAO(countZeroComparator);
				AOTwo->MultiChanAO(countZeroComparator);
				AOThree->MultiChanAO(countZeroComparator);
				AIandCTR->MultiChanAI(countZeroComparator);
			}


			if  ( ulCounterValue != positionCount ) {
				if (countZeroComparator == BELT_ENCODER_HOLES){  // THIS CONDITION ENFORCES THAT THE CYCLE
												  // HAS TO BE A PERFECT BELT_ENCODER_HOLES ELSE THE CYCLE
												  // WILL BE REPEATED
  					software_counter++;
					finish = clock();

					for (i = 0; i < (int) ulHalfCount; i++){
						fscanf(device2, "%d", &readvalue);
						AOOne->AddHalfBufferElement(i, readvalue);

						fscanf(device3, "%d", &readvalue);
						AOTwo->AddHalfBufferElement(i, readvalue);

						fscanf(device4, "%d", &readvalue);
						AOThree->AddHalfBufferElement(i, readvalue);
					}

					for (iDAQ = 0; iDAQ < 4320; iDAQ = iDAQ+12){
						fprintf(output, "%d %d", (int) software_counter, ((iDAQ/12)+1));
						for(i = 0; i < 12; i++)
							fprintf(output, " %f", AIandCTR->GetHalfBufferElement(iDAQ+i));
						fprintf(output,"\n");
					}

					// to estimate time and cycles left to complete the test
					TimeCalculate((float)(finish - start) / CLOCKS_PER_SEC,(int) software_counter, m_ProgressIndicator); 

				}

				fprintf(holecount,"%d,%d,%d,%d,%d,%d\n", ulCounterValue, positionCount, 
					ulCounterZeroValue, prevCountZeroValue, (ulCounterValue - positionCount), 
					(ulCounterZeroValue - prevCountZeroValue));	

				pzCycleDebugInfo.Format("%d",(ulCounterValue - positionCount));
				// select entire edit box
				m_ProgressIndicator->m_ZeroPositionCounter.SetSel(0,-1,FALSE);	
				// replace selection with message
				m_ProgressIndicator->m_ZeroPositionCounter.ReplaceSel(pzCycleDebugInfo,TRUE);	

				pzCycleDebugInfo.Format("%d",(ulCounterZeroValue - prevCountZeroValue));
				// select entire edit box
				m_ProgressIndicator->m_HoleCounter.SetSel(0,-1,FALSE);	
				// replace selection with message
				m_ProgressIndicator->m_HoleCounter.ReplaceSel(pzCycleDebugInfo,TRUE);	
				m_ProgressIndicator->PumpMessages();
				// increment the software counter 
				
				positionCount = ulCounterValue;

				prevCountZeroValue = ulCounterZeroValue;
			} 
				

			// monitor the zero position hole to see what cycle the test is at
			ulCounterZeroValue = AIandCTR->GPCTR_Monitor(0);
			ulCounterValue = AIandCTR->GPCTR_Monitor(1);

			if (ulCounterValue == ND_YES) {
				MessageBox(" Counter reached terminal count! - The count may be incorrect.");
			}

			iRetVal = NIDAQYield(1);	

		} 

		AIandCTR->GPCTR_Reset(0);
		AIandCTR->GPCTR_Reset(1);
		
		// close files
		fclose(device2);
		fclose(device3);
		fclose(device4);
		fclose(output);
		fclose(holecount);

		// stop motor
		motor->AO(0, 0);

		//clear all outputs
		for( i = 0; i<8; i++){
			AOOne->AO(i, 0);
			AOTwo->AO(i, 0);
			AOThree->AO(i, 0);
		}


		// turn off digital enable
		AOThree->DIG_Port_Disable(BITS_OFF);
		AOThree->DIG_Port_Reset();
		AIandCTR->DIG_Port_Disable(BITS_OFF);
		AIandCTR->DIG_Port_Reset();

		// destroy ModalLess Dialog box to indicate progress;
		m_ProgressIndicator->DestroyWindow();
		m_ProgressIndicator = NULL;

		returnvalue = TRUE;
	}
	// if the user failed to provide proper values
	// display proper messages on what values are missing
	else if ((!motorSpeed) && (!revolutions)){
		MessageBox("Please enter a non-zero value for motor speed and create a test.");

	}
	else if (!motorSpeed){
		MessageBox("Please enter a non-zero value for motor speed.");
	}
	else if (!revolutions){
		MessageBox("Please create a test.");
	}

	delete AOOne;
	delete AOTwo;
	delete AOThree;
	delete AIandCTR;
	delete motor;
	delete m_ProgressIndicator;
	return returnvalue;

}


bool CTestRunEngine::NonBufferedDynamicMode()
{

	int pointsPerHole = 512;

	short AOchavect[] = {0, 1, 2, 3, 4, 5, 6, 7};
	short AOgainvect[] = {1, 1, 1, 1, 1, 1, 1, 1, 1 , 1};
	short AIchavect[] = {0, 1, 2, 3, 4, 5, 6, 7, 16, 17, 18, 19};
	short AIgainvect[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	short motorchavect[] = {8};
	short motorgainvect[] = {1};
	CNIBoard* AOOne = new CNIBoard(2, ISA_BOARD, 8, AOchavect, AOgainvect, 0);
	CNIBoard* AOTwo = new CNIBoard(3, ISA_BOARD, 8, AOchavect, AOgainvect, 0);
	CNIBoard* AOThree = new CNIBoard(4, ISA_BOARD, 8, AOchavect, AOgainvect, 0);
	CNIBoard* AIandCTR = new CNIBoard(1, PCI_BOARD, 12, AIchavect, AIgainvect, 0);
	CNIBoard* motor = new CNIBoard(4, ISA_BOARD, 1, motorchavect, motorgainvect, 0);
	CTestProgressIndicator* m_ProgressIndicator = new CTestProgressIndicator(this);
	CString deviceOutputfile;

	int readvalue;
	int prevComp = -1;
	bool returnvalue = FALSE;

	CString pzCycleDebugInfo;
	
	i16 iStatus = 0; // status value of NI function	
	i16 iRetVal = 0; // null returned value	
	i16 iIgnoreWarning = 0; // indicates to the error handler function to not ignore the warning
	int i = 0, j = 0, iDAQ = 0; // index variables
	clock_t start, finish;	// tracks start and finish time of each operation
	
	int countZeroComparator = 0;
	u32 prevCountZeroValue = 0;
	u32 ulCounterZeroValue = 0;
	u32 ulCounterValue = 0; // counter value of the onboard clock
	u32 positionCount = 0; // holds previous value of ulCounterValue
	int software_counter = 0; // increments each time the NI board's onboard clock changes value 


    const u32 ulCountDAQ = 24*BELT_ENCODER_HOLES; 	// size of the full buffer for double buffered input - 720 points in a cycle by 12 channels
	const u32 ulHalfBufferCount = 12*BELT_ENCODER_HOLES; // half the size of the full buffer

    const u32 ulCount = 16*BELT_ENCODER_HOLES; // size of the full buffer for double buffered output - 720 points in a cycle by 8 channels
    const u32 ulHalfCount = 8*BELT_ENCODER_HOLES; // half the size of the full buffer


	FILE* device2; // pointer to input file for device 2
	FILE* device3; // pointer to input file for device 3
	FILE* device4; // pointer to input file for device 4
	FILE* output; // pointer to output file 
	FILE* holecount;

	CDataList* ao1ListPtr = new CDataList(ulHalfCount, SHORT_TYPE);
	CDataList* ao1CurrentStubPtr = ao1ListPtr;
	CDataList* ao2ListPtr = new CDataList(ulHalfCount, SHORT_TYPE);
	CDataList* ao2CurrentStubPtr = ao2ListPtr;
	CDataList* ao3ListPtr = new CDataList(ulHalfCount, SHORT_TYPE);
	CDataList* ao3CurrentStubPtr = ao3ListPtr;
	CDataList* aiListPtr = new CDataList(ulHalfBufferCount, DOUBLE_TYPE);
	CDataList* aiCurrentStubPtr = aiListPtr;


	AOOne->AssignBuffer(ao1CurrentStubPtr->GetCurrentStub(), SHORT_TYPE);
	AOTwo->AssignBuffer(ao2CurrentStubPtr->GetCurrentStub(), SHORT_TYPE);
	AOThree->AssignBuffer(ao3CurrentStubPtr->GetCurrentStub(), SHORT_TYPE);
	AIandCTR->AssignBuffer(aiCurrentStubPtr->GetCurrentStub(), DOUBLE_TYPE);
	// ensure that motor speed has a non-zero value and 
	// there are cycles to run - otherwise inform the user to enter 
	// a non-zero value and/or to create a test

	if ((motorSpeed > 0.01) && (revolutions)){
		
		
		m_ProgressIndicator->Create();
		// set the range of values on the graphical progress bar from 0 to m_revolutions
		m_ProgressIndicator->m_ProgressOfCycles.SetRange(0, revolutions);	

		// open the input files for reading data for device 2, 3 and 4
		deviceOutputfile.Format("device2_seq_%d.out", sequenceNumber);
		device2 = fopen(deviceOutputfile, "r");
		deviceOutputfile.Format("device3_seq_%d.out", sequenceNumber);
		device3 = fopen(deviceOutputfile, "r");
		deviceOutputfile.Format("device4_seq_%d.out", sequenceNumber);
		device4 = fopen(deviceOutputfile, "r");

		holecount = fopen(hole_countFilename, "w");
		fprintf(holecount,"Counter1,PrevValue,Counter0,PrevValue\n");

		// open the output file for writing data for data recorded from data acquisition
		output = fopen(filename, "w");
		


		AIandCTR->GPCTR_Config(1);

		// start the counter 1
		AIandCTR->GPCTR_Enable(1);

		// Timing and counter configuration end 

	
		// Enable outputs - turn on digital enable 
		// configure the digital ports for output of data
		AOThree->DIG_Port_Config();
		AIandCTR->DIG_Port_Config();
		// output values to the ports with all the bits set to 1
		AOThree->DIG_Port_Enable(FOUR_BITS_ON);
		AIandCTR->DIG_Port_Enable(EIGHT_BITS_ON);

		

		//clear all outputs
		for( i = 0; i<8; i++){
			AOOne->AO(i, 0);
			AOTwo->AO(i, 0);
			AOThree->AO(i, 0);
		}


		// Timing and counter configuration start 
		AIandCTR->GPCTR_Config(0);

		AIandCTR->GPCTR_Enable(0);

		// read in the values for the output buffers for devices 2, 3 and 4
		for (iDAQ = 0; iDAQ < revolutions; iDAQ++){
			for (i = 0; i < (int) ulHalfCount; i++){
				fscanf(device2, "%d", &readvalue);
				AOOne->AddHalfBufferElement(i, readvalue);

				fscanf(device3, "%d", &readvalue);
				AOTwo->AddHalfBufferElement(i, readvalue);

				fscanf(device4, "%d", &readvalue);
				AOThree->AddHalfBufferElement(i, readvalue);
			}
			if (iDAQ != (revolutions - 1)){ 
				ao1CurrentStubPtr->AttachNode(new CDataList(ulHalfCount, SHORT_TYPE));
				ao1CurrentStubPtr = ao1CurrentStubPtr->Forward();
				ao2CurrentStubPtr->AttachNode(new CDataList(ulHalfCount, SHORT_TYPE));
				ao2CurrentStubPtr = ao2CurrentStubPtr->Forward();
				ao3CurrentStubPtr->AttachNode(new CDataList(ulHalfCount, SHORT_TYPE));
				ao3CurrentStubPtr = ao3CurrentStubPtr->Forward();
				AOOne->AssignBuffer(ao1CurrentStubPtr->GetCurrentStub(), SHORT_TYPE);
				AOTwo->AssignBuffer(ao2CurrentStubPtr->GetCurrentStub(), SHORT_TYPE);
				AOThree->AssignBuffer(ao3CurrentStubPtr->GetCurrentStub(), SHORT_TYPE);
			}
		}
		ao1CurrentStubPtr = ao1ListPtr;
		ao2CurrentStubPtr = ao2ListPtr;
		ao3CurrentStubPtr = ao3ListPtr;
		AOOne->AssignBuffer(ao1CurrentStubPtr->GetCurrentStub(), SHORT_TYPE);
		AOTwo->AssignBuffer(ao2CurrentStubPtr->GetCurrentStub(), SHORT_TYPE);
		AOThree->AssignBuffer(ao3CurrentStubPtr->GetCurrentStub(), SHORT_TYPE);

		// start the motor by writing an analog value to the motor
		motor->AO(0, motorSpeed);
		

		// align the belt
		// wait for the belt to reach zero position by watching to see when the counter tracking the zero position hole switches values
		while ((( (int)ulCounterValue < 1) && (iStatus == 0)) && (!m_ProgressIndicator->CheckCancelButton())) {
			ulCounterValue = AIandCTR->GPCTR_Monitor(1);
			ulCounterZeroValue = AIandCTR->GPCTR_Monitor(0);
		} 


		positionCount = ulCounterValue;
		prevCountZeroValue = ulCounterZeroValue;


		// assign current cpu clock time to start (required for 
		// estimation of the time it takes for the cycles to be completed -
		// can also be thought of as the start time for the test)
		start = clock();	

		while ((( software_counter < revolutions) && (iStatus == 0)) && (!m_ProgressIndicator->CheckCancelButton())) {
			
			if (prevCountZeroValue > ulCounterZeroValue)
				countZeroComparator = (ulCounterZeroValue + (16777215 - prevCountZeroValue))/pointsPerHole;
			else
				countZeroComparator = (ulCounterZeroValue - prevCountZeroValue)/pointsPerHole;

			if ((countZeroComparator < BELT_ENCODER_HOLES) && (countZeroComparator != prevComp)){
				prevComp = countZeroComparator;
				AOOne->MultiChanAO(countZeroComparator);
				AOTwo->MultiChanAO(countZeroComparator);
				AOThree->MultiChanAO(countZeroComparator);
				AIandCTR->MultiChanAI(countZeroComparator);
			}


			if  ( ulCounterValue != positionCount ) {
				if (countZeroComparator == BELT_ENCODER_HOLES){  // THIS CONDITION ENFORCES THAT THE CYCLE
												  // HAS TO BE A PERFECT BELT_ENCODER_HOLES ELSE THE CYCLE
												  // WILL BE REPEATED
  					software_counter++;
					finish = clock();

					if (software_counter != revolutions){
						// THIS LIMITS THE SECTIONA cycles AND SECTIONB cycles
						if ((software_counter <= sectionA) ||  // section A cycles
							( ( ((software_counter - sectionA)%sectionB) == 0 ) || // last cycle in section B
							( ((software_counter - sectionA)%sectionB) == (sectionB - 1) ) ) ) // cycle before last cycle in section B
						ao1CurrentStubPtr = ao1CurrentStubPtr->Forward();
						ao2CurrentStubPtr = ao2CurrentStubPtr->Forward();
						ao3CurrentStubPtr = ao3CurrentStubPtr->Forward();
						AOOne->AssignBuffer(ao1CurrentStubPtr->GetCurrentStub(), SHORT_TYPE);
						AOTwo->AssignBuffer(ao2CurrentStubPtr->GetCurrentStub(), SHORT_TYPE);
						AOThree->AssignBuffer(ao3CurrentStubPtr->GetCurrentStub(), SHORT_TYPE);

						aiCurrentStubPtr->AttachNode(new CDataList(ulHalfBufferCount, DOUBLE_TYPE));
						aiCurrentStubPtr = aiCurrentStubPtr->Forward();
						AIandCTR->AssignBuffer(aiCurrentStubPtr->GetCurrentStub(), DOUBLE_TYPE);
					}

					// to estimate time and cycles left to complete the test
					TimeCalculate((float)(finish - start) / CLOCKS_PER_SEC,(int) software_counter, m_ProgressIndicator); 

				}

				fprintf(holecount,"%d,%d,%d,%d,%d,%d\n", ulCounterValue, positionCount, 
					ulCounterZeroValue, prevCountZeroValue, (ulCounterValue - positionCount), 
					(ulCounterZeroValue - prevCountZeroValue));	

				pzCycleDebugInfo.Format("%d",(ulCounterValue - positionCount));
				// select entire edit box
				m_ProgressIndicator->m_ZeroPositionCounter.SetSel(0,-1,FALSE);	
				// replace selection with message
				m_ProgressIndicator->m_ZeroPositionCounter.ReplaceSel(pzCycleDebugInfo,TRUE);	

				pzCycleDebugInfo.Format("%d",(ulCounterZeroValue - prevCountZeroValue));
				// select entire edit box
				m_ProgressIndicator->m_HoleCounter.SetSel(0,-1,FALSE);	
				// replace selection with message
				m_ProgressIndicator->m_HoleCounter.ReplaceSel(pzCycleDebugInfo,TRUE);	
				m_ProgressIndicator->PumpMessages();
				// increment the software counter 
				
				positionCount = ulCounterValue;

				prevCountZeroValue = ulCounterZeroValue;
			} 
				

			// monitor the zero position hole to see what cycle the test is at
			ulCounterZeroValue = AIandCTR->GPCTR_Monitor(0);
			ulCounterValue = AIandCTR->GPCTR_Monitor(1);

			if (ulCounterValue == ND_YES) {
				MessageBox(" Counter reached terminal count! - The count may be incorrect.");
			}

			iRetVal = NIDAQYield(1);	

		} 

		aiCurrentStubPtr = aiListPtr;
		for (i = 0; i < software_counter; i++){
			AIandCTR->AssignBuffer(aiCurrentStubPtr->GetCurrentStub(), DOUBLE_TYPE);

			for (iDAQ = 0; iDAQ < ulHalfBufferCount; iDAQ = iDAQ+12){
				fprintf(output, "%d %d", (i+1), ((iDAQ/12)+1));
				for(j = 0; j < 12; j++)
					fprintf(output, " %f", AIandCTR->GetHalfBufferElement(iDAQ+j));
				fprintf(output,"\n");
			}
			
			aiCurrentStubPtr = aiCurrentStubPtr->Forward();
			if (aiCurrentStubPtr == NULL)
				i = software_counter;
		}


		AIandCTR->GPCTR_Reset(0);
		AIandCTR->GPCTR_Reset(1);
		
		// close files
		fclose(device2);
		fclose(device3);
		fclose(device4);
		fclose(output);
		fclose(holecount);

		// stop motor by stepping it down
		while (motorSpeed > 0.1){
			motor->AO(0, motorSpeed); 	NIDAQDelay(1);
			motorSpeed = motorSpeed - 0.2;
		}
		motor->AO(0, 0.000);
/*		if (motorSpeed > 9.0){
			motor->AO(0, 9.0000); 	NIDAQDelay(2);
			motor->AO(0, 7.0000); 	NIDAQDelay(2);
			motor->AO(0, 5.0000);  	NIDAQDelay(2);
			motor->AO(0, 3.0000);	NIDAQDelay(2);
			motor->AO(0, 1.0000);	NIDAQDelay(2);
			motor->AO(0, 0.0000);	
		}
		else if (motorSpeed > 7.0){
			motor->AO(0, 7.0000); 	NIDAQDelay(2);
			motor->AO(0, 5.0000);  	NIDAQDelay(2);
			motor->AO(0, 3.0000);	NIDAQDelay(2);
			motor->AO(0, 1.0000);	NIDAQDelay(2);
			motor->AO(0, 0.0000);	
		}
		else if (motorSpeed > 5.0){
			motor->AO(0, 5.0000);  	NIDAQDelay(2);
			motor->AO(0, 3.0000);	NIDAQDelay(2);
			motor->AO(0, 1.0000);	NIDAQDelay(2);
			motor->AO(0, 0.0000);	
		}
		else if (motorSpeed > 3.0){
			motor->AO(0, 3.0000);	NIDAQDelay(2);
			motor->AO(0, 1.0000);	NIDAQDelay(2);
			motor->AO(0, 0.0000);	
		}
		else if (motorSpeed > 1.0){
			motor->AO(0, 1.0000);	NIDAQDelay(2);
			motor->AO(0, 0.0000);	
		}
		else
			motor->AO(0, 0.0000);	
*/

		//clear all outputs
		for( i = 0; i<8; i++){
			AOOne->AO(i, 0);
			AOTwo->AO(i, 0);
			AOThree->AO(i, 0);
		}


		// turn off digital enable
		AOThree->DIG_Port_Disable(BITS_OFF);
		AOThree->DIG_Port_Reset();
		AIandCTR->DIG_Port_Disable(BITS_OFF);
		AIandCTR->DIG_Port_Reset();

		// destroy ModalLess Dialog box to indicate progress;
		m_ProgressIndicator->DestroyWindow();
		m_ProgressIndicator = NULL;

		delete ao1ListPtr;
		delete ao2ListPtr;
		delete ao3ListPtr;
		delete aiListPtr;
		ao1CurrentStubPtr = NULL;
		ao2CurrentStubPtr = NULL;
		ao3CurrentStubPtr = NULL;
		aiCurrentStubPtr = NULL;

		// assign null buffer thus when object is deleted
		// deconstructor doesn't access unreferenced memory
		AOOne->AssignBuffer(NULL, SHORT_TYPE);
		AOTwo->AssignBuffer(NULL, SHORT_TYPE);
		AOThree->AssignBuffer(NULL, SHORT_TYPE);
		AIandCTR->AssignBuffer(NULL, DOUBLE_TYPE);
		

		returnvalue = TRUE;
	}
	// if the user failed to provide proper values
	// display proper messages on what values are missing
	else if ((motorSpeed < 0.01) && (!revolutions)){
		MessageBox("Please enter a non-zero value for motor speed and create a test.");

	}
	else if (motorSpeed < 0.01){
		MessageBox("Please enter a non-zero value for motor speed.");
	}
	else if (!revolutions){
		MessageBox("Please create a test.");
	}

	delete AOOne;
	delete AOTwo;
	delete AOThree;
	delete AIandCTR;
	delete motor;
	delete m_ProgressIndicator;

	return returnvalue;

}
