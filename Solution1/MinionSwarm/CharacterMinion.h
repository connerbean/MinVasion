#pragma once

#include "Character.h"
class CCharacterMinion : public CCharacter
{
public:
    CCharacterMinion(CGame *game);

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

	bool IsDraggable() override { return false; }

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CCharacterVisitor *visitor) override { visitor->VisitMinion(this); }

private:
	// Poiner to item images
	std::unique_ptr<Gdiplus::Bitmap> mMinionImage;
};