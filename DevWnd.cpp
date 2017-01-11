// DevWnd.cpp : implementation file
//

#include "stdafx.h"
#include "READ Test.h"
#include "DevWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDevWnd property page

IMPLEMENT_DYNCREATE(CDevWnd, CPropertyPage)

CDevWnd::CDevWnd() : CPropertyPage(CDevWnd::IDD)
{
	//{{AFX_DATA_INIT(CDevWnd)
	m_bufferedmode = FALSE;
	m_chargewindow1 = 0;
	m_chargewindow2 = 0;
	m_chargewindow3 = 0;
	m_chargewindow4 = 0;
	m_chargewindow5 = 0;
	m_chargewindow6 = 0;
	m_erasewindow1 = 0;
	m_erasewindow2 = 0;
	m_erasewindow3 = 0;
	m_erasewindow4 = 0;
	m_erasewindow5 = 0;
	m_erasewindow6 = 0;
	m_exposewindow1 = 0;
	m_exposewindow2 = 0;
	m_exposewindow3 = 0;
	m_exposewindow4 = 0;
	m_exposewindow5 = 0;
	m_exposewindow6 = 0;
	m_nonbuffereddynamicmode = TRUE;
	m_nonbufferedmode = FALSE;
	m_chargepinwindow1 = 0;
	m_chargepinwindow2 = 0;
	m_chargepinwindow3 = 0;
	m_chargepinwindow4 = 0;
	m_chargepinwindow5 = 0;
	m_chargepinwindow6 = 0;
	//}}AFX_DATA_INIT
}

CDevWnd::~CDevWnd()
{
}

