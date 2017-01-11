// TestSequence.cpp : implementation file
//

#include "stdafx.h"
#include "direct.h"
#include "READ Test.h"
#include "READ TestDlg.h"
#include "TestSequence.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TestSequence property page

IMPLEMENT_DYNCREATE(TestSequence, CPropertyPage)

TestSequence::TestSequence() : CPropertyPage(TestSequence::IDD)
{

	FILE* istream;
	char buffer[70];
	int i = 0, j = 0;

	chrgDevIncr = NULL;
	list1on = FALSE;
	list2on = FALSE;
	list3on = FALSE;
	list4on = FALSE;
	list5on = FALSE;
	list6on = FALSE;

	if ((istream = fopen("gridlookuptables.txt", "r")) != NULL){
		for (i = 0; i < NUMBEROFSAMPLES; i++)
			for (j = 0; j < NUMBEROFGRIDS; j++){
				fgets(buffer, 200 ,istream);
				gridfilenames[i][j] = buffer;
				gridfilenames[i][j].TrimRight();
				gridfilenames[i][j].TrimLeft();
				
			}
		fclose(istream);
	}
	else
		MessageBox("Unable to open gridlookuptables.txt.");


	copyGrid.AddCycles(0);
	for (i = 0; i < 6; i++){
		copyGrid.AddErase(i, 0);
		copyGrid.AddExpose(i, 0);
		copyGrid.AddGrid(i, 0);
		copyGrid.AddPin(i, 0);
		copyGrid.AddErase2(i, 0);
		copyGrid.AddExpose2(i, 0);
		copyGrid.AddGrid2(i, 0);
		copyGrid.AddPin2(i, 0);
	}

	numberOfSequences = 0;
	currentSequence.ClearAll();
	currentSequenceBinaryForm.ClearAll();
	//{{AFX_DATA_INIT(TestSequence)
	m_cycles = 0;
	m_sectionAcycles = 0;
	m_sectionBcycles = 0;
	m_s1_erase = 0.0f;
	m_s1_expose = 0.0f;
	m_s1_grid = 0.0f;
	m_s1_pin = 0.0f;
	m_s2_erase = 0.0f;
	m_s2_expose = 0.0f;
	m_s2_grid = 0.0f;
	m_s2_pin = 0.0f;
	m_s3_erase = 0.0f;
	m_s3_expose = 0.0f;
	m_s3_grid = 0.0f;
	m_s3_pin = 0.0f;
	m_s4_erase = 0.0f;
	m_s4_expose = 0.0f;
	m_s4_grid = 0.0f;
	m_s4_pin = 0.0f;
	m_s5_erase = 0.0f;
	m_s5_expose = 0.0f;
	m_s5_grid = 0.0f;
	m_s5_pin = 0.0f;
	m_s6_erase = 0.0f;
	m_s6_expose = 0.0f;
	m_s6_grid = 0.0f;
	m_s6_pin = 0.0f;
	m_s1_erase2 = 0.0f;
	m_s1_expose2 = 0.0f;
	m_s1_grid2 = 0.0f;
	m_s1_pin2 = 0.0f;
	m_s2_erase2 = 0.0f;
	m_s2_expose2 = 0.0f;
	m_s2_grid2 = 0.0f;
	m_s2_pin2 = 0.0f;
	m_s3_erase2 = 0.0f;
	m_s3_expose2 = 0.0f;
	m_s3_grid2 = 0.0f;
	m_s3_pin2 = 0.0f;
	m_s4_erase2 = 0.0f;
	m_s4_expose2 = 0.0f;
	m_s4_grid2 = 0.0f;
	m_s4_pin2 = 0.0f;
	m_s5_erase2 = 0.0f;
	m_s5_expose2 = 0.0f;
	m_s5_grid2 = 0.0f;
	m_s5_pin2 = 0.0f;
	m_s6_erase2 = 0.0f;
	m_s6_expose2 = 0.0f;
	m_s6_grid2 = 0.0f;
	m_s6_pin2 = 0.0f;
	m_sampleNumber = 1;
	m_pidc1 = FALSE;
	m_pidc2 = FALSE;
	m_pidc3 = FALSE;
	m_pidc4 = FALSE;
	m_pidc5 = FALSE;
	m_pidc6 = FALSE;
	m_pidc_cycles = 0;
	m_popupoff = TRUE;
	//}}AFX_DATA_INIT
}

TestSequence::~TestSequence()
{
}

