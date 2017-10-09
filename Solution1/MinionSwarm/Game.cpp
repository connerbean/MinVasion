#include "stdafx.h"
#include "Game.h"
#include "Item.h"

CGame::CGame()
{
}


CGame::~CGame()
{
}

/**
* Add an item to the aquarium
* \param item New item to add
*/
void CGame::Add(std::shared_ptr<CItem> item)
{
	mItems.push_back(item);
}

/**
* Finds and deletes the selected item
*/
void CGame::Delete(std::shared_ptr<CItem> item)
{
	auto loc = find(begin(mItems), end(mItems), item);
	if (loc != end(mItems))
	{
		mItems.erase(loc);
	}
}

void CGame::Translation(CPoint point)
{
	point.x = (point.x - mXOffset) / mScale;
	point.y = (point.y - mYOffset) / mScale;
}

/**
* Test to see if things in the aquarium have been hit
*/
std::shared_ptr<CItem> CGame::HitTest(int x, int y)
{
	x = (x - mXOffset) / mScale;
	y = (y - mYOffset) / mScale;
 	for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}

	return  nullptr;
}