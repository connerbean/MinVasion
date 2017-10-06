/**
* \file Game.h
*
* \author Matthew Rhodes
*
*  Class that hold all the pieces to the game
*/
#pragma once
using namespace Gdiplus;
class CGame
{
	/// Game area width in virtual pixels
	const static int Width = 1400;

	/// Game area height in virtual pixels
	const static int Height = 1100;
public:
	CGame();
	~CGame();
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
	Gdiplus::REAL  mScale = 0;

	Gdiplus::REAL mXOffset = 0;

	Gdiplus::REAL mYOffset = 0;
};

