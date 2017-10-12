#pragma once
#include "Character.h"
class CRestartSide : public CCharacter
{
public:
	// Draws graphical images
	virtual void Draw(Gdiplus::Graphics * graphics);

	CRestartSide(CGame *game);


	void NewGame();
	/// Default constructor (disabled)
	CRestartSide() = delete;

	/// Copy constructor (disabled)
	CRestartSide(const CRestartSide &) = delete;

	virtual ~CRestartSide();

	// Detects if two images overlap
	bool HitTest(int x, int y);

	/** Gets whether this item is draggable
	* \return true if draggable, otherwise false*/
	bool IsDraggable() override { return false; }

	bool IsButton() { return true; }

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CCharacterVisitor *visitor) override { visitor->VisitButton(this); }
	

private:
	// Poiner to item images
	std::unique_ptr<Gdiplus::Bitmap> mRestartImage;

	/**
	* X coordinate
	*/
	int mX = 0;

	/**
	* Y coordinate
	*/
	int mY = 0;
};

