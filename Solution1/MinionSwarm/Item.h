/**
* \file Item.h
*
* \author Matthew Rhodes
*
* \ Base class for any Item in our game
*
*/

#pragma once
#include <string>
#include <memory>
//#include "XmlNode.h"
#include "ItemVisitor.h"
#include "Game.h"


class CItem
{
public:

	/** The directory were the images are stored */
	static const std::wstring ImagesDirectory;

	///  Default constructor (disabled)
	CItem() = delete;

	virtual ~CItem();

	void SetImage(const std::wstring &file);

	/**  Get the file name for this tile image
	* \returns Filename or blank if none */
	std::wstring GetFile() { return mFile; }

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor *visitor) = 0;

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

	/**  Draw this item
	* \param graphics The graphics context to draw on */
	virtual void Draw(Gdiplus::Graphics *graphics);

	/**  Test this item to see if it has been clicked on
	* \param x X location on the aquarium to test
	* \param y Y location on the aquarium to test
	* \return true if clicked on */
	virtual bool HitTest(int x, int y);

	//virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node);
	//virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	///  Handle updates for animation
	/// \param elapsed The time since the last update
	virtual void Update(double elapsed) {}

	///  Get the city this item is in
	/// \returns City pointer
	CGame *GetGame() { return mGame; }
	
	///  Copy constructor (disabled)
	CItem(const CItem &) = delete;
protected:
	CItem(CGame *game);

private:
	CGame *mGame;
	int mX = 0;
	int mY = 0;
	std::wstring mFile;

	/// The image of this tile
	std::unique_ptr<Gdiplus::Bitmap> mItemImage;
};

