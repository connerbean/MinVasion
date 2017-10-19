/**
 * \file VillainCollector.h
 *
 * \author Matthew May
 *
 * Collects villains
 */


#pragma once
#include "CharacterVisitor.h"
#include <vector>


/**
 * Villain Visitor
 */
class CVillainCollector : public CCharacterVisitor
{
public:
	/// Constructor
	CVillainCollector();

	/// Destructor
	~CVillainCollector();

	/// Visitor Function
	/// \param villian The visiting villain
	void VisitVillain(CCharacterVillain *villain);

	std::vector<CCharacterVillain*> Retrieve() { return mVillains; }

private:
	std::vector<CCharacterVillain*> mVillains; ///< Vector of all villains visited in the game
};

