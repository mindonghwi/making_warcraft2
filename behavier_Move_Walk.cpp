#include "stdafx.h"
#include "behavier_Move_Walk.h"
#include "unit.h"
#include "unitMGr.h"

BEHAVIER_MOVE_WALK::BEHAVIER_MOVE_WALK():
	_fTimer(0.0f)
{
}

BEHAVIER_MOVE_WALK::~BEHAVIER_MOVE_WALK()
{
}

void BEHAVIER_MOVE_WALK::update(UNIT * pUnit)
{
	_fTimer += TIMEMANAGER->getElapsedTime();

	if (_fTimer > pUnit->getSpeed())
	{


		if (!pUnit->moveTo()) {
			end(pUnit);
			return;
		}
		_fTimer = 0.0f;
	}
	
	

	pUnit->Move();

	if (pUnit->getTarget())
	{
		RECT rc;
		RECT rcTmp = *pUnit->getTarget()->getRect();
		rcTmp.left -= 5;
		rcTmp.top -= 5;
		rcTmp.bottom  += 5;
		rcTmp.right  += 5;

		if (IntersectRect(&rc, pUnit->getCollisionRect(), &rcTmp))
		{
			end(pUnit);
			return;
		}
	}


}

void BEHAVIER_MOVE_WALK::end(UNIT * pUnit)
{
	RECT rcSmall = *pUnit->getCollisionRect();
	rcSmall.left += 5;
	rcSmall.right -= 5;
	rcSmall.top += 5;
	rcSmall.bottom -= 5;
	bool bIsCollision = false;
	for (int i = 0; i < pUnit->getMyUnitMgr()->getUnitCount(); i++)
	{
		if (pUnit != pUnit->getMyUnitMgr()->getUnit(i))
		{
			if (pUnit->getMyUnitMgr()->getUnit(i)->getBehavier() != UNIT::E_BEHAVIERNUM::E_MOVE)
			{
				RECT rc;
				if (IntersectRect(&rc, pUnit->getMyUnitMgr()->getUnit(i)->getCollisionRect(), &rcSmall))
				{
					bIsCollision = true;
					break;
				}
			}
	
		}
	}
	
	if (!bIsCollision)
	{
		pUnit->setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_NONE);
		pUnit->setCurrentState(UNIT::E_STATENUM::E_IDLE);
		pUnit->setBehavier(UNIT::E_BEHAVIERNUM::E_NONE);
		pUnit->getCurrentState()->start();
		pUnit->addMapUnitData();
		pUnit->setIsHold(false);
	}
	else
	{
		pUnit->moveToDir();
	}

	_fTimer = 0.0f;

}
