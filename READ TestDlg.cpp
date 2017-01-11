// READ TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "READ Test.h"
#include "READ TestDlg.h"
#include "TestRunEngine.h"

#include <stdlib.h>
#include <process.h>
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CREADTestDlg dialog

CREADTestDlg::CREADTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CREADTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CREADTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// set pointer to modeless CTestProgressIndicator to NULL;
	m_ProgressIndicator = NULL;
	m_revolutions = 0;
	test_is_PIDC = FALSE;
	okayToTransferToJaz = FALSE;
	chrgDevIncr = new CChargeDeviceIncrement(this);
}

void CREADTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CREADTestDlg)
	DDX_Control(pDX, IDC_TESTSUMMARY, m_TestSummary);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CREADTestDlg, CDialog)
	//{{AFX_MSG_MAP(CREADTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_BUILDTEST, OnBuildtest)
	ON_LBN_DBLCLK(IDC_TESTSUMMARY, OnDblclkTestsummary)
	ON_BN_CLICKED(IDC_RUNTEST, OnRuntest)
	ON_BN_CLICKED(IDC_LIGHTCALIBRATION, OnLightcalibration)
	ON_BN_CLICKED(IDC_PROBECALIBRATION, OnProbecalibration)
	ON_BN_CLICKED(IDC_JAZSAVE, OnJazsave)
	ON_BN_CLICKED(IDC_SETTINGS, OnSettings)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CREADTestDlg message handlers

BOOL CREADTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CREADTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CREADTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CREADTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// this function is called when the motor speed button is pressed
//DEL void CREADTestDlg::OnMotorspeed() 
//DEL {
//DEL 	// open the motor speed dialog
//DEL 	tab1motorSpeed.DoModal();	
//DEL }

// this function is called when the user presses the build test button
// this function builds the test information that shall be required to run the test
void CREADTestDlg::OnBuildtest() 
{
	int i, j; // index variables
	char currentDirectory[100]; // char buffer that shall contain the current directory path
	char buffer[100]; // temporary character buffer
	SequenceInteger temp; // temporary binary sequence used to transfer information to the built on test sequence function
	POSITION p; // holds the current position of the test sequence list
	FILE* instream; // pointer to file

	// Clear summary box
	j = m_TestSummary.GetCount();
	for(i = j; i > -1; --i)
		m_TestSummary.DeleteString(i);

	// reset number of revolutions
	m_revolutions = 0;

	// get current directory path and place in the character buffer currentDirectory
	// this information is used to get the program back to the working directory since
	// the user has the capability to switch directories as they load in information for the test
	_getcwd( currentDirectory, _MAX_PATH );

	LoadSettings();

	// add the property pages to the property sheet and set to Wizard mode
	// the property sheet shall be set as a Wizard prompting the user to enter information in a sequential manner
	m_pBuildTestProperties.AddPage(&Page1GeneralSummary);


	// read in filenames of look up tables
	if (( instream = fopen("filenames.txt", "r")) != NULL){
		for (i = 0; i < 24; i++){
			fscanf(instream, "%s", buffer);
			Page2TestSequence.array_filenames[i] = buffer;
		}
	}
	else
		MessageBox("Unable to open files containing look up values for devices.");
	fclose(instream);

	m_pBuildTestProperties.AddPage(&Page2TestSequence);

	// read in the values of the test counter - this is used to keep the test names unique
	if ((instream = fopen("READ Test.ini", "r")) != NULL)
		fscanf(instream, "%d", &Page3ExperimentName.m_ProjectCounter);
	fclose(instream);

	m_pBuildTestProperties.AddPage(&Page3ExperimentName);
	m_pBuildTestProperties.SetWizardMode();

	Page1GeneralSummary.m_comments.Empty();
	Page3ExperimentName.m_ProjectName.Empty();
	// if the user pressed finish on the final property page do the following
	if (m_pBuildTestProperties.DoModal() == ID_WIZFINISH){


		// change back to current working directory
		_chdir(currentDirectory);

		// assign the number of sequences to i
		i = Page2TestSequence.numberOfSequences;
		// assign the starting position of the list
		p = Page2TestSequence.sequenceBinaryList.GetHeadPosition();

		int seq_number = 0;
		// build one sequence at a time while i is not zero
		while(i){
			seq_number++;
			// get the current test sequence and assign it to temp
			// increment p to the next position on the list
			temp = Page2TestSequence.sequenceBinaryList.GetNext(p);
			// build the test sequence contained in temp
			BuildOneTestSequence(temp, seq_number);
			// decrement i - used to ensure only the correct number of test sequences are built
			i--;
		}


		// remove property pages from the property sheet - needs to be done or conflicts can occur when property sheet is reloaded again
		m_pBuildTestProperties.RemovePage(&Page1GeneralSummary);
		m_pBuildTestProperties.RemovePage(&Page2TestSequence);
		m_pBuildTestProperties.RemovePage(&Page3ExperimentName);

		// add the counter value to the project name
		sprintf(buffer, "%d", Page3ExperimentName.m_ProjectCounter);
		Page3ExperimentName.m_ProjectName += buffer;

		// create folder named under the project name
		mkdir(Page3ExperimentName.m_ProjectName);

		// modify the variable m_ProjectName so that all files pertaining
		// to the project are saved in the folder named under the project name
		Page3ExperimentName.m_ProjectName += "\\" + returnRootName(Page3ExperimentName.m_ProjectName);

		// increment project counter and rewrite the value back to the file
		Page3ExperimentName.m_ProjectCounter++;
		if ((instream = fopen("READ Test.ini", "w")) != NULL)
			fprintf(instream, "%d", Page3ExperimentName.m_ProjectCounter);
		fclose(instream);

		// display the current test summary
		DisplaySummary();

		// save the experiment information
		SaveExperimentInfo();
	}
	else{
		// remove property pages from the property sheet - needs to be done or conflicts can occur when property sheet is reloaded again
		m_pBuildTestProperties.RemovePage(&Page1GeneralSummary);
		m_pBuildTestProperties.RemovePage(&Page2TestSequence);
		m_pBuildTestProperties.RemovePage(&Page3ExperimentName);
		// since test creation was cancelled remove whatever is on the test sequence list both the float and binary versions and reset the number of sequences
		Page2TestSequence.sequenceFloatList.RemoveAll();
		Page2TestSequence.sequenceBinaryList.RemoveAll();
		Page2TestSequence.numberOfSequences = 0;
	}

}

