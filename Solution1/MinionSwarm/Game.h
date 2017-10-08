/**
* \file Game.h
*
* \author Matthew Rhodes
*
*  Class that hold all the pieces to the game
*/
#pragma once
#include <memory>


using namespace Gdiplus;
using namespace std;

class CItem;

class CGame
{
	/// Game area width in virtual pixels
	const static int Width = 1400;

	/// Game area height in virtual pixels
	const static int Height = 1100;
public:

	/**
	* Add fish to the aquarium
	*/
	void CGame::Add(std::shared_ptr<CItem> item);

	CGame();
	virtual ~CGame();
	/**
	* Draw the game area
	* \param graphics The GDI+ graphics context to draw on
	* \param width Width of the client window
	* \param height Height of the client window
	*/
	void CGame::OnDraw(Gdiplus::Graphics *graphics, int width, int height)
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

	}
private:
	/**
	* mScale is the average of scaleX and scaleY
	*/
	Gdiplus::REAL  mScale = 0;

	/**
	* Offset for X
	*/
	Gdiplus::REAL mXOffset = 0;

	/**
	* Offset for Y
	*/
	Gdiplus::REAL mYOffset = 0;
};

