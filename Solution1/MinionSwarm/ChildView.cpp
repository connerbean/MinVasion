
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
	auto Gru = make_shared<CCharacterGru>(&mGame);
	Gru->SetLocation(0, 400);
	mGame.Add(Gru);

	auto villainArya = make_shared<CCharacterVillain>(&mGame, CCharacterVillain::Types::Arya);
	villainArya->SetLocation(0, 220);
	mGame.Add(villainArya);

	auto villainJuicer = make_shared<CCharacterVillain>(&mGame, CCharacterVillain::Types::Juicer);
	villainJuicer->SetLocation(-250, -250);
	mGame.Add(villainJuicer);

	auto villainPokeball = make_shared<CCharacterVillain>(&mGame, CCharacterVillain::Types::Pokeball);
	villainPokeball->SetLocation(250, -250);
	mGame.Add(villainPokeball);

	auto restartSide = make_shared<CRestartSide>(&mGame);
	restartSide->SetLocation(-650, -420);
	mGame.Add(restartSide);

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

	mClock.Update(elapsed);		// adds elapsed time to overall time
	mGame.Update(elapsed);
	mGame.OnDraw(&graphics, rect.Width(), rect.Height());

	mClock.DisplayTime(&graphics);	// displays timer in correct location in correct format
	
	
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
		// We have selected an item
		// Move it to the end of the list of items
		mGame.Delete(mGrabbedItem);
		mGame.Add(mGrabbedItem);
	}
	if (mGrabbedItem->IsButton() == true)
	{
		mGame.Restart();
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