// the function displays the test summary by gathering the information from various test property pages and placing them in the
// list box in the main window - should be only called from the build test function when all the information is available
void CREADTestDlg::DisplaySummary()
{
	char buffer [70];  // character buffer
	CString displayString; // stirng to be displayed
	// add to list box the experiment filename, date and time and summary comments
	m_TestSummary.InsertString(-1,"Experiment Filename:");
	m_TestSummary.InsertString(-1,Page3ExperimentName.m_ProjectName);
	m_TestSummary.InsertString(-1,"");
	m_TestSummary.InsertString(-1,"Experiment Date and Time:");
	m_TestSummary.InsertString(-1,Page1GeneralSummary.m_DateAndTime);
	m_TestSummary.InsertString(-1,"");
	m_TestSummary.InsertString(-1,"Experiment Summary");
	m_TestSummary.InsertString(-1,Page1GeneralSummary.m_comments);
	m_TestSummary.InsertString(-1,"");	

	// add to the list box information about the samples - sample number, sample id, start hole and end hole, comments
	m_TestSummary.InsertString(-1,"Samples:");
	for (int i = 0; i < 12; i ++){
		sprintf(buffer,"Sample %d: Start Hole %d, End Hole %d, ", (i+1), tab3sampleInformation.startHole[i], tab3sampleInformation.endHole[i]);
		displayString.Insert(0, buffer);
		displayString += "Sample ID - " + tab3sampleInformation.sampleID[i] + ", Comments - " + tab3sampleInformation.comments[i];
		m_TestSummary.InsertString(-1,displayString);
		displayString.Empty();
	}
	m_TestSummary.InsertString(-1,"");	

	// add to the list box information about the devices - station number, position of charging device, Vddp probe, Expose Light device, Vexp probe and Erase Light device
	m_TestSummary.InsertString(-1,"Devices:");
	for (i = 0; i < 6; i ++){
		sprintf(buffer,"Station %d: Charge %d, VDDP %d, Expose %d, VEXP %d, Erase %d", 
			i+1, tab2devicePositions.chargingDevice[i], tab2devicePositions.vddpProbe[i],tab2devicePositions.exposeDevice[i],
			tab2devicePositions.vexpProbe[i], tab2devicePositions.eraseDevice[i]);
		m_TestSummary.InsertString(-1,buffer);
	}

}

// this function is called when the user double clicks on the test summary list box in the main window
// it checks to see if the user clicked on one of the samples or stations and if so displays that information
void CREADTestDlg::OnDblclkTestsummary() 
{
	int i; // index variable
	char buffer [200]; // character buffer
	CString displayString, tempString; // display strings
	// get the cursor selection of the user
	i = m_TestSummary.GetCurSel();
	// if the user selected samples display the information regarding that particular sample
	if ((10 <= i) && (i <= 21)){
		i -= 10;
		sprintf(buffer,"%d", (i+1));
		displayString += "Sample ";
		displayString += buffer;
		sprintf(buffer,"%d", tab3sampleInformation.startHole[i]);
		tempString.Insert(0, buffer);	
		displayString += "\n\n\nStartHole\t\t" + tempString;
		tempString.Empty();
		sprintf(buffer,"%d", tab3sampleInformation.endHole[i]);
		tempString.Insert(0, buffer);		
		displayString += "\nEndHole\t\t" + tempString;
		displayString += "\nSample ID\t" + tab3sampleInformation.sampleID[i] + "\nComments\t" + tab3sampleInformation.comments[i];
		MessageBox(displayString);

	}
	// else if the user selected stations display the information regarding that particular station
	else if ((24 <= i) && (i <= 29)){
		i -= 24;
		sprintf(buffer,"Station %d \n\n\nCharge\t%d \nVDDP\t%d \nExpose\t%d \nVEXP\t%d \nErase\t%d", 
			i+1, tab2devicePositions.chargingDevice[i], tab2devicePositions.vddpProbe[i],tab2devicePositions.exposeDevice[i],
			tab2devicePositions.vexpProbe[i], tab2devicePositions.eraseDevice[i]);
		MessageBox(buffer);

	}


}

