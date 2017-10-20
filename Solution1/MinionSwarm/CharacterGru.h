/**
* \file Character.h
*
* \author Matthew Rhodes
*
*  Class that makes Gru and all Gru related aspects
*/
#pragma once
#include "Character.h"
#include "Vector.h"
#include <memory>

/**
* Class definition for Gru he is what the 
* minions are flocking to
*/
class CCharacterGru : public CCharacter
{
public:
    CCharacterGru(CGame *game);

    /// Default constructor (disabled)
    CCharacterGru() = delete;

    /// Copy constructor (disabled)
    CCharacterGru(const CCharacterGru &) = delete;

    // Virtual destructor
    virtual  ~CCharacterGru();

    // Draws graphical images
    virtual void Draw(Gdiplus::Graphics * graphics);

    // Detects if two images overlap
    bool HitTest(int x, int y);

	/**  Constrain the Items to MAX/MIN */
	virtual void Constraints();

	/** Overrides the IsDraggable function
	* \returns true because Gru is the 
	* only draggable object
	*/
	bool IsDraggable() override { return true; }

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CCharacterVisitor *visitor) override { visitor->VisitGru(this); }

	/** Gets Gru's location for the minions
	* \returns mP Gru's location
	*/ 
	auto GetmP()
	{ 
		mP = make_shared<CVector>(GetX(), GetY());
		return mP;
	}

private:
    /// Poiner to item images
    std::unique_ptr<Gdiplus::Bitmap> mGruImage;

	/// Grus location that the minions need
	std::shared_ptr<CVector> mP;

};