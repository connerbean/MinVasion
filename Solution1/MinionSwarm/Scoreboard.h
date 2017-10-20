/**
 * \file Clock.h
 *
 * \author Collin Dillinger
 *
 * Implementation of scoreboard 
 */

#pragma once

class CGame;

/**
 * CScoreboard Class
 */
class CScoreboard
{
public:
	/// Constructor
	CScoreboard(CGame *game);
	/// Destructor
	~CScoreboard();
	
	/// Draws the clock on the screen
	void Draw(Gdiplus::Graphics *graphics);

private:
	CGame *mGame;		///< Main game object
};