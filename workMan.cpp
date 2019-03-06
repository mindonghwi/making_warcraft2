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

WORKMAN::WORKMAN()
{
}

WORKMAN::~WORKMAN()
{
}

void WORKMAN::init(int nPosX, int nPosY, int nWidth, int nHeight)
{
	UNIT::init(nPosX, nPosY, nWidth, nHeight);

	allocateState();
	allocateBehavier();
	UNIT::setCurrentState(UNIT::E_STATENUM::E_IDLE);
	UNIT::setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_NONE);
}

void WORKMAN::update()
{


}

void WORKMAN::release()
{
}

void WORKMAN::render(HDC hdc)
{
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
}

void WORKMAN::allocateBehavier()
{
	UNIT::_arBeHavier[static_cast<int>(UNIT::E_BEHAVIERNUM::E_NONE)] = new BEHAVIER_NONE();
	UNIT::_arBeHavier[static_cast<int>(UNIT::E_BEHAVIERNUM::E_ATTACK)] = new BEHAVIER_ATTACK();
	UNIT::_arBeHavier[static_cast<int>(UNIT::E_BEHAVIERNUM::E_MOVE)] = new BEHAVIER_MOVE_WALK();
	UNIT::_arBeHavier[static_cast<int>(UNIT::E_BEHAVIERNUM::E_HARVEST)] = new BEHAVIER_ATTACK();
	UNIT::_arBeHavier[static_cast<int>(UNIT::E_BEHAVIERNUM::E_MAGIC)] = new BEHAVIER_NONE();
}
