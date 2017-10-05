/**
 * \file Clock.h
 *
 * \author Conner Bean
 *
 * Implementation of CClock 
 *  - running time of game
 */

#pragma once




/**
 * CClock Class
 */
class CClock
{
public:
	/// Constructor
	CClock();
	/// Destructor
	~CClock();

	/// Update function \param elapsed is time elapsed
	void Update(double elapsed);
	/// DisplayTime displays time \param graphics for drawing
	void DisplayTime(Gdiplus::Graphics *graphics);

private:
	double mTimePassed = 0;		///< Total time passed
	int mSeconds = 0;			///< Total seconds passed
	int mMinutes = 0;			///< Total minutes passed
};