void TestSequence::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TestSequence)
	DDX_Control(pDX, IDC_GRID4_LIST, m_grid4_list);
	DDX_Control(pDX, IDC_GRID6_LIST, m_grid6_list);
	DDX_Control(pDX, IDC_GRID5_LIST, m_grid5_list);
	DDX_Control(pDX, IDC_GRID3_LIST, m_grid3_list);
	DDX_Control(pDX, IDC_GRID2_LIST, m_grid2_list);
	DDX_Control(pDX, IDC_GRID1_LIST, m_grid1_list);
	DDX_Control(pDX, IDC_SEQUENCELIST, m_SequenceList);
	DDX_Text(pDX, IDC_SECTIONACYCLES, m_sectionAcycles);
	DDX_Text(pDX, IDC_SECTIONBCYCLES, m_sectionBcycles);
	DDX_Text(pDX, IDC_CYCLES, m_cycles);
	DDX_Text(pDX, IDC_S1_ERASE, m_s1_erase);
	DDX_Text(pDX, IDC_S1_EXPOSE, m_s1_expose);
	DDX_Text(pDX, IDC_S1_GRID, m_s1_grid);
	DDX_Text(pDX, IDC_S1_PIN, m_s1_pin);
	DDX_Text(pDX, IDC_S2_ERASE, m_s2_erase);
	DDX_Text(pDX, IDC_S2_EXPOSE, m_s2_expose);
	DDX_Text(pDX, IDC_S2_GRID, m_s2_grid);
	DDX_Text(pDX, IDC_S2_PIN, m_s2_pin);
	DDX_Text(pDX, IDC_S3_ERASE, m_s3_erase);
	DDX_Text(pDX, IDC_S3_EXPOSE, m_s3_expose);
	DDX_Text(pDX, IDC_S3_GRID, m_s3_grid);
	DDX_Text(pDX, IDC_S3_PIN, m_s3_pin);
	DDX_Text(pDX, IDC_S4_ERASE, m_s4_erase);
	DDX_Text(pDX, IDC_S4_EXPOSE, m_s4_expose);
	DDX_Text(pDX, IDC_S4_GRID, m_s4_grid);
	DDX_Text(pDX, IDC_S4_PIN, m_s4_pin);
	DDX_Text(pDX, IDC_S5_ERASE, m_s5_erase);
	DDX_Text(pDX, IDC_S5_EXPOSE, m_s5_expose);
	DDX_Text(pDX, IDC_S5_GRID, m_s5_grid);
	DDX_Text(pDX, IDC_S5_PIN, m_s5_pin);
	DDX_Text(pDX, IDC_S6_ERASE, m_s6_erase);
	DDX_Text(pDX, IDC_S6_EXPOSE, m_s6_expose);
	DDX_Text(pDX, IDC_S6_GRID, m_s6_grid);
	DDX_Text(pDX, IDC_S6_PIN, m_s6_pin);
	DDX_Text(pDX, IDC_S1_ERASE2, m_s1_erase2);
	DDX_Text(pDX, IDC_S1_EXPOSE2, m_s1_expose2);
	DDX_Text(pDX, IDC_S1_GRID2, m_s1_grid2);
	DDX_Text(pDX, IDC_S1_PIN2, m_s1_pin2);
	DDX_Text(pDX, IDC_S2_ERASE2, m_s2_erase2);
	DDX_Text(pDX, IDC_S2_EXPOSE2, m_s2_expose2);
	DDX_Text(pDX, IDC_S2_GRID2, m_s2_grid2);
	DDX_Text(pDX, IDC_S2_PIN2, m_s2_pin2);
	DDX_Text(pDX, IDC_S3_ERASE2, m_s3_erase2);
	DDX_Text(pDX, IDC_S3_EXPOSE2, m_s3_expose2);
	DDX_Text(pDX, IDC_S3_GRID2, m_s3_grid2);
	DDX_Text(pDX, IDC_S3_PIN2, m_s3_pin2);
	DDX_Text(pDX, IDC_S4_ERASE2, m_s4_erase2);
	DDX_Text(pDX, IDC_S4_EXPOSE2, m_s4_expose2);
	DDX_Text(pDX, IDC_S4_GRID2, m_s4_grid2);
	DDX_Text(pDX, IDC_S4_PIN2, m_s4_pin2);
	DDX_Text(pDX, IDC_S5_ERASE2, m_s5_erase2);
	DDX_Text(pDX, IDC_S5_EXPOSE2, m_s5_expose2);
	DDX_Text(pDX, IDC_S5_GRID2, m_s5_grid2);
	DDX_Text(pDX, IDC_S5_PIN2, m_s5_pin2);
	DDX_Text(pDX, IDC_S6_ERASE2, m_s6_erase2);
	DDX_Text(pDX, IDC_S6_EXPOSE2, m_s6_expose2);
	DDX_Text(pDX, IDC_S6_GRID2, m_s6_grid2);
	DDX_Text(pDX, IDC_S6_PIN2, m_s6_pin2);
	DDX_Text(pDX, IDC_SAMPLE, m_sampleNumber);
	DDX_Check(pDX, IDC_PIDC_CHECK1, m_pidc1);
	DDX_Check(pDX, IDC_PIDC_CHECK2, m_pidc2);
	DDX_Check(pDX, IDC_PIDC_CHECK3, m_pidc3);
	DDX_Check(pDX, IDC_PIDC_CHECK4, m_pidc4);
	DDX_Check(pDX, IDC_PIDC_CHECK5, m_pidc5);
	DDX_Check(pDX, IDC_PIDC_CHECK6, m_pidc6);
	DDX_Text(pDX, IDC_CYCLES_PIDC, m_pidc_cycles);
	DDX_Check(pDX, IDC_POPUPCHECK, m_popupoff);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TestSequence, CPropertyPage)
	//{{AFX_MSG_MAP(TestSequence)
	ON_BN_CLICKED(IDC_TESTSEQUENCEBACKWARD, OnBack)
	ON_BN_CLICKED(IDC_TESTSEQUENCEFORWARD, OnForward)
	ON_BN_CLICKED(IDC_TESTSEQUENCELOAD, OnLoad)
	ON_BN_CLICKED(IDC_ADDSEQUENCE, OnAddsequence)
	ON_BN_CLICKED(IDC_REMOVESEQUENCE, OnRemovesequence)
	ON_LBN_DBLCLK(IDC_SEQUENCELIST, OnDblclkSequencelist)
	ON_BN_CLICKED(IDC_MODIFYSEQUENCE, OnModifysequence)
	ON_BN_CLICKED(IDC_RESETCURRENTSEQUENCE, OnResetcurrentsequence)
	ON_BN_CLICKED(IDC_COPYVALUES, OnCopyvalues)
	ON_BN_CLICKED(IDC_PASTEVALUES, OnPastevalues)
	ON_BN_CLICKED(IDC_PIDC_CHECK1, OnPidcCheck1)
	ON_BN_CLICKED(IDC_PIDC_CHECK2, OnPidcCheck2)
	ON_BN_CLICKED(IDC_PIDC_CHECK3, OnPidcCheck3)
	ON_BN_CLICKED(IDC_PIDC_CHECK4, OnPidcCheck4)
	ON_BN_CLICKED(IDC_PIDC_CHECK5, OnPidcCheck5)
	ON_BN_CLICKED(IDC_PIDC_CHECK6, OnPidcCheck6)
	ON_BN_CLICKED(IDC_REPEATSEQUENCE, OnRepeatsequence)
	ON_BN_CLICKED(IDC_SETINCREMENTS, OnSetincrements)
	ON_EN_SETFOCUS(IDC_S1_GRID, OnSetfocusS1Grid)
	ON_EN_KILLFOCUS(IDC_S1_GRID, OnKillfocusS1Grid)
	ON_EN_SETFOCUS(IDC_S2_GRID, OnSetfocusS2Grid)
	ON_EN_KILLFOCUS(IDC_S2_GRID, OnKillfocusS2Grid)
	ON_EN_SETFOCUS(IDC_S3_GRID, OnSetfocusS3Grid)
	ON_EN_KILLFOCUS(IDC_S3_GRID, OnKillfocusS3Grid)
	ON_EN_SETFOCUS(IDC_S4_GRID, OnSetfocusS4Grid)
	ON_EN_KILLFOCUS(IDC_S4_GRID, OnKillfocusS4Grid)
	ON_EN_SETFOCUS(IDC_S5_GRID, OnSetfocusS5Grid)
	ON_EN_KILLFOCUS(IDC_S5_GRID, OnKillfocusS5Grid)
	ON_EN_SETFOCUS(IDC_S6_GRID, OnSetfocusS6Grid)
	ON_EN_KILLFOCUS(IDC_S6_GRID, OnKillfocusS6Grid)
	ON_BN_CLICKED(IDC_POPUPCHECK, OnPopupcheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TestSequence message handlers

// this function is called by the framework when the property page becomes active
// it overrides the default implementation CPropertyPage::OnSetActive() by adding some extra functionality
BOOL TestSequence::OnSetActive() 
{
	CREADTestApp* pApp = (CREADTestApp*) AfxGetApp(); // pointer to main CWinApp object
	CREADTestDlg* dlg = (CREADTestDlg*) pApp->m_pMainWnd; // pointer to main window
	// set the wizard buttons NEXT and BACK active for this page
	dlg->m_pBuildTestProperties.SetWizardButtons(PSWIZB_NEXT | PSWIZB_BACK);	

	chrgDevIncr = dlg->chrgDevIncr;

	readgridvalues();
	// update dialog box 
	Update();
	
	// set the page to be active
	return CPropertyPage::OnSetActive();
}

// this function is called by the framework when the property page becomes inactive
// it overrides the default implementation CPropertyPage::OnKillActive()
BOOL TestSequence::OnKillActive() 
{
	// record the values from the dialog box for the current station
	Record();
	chrgDevIncr = NULL;
	// deactivate the page
	return CPropertyPage::OnKillActive();

}

// this function is called when the user presses the back button
void TestSequence::OnBack() 
{
	// if not the lowest sample number
	if (m_sampleNumber > 1){
		// record current values
		Record();
		// decrement sample number
		--m_sampleNumber;

		readgridvalues();
		// update dialog box with new values for the new sample
		Update();
	}
	else
		MessageBox("You are attempting to bypass the limit!");

	
}

// this function is called when the user presses the forward button
void TestSequence::OnForward() 
{
	// if not the highest sample number
	if (m_sampleNumber < 12){
		// record current values
		Record();
		// increment sample number
		++m_sampleNumber;

		readgridvalues();
		// update dialog box with new values for the new sample
		Update();
	}
	else
		MessageBox("You are attempting to bypass the limit!");

	
}

// this function is called when the user presses the Load button
void TestSequence::OnLoad() 
{
	CString filename;			// Name of the data file
	int i = 0, j = 0;	// index variables
	HCURSOR lhCursor;

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
		// place wait cursor
		lhCursor = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
		SetCursor(lhCursor);

		// change back to the current working directory
		_chdir( currentDirectory );

		// Get the user to specify a file name for the calibration data - use the standard windows dialog
		filename = filetoopen.GetPathName();
		// load the file
		Load(filename);

		// place normal cursor
		lhCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		SetCursor(lhCursor);
	}

	// change back to the current working directory
	_chdir( currentDirectory );

	// update dialog box
	Update();
}

