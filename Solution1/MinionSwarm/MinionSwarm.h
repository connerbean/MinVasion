/**
* \file MinionSwarm.h
*
* \author Matthew Rhodes
*
*  Class that the entire solution is derived from
*/
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


/** CCharacterMinionSwarmApp:
* See MinionSwarm.cpp for the implementation of this class
*/
class CCharacterMinionSwarmApp : public CWinApp
{
public:
	CCharacterMinionSwarmApp();


// Overrides
public:
	/// Initializes the intance for the game
	/// \returns a bool
	virtual BOOL InitInstance();

	/// Exits the instance for the game
	/// \returns an int
	virtual int ExitInstance();

// Implementation

public:
	/// the documentation for the Minion swarm game
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:

	/// essential gdiplus component
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;

	/// essential token that is needed in order to get the graphics working
	ULONG_PTR gdiplusToken;
};

/// The one and only CCharacterMinionSwarmApp object
extern CCharacterMinionSwarmApp theApp;
