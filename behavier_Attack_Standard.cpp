#include "stdafx.h"
#include "behavier_Attack_Standard.h"
#include "unit.h"
#include "unitMGr.h"

BEHAVIER_ATTACK::BEHAVIER_ATTACK()
{
}

BEHAVIER_ATTACK::~BEHAVIER_ATTACK()
{
}

void BEHAVIER_ATTACK::update(UNIT * pUnit)
{

	//_fTimer += TIMEMANAGER->getElapsedTime();
	//
	//if (_fTimer > pUnit->getSpeed())
	//{
	//	if (!pUnit->moveTo()) {
	//		end(pUnit);
	//		return;
	//	}
	//	_fTimer = 0.0f;
	//}
	//
	//
	//pUnit->Move();

	//어택범위에 적이 들어오면 적을 공격한다.
	pUnit->getTarget()->decreaseHp(pUnit->getAttack());
	
	//서치범위에 적을 찾으면 astar 재탐색
	//서치범위에 적이 없으면 걍 멈추기
	
	if (pUnit->getTarget())
	{
		RECT rc;
		RECT rcTmp = *pUnit->getRect();
		rcTmp.left -= 5;
		rcTmp.top -= 5;
		rcTmp.bottom += 5;
		rcTmp.right += 5;

		if (IntersectRect(&rc, pUnit->getCollisionRect(), &rcTmp))
		{

		}
		else
		{
			float fDistance = getDistance(pUnit->getPosX(), pUnit->getPosY(), pUnit->getTarget()->getPosX(), pUnit->getTarget()->getPosY());
			if (pUnit->getSearchRange() <= fDistance)
			{
				end(pUnit);
			}
			else if (pUnit->getAttackRange() <= fDistance)
			{
				//이동해라
				OBJECT* pTarget = pUnit->getTarget();
				pUnit->clearCommand();
				pUnit->setTarget(pTarget);
				pUnit->getMyUnitMgr()->commandReAttack(pUnit, pUnit->getTarget());
				//pUnit->clearCommand();
				//pUnit->commandMove(pUnit->getTarget()->getPosX(), pUnit->getTarget()->getPosY());
			}

		}
	}


}

void BEHAVIER_ATTACK::end(UNIT * pUnit)
{
	//유닛이 서치를 해본다
	//적 유닛이나 건물이 서치범위에 있으면 command(move,attack)
	//적유닛이나 건물이 없을때 아이들
	
	pUnit->setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_NONE);
	pUnit->setCurrentState(UNIT::E_STATENUM::E_IDLE);
	pUnit->setBehavier(UNIT::E_BEHAVIERNUM::E_NONE);
	pUnit->getCurrentState()->start();
	pUnit->setTarget(nullptr);
}
