/**
 * \file ItemVisitor.h
 *
 * \author Collin Dillinger
 *
 * Item visitor base class.
 */

#pragma once

 // Forward references to all item types
class CMinion;
class CGru;
class CVillain;

/** Item visitor base class */
class CItemVisitor
{
public:
	CItemVisitor();
	virtual ~CItemVisitor();

	/** Visit a CMinion object
	 * \param minion Minion we are visiting */
	virtual void VisitMinion(CMinion *minion) {}

	/** Visit a CGru object
	 * \param gru Gru we are visiting */
	virtual void VisitGru(CGru *gru) {}

	/** Visit a CVillain object
	 * \param villain Villain we are visiting */
	virtual void VisitVillain(CVillain *villain) {}
};

