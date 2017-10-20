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

const REAL ClockXLocation = 550; ///<Clock's X location to display at
const REAL ClockYLocation = -510; ///<Clock's Y Location to display at
const int SecondsInMinute = 60; ///< Number of seconds in a minute

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
 * \param elapsed time passed since this was last called
 */
void CClock::Update(double elapsed)
{
	mTimePassed += elapsed;
}

/** Draws the clock on the screen
 * \param graphics The graphics context to draw on */
void CClock::Draw(Gdiplus::Graphics * graphics)
{
	int seconds = (int)fmod(mTimePassed, SecondsInMinute);
	int minutes = (int)mTimePassed / SecondsInMinute;

	// time to display clock
	wstring s = to_wstring(seconds); // total seconds

	if (seconds < 10) s = L"0" + s;  // formatting single digit seconds

	wstring m = to_wstring(minutes); // total minutes

	wstring fin = m + L":" + s;	      // final printable wstring

	if (graphics != NULL)
	{
		FontFamily fontFamily(L"Arial");
		Gdiplus::Font font(&fontFamily, 26);

		SolidBrush green(Color(0, 140, 0));
		graphics->DrawString(fin.c_str(), -1, &font, PointF(ClockXLocation, ClockYLocation), &green);
	}
}