// this function is called when the user presses run test
// it reads the output files device2.out, device3.out and device4.out and outputs the data while
// simultaneous reading in all the data from the various probes and placing them 
// in a results file.
void CREADTestDlg::OnRuntest() 
{
	SequenceInteger temp;
	// assign the number of sequences to i
	int	i = Page2TestSequence.numberOfSequences;
		// assign the starting position of the list
	POSITION p = Page2TestSequence.sequenceBinaryList.GetHeadPosition();

	int seq_number = 0;
	// run one sequence at a time while i is not zero
	while(i){
		seq_number++;

		// get the current test sequence and assign it to temp
		// increment p to the next position on the list
		temp = Page2TestSequence.sequenceBinaryList.GetNext(p);

		CTestRunEngine* TestRunEngine = new CTestRunEngine(Page3ExperimentName.m_ProjectName+ ".trf", 
														   tab1motorSpeed.m_MotorSpeed,
														   m_revolutions, seq_number,
														   temp.sectionAcycles, temp.sectionBcycles);
		if (m_miscSettings.m_bufferedmode)
			TestRunEngine->BufferedMode();
		else if (m_miscSettings.m_nonbufferedmode)
			TestRunEngine->NonBufferedMode();
		else if (m_miscSettings.m_nonbuffereddynamicmode)
			TestRunEngine->NonBufferedDynamicMode();
		else
			MessageBox("Please select a mode of operation from the settings option.");
		delete TestRunEngine;

		// decrement i - used to ensure only the correct number of test sequences are built
		i--;

	}



}


// this function is called to save the experiment information
void CREADTestDlg::SaveExperimentInfo()
{
	CString filename; // holds filename
	CString calfile; // holds filename of calibration file

	// save device positions to a file and save it under the common project name with extension ".rdp"
	filename.Empty();
	filename = Page3ExperimentName.m_ProjectName + ".rdp";
	tab2devicePositions.Save(filename);

	// save test summary to a file and save it under the common project name with extension ".tsu"
	filename.Empty();
	filename = Page3ExperimentName.m_ProjectName + ".tsu";	
	Page1GeneralSummary.Save(filename);

	// save samples' information to a file and save it under the common project name with extension ".tsi"
	filename.Empty();
	filename = Page3ExperimentName.m_ProjectName + ".tsi";
	tab3sampleInformation.Save(filename);

	// save test sequence to a file and save it under the common project name with extension ".seq"
	filename.Empty();
	filename = Page3ExperimentName.m_ProjectName + ".seq";
	if (!test_is_PIDC){
		Page2TestSequence.Save(filename);
	}
	else
	{
		test_is_PIDC = FALSE;

	}

	// save probe calibration information to a file and save it under the common project name with extension ".rcl"
	// get the name of the file to be copied
	calfile = "read_probes.rcl";
	filename = Page3ExperimentName.m_ProjectName + ".rcl";
	// Copy the file
	::CopyFile(calfile, filename, FALSE);

	filename.Empty();
	filename = Page3ExperimentName.m_ProjectName + ".icr";
	chrgDevIncr->Save(filename);

}

// this function is called when the user presses the light calibration button
void CREADTestDlg::OnLightcalibration() 
{
	// add the scaling calculation and the light calibration as two tabs
	//m_pLightCalibration.AddPage(&tab1scaleCalculator);
	m_pLightCalibration.AddPage(&tab2lightCalibration);
	m_pLightCalibration.AddPage(&tab3Modified_LightMeterScalingCalculator);
	m_pLightCalibration.DoModal();
	//m_pLightCalibration.RemovePage(&tab1scaleCalculator);
	m_pLightCalibration.RemovePage(&tab2lightCalibration);
	m_pLightCalibration.RemovePage(&tab3Modified_LightMeterScalingCalculator);
}

