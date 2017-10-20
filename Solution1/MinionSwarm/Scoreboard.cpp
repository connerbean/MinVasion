/**
 * \file Clock.cpp
 *
 * \author Collin Dillinger
 */
#include "stdafx.h"
#include "Game.h"
#include "VillainCollector.h"
#include "CharacterVillain.h"
#include "Scoreboard.h"

using namespace Gdiplus;
using namespace std;

const float CenterXLocation = 580;
const float TopYLocation = -450;
const float TextTopMargin = 5;
const float TextYHeight = 50;

/**
 * Constructor
 * \param game The Game this is a member of
 */
CScoreboard::CScoreboard(CGame *game)
{
	mGame = game;
}

/**
 * Destructor
 */
CScoreboard::~CScoreboard()
{
}

/** Draw this item
 * \param graphics The graphics context to draw on */
void CScoreboard::Draw(Gdiplus::Graphics * graphics)
{
	// Initialize the string drawing variables
	StringFormat format;
	format.SetAlignment(StringAlignmentCenter);

	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 26);

	SolidBrush green(Color(0, 140, 0));

	// Get a collection of villains
	CVillainCollector villainCollector;
	mGame->Accept(&villainCollector);

	double yLocation = TopYLocation;

	for (auto villain : villainCollector.Retrieve())
	{
		// Only display if the villain has a score above 0
		int score = villain->GetPoints();
		if (score > 0)
		{
			yLocation += villain->DrawAt(graphics, CenterXLocation, yLocation);

			// Draw points below image
			wstring points = to_wstring(score);

			graphics->DrawString(points.c_str(), -1, &font, PointF(CenterXLocation, yLocation + TextTopMargin), &format, &green);

			yLocation += TextYHeight;
		}
	}
}