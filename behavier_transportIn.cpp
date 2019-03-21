#include "stdafx.h"
#include "behavier_transportIn.h"
#include "unit.h"
BEHAVIER_TRANSPORTIN::BEHAVIER_TRANSPORTIN()
{
}

BEHAVIER_TRANSPORTIN::~BEHAVIER_TRANSPORTIN()
{
}

void BEHAVIER_TRANSPORTIN::update(UNIT * pUnit)
{
	RECT rc = *pUnit->getTarget()->getRect();
	RECT rcMy = *pUnit->getCollisionRect();

	rc.left -= 32;
	rc.top -= 32;
	rc.right += 32;
	rc.bottom += 32;

	RECT rcTmp;
	if (IntersectRect(&rcTmp,&rc,&rcMy))
	{
		end(pUnit);
	}
}

void BEHAVIER_TRANSPORTIN::end(UNIT * pUnit)
{
	pUnit->commandTransportIn();
}
