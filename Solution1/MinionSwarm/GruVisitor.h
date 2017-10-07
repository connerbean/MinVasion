/**
 * \file GruVisitor.h
 *
 * \author Matthew May
 *
 * This Class implements a Gru Visitor
 */

#pragma once
#include "ItemVisitor.h"


/**
 * Gru Visitor
 */
class CGruVisitor : public CItemVisitor
{
public:
	/// Constructor
	CGruVisitor();
	/// Destructor
	~CGruVisitor();

	/// Vistor Function
	///\param gru Is the Gru Type
	void VisitGru(CGru *gru);
};

