// PIDC.cpp : implementation file
//

#include "stdafx.h"
#include "READ Test.h"
#include "PIDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPIDC dialog


CPIDC::CPIDC(CWnd* pParent /*=NULL*/)
	: CDialog(CPIDC::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPIDC)
	m_cycles = 0;
	m_erase = 0.0f;
	m_expose = 0.0f;
	m_grid = 0.0f;
	m_pin = 0.0f;
	m_projectname = _T("");
	m_projectcounter = 0;
	//}}AFX_DATA_INIT
}


void CPIDC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPIDC)
	DDX_Text(pDX, IDC_PIDC_CYCLES, m_cycles);
	DDX_Text(pDX, IDC_PIDC_ERASE, m_erase);
	DDX_Text(pDX, IDC_PIDC_EXPOSE, m_expose);
	DDX_Text(pDX, IDC_PIDC_GRID, m_grid);
	DDX_Text(pDX, IDC_PIDC_PIN, m_pin);
	DDX_Text(pDX, IDC_PIDC_PROJECTNAME, m_projectname);
	DDX_Text(pDX, IDC_PIDC_PROJECTCOUNTER, m_projectcounter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPIDC, CDialog)
	//{{AFX_MSG_MAP(CPIDC)
	ON_BN_CLICKED(IDC_PIDC_BROWSE, OnPidcBrowse)
	ON_BN_CLICKED(IDC_PIDC_START, OnPidcStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPIDC message handlers

// this function is called when the user presses the browse button
void CPIDC::OnPidcBrowse() 
{

	
}

// this function is called when the user presses the start button
void CPIDC::OnPidcStart() 
{

	
}
/////////////////////////////////////////////////////////////////////////////
// CPIDC property page

IMPLEMENT_DYNCREATE(CPIDC, CPropertyPage)

CPIDC::CPIDC() : CPropertyPage(CPIDC::IDD)
{
	//{{AFX_DATA_INIT(CPIDC)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPIDC::~CPIDC()
{
}

void CPIDC::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPIDC)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPIDC, CPropertyPage)
	//{{AFX_MSG_MAP(CPIDC)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPIDC message handlers
