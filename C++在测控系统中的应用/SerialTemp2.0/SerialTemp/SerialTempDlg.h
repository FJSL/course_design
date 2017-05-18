// SerialTempDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
#include "Afxtempl.h"//链表类的声明
#include "CustomChart.h"
//}}AFX_INCLUDES


/*************************************userDef***************************************/

// 定义温度范围
#define MAX_TEMPERATURE 60
#define MIN_TEMPERATURE 50




#if !defined(AFX_SERIALTEMPDLG_H__5364CF3C_1A05_45A9_84BD_149CAF03A904__INCLUDED_)
#define AFX_SERIALTEMPDLG_H__5364CF3C_1A05_45A9_84BD_149CAF03A904__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSerialTempDlg dialog

class CSerialTempDlg : public CDialog
{
// Construction
public:
	int getRandomTemprature();
	void InitSerialPort();
	void InitCombox();
	void DealTemprature(CString str);
	CSerialTempDlg(CWnd* pParent = NULL);	// standard constructor
	/**********************************User***********************************/

	CStatusBar m_bar;

	CustomChart chart; // 绘图

	/**********************************serial********************************/


	/***********************************temp*********************************/
	int temprature;
	CString	m_str;  // 串口接收数据的缓冲
	CList<CPoint, CPoint&> list; 
	
	bool tempFlag;
	// Dialog Data
	//{{AFX_DATA(CSerialTempDlg)
	enum { IDD = IDD_SERIALTEMP_DIALOG };
	CComboBox	mLowPortName;
	CComboBox	mLowStopBit;
	CComboBox	mLowDataBit;
	CComboBox	mLowCheck;
	CComboBox	mLowBaud;
	CComboBox	mDataBit;
	CComboBox	mStopBit;
	CComboBox	mCheckBit;
	CComboBox	mComboPortName; 
	CComboBox	mComboBaud;
	CButton	mBtnTempSender;   //下位机发送按钮
	CButton	mBtnOpen;
	CMSComm	mSerial; // 上位机串口
	CMSComm	mLowSerial; // 下位机串口

	CString	m_strPortName;
	CString	mStrTem;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialTempDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSerialTempDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSerialSw();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDropdownComboPortName();
	afx_msg void OnBtnTempSender();
	afx_msg void OnOnCommMscomm1();
	afx_msg void OnDropdownComboLowPortname();
	afx_msg void OnSelendOkComboBaudrate();
	afx_msg void OnSelendOkComboLowPortName();
	afx_msg void OnSelendOkComboLowBaudRate();
	afx_msg void OnSelendOkComboLowCheck();
	afx_msg void OnSelendOkComboLowDataBit();
	afx_msg void OnSelendOkComboLowStopbit();
	afx_msg void OnSelendokComboCheckbit();
	afx_msg void OnSelendOkComboDataBit();
	afx_msg void OnSelendOkComboStopbit();
	afx_msg void OnSelendOkComboPortName();
	afx_msg void OnButtonFile();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALTEMPDLG_H__5364CF3C_1A05_45A9_84BD_149CAF03A904__INCLUDED_)
