#if !defined(AFX_TESTSEQUENCE_H__B30E4E6D_F4ED_4F3A_84DD_763994581FAA__INCLUDED_)
#define AFX_TESTSEQUENCE_H__B30E4E6D_F4ED_4F3A_84DD_763994581FAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestSequence.h : header file
//
#include "ChargeDeviceIncrement.h"
#include "SamplesGridFloat.h"
#include "SamplesGridInteger.h"
#include "SequenceFloat.h"
#include "SequenceInteger.h"
#include <afxtempl.h>
#include <afxcoll.h>


#define NUMBEROFSAMPLES 12
#define NUMBEROFGRIDS 6

/////////////////////////////////////////////////////////////////////////////
// TestSequence dialog

class TestSequence : public CPropertyPage
{
	DECLARE_DYNCREATE(TestSequence)

// Construction
public:
	void readgridvalues();
	CString gridfilenames[NUMBEROFSAMPLES][NUMBEROFGRIDS];
	bool list1on;
	bool list2on;
	bool list3on;
	bool list4on;
	bool list5on;
	bool list6on;
	void CallAllIncrementCheck();
	CChargeDeviceIncrement* chrgDevIncr;

	char* cleanstring(char* bufferptr);
	void ShowHide(int* showcntl, int num_show, int* hidecntl, int num_hide);
	void Addsequence();
	void ConvertFloatToBinary();
	SamplesGridFloat copyGrid;
	CList <SequenceInteger, SequenceInteger> sequenceBinaryList;
	CList <SequenceFloat, SequenceFloat> sequenceFloatList;
	SequenceInteger currentSequenceBinaryForm;
	SequenceFloat currentSequence;
	int numberOfSequences;
	int LightDevice_LookUpAndConvert(CString lookupfile, float m_lookup);
	int ChargingDevice_LookUpAndConvert(CString lookupfile, float m_lookup);
	CString array_filenames [24];
	void Load (CString loadfilename);
	void Save(CString savefilename);
	void Update();
	void Record();
	TestSequence();
	~TestSequence();

// Dialog Data
	//{{AFX_DATA(TestSequence)
	enum { IDD = IDD_TESTSEQUENCE };
	CListBox	m_grid4_list;
	CListBox	m_grid6_list;
	CListBox	m_grid5_list;
	CListBox	m_grid3_list;
	CListBox	m_grid2_list;
	CListBox	m_grid1_list;
	CListBox	m_SequenceList;
	int		m_cycles;
	float	m_s1_erase;
	float	m_s1_expose;
	float	m_s1_grid;
	float	m_s1_pin;
	float	m_s2_erase;
	float	m_s2_expose;
	float	m_s2_grid;
	float	m_s2_pin;
	float	m_s3_erase;
	float	m_s3_expose;
	float	m_s3_grid;
	float	m_s3_pin;
	float	m_s4_erase;
	float	m_s4_expose;
	float	m_s4_grid;
	float	m_s4_pin;
	float	m_s5_erase;
	float	m_s5_expose;
	float	m_s5_grid;
	float	m_s5_pin;
	float	m_s6_erase;
	float	m_s6_expose;
	float	m_s6_grid;
	float	m_s6_pin;
	float	m_s1_erase2;
	float	m_s1_expose2;
	float	m_s1_grid2;
	float	m_s1_pin2;
	float	m_s2_erase2;
	float	m_s2_expose2;
	float	m_s2_grid2;
	float	m_s2_pin2;
	float	m_s3_erase2;
	float	m_s3_expose2;
	float	m_s3_grid2;
	float	m_s3_pin2;
	float	m_s4_erase2;
	float	m_s4_expose2;
	float	m_s4_grid2;
	float	m_s4_pin2;
	float	m_s5_erase2;
	float	m_s5_expose2;
	float	m_s5_grid2;
	float	m_s5_pin2;
	float	m_s6_erase2;
	float	m_s6_expose2;
	float	m_s6_grid2;
	float	m_s6_pin2;
	int		m_sectionAcycles;
	int		m_sectionBcycles;
	int		m_sampleNumber;
	BOOL	m_pidc1;
	BOOL	m_pidc2;
	BOOL	m_pidc3;
	BOOL	m_pidc4;
	BOOL	m_pidc5;
	BOOL	m_pidc6;
	int		m_pidc_cycles;
	BOOL	m_popupoff;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(TestSequence)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(TestSequence)
	afx_msg void OnBack();
	afx_msg void OnForward();
	afx_msg void OnLoad();
	afx_msg void OnAddsequence();
	afx_msg void OnRemovesequence();
	afx_msg void OnDblclkSequencelist();
	afx_msg void OnModifysequence();
	afx_msg void OnResetcurrentsequence();
	afx_msg void OnCopyvalues();
	afx_msg void OnPastevalues();
	afx_msg void OnPidcCheck1();
	afx_msg void OnPidcCheck2();
	afx_msg void OnPidcCheck3();
	afx_msg void OnPidcCheck4();
	afx_msg void OnPidcCheck5();
	afx_msg void OnPidcCheck6();
	afx_msg void OnRepeatsequence();
	afx_msg void OnSetincrements();
	afx_msg void OnSetfocusS1Grid();
	afx_msg void OnKillfocusS1Grid();
	afx_msg void OnSetfocusS2Grid();
	afx_msg void OnKillfocusS2Grid();
	afx_msg void OnSetfocusS3Grid();
	afx_msg void OnKillfocusS3Grid();
	afx_msg void OnSetfocusS4Grid();
	afx_msg void OnKillfocusS4Grid();
	afx_msg void OnSetfocusS5Grid();
	afx_msg void OnKillfocusS5Grid();
	afx_msg void OnSetfocusS6Grid();
	afx_msg void OnKillfocusS6Grid();
	afx_msg void OnPopupcheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	float exposeValues[6];
	float* getHighestExposeValue();
	void CallAllPidcCheck();

};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSEQUENCE_H__B30E4E6D_F4ED_4F3A_84DD_763994581FAA__INCLUDED_)
