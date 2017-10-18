/**
 * \file CharacterMinion.cpp
 *
 * \author Conner Bean
 */

#include "stdafx.h"
#include <string>
#include "CharacterMinion.h"
#include "Game.h"

using namespace Gdiplus;
using namespace std;

/// Item filename 
const wstring MinionImageName = L"images/dave.png";

/** Constructor
* \param game The Game this is a member of
* \param name The file name that we load for the minion image
* \param scoreValue The score associated with destroying the minion
*/
CCharacterMinion::CCharacterMinion(CGame *game, const wstring name, int scoreValue) : CCharacter(game)
{
	mMinionImage = unique_ptr<Bitmap>(Bitmap::FromFile(wstring(name.begin(),name.end()).c_str()));
	if (mMinionImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += MinionImageName;
		AfxMessageBox(msg.c_str());
	}
	mScoreValue = scoreValue;
}

/**
* Destructor
*/
CCharacterMinion::~CCharacterMinion()
{
}

/**
* Draw this item
* \param graphics Graphics device to draw on
*/
void CCharacterMinion::Draw(Gdiplus::Graphics *graphics)
{
	double wid = mMinionImage->GetWidth();
	double hit = mMinionImage->GetHeight();
	graphics->DrawImage(mMinionImage.get(),
		float(GetX() - wid / 2), float(GetY() - hit / 2),
		float(mMinionImage->GetWidth()), float(mMinionImage->GetHeight()));
}

void CCharacterMinion::Update(int elapsed)
{
	CGruVisitor visitor;
	mGame->Accept(&visitor);
	mGruLocation = visitor.GetLocation();
}

/**
* Test to see if we hit this object with a mouse.
* \param x X position to test
* \param y Y position to test
* \return true if hit.
*/
bool CCharacterMinion::HitTest(int x, int y)
{
	double wid = mMinionImage->GetWidth();
	double hit = mMinionImage->GetHeight();

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
	auto format = mMinionImage->GetPixelFormat();
	if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
	{
		// This image has an alpha map, which implements the 
		// transparency. If so, we should check to see if we
		// clicked on a pixel where alpha is not zero, meaning
		// the pixel shows on the screen.
		Color color;
		mMinionImage->GetPixel((int)testX, (int)testY, &color);
		return color.GetAlpha() != 0;
	}
	else {
		return true;
	}
}