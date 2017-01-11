// NIBoard.cpp: implementation of the CNIBoard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "READ Test.h"
#include "NIBoard.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNIBoard::CNIBoard()
{

}

CNIBoard::CNIBoard(int device, int bus_Arch, int numChans, short* chanVect, short* gainVect, int count){
	CString AlertMessage;
	iDevice = device;
	iBus_Arch = bus_Arch;
	iNumChans = numChans;
	piChanVect = chanVect;
	piGainVect = gainVect;
	ulCount = count;
	pdBuffer = (double*) malloc(ulCount*sizeof(double));
	pdHalfBuffer = (double*) malloc((0.5)*ulCount*sizeof(double));
	piBuffer = (short*) malloc(ulCount*sizeof(short));
	piHalfBuffer = (short*) malloc((0.5)*ulCount*sizeof(short));


}

CNIBoard::~CNIBoard()
{
	free(pdBuffer);
	free(pdHalfBuffer);
	free(piBuffer);
	free(piHalfBuffer);
}

void CNIBoard::GPCTR_Config(int iCounter)
{
	int iStatus, iRetVal;
	unsigned long counter, source;
	if (iCounter == 0){
		counter = ND_COUNTER_0;
		source = ND_PFI_1;
	}
	else if (iCounter == 1){
		counter = ND_COUNTER_1;
		source = ND_PFI_8;
	}

	iStatus = GPCTR_Control(iDevice, counter, ND_RESET);	
	iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/RESET", 0);

	iStatus = GPCTR_Set_Application(iDevice, counter, ND_SIMPLE_EVENT_CNT); 	
	iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Set_Application", 0);

	iStatus = GPCTR_Change_Parameter(iDevice, counter, ND_SOURCE, source);		
	iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Change_Parameter/SOURCE", 0);

	iStatus = GPCTR_Change_Parameter(iDevice, counter, ND_INITIAL_COUNT, 0);		
	iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Change_Parameter/INITCOUNT", 0);	
}

void CNIBoard::GPCTR_Enable(int iCounter)
{
	int iStatus, iRetVal;
	unsigned long counter;
	if (iCounter == 0){
		counter = ND_COUNTER_0;
	}
	else if (iCounter == 1){
		counter = ND_COUNTER_1;
	}

	iStatus = GPCTR_Control(iDevice, counter, ND_PROGRAM);		
	iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/PROGRAM", 0);

}

void CNIBoard::GPCTR_Disable(int iCounter)
{
	int iStatus, iRetVal;
	unsigned long counter;
	if (iCounter == 0){
		counter = ND_COUNTER_0;
	}
	else if (iCounter == 1){
		counter = ND_COUNTER_1;
	}

	iStatus = GPCTR_Control(iDevice, counter, ND_DISARM);		
	iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/DISARM", 0);
	
}

void CNIBoard::GPCTR_Reset(int iCounter)
{
	int iStatus, iRetVal;
	unsigned long counter;
	if (iCounter == 0){
		counter = ND_COUNTER_0;
	}
	else if (iCounter == 1){
		counter = ND_COUNTER_1;
	}

	iStatus = GPCTR_Control(iDevice, counter, ND_RESET);		
	iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Control/RESET", 0);

}

int CNIBoard::GPCTR_Monitor(int iCounter)
{
	int iStatus, iRetVal;
	unsigned long counter, counter_value;
	if (iCounter == 0){
		counter = ND_COUNTER_0;
	}
	else if (iCounter == 1){
		counter = ND_COUNTER_1;
	}

	iStatus = GPCTR_Watch(1, counter, ND_COUNT, &counter_value);
	iRetVal = NIDAQErrorHandler(iStatus, "GPCTR_Watch/COUNT", 0);	

	return (int) counter_value;

}


void CNIBoard::DIG_Port_Config()
{
	int iStatus, iRetVal;
	iStatus = DIG_Prt_Config(iDevice, 0, 0, 1);
    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Prt_Config", 0);	  

}

void CNIBoard::DIG_Port_Enable(unsigned long bit_pattern)
{
	int iStatus, iRetVal;
	iStatus = DIG_Out_Port(iDevice, 0, bit_pattern);
	iRetVal = NIDAQErrorHandler(iStatus, "DIG_Out_Prt", 0);

}

void CNIBoard::DIG_Port_Disable(unsigned long bit_pattern)
{
	int iStatus, iRetVal;
	iStatus = DIG_Out_Port(iDevice, 0, bit_pattern);
	iRetVal = NIDAQErrorHandler(iStatus, "DIG_Out_Prt", 0);

}