// this function records the current sequence information to the currentSequence data structure
void TestSequence::Record()
{
	// save and validate data from the dialog box to associated variables
	UpdateData(TRUE); 
	// record the respective information to the respective parts of the currentSequence data structure for the current sample
	currentSequence.pidc[0] = m_pidc1;
	currentSequence.pidc[1] = m_pidc2;
	currentSequence.pidc[2] = m_pidc3;
	currentSequence.pidc[3] = m_pidc4;
	currentSequence.pidc[4] = m_pidc5;
	currentSequence.pidc[5] = m_pidc6;
	currentSequence.pidc_cycles = m_pidc_cycles;

	if (m_pidc1 || m_pidc2 || m_pidc3 || m_pidc4 || m_pidc5 || m_pidc6){
		if (m_pidc_cycles >= 0)
		currentSequence.sample[m_sampleNumber-1].AddCycles(m_pidc_cycles);
	}
	else {
		if (m_cycles >= 0)
		currentSequence.sample[m_sampleNumber-1].AddCycles(m_cycles);
	}


	currentSequence.sample[m_sampleNumber-1].AddErase(0, m_s1_erase);
	currentSequence.sample[m_sampleNumber-1].AddExpose(0, m_s1_expose);
	currentSequence.sample[m_sampleNumber-1].AddGrid(0, m_s1_grid);
	currentSequence.sample[m_sampleNumber-1].AddPin(0, m_s1_pin);
	currentSequence.sample[m_sampleNumber-1].AddErase(1, m_s2_erase);
	currentSequence.sample[m_sampleNumber-1].AddExpose(1, m_s2_expose);
	currentSequence.sample[m_sampleNumber-1].AddGrid(1, m_s2_grid);
	currentSequence.sample[m_sampleNumber-1].AddPin(1, m_s2_pin);
	currentSequence.sample[m_sampleNumber-1].AddErase(2, m_s3_erase);
	currentSequence.sample[m_sampleNumber-1].AddExpose(2, m_s3_expose);
	currentSequence.sample[m_sampleNumber-1].AddGrid(2, m_s3_grid);
	currentSequence.sample[m_sampleNumber-1].AddPin(2, m_s3_pin);
	currentSequence.sample[m_sampleNumber-1].AddErase(3, m_s4_erase);
	currentSequence.sample[m_sampleNumber-1].AddExpose(3, m_s4_expose);
	currentSequence.sample[m_sampleNumber-1].AddGrid(3, m_s4_grid);
	currentSequence.sample[m_sampleNumber-1].AddPin(3, m_s4_pin);
	currentSequence.sample[m_sampleNumber-1].AddErase(4, m_s5_erase);
	currentSequence.sample[m_sampleNumber-1].AddExpose(4, m_s5_expose);
	currentSequence.sample[m_sampleNumber-1].AddGrid(4, m_s5_grid);
	currentSequence.sample[m_sampleNumber-1].AddPin(4, m_s5_pin);
	currentSequence.sample[m_sampleNumber-1].AddErase(5, m_s6_erase);
	currentSequence.sample[m_sampleNumber-1].AddExpose(5, m_s6_expose);
	currentSequence.sample[m_sampleNumber-1].AddGrid(5, m_s6_grid);
	currentSequence.sample[m_sampleNumber-1].AddPin(5, m_s6_pin);


	currentSequence.sample[m_sampleNumber-1].AddErase2(0, m_s1_erase2);
	currentSequence.sample[m_sampleNumber-1].AddExpose2(0, m_s1_expose2);
	currentSequence.sample[m_sampleNumber-1].AddGrid2(0, m_s1_grid2);
	currentSequence.sample[m_sampleNumber-1].AddPin2(0, m_s1_pin2);
	currentSequence.sample[m_sampleNumber-1].AddErase2(1, m_s2_erase2);
	currentSequence.sample[m_sampleNumber-1].AddExpose2(1, m_s2_expose2);
	currentSequence.sample[m_sampleNumber-1].AddGrid2(1, m_s2_grid2);
	currentSequence.sample[m_sampleNumber-1].AddPin2(1, m_s2_pin2);
	currentSequence.sample[m_sampleNumber-1].AddErase2(2, m_s3_erase2);
	currentSequence.sample[m_sampleNumber-1].AddExpose2(2, m_s3_expose2);
	currentSequence.sample[m_sampleNumber-1].AddGrid2(2, m_s3_grid2);
	currentSequence.sample[m_sampleNumber-1].AddPin2(2, m_s3_pin2);
	currentSequence.sample[m_sampleNumber-1].AddErase2(3, m_s4_erase2);
	currentSequence.sample[m_sampleNumber-1].AddExpose2(3, m_s4_expose2);
	currentSequence.sample[m_sampleNumber-1].AddGrid2(3, m_s4_grid2);
	currentSequence.sample[m_sampleNumber-1].AddPin2(3, m_s4_pin2);
	currentSequence.sample[m_sampleNumber-1].AddErase2(4, m_s5_erase2);
	currentSequence.sample[m_sampleNumber-1].AddExpose2(4, m_s5_expose2);
	currentSequence.sample[m_sampleNumber-1].AddGrid2(4, m_s5_grid2);
	currentSequence.sample[m_sampleNumber-1].AddPin2(4, m_s5_pin2);
	currentSequence.sample[m_sampleNumber-1].AddErase2(5, m_s6_erase2);
	currentSequence.sample[m_sampleNumber-1].AddExpose2(5, m_s6_expose2);
	currentSequence.sample[m_sampleNumber-1].AddGrid2(5, m_s6_grid2);
	currentSequence.sample[m_sampleNumber-1].AddPin2(5, m_s6_pin2);

	currentSequence.sectionAcycles = m_sectionAcycles;
	currentSequence.sectionBcycles = m_sectionBcycles;

}

