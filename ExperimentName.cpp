// ExperimentName.cpp : implementation file
//

#include "stdafx.h"
#include "direct.h"
#include "READ Test.h"
#include "READ TestDlg.h"
#include "ExperimentName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ExperimentName property page

IMPLEMENT_DYNCREATE(ExperimentName, CPropertyPage)

ExperimentName::ExperimentName() : CPropertyPage(ExperimentName::IDD)
{
	//{{AFX_DATA_INIT(ExperimentName)
	m_ProjectName = _T("");
	m_ProjectCounter = 0;
	//}}AFX_DATA_INIT
}

ExperimentName::~ExperimentName()
{
}

void ExperimentName::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ExperimentName)
	DDX_Text(pDX, IDC_PROJECTNAME, m_ProjectName);
	DDX_Text(pDX, IDC_PROJECTCOUNTER, m_ProjectCounter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ExperimentName, CPropertyPage)
	//{{AFX_MSG_MAP(ExperimentName)
	ON_EN_CHANGE(IDC_PROJECTNAME, OnChangeProjectname)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// this function is called by the framework when the property page becomes active
// it overrides the default implementation CPropertyPage::OnSetActive() by adding some extra functionality
BOOL ExperimentName::OnSetActive() 
{
	CREADTestApp* pApp = (CREADTestApp*) AfxGetApp(); // pointer to main CWinApp object
	CREADTestDlg* dlg = (CREADTestDlg*) pApp->m_pMainWnd; // pointer to main window
	// set the wizard buttons FINISH and BACK active for this page
	dlg->m_pBuildTestProperties.SetWizardButtons(PSWIZB_FINISH | PSWIZB_BACK);	
	// set the page to be active
	return CPropertyPage::OnSetActive();
}

// this function is called by the framework when the property page becomes inactive
// it overrides the default implementation CPropertyPage::OnKillActive()
BOOL ExperimentName::OnKillActive() 
{		
	// deactivate the page
	return CPropertyPage::OnKillActive();
}

/////////////////////////////////////////////////////////////////////////////
// ExperimentName message handlers

// this function is called when ever the project name changes on the dialog box
void ExperimentName::OnChangeProjectname() 
{
	// update variables associated with the dialog box
	UpdateData(TRUE);
	
}

// this function is called when the user presses the browse button
// it enables the user to select a directory location to place the files in
void ExperimentName::OnBrowse() 
{
	char currentDirectory[ _MAX_PATH ]; // character buffer to hold the directory path

	// Object to describe the file and path
	CFileDialog File(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Test Summary Files (*.tsu)|*.tsu|All Files (*.*)|*.*||", NULL);

	// get the current working directory - this ensure the program returns to the 
	// proper working directory after the user makes their selection of a directory path for the test files
	_getcwd( currentDirectory, _MAX_PATH );

	// Let the user specify the location of the file
	// Display the dialog to get the user to specify a destination file for the data
	if (File.DoModal() == IDOK){
		// change back to the current working directory
		_chdir( currentDirectory );

		// get the full path name and assign it as project name
		m_ProjectName = File.GetPathName();
		// update the dialog box with the current information
		UpdateData(FALSE);
	}

	
	
}
