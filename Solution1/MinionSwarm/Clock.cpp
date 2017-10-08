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

	if (mTimePassed > 1)	// if its been a second
	{
		mSeconds++;

		if (mSeconds >= 60) // if over 60 seconds, increment minute, reset second
		{
			mMinutes++;
			mSeconds -= 60;
		}

		mTimePassed = mTimePassed - 1;		// Get remainder, basically modulo for doubles
	}
}


/**
* DisplayTime used to display current time
*
* Should be called in OnPaint in ChildView
*
* \param graphics
*/
void CClock::DisplayTime(Gdiplus::Graphics *graphics)
{
	wstring s = to_wstring(mSeconds); // total seconds

	if (mSeconds < 10) s = L"0" + s;  // formatting single digit seconds

	wstring m = to_wstring(mMinutes); // total minutes

	wstring fin = m + L":" + s;	      // final printable wstring

	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 46);

	SolidBrush green(Color(0, 94, 0));
	graphics->DrawString(fin.c_str(), -1, &font, PointF(1050, -550), &green);
}