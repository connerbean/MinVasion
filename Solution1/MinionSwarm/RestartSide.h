#pragma once
#include "Game.h"
class CRestartSide :
	public CGame
{
public:
	// Draws graphical images
	virtual void Draw(Gdiplus::Graphics * graphics);

	CRestartSide();
	virtual ~CRestartSide();

	/**  The X location of the center of the tile
	* \returns X location in pixels */
	int GetX() const { return mX; }

	/**  The Y location of the center of the tile
	* \returns Y location in pixels */
	int GetY() const { return mY; }

private:
	// Poiner to item images
	std::unique_ptr<Gdiplus::Bitmap> mRestartImage;

	/**
	* X coordinate
	*/
	int mX = 0;

	/**
	* Y coordinate
	*/
	int mY = 0;
};