// this function loads the currents sequences information from the currentSequence data structure
void TestSequence::Update()
{
	// read the respective information form the respective parts of the currentSequence data structure for the current sample
	m_pidc1 = currentSequence.pidc[0];
	m_pidc2 = currentSequence.pidc[1];
	m_pidc3 = currentSequence.pidc[2];
	m_pidc4 = currentSequence.pidc[3];
	m_pidc5 = currentSequence.pidc[4];
	m_pidc6 = currentSequence.pidc[5];
	m_pidc_cycles = currentSequence.pidc_cycles;	

	if (m_pidc1 || m_pidc2 || m_pidc3 || m_pidc4 || m_pidc5 || m_pidc6){
		if (m_pidc_cycles >= 0)
			m_cycles = m_pidc_cycles;
	}
	else {
		if (currentSequence.sample[m_sampleNumber-1].GetCycles() >= 0)
		m_cycles = currentSequence.sample[m_sampleNumber-1].GetCycles();
	}


	

	m_s1_erase = currentSequence.sample[m_sampleNumber-1].GetErase(0);
	m_s1_expose = currentSequence.sample[m_sampleNumber-1].GetExpose(0);
	m_s1_grid = currentSequence.sample[m_sampleNumber-1].GetGrid(0);
	m_s1_pin = currentSequence.sample[m_sampleNumber-1].GetPin(0);
	m_s2_erase = currentSequence.sample[m_sampleNumber-1].GetErase(1);
	m_s2_expose = currentSequence.sample[m_sampleNumber-1].GetExpose(1);
	m_s2_grid = currentSequence.sample[m_sampleNumber-1].GetGrid(1);
	m_s2_pin = currentSequence.sample[m_sampleNumber-1].GetPin(1);
	m_s3_erase = currentSequence.sample[m_sampleNumber-1].GetErase(2);
	m_s3_expose = currentSequence.sample[m_sampleNumber-1].GetExpose(2);
	m_s3_grid = currentSequence.sample[m_sampleNumber-1].GetGrid(2);
	m_s3_pin = currentSequence.sample[m_sampleNumber-1].GetPin(2);
	m_s4_erase = currentSequence.sample[m_sampleNumber-1].GetErase(3);
	m_s4_expose = currentSequence.sample[m_sampleNumber-1].GetExpose(3);
	m_s4_grid = currentSequence.sample[m_sampleNumber-1].GetGrid(3);
	m_s4_pin = currentSequence.sample[m_sampleNumber-1].GetPin(3);
	m_s5_erase = currentSequence.sample[m_sampleNumber-1].GetErase(4);
	m_s5_expose = currentSequence.sample[m_sampleNumber-1].GetExpose(4);
	m_s5_grid = currentSequence.sample[m_sampleNumber-1].GetGrid(4);
	m_s5_pin = currentSequence.sample[m_sampleNumber-1].GetPin(4);
	m_s6_erase = currentSequence.sample[m_sampleNumber-1].GetErase(5);
	m_s6_expose = currentSequence.sample[m_sampleNumber-1].GetExpose(5);
	m_s6_grid = currentSequence.sample[m_sampleNumber-1].GetGrid(5);
	m_s6_pin = currentSequence.sample[m_sampleNumber-1].GetPin(5);

	m_s1_erase2 = currentSequence.sample[m_sampleNumber-1].GetErase2(0);
	m_s1_expose2 = currentSequence.sample[m_sampleNumber-1].GetExpose2(0);
	m_s1_grid2 = currentSequence.sample[m_sampleNumber-1].GetGrid2(0);
	m_s1_pin2 = currentSequence.sample[m_sampleNumber-1].GetPin2(0);
	m_s2_erase2 = currentSequence.sample[m_sampleNumber-1].GetErase2(1);
	m_s2_expose2 = currentSequence.sample[m_sampleNumber-1].GetExpose2(1);
	m_s2_grid2 = currentSequence.sample[m_sampleNumber-1].GetGrid2(1);
	m_s2_pin2 = currentSequence.sample[m_sampleNumber-1].GetPin2(1);
	m_s3_erase2 = currentSequence.sample[m_sampleNumber-1].GetErase2(2);
	m_s3_expose2 = currentSequence.sample[m_sampleNumber-1].GetExpose2(2);
	m_s3_grid2 = currentSequence.sample[m_sampleNumber-1].GetGrid2(2);
	m_s3_pin2 = currentSequence.sample[m_sampleNumber-1].GetPin2(2);
	m_s4_erase2 = currentSequence.sample[m_sampleNumber-1].GetErase2(3);
	m_s4_expose2 = currentSequence.sample[m_sampleNumber-1].GetExpose2(3);
	m_s4_grid2 = currentSequence.sample[m_sampleNumber-1].GetGrid2(3);
	m_s4_pin2 = currentSequence.sample[m_sampleNumber-1].GetPin2(3);
	m_s5_erase2 = currentSequence.sample[m_sampleNumber-1].GetErase2(4);
	m_s5_expose2 = currentSequence.sample[m_sampleNumber-1].GetExpose2(4);
	m_s5_grid2 = currentSequence.sample[m_sampleNumber-1].GetGrid2(4);
	m_s5_pin2 = currentSequence.sample[m_sampleNumber-1].GetPin2(4);
	m_s6_erase2 = currentSequence.sample[m_sampleNumber-1].GetErase2(5);
	m_s6_expose2 = currentSequence.sample[m_sampleNumber-1].GetExpose2(5);
	m_s6_grid2 = currentSequence.sample[m_sampleNumber-1].GetGrid2(5);
	m_s6_pin2 = currentSequence.sample[m_sampleNumber-1].GetPin2(5);

	m_sectionAcycles = currentSequence.sectionAcycles;
	m_sectionBcycles = currentSequence.sectionBcycles;


	// call all pidc check functions to update dialog;
	CallAllIncrementCheck();
	CallAllPidcCheck();
	

	// update dialog box
	UpdateData(FALSE);


}

// this function saves the test sequence information to a file
void TestSequence::Save(CString savefilename)
{
	FILE* outstream; // pointer to open file
	int i, j, k; // index variables
	POSITION p; // position variable, used to access the linked list
	SequenceFloat temp; // temporary sequence float structure 

	float* highest_expose_values;
	highest_expose_values = getHighestExposeValue();

	// if filename doesn't end with the extension .seq add the extension
	if (savefilename.Right(3) != "seq")
		savefilename += ".seq";

	// check if file is null and open file
	if ((outstream = fopen (savefilename, "w")) != NULL){
		// print the number of sequences to file
		fprintf(outstream,"%d", numberOfSequences);
		// get head position
		p = sequenceFloatList.GetHeadPosition();
		// while number of Sequence is not zero
		while(numberOfSequences){
			// get current sequenceFloat from list and increment p
			temp = sequenceFloatList.GetNext(p);
			// print the sequence to file
			for ( i = 0; i<12; i++)
			{
				// print the cycles for that sample
				fprintf(outstream,"\n%d ", temp.sample[i].GetCycles());
				// print the values of erase, expose, grid and pin for each station for that sample
				for (j = 0; j<6; j++){
					fprintf(outstream,"%f %f %f %f ", temp.sample[i].GetErase(j), temp.sample[i].GetExpose(j), temp.sample[i].GetGrid(j), temp.sample[i].GetPin(j));
				}
				for (j = 0; j<6; j++){
					fprintf(outstream,"%f %f %f %f ", temp.sample[i].GetErase2(j), temp.sample[i].GetExpose2(j), temp.sample[i].GetGrid2(j), temp.sample[i].GetPin2(j));
				}

			}
			fprintf(outstream,"\n");
			fprintf(outstream,"%d %d\n",temp.sectionAcycles, temp.sectionBcycles);
			// print Pidc settings
			fprintf(outstream,"\n");
			for (k = 0; k < 6; k++){
				if (temp.pidc[k])
					fprintf(outstream,"1 ");
				else 
					fprintf(outstream,"0 ");
				fprintf(outstream,"%f ", highest_expose_values[k]);
			}

			fprintf(outstream,"%d ", temp.pidc_cycles);

			// decrement number of sequences
			numberOfSequences--;
		}
		// close file
		fclose(outstream);
		// empty both the float and binary lists
		sequenceFloatList.RemoveAll();
		sequenceBinaryList.RemoveAll();
	}
	else
		MessageBox("Test Sequence file not saved.");

}

// this function loads the test sequence information from a file
void TestSequence::Load(CString loadfilename)
{
	FILE* filehandle;	// Pointer to open file
	int i, j, k, l, fcycles; 	// index variables
	int pidc_integer;  // temporary holding value for pidc setting
	int localAcycles, localBcycles;
	float dummyFloatValue, ferase, fexpose, fgrid, fpin;
	
	// Open the file for reading - check to ensure it is not null file
	if ((filehandle = fopen(loadfilename, "r" )) != NULL){
		// clear the current sequence data structure
		currentSequence.ClearAll();
		// read in number of sequences - this is used to determine how many sequences
		// need to be read since this is a vary amount and not a fixed amount
		fscanf(filehandle,"%d ", &k);
		// each sequence
		while(k){
			// each sample
			for ( i = 0; i<12; i++){
				// read in number of cycles
				fscanf(filehandle,"%d ", &fcycles);
				currentSequence.sample[i].AddCycles(fcycles);
				// each station
				for (j = 0; j<6; j++){
					// read in erase value, expose value, grid value and pin value
					fscanf(filehandle,"%f %f %f %f ", &ferase, &fexpose, &fgrid, &fpin);
					currentSequence.sample[i].AddErase(j, ferase);
					currentSequence.sample[i].AddExpose(j, fexpose);
					currentSequence.sample[i].AddGrid(j, fgrid);
					currentSequence.sample[i].AddPin(j, fpin);
				}
				for (j = 0; j<6; j++){
					// read in erase value, expose value, grid value and pin value
					fscanf(filehandle,"%f %f %f %f ", &ferase, &fexpose, &fgrid, &fpin);
					currentSequence.sample[i].AddErase2(j, ferase);
					currentSequence.sample[i].AddExpose2(j, fexpose);
					currentSequence.sample[i].AddGrid2(j, fgrid);
					currentSequence.sample[i].AddPin2(j, fpin);
				}
			}

			fscanf(filehandle,"%d %d", &localAcycles, &localBcycles);
			currentSequence.sectionAcycles = localAcycles;
			currentSequence.sectionBcycles = localBcycles;

			// read in Pidc settings
			for (l = 0; l<6; l++){
				fscanf(filehandle,"%d ", &pidc_integer);
				if (pidc_integer == 1)
					currentSequence.pidc[l] = TRUE;
				else if (pidc_integer == 0)
					currentSequence.pidc[l] = FALSE;
				else
					MessageBox("The PIDC settings could be wrong.");
				fscanf(filehandle,"%f ", &dummyFloatValue);
			}
			fscanf(filehandle,"%d ", &currentSequence.pidc_cycles);

			// add sequence to linked list
			Addsequence();
			// decrement k to indicate one sequence has been added
			k--;
		}
		// close file
		fclose(filehandle);
	}
	else
		MessageBox("Test Sequence file not loaded.");


}

