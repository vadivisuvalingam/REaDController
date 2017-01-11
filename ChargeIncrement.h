#if !defined(AFX_CHARGEINCREMENT_H__C6C59571_DC35_11D6_90F7_D3875EBF9691__INCLUDED_)
#define AFX_CHARGEINCREMENT_H__C6C59571_DC35_11D6_90F7_D3875EBF9691__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChargeIncrement.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChargeIncrement dialog

class CChargeIncrement : public CPropertyPage
{
	DECLARE_DYNCREATE(CChargeIncrement)

// Construction
public:
	CChargeIncrement();
	~CChargeIncrement();

// Dialog Data
	//{{AFX_DATA(CChargeIncrement)
	enum { IDD = IDD_CHARGEINCREMENT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CChargeIncrement)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CChargeIncrement)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARGEINCREMENT_H__C6C59571_DC35_11D6_90F7_D3875EBF9691__INCLUDED_)
