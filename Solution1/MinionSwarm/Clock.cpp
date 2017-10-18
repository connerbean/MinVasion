/**
 * \file Clock.cpp
 *
 * \author Conner Bean
 */


#include "stdafx.h"
#include "Clock.h"
#include <string>

using namespace Gdiplus;
using namespace std;


const REAL ClockXLocation = 1050; ///<Clock's X location to display at
const REAL ClockYLocation = -550; ///<Clock's Y Location to display at

/**
 * Constructor
 */
CClock::CClock()
{
}

/**
 * Destructor
 */
CClock::~CClock()
{
}

/**
 * Update used to increment overall time
 *
 * Should be called after MinionSwarm.Update in 
 *		ChildView
 *
 * \param elapsed 
 */
void CClock::Update(double elapsed)
{
	mTimePassed += elapsed;
}

/** Draw this item
 * \param graphics The graphics context to draw on */
void CClock::Draw(Gdiplus::Graphics * graphics)
{
	int seconds = (int)fmod(mTimePassed, 60);
	int minutes = (int)mTimePassed / 60;

	// time to display clock
	wstring s = to_wstring(seconds); // total seconds

	if (seconds < 10) s = L"0" + s;  // formatting single digit seconds

	wstring m = to_wstring(minutes); // total minutes

	wstring fin = m + L":" + s;	      // final printable wstring

	if (graphics != NULL)
	{
		FontFamily fontFamily(L"Arial");
		Gdiplus::Font font(&fontFamily, 46);

		SolidBrush green(Color(0, 94, 0));
		graphics->DrawString(fin.c_str(), -1, &font, PointF(ClockXLocation, ClockYLocation), &green);
	}
}