; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSerialTempDlg
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SerialTemp.h"

ClassCount=4
Class1=CSerialTempApp
Class2=CSerialTempDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_SERIALTEMP_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CustomChart
Resource4=IDR_MENU1

[CLS:CSerialTempApp]
Type=0
HeaderFile=SerialTemp.h
ImplementationFile=SerialTemp.cpp
Filter=N

[CLS:CSerialTempDlg]
Type=0
HeaderFile=SerialTempDlg.h
ImplementationFile=SerialTempDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT_TEMPRATURE

[CLS:CAboutDlg]
Type=0
HeaderFile=SerialTempDlg.h
ImplementationFile=SerialTempDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SERIALTEMP_DIALOG]
Type=1
Class=CSerialTempDlg
ControlCount=31
Control1=IDC_BTN_OPEN,button,1342242816
Control2=IDC_MSCOMM1,{648A5600-2C6E-101B-82B6-000000000014},1342242816
Control3=IDC_COMBO_PORTNAME,combobox,1344339971
Control4=IDC_STATIC,static,1342308352
Control5=IDC_COMBO_BAUDRATE,combobox,1344339971
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287
Control8=IDC_COMBO_CHECKBIT,combobox,1344339971
Control9=IDC_STATIC,static,1342308352
Control10=IDC_COMBO_DATA_BIT,combobox,1344339971
Control11=IDC_STATIC,static,1342308352
Control12=IDC_COMBO_STOPBIT,combobox,1344339971
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,button,1342177287
Control15=IDC_COMBO_LOW_PORTNAME,combobox,1344339971
Control16=IDC_STATIC,static,1342308352
Control17=IDC_COMBO_LOW_BAUD,combobox,1344339971
Control18=IDC_STATIC,static,1342308352
Control19=IDC_COMBO_LOW_CHECK,combobox,1344339971
Control20=IDC_STATIC,static,1342308352
Control21=IDC_COMBO_LOW_DATA_BIT,combobox,1344339971
Control22=IDC_COMBO_LOW_STOPBIT,combobox,1344339971
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_BTN_TEMP_SENDER,button,1342242816
Control26=IDC_MSCOMM2,{648A5600-2C6E-101B-82B6-000000000014},1342242816
Control27=IDC_STATIC,button,1342177287
Control28=IDC_BUTTON_FILE,button,1342242816
Control29=IDC_EDIT_TEMPRATURE,edit,1350631552
Control30=IDC_STATIC,static,1342308352
Control31=IDC_CUSTOM1,CustomChart,1342242816

[MNU:IDR_MENU1]
Type=1
Class=?
CommandCount=0

[CLS:CustomChart]
Type=0
HeaderFile=CustomChart.h
ImplementationFile=CustomChart.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC

