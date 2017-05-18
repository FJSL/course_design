// SerialTempDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SerialTemp.h"
#include "SerialTempDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*********************************״̬��***************************************/
static UINT BASED_CODE indicators[]=
{
    ID_INDICATOR_NAME,
    ID_INDICATOR_NUMBER,
    ID_INDICATOR_MAJOR
};
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialTempDlg dialog

CSerialTempDlg::CSerialTempDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSerialTempDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSerialTempDlg)
	m_str = _T("");
	m_strPortName = _T("");
	mStrTem = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}




void CSerialTempDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSerialTempDlg)
	DDX_Control(pDX, IDC_COMBO_LOW_PORTNAME, mLowPortName);
	DDX_Control(pDX, IDC_COMBO_LOW_STOPBIT, mLowStopBit);
	DDX_Control(pDX, IDC_COMBO_LOW_DATA_BIT, mLowDataBit);
	DDX_Control(pDX, IDC_COMBO_LOW_CHECK, mLowCheck);
	DDX_Control(pDX, IDC_COMBO_LOW_BAUD, mLowBaud);
	DDX_Control(pDX, IDC_COMBO_DATA_BIT, mDataBit);
	DDX_Control(pDX, IDC_COMBO_STOPBIT, mStopBit);
	DDX_Control(pDX, IDC_COMBO_CHECKBIT, mCheckBit);
	DDX_Control(pDX, IDC_COMBO_PORTNAME, mComboPortName);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, mComboBaud);
	DDX_Control(pDX, IDC_BTN_TEMP_SENDER, mBtnTempSender);
	DDX_Control(pDX, IDC_BTN_OPEN, mBtnOpen);
	DDX_Control(pDX, IDC_MSCOMM1, mSerial);
	DDX_Control(pDX, IDC_MSCOMM2, mLowSerial);
	DDX_Control(pDX, IDC_CUSTOM1, chart);
	DDX_CBString(pDX, IDC_COMBO_PORTNAME, m_strPortName);
	DDX_Text(pDX, IDC_EDIT_TEMPRATURE, mStrTem);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSerialTempDlg, CDialog)
	//{{AFX_MSG_MAP(CSerialTempDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, OnSerialSw)
	ON_WM_TIMER()
	ON_CBN_DROPDOWN(IDC_COMBO_PORTNAME, OnDropdownComboPortName)
	ON_BN_CLICKED(IDC_BTN_TEMP_SENDER, OnBtnTempSender)
	ON_CBN_DROPDOWN(IDC_COMBO_LOW_PORTNAME, OnDropdownComboLowPortname)
	ON_CBN_SELENDOK(IDC_COMBO_BAUDRATE, OnSelendOkComboBaudrate)
	ON_CBN_SELENDOK(IDC_COMBO_LOW_PORTNAME, OnSelendOkComboLowPortName)
	ON_CBN_SELENDOK(IDC_COMBO_LOW_BAUD, OnSelendOkComboLowBaudRate)
	ON_CBN_SELENDOK(IDC_COMBO_LOW_CHECK, OnSelendOkComboLowCheck)
	ON_CBN_SELENDOK(IDC_COMBO_LOW_DATA_BIT, OnSelendOkComboLowDataBit)
	ON_CBN_SELENDOK(IDC_COMBO_LOW_STOPBIT, OnSelendOkComboLowStopbit)
	ON_CBN_SELENDOK(IDC_COMBO_CHECKBIT, OnSelendokComboCheckbit)
	ON_CBN_SELENDOK(IDC_COMBO_DATA_BIT, OnSelendOkComboDataBit)
	ON_CBN_SELENDOK(IDC_COMBO_STOPBIT, OnSelendOkComboStopbit)
	ON_CBN_SELENDOK(IDC_COMBO_PORTNAME, OnSelendOkComboPortName)
	ON_BN_CLICKED(IDC_BUTTON_FILE, OnButtonFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CSerialTempDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CSerialTempDlg)
	ON_EVENT(CSerialTempDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialTempDlg message handlers

BOOL CSerialTempDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	/*************************************UserInit***************************************/
	// ���ö�ʱ��1 ����500ms 
	SetTimer(1,500,NULL);

	InitCombox();
	InitSerialPort();
	tempFlag = false; //Ĭ�ϲ�Ҫ�����¶�


	chart.SetDrawingSource(&list);

	m_bar.Create(this);
	m_bar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));//����ָ����ָʾ��������ID����ʽ�Ϳ��
	m_bar.SetPaneInfo(0, ID_INDICATOR_NAME, SBPS_STRETCH, 20);
	m_bar.SetPaneInfo(1, ID_INDICATOR_NUMBER, SBPS_STRETCH, 20);
	m_bar.SetPaneInfo(2, ID_INDICATOR_MAJOR, SBPS_STRETCH, 20);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, ID_INDICATOR_NAME);//��ʾ��������״̬�� 
	return TRUE;  // return TRUE  unless you set the focus to a control
}


