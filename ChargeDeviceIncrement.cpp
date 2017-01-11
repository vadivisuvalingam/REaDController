// ChargeDeviceIncrement.cpp : implementation file
//

#include "stdafx.h"
#include "READ Test.h"
#include "ChargeDeviceIncrement.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChargeDeviceIncrement dialog


CChargeDeviceIncrement::CChargeDeviceIncrement(CWnd* pParent /*=NULL*/)
	: CDialog(CChargeDeviceIncrement::IDD, pParent)
{
	num_bits = (float) 204.8;
	m_increment1 = 0;
	m_increment2 = 0;
	m_increment3 = 0;
	m_increment4 = 0;
	m_increment5 = 0;
	m_increment6 = 0;
	m_initial1 = 0;
	m_initial2 = 0;
	m_initial3 = 0;
	m_initial4 = 0;
	m_initial5 = 0;
	m_initial6 = 0;

	m_grid1 = FALSE;
	m_grid2 = FALSE;
	m_grid3 = FALSE;
	m_grid4 = FALSE;
	m_grid5 = FALSE;
	m_grid6 = FALSE;
	//{{AFX_DATA_INIT(CChargeDeviceIncrement)
	m_cyclesBeforeIncrement = 0;
	m_totalnumber = 0;
	m_chrg_dwn1 = FALSE;
	m_chrg_dwn2 = FALSE;
	m_chrg_dwn3 = FALSE;
	m_chrg_dwn4 = FALSE;
	m_chrg_dwn5 = FALSE;
	m_chrg_dwn6 = FALSE;
	m_chrg_up1 = FALSE;
	m_chrg_up2 = FALSE;
	m_chrg_up3 = FALSE;
	m_chrg_up4 = FALSE;
	m_chrg_up5 = FALSE;
	m_chrg_up6 = FALSE;
	m_lowerlimit = 0.0f;
	m_upperlimit = 0.0f;
	//}}AFX_DATA_INIT
}


