/**
 * \file CharacterVillain.h
 *
 * \author Collin Dillinger
 *
 * Class that implements a villain character
 */

#pragma once

#include "Character.h" 

/**
 * A Villain character
 */
class CCharacterVillain : public CCharacter
{
public:
	/// Types of villain
	enum Types { Arya, Juicer, Pokeball };

	CCharacterVillain(CGame *game, Types villainType);

	///  Default constructor (disabled)
	CCharacterVillain() = delete;

	///  Copy constructor (disabled)
	CCharacterVillain(const CCharacterVillain &) = delete;

	virtual ~CCharacterVillain();

	virtual void Draw(Gdiplus::Graphics * graphics) override;

	float DrawAt(Gdiplus::Graphics * graphics, float centerX, float topY);

	bool HitTest(int x, int y) override;

	/** Gets whether Gru is draggable
	 * \return true */
	bool IsDraggable() override { return false; }

	/** Adds points to this villain
	 * \param baseScore The base score of the minion this gor points from
	 */
	void AddPoints(int baseScore) { mPointsAccumulated += baseScore * mMultiplier; }

	/** Gets the total number of points this villain has accumulated
	 * \return the number of points
	 */
	int GetPoints() { return mPointsAccumulated; }

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CCharacterVisitor *visitor) override { visitor->VisitVillain(this); }

private:
	void LoadImage(std::wstring name);

	/// The type of villain
	Types mType;

	/// The point multiplier for this villain
	int mMultiplier = 1;

	/// Number of points this villain has accumulated
	int mPointsAccumulated = 0;

	/// Pointer to villain image
	std::unique_ptr<Gdiplus::Bitmap> mVillainImage;
};

