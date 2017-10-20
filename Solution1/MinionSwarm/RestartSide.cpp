#include "stdafx.h"
#include "RestartSide.h"
#include <string>

/// Item filename 
const wstring NewGameImageName = L"images/new-game.png";

/**
* Draw this item
* \param graphics Graphics device to draw on
*/
void CRestartSide::Draw(Gdiplus::Graphics *graphics)
{
	double wid = mRestartImage->GetWidth();
	double hit = mRestartImage->GetHeight();
	graphics->DrawImage(mRestartImage.get(),
		float(GetX() - wid / 2), float(GetY() - hit / 2),
		float(mRestartImage->GetWidth()), float(mRestartImage->GetHeight()));
}

/**
* Constructor for the restart side class
*/
CRestartSide::CRestartSide()
{
	mRestartImage = unique_ptr<Bitmap>(Bitmap::FromFile(NewGameImageName.c_str()));
	if (mRestartImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += NewGameImageName;
		AfxMessageBox(msg.c_str());
	}
}

CRestartSide::~CRestartSide()
{
}

/**
* Test to see if we hit this object with a mouse.
* \param x X position to test
* \param y Y position to test
* \return true if hit.
*/
bool CRestartSide::HitTest(int x, int y)
{
	double wid = mRestartImage->GetWidth();
	double hit = mRestartImage->GetHeight();

	// Make x and y relative to the top-left corner of the bitmap image
	// Subtracting the center makes x, y relative to the image center
	// Adding half the size makes x, y relative to theimage top corner
	double testX = x - GetX() + wid / 2;
	double testY = y - GetY() + hit / 2;

	// Test to see if x, y are in the image
	if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
	{
		// We are outside the image
		return false;
	}

	// Test to see if x, y are in the drawn part of the image
	auto format = mRestartImage->GetPixelFormat();
	if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
	{
		// This image has an alpha map, which implements the 
		// transparency. If so, we should check to see if we
		// clicked on a pixel where alpha is not zero, meaning
		// the pixel shows on the screen.
		Color color;
		mRestartImage->GetPixel((int)testX, (int)testY, &color);
		return color.GetAlpha() != 0;
	}
	else {
		return true;
	}
}