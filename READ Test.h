// READ Test.h : main header file for the READ TEST application
//

#if !defined(AFX_READTEST_H__D5A517A2_B63E_458E_A385_6FC96E51167F__INCLUDED_)
#define AFX_READTEST_H__D5A517A2_B63E_458E_A385_6FC96E51167F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "nidaq.h"
#include "nidaqex.h"

#define BELT_ENCODER_HOLES 400
#define BELT_LENGTH_INCHES 93.75
#define UNIPOLAR_PRECISION 4096
#define BIPOLAR_PRECISION 2048
#define GIVESPACE 7
#define ISA_BOARD 0
#define PCI_BOARD 1
#define FOUR_BITS_ON 15
#define EIGHT_BITS_ON 255
#define BITS_OFF 0

/////////////////////////////////////////////////////////////////////////////
// CREADTestApp:
// See READ Test.cpp for the implementation of this class
//

class CREADTestApp : public CWinApp
{
public:
	CREADTestApp();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CREADTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CREADTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READTEST_H__D5A517A2_B63E_458E_A385_6FC96E51167F__INCLUDED_)