/**
* @ Function Name : InitCombox
* @ Author        : TBP
* @ Brief         : ��ʼ����Ͽ�
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::InitCombox()
{
	
	/**************************��λ������ ************************************/
	mLowStopBit.SetCurSel(0);  // 1λ  ȡ�õ�ǰλ
	mLowDataBit.SetCurSel(3); // 8
	mLowCheck.SetCurSel(0);  // ��У��
	mLowBaud.SetCurSel(4);  // 9600

//	OnDropdownComboPortName(); // ���´��ں���Ͽ������
   
	mStopBit.SetCurSel(0);
	mDataBit.SetCurSel(3);;
	mCheckBit.SetCurSel(0);
	mComboBaud.SetCurSel(4);  // ��ʾΪ9600 

}

/**
* @ Function Name : InitSerialPort
* @ Author        : TBP
* @ Brief         : ��ʼ����Ͽ�
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::InitSerialPort()
{

	mSerial.SetInputMode(1);
	mSerial.SetInBufferSize(1024);
	mSerial.SetOutBufferSize(512);
	mSerial.SetRThreshold(1);
	mSerial.SetSettings("9600,N,8,1");

	mLowSerial.SetInputMode(1);
	mLowSerial.SetInBufferSize(1024);
	mLowSerial.SetOutBufferSize(512);
	mSerial.SetRThreshold(1);
	mSerial.SetSettings("9600,N,8,1"); 
}


void CSerialTempDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSerialTempDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CSerialTempDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




/**
* @ Function Name : OnTimer
* @ Author        : TBP
* @ Brief         : ��ʱ���Ļص�
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::OnTimer(UINT nIDEvent) 
{
	if(tempFlag)
	{
		int temp = getRandomTemprature(); 
		temp = temp%MAX_TEMPERATURE;			// �õ�ָ���¶ȷ�Χ���¶�
		temp+=MIN_TEMPERATURE;
	//	temp/=100;
		if(temp>MAX_TEMPERATURE)
			temp = MAX_TEMPERATURE;
		mStrTem.Format("{%d}",temp);             // ���¶�����ת���ַ��� ��ʽ�� { �¶��ַ��� }
		mLowSerial.SetOutput(COleVariant(mStrTem));  // �����ַ���
		UpdateData(false);                           // ���½���
	}	
	CDialog::OnTimer(nIDEvent);
}


/**
* @ Function Name : DealTemprature
* @ Author        : TBP
* @ Brief         : �Ӵ����ַ����н������¶���Ϣ,��ӵ�������
* @ Date          : 2016.07.09
* @ Modify        : ...
**/
void CSerialTempDlg::DealTemprature(CString str)
{
	static int x = 0;
	int index = str.Find('{');
	str = str.Mid(index+1);
	index = str.Find('}');
	str = str.Left(index);
	CPoint point;
	point.y=atof(str) - 7059;
	point.x =x++; 
	list.AddTail(point);	
}


