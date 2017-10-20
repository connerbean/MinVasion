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
class CCharacterGru;
class CCharacterMinion;
class CCharacterVillain;
class CCharacterVisitor;

/**
* Class definition for the game that holds 
* all the pieces and pictures
*/
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

	///Deletes item from game
	///\param item The item to delete
	void CGame::Delete(CCharacter *item);

	/**
	* Declartion for Update function
	*
	* \param elapsed The time since the last update
	*/
	void CGame::Update(double elapsed);

	void CGame::Reset();
	/**
	* Add character to the game
	*/
	void CGame::Add(std::shared_ptr<CCharacter> item);

	CGame(); ///<Constructor
	virtual ~CGame(); ///<Virtual destructor

	/** Test an x,y click location to see if it clicked
	* on some item in the game.
	* \param x X location
	* \param y Y location
	* \returns Pointer to item we clicked on or nullptr if none.
	*/
	std::shared_ptr<CCharacter> CGame::HitTest(int x, int y);


	void CGame::Accept(CCharacterVisitor *visitor);

	/**
	* Draw the game area
	* \param graphics The GDI+ graphics context to draw on
	* \param width Width of the client window
	* \param height Height of the client window
	*/
	void CGame::OnDraw(Gdiplus::Graphics *graphics, int width, int height);

	/// Get items length
	/// \returns mItems size
	int GetItemsSize() { return mItems.size(); }

	/// Gets whether Gru died
	bool IsGameOver() { return mGru == nullptr; }

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

	std::vector<std::shared_ptr<CCharacter>> mItems; ///< Vector of all characters in the game

	std::shared_ptr<CCharacterGru> mGru; ///< pointer to Gru

public:
	/** Iterator that iterates over the city tiles */
	class Iter
	{
	public:
		/** Constructor
		* \param game The game we are iterating over
		* \param pos The position to start the iterator at
		*/
		Iter(CGame *game, int pos) : mGame(game), mPos(pos) {}

		/** Test for end of the iterator
		* \param other The other Iter item to compare to
		* \returns True if we this position equals not equal to the other position */
		bool operator!=(const Iter &other) const
		{
			return mPos != other.mPos;
		}

		/** Get value at current position
		* \returns Value at mPos in the collection */
		std::shared_ptr<CCharacter> operator *() const { return mGame->mItems[mPos]; }

		/** Increment the iterator
		* \returns Reference to this iterator */
		const Iter& operator++()
		{
			mPos++;
			return *this;
		}


	private:
		CGame *mGame;   ///< Game we are iterating over
		int mPos;       ///< Position in the collection
	};

	/** Get an iterator for the beginning of the collection
	* \returns Iter object at position 0 */
	Iter begin() { return Iter(this, 0); }

	/** Get an iterator for the end of the collection
	* \returns Iter object at position past the end */
	Iter end() { return Iter(this, mItems.size()); }
};

