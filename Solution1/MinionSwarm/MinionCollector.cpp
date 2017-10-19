/**
 * \file MinionCollector.cpp
 *
 * \author Collin Dillinger
 */

#include "stdafx.h"
#include "MinionCollector.h"
#include "CharacterMinion.h"


/**
 * Constructor
 */
CMinionCollector::CMinionCollector()
{
}


/**
 * Destructor
 */
CMinionCollector::~CMinionCollector()
{
	mMinions.clear();
}

void CMinionCollector::VisitMinion(CCharacterMinion *minion)
{
	mMinions.push_back(minion);
}