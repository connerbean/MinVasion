
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "MinionSwarm.h"
#include "ChildView.h"
#include "Game.h"
#include <algorithm>
#include "Gru.h"
#include "DoubleBufferDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace Gdiplus;
using namespace std;
// CChildView


CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}



void CChildView::OnPaint() 
{
	CPaintDC paintDC(this);     // device context for painting
	CDoubleBufferDC dc(&paintDC); // device context for painting
	Graphics graphics(dc.m_hDC);

	CRect rect;
	GetClientRect(&rect);

	mGame.OnDraw(&graphics, rect.Width(), rect.Height());
	// Do not call CWnd::OnPaint() for painting messages
	auto Gru = make_shared<CGru>(&mGame);
	Gru->SetLocation(100, 400);
	Gru->Draw(&graphics);
	mGame.Add(Gru);
	
}



void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	auto mGrabbedItem = mGame.HitTest(point.x, point.y);
	if (mGrabbedItem != nullptr)
	{
		// We have selected an item
		// Move it to the end of the list of items
		mGame.Delete(mGrabbedItem);
		mGame.Add(mGrabbedItem);
	}
}

/** Called when the left mouse button is released
* \param nFlags Flags associated with the mouse button release
* \param point Where the button was pressed
*/
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	OnMouseMove(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return false;
}