// this function is called when the user presses the probe calibration button
void CREADTestDlg::OnProbecalibration() 
{
	// Declare variables
	FILE *filehandle;			// Pointer to open file
	CString filename;			// Name of the data file
	int i;						// Counter to index through the lines of the input files
	int j;						// Counter to index through the information contained on a line of the input files
	int dummy;					// Dummy variable 


	// Open the device channel file for reading
	if ( (filehandle = fopen("read_devices.rch", "r")) != NULL )
	{
		// Read the device and channel information for all of the voltage probes
		for (i=0; i<6; i++)
		{
			// Read the device and channel numbers for the vddp and vexp probes
			fscanf(filehandle, "%d%d", &probeCalibration.probes[(2*i)].device, &probeCalibration.probes[(2*i)].channel);
			fscanf(filehandle, "%d%d", &probeCalibration.probes[((2*i)+1)].device, &probeCalibration.probes[((2*i)+1)].channel);

			// Scan through the rest of the device and channel numbers for the rest of the station members
			for (j=0; j<8; j++)
				fscanf(filehandle, "%d", &dummy);
		}

		// Close the file
		fclose( filehandle );
	}
	else
	{
		MessageBox("The file \"read_devices.rch\" was not present.\nCalibration cannot continue.");
		OnOK();
	}

	
	// Open the previous calibration file for reading
	if ( (filehandle = fopen("read_probes.rcl", "r")) != NULL )
	{
		// Read the calibration information from the data file
		for (i=0; i<12; i++)
		{
			// Read the current probe's information
			fscanf(filehandle, "%lf%lf", &probeCalibration.probes[i].zero, &probeCalibration.probes[i].slope);
		}

		// Close the file
		fclose( filehandle );
	}
	else
	{
		// There was no calibration file present
		// Fill all of the calibration values with zeroes
		for (i=0; i<12; i++)
		{
			probeCalibration.probes[i].zero = 0;
			probeCalibration.probes[i].slope = 0;
		}
	}

	// Update the information on all of the probes for the interface
	probeCalibration.m_s1_vddp_zero = probeCalibration.probes[0].zero;
	probeCalibration.m_s1_vddp_slope = probeCalibration.probes[0].slope;
	probeCalibration.m_s1_vexp_zero = probeCalibration.probes[1].zero;
	probeCalibration.m_s1_vexp_slope = probeCalibration.probes[1].slope;

	probeCalibration.m_s2_vddp_zero = probeCalibration.probes[2].zero;
	probeCalibration.m_s2_vddp_slope = probeCalibration.probes[2].slope;
	probeCalibration.m_s2_vexp_zero = probeCalibration.probes[3].zero;
	probeCalibration.m_s2_vexp_slope = probeCalibration.probes[3].slope;

	probeCalibration.m_s3_vddp_zero = probeCalibration.probes[4].zero;
	probeCalibration.m_s3_vddp_slope = probeCalibration.probes[4].slope;
	probeCalibration.m_s3_vexp_zero = probeCalibration.probes[5].zero;
	probeCalibration.m_s3_vexp_slope = probeCalibration.probes[5].slope;

	probeCalibration.m_s4_vddp_zero = probeCalibration.probes[6].zero;
	probeCalibration.m_s4_vddp_slope = probeCalibration.probes[6].slope;
	probeCalibration.m_s4_vexp_zero = probeCalibration.probes[7].zero;
	probeCalibration.m_s4_vexp_slope = probeCalibration.probes[7].slope;

	probeCalibration.m_s5_vddp_zero = probeCalibration.probes[8].zero;
	probeCalibration.m_s5_vddp_slope = probeCalibration.probes[8].slope;
	probeCalibration.m_s5_vexp_zero = probeCalibration.probes[9].zero;
	probeCalibration.m_s5_vexp_slope = probeCalibration.probes[9].slope;

	probeCalibration.m_s6_vddp_zero = probeCalibration.probes[10].zero;
	probeCalibration.m_s6_vddp_slope = probeCalibration.probes[10].slope;
	probeCalibration.m_s6_vexp_zero = probeCalibration.probes[11].zero;
	probeCalibration.m_s6_vexp_slope = probeCalibration.probes[11].slope;

	// Update the interface
	UpdateData(FALSE);

	probeCalibration.DoModal();
		
}


// this function is called when the user presses the exit button
void CREADTestDlg::OnExit() 
{
	OnOK();	//Exit main dialog box
}


float* CREADTestDlg::returnPidcIncrements(int cycles)
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
		if (cycles)
			global_pidc_increment[index] = highest_value / cycles;
		else
			global_pidc_increment[index] = 0;

	}
	return global_pidc_increment;

}

int* CREADTestDlg::returnPidcExpose(int currentcycle, float *pidc_increment)
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

// Save current test and associated files to Jaz drive
void CREADTestDlg::OnJazsave() 
{
	CString newFile, oldFile;	// contain filenames
	JazPath.m_JazDirectory = "E:\\";	// contain path directory
	JazPath.m_JazProjectName = returnRootName(Page3ExperimentName.m_ProjectName);// contain pathname
	if (okayToTransferToJaz){
		if (JazPath.DoModal() == IDOK){
			okayToTransferToJaz = FALSE;
			newFile = JazPath.m_JazDirectory + JazPath.m_JazProjectName;
			mkdir(newFile);

			newFile =  JazPath.m_JazDirectory + JazPath.m_JazProjectName + "\\" 
				+ JazPath.m_JazProjectName + ".rcl";
			oldFile = Page3ExperimentName.m_ProjectName + ".rcl";
			::CopyFile(oldFile, newFile, FALSE);

			newFile =  JazPath.m_JazDirectory + JazPath.m_JazProjectName + "\\" 
				+ JazPath.m_JazProjectName + ".rdp";
			oldFile = Page3ExperimentName.m_ProjectName + ".rdp";
			::CopyFile(oldFile, newFile, FALSE);

			newFile =  JazPath.m_JazDirectory + JazPath.m_JazProjectName + "\\" 
				+ JazPath.m_JazProjectName + ".seq";
			oldFile = Page3ExperimentName.m_ProjectName + ".seq";
			::CopyFile(oldFile, newFile, FALSE);

			newFile =  JazPath.m_JazDirectory + JazPath.m_JazProjectName + "\\" 
				+ JazPath.m_JazProjectName + ".trf";
			oldFile = Page3ExperimentName.m_ProjectName + ".trf";
			::CopyFile(oldFile, newFile, FALSE);

			newFile =  JazPath.m_JazDirectory + JazPath.m_JazProjectName + "\\" 
				+ JazPath.m_JazProjectName + ".tsi";
			oldFile = Page3ExperimentName.m_ProjectName + ".tsi";
			::CopyFile(oldFile, newFile, FALSE);

			newFile =  JazPath.m_JazDirectory + JazPath.m_JazProjectName + "\\" 
				+ JazPath.m_JazProjectName + ".tsu";
			oldFile = Page3ExperimentName.m_ProjectName + ".tsu";
			::CopyFile(oldFile, newFile, FALSE);

		}
	}
	else 
		MessageBox("Please run a test before saving to JAZ drive.");
}

