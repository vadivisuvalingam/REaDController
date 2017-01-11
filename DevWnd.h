#if !defined(AFX_DEVWND_H__B109C450_EFD7_11D6_9109_91A7B8844A91__INCLUDED_)
#define AFX_DEVWND_H__B109C450_EFD7_11D6_9109_91A7B8844A91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DevWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDevWnd dialog

class CDevWnd : public CPropertyPage
{
	DECLARE_DYNCREATE(CDevWnd)

// Construction
public:
	void Save(CString filename);
	void Load(CString filename);
	CDevWnd();
	~CDevWnd();

// Dialog Data
	//{{AFX_DATA(CDevWnd)
	enum { IDD = IDD_MISCSETTINGS };
	BOOL	m_bufferedmode;
	int		m_chargewindow1;
	int		m_chargewindow2;
	int		m_chargewindow3;
	int		m_chargewindow4;
	int		m_chargewindow5;
	int		m_chargewindow6;
	int		m_erasewindow1;
	int		m_erasewindow2;
	int		m_erasewindow3;
	int		m_erasewindow4;
	int		m_erasewindow5;
	int		m_erasewindow6;
	int		m_exposewindow1;
	int		m_exposewindow2;
	int		m_exposewindow3;
	int		m_exposewindow4;
	int		m_exposewindow5;
	int		m_exposewindow6;
	BOOL	m_nonbuffereddynamicmode;
	BOOL	m_nonbufferedmode;
	int		m_chargepinwindow1;
	int		m_chargepinwindow2;
	int		m_chargepinwindow3;
	int		m_chargepinwindow4;
	int		m_chargepinwindow5;
	int		m_chargepinwindow6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDevWnd)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDevWnd)
	afx_msg void OnBufferedmode();
	afx_msg void OnNonbufferedmode();
	afx_msg void OnNonbuffereddynamicmode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVWND_H__B109C450_EFD7_11D6_9109_91A7B8844A91__INCLUDED_)
