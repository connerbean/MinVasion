#pragma once
#include "Item.h"
class CGru : public CItem
{
public:
    CGru(CGame *game);

    /// Default constructor (disabled)
    CGru() = delete;

    /// Copy constructor (disabled)
    CGru(const CGru &) = delete;

    // Virtual destructor
    virtual  ~CGru();

    // Draws graphical images
    virtual void Draw(Gdiplus::Graphics * graphics);

    // Detects if two images overlap
    bool HitTest(int x, int y);

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor *visitor) override { visitor->VisitGru(this); }

private:
    // Poiner to item images
    std::unique_ptr<Gdiplus::Bitmap> mGruImage;

};