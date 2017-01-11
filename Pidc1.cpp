// Pidc1.cpp : implementation file
//

#include "stdafx.h"
#include <direct.h>
#include "READ Test.h"
#include "READ TestDlg.h"
#include "Pidc1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPidc property page

IMPLEMENT_DYNCREATE(CPidc, CPropertyPage)

CPidc::CPidc() : CPropertyPage(CPidc::IDD)
{
	m_expose = 0.0f;
	//{{AFX_DATA_INIT(CPidc)
	m_cycles = 0;
	m_erase = 0.0f;
	m_grid = 0.0f;
	m_pin = 0.0f;
	m_s1 = FALSE;
	m_s2 = FALSE;
	m_s3 = FALSE;
	m_s4 = FALSE;
	m_s5 = FALSE;
	m_s6 = FALSE;
	//}}AFX_DATA_INIT
}

CPidc::~CPidc()
{
}

void CPidc::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPidc)
	DDX_Text(pDX, IDC_PIDC_CYCLES, m_cycles);
	DDX_Text(pDX, IDC_PIDC_ERASE, m_erase);
	DDX_Text(pDX, IDC_PIDC_GRID, m_grid);
	DDX_Text(pDX, IDC_PIDC_PIN, m_pin);
	DDX_Check(pDX, IDC_CHECK_S1_ERASE, m_s1);
	DDX_Check(pDX, IDC_CHECK_S2_ERASE, m_s2);
	DDX_Check(pDX, IDC_CHECK_S3_ERASE, m_s3);
	DDX_Check(pDX, IDC_CHECK_S4_ERASE, m_s4);
	DDX_Check(pDX, IDC_CHECK_S5_ERASE, m_s5);
	DDX_Check(pDX, IDC_CHECK_S6_ERASE, m_s6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPidc, CPropertyPage)
	//{{AFX_MSG_MAP(CPidc)
	ON_BN_CLICKED(IDC_CHECK_S1_ERASE, OnCheckS1Erase)
	ON_BN_CLICKED(IDC_CHECK_S2_ERASE, OnCheckS2Erase)
	ON_BN_CLICKED(IDC_CHECK_S3_ERASE, OnCheckS3Erase)
	ON_BN_CLICKED(IDC_CHECK_S4_ERASE, OnCheckS4Erase)
	ON_BN_CLICKED(IDC_CHECK_S5_ERASE, OnCheckS5Erase)
	ON_BN_CLICKED(IDC_CHECK_S6_ERASE, OnCheckS6Erase)
	ON_BN_CLICKED(IDC_LOAD_PIDC, OnLoadPidc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPidc message handlers

// this function is called by the framework when the property page becomes active
// it overrides the default implementation CPropertyPage::OnSetActive() by adding some extra functionality
BOOL CPidc::OnSetActive() 
{
	CREADTestApp* pApp = (CREADTestApp*) AfxGetApp();  // pointer to main CWinApp object
	CREADTestDlg* dlg = (CREADTestDlg*) pApp->m_pMainWnd; // pointer to main window
	// set the wizard buttons NEXT and BACK active for this page
	dlg->m_pBuildTestProperties.SetWizardButtons(PSWIZB_NEXT | PSWIZB_BACK);	
	// update dialog box
	UpdateData(FALSE);
	// set the page to be active
	return CPropertyPage::OnSetActive();
}

// this function is called by the framework when the property page becomes inactive
// it overrides the default implementation CPropertyPage::OnKillActive()
BOOL CPidc::OnKillActive() 
{
	// update the variables associated with the dialog box
	UpdateData(TRUE);
	// convert to binary values
	ConvertFloatToBinary();
	// deactivate the page
	return CPropertyPage::OnKillActive();
}


// Handle messages from check boxes
// set the correct erase station
void CPidc::OnCheckS1Erase() {UpdateData(TRUE);m_s2 = FALSE;m_s3 = FALSE;m_s4 = FALSE;m_s5 = FALSE;m_s6 = FALSE;UpdateData(FALSE);}
void CPidc::OnCheckS2Erase() {UpdateData(TRUE);m_s1 = FALSE;m_s3 = FALSE;m_s4 = FALSE;m_s5 = FALSE;m_s6 = FALSE;UpdateData(FALSE);}
void CPidc::OnCheckS3Erase() {UpdateData(TRUE);m_s2 = FALSE;m_s1 = FALSE;m_s4 = FALSE;m_s5 = FALSE;m_s6 = FALSE;UpdateData(FALSE);}
void CPidc::OnCheckS4Erase() {UpdateData(TRUE);m_s2 = FALSE;m_s3 = FALSE;m_s1 = FALSE;m_s5 = FALSE;m_s6 = FALSE;UpdateData(FALSE);}
void CPidc::OnCheckS5Erase() {UpdateData(TRUE);m_s2 = FALSE;m_s3 = FALSE;m_s4 = FALSE;m_s1 = FALSE;m_s6 = FALSE;UpdateData(FALSE);}
void CPidc::OnCheckS6Erase() {UpdateData(TRUE);m_s2 = FALSE;m_s3 = FALSE;m_s4 = FALSE;m_s5 = FALSE;m_s1 = FALSE;UpdateData(FALSE);}


// this function saves the pidc test information to a file
void CPidc::Save(CString savefilename)
{
	FILE* outstream; // pointer to open file
	int i; // index variables
	float dummyfloat = 0.0;

	// if filename doesn't end with the extension .seq add the extension
	if (savefilename.Right(3) != "seq")
		savefilename += ".seq";

	// check if file is null and open file
	if ((outstream = fopen (savefilename, "w")) != NULL){
		// print the number of sequences to file
		fprintf(outstream,"1");

		// print the sequence to file
		for ( i = 0; i<12; i++)
		{
			// print the cycles for that sample
			fprintf(outstream,"\n%d ", m_cycles);
			// print the values of erase, expose, grid and pin for each station for that sample
			if (m_s1)
				fprintf(outstream,"%f %f %f %f ", m_erase, m_expose, m_grid, m_pin);
			else 
				fprintf(outstream,"%f %f %f %f ", dummyfloat, m_expose, m_grid, m_pin);
			if (m_s2)
				fprintf(outstream,"%f %f %f %f ", m_erase, dummyfloat, dummyfloat, dummyfloat);
			else 
				fprintf(outstream,"%f %f %f %f ", dummyfloat, dummyfloat, dummyfloat, dummyfloat);
			if (m_s3)
				fprintf(outstream,"%f %f %f %f ", m_erase, dummyfloat, dummyfloat, dummyfloat);
			else 
				fprintf(outstream,"%f %f %f %f ", dummyfloat, dummyfloat, dummyfloat, dummyfloat);
			if (m_s4)
				fprintf(outstream,"%f %f %f %f ", m_erase, dummyfloat, dummyfloat, dummyfloat);
			else 
				fprintf(outstream,"%f %f %f %f ", dummyfloat, dummyfloat, dummyfloat, dummyfloat);
			if (m_s5)
				fprintf(outstream,"%f %f %f %f ", m_erase, dummyfloat, dummyfloat, dummyfloat);
			else 
				fprintf(outstream,"%f %f %f %f ", dummyfloat, dummyfloat, dummyfloat, dummyfloat);
			if (m_s6)
				fprintf(outstream,"%f %f %f %f ", m_erase, dummyfloat, dummyfloat, dummyfloat);
			else 
				fprintf(outstream,"%f %f %f %f ", dummyfloat, dummyfloat, dummyfloat, dummyfloat);
		}
		// close file
		fclose(outstream);
	}
	else
		MessageBox("PIDC Test file not saved.");

}

// this function loads the pidc test information from a file
void CPidc::Load(CString loadfilename)
{
	FILE* filehandle;	// Pointer to open file
	int i, dummyvalue;	// index variables
	float dummyfloat, possible_erase_value;
	
	
	// Open the file for reading - check to ensure it is not null file
	if ((filehandle = fopen(loadfilename, "r" )) != NULL){
		// read in number of sequences - this is used to determine how many sequences
		// need to be read since this is a vary amount and not a fixed amount
		fscanf(filehandle,"%d ", &dummyvalue);
		// each sample
		for ( i = 0; i<12; i++){
			// read in number of cycles
			fscanf(filehandle,"%d ", &m_cycles);
			// read in the rest of the values
			fscanf(filehandle,"%f %f %f %f ", &possible_erase_value, &m_expose, &m_grid, &m_pin);
			if (possible_erase_value){	
				m_erase = possible_erase_value;	
				m_s1 = TRUE; m_s2 = FALSE; m_s3 = FALSE; m_s4 = FALSE; m_s5 = FALSE; m_s6 = FALSE;
			}
			fscanf(filehandle,"%f %f %f %f ", &possible_erase_value, &dummyfloat, &dummyfloat, &dummyfloat);
			if (possible_erase_value){	
				m_erase = possible_erase_value;	
				m_s1 = FALSE; m_s2 = TRUE; m_s3 = FALSE; m_s4 = FALSE; m_s5 = FALSE; m_s6 = FALSE;
			}
			fscanf(filehandle,"%f %f %f %f ", &possible_erase_value, &dummyfloat, &dummyfloat, &dummyfloat);
			if (possible_erase_value){	
				m_erase = possible_erase_value;	
				m_s1 = FALSE; m_s2 = FALSE; m_s3 = TRUE; m_s4 = FALSE; m_s5 = FALSE; m_s6 = FALSE;
			}
			fscanf(filehandle,"%f %f %f %f ", &possible_erase_value, &dummyfloat, &dummyfloat, &dummyfloat);
			if (possible_erase_value){	
				m_erase = possible_erase_value;	
				m_s1 = FALSE; m_s2 = FALSE; m_s3 = FALSE; m_s4 = TRUE; m_s5 = FALSE; m_s6 = FALSE;
			}
			fscanf(filehandle,"%f %f %f %f ", &possible_erase_value, &dummyfloat, &dummyfloat, &dummyfloat);
			if (possible_erase_value){	
				m_erase = possible_erase_value;	
				m_s1 = FALSE; m_s2 = FALSE; m_s3 = FALSE; m_s4 = FALSE; m_s5 = TRUE; m_s6 = FALSE;
			}
			fscanf(filehandle,"%f %f %f %f ", &possible_erase_value, &dummyfloat, &dummyfloat, &dummyfloat);
			if (possible_erase_value){	
				m_erase = possible_erase_value;	
				m_s1 = FALSE; m_s2 = FALSE; m_s3 = FALSE; m_s4 = FALSE; m_s5 = FALSE; m_s6 = TRUE;
			}
		}
		// close file
		fclose(filehandle);
	}
	else
		MessageBox("Test Sequence file not loaded.");

}

// this function is called when the user presses the Load button
void CPidc::OnLoadPidc() 
{
	CString filename;	// Name of the data file
	int i = 0, j = 0;	// index variables

	char currentDirectory[ _MAX_PATH ]; // character buffer to hold the directory path

	// Object to describe the file and path
	CFileDialog filetoopen(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "READ Test Sequence Files (*.seq)|*.seq|All Files (*.*)|*.*||");

	// get the current working directory - this ensure the program returns to the 
	// proper working directory after the user makes their selection of a directory path for the test files
	_getcwd( currentDirectory, _MAX_PATH );


	// Let the user specify the location of the file
	// Display the dialog to get the user to specify a destination file for the data
	if ( filetoopen.DoModal() == IDOK )
	{	
		// change back to the current working directory
		_chdir( currentDirectory );

		// Get the user to specify a file name for the calibration data - use the standard windows dialog
		filename = filetoopen.GetPathName();
		// load the file
		Load(filename);
	}
	// update dialog box
	UpdateData(FALSE);
	
}

// This function loads up a lookup table from a file.  It matches the given
// lookup value with a value on the table and returns the value from the 
// table. ( array size is UNIPOLAR_PRECISION )
int CPidc::ChargingDevice_LookUpAndConvert(CString lookupfile, float m_lookup)
{
	FILE* instream;  // pointer to file

	int arraySize = UNIPOLAR_PRECISION;
	float tempArray [UNIPOLAR_PRECISION] [2];		// array to store look up table values that are read in from file

	// index variable
	int i = 0;	
	
	// open file for reading, check if file is null
	if ((instream = fopen(lookupfile,"r")) != NULL){
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
			while (m_lookup > tempArray [i] [0] && i < (arraySize - 1)){i++;}

			if (m_lookup < ((tempArray [i-1] [0] + tempArray [i] [0]) / 2))
				m_lookup = tempArray [i-1] [1];
			else
				m_lookup = tempArray [i] [1];
		}

		// return matched value
		return ((int) m_lookup);
	}
	// if the file is null alert user that the function is unable to open up the file
	else{
		lookupfile = "Unable to open " + lookupfile;
		MessageBox(lookupfile);
		return 0;
	}
}

