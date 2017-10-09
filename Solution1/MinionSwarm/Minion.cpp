#include "stdafx.h"
#include <string>
#include "Minion.h"

using namespace Gdiplus;
using namespace std;

/// Item filename 
const wstring MinionImageName = L"images/dave.png";

/** Constructor
* \param game The Game this is a member of
*/
CMinion::CMinion(CGame *game) : CItem(game)
{
	mMinionImage = unique_ptr<Bitmap>(Bitmap::FromFile(MinionImageName.c_str()));
	if (mMinionImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += MinionImageName;
		AfxMessageBox(msg.c_str());
	}
}

/**
* Destructor
*/
CMinion::~CMinion()
{
}

/**
* Draw this item
* \param graphics Graphics device to draw on
*/
void CMinion::Draw(Gdiplus::Graphics *graphics)
{
	double wid = mMinionImage->GetWidth();
	double hit = mMinionImage->GetHeight();
	graphics->DrawImage(mMinionImage.get(),
		float(GetX() - wid / 2), float(GetY() - hit / 2),
		mMinionImage->GetWidth(), mMinionImage->GetHeight());
}