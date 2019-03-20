#include "stdafx.h"
#include "state_hold.h"
#include "unit.h"

STATE_HOLD::STATE_HOLD()
{
}

STATE_HOLD::~STATE_HOLD()
{
}

void STATE_HOLD::start()
{
	_pUnit->setFrameX(_pUnit->getStartIndex(UNIT::E_STATE::E_IDLE));

}

void STATE_HOLD::update()
{
	_fTimer += TIMEMANAGER->getElapsedTime();

	if (_fTimer >= _pUnit->getFPS(UNIT::E_STATE::E_IDLE))
	{
		_fTimer = 0.0f;
		_pUnit->addFrameX(UNIT::E_STATE::E_IDLE);

	}
}
