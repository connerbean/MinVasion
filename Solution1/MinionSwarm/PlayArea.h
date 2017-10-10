/**
 * \file PlayArea.h
 *
 * \author Matthew May
 *
 * This Class is the limitations of the playing area
 */

#pragma once
#include "Game.h"
#include<memory>


class CPlayArea : public CGame
{
public:
	//Constructor
	CPlayArea();
	//Destructor
	~CPlayArea();

	///Size of the grid
	const static double GridSize;
	///Radius of the grid
	const static double GridRadius;
	///Grid Margins
	const static double GridMargin;

	/// Draws grid
	///\param graphics the window
	///\width width of the window
	///\height height of the window
	void DrawGrid(Graphics * graphics, int width, int height);
};
