// Device.h: interface for the CDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICE_H__79DD4CD1_F2FB_11D6_910D_9107A6264391__INCLUDED_)
#define AFX_DEVICE_H__79DD4CD1_F2FB_11D6_910D_9107A6264391__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDevice  
{
public:
	CDevice();
	virtual ~CDevice();

private:
	char* lookupTable;
	int window;
	int channel;
	int board;
	int position;
	int type;

};

#endif // !defined(AFX_DEVICE_H__79DD4CD1_F2FB_11D6_910D_9107A6264391__INCLUDED_)
