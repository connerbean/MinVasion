
// MinionSwarm.h : main header file for the MinionSwarm application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMinionSwarmApp:
// See MinionSwarm.cpp for the implementation of this class
//

class CMinionSwarmApp : public CWinApp
{
public:
	CMinionSwarmApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMinionSwarmApp theApp;
