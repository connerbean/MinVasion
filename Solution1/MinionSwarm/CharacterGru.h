#pragma once
#include "Character.h"
#include "Vector.h"
#include <memory>

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

	/**  Constrain the Items to MAX/MIN
	* \param item The item we are giving constraints */
	virtual void Constraints(shared_ptr<CCharacter> item);

	/// Overrides the IsDraggable function
	bool IsDraggable() override { return true; }

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CCharacterVisitor *visitor) override { visitor->VisitGru(this); }

	auto GetmP()
	{ 
		mP = make_shared<CVector>(GetX(), GetY());
		return mP;
	}

private:
    // Poiner to item images
    std::unique_ptr<Gdiplus::Bitmap> mGruImage;

	std::shared_ptr<CVector> mP;

	/// Max X Position
	int mMax = 500;
	/// Min X Position
	int mMin = -500;

};