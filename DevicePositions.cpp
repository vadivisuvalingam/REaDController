// DevicePositions.cpp : implementation file
//

#include "stdafx.h"
#include "direct.h"
#include "READ Test.h"
#include "READ TestDlg.h"
#include "DevicePositions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DevicePositions property page

IMPLEMENT_DYNCREATE(DevicePositions, CPropertyPage)

DevicePositions::DevicePositions() : CPropertyPage(DevicePositions::IDD)
{
	// initiallizing variables
	for (int i = 0; i < 6; i++)	{
		chargingDevice[i] = 0;
		eraseDevice[i] = 0;
		exposeDevice[i] = 0;
		vddpProbe[i] = 0;
		vexpProbe[i] = 0;
	}
	//{{AFX_DATA_INIT(DevicePositions)
	m_Station = 1;
	m_ChargingDevice = 0;
	m_EraseDevice = 0;
	m_ExposeDevice = 0;
	m_VddpProbe = 0;
	m_VexpProbe = 0;
	m_int_holes = BELT_ENCODER_HOLES;
	//}}AFX_DATA_INIT
}

DevicePositions::~DevicePositions()
{
}

void DevicePositions::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DevicePositions)
	DDX_Text(pDX, IDC_STATION, m_Station);
	DDX_Text(pDX, IDC_CHARGINGDEVICE, m_ChargingDevice);
	DDX_Text(pDX, IDC_ERASEDEVICE, m_EraseDevice);
	DDX_Text(pDX, IDC_EXPOSEDEVICE, m_ExposeDevice);
	DDX_Text(pDX, IDC_VDDPPROBE, m_VddpProbe);
	DDX_Text(pDX, IDC_VEXPPROBE, m_VexpProbe);
	DDX_Text(pDX, IDC_HOLES, m_int_holes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DevicePositions, CPropertyPage)
	//{{AFX_MSG_MAP(DevicePositions)
	ON_BN_CLICKED(IDC_DEVICEBACKWARD, OnDevicebackward)
	ON_BN_CLICKED(IDC_DEVICEFORWARD, OnDeviceforward)
	ON_BN_CLICKED(IDC_DEVICELOAD, OnDeviceload)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DevicePositions message handlers

// this function is called by the framework when the property page becomes active
// it overrides the default implementation CPropertyPage::OnSetActive() by adding some extra functionality
//DEL BOOL DevicePositions::OnSetActive() 
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
//DEL BOOL DevicePositions::OnKillActive() 
//DEL {
//DEL 	// record the values from the dialog box for the current station
//DEL 	Record();	
//DEL 	// deactivate the page
//DEL 	return CPropertyPage::OnKillActive();
//DEL }

// this function is called when the user presses the back button
// it handles the browsing and displaying of device positions information for the station before the one currently displayed
void DevicePositions::OnDevicebackward() 
{
	// check to ensure that the current station is not station 1 since if it is the user cannot browse beyond that
	if (m_Station > 1){
		// record the values from the dialog box for the current station
		Record();
		// decrement the station
		--m_Station;
		// update the dialog with values for the device positions from the current station
		UpdateDialog();
	}
	// alert the user that they are trying to bypass the limit
	else
		MessageBox("You are attempting to bypass the limit!");
	
}


// this function is called when the user presses the forward button
// it handles the browsing and displaying of device positions information for the station after the one currently displayed
void DevicePositions::OnDeviceforward() 
{
	// check to ensure that the current station is not station 6 since if it is the user cannot browse beyond that
	if (m_Station < 6){
		// record the values from the dialog box for the current station
		Record();
		// decrement the station
		++m_Station;
		// update the dialog with values for the device positions from the current station
		UpdateDialog();
	}
	// alert the user that they are trying to bypass the limit
	else
		MessageBox("You are attempting to bypass the limit!");
	
}

