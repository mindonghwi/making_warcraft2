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

void UNIT::init(int nPosX, int nPosY, int nWidth, int nHeight, int nIndexNum)
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

	_nIndexNum = nIndexNum;
}

void UNIT::create(int nPosX, int nPosY, int nHp, float fSpeed, int nAttack, int nDefence, float fSearchRange, float fAttackRange, float fAttackSpeedps, int nMinimalAttacks)
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
	setMiniMalAttack(nMinimalAttacks);
}


void UNIT::addFrameX(UNIT::E_STATE eState)
{
	_nFrameX++;

	if (_nFrameX > getEndIndex(eState))
	{
		_nFrameX = getStartIndex(eState);
	}
}

void UNIT::setMovePoints(float fEndPosX, float fEndPosY, int * nCount)
{
	UNIT::setMoveIndex(0);

	_pAstar->startFinder(UNIT::OBJECT::getPosX(), UNIT::OBJECT::getPosY(), fEndPosX, fEndPosY, ASTAR::MOVEHEIGHT::GROUND);
	_pAstar->pathFinder();

	UNIT::_vvMovePoint.clear();


	for (int i = 0; i < _pAstar->getListSize(); i++)
	{
		vector<int> vPos;
		vPos.push_back(_pAstar->getNode(i)->nIndexX);//* TILESIZE + 16);
		vPos.push_back(_pAstar->getNode(i)->nIndexY);//* TILESIZE + 16);
		UNIT::_vvMovePoint.push_back(vPos);
	}
	UNIT::setMoveIndex(0);

}

void UNIT::Move()
{
	//와서하자 벡터와 인덱스는 준비가 되어있다.
	//8가지로 나눈다.
	//디렉션을 구한다.
	//그방향으로 선형보간?

	

	float elapsedTime = TIMEMANAGER->getElapsedTime();

	//요곳이 핵심입뉘다!!! 요로분!!!
	_fMoveSpeed = (elapsedTime / getSpeed()) * _travelRange;


	OBJECT::setPosX(OBJECT::getPosX() + Mins::presentPowerX(_fDirAngle, _fMoveSpeed));
	OBJECT::setPosY(OBJECT::getPosY() + Mins::presentPowerY(_fDirAngle, _fMoveSpeed));
	UNIT::setCollisionRect(UNIT::getPosX(), UNIT::getPosY(), 32, 32);

}

bool UNIT::moveTo()
{
	_nMoveVectorIndex++;

	if (_nMoveVectorIndex >= static_cast<int>(_vvMovePoint.size()))
	{
		//OBJECT::setPosX(_vvMovePoint[_nMoveVectorIndex-1][0] );
		//OBJECT::setPosY(_vvMovePoint[_nMoveVectorIndex-1][1] );
		_bIsMoving = false;
		return false;
	}
	_bIsMoving = true;
	_travelRange = getDistance(OBJECT::getPosX() , OBJECT::getPosY(),(float)_vvMovePoint[_nMoveVectorIndex][0] * TILESIZE + 16, (float)_vvMovePoint[_nMoveVectorIndex][1] * TILESIZE + 16);
	

	//각도도 구해준다
	_fDirAngle = getAngle(OBJECT::getPosX(), OBJECT::getPosY() , (float)_vvMovePoint[_nMoveVectorIndex][0] * TILESIZE + 16, (float)_vvMovePoint[_nMoveVectorIndex][1] * TILESIZE + 16);


	if (_fDirAngle >= PI2)
	{
		_fDirAngle -= PI2;
	}
	else if(_fDirAngle < 0){

		_fDirAngle = PI2 - _fDirAngle;

	}
	float fAngle = (_fDirAngle + PI8) / (PI/4.0f);
	//fAngle -= 1.0f;

	if (fAngle >= static_cast<float>(E_DIRECTION::E_DEATH))
	{
		fAngle = 7;
	}

	UNIT::_eDirection = static_cast<E_DIRECTION>(static_cast<int>(fAngle));
	_fMoveSpeed = 0.0f;


	return true;
}

void UNIT::moveToDir()
{
	UNIT::setMoveIndex(0);

	setMovePoints(_nEndTileIndexX, _nEndTileIndexY,0);



	UNIT::getCurrentBehavir()->end(this);
	if (!UNIT::moveTo()) {
		return;
	}
	UNIT::setCurrentState(UNIT::E_STATENUM::E_MOVE);
	UNIT::setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_MOVE);
	UNIT::setBehavier(UNIT::E_BEHAVIERNUM::E_MOVE);

	UNIT::getCurrentState()->start();
}