// This function loads up a lookup table from a file.  It matches the given
// lookup value with a value on the table and returns the value from the 
// table. ( array size is UNIPOLAR_PRECISION )
int TestSequence::ChargingDevice_LookUpAndConvert(CString lookupfile, float m_lookup)
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
int TestSequence::LightDevice_LookUpAndConvert(CString lookupfile, float m_lookup)
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

// this function is called when the add new sequence button is pressed
void TestSequence::OnAddsequence() 
{
	HCURSOR lhCursor;

	// place wait cursor
	lhCursor = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
	SetCursor(lhCursor);

	// record current sequence
	Record();
	// add sequence to linked list
	Addsequence();
	// update the dialog box
	Update();

	// place normal cursor
	lhCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	SetCursor(lhCursor);
}

// this function is called when the remove last sequence button is pressed
void TestSequence::OnRemovesequence() 
{
	int removeNumber = m_SequenceList.GetCount()-1; // remove number is the index value to be removed
																				// index value is zero based so has to be calculated accordingly
	SequenceFloat temp; // temporary sequence float data structure
	SequenceInteger tempBinary; // temporary sequence integer data structure

	// remove from list
	m_SequenceList.DeleteString(removeNumber);

	// if list is not empty - remove from linked list
	if (!sequenceFloatList.IsEmpty()){

		// decrement number of Sequences
		numberOfSequences--;

		// remove from linked list
		temp = sequenceFloatList.RemoveTail();
		tempBinary = sequenceBinaryList.RemoveTail();
	}
}

// this function is called when the remove last sequence button is pressed
void TestSequence::OnDblclkSequencelist() 
{
	POSITION p; // holds the position in the linked list
	int i, j; // index variables
	SequenceFloat temp; // temporary sequence float structure

	// get the user's selection
	i = m_SequenceList.GetCurSel();
	j = 0;

	// as long as the selection is valid
	if (i != LB_ERR){
		// get starting point of the linked list
		p = sequenceFloatList.GetHeadPosition();

		// increment through the list until you get to the position i
		while (j < i){
			temp = sequenceFloatList.GetNext(p);
			j++;
		}

		// get the item i from the list
		temp = sequenceFloatList.GetAt(p);

		// copy to current sequence and update the dialog
		currentSequence.Copy(temp);

		// reset m_sampleNumber
		m_sampleNumber = 1;
		
		// update dialog box
		Update();
	}
	else
		MessageBox("No selection was made.");
}

// this function converts the values in currentSequence to their respective values in currentSequenceBinaryForm
void TestSequence::ConvertFloatToBinary()
{
	int index, stindex; // index variable


	// clear the currentSequenceBinaryForm data structure of all existing values so new one can be place
	currentSequenceBinaryForm.ClearAll();

	currentSequenceBinaryForm.pidc_cycles = currentSequence.pidc_cycles;

	for (stindex = 0; stindex < 6; stindex++){
		currentSequenceBinaryForm.pidc[stindex] = currentSequence.pidc[stindex];
	}

	// for each sample place the appropriate values in the currentSequenceBinaryForm data structure
	// that are converted from their float form in currentSequence to binary format if there values to be converted
	for (index = 0; index < 12; index++){
 		currentSequenceBinaryForm.sample[index].AddCycles(currentSequence.sample[index].GetCycles());

		
		for (stindex = 0; stindex < 6; stindex++){
			if (currentSequence.sample[index].GetErase(stindex))
				currentSequenceBinaryForm.sample[index].AddErase(stindex,LightDevice_LookUpAndConvert((array_filenames[0 + (4 * stindex)]), 
					currentSequence.sample[index].GetErase(stindex)));
			if (currentSequence.sample[index].GetExpose(stindex))
				currentSequenceBinaryForm.sample[index].AddExpose(stindex,LightDevice_LookUpAndConvert((array_filenames[1 + (4 * stindex)]), 
					currentSequence.sample[index].GetExpose(stindex)));
			if (currentSequence.sample[index].GetGrid(stindex))
				currentSequenceBinaryForm.sample[index].AddGrid(stindex,ChargingDevice_LookUpAndConvert((array_filenames[2 + (4 * stindex)]), 
					currentSequence.sample[index].GetGrid(stindex)));
			if (currentSequence.sample[index].GetPin(stindex))
				currentSequenceBinaryForm.sample[index].AddPin(stindex,ChargingDevice_LookUpAndConvert((array_filenames[3 + (4 * stindex)]), 
					currentSequence.sample[index].GetPin(stindex)));
		}
	}



}


// this function adds the current sequence to the linked list
void TestSequence::Addsequence()
{
	char buffer[10];  // holds temporary character buffer
	SequenceFloat temp; // temporary sequence float structure
	SequenceInteger tempBinary; // temporary sequence integer structure
	CString sequenceDisplay; // string to be displayed

	// convert the current sequence to its binary form
	ConvertFloatToBinary();
	// increment number of sequences
	numberOfSequences++;

	// display on the list box
	sprintf(buffer," %d", numberOfSequences);
	sequenceDisplay += "Sequence";
	sequenceDisplay += buffer;
	m_SequenceList.AddString(sequenceDisplay);

	// copy current sequence and its binary form to the temporary data structures
	temp.Copy(currentSequence);
	tempBinary.Copy(currentSequenceBinaryForm);

	// add the temporary data structures to the linked list's tail
	sequenceFloatList.AddTail(temp);
	sequenceBinaryList.AddTail(tempBinary);

	// clear the current sequence and its binary form
	currentSequence.ClearAll();                                                                           
	currentSequenceBinaryForm.ClearAll();

	// reset m_sampleNumber
	m_sampleNumber = 1;


}

// this function is called when the user presses the modify sequence button
void TestSequence::OnModifysequence() 
{
	POSITION p, pBinary; // holds the position in the linked list
	int i, j; // index variables
	SequenceFloat temp; // temporary sequence float structure
	SequenceInteger tempBinary; // temporary sequence integer structure
	HCURSOR lhCursor;

	// place wait cursor
	lhCursor = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
	SetCursor(lhCursor);

	// record current values to current sequence
	Record();
	// convert current sequence to its binary form
	ConvertFloatToBinary();
	// get the user's selection
	i = m_SequenceList.GetCurSel();
	j = 0;

	// as long as it is valid selection
	if (i != LB_ERR){


		// get starting point of the linked list
		p = sequenceFloatList.GetHeadPosition();
		pBinary = sequenceBinaryList.GetHeadPosition();

		// increment through the list until you get to the position i
		while (j < i){
			temp = sequenceFloatList.GetNext(p);
			tempBinary = sequenceBinaryList.GetNext(pBinary);
			j++;
		}
		// copy current sequence and its binary form to the temporary data structures
		temp.Copy(currentSequence);
		tempBinary.Copy(currentSequenceBinaryForm);

		// insert the temporary data structures to the linked list at the specified position
		sequenceFloatList.SetAt(p, temp);
		sequenceBinaryList.SetAt(pBinary, tempBinary);

		// clear current sequence and its binary form
		currentSequence.ClearAll();
		currentSequenceBinaryForm.ClearAll();

		// reset m_sampleNumber
		m_sampleNumber = 1;

		// update dialog box
		Update();

	}
	else
		MessageBox("No selection was made.");

	// place normal cursor
	lhCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	SetCursor(lhCursor);


	
}

