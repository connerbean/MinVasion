/**
 * \file MinionVisitor.h
 *
 * \author Matthew May
 *
 * This Class implements an Minion Visitor
 */

#pragma once
#include "CharacterVisitor.h"


/**
 * Minion visitor
 */
class CMinionVisitor : public CCharacterVisitor
{
public:
	/// Constructor
	CMinionVisitor();
	/// Destructor
	~CMinionVisitor();

	/// Visitor Function
	/// \param minion IS the Minion type
	void VisitMinion(CCharacterMinion *minion);

private:

};
