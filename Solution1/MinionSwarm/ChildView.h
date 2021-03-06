/**
 * \file ChildView.h
 *
 * \author Matthew May
 *
 *  This class describes our window functionality
 */


// ChildView.h : interface of the CChildView class
//


#pragma once
#include "Game.h"
#include "Clock.h"
#include "Scoreboard.h"
#include "RestartSide.h"
#include <memory>


/**
* Class definition for the Childview
*/
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();		///< Where items get painted
	DECLARE_MESSAGE_MAP()

private:
	std::shared_ptr<CRestartSide> mNewGameButton; ///< New Game button
	CGame mGame;			///< game we are currently playing
	CScoreboard mScoreboard;	///< scoreboard for the current game
	CClock mClock;			///< clock object for keeping time
	bool mFirstDraw = true; ///< Boolean for first draw
	long long mLastTime;    ///< Last time we read the timer
	double mTimeFreq;       ///< Rate the timer updates						
	std::shared_ptr<CCharacter> mGrabbedItem;	///< Any item we are currently dragging
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);	///< Event handler for update on timer function
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);		///< Event handler for erasing flicker
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

