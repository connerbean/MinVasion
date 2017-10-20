/**
 * \file CharacterMinion.h
 *
 * \author Conner Bean
 *
 * Minion class used to draw and update
 * Stuart, Jerry, and Mutant minions
 */

#pragma once

#include "Character.h"
#include "GruVisitor.h"
#include "Vector.h"


/**
 * Character Minion class in character
 */
class CCharacterMinion : public CCharacter
{
public:

	/** Constructor for minion
	* \param game The game the minion is in
	* \param name The filename for the minion image
	* \param scoreValue the value attached to minion
	*/
    CCharacterMinion(CGame *game, const wstring name, int scoreValue, int speed);

    /// Default constructor (disabled)
    CCharacterMinion() = delete;

    /// Copy constructor (disabled)
    CCharacterMinion(const CCharacterMinion &) = delete;

    // Virtual destructor
    virtual  ~CCharacterMinion();

	// Draws graphical images
	virtual void Draw(Gdiplus::Graphics * graphics);

	// Detects if two images overlap
	bool HitTest(int x, int y);

	/**  Constrain the Items to MAX/MIN */
	virtual void Constraints();

	/// Set's minions to undraggable
	/// \return bool false 
	bool IsDraggable() override { return false; }

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CCharacterVisitor *visitor) override { visitor->VisitMinion(this); }

	/**
	* Update function that 
	* \param elapsed the time that passes
	**/
	void Update(double elapsed);

	/** Gets the score value of this minion
	* \returns the score for each villian
	*/
	int GetScoreValue() { return mScoreValue; }

	CVector MakeVector()
	{
		CVector mMinionVector = *make_shared<CVector>(GetX(), GetY());
		return mMinionVector;
	}
private:
	/// Poiner to item images
	std::unique_ptr<Gdiplus::Bitmap> mMinionImage;

	int mScoreValue; ///< Individual score value for the minions

	int mSpeed; ///< Individual speed value for the minions

	/// Speed that gets added to the minions location
	int mRunX = 0;

	/// Speed that the minion runs in the Y direction
	int mRunY = 0;

	/// The position of the minion
	CVector mMinP;
	/// Max X Position
	int mMax = 500;
	/// Min X Position
	int mMin = -500;
};