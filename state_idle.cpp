#include "stdafx.h"
#include "state_idle.h"
#include "unit.h"

STATE_IDLE::STATE_IDLE()
{
}

STATE_IDLE::~STATE_IDLE()
{
}

void STATE_IDLE::start()
{
	_pUnit->setFrameX(_pUnit->getStartIndex(UNIT::E_STATE::E_IDLE));


}

void STATE_IDLE::update()
{
	_fTimer += TIMEMANAGER->getElapsedTime();
	
	if (_fTimer >= _pUnit->getFPS(UNIT::E_STATE::E_IDLE))
	{
		_fTimer = 0.0f;
		_pUnit->addFrameX(UNIT::E_STATE::E_IDLE);
		
	}

	//일꾼일때만 아이들이 3개 이것만 조심하자
	
	_pUnit->searchOppent();
}
