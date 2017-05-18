// SerialTemp.h : main header file for the SERIALTEMP application
//

#if !defined(AFX_SERIALTEMP_H__94B80EAD_5531_4793_8E0E_D65A20EA4625__INCLUDED_)
#define AFX_SERIALTEMP_H__94B80EAD_5531_4793_8E0E_D65A20EA4625__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSerialTempApp:
// See SerialTemp.cpp for the implementation of this class
//

class CSerialTempApp : public CWinApp
{
public:
	CSerialTempApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialTempApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSerialTempApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALTEMP_H__94B80EAD_5531_4793_8E0E_D65A20EA4625__INCLUDED_)
