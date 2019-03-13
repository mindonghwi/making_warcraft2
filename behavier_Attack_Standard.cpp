#include "stdafx.h"
#include "behavier_Attack_Standard.h"
#include "unit.h"


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
	if (pUnit->getSearchRange() <= getDistance(pUnit->getPosX(),pUnit->getPosY(),pUnit->getTarget()->getPosX(), pUnit->getTarget()->getPosY()))
	{
		end(pUnit);
	}
	else
	{
		
		//�̵��ض�
		//pUnit->clearCommand();
		//pUnit->commandMove(pUnit->getTarget()->getPosX(), pUnit->getTarget()->getPosY());
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
