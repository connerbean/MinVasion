/**
* \file Character.h
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
#include "CharacterVisitor.h"
#include "Game.h"


class CCharacter
{
public:

	/** The directory were the images are stored */
	static const std::wstring ImagesDirectory;

	///  Default constructor (disabled)
	CCharacter() = delete;

	virtual ~CCharacter();

	void SetImage(const std::wstring &file);

	/**  Get the file name for this tile image
	* \returns Filename or blank if none */
	std::wstring GetFile() { return mFile; }

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CCharacterVisitor *visitor) = 0;

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
	virtual bool HitTest(int x, int y) = 0;

	/** Gets whether this item is draggable
	 * \return true if draggable, otherwise false*/
	virtual bool IsDraggable() = 0;

	/** Gets whether this item is a button or not
	*  \return false because most items are not a button
	*/
	virtual bool IsButton() { return false; }
	///  Handle updates for animation
	/// \param elapsed The time since the last update
	virtual void Update(double elapsed) {}

	///  Get the city this item is in
	/// \returns City pointer
	//CGame *GetGame() { return mGame; }
	
	///  Copy constructor (disabled)
	CCharacter(const CCharacter &) = delete;
protected:
	CCharacter(CGame *game);

private:
	CGame *mGame;
	/**
	* X coordinate
	*/
	int mX = 0;

	/**
	* Y coordinate
	*/
	int mY = 0;

	/**
	* File name for image
	*/
	std::wstring mFile;

	/// The image of this tile
	std::unique_ptr<Gdiplus::Bitmap> mItemImage;
};

