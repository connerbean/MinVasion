/**
 * \file Game.cpp
 *
 * \author Conner Bean
 */

#include "stdafx.h"
#include "Game.h"
#include "Character.h"
#include "PlayArea.h"
#include "CharacterGru.h"
#include "CharacterMinion.h"
#include "RestartSide.h"
#include "CharacterVillain.h"
#include "GruVisitor.h"
#include "CharacterVisitor.h"
#include "VillainCollector.h"
#include "MinionCollector.h"

/**
 * Constructor
 */
CGame::CGame()
{
	Reset();
}


/**
 * destructor
 */
CGame::~CGame()
{
}

/**
* Add an item to the game
* \param item New item to add
*/
void CGame::Add(std::shared_ptr<CCharacter> item)
{
	mItems.push_back(item);
}

/**
* Finds and deletes the selected item
* \param item The item to delete
*/
void CGame::Delete(std::shared_ptr<CCharacter> item)
{
	auto loc = find(::begin(mItems), ::end(mItems), item);
	if (loc != ::end(mItems))
	{
		mItems.erase(loc);
	}
}

/**
* Finds and deletes the selected item
* \param item The item to delete
*/
void CGame::Delete(CCharacter *item)
{
	for (std::shared_ptr<CCharacter> character : mItems)
	{
		if (character.get() == item)
		{
			Delete(character);
			break;
		}
	}
}

/**
 * Converts the Y value so pieces can be moved in the game
 * \param y The int to convert
 * \returns y The converted int
 */
int CGame::ConvertY(int y)
{
	y = int((y - mYOffset) / mScale);
	return y;
}

void CGame::Accept(CCharacterVisitor *visitor)
{
	for (std::shared_ptr<CCharacter> item : mItems)
	{
		item->Accept(visitor);
	}
}

void CGame::Reset()
{
	// Reset time
	mUpdateTime = 0;

	// Reset characters
	mItems.clear();

	// Villains on bottom...
	auto villainArya = make_shared<CCharacterVillain>(this, CCharacterVillain::Types::Arya);
	villainArya->SetLocation(0, 220);
	Add(villainArya);

	auto villainJuicer = make_shared<CCharacterVillain>(this, CCharacterVillain::Types::Juicer);
	villainJuicer->SetLocation(-250, -250);
	Add(villainJuicer);

	auto villainPokeball = make_shared<CCharacterVillain>(this, CCharacterVillain::Types::Pokeball);
	villainPokeball->SetLocation(250, -250);
	Add(villainPokeball);

	// ... then Gru...
	mGru = make_shared<CCharacterGru>(this);
	mGru->SetLocation(0, 400);
	Add(mGru);

	// ... then any minions
}


/**
 * Converts the X value so pieces can be moved in the game
 * \param x The number to convert
 * \returns x The converted int
 */
int CGame::ConvertX(int x)
{
	x = int((x - mXOffset) / mScale);
	return x;
}

/**
* Test to see if things in the game board have been hit
* \param x pointX
* \param y pointY
* \returns item if hit, null if not
*/
std::shared_ptr<CCharacter> CGame::HitTest(int x, int y)
{
	x = int((x - mXOffset) / mScale);
	y = int((y - mYOffset) / mScale);
 	for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}

	return  nullptr;
}

const int spawnLocationY = -450; ///< Y starting location for minion spawn
								
const wstring StuartImageName = L"images/stuart.png";  ///< Stuart filename 
const wstring MutantImageName = L"images/mutant.png";  ///< Mutant filename 
const wstring JerryImageName = L"images/jerry.png";  ///< Jerry filename 
const wstring DaveImageName = L"images/dave.png";  ///< Dave filename 

const int minionSpeed = 100; ///< Regular minion speed
const int mutantSpeed = 200; ///< Mutant minion speed
const int minionValue = 1; ///< Regular minion value
const int mutantValue = 5; ///< Mutant minon value

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CGame::Update(double elapsed)
{
	// Only spawn new minions if Gru is alive
	if (!IsGameOver())
	{
		mUpdateTime += elapsed;

		// Following is minion spawning code
		if (mUpdateTime > 0.5)
		{
			int MinionPicker = (rand() % 101) - 1;
			int spawnLocationX = (rand() % 950) - 475;

			if (MinionPicker <= 10)		// 10% of time give a mutant
			{
				auto newMinion = make_shared<CCharacterMinion>(this, MutantImageName, mutantValue, mutantSpeed);
				newMinion->SetLocation(spawnLocationX, spawnLocationY);
				Add(newMinion);
			}

			else if (MinionPicker <= 40)		// 30% of time give a mutant
			{
				auto newMinion = make_shared<CCharacterMinion>(this, DaveImageName, minionValue, minionSpeed);
				newMinion->SetLocation(spawnLocationX, spawnLocationY);
				Add(newMinion);
			}

			else if (MinionPicker <= 70) // give 30% chance for Stuart
			{
				auto newMinion = make_shared<CCharacterMinion>(this, StuartImageName, minionValue, minionSpeed);
				newMinion->SetLocation(spawnLocationX, spawnLocationY);
				Add(newMinion);
			}

			else // and last 30% chance for Jerry
			{
				auto newMinion = make_shared<CCharacterMinion>(this, JerryImageName, minionValue, minionSpeed);
				newMinion->SetLocation(spawnLocationX, spawnLocationY);
				Add(newMinion);
			}


			mUpdateTime = 0 + (rand() % 3) / 4;
		}
	}


	// Then update rest of items in game
	for (auto item : mItems)
	{
		item->Update(elapsed);
		item->Constraints(); // make sure items stay in the board
	}


	CVillainCollector villainCollector;
	Accept(&villainCollector);

	CMinionCollector minionCollector;
	Accept(&minionCollector);

	// TODO: potentially move these to visitor classes
	if (!IsGameOver())
	{
		// Check if Gru hits any villain or minion
		for (auto item : mItems)
		{
			if (item != mGru && mGru->HitTest((int)item->GetX(), (int)item->GetY()))
			{
				Delete(mGru);
				mGru = nullptr;

				break;
			}
		}

		// Check if any minion hit a villain
		for (auto villain : villainCollector.Retrieve())
		{
			for (auto minion : minionCollector.Retrieve())
			{
				if (villain->HitTest((int)minion->GetX(), (int)minion->GetY()))
				{
					// If it did, grant points and delete the minion
					villain->AddPoints(minion->GetScoreValue());
					Delete(minion);
					break;
				}
			}
		}
	}
}


/**
 * On draw function to draw game
 * \param graphics our settings
 * \param width width of display
 * \param height height of display
 */
void CGame::OnDraw(Gdiplus::Graphics * graphics, int width, int height)
{
	// Fill the background with black
	SolidBrush brush(Color::Black);
	graphics->FillRectangle(&brush, 0, 0, width, height);

	//
	// Automatic Scaling
	//
	float scaleX = float(width) / float(Width);
	float scaleY = float(height) / float(Height);
	mScale = min(scaleX, scaleY);

	mXOffset = width / 2.0f;
	mYOffset = height / 2.0f;

	graphics->TranslateTransform(mXOffset, mYOffset);
	graphics->ScaleTransform(mScale, mScale);

	// From here on you are drawing virtual pixels

	///Draw Board
	CPlayArea grid;
	grid.DrawGrid(graphics, width, height);

	for (auto item : mItems)
	{
		item->Draw(graphics);
	}
	


}