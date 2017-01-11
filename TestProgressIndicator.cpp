// TestProgressIndicator.cpp : implementation file
//

#include "stdafx.h"
#include "READ Test.h"
#include "TestProgressIndicator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestProgressIndicator dialog


CTestProgressIndicator::CTestProgressIndicator(CWnd* pParent /*=NULL*/)
	: CDialog(CTestProgressIndicator::IDD, pParent)
{
	m_pParent = pParent;
	m_nID = CTestProgressIndicator::IDD;
	m_CancelRecordingData = FALSE;
	//{{AFX_DATA_INIT(CTestProgressIndicator)
	//}}AFX_DATA_INIT
}


void CTestProgressIndicator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestProgressIndicator)
	DDX_Control(pDX, IDC_ZEROPOSITONCOUNTER, m_ZeroPositionCounter);
	DDX_Control(pDX, IDC_HOLECOUNTER, m_HoleCounter);
	DDX_Control(pDX, IDC_TIMELEFT, m_TimeLeft);
	DDX_Control(pDX, IDC_PROGRESSOFCYCLES, m_ProgressOfCycles);
	DDX_Control(pDX, IDC_CYCLESLEFT, m_CyclesLeft);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestProgressIndicator, CDialog)
	//{{AFX_MSG_MAP(CTestProgressIndicator)
	ON_BN_CLICKED(IDC_CANCELRECORDINGDATA, OnCancelrecordingdata)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestProgressIndicator message handlers

// this function creates the modeless dialog box
BOOL CTestProgressIndicator::Create() 
{
	// create a dialog with the calling window as parent and the IDD_PROGRESS resource as 
	// the dialog window
	return CDialog::Create(m_nID, m_pParent);
}

// this function is called after the dialog window has been destroyed
void CTestProgressIndicator::PostNcDestroy() 
{
	// delete the class instance from memory
	delete this;
}

// the function set a flag and is called when the user presses the cancel button
void CTestProgressIndicator::OnCancelrecordingdata() 
{
	// sets the flag to true to indicate that user wishes to cancel the current operation
	m_CancelRecordingData = TRUE;
	
}

// the function ensures that the modaless dialog box receives messages even when
// it is not active directly - e.g. this allows the user to press cancel even though the program is running the test
void CTestProgressIndicator::PumpMessages()
{
    // Must call Create() before using the dialog
    ASSERT(m_hWnd!=NULL);

    MSG msg; // message 

    // Handle dialog messages
	// while there are messages on the message queue process them
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){ 
		// if the message is for this dialog and has not been processed - process them
		if(!IsDialogMessage(&msg)){  
			// translate the message
			TranslateMessage(&msg);
			// dispatch the message to the appropriate procedure
			DispatchMessage(&msg);  
		}
    }
}

// this message checks the flag the ensure the cancel button has been pressed or not
BOOL CTestProgressIndicator::CheckCancelButton()
{
    // process all pending messages
    PumpMessages();

	// assign the flag to the return value
    BOOL bResult = m_CancelRecordingData;
    
	// return the value of the flag
    return bResult;
}

