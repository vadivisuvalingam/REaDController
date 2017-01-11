// GeneralSummary.cpp : implementation file
//

#include "stdafx.h"
#include "READ Test.h"
#include "READ TestDlg.h"
#include "GeneralSummary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GeneralSummary property page

IMPLEMENT_DYNCREATE(GeneralSummary, CPropertyPage)

GeneralSummary::GeneralSummary() : CPropertyPage(GeneralSummary::IDD)
{
	//{{AFX_DATA_INIT(GeneralSummary)
	m_comments = _T("");
	m_DateAndTime = _T("");
	//}}AFX_DATA_INIT
}

GeneralSummary::~GeneralSummary()
{
}

void GeneralSummary::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GeneralSummary)
	DDX_Text(pDX, IDC_COMMENTS, m_comments);
	DDX_Text(pDX, IDC_DATEANDTIME, m_DateAndTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GeneralSummary, CPropertyPage)
	//{{AFX_MSG_MAP(GeneralSummary)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GeneralSummary message handlers

// this function is called by the framework when the property page becomes active
// it overrides the default implementation CPropertyPage::OnSetActive() by adding some extra functionality
BOOL GeneralSummary::OnSetActive() 
{
	CREADTestApp* pApp = (CREADTestApp*) AfxGetApp();  // pointer to main CWinApp object
	CREADTestDlg* dlg = (CREADTestDlg*) pApp->m_pMainWnd; // pointer to main window
	// set the wizard buttons NEXT and BACK active for this page
	dlg->m_pBuildTestProperties.SetWizardButtons(PSWIZB_NEXT | PSWIZB_BACK);	
	// set the current time
	SetCurrentTime();
	// update dialog box
	UpdateData(FALSE);
	// set the page to be active
	return CPropertyPage::OnSetActive();
}

// this function is called by the framework when the property page becomes inactive
// it overrides the default implementation CPropertyPage::OnKillActive()
BOOL GeneralSummary::OnKillActive() 
{
	// update the variables associated with the dialog box
	UpdateData(TRUE);
	// deactivate the page
	return CPropertyPage::OnKillActive();
}


// this function sets the current time based on the calendar and clock on the computer 
void GeneralSummary::SetCurrentTime()
{
	CTime testTime = CTime::GetCurrentTime(); // holds the value of the calendar and clock of the computer
	char buffer [50]; // temporary character buffer

	// place in the character buffer the date and time
	sprintf(buffer, "M-D-Y: %d-%d-%d  H:M:S: %d:%d:%d", testTime.GetMonth(), testTime.GetDay(), testTime.GetYear(), testTime.GetHour(), testTime.GetMinute(), testTime.GetSecond());
	// update the variable associated with the date and time display
	m_DateAndTime =	buffer;
}

// this function saves the test summary information 
void GeneralSummary::Save(CString savefilename)
{
	FILE* outstream; // pointer to file 

	// if the filename doesn't end with .tsu extension, add it to the filename
	if (savefilename.Right(3) != "tsu")
		savefilename += ".tsu";

	// open file to write summary information into, check that it is not a null file
	if ((outstream = fopen( savefilename, "w" )) != NULL){	
		// write summary information into file - comments and date and time information
		fprintf(outstream,"%s\n%s", m_comments, m_DateAndTime);
		// close file 
		fclose(outstream);	
	}
	// if it is a null file don't save the values and alert the user
	else
		MessageBox("General Summary not saved.");

}
