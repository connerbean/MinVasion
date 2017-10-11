/**
 * \file VillainVisitor.h
 *
 * \author Matthew May
 *
 * This class implements a villian visitor
 */


#pragma once
#include "CharacterVisitor.h"


/**
 * Villain Visitor
 */
class CVillainVisitor : public CCharacterVisitor
{
public:
	/// Constructor
	CVillainVisitor();

	/// Destructor
	~CVillainVisitor();

	///Visitor Function
	///\param villian Is the villain type
	void VisitVillain(CCharacterVillain *villain);
};

