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

	void Update(double elapsed);

	void Draw(Gdiplus::Graphics *graphics);

	/// Getter for mTimePassed
	/// \returns mTimePassed
	double GetTimePassed() { return mTimePassed; }

	/// Reset all variables related to the clock
	void Reset() { mTimePassed = 0; }

private:
	double mTimePassed = 0;		///< Total time passed
};

