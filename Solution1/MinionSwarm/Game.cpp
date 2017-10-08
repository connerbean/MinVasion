#include "stdafx.h"
#include "Game.h"
#include "Item.h"
#include "PlayArea.h"

CGame::CGame()
{
}


CGame::~CGame()
{
}

void CGame::OnDraw(Gdiplus::Graphics * graphics, int width, int height)
{
	// Fill the background with black
	SolidBrush brush(Color::Black);
	graphics->FillRectangle(&brush, 0, 0, width, height);

	//
	// Automatic Scaling
	//
	float scaleX = float(width) / float(Width);
	float scaleY = float(height) / float(Height);
	mScale = min(scaleX, scaleY);

	mXOffset = width / 2.0f;
	mYOffset = height / 2.0f;

	graphics->TranslateTransform(mXOffset, mYOffset);
	graphics->ScaleTransform(mScale, mScale);

	// From here on you are drawing virtual pixels

	///Draw Board
	CPlayArea grid;
	grid.DrawGrid(graphics, width, height);

}
