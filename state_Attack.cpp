#include "stdafx.h"
#include "state_Attack.h"
#include "unit.h"

STATE_ATTACK::STATE_ATTACK()
{
}

STATE_ATTACK::~STATE_ATTACK()
{
}

void STATE_ATTACK::start()
{
	_pUnit->setFrameX(_pUnit->getStartIndex(UNIT::E_STATE::E_ATTACK));
	_fTimer = 0.0f;
	if (_pUnit->getTarget() == nullptr)
	{
		_pUnit->commandIdle();
	}
	else
	{
		_pUnit->targetDirection();
	}
}

void STATE_ATTACK::update()
{
	_fTimer += TIMEMANAGER->getElapsedTime();

	if (_fTimer >= _pUnit->getFPS(UNIT::E_STATE::E_ATTACK))
	{
		_fTimer = 0.0f;
		_pUnit->targetDirection();
		_pUnit->addFrameX(UNIT::E_STATE::E_ATTACK);
	}
}

