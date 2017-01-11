// SampleInformation.cpp : implementation file
//

#include "stdafx.h"
#include "direct.h"
#include "READ Test.h"
#include "READ TestDlg.h"
#include "SampleInformation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SampleInformation property page

IMPLEMENT_DYNCREATE(SampleInformation, CPropertyPage)

SampleInformation::SampleInformation() : CPropertyPage(SampleInformation::IDD)
{
	// initialize the variables
	for (int i = 0; i<12; ++i){
		comments [i] = _T("*");
		sampleID [i] = _T("*");
		startHole [i] = 0;
		endHole [i] = 0;
	}
	//{{AFX_DATA_INIT(SampleInformation)
	m_sampleNumber = 1;
	m_sampleID = _T("*");
	m_startHole = 0;
	m_endHole = 0;
	m_comments = _T("*");
	//}}AFX_DATA_INIT
}

SampleInformation::~SampleInformation()
{
}

void SampleInformation::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SampleInformation)
	DDX_Text(pDX, IDC_SAMPLENUMBER, m_sampleNumber);
	DDX_Text(pDX, IDC_SAMPLEID, m_sampleID);
	DDX_Text(pDX, IDC_STARTHOLE, m_startHole);
	DDX_Text(pDX, IDC_ENDHOLE, m_endHole);
	DDX_Text(pDX, IDC_COMMENTS, m_comments);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SampleInformation, CPropertyPage)
	//{{AFX_MSG_MAP(SampleInformation)
	ON_BN_CLICKED(IDC_FORWARD, OnForward)
	ON_BN_CLICKED(IDC_BACKWARD, OnBack)
	ON_BN_CLICKED(IDC_LOAD, OnLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SampleInformation message handlers

// this function is called by the framework when the property page becomes active
// it overrides the default implementation CPropertyPage::OnSetActive() by adding some extra functionality
//DEL BOOL SampleInformation::OnSetActive() 
//DEL {
//DEL 	CREADTestApp* pApp = (CREADTestApp*) AfxGetApp(); // pointer to main CWinApp object
//DEL 	CREADTestDlg* dlg = (CREADTestDlg*) pApp->m_pMainWnd; // pointer to main window
//DEL 	// set the wizard buttons NEXT and BACK active for this page
//DEL 	dlg->m_pBuildTestProperties.SetWizardButtons(PSWIZB_NEXT | PSWIZB_BACK);	
//DEL 	// set the page to be active
//DEL 	return CPropertyPage::OnSetActive();
//DEL }

// this function is called by the framework when the property page becomes inactive
// it overrides the default implementation CPropertyPage::OnKillActive()
//DEL BOOL SampleInformation::OnKillActive() 
//DEL {
//DEL 	// record current set of data 	
//DEL 	OnRecord();		
//DEL 	// deactivate the page
//DEL 	return CPropertyPage::OnKillActive();
//DEL }



// Forward function.  The function is called when the forward button is 
// pressed.  The dialog box goes to the next sample number and information.
void SampleInformation::OnForward() 
{
	if (m_sampleNumber	< 12){	// ensure sample number doesn't exceed the limit

		OnRecord();			// record current set of data

		m_sampleNumber++;	// advance sample number

		OnUpdate();			// update variables associated with dialog box

	}
	
	else	// message to user that they are trying to exceed limit
	
		MessageBox("You are attempting to bypass the limit!");
}


// Backward function.  The function is called when the back button is 
// pressed.  The dialog box goes to the previous sample number and 
// information.
void SampleInformation::OnBack() 
{
	if (m_sampleNumber	> 1){	// ensure sample number doesn't exceed the limit

		OnRecord();			// record current set of data
		
		m_sampleNumber--;	// advance sample number
		
		OnUpdate();			// update variables associated with dialog box

	}
	
	else	// message to user that they are trying to exceed limit
	
		MessageBox("You are attempting to bypass the limit!");
}


// Record function.  This function records the current sample information
// into an array that is later stored in a file.
void SampleInformation::OnRecord() 
{
	UpdateData(TRUE);	// update variables with values from dialog box

	RecordValues();
}


// Load function.  This function loads the sample information from a file
// that the user selects to be loaded.  This function is called when the 
// load button is pressed.
void SampleInformation::OnLoad() 
{
	int temp = 0;		// dummy integer value
	CString Filepath;	// contains pathname for the file to loaded
	CString instr;		// String being read from the file
	char currentDirectory[ _MAX_PATH ]; // character buffer to hold the directory path

	/* dialog box for opening the file */
	CFileDialog m_IdFile(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Test Samples Info (.tsi)|*.tsi|All Files (*.*)|*.*||");	

	// get the current working directory - this ensure the program returns to the 
	// proper working directory after the user makes their selection of a directory path for the test files
	_getcwd( currentDirectory, _MAX_PATH );


	if (m_IdFile.DoModal() == IDOK)		// ensure response from dialog is IDOK
	{
		// change back to the current working directory
		_chdir( currentDirectory );

		// get the path name of the file and load it
		Filepath = m_IdFile.GetPathName();
		Load(Filepath);

		OnUpdate();			// update variables associated with dialog box

	}


}


// Update function.  This function updates the dialog box with information
// from the various information arrays.
void SampleInformation::OnUpdate()
{
	/* update comments variable with value from string array */	
	m_comments = comments [m_sampleNumber-1];	

	m_comments.TrimLeft();	// delete all white spaces on the left of the string

	m_comments.TrimRight();	// delete all white spaces on the right of the string

	/* update samplesID variable with value from int array */	
	m_sampleID = sampleID [m_sampleNumber-1];
	
	/* update startHole variable with value from int array */	
	m_startHole = startHole [m_sampleNumber-1];
	
	/* update endHole variable with value from int array */	
	m_endHole = endHole [m_sampleNumber-1];

	UpdateData(FALSE);	// update dialog box
}

// this function saves the samples information to a file
void SampleInformation::Save(CString savefilename)
{
	FILE* outstream;  // pointer to open file
	int i; // index variable

	// if the filename doesn't end with the extension ".tsi" add the extension to the filename
	if (savefilename.Right(3) != "tsi")
		savefilename += ".tsi";

	// open the file and ensure it is not null
	if ((outstream = fopen (savefilename, "w")) != NULL){
		// each sample
		for ( i = 0; i<12; i++)
		{
			// write the sample comments and sample ID
			fprintf(outstream,"%s\n%s\n", comments[i], sampleID[i]);
			// write the sample start hole and end hole
			fprintf(outstream,"%d\t%d\n", startHole[i], endHole[i]);
		}
		// close the file
		fclose(outstream);
	}
	// if file is null alert user that file was not saved
	else
		MessageBox("Sample Information file not saved.");
}

// this function loads the sample information from a file
void SampleInformation::Load(CString loadfilename)
{
	char buffer[300] = {" "};	// temporary character buffer
	FILE* gstream; // pointer to open file

	// open file for reading in values
	if ((gstream = fopen( loadfilename, "r" )) != NULL){

		// each sample
		for (int i=0; i<12; i++)
		{
			// Read the first line - comment
			fgets(buffer, 300, gstream);
			// Place the info into the array of comments
			comments[i] = buffer;
			// Cut the new line character off the end of the string
			comments[i].TrimRight();

			// Read the second line - samp id
			fgets(buffer, 300, gstream);
			// Place the info into the array of sample IDs
			sampleID[i] = buffer;
			// Cut the new line character off the end of the string
			sampleID[i].TrimRight();

			// Read the start and end holes from the third line of sample information
			fscanf(gstream, "%d%d", &startHole[i], &endHole[i]);
			
			// Read a dummy stream - in order to get to the next line for the next sample
			fgets(buffer, 300, gstream);

		}
		fclose(gstream);	// close file

	}
	else
		MessageBox ("Sample Information file not loaded.");

}

void SampleInformation::RecordValues()
{

	m_comments.TrimLeft();	// delete all white spaces on the left of the string

	m_comments.TrimRight();	// delete all white spaces on the right of the string

	if (!m_comments.IsEmpty())	// ensure string is not empty
		/* update comments string array with current value */
		comments [m_sampleNumber-1] = m_comments;	
	else
		/* update comments string array with default value */
		comments [m_sampleNumber-1] = "*****";	

	sampleID [m_sampleNumber-1] = m_sampleID;	// update sampleID int array with current value

	startHole [m_sampleNumber-1] = m_startHole;	// update startHole int array with current value

	endHole [m_sampleNumber-1] = m_endHole;		// update endHole int array with current value

}