/**
* @ Function Name : OnOnCommMscomm1
* @ Author        : TBP
* @ Brief         : ���ڽ��յ����ݵĻص�
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::OnOnCommMscomm1() 
{	
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len,k;
	BYTE rxdata [2048];             
	CString strtemp;
	if(mSerial.GetCommEvent()==2) 
	{
	  variant_inp=mSerial.GetInput(); 
	  safearray_inp=variant_inp;           
	  len=safearray_inp.GetOneDimSize(); 
	  for(k=0;k<len;k++)
		  safearray_inp.GetElement(&k,rxdata+k);  
	  for(k=0;k<len;k++)                 
	  {
		 BYTE bt=*(char*)(rxdata+k);    
		 strtemp.Format("%c",bt);        
		 m_str+=strtemp;
		 if(m_str.Find('{') >=0 && m_str.Find('}') >=0)
		 {
			DealTemprature(m_str);
			m_str = "";  // ��ջ���
		 }
	  }
	}
	UpdateData(false);
}



/********************************************ControlMessage*********************************************/


/***************************************************��λ��***********************************************/

/**
* @ Function Name : OnSelendOkComboLowPortName
* @ Author        : TBP
* @ Brief         : ���ںŵ�ѡ��
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::OnSelendOkComboLowPortName() 
{
	int index = mLowPortName.GetCurSel();
	CString str;
	mLowPortName.GetLBText(index,str);
	str.Replace("COM",""); // ȡ�ô��ں� ȥ��COM����
	index = _ttoi(str);
	mLowSerial.SetCommPort(index);
}

/**
* @ Function Name : OnSelendOkComboLowBaudRate
* @ Author        : TBP
* @ Brief         : �����ʵ�ѡ��
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::OnSelendOkComboLowBaudRate() 
{
	int index = mLowBaud.GetCurSel();
	CString str;
	mLowBaud.GetLBText(index,str);
	mLowSerial.SetSettings( str+",,,");
}

/**
* @ Function Name : OnSelendOkComboLowCheck
* @ Author        : TBP
* @ Brief         : У��λ
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::OnSelendOkComboLowCheck() 
{
	int index = mLowBaud.GetCurSel();
	switch(index)
	{
	case 0:
		mLowSerial.SetSettings(",N,,"); 
		break;
	case 1:
		mLowSerial.SetSettings(",O,,"); 
		break;
	case 2:
		mLowSerial.SetSettings(",E,,");
		break;
	}
}

/**
* @ Function Name : OnSelendOkComboLowDataBit
* @ Author        : TBP
* @ Brief         : ����λ
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::OnSelendOkComboLowDataBit() 
{
	int index = mLowDataBit.GetCurSel();
	switch(index)
	{
	case 0:
		mLowSerial.SetSettings(",,5,"); 
		break;
	case 1:
		mLowSerial.SetSettings(",,6,"); 
		break;
	case 2:
		mLowSerial.SetSettings(",,7,");
		break;
	case 3:
		mLowSerial.SetSettings(",,8,");
		break;
	}
	
}

/**
* @ Function Name : OnSelendOkComboLowDataBit
* @ Author        : TBP
* @ Brief         : ֹͣλ
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::OnSelendOkComboLowStopbit() 
{
	int index = mLowStopBit.GetCurSel();
	switch(index)
	{
	case 0:
		mLowSerial.SetSettings(",,,1"); 
		break;
	case 1:
		mLowSerial.SetSettings(",,,1.5"); 
		break;
	case 2:
		mLowSerial.SetSettings(",,,2");
		break;
	}
}


/**
* @ Function Name : OnBtnTempSender
* @ Author        : TBP
* @ Brief         : ģ�ⷢ���¶ȵĴ��ڿ���
* @ Date          : 2016.07.09
* @ Modify        : ...
**/
void CSerialTempDlg::OnBtnTempSender() 
{
	if(mLowSerial.GetPortOpen())
	{
		mLowSerial.SetPortOpen(false); //�رմ���
		tempFlag = false;
		mBtnTempSender.SetWindowText("�����¶�");
	}
	else
	{	
//		mLowSerial.SetCommPort(1);
		mLowSerial.SetPortOpen(true);	 //�򿪴���
		mLowSerial.SetInputLen(0);
		mLowSerial.GetInput();
		tempFlag = true;              // �����¶�
		mBtnTempSender.SetWindowText("ֹͣ����");
	}
}