void CREADTestDlg::OnSettings() 
{
	LoadSettings();

	m_pSettings.AddPage(&tab1motorSpeed);
	m_pSettings.AddPage(&tab2devicePositions);
	m_pSettings.AddPage(&tab3sampleInformation);
	m_pSettings.AddPage(&m_miscSettings);
	if (m_pSettings.DoModal() == IDOK){
		m_pSettings.RemovePage(&tab1motorSpeed);
		m_pSettings.RemovePage(&tab2devicePositions);
		m_pSettings.RemovePage(&tab3sampleInformation);
		m_pSettings.RemovePage(&m_miscSettings);

		tab2devicePositions.RecordValues();
		tab3sampleInformation.RecordValues();

		// lookup the rpm based on the inches per sec value
 		tab1motorSpeed.m_MotorspeedRPM = tab1motorSpeed.LookUpAndConvert("rpm_lookup.rsi", tab1motorSpeed.m_MotorspeedInches);
  
 		// lookup the output analog value based on the rpm
 		tab1motorSpeed.m_MotorSpeed = tab1motorSpeed.LookUpAndConvert("analog_lookup.rsi", tab1motorSpeed.m_MotorspeedRPM);
		SaveSettings();
		
	}
	else{
		m_pSettings.RemovePage(&tab1motorSpeed);
		m_pSettings.RemovePage(&tab2devicePositions);
		m_pSettings.RemovePage(&tab3sampleInformation);
		m_pSettings.RemovePage(&m_miscSettings);
	}

	
}

void CREADTestDlg::SaveSettings()
{
	tab1motorSpeed.Save("motorspeed.ini");
	tab2devicePositions.Save("deviceposini.rdp");
	tab3sampleInformation.Save("sampleinfoini.tsi");
	m_miscSettings.Save("miscsettings.msi");
	
}

void CREADTestDlg::LoadSettings()
{
	tab1motorSpeed.Load("motorspeed.ini");
	tab2devicePositions.Load("deviceposini.rdp");
	tab3sampleInformation.Load("sampleinfoini.tsi");
	m_miscSettings.Load("miscsettings.msi");

	tab2devicePositions.m_ChargingDevice = tab2devicePositions.chargingDevice[tab2devicePositions.m_Station-1];
	tab2devicePositions.m_EraseDevice = tab2devicePositions.eraseDevice[tab2devicePositions.m_Station-1];
	tab2devicePositions.m_ExposeDevice = tab2devicePositions.exposeDevice[tab2devicePositions.m_Station-1];
	tab2devicePositions.m_VddpProbe = tab2devicePositions.vddpProbe[tab2devicePositions.m_Station-1] ;
	tab2devicePositions.m_VexpProbe = tab2devicePositions.vexpProbe[tab2devicePositions.m_Station-1] ;

	/* update comments variable with value from string array */	
	tab3sampleInformation.m_comments = tab3sampleInformation.comments [tab3sampleInformation.m_sampleNumber-1];	

	tab3sampleInformation.m_comments.TrimLeft();	// delete all white spaces on the left of the string

	tab3sampleInformation.m_comments.TrimRight();	// delete all white spaces on the right of the string

	/* update samplesID variable with value from int array */	
	tab3sampleInformation.m_sampleID = tab3sampleInformation.sampleID [tab3sampleInformation.m_sampleNumber-1];
	
	/* update startHole variable with value from int array */	
	tab3sampleInformation.m_startHole = tab3sampleInformation.startHole [tab3sampleInformation.m_sampleNumber-1];
	
	/* update endHole variable with value from int array */	
	tab3sampleInformation.m_endHole = tab3sampleInformation.endHole [tab3sampleInformation.m_sampleNumber-1];
	


}

CString CREADTestDlg::returnRootName(CString pathname)
{
	CString newFile, oldFile;
	int browse, i;
	oldFile = pathname;
	browse = oldFile.GetLength();
	newFile.Empty();
	for (i = 0; i < browse; i++){
		newFile += oldFile.GetAt(i);
		if (oldFile.GetAt(i) == '\\')
			newFile.Empty();
	}
	return newFile;

}

