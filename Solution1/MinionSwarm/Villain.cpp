/**
 * \file Villain.cpp
 *
 * \author Collin Dillinger
 */

#include "stdafx.h"
#include "Villain.h"

using namespace std;

/// Image for Arya
const wstring AryaImage = L"arya.png";

/// Image for Juicer
const wstring JuicerImage = L"juicer.png";

/// Image for Pokeball
const wstring PokeballImage = L"pokeball.png";

/** Constructor.
 * \param city The game this is a member of
 * \param villainType The type of villain this object will be
 */
CVillain::CVillain(CGame * game, Types villainType) : CItem(game)
{
	if (villainType == Types::Arya)
	{
		LoadImage(AryaImage);
		mMultiplier = 1;
	}
	else if (villainType == Types::Juicer)
	{
		LoadImage(JuicerImage);
		mMultiplier = 2;
	}
	else if (villainType == Types::Pokeball)
	{
		LoadImage(PokeballImage);
		mMultiplier = 3;
	}
}

/**
 *  Destructor.
 */
CVillain::~CVillain()
{
}

/** Draw this item
 * \param graphics The graphics context to draw on */
void CVillain::Draw(Gdiplus::Graphics *graphics)
{
	double wid = mVillainImage->GetWidth();
	double hit = mVillainImage->GetHeight();
	graphics->DrawImage(mVillainImage.get(),
		float(GetX() - wid / 2), float(GetY() - hit / 2),
		float(mVillainImage->GetWidth()), float(mVillainImage->GetHeight()));
}

/**
 * Test to see if we hit this object with a mouse.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CVillain::HitTest(int x, int y)
{
	double wid = mVillainImage->GetWidth();
	double hit = mVillainImage->GetHeight();

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
	auto format = mVillainImage->GetPixelFormat();
	if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
	{
		// This image has an alpha map, which implements the 
		// transparency. If so, we should check to see if we
		// clicked on a pixel where alpha is not zero, meaning
		// the pixel shows on the screen.
		Color color;
		mVillainImage->GetPixel((int)testX, (int)testY, &color);
		return color.GetAlpha() != 0;
	}
	else {
		return true;
	}
}


/**
 * Load an image into a bitmap
 * \param name Filename to load from
 */
void CVillain::LoadImage(std::wstring name)
{
	wstring filename = ImagesDirectory + name;
	mVillainImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mVillainImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}
}
