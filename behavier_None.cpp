#include "stdafx.h"
#include "behavier_None.h"
#include "unit.h"
BEHAVIER_NONE::BEHAVIER_NONE()
{
}

BEHAVIER_NONE::~BEHAVIER_NONE()
{
}

void BEHAVIER_NONE::update(UNIT * pUnit)
{
	pUnit->setIsHold(false);
}

void BEHAVIER_NONE::end(UNIT * pUnit)
{
}
