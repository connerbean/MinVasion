#pragma once
#include "Game.h"
class CRestartSide :
	public CGame
{
public:
	// Draws graphical images
	virtual void Draw(Gdiplus::Graphics * graphics);

	CRestartSide();
	~CRestartSide();

private:
	// Poiner to item images
	std::unique_ptr<Gdiplus::Bitmap> mRestartImage;
};