/**
* @ Function Name : OnDropdownComboLowPortname
* @ Author        : TBP
* @ Brief         : ��Ͽ��չ��ʱ�� �����������ߵ�com��
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::OnDropdownComboLowPortname() 
{
	mLowPortName.ResetContent();
	
 	HKEY hKey; 
	int rtn;
	rtn = RegOpenKeyEx( HKEY_LOCAL_MACHINE, "Hardware\\DeviceMap\\SerialComm", NULL, KEY_READ, &hKey);
	if( rtn == ERROR_SUCCESS) // �򿪴���ע��� 
	{ 
		int i=0; 
		TCHAR portName[256],commName[256]; 
		DWORD dwLong,dwSize; 
		while(1) 
		{ 
			dwSize = sizeof(portName); 
			dwLong = dwSize;
			rtn = RegEnumValue( hKey, i, portName, &dwLong, NULL, NULL, (PUCHAR)commName, &dwSize );
			if( rtn == ERROR_NO_MORE_ITEMS ) // ö�ٴ��� 
				break; 
			CString str = (CString)commName;
			mLowPortName.AddString(str);
			i++;
		} 
	    RegCloseKey(hKey);
		//mLowPortName.SetCurSel(temSerialIndex);
	}
}



/********************************************************��λ��********************************************************/

