
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "DoubleBufferDC.h"
#include "MinionSwarm.h"
#include "ChildView.h"
#include "Game.h"
#include "CharacterGru.h"
#include "CharacterMinion.h"
#include "CharacterVillain.h"
#include "RestartSide.h"
#include <algorithm>

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
	mNewGameButton = make_shared<CRestartSide>();
	mNewGameButton->SetLocation(-650, -420);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
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
	// if its the first draw, start timer
	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);
	}

	CPaintDC paintDC(this);     // device context for painting
	CDoubleBufferDC dc(&paintDC); // device context for painting

	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	Graphics graphics(dc.m_hDC);

	CRect rect;
	GetClientRect(&rect);	

	

	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	mGame.Update(elapsed);
	mNewGameButton->Update(elapsed);
	mGame.OnDraw(&graphics, rect.Width(), rect.Height());
	mNewGameButton->Draw(&graphics);

	mClock.Update(elapsed, &graphics);		// adds elapsed time to overall time
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


/**
* Erase the background
*
* This is disabled to eliminate flicker
* \param pDC Device context
* \returns FALSE
*/
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

/** Called when there is a left mouse button press
* \param nFlags Flags associated with the mouse button press
* \param point Where the button was pressed
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	mGrabbedItem = mGame.HitTest(point.x, point.y);
	if (mGrabbedItem != nullptr)
	{

	}
	// TODO: remove dependency of CGame for x and y conversion
	if (mNewGameButton->HitTest(mGame.ConvertX(point.x), mGame.ConvertY(point.y)))
	{
		mGame.Reset();
		mClock.Reset();
	}
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	OnMouseMove(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		
		// If an item is being moved, we only continue to 
		// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{
			int x = mGame.ConvertX(point.x);
			int y = mGame.ConvertY(point.y);

			// Only move item if it is draggable
			if (mGrabbedItem->IsDraggable())
			{
				mGrabbedItem->SetLocation(x, y);

				mGrabbedItem->Constraints(mGrabbedItem->GetX(), mGrabbedItem->GetY());

			}
			
			/*if (mGrabbedItem->Killer() == true)
			{
				mGame.Delete(mGrabbedItem);
				mGame.Add(mGrabbedItem);
				/**mAquarium.Delete(mGrabbedItem);
				auto fishLocation = mAquarium.HitTest(point.x, point.y);
				if ( fishLocation != nullptr)
				{
				mAquarium.Delete(fishLocation);
				}
				mAquarium.Add(mGrabbedItem);
			}*/

		}
		else
		{
			// When the left button is released, we release the
			// item.
			mGrabbedItem = nullptr;
		}

		// Force the screen to redraw
		Invalidate();
	}
}