// This function loads up a lookup table from a file.  It matches the given
// lookup value with a value on the table and returns the value from the
// table. ( array size is BIPOLAR_PRECISION )
int CPidc::LightDevice_LookUpAndConvert(CString lookupfile, float m_lookup)
{
	FILE* instream;  // pointer to file

	const int arraySize = BIPOLAR_PRECISION; // array size
	float tempArray [BIPOLAR_PRECISION] [2];		// array to store look up table values that are read in from file

	// index variable
	int i = 0;
	
	// open file for reading
	if ((instream = fopen(lookupfile,"r")) != NULL){
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
			while (m_lookup > tempArray [i] [0] && i < (arraySize - 1)){i++;}

			if (m_lookup < ((tempArray [i-1] [0] + tempArray [i] [0]) / 2))
				m_lookup = tempArray [i-1] [1];
			else
				m_lookup = tempArray [i] [1];
		}

		// return matched value
		return ((int) m_lookup);
	}
	// if the file is null alert user that the function is unable to open up the file
	else{
		lookupfile = "Unable to open " + lookupfile;
		MessageBox(lookupfile);
		return 0;
	}
}

// this function converts the float values to their respective values binary form
void CPidc::ConvertFloatToBinary()
{
	if (m_s1)
		b_erase = LightDevice_LookUpAndConvert((array_filenames[0]), m_erase);
	if (m_s2)
		b_erase = LightDevice_LookUpAndConvert((array_filenames[4]),m_erase );
	if (m_s3)
		b_erase = LightDevice_LookUpAndConvert((array_filenames[8]), m_erase );
	if (m_s4)
		b_erase = LightDevice_LookUpAndConvert((array_filenames[12]), m_erase );
	if (m_s5)
		b_erase = LightDevice_LookUpAndConvert((array_filenames[16]), m_erase );
	if (m_s6)
		b_erase = LightDevice_LookUpAndConvert((array_filenames[20]), m_erase );

	b_expose =	LightDevice_LookUpAndConvert((array_filenames[1]), m_expose );
	b_grid = ChargingDevice_LookUpAndConvert((array_filenames[2]), m_grid );
	b_pin =  ChargingDevice_LookUpAndConvert((array_filenames[3]), m_pin );

}