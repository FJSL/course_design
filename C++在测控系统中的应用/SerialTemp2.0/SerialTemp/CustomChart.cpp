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
* @ Brief         : 设置绘图资源
* @ Input         : CList<CPoint,CPoint&> *list 链表指针
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
* @ Brief         : 注册窗口
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

	dc.SetMapMode(MM_ANISOTROPIC);  // 设置映射模式
	dc.SetViewportOrg(5*padding,height-4*padding);
	dc.SetViewportExt(width, -height); // 指定设备视口为width×height的像素单位 
	dc.SetWindowExt(500, 500); // 指定逻辑窗口为500×100的逻辑单位  温度值为 0 ~ 100 

	CDC MemDC;          //用于缓冲作图的内存DC
    MemDC.CreateCompatibleDC(&dc);  //依附窗口DC创建兼容内存DC
    //创建一个内存中的图像
    CBitmap MemBitmap;
    MemBitmap.CreateCompatibleBitmap(&dc, width, height);
	MemDC.SelectObject(&MemBitmap);

	MemDC.SetMapMode(MM_ANISOTROPIC);  // 设置映射模式
	MemDC.SetViewportOrg(5*padding,height-4*padding);
	MemDC.SetViewportExt(width,-height ); // 指定设备视口为width×height的像素单位 
	MemDC.SetWindowExt(500, 500); // 指定逻辑窗口为500×100的逻辑单位  温度值为 0 ~ 500	
	MemDC.DPtoLP(rect); // 将设备坐标转化成逻辑坐标

	 
	//先用一种颜色作为内存显示设备的背景色
    MemDC.FillSolidRect(rect, dc.GetBkColor());
	// 绘制坐标系
	DrawCoordinate(MemDC,500,500);

	CPoint mousePoint;
	GetCursorPos(&mousePoint); // 取得鼠标当前的设备坐标
	ScreenToClient(&mousePoint); // 转化成控件内的相对坐标
	MemDC.DPtoLP(&mousePoint);   // 转化成逻辑坐标
	if(mousePoint.x>0 && mousePoint.y > 0)
		// 绘制参考线
		DrawRefenceLine(MemDC,mousePoint,500,500);

	CPen pen(PS_SOLID, 1, RGB(255, 1, 1));
	MemDC.SelectObject(&pen);

	// 读取链表绘制曲线
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
	// 内存块复制
	dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),&MemDC, rect.left, rect.top, SRCCOPY);
	ReleaseDC(&MemDC);
}

/**
* @ Function Name : DrawCoordinate
* @ Author        : zzq
* @ Brief         : 绘制坐标系
* @ Input         : CPaintDC &dc 设备上下文
*                 : int width 
*				  : int height
* @ Date          : 2016.07.08
* @ Modify        : ...
**/
void CustomChart::DrawCoordinate(CDC &dc,int width,int height)
{
	// 绘制y轴
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	dc.SelectObject(&pen);

	// y轴箭头
	dc.MoveTo(0,-2*padding);
	dc.LineTo(0  , height - 2*padding);
	dc.LineTo(-4 , height - 2*padding - 4);
	dc.MoveTo(0 , height - 2*padding);
	dc.LineTo(4,height - 2*padding - 4);

	// 刻度
	for(int i =10; i<height-2*padding;i+=10)
	{
		dc.MoveTo(0,i);
		dc.LineTo(-8,i);
		CString str;
		str.Format("%d",i);
		dc.TextOut(-30,i+2,str);
	}
	dc.TextOut(10,height-10,"T/°C");
	// X轴
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
	InvalidateRect(rect,false);   //更新界面 不清楚界面
	OnPaint();
	CWnd::OnTimer(nIDEvent);
}


void CustomChart::DrawRefenceLine(CDC &dc,CPoint point,int width,int height)
{
	// 灰色
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
