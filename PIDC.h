#if !defined(AFX_PIDC_H__2BE83FB6_3FB7_4AE5_AD5D_A9A95DBFC96F__INCLUDED_)
#define AFX_PIDC_H__2BE83FB6_3FB7_4AE5_AD5D_A9A95DBFC96F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PIDC.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPIDC dialog

class CPIDC : public CPropertyPage
{
	DECLARE_DYNCREATE(CPIDC)

// Construction
public:
	CPIDC();
	~CPIDC();

// Dialog Data
	//{{AFX_DATA(CPIDC)
	enum { IDD = IDD_PIDC };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPIDC)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPIDC)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIDC_H__2BE83FB6_3FB7_4AE5_AD5D_A9A95DBFC96F__INCLUDED_)
