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

	/** Gets a vector containing Gru's location
	 * \return a pointer to the vector of Gru's location
	 */
	auto GetLocation() { return mLocation; };

	/// Vistor Function
	/// \param gru Is the Gru Type
	void VisitGru(CCharacterGru *gru)
	{
		mLocation = gru->GetmP();
	}

private:
	std::shared_ptr<CVector> mLocation; ///< A pointer to the vector containing Gru's location
};

