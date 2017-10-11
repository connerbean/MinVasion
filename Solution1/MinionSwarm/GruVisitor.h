/**
 * \file GruVisitor.h
 *
 * \author Matthew May
 *
 * This Class implements a Gru Visitor
 */

#pragma once
#include "CharacterVisitor.h"


/**
 * Gru Visitor
 */
class CGruVisitor : public CCharacterVisitor
{
public:
	/// Constructor
	CGruVisitor();
	/// Destructor
	~CGruVisitor();

	/// Vistor Function
	///\param gru Is the Gru Type
	void VisitGru(CCharacterGru *gru);
};