void CNIBoard::DIG_Port_Reset()
{
	int iStatus, iRetVal;
	iStatus = DIG_Prt_Config(iDevice, 0, 0, 0);
    iRetVal = NIDAQErrorHandler(iStatus, "DIG_Prt_Config", 0);	  

}

void CNIBoard::AI_Buffer_Config()
{
	int iStatus, iRetVal;
	iStatus = Select_Signal(iDevice, ND_IN_SCAN_START, ND_PFI_8, ND_LOW_TO_HIGH);		
	iRetVal = NIDAQErrorHandler(iStatus, "Select_Signal", 0);	
	iStatus = DAQ_Config(iDevice, 0, 2);		
	iRetVal = NIDAQErrorHandler(iStatus, "DAQ_Config", 0);	
	iStatus = DAQ_DB_Config(iDevice, 1);		
	iRetVal = NIDAQErrorHandler(iStatus, "DAQ_DB_Config", 0);
	iStatus = DAQ_Rate(10000.0, 0, &iSampTB, &uSampInt);
	iStatus = SCAN_Setup(1, iNumChans, piChanVect, piGainVect);		
	iRetVal = NIDAQErrorHandler(iStatus, "SCAN_Setup", 0);	
	
}

void CNIBoard::AI_Buffer_Reset()
{
	int iStatus;
	iStatus = DAQ_Config(iDevice, 0, 0);
	iStatus = Select_Signal(iDevice, ND_IN_SCAN_START, ND_INTERNAL_TIMER, ND_LOW_TO_HIGH);
	iStatus = DAQ_Clear(iDevice);
	iStatus = DAQ_DB_Config(iDevice, 0);

}

void CNIBoard::AI_Buffer_Start()
{
	int iStatus, iRetVal;
	iStatus = SCAN_Start(iDevice, piBuffer, ulCount, iSampTB, uSampInt, 0, 0);		
	iRetVal = NIDAQErrorHandler(iStatus, "SCAN_Start", 0);	
}

void CNIBoard::AI_Buffer_Monitor(short* iHalfReady)
{
	int iStatus;
	short iDAQstopped = ND_NO;
	iStatus = DAQ_DB_HalfReady(1, iHalfReady, &iDAQstopped);
}

void CNIBoard::AI_Buffer_Transfer()
{
	int iStatus, iRetVal;
	unsigned long ulPtsTfr;
	short iDAQstopped = ND_NO;
	iStatus = DAQ_DB_Transfer(iDevice, piHalfBuffer, &ulPtsTfr, &iDAQstopped);	
	iRetVal = NIDAQErrorHandler(iStatus, "DAQ_DB_Transfer",	 0);
	iStatus = DAQ_VScale(iDevice, 1, 1, 1.0, 0.0, (0.5*ulCount), piHalfBuffer, pdHalfBuffer);	
	iRetVal = NIDAQErrorHandler(iStatus, "DAQ_VScale", 0);	

}

void CNIBoard::AO_Buffer_Config()
{
	int iStatus, iRetVal;
	iStatus = WFM_DB_Config(iDevice, iNumChans, piChanVect,  1, 1, 0);    
	iRetVal = NIDAQErrorHandler(iStatus, "WFM_DB_Config",  0);
	iStatus = WFM_Group_Setup(iDevice, iNumChans, piChanVect,  1);
	iRetVal = NIDAQErrorHandler(iStatus, "WFM_Group_Setup",  0);
	iStatus = WFM_Load(iDevice, iNumChans, piChanVect, piBuffer, ulCount, 0, 0);  
	iRetVal = NIDAQErrorHandler(iStatus, "WFM_Load",  0);
	iStatus = WFM_ClockRate(iDevice, 1, 0, 0, 0, 0);    
	iRetVal = NIDAQErrorHandler(iStatus, "WFM_ClockRate",  0);

}

void CNIBoard::AO_Buffer_Start()
{
	int iStatus, iRetVal;
	iStatus = WFM_Group_Control(iDevice, 1, 1);         
	iRetVal = NIDAQErrorHandler(iStatus, "WFM_Group_Control/START", 0);
}

void CNIBoard::AO_Buffer_Pause()
{
	int iStatus, iRetVal;
	iStatus = WFM_Group_Control(iDevice, 1, 2);         
	iRetVal = NIDAQErrorHandler(iStatus, "WFM_Group_Control/PAUSE", 0);
}

