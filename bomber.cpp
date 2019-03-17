#include "stdafx.h"
#include "bomber.h"
#include "unitMGr.h"
#include "unitBehavierHeader.h"
#include "unitStateHeader.h"

BOMBER::BOMBER()
{
}

BOMBER::~BOMBER()
{
}

void BOMBER::init(int nPosX, int nPosY, int nWidth, int nHeight, int nIndexNum)
{
	UNIT::init(nPosX, nPosY, nWidth, nHeight, nIndexNum);
	UNIT::OBJECT::setPosZ(200);
	allocateAnimation();
	allocateState();
	allocateBehavier();
	UNIT::setCurrentState(UNIT::E_STATENUM::E_IDLE);
	UNIT::getCurrentState()->start();
	UNIT::setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_NONE);
	UNIT::setUnit(UNIT::E_UNIT::E_BOMBER);
	UNIT::OBJECT::setImage(IMAGEMANAGER->findImage("dwavenDemolition"));

	UNIT::setCollisionRect(UNIT::getPosX(), UNIT::getPosY(), 32, 32);
	UNIT::setPopulation(1);

	_eBuilds = E_BUILDS::E_MAX;
	_fTimer = 0.0f;

	_nCommand = 0;
	_nCommand += static_cast<unsigned int>(COMMAND::E_COMMAND::E_STOP);
	_nCommand += static_cast<unsigned int>(COMMAND::E_COMMAND::E_HOLD);
	_nCommand += static_cast<unsigned int>(COMMAND::E_COMMAND::E_MOVE);
	//_nCommand += static_cast<unsigned int>(COMMAND::E_COMMAND::E_ATTACK);

}

void BOMBER::update()
{

	//커맨드 큐 사용
	if (_eBehavier == UNIT::E_BEHAVIERNUM::E_NONE && !_queWaitCommand.empty())
	{
		COMMAND* pCommand = _queWaitCommand.front();
		pCommand->start();
		_queWaitCommand.pop();
		_pUnitMgr->returnPool(pCommand);
	}




	_pCamera->pushRenderObject(this);
}

void BOMBER::updateBehavier()
{
	UNIT::getCurrentState()->update();
	UNIT::getCurrentBehavir()->update(this);
}

void BOMBER::release()
{
}

void BOMBER::render(HDC hdc)
{
	UNIT::OBJECT::getImage()->frameRenderCenter(hdc, UNIT::OBJECT::getPosX(), UNIT::OBJECT::getPosY(), _nFrameX, static_cast<int>(_eDirection));

}

void BOMBER::renderSelected(HDC hdc)
{
	RECT rc = *UNIT::getCollisionRect();
	rc.left -= 16;
	rc.top -= 16;
	rc.right += 16;
	rc.bottom += 16;
	DrawEdge(hdc, &rc, BDR_RAISEDOUTER, BF_FLAT | BF_TOPLEFT | BF_BOTTOMRIGHT);
}



void BOMBER::allocateState()
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

void BOMBER::allocateBehavier()
{
	UNIT::_arBeHavier[static_cast<int>(UNIT::E_BEHAVIERNUM::E_NONE)] = new BEHAVIER_NONE();
	UNIT::_arBeHavier[static_cast<int>(UNIT::E_BEHAVIERNUM::E_ATTACK)] = new BEHAVIER_ATTACK();
	UNIT::_arBeHavier[static_cast<int>(UNIT::E_BEHAVIERNUM::E_MOVE)] = new BEHAVIER_MOVE_WALK();
	UNIT::_arBeHavier[static_cast<int>(UNIT::E_BEHAVIERNUM::E_HARVEST)] = new BEHAVIER_NONE();
	UNIT::_arBeHavier[static_cast<int>(UNIT::E_BEHAVIERNUM::E_MAGIC)] = new BEHAVIER_NONE();

}

void BOMBER::allocateAnimation()
{//금은 +10 나무는 +15
	setStartIndex(UNIT::E_STATE::E_IDLE, 0);
	setEndIndex(UNIT::E_STATE::E_IDLE, 0);

	setStartIndex(UNIT::E_STATE::E_MOVE, 1);
	setEndIndex(UNIT::E_STATE::E_MOVE, 4);

	setStartIndex(UNIT::E_STATE::E_ATTACK, 5);
	setEndIndex(UNIT::E_STATE::E_ATTACK, 7);

	setStartIndex(UNIT::E_STATE::E_DEATH, 0);
	setEndIndex(UNIT::E_STATE::E_DEATH, 5);

	setFPS(UNIT::E_STATE::E_IDLE, 100.0f);
	setFPS(UNIT::E_STATE::E_MOVE, 0.125f);
	setFPS(UNIT::E_STATE::E_ATTACK, 0.125f);
	setFPS(UNIT::E_STATE::E_DEATH, 0.7f);

	_eDirection = UNIT::E_DIRECTION::E_BOTTOM;
}
