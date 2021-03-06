/**
 * \file PlayArea.cpp
 *
 * \author Matthew May
 */
#include "stdafx.h"
#include "PlayArea.h"

 /// The size of the playing area square in virtual pixels
const REAL CPlayArea::GridSize = 1000.0;

/// The range from the center to an edge for the playing area
/// in virtual pixels
const REAL CPlayArea::GridRadius = CPlayArea::GridSize / 2.0;

/// Do not allow Minions or Gru to come closer than this distance
/// to the playing area edges (virtual pixels)
const REAL CPlayArea::GridMargin = 50.0;

/**
 * Constructor
 */
CPlayArea::CPlayArea()
{
}

/**
 * Destructor
 */
CPlayArea::~CPlayArea()
{
}

/**
 * Draws the Green Board for play
 * \param graphics 
 * \param width 
 * \param height 
 */
void CPlayArea::DrawGrid(Graphics *graphics, int width, int height)
{
	Pen pen(Color(0, 128, 0), 3);
	graphics->DrawRectangle(&pen, -GridRadius, -GridRadius, GridSize, GridSize);
}