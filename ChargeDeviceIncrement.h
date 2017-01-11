#if !defined(AFX_CHARGEDEVICEINCREMENT_H__BC9E4540_DCEE_11D6_90F8_A55C52FE9791__INCLUDED_)
#define AFX_CHARGEDEVICEINCREMENT_H__BC9E4540_DCEE_11D6_90F8_A55C52FE9791__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChargeDeviceIncrement.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChargeDeviceIncrement dialog

class CChargeDeviceIncrement : public CDialog
{
// Construction
public:
	float num_bits;
	void Load(CString);
	void Save(CString);
	CChargeDeviceIncrement(CWnd* pParent = NULL);   // standard constructor
	bool m_grid1;
	bool m_grid2;
	bool m_grid3;
	bool m_grid4;
	bool m_grid5;
	bool m_grid6;
	float m_increment1;
	float m_increment2;
	float m_increment3;
	float m_increment4;
	float m_increment5;
	float m_increment6;
	float m_initial1;
	float m_initial2;
	float m_initial3;
	float m_initial4;
	float m_initial5;
	float m_initial6;

// Dialog Data
	//{{AFX_DATA(CChargeDeviceIncrement)
	enum { IDD = IDD_CHARGEINCREMENT };
	int		m_cyclesBeforeIncrement;
	int		m_totalnumber;
	BOOL	m_chrg_dwn1;
	BOOL	m_chrg_dwn2;
	BOOL	m_chrg_dwn3;
	BOOL	m_chrg_dwn4;
	BOOL	m_chrg_dwn5;
	BOOL	m_chrg_dwn6;
	BOOL	m_chrg_up1;
	BOOL	m_chrg_up2;
	BOOL	m_chrg_up3;
	BOOL	m_chrg_up4;
	BOOL	m_chrg_up5;
	BOOL	m_chrg_up6;
	float	m_lowerlimit;
	float	m_upperlimit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChargeDeviceIncrement)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChargeDeviceIncrement)
	afx_msg void OnChargingDwn1();
	afx_msg void OnChargingDwn2();
	afx_msg void OnChargingDwn3();
	afx_msg void OnChargingDwn4();
	afx_msg void OnChargingDwn5();
	afx_msg void OnChargingDwn6();
	afx_msg void OnChargingUp1();
	afx_msg void OnChargingUp2();
	afx_msg void OnChargingUp3();
	afx_msg void OnChargingUp4();
	afx_msg void OnChargingUp5();
	afx_msg void OnChargingUp6();
	afx_msg void OnCancelIncrementEnter();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Reset();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARGEDEVICEINCREMENT_H__BC9E4540_DCEE_11D6_90F8_A55C52FE9791__INCLUDED_)
