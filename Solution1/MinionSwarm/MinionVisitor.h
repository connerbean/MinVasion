/**
 * \file MinionVisitor.h
 *
 * \author Matthew May
 *
 * This Class implements an Minion Visitor
 */

#pragma once
#include "CharacterVisitor.h"
#include <vector>

/**
 * Minion visitor
 */
class CMinionVisitor : public CCharacterVisitor
{
public:
	/// Constructor
	CMinionVisitor(CCharacterMinion *requestor);
	/// Destructor
	~CMinionVisitor();

	/// Visitor Function
	/// \param minion IS the Minion type
	void VisitMinion(CCharacterMinion *minion)
	{
		mMinions.push_back(minion);
	}

	auto GetList() { return mMinions; }

private:

	std::vector<CCharacterMinion*> mMinions;
};
