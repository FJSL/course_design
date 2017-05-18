#if !defined(AFX_CUSTOMCHART_H__77FD0112_5E42_41C4_82F7_1436787E1CAE__INCLUDED_)
#define AFX_CUSTOMCHART_H__77FD0112_5E42_41C4_82F7_1436787E1CAE__INCLUDED_

#include "Afxtempl.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomChart.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CustomChart window

class CustomChart : public CWnd
{
// Construction
public:
	CustomChart();

// Attributes
public:
	CList<CPoint,CPoint&> *mList;
	int padding;
	int scal;  // 缩放比例

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CustomChart)
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawRefenceLine(CDC &dc,CPoint point,int width,int height);

	// 设置绘图资源
	void SetDrawingSource(CList<CPoint,CPoint&> *list);
	bool RegisterWndClass();
	virtual ~CustomChart();

	// Generated message map functions
protected:
	//{{AFX_MSG(CustomChart)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DrawCoordinate(CDC &dc,int width,int height);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMCHART_H__77FD0112_5E42_41C4_82F7_1436787E1CAE__INCLUDED_)