void CDevWnd::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDevWnd)
	DDX_Check(pDX, IDC_BUFFEREDMODE, m_bufferedmode);
	DDX_Text(pDX, IDC_CHARGEWINDOW1, m_chargewindow1);
	DDX_Text(pDX, IDC_CHARGEWINDOW2, m_chargewindow2);
	DDX_Text(pDX, IDC_CHARGEWINDOW3, m_chargewindow3);
	DDX_Text(pDX, IDC_CHARGEWINDOW4, m_chargewindow4);
	DDX_Text(pDX, IDC_CHARGEWINDOW5, m_chargewindow5);
	DDX_Text(pDX, IDC_CHARGEWINDOW6, m_chargewindow6);
	DDX_Text(pDX, IDC_ERASEWINDOW1, m_erasewindow1);
	DDX_Text(pDX, IDC_ERASEWINDOW2, m_erasewindow2);
	DDX_Text(pDX, IDC_ERASEWINDOW3, m_erasewindow3);
	DDX_Text(pDX, IDC_ERASEWINDOW4, m_erasewindow4);
	DDX_Text(pDX, IDC_ERASEWINDOW5, m_erasewindow5);
	DDX_Text(pDX, IDC_ERASEWINDOW6, m_erasewindow6);
	DDX_Text(pDX, IDC_EXPOSEWINDOW1, m_exposewindow1);
	DDX_Text(pDX, IDC_EXPOSEWINDOW2, m_exposewindow2);
	DDX_Text(pDX, IDC_EXPOSEWINDOW3, m_exposewindow3);
	DDX_Text(pDX, IDC_EXPOSEWINDOW4, m_exposewindow4);
	DDX_Text(pDX, IDC_EXPOSEWINDOW5, m_exposewindow5);
	DDX_Text(pDX, IDC_EXPOSEWINDOW6, m_exposewindow6);
	DDX_Check(pDX, IDC_NONBUFFEREDDYNAMICMODE, m_nonbuffereddynamicmode);
	DDX_Check(pDX, IDC_NONBUFFEREDMODE, m_nonbufferedmode);
	DDX_Text(pDX, IDC_CHARGEPINWINDOW1, m_chargepinwindow1);
	DDX_Text(pDX, IDC_CHARGEPINWINDOW2, m_chargepinwindow2);
	DDX_Text(pDX, IDC_CHARGEPINWINDOW3, m_chargepinwindow3);
	DDX_Text(pDX, IDC_CHARGEPINWINDOW4, m_chargepinwindow4);
	DDX_Text(pDX, IDC_CHARGEPINWINDOW5, m_chargepinwindow5);
	DDX_Text(pDX, IDC_CHARGEPINWINDOW6, m_chargepinwindow6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDevWnd, CPropertyPage)
	//{{AFX_MSG_MAP(CDevWnd)
	ON_BN_CLICKED(IDC_BUFFEREDMODE, OnBufferedmode)
	ON_BN_CLICKED(IDC_NONBUFFEREDMODE, OnNonbufferedmode)
	ON_BN_CLICKED(IDC_NONBUFFEREDDYNAMICMODE, OnNonbuffereddynamicmode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDevWnd message handlers

void CDevWnd::OnBufferedmode() 
{
	UpdateData(TRUE);
	if (m_bufferedmode){
		m_nonbufferedmode = FALSE;
		m_nonbuffereddynamicmode = FALSE;
	}
	else
		m_bufferedmode = TRUE;
	UpdateData(FALSE);
	
}

void CDevWnd::OnNonbufferedmode() 
{
	UpdateData(TRUE);
	if (m_nonbufferedmode){
		m_bufferedmode = FALSE;
		m_nonbuffereddynamicmode = FALSE;
	}
	else
		m_nonbufferedmode = TRUE;
	UpdateData(FALSE);
	
}

void CDevWnd::OnNonbuffereddynamicmode() 
{
	UpdateData(TRUE);
	if (m_nonbuffereddynamicmode){
		m_nonbufferedmode = FALSE;
		m_bufferedmode = FALSE;
	}
	else
		m_nonbuffereddynamicmode = TRUE;
	UpdateData(FALSE);
	
}



void CDevWnd::Load(CString filename)
{
	FILE* filestream;
	int readvalue = 0;
	if ((filestream = fopen(filename,"r")) != NULL){
		fscanf(filestream,"%d",&readvalue); 
		if (readvalue) m_bufferedmode = TRUE; else m_bufferedmode = FALSE;
		fscanf(filestream,"%d",&readvalue); 
		if (readvalue) m_nonbufferedmode = TRUE; else m_nonbufferedmode = FALSE;
		fscanf(filestream,"%d",&readvalue); 
		if (readvalue) m_nonbuffereddynamicmode = TRUE; else m_nonbuffereddynamicmode = FALSE;
		fscanf(filestream,"%d",&readvalue); m_chargewindow1 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_chargewindow2 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_chargewindow3 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_chargewindow4 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_chargewindow5 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_chargewindow6 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_chargepinwindow1 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_chargepinwindow2 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_chargepinwindow3 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_chargepinwindow4 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_chargepinwindow5 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_chargepinwindow6 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_erasewindow1 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_erasewindow2 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_erasewindow3 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_erasewindow4 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_erasewindow5 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_erasewindow6 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_exposewindow1 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_exposewindow2 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_exposewindow3 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_exposewindow4 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_exposewindow5 = readvalue;
		fscanf(filestream,"%d",&readvalue); m_exposewindow6 = readvalue;
		fclose(filestream);
	}
	else
		MessageBox("Unable to load miscellaneous settings file.");
	

}

void CDevWnd::Save(CString filename)
{
	FILE* filestream;
	int writevalue = 0;
	if ((filestream = fopen(filename,"w")) != NULL){
		if (m_bufferedmode) writevalue = 1; else writevalue = 0;
		fprintf(filestream,"%d\n",writevalue); 
		if (m_nonbufferedmode) writevalue = 1; else writevalue = 0;
		fprintf(filestream,"%d\n",writevalue); 
		if (m_nonbuffereddynamicmode) writevalue = 1; else writevalue = 0;
		fprintf(filestream,"%d\n",writevalue); 
		writevalue = m_chargewindow1; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_chargewindow2; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_chargewindow3; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_chargewindow4; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_chargewindow5; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_chargewindow6; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_chargepinwindow1; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_chargepinwindow2; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_chargepinwindow3; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_chargepinwindow4; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_chargepinwindow5; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_chargepinwindow6; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_erasewindow1; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_erasewindow2; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_erasewindow3; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_erasewindow4; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_erasewindow5; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_erasewindow6; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_exposewindow1; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_exposewindow2; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_exposewindow3; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_exposewindow4; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_exposewindow5; fprintf(filestream,"%d\n",writevalue);  
		writevalue = m_exposewindow6; fprintf(filestream,"%d\n",writevalue);  
		fclose(filestream);
	}
	else
		MessageBox("Unable to load miscellaneous settings file.");
	

}
