/**
 * \file CharacterVisitor.h
 *
 * \author Collin Dillinger
 *
 * Item visitor base class.
 */

#pragma once

 // Forward references to all item types
class CCharacterMinion;
class CCharacterGru;
class CCharacterVillain;

/** Item visitor base class */
class CCharacterVisitor
{
public:
	CCharacterVisitor();
	virtual ~CCharacterVisitor();

	/** Visit a CCharacterMinion object
	 * \param minion Minion we are visiting */
	virtual void VisitMinion(CCharacterMinion *minion) {}

	/** Visit a CCharacterGru object
	 * \param gru Gru we are visiting */
	virtual void VisitGru(CCharacterGru *gru) {}

	/** Visit a CCharacterVillain object
	 * \param villain Villain we are visiting */
	virtual void VisitVillain(CCharacterVillain *villain) {}
};

