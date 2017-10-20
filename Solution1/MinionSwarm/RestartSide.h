/**
* \file RestartSide.h
*
* \author Matthew Rhodes
*
*  That holds the Reset button
*/
#pragma once
#include "Character.h"
#include "Element.h"

/**
* Class definition for the Restart button that is 
* extended from the element class
*/
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
	/** returns true because the item we are clicking
	* \returns true because this is a button
	*/
	bool IsButton() { return true; }
	
private:
	/// Pointer to buttom item image
	std::unique_ptr<Gdiplus::Bitmap> mRestartImage;
};