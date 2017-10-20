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

	
	/// \param villain The visiting villain
	void VisitVillain(CCharacterVillain *villain);

	/**
	* Retrieve function 
	* \returns the information from the villians vector
	*/
	std::vector<CCharacterVillain*> Retrieve() { return mVillains; }

private:
	std::vector<CCharacterVillain*> mVillains; ///< Vector of all villains visited in the game
};

