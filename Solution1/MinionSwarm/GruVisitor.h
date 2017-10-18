/**
 * \file GruVisitor.h
 *
 * \author Matthew May
 *
 * This Class implements a Gru Visitor
 */

#pragma once
#include "CharacterVisitor.h"
#include "Vector.h"
#include <memory>
#include "CharacterGru.h"

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

	auto GetLocation() { return Location; };

	/// Vistor Function
	///\param gru Is the Gru Type
	void VisitGru(CCharacterGru *gru)
	{
		Location = gru->GetmP();
	}

private:
	std::shared_ptr<CVector> Location;
};

