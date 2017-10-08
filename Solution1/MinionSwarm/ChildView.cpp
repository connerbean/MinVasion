
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "MinionSwarm.h"
#include "ChildView.h"
#include "Game.h"
#include <algorithm>
#include "Gru.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace Gdiplus;
using namespace std;
// CChildView

/// Frame duration in milliseconds
const int FrameDuration = 30;

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
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
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	//CDoubleBufferDC dc(&paintDC); // device context for painting
	// Do not call CWnd::OnPaint() for painting messages
	Graphics graphics(dc.m_hDC);

	CRect rect;
	GetClientRect(&rect);

	mGame.OnDraw(&graphics, rect.Width(), rect.Height());
	// Do not call CWnd::OnPaint() for painting messages
	auto Gru = make_shared<CGru>(&mGame);
	Gru->SetLocation(100, -200);
	Gru->Draw(&graphics);
}


/**
* Handle timer events
* \param nIDEvent The timer event ID
*/
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}
