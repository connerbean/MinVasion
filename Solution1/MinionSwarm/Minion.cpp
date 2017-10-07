#include "stdafx.h"
#include <string>
#include "Minion.h"

using namespace Gdiplus;
using namespace std;

/// Item filename 
const wstring MinionImageName = L"images/Minion.png";

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CMinion::CMinion(CGame *game) : CItem(game)
{
}

/**
* Destructor
*/
CMinion::~CMinion()
{
}