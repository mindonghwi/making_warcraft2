#include "stdafx.h"
#include "behavier_Move_Walk.h"
#include "unit.h"
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
}

void BEHAVIER_MOVE_WALK::end(UNIT * pUnit)
{
	pUnit->setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_NONE);
	pUnit->setCurrentState(UNIT::E_STATENUM::E_IDLE);
	pUnit->setBehavier(UNIT::E_BEHAVIERNUM::E_NONE);



	pUnit->getCurrentState()->start();
	_fTimer = 0.0f;



	if (pUnit->getUnit() == UNIT::E_UNIT::E_WORKMAN)
	{
		pUnit->build();
	}
}
