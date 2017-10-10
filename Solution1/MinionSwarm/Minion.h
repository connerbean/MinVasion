#pragma once

#include "Item.h"
class CMinion : public CItem
{
public:
    CMinion(CGame *game);

    /// Default constructor (disabled)
    CMinion() = delete;

    /// Copy constructor (disabled)
    CMinion(const CMinion &) = delete;

    // Virtual destructor
    virtual  ~CMinion();

	// Draws graphical images
	virtual void Draw(Gdiplus::Graphics * graphics);

	// Detects if two images overlap
	bool HitTest(int x, int y);

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor *visitor) override { visitor->VisitMinion(this); }

private:
	// Poiner to item images
	std::unique_ptr<Gdiplus::Bitmap> mMinionImage;
};