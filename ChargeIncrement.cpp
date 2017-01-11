// ChargeIncrement.cpp : implementation file
//

#include "stdafx.h"
#include "READ Test.h"
#include "ChargeIncrement.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChargeIncrement property page

IMPLEMENT_DYNCREATE(CChargeIncrement, CPropertyPage)

CChargeIncrement::CChargeIncrement() : CPropertyPage(CChargeIncrement::IDD)
{
	//{{AFX_DATA_INIT(CChargeIncrement)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CChargeIncrement::~CChargeIncrement()
{
}

void CChargeIncrement::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChargeIncrement)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChargeIncrement, CPropertyPage)
	//{{AFX_MSG_MAP(CChargeIncrement)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChargeIncrement message handlers
