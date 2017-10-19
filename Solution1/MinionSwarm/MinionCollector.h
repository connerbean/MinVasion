/**
 * \file MinionCollector.h
 *
 * \author Collin Dillinger
 *
 * Collects minions
 */


#pragma once
#include "CharacterVisitor.h"
#include <vector>


/**
 * Villain Visitor
 */
class CMinionCollector : public CCharacterVisitor
{
public:
	/// Constructor
	CMinionCollector();

	/// Destructor
	~CMinionCollector();

	/// Visitor Function
	///\param minion The visiting minion
	void VisitMinion(CCharacterMinion *minion);

	std::vector<CCharacterMinion*> Retrieve() { return mMinions; }

private:
	std::vector<CCharacterMinion*> mMinions; ///< Vector of all minions visited
};

