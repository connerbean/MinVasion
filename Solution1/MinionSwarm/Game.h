/**
* \file Game.h
*
* \author Matthew Rhodes
*
*  Class that hold all the pieces to the game
*/
#pragma once
#include <memory>
#include <vector>

using namespace Gdiplus;
using namespace std;

class CCharacter;

class CGame
{
	/// Game area width in virtual pixels
	const static int Width = 1400;

	/// Game area height in virtual pixels
	const static int Height = 1100;
public:
	///Converts the X value so pieces can be moved in the game
	int CGame::ConvertX(int x);

	///Converts the Y value so pieces can be moved in the game
	int CGame::ConvertY(int y);

	///Deletes item from game
	///\param item The item to delete
	void CGame::Delete(std::shared_ptr<CCharacter> item);

	/**
	* Declartion for Update function
	*
	* \param elapsed The time since the last update
	*/
	void CGame::Update(double elapsed);

	/**
	* Add fish to the aquarium
	*/
	void CGame::Add(std::shared_ptr<CCharacter> item);

	CGame(); ///<Constructor
	virtual ~CGame(); ///<Virtual destructor

	/** Test an x,y click location to see if it clicked
	* on some item in the aquarium.
	* \param x X location
	* \param y Y location
	* \returns Pointer to item we clicked on or nullptr if none.
	*/
	std::shared_ptr<CCharacter> CGame::HitTest(int x, int y);

	/**
	* Draw the game area
	* \param graphics The GDI+ graphics context to draw on
	* \param width Width of the client window
	* \param height Height of the client window
	*/
	void CGame::OnDraw(Gdiplus::Graphics *graphics, int width, int height);

private:
	/**
	* mScale is the average of scaleX and scaleY
	*/
	Gdiplus::REAL  mScale = 0;

	/**
	* Offset for X
	*/
	Gdiplus::REAL mXOffset = 0;

	/**
	* Offset for Y
	*/
	Gdiplus::REAL mYOffset = 0;

	double mUpdateTime = 0; ///< double used to keep track of update time in seconds

	std::vector<std::shared_ptr<CCharacter> > mItems; ///< Vector of all items in the game
};

