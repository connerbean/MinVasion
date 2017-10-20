/**
 * \file CharacterGru.cpp
 *
 * \author Matthew May
 */

#include "stdafx.h"
#include <string>
#include "CharacterGru.h"

using namespace Gdiplus;
using namespace std;

/// Item filename 
const wstring GruImageName = L"images/gru.png";

/// Max X or Y Position
const int MaxVal = 500;

/// Min X or Y Position
const int MinVal = -500;

/**
* Constructor
* \param game Game this item is a member of
*/
CCharacterGru::CCharacterGru(CGame *game) : CCharacter(game)
{
    mGruImage = unique_ptr<Bitmap>(Bitmap::FromFile(GruImageName.c_str()));
    if (mGruImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += GruImageName;
        AfxMessageBox(msg.c_str());
    }
	
}

/**
* Destructor
*/
CCharacterGru::~CCharacterGru()
{
}

/**
* Draw this item
* \param graphics Graphics device to draw on
*/
void CCharacterGru::Draw(Gdiplus::Graphics *graphics)
{
    double wid = mGruImage->GetWidth();
    double hit = mGruImage->GetHeight();
    graphics->DrawImage(mGruImage.get(),
        float(GetX() - wid / 2), float(GetY() - hit / 2),
        float(mGruImage->GetWidth()), float(mGruImage->GetHeight()));
}

/**
* Test to see if we hit this object with a mouse.
* \param x X position to test
* \param y Y position to test
* \return true if hit.
*/
bool CCharacterGru::HitTest(int x, int y)
{
	double wid = mGruImage->GetWidth();
	double hit = mGruImage->GetHeight();

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
	auto format = mGruImage->GetPixelFormat();
	if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
	{
		// This image has an alpha map, which implements the 
		// transparency. If so, we should check to see if we
		// clicked on a pixel where alpha is not zero, meaning
		// the pixel shows on the screen.
		Color color;
		mGruImage->GetPixel((int)testX, (int)testY, &color);
		return color.GetAlpha() != 0;
	}
	else {
		return true;
	}
}

/**
* Constrains the Item to the board
*/
void CCharacterGru::Constraints()
{
	const int height = mGruImage->GetHeight()/2;
	const int width = mGruImage->GetWidth()/2;

	auto x = GetX();
	auto y = GetY();

	if ((x + width) > MaxVal)
	{
		x = MaxVal - width;
	}
	else if ((x - width) < MinVal)
	{
		x = MinVal + width;
	}
	if ((y + height) > MaxVal)
	{
		y = MaxVal - height;
	}
	else if ((y - height) <= MinVal)
	{
		y = MinVal + height;
	}
	SetLocation(x, y);
}