// this button is called when the user presses the reset button
void TestSequence::OnResetcurrentsequence() 
{
	// clear the current sequence and its binary form
	currentSequence.ClearAll();
	currentSequenceBinaryForm.ClearAll();

	// reset the sample number
	m_sampleNumber = 1;

	// update the dialog box
	Update();
	
}

// this function is called when the user presses the copy values function
void TestSequence::OnCopyvalues() 
{
	// save and validate data from the dialog box to associated variables
	UpdateData(TRUE); 
	// record the respective information to the respective parts of the copyGrid data structure for the current sample
//	if (m_pidc1 || m_pidc2 || m_pidc3 || m_pidc4 || m_pidc5 || m_pidc6)
//		copyGrid.cycles = m_pidc_cycles;
//	else
		copyGrid.AddCycles(m_cycles);

	copyGrid.AddErase(0, m_s1_erase);
	copyGrid.AddExpose(0, m_s1_expose);
	copyGrid.AddGrid(0, m_s1_grid);
	copyGrid.AddPin(0, m_s1_pin);
	copyGrid.AddErase(1, m_s2_erase);
	copyGrid.AddExpose(1, m_s2_expose);
	copyGrid.AddGrid(1, m_s2_grid);
	copyGrid.AddPin(1, m_s2_pin);
	copyGrid.AddErase(2, m_s3_erase);
	copyGrid.AddExpose(2, m_s3_expose);
	copyGrid.AddGrid(2, m_s3_grid);
	copyGrid.AddPin(2, m_s3_pin);
	copyGrid.AddErase(3, m_s4_erase);
	copyGrid.AddExpose(3, m_s4_expose);
	copyGrid.AddGrid(3, m_s4_grid);
	copyGrid.AddPin(3, m_s4_pin);
	copyGrid.AddErase(4, m_s5_erase);
	copyGrid.AddExpose(4, m_s5_expose);
	copyGrid.AddGrid(4, m_s5_grid);
	copyGrid.AddPin(4, m_s5_pin);
	copyGrid.AddErase(5, m_s6_erase);
	copyGrid.AddExpose(5, m_s6_expose);
	copyGrid.AddGrid(5, m_s6_grid);
	copyGrid.AddPin(5, m_s6_pin);

	copyGrid.AddErase2(0, m_s1_erase2);
	copyGrid.AddExpose2(0, m_s1_expose2);
	copyGrid.AddGrid2(0, m_s1_grid2);
	copyGrid.AddPin2(0, m_s1_pin2);
	copyGrid.AddErase2(1, m_s2_erase2);
	copyGrid.AddExpose2(1, m_s2_expose2);
	copyGrid.AddGrid2(1, m_s2_grid2);
	copyGrid.AddPin2(1, m_s2_pin2);
	copyGrid.AddErase2(2, m_s3_erase2);
	copyGrid.AddExpose2(2, m_s3_expose2);
	copyGrid.AddGrid2(2, m_s3_grid2);
	copyGrid.AddPin2(2, m_s3_pin2);
	copyGrid.AddErase2(3, m_s4_erase2);
	copyGrid.AddExpose2(3, m_s4_expose2);
	copyGrid.AddGrid2(3, m_s4_grid2);
	copyGrid.AddPin2(3, m_s4_pin2);
	copyGrid.AddErase2(4, m_s5_erase2);
	copyGrid.AddExpose2(4, m_s5_expose2);
	copyGrid.AddGrid2(4, m_s5_grid2);
	copyGrid.AddPin2(4, m_s5_pin2);
	copyGrid.AddErase2(5, m_s6_erase2);
	copyGrid.AddExpose2(5, m_s6_expose2);
	copyGrid.AddGrid2(5, m_s6_grid2);
	copyGrid.AddPin2(5, m_s6_pin2);
	
}

// this function is called when the user presses the paste values function
void TestSequence::OnPastevalues() 
{
	// read the respective information form the respective parts of the copyGrid data structure for the current sample
//	if (m_pidc1 || m_pidc2 || m_pidc3 || m_pidc4 || m_pidc5 || m_pidc6)
//		m_pidc_cycles = copyGrid.cycles;

	m_cycles = copyGrid.GetCycles();
	m_s1_erase = copyGrid.GetErase(0);
	m_s1_expose = copyGrid.GetExpose(0);
	m_s1_grid = copyGrid.GetGrid(0);
	m_s1_pin = copyGrid.GetPin(0);
	m_s2_erase = copyGrid.GetErase(1);
	m_s2_expose = copyGrid.GetExpose(1);
	m_s2_grid = copyGrid.GetGrid(1);
	m_s2_pin = copyGrid.GetPin(1);
	m_s3_erase = copyGrid.GetErase(2);
	m_s3_expose = copyGrid.GetExpose(2);
	m_s3_grid = copyGrid.GetGrid(2);
	m_s3_pin = copyGrid.GetPin(2);
	m_s4_erase = copyGrid.GetErase(3);
	m_s4_expose = copyGrid.GetExpose(3);
	m_s4_grid = copyGrid.GetGrid(3);
	m_s4_pin = copyGrid.GetPin(3);
	m_s5_erase = copyGrid.GetErase(4);
	m_s5_expose = copyGrid.GetExpose(4);
	m_s5_grid = copyGrid.GetGrid(4);
	m_s5_pin = copyGrid.GetPin(4);
	m_s6_erase = copyGrid.GetErase(5);
	m_s6_expose = copyGrid.GetExpose(5);
	m_s6_grid = copyGrid.GetGrid(5);
	m_s6_pin = copyGrid.GetPin(5);

	m_s1_erase2 = copyGrid.GetErase2(0);
	m_s1_expose2 = copyGrid.GetExpose2(0);
	m_s1_grid2 = copyGrid.GetGrid2(0);
	m_s1_pin2 = copyGrid.GetPin2(0);
	m_s2_erase2 = copyGrid.GetErase2(1);
	m_s2_expose2 = copyGrid.GetExpose2(1);
	m_s2_grid2 = copyGrid.GetGrid2(1);
	m_s2_pin2 = copyGrid.GetPin2(1);
	m_s3_erase2 = copyGrid.GetErase2(2);
	m_s3_expose2 = copyGrid.GetExpose2(2);
	m_s3_grid2 = copyGrid.GetGrid2(2);
	m_s3_pin2 = copyGrid.GetPin2(2);
	m_s4_erase2 = copyGrid.GetErase2(3);
	m_s4_expose2 = copyGrid.GetExpose2(3);
	m_s4_grid2 = copyGrid.GetGrid2(3);
	m_s4_pin2 = copyGrid.GetPin2(3);
	m_s5_erase2 = copyGrid.GetErase2(4);
	m_s5_expose2 = copyGrid.GetExpose2(4);
	m_s5_grid2 = copyGrid.GetGrid2(4);
	m_s5_pin2 = copyGrid.GetPin2(4);
	m_s6_erase2 = copyGrid.GetErase2(5);
	m_s6_expose2 = copyGrid.GetExpose2(5);
	m_s6_grid2 = copyGrid.GetGrid2(5);
	m_s6_pin2 = copyGrid.GetPin2(5);
	// update dialog box
	UpdateData(FALSE);

}


// this function called when the Pidc button for 
// station 1 is checked or unchecked, it disables the cycles
// and station 1 erase entries
void TestSequence::OnPidcCheck1() 
{
	UpdateData(TRUE);
	// call all pidc check functions to update dialog;
	CallAllPidcCheck();

}


