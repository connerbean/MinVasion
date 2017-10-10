#include "stdafx.h"
#include "RestartSide.h"

/// Item filename 
const wstring GruImageName = L"images/new-game.png";

/**
* Draw this item
* \param graphics Graphics device to draw on
*/
void CRestartSide::Draw(Gdiplus::Graphics *graphics)
{
	double wid = mRestartImage->GetWidth();
	double hit = mRestartImage->GetHeight();
	graphics->DrawImage(mRestartImage.get(),
		float(0), float(0),
		float(mRestartImage->GetWidth()), float(mRestartImage->GetHeight()));
}


CRestartSide::~CRestartSide()
{
}

/**
* Constructor
* \param game Game this item is a member of
*/
CRestartSide::CRestartSide()
{
	mRestartImage = unique_ptr<Bitmap>(Bitmap::FromFile(GruImageName.c_str()));
	if (mRestartImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += GruImageName;
		AfxMessageBox(msg.c_str());
	}
}