/**
* @ Function Name : OnChangeComboBaudrate
* @ Author        : TBP
* @ Brief         : ��������Ͽ�Ļص�
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::OnSelendOkComboBaudrate() 
{
		// ȡ�õ�ǰ��ѡ�е�index
	int index = mComboBaud.GetCurSel();
	// �õ�ѡ�е��ַ���
	CString str;
	mComboBaud.GetLBText(index,str);
	//MessageBox(str);
	mSerial.SetSettings(str+",,,");
}

/**
* @ Function Name : OnSelendokComboCheckbit
* @ Author        : TBP
* @ Brief         : ��λ��У��λ
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::OnSelendokComboCheckbit() 
{
	int index = mCheckBit.GetCurSel();
	switch(index)
	{
	case 0:
		mSerial.SetSettings(",N,,"); 
		break;
	case 1:
		mSerial.SetSettings(",O,,"); 
		break;
	case 2:
		mSerial.SetSettings(",E,,");
		break;
	}
}


/**
* @ Function Name : OnSelendOkComboDataBit
* @ Author        : TBP
* @ Brief         : ��λ������λ
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::OnSelendOkComboDataBit() 
{
	int index = mDataBit.GetCurSel();
	switch(index)
	{
	case 0:
		mSerial.SetSettings(",,5,"); 
		break;
	case 1:
		mSerial.SetSettings(",,6,"); 
		break;
	case 2:
		mSerial.SetSettings(",,7,");
		break;
	case 3:
		mSerial.SetSettings(",,8,");
		break;
	}
}

/**
* @ Function Name : OnSelendOkComboStopbit
* @ Author        : TBP
* @ Brief         : ��λ������λ
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::OnSelendOkComboStopbit() 
{
	int index = mStopBit.GetCurSel();
	switch(index)
	{
	case 0:
		mSerial.SetSettings(",,,1"); 
		break;
	case 1:
		mSerial.SetSettings(",,,1.5"); 
		break;
	case 2:
		mSerial.SetSettings(",,,2");
		break;
	}
}

/**
* @ Function Name : OnSelendOkComboPortName
* @ Author        : TBP
* @ Brief         : ���ںŵ�ѡ��
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::OnSelendOkComboPortName() 
{
	int index = mComboPortName.GetCurSel();
	CString str;
	mComboPortName.GetLBText(index,str);
	str.Replace("COM",""); // ȡ�ô��ں� ȥ��COM����
	index = _ttoi(str);
	mSerial.SetCommPort(index);	
}


/**
* @ Function Name : OnSerialSw
* @ Author        : TBP
* @ Brief         : ���ڿ��ػص�
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::OnSerialSw() 
{
	if(mSerial.GetPortOpen())
	{
		mSerial.SetPortOpen(false);
		mBtnOpen.SetWindowText("�򿪴���");
	}
	else 
	{
	//	mSerial.SetCommPort(3);
		mSerial.SetPortOpen(true);
		mSerial.SetInputLen(0);
		mSerial.GetInput();
		mBtnOpen.SetWindowText("�رմ���");
	}
}

/**
* @ Function Name : OnDropdownComboPortName
* @ Author        : TBP
* @ Brief         : ��Ͽ��չ��ʱ�� �����������ߵ�com��
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::OnDropdownComboPortName() 
{
	mComboPortName.ResetContent();
 	HKEY hKey; 
	int rtn;
	rtn = RegOpenKeyEx( HKEY_LOCAL_MACHINE, "Hardware\\DeviceMap\\SerialComm", NULL, KEY_READ, &hKey);
	if( rtn == ERROR_SUCCESS) // �򿪴���ע��� 
	{ 
		int i=0; 
		TCHAR portName[256],commName[256]; 
		DWORD dwLong,dwSize; 
		while(1) 
		{ 
			dwSize = sizeof(portName); 
			dwLong = dwSize;
			rtn = RegEnumValue( hKey, i, portName, &dwLong, NULL, NULL, (PUCHAR)commName, &dwSize );
			if( rtn == ERROR_NO_MORE_ITEMS ) // ö�ٴ��� 
				break; 
			CString str = (CString)commName;
			mComboPortName.AddString(str);
			i++;
		} 
	    RegCloseKey(hKey);
		//mComboPortName.SetCurSel(termiSerialIndex);
	}
}


/***************************************����¶�***********************************************/
/**
* @ Function Name : OnDropdownComboPortName
* @ Author        : TBP
* @ Brief         : �����
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
int CSerialTempDlg::getRandomTemprature()
{
	srand((unsigned)time(NULL));  // �����������
	int temperatrue = rand();
	return temperatrue;
}

/******************************�ļ�����****************************/
/**
* @ Function Name : OnButtonFile
* @ Author        : TBP
* @ Brief         : �����ļ�
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CSerialTempDlg::OnButtonFile() 
{
	CString filePath;
	CFileDialog saveDialog(false,_T("txt"),_T("δ����"));
	if (saveDialog.DoModal()!=IDOK)   //��ʾһ��ģ̬�Ի���
	{
		//MessageBox(_T(""));
		return;
	}
	filePath = saveDialog.GetPathName();     // �����ļ�·�� 
	//CFile file;
	CStdioFile file;
	if (!file.Open(filePath, CFile::modeCreate | CFile::modeWrite)) {
		MessageBox(_T("���ļ�ʧ��"));
		return;
	}
	POSITION pos = list.GetHeadPosition();
	while (pos != NULL) {
		CPoint point;
		point = list.GetNext(pos);
		CString string;
		string.Format(_T("{ %5d : %-5d }\r\n"), point.x, point.y);
		// д�ļ�
		file.WriteString(string);
	}
	file.Close();
	MessageBox("����ɹ���");
}