// this function is called when the user presses the load button
// it handles the open of a file dialog and allowing the user to chose a file to load and then loading the file 
void DevicePositions::OnDeviceload() 
{
	char currentDirectory[ _MAX_PATH ]; // character buffer to hold the directory path
	CString filename; // Name of the data file
	
	// Object to describe the file and path
	CFileDialog filetoopen(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "READ Device Position Files (*.rdp)|*.rdp|All Files (*.*)|*.*||");

	// get the current working directory - this ensure the program returns to the 
	// proper working directory after the user makes their selection of a directory path for the test files
	_getcwd( currentDirectory, _MAX_PATH );

	// Let the user specify the location of the file
	// Display the dialog to get the user to specify a destination file for the data
	if ( filetoopen.DoModal() == IDOK )
	{	
		// change back to the current working directory
		_chdir( currentDirectory );

		// Get the user to specify a file name 
		filename = filetoopen.GetPathName();
		// load the file
		Load(filename);
		
	}

	// update the dialog with values for the device positions 
	UpdateDialog();
	
}

// this function records the information from the dialog box to the current station
void DevicePositions::Record()
{
	// update the values associated with the dialog box
	UpdateData(TRUE);
	RecordValues();
}

// this function updates the dialog with information from the current station
void DevicePositions::UpdateDialog()
{
	// update the dialog with information from the station's device positions
	m_ChargingDevice = chargingDevice[m_Station-1];
	m_EraseDevice = eraseDevice[m_Station-1];
	m_ExposeDevice = exposeDevice[m_Station-1];
	m_VddpProbe = vddpProbe[m_Station-1] ;
	m_VexpProbe = vexpProbe[m_Station-1] ;
	// update the dialog box with values associated with the dialog box controls
	UpdateData(FALSE);
}

// this function saves the device positions information to a file
void DevicePositions::Save(CString savefilename)
{
	FILE* outstream;  // pointer to file
	int i; // index variable

	// if the filename doesn't end with the extension .rdp add the extension to the filename
	if (savefilename.Right(3) != "rdp")
		savefilename += ".rdp";

	// open file to write, check to see if the file is NULL
	if ((outstream = fopen(savefilename, "w")) != NULL){
		// read in first value and store it in file
		fprintf(outstream, "%d\n", m_int_holes);
		// read in the next set of lines and store it in file
		for (i = 0; i < 6; i++)
		{
			fprintf(outstream,"%d\t%d\t%d\t%d\t%d\n", vddpProbe[i], vexpProbe[i], chargingDevice[i], exposeDevice[i], eraseDevice[i]);
		}
		// close the file
		fclose(outstream);
	}
	// if the file is NULL don't save any information and alert the user
	else
		MessageBox("Device Positions file not saved.");

}

// this function loads the device positions information from a file
void DevicePositions::Load(CString loadfilename)
{
	FILE *filehandle;	// Pointer to open file
	int i;		// index variable

	// Open the file for reading, check if it is NULL
	if ((filehandle = fopen(loadfilename, "r" )) != NULL){

		// Read the number of holes per revolution
		fscanf(filehandle, "%d", &m_int_holes);

		// Begin reading the position data - station at a time - hardcoded here
		for (i = 0; i < 6; i++)
			fscanf(filehandle, "%d%d%d%d%d", &vddpProbe[i], &vexpProbe[i], &chargingDevice[i], &exposeDevice[i], &eraseDevice[i]);

		// close the file
		fclose(filehandle);
	}
	// if the file is NULL don't open the file and alert the user
	else
		MessageBox("Device Positions file not opened.");


}

void DevicePositions::RecordValues()
{
	// update the station's device positions with information from the dialog
	chargingDevice[m_Station-1] = m_ChargingDevice;
	eraseDevice[m_Station-1] = m_EraseDevice;
	exposeDevice[m_Station-1] = m_ExposeDevice;
	vddpProbe[m_Station-1] = m_VddpProbe;
	vexpProbe[m_Station-1] = m_VexpProbe;

}
