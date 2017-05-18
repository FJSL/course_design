// CustomChart.cpp : implementation file
//

#include "stdafx.h"
#include "SerialTemp.h"
#include "CustomChart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CustomChart

CustomChart::CustomChart()
{
	RegisterWndClass();
	padding = 5;
	scal= 0;

}

CustomChart::~CustomChart()
{
//	KillTimer(2);
}


BEGIN_MESSAGE_MAP(CustomChart, CWnd)
	//{{AFX_MSG_MAP(CustomChart)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/**
* @ Function Name : SetDrawingSource
* @ Author        : zzq
* @ Brief         : ���û�ͼ��Դ
* @ Input         : CList<CPoint,CPoint&> *list ����ָ��
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CustomChart::SetDrawingSource(CList<CPoint,CPoint&> *list)
{
	mList = list;
	SetTimer(2,30,NULL); // 30 ftps
}

/////////////////////////////////////////////////////////////////////////////
// CustomChart message handlers

/**
* @ Function Name : RegisterWndClass
* @ Author        : zzq
* @ Brief         : ע�ᴰ��
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
bool CustomChart::RegisterWndClass()
{
	WNDCLASS windowclass;
	HINSTANCE hInst=AfxGetInstanceHandle();
	if(!::GetClassInfo(hInst,"CustomChart",&windowclass))
	{
	 windowclass.style=CS_DBLCLKS;
	 windowclass.lpfnWndProc=::DefWindowProc;
	 windowclass.cbClsExtra=windowclass.cbWndExtra=0;
	 windowclass.hInstance=hInst;
	 windowclass.hIcon=NULL;
	 windowclass.hCursor=AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	 windowclass.hbrBackground=::GetSysColorBrush(COLOR_WINDOW);
 	 windowclass.lpszMenuName=NULL;
	 windowclass.lpszClassName="CustomChart";
	  if(!AfxRegisterClass(&windowclass))
	  {
		AfxThrowResourceException();
		return false;
	  }
	}
	return true;
}

void CustomChart::OnPaint() 
{	
	CPaintDC dc(this); // device context for painting
    CRect rect;   
    GetClientRect(rect);   
	int width  = rect.Width();
	int height = rect.Height();

	dc.SetMapMode(MM_ANISOTROPIC);  // ����ӳ��ģʽ
	dc.SetViewportOrg(5*padding,height-4*padding);
	dc.SetViewportExt(width, -height); // ָ���豸�ӿ�Ϊwidth��height�����ص�λ 
	dc.SetWindowExt(500, 500); // ָ���߼�����Ϊ500��100���߼���λ  �¶�ֵΪ 0 ~ 100 

	CDC MemDC;          //���ڻ�����ͼ���ڴ�DC
    MemDC.CreateCompatibleDC(&dc);  //��������DC���������ڴ�DC
    //����һ���ڴ��е�ͼ��
    CBitmap MemBitmap;
    MemBitmap.CreateCompatibleBitmap(&dc, width, height);
	MemDC.SelectObject(&MemBitmap);

	MemDC.SetMapMode(MM_ANISOTROPIC);  // ����ӳ��ģʽ
	MemDC.SetViewportOrg(5*padding,height-4*padding);
	MemDC.SetViewportExt(width,-height ); // ָ���豸�ӿ�Ϊwidth��height�����ص�λ 
	MemDC.SetWindowExt(500, 500); // ָ���߼�����Ϊ500��100���߼���λ  �¶�ֵΪ 0 ~ 500	
	MemDC.DPtoLP(rect); // ���豸����ת�����߼�����

	 
	//����һ����ɫ��Ϊ�ڴ���ʾ�豸�ı���ɫ
    MemDC.FillSolidRect(rect, dc.GetBkColor());
	// ��������ϵ
	DrawCoordinate(MemDC,500,500);

	CPoint mousePoint;
	GetCursorPos(&mousePoint); // ȡ����굱ǰ���豸����
	ScreenToClient(&mousePoint); // ת���ɿؼ��ڵ��������
	MemDC.DPtoLP(&mousePoint);   // ת�����߼�����
	if(mousePoint.x>0 && mousePoint.y > 0)
		// ���Ʋο���
		DrawRefenceLine(MemDC,mousePoint,500,500);

	CPen pen(PS_SOLID, 1, RGB(255, 1, 1));
	MemDC.SelectObject(&pen);

	// ��ȡ�����������
	POSITION position = mList->GetHeadPosition();
	if(position != NULL)
	{
		CPoint point  = mList->GetNext(position);
		MemDC.MoveTo(point.x ,point.y);
		while(position!=NULL)
		{
			for(int i = 0 ; i<scal ; i++)
			{
				mList->GetNext(position);
			}
			CPoint point = mList->GetNext(position);
			MemDC.LineTo(point.x ,point.y);
		}	
	}
	//dc.BitBlt(0, 0, rect.Width(), rect.Height(),&MemDC,NULL, NULL, SRCCOPY);
	// �ڴ�鸴��
	dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),&MemDC, rect.left, rect.top, SRCCOPY);
	ReleaseDC(&MemDC);
}

/**
* @ Function Name : DrawCoordinate
* @ Author        : zzq
* @ Brief         : ��������ϵ
* @ Input         : CPaintDC &dc �豸������
*                 : int width 
*				  : int height
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CustomChart::DrawCoordinate(CDC &dc,int width,int height)
{
	// ����y��
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	dc.SelectObject(&pen);

	// y���ͷ
	dc.MoveTo(0,-2*padding);
	dc.LineTo(0  , height - 2*padding);
	dc.LineTo(-4 , height - 2*padding - 4);
	dc.MoveTo(0 , height - 2*padding);
	dc.LineTo(4,height - 2*padding - 4);

	// �̶�
	for(int i =10; i<height-2*padding;i+=10)
	{
		dc.MoveTo(0,i);
		dc.LineTo(-8,i);
		CString str;
		str.Format("%d",i);
		dc.TextOut(-30,i+2,str);
	}
	dc.TextOut(10,height-10,"T/��C");
	// X��
	dc.MoveTo(-5*padding,0);
	dc.LineTo(width-9*padding ,0);
	dc.LineTo(width -9*padding- 10,1);
	dc.MoveTo(width - 9*padding,0);
	dc.LineTo(width - 9*padding -10,-1);
	
}

void CustomChart::OnTimer(UINT nIDEvent) 
{

	CRect rect;
	GetClientRect(&rect);
	InvalidateRect(rect,false);   //���½��� ���������
	OnPaint();
	CWnd::OnTimer(nIDEvent);
}


void CustomChart::DrawRefenceLine(CDC &dc,CPoint point,int width,int height)
{
	// ��ɫ
	CPen pen(PS_DASH, 1, RGB(125, 125, 125));
	dc.SelectObject(&pen);
	dc.MoveTo(0,point.y);  
	dc.LineTo(width,point.y);
	
	dc.MoveTo(point.x,0);
	dc.LineTo(point.x,height);

}

BOOL CustomChart::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	//scal  = zDelta;
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}
