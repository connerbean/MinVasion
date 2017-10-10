/**
 * \file Villain.h
 *
 * \author Collin Dillinger
 *
 * Class that implements a villain character
 */

#pragma once

#include "Item.h" 

/**
 * A Villain character
 */
class CVillain : public CItem
{
public:
	/// Types of villain
	enum Types { Arya, Juicer, Pokeball };

	CVillain(CGame *game, Types villainType);

	///  Default constructor (disabled)
	CVillain() = delete;

	///  Copy constructor (disabled)
	CVillain(const CVillain &) = delete;

	virtual ~CVillain();

	virtual void Draw(Gdiplus::Graphics * graphics) override;

	bool HitTest(int x, int y) override;

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor *visitor) override { visitor->VisitVillain(this); }

private:
	void LoadImage(std::wstring name);

	/// The type of villain
	Types mType;

	/// The point multiplier for this villain
	int mMultiplier = 1;

	/// Pointer to villain image
	std::unique_ptr<Gdiplus::Bitmap> mVillainImage;
};

