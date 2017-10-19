/**
 * \file VillainCollector.cpp
 *
 * \author Matthew May
 */

#include "stdafx.h"
#include "VillainCollector.h"
#include "CharacterVillain.h"


/**
 * Constructor
 */
CVillainCollector::CVillainCollector()
{
}


/**
 * Destructor
 */
CVillainCollector::~CVillainCollector()
{
	mVillains.clear();
}

void CVillainCollector::VisitVillain(CCharacterVillain *villain)
{
	mVillains.push_back(villain);
}