// this function called when the Pidc button for 
// station 2 is checked or unchecked, it disables the cycles
// and station 2 erase entries
void TestSequence::OnPidcCheck2() 
{
	UpdateData(TRUE);
	// call all pidc check functions to update dialog;
	CallAllPidcCheck();
	
}


// this function called when the Pidc button for 
// station 3 is checked or unchecked, it disables the cycles
// and station 3 erase entries
void TestSequence::OnPidcCheck3() 
{
	UpdateData(TRUE);
	// call all pidc check functions to update dialog;
	CallAllPidcCheck();
	
}


// this function called when the Pidc button for 
// station 4 is checked or unchecked, it disables the cycles
// and station 4 erase entries
void TestSequence::OnPidcCheck4() 
{
	UpdateData(TRUE);
	// call all pidc check functions to update dialog;
	CallAllPidcCheck();
	
}


// this function called when the Pidc button for 
// station 5 is checked or unchecked, it disables the cycles
// and station 5 erase entries
void TestSequence::OnPidcCheck5() 
{
	UpdateData(TRUE);
	// call all pidc check functions to update dialog;
	CallAllPidcCheck();

	
}


// this function called when the Pidc button for 
// station 6 is checked or unchecked, it disables the cycles
// and station 6 erase entries
void TestSequence::OnPidcCheck6() 
{
	UpdateData(TRUE);
	// call all pidc check functions to update dialog;
	CallAllPidcCheck();
}

// function similar to Sami Mesbhah's ShowHide
// it takes in id values of MS objects and either disables or enables them
void TestSequence::ShowHide(int *showcntl, int num_show, int *hidecntl, int num_hide)
{
	int i;

	for(i = 0; i < num_show; i++){
		CWnd* item = GetDlgItem(showcntl[i]);
		item->EnableWindow(TRUE);
		item->UpdateWindow();
	}
	for(i = 0; i < num_hide; i++){
		CWnd* item = GetDlgItem(hidecntl[i]);
		item->EnableWindow(FALSE);
		item->UpdateWindow();
	}
	
}

// this function tests all the pidc values that are
// currently valid and updates the screen
// called from the update function and OnPidcCheck(1,2,3,4,5,6) functions
void TestSequence::CallAllPidcCheck()
{
	int num_cntl =1;
	int controls [1];

	controls [0] = IDC_CYCLES;
	if ((m_pidc1 || m_pidc2 || m_pidc3 || m_pidc4 || m_pidc5 || m_pidc6)
		 || (chrgDevIncr->m_grid1 || chrgDevIncr->m_grid2 || chrgDevIncr->m_grid3 || chrgDevIncr->m_grid4 || chrgDevIncr->m_grid5 || chrgDevIncr->m_grid6))
		ShowHide(NULL,0,controls,num_cntl);
	else
		ShowHide(controls,num_cntl,NULL,0);

	controls [0] = IDC_S1_EXPOSE;	
	if (m_pidc1)
		ShowHide(NULL,0,controls,num_cntl);
	else
		ShowHide(controls,num_cntl,NULL,0);

	controls [0] = IDC_S2_EXPOSE;	
	if (m_pidc2)
		ShowHide(NULL,0,controls,num_cntl);
	else
		ShowHide(controls,num_cntl,NULL,0);

	controls [0] = IDC_S3_EXPOSE;	
	if (m_pidc3)
		ShowHide(NULL,0,controls,num_cntl);
	else
		ShowHide(controls,num_cntl,NULL,0);

	controls [0] = IDC_S4_EXPOSE;	
	if (m_pidc4)
		ShowHide(NULL,0,controls,num_cntl);
	else
		ShowHide(controls,num_cntl,NULL,0);

	controls [0] = IDC_S5_EXPOSE;	
	if (m_pidc5)
		ShowHide(NULL,0,controls,num_cntl);
	else
		ShowHide(controls,num_cntl,NULL,0);

	controls [0] = IDC_S6_EXPOSE;	
	if (m_pidc6)
		ShowHide(NULL,0,controls,num_cntl);
	else
		ShowHide(controls,num_cntl,NULL,0);
}


float* TestSequence::getHighestExposeValue()
{
	int index;
	float highest_value;
	int i, temp;
	char* name;
	FILE* instream;
	for (index = 0; index < 6; index++){
		// read the highest value from the lookup table
		// array_filenames 1,5,9,13,17,21 corresponds to Expose
		temp = 1 +(index*4);
		name = array_filenames[temp].GetBuffer(array_filenames[temp].GetLength());

		if ((instream = fopen(name, "r")) != NULL){
			for (i = 0; i < BIPOLAR_PRECISION; i++)
				fscanf(instream, "%f %f", &highest_value, &highest_value);
		}
		fclose(instream);

		// calculate increment value
		exposeValues[index] = highest_value;

	}
	return exposeValues;
}

void TestSequence::OnRepeatsequence() 
{
	POSITION p; // holds the position in the linked list
	int i, j; // index variables
	SequenceFloat temp; // temporary sequence float structure
	HCURSOR lhCursor;


	// check list to see if a correct item has been selected
	// if so copy that sequence and insert it after the last sequence
	i = m_SequenceList.GetCurSel();
	j = 0;
	if (i != LB_ERR){

		// place wait cursor
		lhCursor = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
		SetCursor(lhCursor);


		// get starting point of the linked list
		p = sequenceFloatList.GetHeadPosition();

		// increment through the list until you get to the position i
		while (j < i){
			temp = sequenceFloatList.GetNext(p);
			j++;
		}

		// get the item i from the list
		temp = sequenceFloatList.GetAt(p);

		// copy to current sequence and update the dialog
		currentSequence.Copy(temp);

		// reset m_sampleNumber
		m_sampleNumber = 1;
		
		// add sequence to linked list
		Addsequence();

		// update the dialog box
		Update();

		// place normal cursor
		lhCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		SetCursor(lhCursor);


	}
	// if a correct item has not been selected inform user to make a correct selection
	else
		MessageBox("No selection was made.");


	
}

void TestSequence::OnSetincrements() 
{
	if (chrgDevIncr == NULL)
		MessageBox ("Can not perform increment operation.");
	else{
		chrgDevIncr->DoModal();
		CallAllIncrementCheck();
	}
	UpdateData(FALSE);
	
}

