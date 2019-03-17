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

	//���ù����� ���� ������ ���� �����Ѵ�.
	pUnit->getTarget()->decreaseHp(pUnit->getAttack());
	
	//��ġ������ ���� ã���� astar ��Ž��
	//��ġ������ ���� ������ �� ���߱�
	
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
				//�̵��ض�
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
	//������ ��ġ�� �غ���
	//�� �����̳� �ǹ��� ��ġ������ ������ command(move,attack)
	//�������̳� �ǹ��� ������ ���̵�
	
	pUnit->setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_NONE);
	pUnit->setCurrentState(UNIT::E_STATENUM::E_IDLE);
	pUnit->setBehavier(UNIT::E_BEHAVIERNUM::E_NONE);
	pUnit->getCurrentState()->start();
	pUnit->setTarget(nullptr);
}
