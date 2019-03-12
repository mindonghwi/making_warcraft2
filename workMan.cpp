#include "stdafx.h"
#include "workMan.h"
#include "state_AttackMove.h"
#include "state_hold.h"
#include "state_idle.h"
#include "state_move.h"
#include "state_Patrol.h"
#include "state_special.h"
#include "state_Attack.h"

#include "behavier_Attack_Standard.h"
#include "behavier_Move_Walk.h"
#include "behavier_Harvest_WorkMan.h"
#include "behavier_None.h"

#include "command.h"
#include "stopCommand.h"
#include "holdCommand.h"
#include "moveCommand.h"
#include "buildCommand.h"
#include "unitMGr.h"

WORKMAN::WORKMAN()
{
}

WORKMAN::~WORKMAN()
{
}

void WORKMAN::init(int nPosX, int nPosY, int nWidth, int nHeight, int nIndexNum)
{
	UNIT::init(nPosX, nPosY, nWidth, nHeight,nIndexNum);
	UNIT::OBJECT::setPosZ(200);
	allocateAnimation();
	allocateState();
	allocateBehavier();
	UNIT::setCurrentState(UNIT::E_STATENUM::E_IDLE);
	UNIT::getCurrentState()->start();
	UNIT::setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_NONE);
	UNIT::setUnit(UNIT::E_UNIT::E_WORKMAN);
	UNIT::OBJECT::setImage(IMAGEMANAGER->findImage("peasantSprite"));

	UNIT::setCollisionRect(UNIT::getPosX(), UNIT::getPosY(), 32, 32);
	UNIT::setPopulation(1);

	_eBuilds = BUILDMGR::E_BUILDS::E_MAX;
	_fTimer = 0.0f;

	_nCommand = 0;
	_nCommand += static_cast<unsigned int>(COMMAND::E_COMMAND::E_STOP);
	_nCommand += static_cast<unsigned int>(COMMAND::E_COMMAND::E_HOLD);
	_nCommand += static_cast<unsigned int>(COMMAND::E_COMMAND::E_MOVE);
	_nCommand += static_cast<unsigned int>(COMMAND::E_COMMAND::E_BUILD);

	
}

void WORKMAN::update()
{
	if (_bIsBannedSelected)
	{
		_fTimer += TIMEMANAGER->getElapsedTime();
		if (_fTimer >= _fBuildTime)
		{
			UNIT::setIsBannedSelect(false);
		}
		//등장위치 조정
		if (_pMap->getTile((int)OBJECT::getPosX()/TILESIZE, (int)OBJECT::getPosY() / TILESIZE)->getObject() != TILE::E_OBJECT::E_NONE)
		{
			for (int i = 0; i < 25; i++)
			{
				OBJECT::setPosX(OBJECT::getPosX() + _pUnitMgr->getIntervalX(i) * TILESIZE);
				OBJECT::setPosY(OBJECT::getPosY() + _pUnitMgr->getIntervalY(i) * TILESIZE);

				if (_pMap->getTile((int)OBJECT::getPosX() / TILESIZE, (int)OBJECT::getPosY() / TILESIZE)->getObject() == TILE::E_OBJECT::E_NONE)
				{
					OBJECT::settingRect();
					setCollisionRect(OBJECT::getPosX(), OBJECT::getPosY(), 32, 32);
					break;
				}
			}
		}

		return;
	}

	if (_eBehavier == UNIT::E_BEHAVIERNUM::E_NONE && !_queWaitCommand.empty())
	{
		COMMAND* pCommand = _queWaitCommand.front();
		pCommand->start();
		_queWaitCommand.pop();
		_pUnitMgr->returnPool(pCommand);
	}

	


	_pCamera->pushRenderObject(this);
}

void WORKMAN::updateBehavier()
{
	UNIT::getCurrentState()->update();
	UNIT::getCurrentBehavir()->update(this);

}

void WORKMAN::release()
{
}

void WORKMAN::render(HDC hdc)
{
	UNIT::OBJECT::getImage()->frameRenderCenter(hdc, UNIT::OBJECT::getPosX(), UNIT::OBJECT::getPosY(), _nFrameX, static_cast<int>(_eDirection));

}

void WORKMAN::renderSelected(HDC hdc)
{
	DrawEdge(hdc, UNIT::getCollisionRect(), BDR_RAISEDOUTER, BF_FLAT | BF_TOPLEFT | BF_BOTTOMRIGHT);
}


