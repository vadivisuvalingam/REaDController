// TestBuildEngine.cpp : implementation file
//

#include "stdafx.h"
#include "READ Test.h"
#include "TestBuildEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestBuildEngine

CTestBuildEngine::CTestBuildEngine()
{
}

CTestBuildEngine::~CTestBuildEngine()
{
}


BEGIN_MESSAGE_MAP(CTestBuildEngine, CWnd)
	//{{AFX_MSG_MAP(CTestBuildEngine)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTestBuildEngine message handlers

float* CTestBuildEngine::returnPidcIncrements(int cycles)
{
	//float pidc_increment[6]; 
	int index;
	float highest_value;
	int i, temp;
	char* name;
	FILE* instream;
	for (index = 0; index < 6; index++){
		// read the highest value from the lookup table
		// array_filenames 1,5,9,13,17,21 corresponds to Expose
		temp = 1 +(index*4);
		name = Page2TestSequence.array_filenames[temp].GetBuffer(Page2TestSequence.array_filenames[temp].GetLength());

		if ((instream = fopen(name, "r")) != NULL){
			for (i = 0; i < BIPOLAR_PRECISION; i++)
				fscanf(instream, "%f %f", &highest_value, &highest_value);
		}
		fclose(instream);

		// calculate increment value
		global_pidc_increment[index] = highest_value / cycles;

	}
	return global_pidc_increment;

}

int* CTestBuildEngine::returnPidcExpose(int currentcycle, float *pidc_increment)
{
	//int pidc_expose[6];
	int index;
	float lookUpValue;

	for (index = 0; index < 6; index++){
		lookUpValue = currentcycle * pidc_increment[index];
		// read the expose value for the current cycle from lookup table
		// array_filenames 1,5,9,13,17,21 corresponds to Expose
		global_pidc_expose[index] = Page2TestSequence.LightDevice_LookUpAndConvert(Page2TestSequence.array_filenames[1+(index*4)], lookUpValue);
	}
	return global_pidc_expose;


}