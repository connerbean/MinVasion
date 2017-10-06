#include "stdafx.h"
#include "Item.h"

using namespace std;
using namespace Gdiplus;

CItem::CItem(CGame *game) : mGame(game)
{
}


CItem::~CItem()
{
}


/**  Test to see if we hit this object with a mouse.
* \param x X position to test
* \param y Y position to test
* \return true if hit.
*/
bool CItem::HitTest(int x, int y)
{
	// Simple manhattan distance 
	return true;
}

/**
*  Draw our tile
* \param graphics The graphics context to draw on
*/
void CItem::Draw(Gdiplus::Graphics *graphics)
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

void CItem::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	mX = node->GetAttributeIntValue(L"x", 0);
	mY = node->GetAttributeIntValue(L"y", 0);
	mZoning = (CTile::Zonings)node->GetAttributeIntValue(L"zoning", 0);
}*/

/// The directory containing the file images
const std::wstring CItem::ImagesDirectory = L"images/";

/**
*  Set the image file to draw
* \param file The base filename. Blank files are allowed
*/
void CItem::SetImage(const std::wstring &file)
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