void TestSequence::CallAllIncrementCheck()
{
	CString message; // to be deleted after debug 
	int num_cntl_hide = 0, num_cntl_show = 0; ;
	int show_controls [6], hide_controls [6];
	bool hide_cycle = FALSE;

	if (chrgDevIncr == NULL)
		MessageBox ("Increment Object doesn't seem to exist.");
	else{
		if (chrgDevIncr->m_grid1){
			hide_controls[num_cntl_hide] = IDC_S1_GRID;
			num_cntl_hide++;
			hide_cycle = TRUE;
//			message.Format("Increment %f Initial %f",chrgDevIncr->m_increment1,chrgDevIncr->m_initial1);
//			MessageBox(message);
		}
		else{
			show_controls[num_cntl_show] = IDC_S1_GRID;
			num_cntl_show++;
		}
		if (chrgDevIncr->m_grid2){
			hide_controls[num_cntl_hide] = IDC_S2_GRID;
			num_cntl_hide++;
			hide_cycle = TRUE;
//			message.Format("Increment %f Initial %f",chrgDevIncr->m_increment2,chrgDevIncr->m_initial2);
//			MessageBox(message);
		}
		else{
			show_controls[num_cntl_show] = IDC_S2_GRID;
			num_cntl_show++;
		}
		if (chrgDevIncr->m_grid3){
			hide_controls[num_cntl_hide] = IDC_S3_GRID;
			num_cntl_hide++;
			hide_cycle = TRUE;
//			message.Format("Increment %f Initial %f",chrgDevIncr->m_increment3,chrgDevIncr->m_initial3);
//			MessageBox(message);
		}
		else{
			show_controls[num_cntl_show] = IDC_S3_GRID;
			num_cntl_show++;
		}
		if (chrgDevIncr->m_grid4){
			hide_controls[num_cntl_hide] = IDC_S4_GRID;
			num_cntl_hide++;
			hide_cycle = TRUE;
//			message.Format("Increment %f Initial %f",chrgDevIncr->m_increment4,chrgDevIncr->m_initial4);
//			MessageBox(message);
		}
		else{
			show_controls[num_cntl_show] = IDC_S4_GRID;
			num_cntl_show++;
		}
		if (chrgDevIncr->m_grid5){
			hide_controls[num_cntl_hide] = IDC_S5_GRID;
			num_cntl_hide++;
			hide_cycle = TRUE;
//			message.Format("Increment %f Initial %f",chrgDevIncr->m_increment5,chrgDevIncr->m_initial5);
//			MessageBox(message);
		}
		else{
			show_controls[num_cntl_show] = IDC_S5_GRID;
			num_cntl_show++;
		}
		if (chrgDevIncr->m_grid6){
			hide_controls[num_cntl_hide] = IDC_S6_GRID;
			num_cntl_hide++;
			hide_cycle = TRUE;
//			message.Format("Increment %f Initial %f",chrgDevIncr->m_increment6,chrgDevIncr->m_initial6);
//			MessageBox(message);
		}
		else{
			show_controls[num_cntl_show] = IDC_S6_GRID;
			num_cntl_show++;
		}
		ShowHide(show_controls,num_cntl_show, hide_controls, num_cntl_hide);

		if (hide_cycle){
			hide_controls[0] = IDC_CYCLES;
			hide_controls[1] = IDC_CYCLES_PIDC;
			ShowHide(NULL,0,hide_controls,2);
			hide_controls[0] = IDC_PIDC_CHECK1;
			hide_controls[1] = IDC_PIDC_CHECK2;
			hide_controls[2] = IDC_PIDC_CHECK3;
			hide_controls[3] = IDC_PIDC_CHECK4;
			hide_controls[4] = IDC_PIDC_CHECK5;
			hide_controls[5] = IDC_PIDC_CHECK6;
			ShowHide(NULL,0,hide_controls,6);
			if(chrgDevIncr->m_totalnumber*chrgDevIncr->m_cyclesBeforeIncrement)
				m_cycles = chrgDevIncr->m_totalnumber*chrgDevIncr->m_cyclesBeforeIncrement;
		}
		else
		{
			show_controls[0] = IDC_CYCLES;
			show_controls[1] = IDC_CYCLES_PIDC;
			ShowHide(show_controls,2,NULL,0);
			show_controls[0] = IDC_PIDC_CHECK1;
			show_controls[1] = IDC_PIDC_CHECK2;
			show_controls[2] = IDC_PIDC_CHECK3;
			show_controls[3] = IDC_PIDC_CHECK4;
			show_controls[4] = IDC_PIDC_CHECK5;
			show_controls[5] = IDC_PIDC_CHECK6;
			ShowHide(show_controls,6,NULL,0);
		}
	}

}


void TestSequence::OnSetfocusS1Grid() 
{
	if ((!m_popupoff) && (!m_grid1_list.IsWindowVisible()))
		m_grid1_list.ShowWindow(SW_SHOW);
	
}

void TestSequence::OnKillfocusS1Grid() 
{
	if (m_grid1_list.IsWindowVisible())
		m_grid1_list.ShowWindow(SW_HIDE);

	
}

void TestSequence::OnSetfocusS2Grid() 
{
	if ((!m_popupoff) && (!m_grid2_list.IsWindowVisible()))
		m_grid2_list.ShowWindow(SW_SHOW);
	
}

void TestSequence::OnKillfocusS2Grid() 
{
	if (m_grid2_list.IsWindowVisible())
		m_grid2_list.ShowWindow(SW_HIDE);

	
}

void TestSequence::OnSetfocusS3Grid() 
{
	if ((!m_popupoff) && (!m_grid3_list.IsWindowVisible()))
		m_grid3_list.ShowWindow(SW_SHOW);

	
}

void TestSequence::OnKillfocusS3Grid() 
{
	if (m_grid3_list.IsWindowVisible())
		m_grid3_list.ShowWindow(SW_HIDE);

	
}

void TestSequence::OnSetfocusS4Grid() 
{
	if ((!m_popupoff) && (!m_grid4_list.IsWindowVisible()))
		m_grid4_list.ShowWindow(SW_SHOW);

	
}

void TestSequence::OnKillfocusS4Grid() 
{
	if (m_grid4_list.IsWindowVisible())
		m_grid4_list.ShowWindow(SW_HIDE);

	
}

void TestSequence::OnSetfocusS5Grid() 
{
	if ((!m_popupoff) && (!m_grid5_list.IsWindowVisible()))
		m_grid5_list.ShowWindow(SW_SHOW);

	
}

void TestSequence::OnKillfocusS5Grid() 
{
	if (m_grid5_list.IsWindowVisible())
		m_grid5_list.ShowWindow(SW_HIDE);

	
}

void TestSequence::OnSetfocusS6Grid() 
{
	if ((!m_popupoff) && (!m_grid6_list.IsWindowVisible()))
		m_grid6_list.ShowWindow(SW_SHOW);

	
}

void TestSequence::OnKillfocusS6Grid() 
{
	if (m_grid6_list.IsWindowVisible())
		m_grid6_list.ShowWindow(SW_HIDE);

	
}

// PURPOSE: reads grids' associated text files
// and inserts the file into the pop up menus.
void TestSequence::readgridvalues(){
	int j = 0;
	const int bufferlength = 200;
	FILE* istream;
	CString message;
	CString insertString;
	char buffer[bufferlength] = "";
	int index = 0;

	int curr_sam = m_sampleNumber - 1;
	
	// clear the list objects
	m_grid1_list.ResetContent();
	m_grid2_list.ResetContent();
	m_grid3_list.ResetContent();
	m_grid4_list.ResetContent();
	m_grid5_list.ResetContent();
	m_grid6_list.ResetContent();

	// for each grid read in the associated grid file values
	// and insert into the list objects
	for (j = 0; j < NUMBEROFGRIDS; j++){
		if ((istream = fopen(gridfilenames[curr_sam][j], "r")) != NULL){
			// reset index for new file
			index = 0;
			do {
				fgets(buffer, bufferlength, istream);
				insertString = cleanstring(buffer);
				
				if (j == 0){
					m_grid1_list.InsertString(index, insertString);
				}
				else if (j == 1){
					m_grid2_list.InsertString(index, insertString);
				}
				else if (j == 2){
					m_grid3_list.InsertString(index, insertString);
				}
				else if (j == 3){
					m_grid4_list.InsertString(index, insertString);
				}
				else if (j == 4){
					m_grid5_list.InsertString(index, insertString);
				}
				else if (j == 5){
					m_grid6_list.InsertString(index, insertString);
				}
				index++;
			} while (!feof(istream));

			index--;
			if (j == 0){
				m_grid1_list.DeleteString(index);
			}
			else if (j == 1){
				m_grid2_list.DeleteString(index);
			}
			else if (j == 2){
				m_grid3_list.DeleteString(index);
			}
			else if (j == 3){
				m_grid4_list.DeleteString(index);
			}
			else if (j == 4){
				m_grid5_list.DeleteString(index);
			}
			else if (j == 5){
				m_grid6_list.DeleteString(index);
			}


				
	
			fclose(istream);
		}
		else{
			message = "Unable to open " + gridfilenames[curr_sam][j];
			message += ".";
			MessageBox(message);
		}
	}
}

// PURPOSE: function removes tab and newline escape sequences from
// a string.
// INPUTS: character pointer to string.
// RETURN VALUE: character pointer to formatted string.
char* TestSequence::cleanstring(char* bufferptr){
	char* index = bufferptr;
	while (*index != NULL){
		if ((*index == '\n') || (*index == '\t'))
			*index = ' ';
		index++;
	}
	return bufferptr;
}

void TestSequence::OnPopupcheck() 
{
	UpdateData(TRUE);	
}