void WORKMAN::command()
{
	//if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	//{
	//	_fEndX = static_cast<float>(_ptMouse.x + _pCamera->getLeft());
	//	_fEndY = static_cast<float>(_ptMouse.y + _pCamera->getTop());

	//	setMovePoints(static_cast<float>(_ptMouse.x + _pCamera->getLeft()), static_cast<float>(_ptMouse.y + _pCamera->getTop()));
	//	UNIT::getCurrentBehavir()->end(this);
	//	if (!UNIT::moveTo()) {
	//		return;
	//	}
	//	UNIT::setCurrentState(UNIT::E_STATENUM::E_MOVE);
	//	UNIT::setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_MOVE);
	//	UNIT::setBehavier(UNIT::E_BEHAVIERNUM::E_MOVE);

	//	UNIT::getCurrentState()->start();
	//}
}

void WORKMAN::commandBuild()
{
	_fEndX = static_cast<float>(_ptMouse.x + _pCamera->getLeft());
	_fEndY = static_cast<float>(_ptMouse.y + _pCamera->getTop());

	setMovePoints(static_cast<float>(_ptMouse.x + _pCamera->getLeft()), static_cast<float>(_ptMouse.y + _pCamera->getTop()));
	UNIT::getCurrentBehavir()->end(this);
	if (!UNIT::moveTo()) {
		return;
	}
	UNIT::setCurrentState(UNIT::E_STATENUM::E_MOVE);
	UNIT::setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_MOVE);
	UNIT::setBehavier(UNIT::E_BEHAVIERNUM::E_MOVE);

	UNIT::getCurrentState()->start();

}

void WORKMAN::build(float fPosX, float fPosY, BUILDMGR::E_BUILDS eBuilds)
{
	_pBuildMgr->buildBuilding(eBuilds, fPosX, fPosY);
	_bIsBannedSelected = true;
	_fBuildTime = _pBuildMgr->getBuildTime(eBuilds);
	_fTimer = 0.0f;
}




void WORKMAN::allocateState()
{
	UNIT::_arState[static_cast<int>(UNIT::E_STATENUM::E_IDLE)] = new STATE_IDLE();
	UNIT::_arState[static_cast<int>(UNIT::E_STATENUM::E_MOVE)] = new STATE_MOVE();
	UNIT::_arState[static_cast<int>(UNIT::E_STATENUM::E_PATROL)] = new STATE_PATROL();
	UNIT::_arState[static_cast<int>(UNIT::E_STATENUM::E_ATTACK)] = new STATE_ATTACK();
	UNIT::_arState[static_cast<int>(UNIT::E_STATENUM::E_ATTACK_MOVE)] = new STATE_ATTACKMOVE();
	UNIT::_arState[static_cast<int>(UNIT::E_STATENUM::E_HOLD)] = new STATE_HOLD();
	UNIT::_arState[static_cast<int>(UNIT::E_STATENUM::E_SPECIAL_01)] = new STATE_SPECIAL();


	for (int i = 0; i < static_cast<int>(UNIT::E_STATENUM::E_MAX); i++)
	{
		UNIT::_arState[i]->setUnit(this);
	}
}

void WORKMAN::allocateBehavier()
{
	UNIT::_arBeHavier[static_cast<int>(UNIT::E_BEHAVIERNUM::E_NONE)] = new BEHAVIER_NONE();
	UNIT::_arBeHavier[static_cast<int>(UNIT::E_BEHAVIERNUM::E_ATTACK)] = new BEHAVIER_ATTACK();
	UNIT::_arBeHavier[static_cast<int>(UNIT::E_BEHAVIERNUM::E_MOVE)] = new BEHAVIER_MOVE_WALK();
	UNIT::_arBeHavier[static_cast<int>(UNIT::E_BEHAVIERNUM::E_HARVEST)] = new BEHAVIER_ATTACK();
	UNIT::_arBeHavier[static_cast<int>(UNIT::E_BEHAVIERNUM::E_MAGIC)] = new BEHAVIER_NONE();
}

void WORKMAN::allocateAnimation()
{

	//금은 +10 나무는 +15
	setStartIndex(UNIT::E_STATE::E_IDLE, 0);
	setEndIndex(UNIT::E_STATE::E_IDLE, 0);

	setStartIndex(UNIT::E_STATE::E_MOVE, 1);
	setEndIndex(UNIT::E_STATE::E_MOVE, 4);

	setStartIndex(UNIT::E_STATE::E_ATTACK, 5);
	setEndIndex(UNIT::E_STATE::E_ATTACK, 9);

	setStartIndex(UNIT::E_STATE::E_DEATH, 0);
	setEndIndex(UNIT::E_STATE::E_DEATH, 3);

	setFPS(UNIT::E_STATE::E_IDLE, 100.0f);
	setFPS(UNIT::E_STATE::E_MOVE, 0.125f);
	setFPS(UNIT::E_STATE::E_ATTACK, 0.125f);
	setFPS(UNIT::E_STATE::E_ATTACK, 0.7f);

	_eDirection = UNIT::E_DIRECTION::E_BOTTOM;
}

//MOVE를 예로 상태는 캐릭터의 상태가 변한다. 즉 애니메이션이
//행동은 움직인다 xy가