// before using this function remember to delete the contents of device2.out, device3.out and device4.out since the functions
// appends to the end of the file.
void CREADTestDlg::BuildOneTestSequence(SequenceInteger sequenceBinaryForm, int seq_number)
{
	FILE* device2Output; // pointer to file that shall contain the output information for device 2
	FILE* device3Output; // pointer to file that shall contain the output information for device 3
	FILE* device4Output; // pointer to file that shall contain the output information for device 4
	CString deviceOutputfile;

	float* pidc_increment; // array of pidc_increments
	int* pidc_expose;  // array of pidc expose values
	
	BOOL pidc[6] = {sequenceBinaryForm.pidc[0], sequenceBinaryForm.pidc[1], sequenceBinaryForm.pidc[2], 
		sequenceBinaryForm.pidc[3], sequenceBinaryForm.pidc[4], sequenceBinaryForm.pidc[5]}; 

	int dataArray2 [2*BELT_ENCODER_HOLES] [8] = {100};
	int dataArray3 [2*BELT_ENCODER_HOLES] [8] = {100};
	int dataArray4 [2*BELT_ENCODER_HOLES] [8] = {100};/* dataArray is an array of ints that shall contain the binary output information for the current cycle for a device
								   - each device has 8 output channels and each cycle contains BELT_ENCODER_HOLES points per channel hence a BELT_ENCODER_HOLES by 8 array */
	int i = 0, j = 0, k = 0, m = 0, n = 0; // index variables used for a variety of purposes throughout the function
	int max_cycles = 0;
	int curr_incr_cyc = 0;

	// find the maximum number of cycles among the samples
	for (i = 0; i < 12; i++){
		max_cycles =  __max(sequenceBinaryForm.sample[i].GetCycles(), max_cycles);
	}

	if(pidc[0] || pidc[1] || pidc[2] || pidc[3] || pidc[4] || pidc[5] ){
		// assign the max of pidc_cycles and max_cycles to max_cycles
		max_cycles =  __max(sequenceBinaryForm.pidc_cycles, max_cycles);
		pidc_increment = returnPidcIncrements(max_cycles);
	}

	// open files for writing the output information into
	deviceOutputfile.Format("device2_seq_%d.out", seq_number);
	device2Output = fopen(deviceOutputfile, "w");
	deviceOutputfile.Format("device3_seq_%d.out", seq_number);
	device3Output = fopen(deviceOutputfile, "w");
	deviceOutputfile.Format("device4_seq_%d.out", seq_number);
	device4Output = fopen(deviceOutputfile, "w");

	// clear dataArray of previous values
	for (m = 0; m < 2*BELT_ENCODER_HOLES; m++){
		for (n = 0; n < 8; n++){
			dataArray2 [m] [n] = 0;
			dataArray3 [m] [n] = 0;
			dataArray4 [m] [n] = 0;
		}
	}

	// fill in output for cycle 1 for devices 2, 3 and 4
	for ( k = 1; k <= max_cycles; k++){
		if (chrgDevIncr->m_cyclesBeforeIncrement > 0){
			if ((k-1)%chrgDevIncr->m_cyclesBeforeIncrement == 0)
				curr_incr_cyc++;
		}
		if(pidc[0] || pidc[1] || pidc[2] || pidc[3] || pidc[4] || pidc[5] )
			pidc_expose = returnPidcExpose((k-1), pidc_increment);

		
		// fill in the dataArray from information collected from the samples and the test sequence
		// the information shall then be used as output for device 2
		for ( i = 0; i < 12; i++){
			if (sequenceBinaryForm.sample[i].GetCycles() >= k){
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_chargewindow3; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_chargewindow3; j++){
					if (chrgDevIncr->m_grid3)
						dataArray2[j+tab2devicePositions.chargingDevice[2]] [0] =  (int) (chrgDevIncr->m_initial3 + (chrgDevIncr->m_increment3*curr_incr_cyc));
					else
						if (k%2 == 1)
							dataArray2[j+tab2devicePositions.chargingDevice[2]] [0] =  sequenceBinaryForm.sample[i].GetGrid(2);
						else
							dataArray2[j+tab2devicePositions.chargingDevice[2]] [0] =  sequenceBinaryForm.sample[i].GetGrid2(2);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_chargepinwindow3; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_chargepinwindow3; j++){
					if (k%2 == 1)
						dataArray2[j+tab2devicePositions.chargingDevice[2]] [1] =  sequenceBinaryForm.sample[i].GetPin(2);
					else
						dataArray2[j+tab2devicePositions.chargingDevice[2]] [1] =  sequenceBinaryForm.sample[i].GetPin2(2);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_chargewindow4; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_chargewindow4; j++){
					if (chrgDevIncr->m_grid4)
						dataArray2[j+tab2devicePositions.chargingDevice[3]] [2] =  (int) (chrgDevIncr->m_initial4 + (chrgDevIncr->m_increment4*curr_incr_cyc));
					else
						if (k%2 == 1)
							dataArray2[j+tab2devicePositions.chargingDevice[3]] [2] =  sequenceBinaryForm.sample[i].GetGrid(3);
						else
							dataArray2[j+tab2devicePositions.chargingDevice[3]] [2] =  sequenceBinaryForm.sample[i].GetGrid2(3);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_chargepinwindow4; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_chargepinwindow4; j++){
					if (k%2 == 1)
						dataArray2[j+tab2devicePositions.chargingDevice[3]] [3] =  sequenceBinaryForm.sample[i].GetPin(3);
					else
						dataArray2[j+tab2devicePositions.chargingDevice[3]] [3] =  sequenceBinaryForm.sample[i].GetPin2(3);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_chargewindow5; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_chargewindow5; j++){
					if (chrgDevIncr->m_grid5)
						dataArray2[j+tab2devicePositions.chargingDevice[4]] [4] =  (int) (chrgDevIncr->m_initial5 + (chrgDevIncr->m_increment5*curr_incr_cyc));
					else
						if (k%2 == 1)
							dataArray2[j+tab2devicePositions.chargingDevice[4]] [4] =  sequenceBinaryForm.sample[i].GetGrid(4);
						else
							dataArray2[j+tab2devicePositions.chargingDevice[4]] [4] =  sequenceBinaryForm.sample[i].GetGrid2(4);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_chargepinwindow5; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_chargepinwindow5; j++){
					if (k%2 == 1)
						dataArray2[j+tab2devicePositions.chargingDevice[4]] [5] =  sequenceBinaryForm.sample[i].GetPin(4);
					else
						dataArray2[j+tab2devicePositions.chargingDevice[4]] [5] =  sequenceBinaryForm.sample[i].GetPin2(4);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_chargewindow6; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_chargewindow6; j++){
					if (chrgDevIncr->m_grid6)
						dataArray2[j+tab2devicePositions.chargingDevice[5]] [6] =  (int) (chrgDevIncr->m_initial6 + (chrgDevIncr->m_increment6*curr_incr_cyc));
					else
						if (k%2 == 1)
							dataArray2[j+tab2devicePositions.chargingDevice[5]] [6] =  sequenceBinaryForm.sample[i].GetGrid(5);
						else
							dataArray2[j+tab2devicePositions.chargingDevice[5]] [6] =  sequenceBinaryForm.sample[i].GetGrid2(5);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_chargepinwindow6; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_chargepinwindow6; j++){
					if (k%2 == 1)
						dataArray2[j+tab2devicePositions.chargingDevice[5]] [7] =  sequenceBinaryForm.sample[i].GetPin(5);
					else
						dataArray2[j+tab2devicePositions.chargingDevice[5]] [7] =  sequenceBinaryForm.sample[i].GetPin2(5);
				}
			}
		}

		// fill in the dataArray from information collected from the samples and the test sequence
		// the information shall then be used as output for device 3
		for ( i = 0; i < 12; i++){
			if (sequenceBinaryForm.sample[i].GetCycles() >= k){
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_exposewindow5; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_exposewindow5; j++){
					if (k%2 == 1)
						dataArray3[j+tab2devicePositions.exposeDevice[4]] [0] = sequenceBinaryForm.sample[i].GetExpose(4);
					else
						dataArray3[j+tab2devicePositions.exposeDevice[4]] [0] = sequenceBinaryForm.sample[i].GetExpose2(4);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_erasewindow5; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_erasewindow5; j++){
					if (k%2 == 1)
						dataArray3[j+tab2devicePositions.eraseDevice[4]] [1] = sequenceBinaryForm.sample[i].GetErase(4);
					else
						dataArray3[j+tab2devicePositions.eraseDevice[4]] [1] = sequenceBinaryForm.sample[i].GetErase2(4);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_exposewindow6; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_exposewindow6; j++){
					if (k%2 == 1)
						dataArray3[j+tab2devicePositions.exposeDevice[5]] [2] = sequenceBinaryForm.sample[i].GetExpose(5);
					else
						dataArray3[j+tab2devicePositions.exposeDevice[5]] [2] = sequenceBinaryForm.sample[i].GetExpose2(5);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_erasewindow6; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_erasewindow6; j++){
					if (k%2 == 1)
						dataArray3[j+tab2devicePositions.eraseDevice[5]] [3] = sequenceBinaryForm.sample[i].GetErase(5);
					else
						dataArray3[j+tab2devicePositions.eraseDevice[5]] [3] = sequenceBinaryForm.sample[i].GetErase2(5);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_chargewindow1; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_chargewindow1; j++){
					if (chrgDevIncr->m_grid1)
						dataArray3[j+tab2devicePositions.chargingDevice[0]] [4] = (int) (chrgDevIncr->m_initial1 + (chrgDevIncr->m_increment1*curr_incr_cyc));
					else
						if (k%2 == 1)
							dataArray3[j+tab2devicePositions.chargingDevice[0]] [4] = sequenceBinaryForm.sample[i].GetGrid(0);
						else
							dataArray3[j+tab2devicePositions.chargingDevice[0]] [4] = sequenceBinaryForm.sample[i].GetGrid2(0);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_chargepinwindow1; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_chargepinwindow1; j++){
					if (k%2 == 1)
						dataArray3[j+tab2devicePositions.chargingDevice[0]] [5] = sequenceBinaryForm.sample[i].GetPin(0);
					else
						dataArray3[j+tab2devicePositions.chargingDevice[0]] [5] = sequenceBinaryForm.sample[i].GetPin2(0);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_chargewindow2; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_chargewindow2; j++){
					if (chrgDevIncr->m_grid2)
						dataArray3[j+tab2devicePositions.chargingDevice[1]] [6] = (int) (chrgDevIncr->m_initial2 + ( chrgDevIncr->m_increment2*curr_incr_cyc));
					else
						if (k%2 == 1)
							dataArray3[j+tab2devicePositions.chargingDevice[1]] [6] = sequenceBinaryForm.sample[i].GetGrid(1);
						else
							dataArray3[j+tab2devicePositions.chargingDevice[1]] [6] = sequenceBinaryForm.sample[i].GetGrid2(1);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_chargepinwindow2; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_chargepinwindow2; j++){
					if (k%2 == 1)
						dataArray3[j+tab2devicePositions.chargingDevice[1]] [7] = sequenceBinaryForm.sample[i].GetPin(1);
					else
						dataArray3[j+tab2devicePositions.chargingDevice[1]] [7] = sequenceBinaryForm.sample[i].GetPin2(1);
				}
			}
		}

		// fill in values for pidc if applicable
		for (m = 0; m < BELT_ENCODER_HOLES; m++)
			for (n = 0; n < 8; n++){
				if (pidc[4])
					dataArray3 [m+tab2devicePositions.exposeDevice[4]] [0] = pidc_expose[4];
				if (pidc[5])
					dataArray3 [m+tab2devicePositions.exposeDevice[5]] [2] = pidc_expose[5];

			}


		// fill in the dataArray from information collected from the samples and the test sequence
		// the information shall then be used as output for device 4
		for ( i = 0; i < 12; i++){
			if (sequenceBinaryForm.sample[i].GetCycles() >= k){
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_exposewindow1; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_exposewindow1; j++){
					if (k%2 == 1)
						dataArray4[j+tab2devicePositions.exposeDevice[0]] [0] = sequenceBinaryForm.sample[i].GetExpose(0);
					else
						dataArray4[j+tab2devicePositions.exposeDevice[0]] [0] = sequenceBinaryForm.sample[i].GetExpose2(0);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_erasewindow1; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_erasewindow1; j++){
					if (k%2 == 1)
						dataArray4[j+tab2devicePositions.eraseDevice[0]] [1] = sequenceBinaryForm.sample[i].GetErase(0);
					else
						dataArray4[j+tab2devicePositions.eraseDevice[0]] [1] = sequenceBinaryForm.sample[i].GetErase2(0);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_exposewindow2; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_exposewindow2; j++){
					if (k%2 == 1)
						dataArray4[j+tab2devicePositions.exposeDevice[1]] [2] = sequenceBinaryForm.sample[i].GetExpose(1);
					else
						dataArray4[j+tab2devicePositions.exposeDevice[1]] [2] = sequenceBinaryForm.sample[i].GetExpose2(1);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_erasewindow2; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_erasewindow2; j++){
					if (k%2 == 1)
						dataArray4[j+tab2devicePositions.eraseDevice[1]] [3] = sequenceBinaryForm.sample[i].GetErase(1);
					else
						dataArray4[j+tab2devicePositions.eraseDevice[1]] [3] = sequenceBinaryForm.sample[i].GetErase2(1);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_exposewindow3; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_exposewindow3; j++){
					if (k%2 == 1)
						dataArray4[j+tab2devicePositions.exposeDevice[2]] [4] = sequenceBinaryForm.sample[i].GetExpose(2);
					else
						dataArray4[j+tab2devicePositions.exposeDevice[2]] [4] = sequenceBinaryForm.sample[i].GetExpose2(2);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_erasewindow3; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_erasewindow3; j++){
					if (k%2 == 1)
						dataArray4[j+tab2devicePositions.eraseDevice[2]] [5] = sequenceBinaryForm.sample[i].GetErase(2);
					else
						dataArray4[j+tab2devicePositions.eraseDevice[2]] [5] = sequenceBinaryForm.sample[i].GetErase2(2);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_exposewindow4; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_exposewindow4; j++){
					if (k%2 == 1)
						dataArray4[j+tab2devicePositions.exposeDevice[3]] [6] = sequenceBinaryForm.sample[i].GetExpose(3);
					else
						dataArray4[j+tab2devicePositions.exposeDevice[3]] [6] = sequenceBinaryForm.sample[i].GetExpose2(3);
				}
				for(j = tab3sampleInformation.startHole[i] - m_miscSettings.m_erasewindow4; j <= tab3sampleInformation.endHole[i] + m_miscSettings.m_erasewindow4; j++){
					if (k%2 == 1)
						dataArray4[j+tab2devicePositions.eraseDevice[3]] [7] = sequenceBinaryForm.sample[i].GetErase(3);
					else
						dataArray4[j+tab2devicePositions.eraseDevice[3]] [7] = sequenceBinaryForm.sample[i].GetErase2(3);
				}
			}
		}

		// fill in values for pidc if applicable
		for (m = 0; m < BELT_ENCODER_HOLES; m++)
			for (n = 0; n < 8; n++){
				if (pidc[0])
					dataArray4 [m+tab2devicePositions.exposeDevice[0]] [0] = pidc_expose[0];
				if (pidc[1])
					dataArray4 [m+tab2devicePositions.exposeDevice[1]] [2] = pidc_expose[1];
				if (pidc[2])
					dataArray4 [m+tab2devicePositions.exposeDevice[2]] [4] = pidc_expose[2];
				if (pidc[3])
					dataArray4 [m+tab2devicePositions.exposeDevice[3]] [6] = pidc_expose[3];

			}

		// fill in the output files for device 2, 3 ,4 and 
		// shift values (past BELT_ENCODER_HOLES position) 
		// up so next cycle overlaps with current cycle
		for (i = 0; i < BELT_ENCODER_HOLES; i++){
			for (j = 0; j < 8; j++){
				fprintf(device2Output,"\t%d", dataArray2[i][j]);
				dataArray2 [i] [j] = dataArray2 [i+BELT_ENCODER_HOLES] [j];
				dataArray2 [i+BELT_ENCODER_HOLES] [j] = 0;
				fprintf(device3Output,"\t%d", dataArray3[i][j]);
				dataArray3 [i] [j] = dataArray3 [i+BELT_ENCODER_HOLES] [j];
				dataArray3 [i+BELT_ENCODER_HOLES] [j] = 0;
				fprintf(device4Output,"\t%d", dataArray4[i][j]);
				dataArray4 [i] [j] = dataArray4 [i+BELT_ENCODER_HOLES] [j];
				dataArray4 [i+BELT_ENCODER_HOLES] [j] = 0;
			}
			fprintf(device2Output,"\n");
			fprintf(device3Output,"\n");
			fprintf(device4Output,"\n");
		}

	}

	// fill in the last set of values
	for (i = 0; i < BELT_ENCODER_HOLES; i++){
		for (j = 0; j < 8; j++){
			fprintf(device2Output,"\t%d", dataArray2[i][j]);
			fprintf(device3Output,"\t%d", dataArray3[i][j]);
			fprintf(device4Output,"\t%d", dataArray4[i][j]);
		}
		fprintf(device2Output,"\n");
		fprintf(device3Output,"\n");
		fprintf(device4Output,"\n");
	}

	// an additional cycle is added to the max cycles since a full cycle for all the stations 
	// overlaps over two actual cycles - m_revolutions is the cumulative sum of all the cycles of the test sequences
	m_revolutions += max_cycles + 1;

	// close the files
	fclose(device2Output);
	fclose(device3Output);
	fclose(device4Output);
}
