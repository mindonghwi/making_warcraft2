#include "stdafx.h"
#include "unit.h"
#include "buildMgr.h"
#include "unitMGr.h"
#include "bulletMgr.h"
#include "player.h"

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
	setMaxHp(0);
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
	setMaxHp(nHp);
}

void UNIT::release()
{
	while (!_queWaitCommand.empty())
	{
		COMMAND* pCommand = _queWaitCommand.front();
		_queWaitCommand.pop();
		_pUnitMgr->returnPool(pCommand);
	}
	_pCamera = nullptr;
	_pAstar = nullptr;
	_pUnitMgr = nullptr;
	_pMap = nullptr;
	_pTarget = nullptr;
	_pResourceMgr = nullptr;
	_pPlayer = nullptr;
	_pBuildMgr = nullptr;

	OBJECT::setPosX(0.0f);
	OBJECT::setPosY(0.0f);
	OBJECT::setImage(nullptr);

	for (int i = 0; i <static_cast<int>(UNIT::E_STATENUM::E_MAX); i++)
	{
		delete _arState[i];
		_arState[i] = nullptr;
	}
	for (int i = 0; i <static_cast<int>(UNIT::E_BEHAVIERNUM::E_MAX); i++)
	{
		delete _arBeHavier[i];
		_arBeHavier[i] = nullptr;
	}
}


void UNIT::addFrameX(UNIT::E_STATE eState)
{
	_nFrameX++;

	if (_nFrameX > getEndIndex(eState))
	{
		_nFrameX = getStartIndex(eState);
	}
}

void UNIT::decreaseHp(int nHp)
{
	int nDecreaseHp = nHp - _nDefence;
	if (nDecreaseHp < 1)
	{
		nDecreaseHp = 1;
	}
	OBJECT::_nHp -= nDecreaseHp;
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
		removeMapUnitData();
		UNIT::setCurrentState(UNIT::E_STATENUM::E_MOVE);
		UNIT::setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_MOVE);
		UNIT::setBehavier(UNIT::E_BEHAVIERNUM::E_MOVE);

		UNIT::getCurrentState()->start();
	//}

}

void UNIT::command()
{
}

void UNIT::setMovePoints(float fEndPosX, float fEndPosY)
{
	UNIT::setMoveIndex(0);

	if (_eUnit == E_UNIT::E_FLYER || _eUnit == E_UNIT::E_RECONNAISSANCE)
	{
		_pAstar->startFinder(UNIT::OBJECT::getPosX(), UNIT::OBJECT::getPosY(), fEndPosX, fEndPosY, ASTAR::MOVEHEIGHT::FLY);
	}

	else if (_eUnit==E_UNIT::E_BATTLESHIP || _eUnit == E_UNIT::E_GALLEYS || _eUnit == E_UNIT::E_OILTANKER || _eUnit == E_UNIT::E_TRANSPORT|| _eUnit == E_UNIT::E_SUBMARIN)
	{
		_pAstar->startFinder(UNIT::OBJECT::getPosX(), UNIT::OBJECT::getPosY(), fEndPosX, fEndPosY, ASTAR::MOVEHEIGHT::WATER);
	}
	else
	{
		_pAstar->startFinder(UNIT::OBJECT::getPosX(), UNIT::OBJECT::getPosY(), fEndPosX, fEndPosY, ASTAR::MOVEHEIGHT::GROUND);
	}

	_pAstar->pathFinder();

	UNIT::_vvMovePoint.clear();


	for (int i = 0; i < _pAstar->getListSize(); i++)
	{
		vector<int> vPos;
		vPos.push_back(_pAstar->getNode(i)->nIndexX);//* TILESIZE + 16);
		vPos.push_back(_pAstar->getNode(i)->nIndexY);//* TILESIZE + 16);
		UNIT::_vvMovePoint.push_back(vPos);
	}

	if ((int)UNIT::_vvMovePoint.size() == 1)
	{
		bool bIsPrison = false;
		for (int i = -1; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (_pMap->getTile(_vvMovePoint[0][0]+i, _vvMovePoint[0][1]+j)->getObject() == TILE::E_OBJECT::E_NONE)
				{
					bIsPrison = true;

					break;
				}
			}
			if (bIsPrison)
			{
				break;
			}
		}

		if (!bIsPrison) {
			vector<int> vPos;
			vPos.push_back(_pAstar->getNode(0)->nIndexX + 1);
			vPos.push_back(_pAstar->getNode(0)->nIndexY + 1);
			UNIT::_vvMovePoint.push_back(vPos);
		}
	}

	UNIT::setMoveIndex(0);

}

void UNIT::setMovePoints(float fEndPosX, float fEndPosY, ASTAR::MOVEHEIGHT eMoveHeight)
{

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

	setMovePoints((float)_fEndX, (float)_fEndY);
	removeMapUnitData();


	//UNIT::getCurrentBehavir()->end(this);
	if (!UNIT::moveTo()) {
		return;
	}
	UNIT::setCurrentState(UNIT::E_STATENUM::E_MOVE);
	UNIT::setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_MOVE);
	UNIT::setBehavier(UNIT::E_BEHAVIERNUM::E_MOVE);
	setIsHold(false);
	UNIT::getCurrentState()->start();
}

