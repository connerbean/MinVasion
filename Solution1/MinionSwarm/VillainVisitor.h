/**
 * \file VillainVisitor.h
 *
 * \author Matthew May
 *
 * This class implements a villian visitor
 */


#pragma once
#include "ItemVisitor.h"


/**
 * Villain Visitor
 */
class CVillainVisitor : public CItemVisitor
{
public:
	/// Constructor
	CVillainVisitor();

	/// Destructor
	~CVillainVisitor();

	///Visitor Function
	///\param villian Is the villain type
	void VisitVillain(CVillain *villain);
};

