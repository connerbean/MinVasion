/**
 * \file MinionVisitor.h
 *
 * \author Matthew May
 *
 * This Class implements an Minion Visitor
 */

#pragma once
#include "ItemVisitor.h"


/**
 * Minion visitor
 */
class CMinionVisitor : public CItemVisitor
{
public:
	/// Constructor
	CMinionVisitor();
	/// Destructor
	~CMinionVisitor();

	/// Visitor Function
	/// \param minion IS the Minion type
	void VisitMinion(CMinion *minion);

private:

};
