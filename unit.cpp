#include "stdafx.h"
#include "unit.h"
#include "buildMgr.h"
#include "unitMGr.h"

UNIT::UNIT() :
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

void UNIT::commandMove(float fEndPosX, float fEndPosY)
{
	//if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	//{
		_fEndX = fEndPosX;
		_fEndY = fEndPosY;

		setMovePoints(fEndPosX,fEndPosY);
		UNIT::getCurrentBehavir()->end(this);
		if (!UNIT::moveTo()) {
			return;
		}
		UNIT::setCurrentState(UNIT::E_STATENUM::E_MOVE);
		UNIT::setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_MOVE);
		UNIT::setBehavier(UNIT::E_BEHAVIERNUM::E_MOVE);

		UNIT::getCurrentState()->start();
	//}

}

void UNIT::setMovePoints(float fEndPosX, float fEndPosY)
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
	//�ͼ����� ���Ϳ� �ε����� �غ� �Ǿ��ִ�.
	//8������ ������.
	//�𷺼��� ���Ѵ�.
	//�׹������� ��������?
	float elapsedTime = TIMEMANAGER->getElapsedTime();

	//����� �ٽ��Դ���!!! ��κ�!!!
	_fMoveSpeed = (elapsedTime / getSpeed()) * _travelRange;


	OBJECT::setPosX(OBJECT::getPosX() + Mins::presentPowerX(_fDirAngle, _fMoveSpeed));
	OBJECT::setPosY(OBJECT::getPosY() + Mins::presentPowerY(_fDirAngle, _fMoveSpeed));
	UNIT::setCollisionRect(UNIT::getPosX(), UNIT::getPosY(), 32, 32);

}

void UNIT::build(float fPosX, float fPosY, E_BUILDS eBuilds)
{
}

void UNIT::commandBuild()
{
}

bool UNIT::moveTo()
{
	_nMoveVectorIndex++;

	if (_pTarget != nullptr)
	{
		if (getAttackRange() >= getDistance(getPosX(), getPosY(), getTarget()->getPosX(), getTarget()->getPosY())) {
			return false;
		}
	}

	if (_nMoveVectorIndex >= static_cast<int>(_vvMovePoint.size()))
	{
		//OBJECT::setPosX(_vvMovePoint[_nMoveVectorIndex-1][0] );
		//OBJECT::setPosY(_vvMovePoint[_nMoveVectorIndex-1][1] );
		_bIsMoving = false;
		return false;
	}
	_bIsMoving = true;
	_travelRange = getDistance(OBJECT::getPosX() , OBJECT::getPosY(),(float)_vvMovePoint[_nMoveVectorIndex][0] * TILESIZE + 16, (float)_vvMovePoint[_nMoveVectorIndex][1] * TILESIZE + 16);
	

	//������ �����ش�
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

	setMovePoints((float)_fEndX, (float)_fEndY);



	UNIT::getCurrentBehavir()->end(this);
	if (!UNIT::moveTo()) {
		return;
	}
	UNIT::setCurrentState(UNIT::E_STATENUM::E_MOVE);
	UNIT::setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_MOVE);
	UNIT::setBehavier(UNIT::E_BEHAVIERNUM::E_MOVE);

	UNIT::getCurrentState()->start();
}

void UNIT::commandIdle()
{
	UNIT::getCurrentBehavir()->end(this);

	UNIT::setCurrentState(UNIT::E_STATENUM::E_IDLE);
	UNIT::setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_NONE);
	UNIT::setBehavier(UNIT::E_BEHAVIERNUM::E_NONE);

	UNIT::getCurrentState()->start();
	
}

void UNIT::addCommand(COMMAND * pCommand)
{
	_queWaitCommand.push(pCommand);
}

void UNIT::clearCommand()
{
	while (!_queWaitCommand.empty())
	{
		_queWaitCommand.pop();
	}
	commandIdle();

}

void UNIT::attack(OBJECT * pObject)
{

	UNIT::getCurrentBehavir()->end(this);

	UNIT::setCurrentState(UNIT::E_STATENUM::E_ATTACK);
	UNIT::setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_ATTACK);
	UNIT::setBehavier(UNIT::E_BEHAVIERNUM::E_ATTACK);

	UNIT::getCurrentState()->start();



	_pTarget = pObject;
}

void UNIT::targetDirection()
{
	_fDirAngle = getAngle(OBJECT::getPosX(), OBJECT::getPosY(), _pTarget->getPosX(), _pTarget->getPosY());


	if (_fDirAngle >= PI2)
	{
		_fDirAngle -= PI2;
	}
	else if (_fDirAngle < 0) {

		_fDirAngle = PI2 - _fDirAngle;

	}
	float fAngle = (_fDirAngle + PI8) / (PI / 4.0f);
	//fAngle -= 1.0f;

	if (fAngle >= static_cast<float>(E_DIRECTION::E_DEATH))
	{
		fAngle = 7;
	}

	UNIT::_eDirection = static_cast<E_DIRECTION>(static_cast<int>(fAngle));

}

