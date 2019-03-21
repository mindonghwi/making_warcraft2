#include "stdafx.h"
#include "state_none.h"
#include "unit.h"

STATE_NONE::STATE_NONE()
{
}

STATE_NONE::~STATE_NONE()
{
}

void STATE_NONE::start()
{
	_pUnit->setFrameX(_pUnit->getStartIndex(UNIT::E_STATE::E_IDLE));
	_pUnit->setPosX(-2000);
	_pUnit->setPosY(-2000);

}

void STATE_NONE::update()
{
	_fTimer += TIMEMANAGER->getElapsedTime();

	if (_fTimer >= _pUnit->getFPS(UNIT::E_STATE::E_IDLE))
	{
		_fTimer = 0.0f;
		_pUnit->addFrameX(UNIT::E_STATE::E_IDLE);
	}
	

}