void UNIT::commandIdle()
{
	UNIT::getCurrentBehavir()->end(this);

	UNIT::setCurrentState(UNIT::E_STATENUM::E_IDLE);
	UNIT::setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_NONE);
	UNIT::setBehavier(UNIT::E_BEHAVIERNUM::E_NONE);
	setIsHold(false);
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
		COMMAND* pCommand = _queWaitCommand.front();
		_queWaitCommand.pop();
		_pUnitMgr->returnPool(pCommand);
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
	if (_pTarget == nullptr)
	{
		return;
	}
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
		fAngle = static_cast<float>(E_DIRECTION::E_RIGHT);
	}

	UNIT::_eDirection = static_cast<E_DIRECTION>(static_cast<int>(fAngle));

}

void UNIT::harvestResources()
{
}

void UNIT::commandHarvest()
{
}

void UNIT::commandReturnHarvest()
{
}

bool UNIT::IsNearResources()
{
	if (_eHarvest == E_HARVEST::E_GOLD)
	{
		OBJECT* pObject = _pResourceMgr->getfindNearGoldMine(getPosX(), getPosY());
		if (Mins::getDoubleDis(pObject->getPosX(), pObject->getPosY(),getPosX(),getPosY()) >= TILESIZE * TILESIZE)
		{
			return false;
		}
	}
	else if (_eHarvest == E_HARVEST::E_TREE)
	{
		OBJECT* pObject = _pResourceMgr->getfindNearTree(getPosX(), getPosY());
		RECT rc;
		RECT rcTmp = *_pTarget->getRect();
		rcTmp.left -= 8;
		rcTmp.top -= 8;
		rcTmp.bottom += 8;
		rcTmp.right  += 8;

		if (IntersectRect(&rc, &rcTmp, getCollisionRect()))
		{
			return false;
		}
	}

	return true;
}

void UNIT::updateRect()
{
	OBJECT::settingRect();
}

void UNIT::removeMapUnitData()
{
	if (_pMap->getTile(getPosX() / TILESIZE, getPosY() / TILESIZE)->getObject() == TILE::E_OBJECT::E_UNIT)
	{
		_pMap->getTile(getPosX() / TILESIZE, getPosY() / TILESIZE)->setObject(TILE::E_OBJECT::E_NONE);
	}
}

void UNIT::addMapUnitData()
{
	if (_pMap->getTile(getPosX() / TILESIZE, getPosY() / TILESIZE)->getObject() == TILE::E_OBJECT::E_NONE)
	{
		_pMap->getTile(getPosX() / TILESIZE, getPosY() / TILESIZE)->setObject(TILE::E_OBJECT::E_UNIT);
	}
}

void UNIT::fireBullet()
{
	if (getUnit() == E_UNIT::E_ARCHER)
	{
		_pBulletMgr->fire("arrows", getPosX(), getPosY(), getTarget());
	}
	else if (getUnit() == E_UNIT::E_BALLISTA)
	{
		_pBulletMgr->fire("ballises", getPosX(), getPosY(), getTarget());
	}
	else if (getUnit() == E_UNIT::E_BATTLESHIP ||
		getUnit() == E_UNIT::E_GALLEYS)
	{
		_pBulletMgr->fire("bullet", getPosX(), getPosY(), getTarget());
	}
	else if (getUnit() == E_UNIT::E_MAGICIAN)
	{
		_pBulletMgr->fire("fireBall", getPosX(), getPosY(), getTarget());
	}
	else if (getUnit() == E_UNIT::E_FLYER)
	{
		//_pBulletMgr->fire("axe", getPosX(), getPosY(), getTarget());
		_pBulletMgr->fire("axe", getPosX(), getPosY(), _pPlayer->getOpponent(), getTarget()->getPosX(), getTarget()->getPosY());
	}
}

void UNIT::searchOppent()
{
	//if (getUnit() == E_UNIT::E_WORKMAN || getUnit() == E_UNIT::E_RECONNAISSANCE || getUnit() == E_UNIT::E_OILTANKER || getUnit() == E_UNIT::E_TRANSPORT)
	//{
	//	return;
	//}
	for (int i = 0; i < _pOpponent->getUnitMgr()->getUnitCount(); i++)
	{
		float fDoubleSearchRange = getSearchRange() * getSearchRange();
		if (fDoubleSearchRange >= Mins::getDoubleDis(getPosX(), getPosY(), _pOpponent->getUnitMgr()->getUnit(i)->getPosX(), _pOpponent->getUnitMgr()->getUnit(i)->getPosY()))
		{
			//clearCommand();
			_pUnitMgr->commandAatackNonMove(this,_pOpponent->getUnitMgr()->getUnit(i));
			break;
		}
	}

}

void UNIT::commandHold()
{

	UNIT::getCurrentBehavir()->end(this);

	UNIT::setCurrentState(UNIT::E_STATENUM::E_HOLD);
	UNIT::setCurrentBehavir(UNIT::E_BEHAVIERNUM::E_HOLD);
	UNIT::setBehavier(UNIT::E_BEHAVIERNUM::E_HOLD);

	UNIT::getCurrentState()->start();
}

void UNIT::commandTransport()
{
	
}

void UNIT::commandTransportIn()
{
}

void UNIT::commandTransportOut(int nMapIndexX, int nMapIndexY)
{
}

