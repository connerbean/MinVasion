/**
* \file Character.h
*
* \author Matthew Rhodes
*
* Base class for any Item in our game
*
*/

#pragma once
#include <string>
#include <memory>
#include "CharacterVisitor.h"
#include "Element.h"


class CCharacter : public CElement
{
public:
	///  Default constructor (disabled)
	CCharacter() = delete;

	///  Copy constructor (disabled)
	CCharacter(const CCharacter &) = delete;

	virtual ~CCharacter();

	/**  Constrain the Items to MAX/MIN
	* \param x X location
	* \param y Y location */
	void Constraints(shared_ptr<CCharacter>item);

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CCharacterVisitor *visitor) = 0;

	/** Gets whether this item is draggable
	 * \return true if draggable, otherwise false*/
	virtual bool IsDraggable() = 0;

	///  Get the city this item is in
	/// \returns City pointer
	CGame *GetGame() { return mGame; }
	
protected:
	CCharacter(CGame *game);

private:
	/// The game this character is contained in
	CGame *mGame;

	/// Max X Position
	int mMax = 500;
	/// Min X Position
	int mMin = -500;

};

