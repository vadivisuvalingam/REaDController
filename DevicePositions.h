#if !defined(AFX_DEVICEPOSITIONS_H__A8E5065F_98BC_4DE5_8793_8334A7F4E307__INCLUDED_)
#define AFX_DEVICEPOSITIONS_H__A8E5065F_98BC_4DE5_8793_8334A7F4E307__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DevicePositions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DevicePositions dialog

class DevicePositions : public CPropertyPage
{
	DECLARE_DYNCREATE(DevicePositions)

// Construction
public:
	void RecordValues();
	void Load(CString loadfilename);
	void Save(CString savefilename);
	void UpdateDialog();
	void Record();
	int chargingDevice[6];
	int eraseDevice[6];
	int exposeDevice[6];
	int vddpProbe[6];
	int vexpProbe[6];
	DevicePositions();
	~DevicePositions();

// Dialog Data
	//{{AFX_DATA(DevicePositions)
	enum { IDD = IDD_DEVICEPOSITIONS };
	int		m_Station;
	int		m_ChargingDevice;
	int		m_EraseDevice;
	int		m_ExposeDevice;
	int		m_VddpProbe;
	int		m_VexpProbe;
	int		m_int_holes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(DevicePositions)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(DevicePositions)
	afx_msg void OnDevicebackward();
	afx_msg void OnDeviceforward();
	afx_msg void OnDeviceload();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICEPOSITIONS_H__A8E5065F_98BC_4DE5_8793_8334A7F4E307__INCLUDED_)
