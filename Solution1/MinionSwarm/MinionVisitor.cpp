/**
 * \file MinionVisitor.cpp
 *
 * \author Matthew May
 */

#include "stdafx.h"
#include "MinionVisitor.h"
#include "CharacterMinion.h"


/**
 * Constructor
 * \param requestor The minion who requested this visitor
 */
CMinionVisitor::CMinionVisitor(CCharacterMinion *requestor)
{
	mRequestor = requestor;
}

/**
 * Destructor
 */
CMinionVisitor::~CMinionVisitor()
{
}


void CMinionVisitor::VisitMinion(CCharacterMinion *minion)
{

}