void CNIBoard::AO_Buffer_Continue()
{
	int iStatus, iRetVal;
	iStatus = WFM_Group_Control(iDevice, 1, 4);         
	iRetVal = NIDAQErrorHandler(iStatus, "WFM_Group_Control/CONTINUE", 0);
}

void CNIBoard::AO_Buffer_Monitor(short* iHalfReady)
{
	int iStatus;
	iStatus = WFM_DB_HalfReady(iDevice, iNumChans, piChanVect, iHalfReady);
}

void CNIBoard::AO_Buffer_Reset()
{
	short iWFMstopped = 0;
	unsigned long ulItersDone, ulPtsDone;
	int iStatus, iRetVal;
	while (iWFMstopped != 1)  {

		iStatus = WFM_Check(iDevice, 0, &iWFMstopped, &ulItersDone, &ulPtsDone);
      	iRetVal = NIDAQYield(1);
  
	} 

	iStatus = WFM_Group_Control(iDevice, 1, 0);
	iStatus = WFM_DB_Config(iDevice, iNumChans, piChanVect, 0, 0, 0);

}

void CNIBoard::AO_Buffer_Transfer()
{
	int iStatus, iRetVal;
	iStatus = WFM_DB_Transfer(iDevice, iNumChans, piChanVect, piHalfBuffer, (0.5*ulCount));  
	iRetVal = NIDAQErrorHandler(iStatus,  "WFM_DB_Transfer3", 0);

}

void CNIBoard::RTSI_Connect()
{
	int iStatus, iRetVal;
	if (iBus_Arch == ISA_BOARD){
		iStatus = RTSI_Conn (iDevice, 5, 3, 0);	    
		iRetVal = NIDAQErrorHandler(iStatus, "RTSI_Conn", 0);
	}
	else if (iBus_Arch == PCI_BOARD) {
		iStatus = Select_Signal(iDevice, ND_RTSI_3, ND_GPCTR0_SOURCE, ND_LOW_TO_HIGH );		
		iRetVal = NIDAQErrorHandler(iStatus, "Select_Signal", 0);
	}
}

void CNIBoard::RTSI_Disconnect()
{
	int iStatus, iRetVal;
	if (iBus_Arch == ISA_BOARD){
		iStatus = RTSI_Conn (iDevice, 5, 3, 0);	    
		iRetVal = NIDAQErrorHandler(iStatus, "RTSI_Conn", 0);
	}
	else if (iBus_Arch == PCI_BOARD) {
		iStatus = Select_Signal(iDevice, ND_RTSI_3, ND_GPCTR0_SOURCE, ND_LOW_TO_HIGH );		
		iRetVal = NIDAQErrorHandler(iStatus, "Select_Signal", 0);
	}
}

void CNIBoard::AO(int iChan, double iValue)
{
	AO_VWrite(iDevice, piChanVect[iChan], iValue);
}

void CNIBoard::AI(int iChan, double* iValue)
{
	AI_VRead(iDevice, piChanVect[iChan], piGainVect[iChan], iValue);
}

void CNIBoard::AddFullBufferElement(int index, int value)
{
	piBuffer[index] = value;
}

void CNIBoard::AddHalfBufferElement(int index, int value)
{
	piHalfBuffer[index] = value;
}

double CNIBoard::GetFullBufferElement(int index)
{
	double returnvalue = pdBuffer[index];
	pdBuffer[index] = 0;
	return returnvalue;
}

double CNIBoard::GetHalfBufferElement(int index)
{
	double returnvalue = pdHalfBuffer[index];
	pdHalfBuffer[index] = 0;
	return returnvalue;
}

void CNIBoard::MultiChanAO(int index)
{
	int i = 0;
	for ( i = 0; i < iNumChans; i++ )
		AO_Write(iDevice, piChanVect[i], piHalfBuffer[(index*iNumChans)+i]);

}

void CNIBoard::MultiChanAI(int index)
{
	int i = 0;
	for ( i = 0; i < iNumChans; i++ )
		AI_VRead(iDevice, piChanVect[i], piGainVect[i], &pdHalfBuffer[(index*iNumChans)+i]);

}

void CNIBoard::AssignBuffer(void* bufferptr, int type)
{
	if (type == SHORT_TYPE)
		piHalfBuffer = (short*)bufferptr;
	if (type == DOUBLE_TYPE)
		pdHalfBuffer = (double*)bufferptr;
}
