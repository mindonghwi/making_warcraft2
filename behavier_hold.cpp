#include "stdafx.h"
#include "behavier_hold.h"
#include "unit.h"
#include "unitMGr.h"
#include "player.h"
BEHAVIER_HOLD::BEHAVIER_HOLD()
{
}

BEHAVIER_HOLD::~BEHAVIER_HOLD()
{
}

void BEHAVIER_HOLD::update(UNIT * pUnit)
{
	bool bIsHold = false;
	for (int i = 0; i < pUnit->getOpponent()->getUnitMgr()->getUnitCount(); i++)
	{
		float fDoubleSearchRange = pUnit->getAttackRange() * pUnit->getAttackRange();
		if (fDoubleSearchRange >= Mins::getDoubleDis(pUnit->getPosX(), pUnit->getPosY(), pUnit->getOpponent()->getUnitMgr()->getUnit(i)->getPosX(), pUnit->getOpponent()->getUnitMgr()->getUnit(i)->getPosY()))
		{
			pUnit->getMyUnitMgr()->commandAttackHold(pUnit, pUnit->getOpponent()->getUnitMgr()->getUnit(i));
			bIsHold = true;
			pUnit->setIsHold(true);
			break;
		}
	}

	if (!bIsHold)
	{
		pUnit->commandHold();
		
	}
}

void BEHAVIER_HOLD::end(UNIT * pUnit)
{
	_fTimer = 0.0f;
	
}
