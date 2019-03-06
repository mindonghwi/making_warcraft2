#include "stdafx.h"
#include "state_move.h"
#include "unit.h"
STATE_MOVE::STATE_MOVE()
{
}

STATE_MOVE::~STATE_MOVE()
{
}

void STATE_MOVE::start()
{
	_pUnit->setFrameX(_pUnit->getStartIndex(UNIT::E_STATE::E_MOVE));
	_fTimer = 0.0f;
}

void STATE_MOVE::update()
{
	_fTimer += TIMEMANAGER->getElapsedTime();

	if (_fTimer >= _pUnit->getFPS(UNIT::E_STATE::E_IDLE))
	{
		_fTimer = 0.0f;
		_pUnit->addFrameX(UNIT::E_STATE::E_IDLE);
	}
}
