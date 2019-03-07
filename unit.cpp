#include "stdafx.h"
#include "unit.h"
UNIT::UNIT() :
	_nHp(0),
	_nAttack(0),
	_nDefence(0),
	_fSpeed(0.0f),
	_fSearchRange(0.0f),
	_fAttackRange(0.0f),
	_fAttackSpeedps(0.0f),
	_arState{}
{
}

UNIT::~UNIT()
{
}

void UNIT::init(int nPosX, int nPosY, int nWidth, int nHeight)
{
	OBJECT::init(static_cast<float>(nPosX), static_cast<float>(nPosY), nWidth, nHeight);
	OBJECT::settingRect();

	setHp(0);
	setAttack(0);
	setDefence(0);
	setSpeed(0.0f);
	setSearchRange(0.0f);
	setAttackRange(0.0f);
	setAttackSpeedps(0.0f);
	_vvMovePoint.clear();
}

void UNIT::create(int nPosX, int nPosY, int nHp, float fSpeed, int nAttack, int nDefence, float fSearchRange, float fAttackRange, float fAttackSpeedps)
{
	OBJECT::setPosX(static_cast<float>(nPosX));
	OBJECT::setPosY(static_cast<float>(nPosY));
	OBJECT::settingRect();
	UNIT::setCollisionRect(UNIT::getPosX(), UNIT::getPosY(), 32, 32);

	setHp(nHp);
	setAttack(nAttack);
	setDefence(nDefence);
	setSpeed(fSpeed);
	setSearchRange(fSearchRange);
	setAttackRange(fAttackRange);
	setAttackSpeedps(fAttackSpeedps);
}


void UNIT::addFrameX(UNIT::E_STATE eState)
{
	_nFrameX++;

	if (_nFrameX > getEndIndex(eState))
	{
		_nFrameX = getStartIndex(eState);
	}
}

void UNIT::Move()
{
	//�ͼ����� ���Ϳ� �ε����� �غ� �Ǿ��ִ�.
	//8������ ������.
	//�𷺼��� ���Ѵ�.
	//�׹������� ��������?
	float elapsedTime = TIMEMANAGER->getElapsedTime();

	//����� �ٽ��Դ���!!! ��κ�!!!
	float moveSpeed = (elapsedTime / getSpeed()) * _travelRange;


	OBJECT::setPosX(OBJECT::getPosX() + Mins::presentPowerX(_fDirAngle, moveSpeed));
	OBJECT::setPosY(OBJECT::getPosY() + Mins::presentPowerY(_fDirAngle, moveSpeed));
	UNIT::setCollisionRect(UNIT::getPosX(), UNIT::getPosY(), 32, 32);

}

bool UNIT::moveTo()
{
	_nMoveVectorIndex++;
	if (_nMoveVectorIndex >= static_cast<int>(_vvMovePoint.size()))
	{
		OBJECT::setPosX(_vvMovePoint[_nMoveVectorIndex-1][0] );
		OBJECT::setPosY(_vvMovePoint[_nMoveVectorIndex-1][1] );

		return false;
	}

	_travelRange = getDistance(OBJECT::getPosX() , OBJECT::getPosY(),_vvMovePoint[_nMoveVectorIndex][0], _vvMovePoint[_nMoveVectorIndex][1]);

	//������ �����ش�
	_fDirAngle = getAngle(OBJECT::getPosX(), OBJECT::getPosY() , _vvMovePoint[_nMoveVectorIndex][0], _vvMovePoint[_nMoveVectorIndex][1]);


	return true;
}
