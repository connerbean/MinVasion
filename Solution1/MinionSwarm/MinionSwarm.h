
// MinionSwarm.h : main header file for the MinionSwarm application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCharacterMinionSwarmApp:
// See MinionSwarm.cpp for the implementation of this class
//

class CCharacterMinionSwarmApp : public CWinApp
{
public:
	CCharacterMinionSwarmApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
};

extern CCharacterMinionSwarmApp theApp;
