#pragma once
#include "Character.h"
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

	bool IsDraggable() override { return true; }

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CCharacterVisitor *visitor) override { visitor->VisitGru(this); }

private:
    // Poiner to item images
    std::unique_ptr<Gdiplus::Bitmap> mGruImage;

};