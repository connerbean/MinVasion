#include "stdafx.h"
#include "Game.h"
#include "Item.h"
#include "PlayArea.h"
#include "Gru.h"

CGame::CGame()
{
}


CGame::~CGame()
{
}

/**
* Add an item to the aquarium
* \param item New item to add
*/
void CGame::Add(std::shared_ptr<CItem> item)
{
	mItems.push_back(item);
}

/**
* Finds and deletes the selected item
*/
void CGame::Delete(std::shared_ptr<CItem> item)
{
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		mItems.erase(loc);
	}
}

///Converts the Y value so pieces can be moved in the game
int CGame::ConvertY(int y)
{
	y = (y - mYOffset) / mScale;
	return y;
}

///Converts the X value so pieces can be moved in the game
int CGame::ConvertX(int x)
{
	x = (x - mXOffset) / mScale;
	return x;
}

/**
* Test to see if things in the aquarium have been hit
*/
std::shared_ptr<CItem> CGame::HitTest(int x, int y)
{
	x = (x - mXOffset) / mScale;
	y = (y - mYOffset) / mScale;
 	for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}

	return  nullptr;
}

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CGame::Update(double elapsed)
{
	for (auto item : mItems)
	{
		item->Update(elapsed);
	}
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

	for (auto item : mItems)
	{
		item->Draw(graphics);
	}


}