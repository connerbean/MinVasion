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