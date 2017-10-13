/**
* \file Element.h
*
* \author Collin Dillinger
*
* \ Base class for any element visible in the application
*
*/

#pragma once
#include <string>
#include <memory>
#include "Game.h"


class CElement
{
public:
	/** The directory were the images are stored */
	static const std::wstring ImagesDirectory;

	///  Default constructor
	CElement();
	
	///  Copy constructor (disabled)
	CElement(const CElement &) = delete;

	virtual ~CElement();

	void SetImage(const std::wstring &file);

	/**  Get the file name for this tile image
	* \returns Filename or blank if none */
	std::wstring GetFile() { return mFile; }

	/**  The X location of the center of the tile
	* \returns X location in pixels */
	int GetX() const { return mX; }

	/**  The Y location of the center of the tile
	* \returns Y location in pixels */
	int GetY() const { return mY; }

	/**  Set the item location
	* \param x X location
	* \param y Y location */
	void SetLocation(int x, int y) { mX = x; mY = y; }

	/**  Test this item to see if it has been clicked on
	* \param x X location on the aquarium to test
	* \param y Y location on the aquarium to test
	* \return true if clicked on */
	virtual bool HitTest(int x, int y) = 0;

	/**  Draw this item
	* \param graphics The graphics context to draw on */
	virtual void Draw(Gdiplus::Graphics *graphics);

	///  Handle updates for animation
	/// \param elapsed The time since the last update
	virtual void Update(double elapsed) {}

private:
	int mX = 0; ///< X coordinate

	int mY = 0; ///< Y coordinate

	std::wstring mFile; ///< File name for image

	/// The image of this element
	std::unique_ptr<Gdiplus::Bitmap> mItemImage;
};
