/**
 * \file PlayArea.h
 *
 * \author Matthew May
 *
 * This Class is the limitations of the playing area
 */

#pragma once
#include "Game.h"
#include <memory>

/**
* Class definition for the the area with all the game 
* pieces
*/
class CPlayArea : public CGame
{
public:
	//Constructor
	CPlayArea();
	//Destructor
	~CPlayArea();

	///Size of the grid
	const static REAL GridSize;
	///Radius of the grid
	const static REAL GridRadius;
	///Grid Margins
	const static REAL GridMargin;

	/// Draws grid
	///\param graphics the window
	///\param width of the window
	///\param height of the window
	void DrawGrid(Graphics * graphics, int width, int height);
};

