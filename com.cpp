#include "stdafx.h"
#include "com.h"

COM::COM()
{
	_bIsTown = false;

}

COM::~COM()
{
}

void COM::update()
{
	//�ϱ����� ���� ȸ���� ��������Ѵ�
	//����ȸ���� �� �������� �ϱ������� ������ ������� ��
	//�ϱ��� �Ѹ��� ������ ������� �Ѵ�.
	//���� �ϱ����� ��ä�븦 ��Ų��
	//����ȸ�������� �ϱ��� 7~ 10�������� �̴���.
	
	commandTownBuild();


	_pUnitMgr->update();
	_pBuildMgr->update();

}

void COM::commandTownBuild()
{
	if (_bIsTown)
	{
		return;
	}
	_pUnitMgr->commandBuildAi(_pUnitMgr->getUnit(UNIT::E_UNIT::E_WORKMAN)->getPosX(), _pUnitMgr->getUnit(UNIT::E_UNIT::E_WORKMAN)->getPosY(), E_BUILDS::E_TOWN, _pUnitMgr->getUnit(UNIT::E_UNIT::E_WORKMAN));
	//_pUnitMgr->getUnit(UNIT::E_UNIT::E_WORKMAN)->build(_pUnitMgr->getUnit(UNIT::E_UNIT::E_WORKMAN)->getPosX(), _pUnitMgr->getUnit(UNIT::E_UNIT::E_WORKMAN)->getPosY(), E_BUILDS::E_TOWN);
	_bIsTown = true;
}

//Ÿ���� ������ �ݱ� �ֺ����� ���´�.
//