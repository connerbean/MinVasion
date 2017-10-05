/**
 * \file Villain.h
 *
 * \author Collin Dillinger
 *
 * Class that implements a villain character
 */

#pragma once

//#include "Item.h" // TODO: uncomment me when CItem is implemented

// TODO: delete the following 3 lines when CItem and CGame are implemented
#include "ItemVisitor.h"
class CGame;
class CItem { public: virtual void Accept(CItemVisitor *visitor) = 0; protected: CItem(CGame *game) {} };

/**
 * A Villain character
 */
class CVillain : public CItem
{
public:
	CVillain(CGame *game);

	///  Default constructor (disabled)
	CVillain() = delete;

	///  Copy constructor (disabled)
	CVillain(const CVillain &) = delete;

	virtual ~CVillain();

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitVillain(this); }
};

