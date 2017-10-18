/**
 * \file CharacterVillain.cpp
 *
 * \author Collin Dillinger
 */

#include "stdafx.h"
#include "CharacterVillain.h"

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
CCharacterVillain::CCharacterVillain(CGame * game, Types villainType) : CCharacter(game)
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

	mType = villainType;
}

/**
 *  Destructor.
 */
CCharacterVillain::~CCharacterVillain()
{
}


/** Draw this item
 * \param graphics The graphics context to draw on */
void CCharacterVillain::Draw(Gdiplus::Graphics *graphics)
{
	REAL yLocation = 0, xLocation = 0, pointX = 0;

	if (mPointsAccumulated < 10) pointX = 585;
	else pointX = 575;

	double wid = mVillainImage->GetWidth();
	double hit = mVillainImage->GetHeight();
	graphics->DrawImage(mVillainImage.get(),
		float(GetX() - wid / 2), float(GetY() - hit / 2),
		float(mVillainImage->GetWidth()), float(mVillainImage->GetHeight()));

	
	// Code following this determines position for each 
	//  of the villains to be drawn on the scoreboard
	if (mType == Types::Arya)
	{
		yLocation = 0;
		xLocation = 530;
	}
	else if (mType == Types::Juicer)
	{
		yLocation = -450;
		xLocation = 555;
	}
	else if (mType == Types::Pokeball)
	{
		yLocation = -175;
		xLocation = 575;
	}

	graphics->DrawImage(mVillainImage.get(),
		(xLocation), yLocation,
		float(mVillainImage->GetWidth()), float(mVillainImage->GetHeight()));


	// now draw points below each image
	wstring points = to_wstring(mPointsAccumulated);
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 26);
	SolidBrush green(Color(0, 140, 0));
	graphics->DrawString(points.c_str(), -1, &font, PointF(pointX, REAL(yLocation + hit + 10)), &green);
}

/**
 * Test to see if we hit this object with a mouse.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CCharacterVillain::HitTest(int x, int y)
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
void CCharacterVillain::LoadImage(std::wstring name)
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