void CChargeDeviceIncrement::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChargeDeviceIncrement)
	DDX_Text(pDX, IDC_CYCLESBEFOREINCREMENT, m_cyclesBeforeIncrement);
	DDX_Text(pDX, IDC_TOTALNUMBER, m_totalnumber);
	DDX_Check(pDX, IDC_CHARGING_GRIDDOWN1, m_chrg_dwn1);
	DDX_Check(pDX, IDC_CHARGING_GRIDDOWN2, m_chrg_dwn2);
	DDX_Check(pDX, IDC_CHARGING_GRIDDOWN3, m_chrg_dwn3);
	DDX_Check(pDX, IDC_CHARGING_GRIDDOWN4, m_chrg_dwn4);
	DDX_Check(pDX, IDC_CHARGING_GRIDDOWN5, m_chrg_dwn5);
	DDX_Check(pDX, IDC_CHARGING_GRIDDOWN6, m_chrg_dwn6);
	DDX_Check(pDX, IDC_CHARGING_GRIDUP1, m_chrg_up1);
	DDX_Check(pDX, IDC_CHARGING_GRIDUP2, m_chrg_up2);
	DDX_Check(pDX, IDC_CHARGING_GRIDUP3, m_chrg_up3);
	DDX_Check(pDX, IDC_CHARGING_GRIDUP4, m_chrg_up4);
	DDX_Check(pDX, IDC_CHARGING_GRIDUP5, m_chrg_up5);
	DDX_Check(pDX, IDC_CHARGING_GRIDUP6, m_chrg_up6);
	DDX_Text(pDX, IDC_LOWERLIMIT, m_lowerlimit);
	DDX_Text(pDX, IDC_UPPERLIMIT, m_upperlimit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChargeDeviceIncrement, CDialog)
	//{{AFX_MSG_MAP(CChargeDeviceIncrement)
	ON_BN_CLICKED(IDC_CHARGING_GRIDDOWN1, OnChargingDwn1)
	ON_BN_CLICKED(IDC_CHARGING_GRIDDOWN2, OnChargingDwn2)
	ON_BN_CLICKED(IDC_CHARGING_GRIDDOWN3, OnChargingDwn3)
	ON_BN_CLICKED(IDC_CHARGING_GRIDDOWN4, OnChargingDwn4)
	ON_BN_CLICKED(IDC_CHARGING_GRIDDOWN5, OnChargingDwn5)
	ON_BN_CLICKED(IDC_CHARGING_GRIDDOWN6, OnChargingDwn6)
	ON_BN_CLICKED(IDC_CHARGING_GRIDUP1, OnChargingUp1)
	ON_BN_CLICKED(IDC_CHARGING_GRIDUP2, OnChargingUp2)
	ON_BN_CLICKED(IDC_CHARGING_GRIDUP3, OnChargingUp3)
	ON_BN_CLICKED(IDC_CHARGING_GRIDUP4, OnChargingUp4)
	ON_BN_CLICKED(IDC_CHARGING_GRIDUP5, OnChargingUp5)
	ON_BN_CLICKED(IDC_CHARGING_GRIDUP6, OnChargingUp6)
	ON_BN_CLICKED(IDC_CANCELINCREMENTENTER, OnCancelIncrementEnter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChargeDeviceIncrement message handlers


void CChargeDeviceIncrement::OnChargingDwn1() 
{
	UpdateData(TRUE);	
	if (m_chrg_up1 == TRUE)
		m_chrg_up1 = FALSE;
	UpdateData(FALSE);

}

void CChargeDeviceIncrement::OnChargingDwn2() 
{
	UpdateData(TRUE);
	if (m_chrg_up2 == TRUE)
		m_chrg_up2 = FALSE;
	UpdateData(FALSE);
	
}

void CChargeDeviceIncrement::OnChargingDwn3() 
{
	UpdateData(TRUE);
	if (m_chrg_up3 == TRUE)
		m_chrg_up3 = FALSE;
	UpdateData(FALSE);
	
}

void CChargeDeviceIncrement::OnChargingDwn4() 
{
	UpdateData(TRUE);
	if (m_chrg_up4 == TRUE)
		m_chrg_up4 = FALSE;
	UpdateData(FALSE);
	
}

void CChargeDeviceIncrement::OnChargingDwn5() 
{
	UpdateData(TRUE);
	if (m_chrg_up5 == TRUE)
		m_chrg_up5 = FALSE;
	UpdateData(FALSE);
	
}

void CChargeDeviceIncrement::OnChargingDwn6() 
{
	UpdateData(TRUE);
	if (m_chrg_up6 == TRUE)
		m_chrg_up6 = FALSE;
	UpdateData(FALSE);
	
}

void CChargeDeviceIncrement::OnChargingUp1() 
{
	UpdateData(TRUE);	
	if (m_chrg_dwn1 == TRUE)
		m_chrg_dwn1 = FALSE;
	UpdateData(FALSE);
	
}

void CChargeDeviceIncrement::OnChargingUp2() 
{
	UpdateData(TRUE);	
	if (m_chrg_dwn2 == TRUE)
		m_chrg_dwn2 = FALSE;
	UpdateData(FALSE);
	
}

void CChargeDeviceIncrement::OnChargingUp3() 
{
	UpdateData(TRUE);	
	if (m_chrg_dwn3 == TRUE)
		m_chrg_dwn3 = FALSE;
	UpdateData(FALSE);
	
}

void CChargeDeviceIncrement::OnChargingUp4() 
{
	UpdateData(TRUE);	
	if (m_chrg_dwn4 == TRUE)
		m_chrg_dwn4 = FALSE;
	UpdateData(FALSE);
	
}

void CChargeDeviceIncrement::OnChargingUp5() 
{
	UpdateData(TRUE);	
	if (m_chrg_dwn5 == TRUE)
		m_chrg_dwn5 = FALSE;
	UpdateData(FALSE);
	
}

void CChargeDeviceIncrement::OnChargingUp6() 
{
	UpdateData(TRUE);	
	if (m_chrg_dwn6 == TRUE)
		m_chrg_dwn6 = FALSE;
	UpdateData(FALSE);
	
}

void CChargeDeviceIncrement::OnCancelIncrementEnter() 
{
	Reset();	
	CDialog::OnCancel();
}

void CChargeDeviceIncrement::OnOK() 
{
	UpdateData(TRUE);
	
	float incr = 0;
	if ((m_upperlimit > m_lowerlimit) && (m_totalnumber > 0) && (m_cyclesBeforeIncrement > 0)){
		incr = (m_upperlimit - m_lowerlimit)/m_totalnumber;
		if (m_chrg_up1 || m_chrg_dwn1){
			m_grid1 = TRUE;
			if (m_chrg_up1){
				m_increment1 = incr*num_bits;
				m_initial1 = m_lowerlimit*num_bits;
			}
			else{
				m_increment1 = -incr*num_bits;
				m_initial1 = m_upperlimit*num_bits;
			}
		}
		else 
			m_grid1 = FALSE;
		if (m_chrg_up2 || m_chrg_dwn2){
			m_grid2 = TRUE;
			if (m_chrg_up2){
				m_increment2 = incr*num_bits;
				m_initial2 = m_lowerlimit*num_bits;
			}
			else{
				m_increment2 = -incr*num_bits;
				m_initial2 = m_upperlimit*num_bits;
			}
		}
		else
			m_grid2 = FALSE;
		if (m_chrg_up3 || m_chrg_dwn3){
			m_grid3 = TRUE;
			if (m_chrg_up3){
				m_increment3 = incr*num_bits;
				m_initial3 = m_lowerlimit*num_bits;
			}
			else{
				m_increment3 = -incr*num_bits;
				m_initial3 = m_upperlimit*num_bits;
			}
		}
		else
			m_grid3 = FALSE;
		if (m_chrg_up4 || m_chrg_dwn4){
			m_grid4 = TRUE;
			if (m_chrg_up4){
				m_increment4 = incr*num_bits;
				m_initial4 = m_lowerlimit*num_bits;
			}
			else{
				m_increment4 = -incr*num_bits;
				m_initial4 = m_upperlimit*num_bits;
			}
		}
		else
			m_grid4 = FALSE;
		if (m_chrg_up5 || m_chrg_dwn5){
			m_grid5 = TRUE;
			if (m_chrg_up5){
				m_increment5 = incr*num_bits;
				m_initial5 = m_lowerlimit*num_bits;
			}
			else{
				m_increment5 = -incr*num_bits;
				m_initial5 = m_upperlimit*num_bits;
			}
		}
		else
			m_grid5 = FALSE;
		if (m_chrg_up6 || m_chrg_dwn6){
			m_grid6 = TRUE;
			if (m_chrg_up6){
				m_increment6 = incr*num_bits;
				m_initial6 = m_lowerlimit*num_bits;
			}
			else{
				m_increment6 = -incr*num_bits;
				m_initial6 = m_upperlimit*num_bits;
			}
		}
		else
			m_grid6 = FALSE;
		CDialog::OnOK();
	}
	else
		MessageBox("Either upper limit cannot be less than lower limit.\nOr Number of Increments or Cycles For Each Level\ndo not have positive values.","Increment Dialog Error", MB_ICONERROR);
}

void CChargeDeviceIncrement::Reset()
{
	m_cyclesBeforeIncrement = 0;
	m_lowerlimit = 0;
	m_totalnumber = 0;
	m_upperlimit = 0;
	m_chrg_dwn1 = FALSE;
	m_chrg_dwn2 = FALSE;
	m_chrg_dwn3 = FALSE;
	m_chrg_dwn4 = FALSE;
	m_chrg_dwn5 = FALSE;
	m_chrg_dwn6 = FALSE;
	m_chrg_up1 = FALSE;
	m_chrg_up2 = FALSE;
	m_chrg_up3 = FALSE;
	m_chrg_up4 = FALSE;
	m_chrg_up5 = FALSE;
	m_chrg_up6 = FALSE;
	m_grid1 = FALSE;
	m_grid2 = FALSE;
	m_grid3 = FALSE;
	m_grid4 = FALSE;
	m_grid5 = FALSE;
	m_grid6 = FALSE;
	m_increment1 = 0;
	m_increment2 = 0;
	m_increment3 = 0;
	m_increment4 = 0;
	m_increment5 = 0;
	m_increment6 = 0;
	m_initial1 = 0;
	m_initial2 = 0;
	m_initial3 = 0;
	m_initial4 = 0;
	m_initial5 = 0;
	m_initial6 = 0;

}

void CChargeDeviceIncrement::Save(CString filename){
	FILE* ostream;
	if ((ostream = fopen(filename,"w")) != NULL){
		fprintf(ostream, "%d\n", m_cyclesBeforeIncrement);
		fprintf(ostream, "%d\n", m_totalnumber);
		fprintf(ostream, "%f\n", m_upperlimit);
		fprintf(ostream, "%f\n", m_lowerlimit);
		fprintf(ostream, "%f %f", (m_initial1/num_bits)*1000, (m_increment1/num_bits)*1000);
		fprintf(ostream, "%f %f", (m_initial2/num_bits)*1000, (m_increment2/num_bits)*1000);
		fprintf(ostream, "%f %f", (m_initial3/num_bits)*1000, (m_increment3/num_bits)*1000);
		fprintf(ostream, "%f %f", (m_initial4/num_bits)*1000, (m_increment4/num_bits)*1000);
		fprintf(ostream, "%f %f", (m_initial5/num_bits)*1000, (m_increment5/num_bits)*1000);
		fprintf(ostream, "%f %f", (m_initial6/num_bits)*1000, (m_increment6/num_bits)*1000);
		fclose(ostream);
	}
	else{
		filename = "Unable to open " + filename;
		filename += " to save charge increment info.";
		MessageBox(filename);
	}
}

void CChargeDeviceIncrement::Load(CString filename){
	FILE* istream;
	float writevalue1, writevalue2;
	if ((istream = fopen(filename, "r")) != NULL){
		fscanf(istream, "%d", &m_cyclesBeforeIncrement);
		fscanf(istream, "%d", &m_totalnumber);
		fscanf(istream, "%f", &m_upperlimit);
		fscanf(istream, "%f", &m_lowerlimit);
		writevalue1 = (m_initial1*num_bits)/1000;
		writevalue2 = (m_increment1*num_bits)/1000;
		fscanf(istream, "%f %f", &writevalue1, &writevalue2);
		writevalue1 = (m_initial2*num_bits)/1000;
		writevalue2 = (m_increment2*num_bits)/1000;
		fscanf(istream, "%f %f", &writevalue1, &writevalue2);
		writevalue1 = (m_initial3*num_bits)/1000;
		writevalue2 = (m_increment3*num_bits)/1000;
		fscanf(istream, "%f %f", &writevalue1, &writevalue2);
		writevalue1 = (m_initial4*num_bits)/1000;
		writevalue2 = (m_increment4*num_bits)/1000;
		fscanf(istream, "%f %f", &writevalue1, &writevalue2);
		writevalue1 = (m_initial5*num_bits)/1000;
		writevalue2 = (m_increment5*num_bits)/1000;
		fscanf(istream, "%f %f", &writevalue1, &writevalue2);
		writevalue1 = (m_initial6*num_bits)/1000;
		writevalue2 = (m_increment6*num_bits)/1000;
		fscanf(istream, "%f %f", &writevalue1, &writevalue2);
		fclose(istream);
	}
	else{
		filename = "Unable to open " + filename;
		filename += " to read charge increment info.";
		MessageBox(filename);
	}
}
