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
	* \param item The item we are giving constraints */
	virtual void Constraints(shared_ptr<CCharacter>item) {};

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CCharacterVisitor *visitor) = 0;

	/** Gets whether this item is draggable
	 * \return true if draggable, otherwise false*/
	virtual bool IsDraggable() = 0;

	
protected:
	CCharacter(CGame *game);

	/// The game this character is contained in
	CGame *mGame;
private:
	



};

