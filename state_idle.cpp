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

	//�ϲ��϶��� ���̵��� 3�� �̰͸� ��������
	
	_pUnit->searchOppent();
}
