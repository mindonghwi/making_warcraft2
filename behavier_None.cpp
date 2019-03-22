#include "stdafx.h"
#include "behavier_None.h"
#include "unit.h"
#include "map.h"
#include "unitMGr.h"
BEHAVIER_NONE::BEHAVIER_NONE()
{
}

BEHAVIER_NONE::~BEHAVIER_NONE()
{
}

void BEHAVIER_NONE::update(UNIT * pUnit)
{
	pUnit->setIsHold(false);
	pUnit->setMoveAttack(false);
	if (pUnit->getMap()->getTile(pUnit->getPosX() / TILESIZE, pUnit->getPosY() / TILESIZE)->getObject() != TILE::E_OBJECT::E_UNIT &&
		pUnit->getMap()->getTile(pUnit->getPosX() / TILESIZE, pUnit->getPosY() / TILESIZE)->getObject() != TILE::E_OBJECT::E_OILPATCH &&
		pUnit->getMap()->getTile(pUnit->getPosX() / TILESIZE, pUnit->getPosY() / TILESIZE)->getObject() != TILE::E_OBJECT::E_NONE)
	{
		pUnit->clearCommand();
		pUnit->getMyUnitMgr()->commandMoveSingle(pUnit->getPosX(), pUnit->getPosY(), pUnit);
	}

}

void BEHAVIER_NONE::end(UNIT * pUnit)
{
}
