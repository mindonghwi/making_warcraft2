#include "stdafx.h"
#include "behavier_transportOut.h"
#include "unit.h"

BEHAVIER_TRANSPORTOUT::BEHAVIER_TRANSPORTOUT()
{
}

BEHAVIER_TRANSPORTOUT::~BEHAVIER_TRANSPORTOUT()
{
}

void BEHAVIER_TRANSPORTOUT::update(UNIT * pUnit)
{
	pUnit->setIsHold(false);
	end(pUnit);
}

void BEHAVIER_TRANSPORTOUT::end(UNIT * pUnit)
{
	pUnit->commandIdle();	
}
