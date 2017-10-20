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
CCharacterMinion::CCharacterMinion(CGame *game, const wstring name, int scoreValue, int speed) : CCharacter(game)
{
	mMinionImage = unique_ptr<Bitmap>(Bitmap::FromFile(wstring(name.begin(),name.end()).c_str()));
	if (mMinionImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += MinionImageName;
		AfxMessageBox(msg.c_str());
	}
	mScoreValue = scoreValue;
	mSpeed = speed;
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
		float(GetX() - wid / 2)+ mRunX, float(GetY() - hit / 2) + mRunY,
		float(mMinionImage->GetWidth()), float(mMinionImage->GetHeight()));
}

void CCharacterMinion::Update(double elapsed)
{
	//SetSpeed(5);
	CElement::Update(elapsed);

	CMinionVisitor minionVisitor(this);
	mGame->Accept(&minionVisitor);

	CGruVisitor gruVisitor;
	mGame->Accept(&gruVisitor);

	CVector mGruP = *gruVisitor.GetLocation();
	CVector mMinP = *make_shared<CVector>(GetX(), GetY());
	CVector GruV = mGruP - mMinP;

	if (GruV.Length() > 0)
	{
		GruV.Normalize();
	}

	std::vector<CCharacterMinion*> mMinionList = minionVisitor.GetList();

	CVector cohesion;
	CVector alignment;
	CVector seperation;
	int i = 0;
	double closest = 0;
	for (auto minion : mMinionList)
	{
		cohesion += MakeVector(minion);
		i++;

		if (mMinP.Distance(MakeVector(minion)) <= 200)
		{
			alignment += (mGruP - MakeVector(minion)).Normalize();
		}

		if (mMinP.Distance(MakeVector(minion)) > 0)
		{
			if (closest == 0 || closest > mMinP.Distance(MakeVector(minion)))
			{
				closest = mMinP.Distance(MakeVector(minion));
				seperation = ((MakeVector(minion) - mMinP) * -1);
			}
		}
	}
	CVector cv = ((cohesion / i) - mGruP).Normalize();
	CVector av = alignment.Normalize();
	CVector sv = seperation.Normalize();
	if (mGame->IsGameOver())
	{
		GruV.SetX(0);
		GruV.SetY(0);
	}

	CVector mV = cv * 1 + av * 5 + GruV * 10;
	mV.Normalize();
	mV *= mSpeed;
	CVector newP = mMinP + (mV * elapsed);
	SetLocation(newP.X(), newP.Y());
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

/**
* Constrains the Item to the board
*/
void CCharacterMinion::Constraints()
{
	const int height = mMinionImage->GetHeight() / 2;
	const int width = mMinionImage->GetWidth() / 2;

	auto x = GetX();
	auto y = GetY();

	if ((x + width) > mMax)
	{
		mMax -= width;
		x = mMax;
	}
	else if ((x - width) < mMin)
	{
		mMin += width;
		x = mMin;
	}
	if ((y + height) > mMax)
	{
		mMax -= height;
		y = mMax;
	}
	else if ((y - height) <= mMin)
	{
		mMin += height;
		y = mMin;
	}
	SetLocation(x, y);

	mMax = 500;
	mMin = -500;
}