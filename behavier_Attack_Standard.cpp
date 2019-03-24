#include "stdafx.h"
#include "behavier_Attack_Standard.h"
#include "unit.h"
#include "unitMGr.h"

BEHAVIER_ATTACK::BEHAVIER_ATTACK():
	_fTimer(0.0f)
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
	

	//��ġ������ ���� ã���� astar ��Ž��
	//��ġ������ ���� ������ �� ���߱�
	


	if (pUnit->getTarget())
	{
		if (pUnit == pUnit->getTarget())
		{
			end(pUnit);
			return;
		}
		if (pUnit->getTarget()->getHp() <= 0)
		{
			pUnit->setTarget(nullptr);
			return;
		}



		RECT rc;
		RECT rcTmp = *pUnit->getTarget()->getRect();
		rcTmp.left -= 5;
		rcTmp.top -= 5;
		rcTmp.bottom += 5;
		rcTmp.right += 5;

		_fTimer += TIMEMANAGER->getElapsedTime();
		float fTotalFps = static_cast<float>(pUnit->getEndIndex(UNIT::E_STATE::E_ATTACK) - pUnit->getStartIndex(UNIT::E_STATE::E_ATTACK));
		if (fTotalFps <= 1)
		{
			fTotalFps = 1;
		}
		fTotalFps *= pUnit->getFPS(UNIT::E_STATE::E_ATTACK);
		

		if (IntersectRect(&rc, pUnit->getCollisionRect(), &rcTmp))
		{

			if (_fTimer >= fTotalFps)
			{
				if (pUnit->getUnit() == UNIT::E_UNIT::E_FOOTMAN ||
					pUnit->getUnit() == UNIT::E_UNIT::E_WORKMAN ||
					pUnit->getUnit() == UNIT::E_UNIT::E_KNIGHT ||
					pUnit->getUnit() == UNIT::E_UNIT::E_BOMBER)
				{
					
					pUnit->getTarget()->decreaseHp(pUnit->getAttack());
					
				}

				_fTimer = 0.0f;
			}
		}
		else
		{
			
			float fDistance = getDistance(pUnit->getPosX(), pUnit->getPosY(), pUnit->getTarget()->getPosX(), pUnit->getTarget()->getPosY());
			if (pUnit->getSearchRange() < fDistance)
			{
				end(pUnit);
				return;
			}	
			else if (pUnit->getAttackRange() <= fDistance)
			{
				if (pUnit->isHold()) {
					end(pUnit);
				}

				//�̵��ض�
				OBJECT* pTarget = pUnit->getTarget();
				pUnit->clearCommand();
				pUnit->setTarget(pTarget);
				pUnit->getMyUnitMgr()->commandReAttack(pUnit, pUnit->getTarget());
				//pUnit->clearCommand();
				//pUnit->commandMove(pUnit->getTarget()->getPosX(), pUnit->getTarget()->getPosY());
			}

			if (_fTimer >= fTotalFps)
			{
				pUnit->fireBullet();
				_fTimer = 0.0f;
			}
		}
	}
	else //if(pUnit->getTarget()->getHp() <= 0)
	{
		end(pUnit);
	}

	//if (pUnit->getUnit() == UNIT::E_UNIT::E_ARCHER ||
	//	pUnit->getUnit() == UNIT::E_UNIT::E_BALLISTA ||
	//	pUnit->getUnit() == UNIT::E_UNIT::E_FLYER ||
	//	pUnit->getUnit() == UNIT::E_UNIT::E_BATTLESHIP ||
	//	pUnit->getUnit() == UNIT::E_UNIT::E_GALLEYS ||
	//	pUnit->getUnit() == UNIT::E_UNIT::E_SUBMARIN)
	//{

	//}
	//else
	//{

	//}


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
	pUnit->setIsHold(false);
	_fTimer = 0.0f;
}
