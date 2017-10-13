/**
* \file Character.cpp
*
* \author Matthew Rhodes
*/

#include "stdafx.h"
#include "Character.h"
#include "Game.h"

/**
* Constructor.
* \param game The game this character is a part of
*/
CCharacter::CCharacter(CGame *game) : mGame(game)
{
}


/**
* Destructor.
*/
CCharacter::~CCharacter()
{
}

/**
 * Constrains the Item to the board
 * \param x Location
 * \param y Location
 */
void CCharacter::Constraints(int x, int y)
{
	if (x >= mMax)
	{
		x = mMax;
	}
	else if (x <= mMin)
	{
		x = mMin;
	}
	if (y >= mMax)
	{
		y = mMax;
	}
	else if (y <= mMin)
	{
		y = mMin;
	}
	SetLocation(x, y);
}