// JazPath.cpp : implementation file
//

#include "stdafx.h"
#include "READ Test.h"
#include "JazPath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJazPath dialog


CJazPath::CJazPath(CWnd* pParent /*=NULL*/)
	: CDialog(CJazPath::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJazPath)
	m_JazDirectory = _T("");
	m_JazProjectName = _T("");
	//}}AFX_DATA_INIT
}


void CJazPath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJazPath)
	DDX_Text(pDX, IDC_JAZDIRECTORY, m_JazDirectory);
	DDX_Text(pDX, IDC_JAZPROJECTNAME, m_JazProjectName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJazPath, CDialog)
	//{{AFX_MSG_MAP(CJazPath)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJazPath message handlers
