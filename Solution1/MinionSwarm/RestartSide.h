#pragma once
#include "Character.h"
#include "Element.h"

class CRestartSide : public CElement
{
public:
	// Draws graphical images
	virtual void Draw(Gdiplus::Graphics * graphics);

	CRestartSide();

	/// Copy constructor (disabled)
	CRestartSide(const CRestartSide &) = delete;

	virtual ~CRestartSide();

	// Detects if two images overlap
	bool HitTest(int x, int y);

	bool IsButton() { return true; }


private:
	// Pointer to buttom item
	std::unique_ptr<Gdiplus::Bitmap> mRestartImage;
};
