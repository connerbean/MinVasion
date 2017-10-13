#include "stdafx.h"
#include "Character.h"
#include "Game.h"

using namespace std;
using namespace Gdiplus;

CCharacter::CCharacter(CGame *game) : mGame(game)
{
}


CCharacter::~CCharacter()
{
}


/**  Test to see if we hit this object with a mouse.
* \param x X position to test
* \param y Y position to test
* \return true if hit.
*/
bool CCharacter::HitTest(int x, int y)
{
	double wid = mItemImage->GetWidth();
	double hit = mItemImage->GetHeight();

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
	auto format = mItemImage->GetPixelFormat();
	if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
	{
		// This image has an alpha map, which implements the 
		// transparency. If so, we should check to see if we
		// clicked on a pixel where alpha is not zero, meaning
		// the pixel shows on the screen.
		Color color;
		mItemImage->GetPixel((int)testX, (int)testY, &color);
		return color.GetAlpha() != 0;
	}
	else {
		return true;
	}
}

/**
*  Draw our tile
* \param graphics The graphics context to draw on
*/
void CCharacter::Draw(Gdiplus::Graphics *graphics)
{
	if (mItemImage != nullptr)
	{
		int wid = mItemImage->GetWidth();
		int hit = mItemImage->GetHeight();

		graphics->DrawImage(mItemImage.get(),
			mX, mY - hit,
			wid, hit);
	}

}

/**
* brief Load the attributes for an item node.
*
* This is the  base class version that loads the attributes
* common to all items. Override this to load custom attributes
* for specific items.
*
* \param node The Xml node we are loading the item from

void CCharacter::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	mX = node->GetAttributeIntValue(L"x", 0);
	mY = node->GetAttributeIntValue(L"y", 0);
	mZoning = (CTile::Zonings)node->GetAttributeIntValue(L"zoning", 0);
}*/

/// The directory containing the file images
const std::wstring CCharacter::ImagesDirectory = L"images/";

/**
*  Set the image file to draw
* \param file The base filename. Blank files are allowed
*/
void CCharacter::SetImage(const std::wstring &file)
{
	if (!file.empty())
	{
		wstring filename = ImagesDirectory + file;
		mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
		if (mItemImage->GetLastStatus() != Ok)
		{
			wstring msg(L"Failed to open ");
			msg += filename;
			AfxMessageBox(msg.c_str());
			return;
		}
	}
	else
	{
		mItemImage.release();
	}

	mFile = file;
}


/**
 * Constrains the Item to the board
 * \param x Location
 * \param y Location
 */
void CCharacter::Constraints(int x, int y)
{

	if (x >= mMax)
	{
		mX = mMax;
	}
	if (x <= mMin)
	{
		mX = mMin;
	}
	if (y >= mMax)
	{
		mY = mMax;
	}
	if (y <= mMin)
	{
		mY = mMin;
	}

}