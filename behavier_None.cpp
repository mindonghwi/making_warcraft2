#include "stdafx.h"
#include "behavier_None.h"
#include "unit.h"
#include "map.h"
BEHAVIER_NONE::BEHAVIER_NONE()
{
}

BEHAVIER_NONE::~BEHAVIER_NONE()
{
}

void BEHAVIER_NONE::update(UNIT * pUnit)
{
	pUnit->setIsHold(false);

	if (pUnit->getMap()->getTile(pUnit->getPosX() / TILESIZE, pUnit->getPosY() / TILESIZE)->getObject() != TILE::E_OBJECT::E_UNIT)
	{
		pUnit->moveToDir();
	}

}

void BEHAVIER_NONE::end(UNIT * pUnit)
{
}
