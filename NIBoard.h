// NIBoard.h: interface for the CNIBoar d class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NIBOARD_H__ED1F2734_C6F4_11D6_90EE_E50D9E0B4591__INCLUDED_)
#define AFX_NIBOARD_H__ED1F2734_C6F4_11D6_90EE_E50D9E0B4591__INCLUDED_

#include "DataList.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNIBoard  
{
public:
	void AssignBuffer(void* bufferptr, int type);
	void MultiChanAI(int index);
	void MultiChanAO(int index);
	double GetHalfBufferElement(int index);
	double GetFullBufferElement(int index);
	void AddHalfBufferElement(int index, int value);
	void AddFullBufferElement(int index, int value);

	void RTSI_Disconnect();
	void RTSI_Connect();

	void AO(int iChan, double iValue);
	void AI(int iChan, double* iValue);

	void AO_Buffer_Transfer();
	void AO_Buffer_Reset();
	void AO_Buffer_Monitor(short* iHalfReady);
	void AO_Buffer_Continue();
	void AO_Buffer_Pause();
	void AO_Buffer_Start();
	void AO_Buffer_Config();

	void AI_Buffer_Transfer();
	void AI_Buffer_Monitor(short* iHalfReady);
	void AI_Buffer_Start();
	void AI_Buffer_Reset();
	void AI_Buffer_Config();

	void DIG_Port_Reset();
	void DIG_Port_Disable(unsigned long bit_pattern);
	void DIG_Port_Enable(unsigned long bit_pattern);
	void DIG_Port_Config();

	int GPCTR_Monitor(int iCounter);
	void GPCTR_Reset(int iCounter);
	void GPCTR_Disable(int iCounter);
	void GPCTR_Enable(int iCounter);
	void GPCTR_Config(int iCounter);
	CNIBoard(int device, int bus_Arch, int numChans, short* chanVect, short* gainVect, int count);
	CNIBoard();
	virtual ~CNIBoard();

private:
	int ulCount;
	short iSampTB;
	unsigned short uSampInt;
	short iNumChans;
	double* pdBuffer;
	double* pdHalfBuffer;
	short* piBuffer;
	short* piHalfBuffer;
	short* piGainVect;
	short* piChanVect;
	int iDevice;
	int iBus_Arch;
};

#endif // !defined(AFX_NIBOARD_H__ED1F2734_C6F4_11D6_90EE_E50D9E0B4591__INCLUDED_)
