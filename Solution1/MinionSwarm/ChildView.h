
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "Game.h"
#include "Clock.h"

// CChildView window

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
	CGame mGame;
	CClock mClock;			///< clock object for keeping time
	bool mFirstDraw = true; ///< Boolean for first draw
	long long mLastTime;    ///< Last time we read the timer
	double mTimeFreq;       ///< Rate the timer updates
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);	///< Event handler for update on timer function
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);		///< Event handler for erasing flicker
};

