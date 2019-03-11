#include "stdafx.h"
#include "unitMGr.h"

#include "workMan.h"
#include "map.h"

UNITMGR::UNITMGR()
{
}

UNITMGR::~UNITMGR()
{
}

void UNITMGR::init()
{

	allocateUnitResource();
	allocateUnitPopulation();
	allocateUnitStatus();
	_ptCameraPtMouse.x = _ptMouse.x + _pCamera->getLeft();
	_ptCameraPtMouse.y = _ptMouse.y + _pCamera->getTop();
	allocateIntervalMove();
	_nCount = 0;

}

bool UNITMGR::createUnit(UNIT::E_UNIT eUnit, float fPosX, float fPosY)
{
	switch (eUnit)
	{
	case UNIT::E_UNIT::E_WORKMAN:
		_listUnit.push_back(new WORKMAN);
		break;
	case UNIT::E_UNIT::E_FOOTMAN:
		break;
	case UNIT::E_UNIT::E_ARCHER:
		break;
	case UNIT::E_UNIT::E_BALLISTA:
		break;
	case UNIT::E_UNIT::E_KNIGHT:
		break;
	case UNIT::E_UNIT::E_MAGICIAN:
		break;
	case UNIT::E_UNIT::E_BOMBER:
		break;
	case UNIT::E_UNIT::E_RECONNAISSANCE:
		break;
	case UNIT::E_UNIT::E_OILTANKER:
		break;
	case UNIT::E_UNIT::E_GALLEYS:
		break;
	case UNIT::E_UNIT::E_TRANSPORT:
		break;
	case UNIT::E_UNIT::E_BATTLESHIP:
		break;
	case UNIT::E_UNIT::E_SUBMARIN:
		break;
	case UNIT::E_UNIT::E_FLYER:
		break;
	}

	_listUnit.back()->setLinkCamera(_pCamera);
	_listUnit.back()->setLinkAStar(_pAstar);
	_listUnit.back()->init(static_cast<int>(fPosX), static_cast<int>(fPosY), 64, 64, _nCount);
	_listUnit.back()->create(static_cast<int>(fPosX), static_cast<int>(fPosY), _arUnitHp[static_cast<int>(eUnit)], _arUnitSpeed[static_cast<int>(eUnit)],
		_arUnitAttack[static_cast<int>(eUnit)], _arUnitDefence[static_cast<int>(eUnit)], _arSearchRange[static_cast<int>(eUnit)], _arAttackRange[static_cast<int>(eUnit)], _arAttackSpeed[static_cast<int>(eUnit)],
		_arUnitMinimalAttack[static_cast<int>(eUnit)]);

	_nCount++;
	return false;
}

void UNITMGR::update()
{

	//선택된 애들 선택되었다고 표시
	//selectedUnit();
	//
	//commandSelectUnit();

	list<UNIT*>::iterator	iterUnitList = _listUnit.begin();
	list<UNIT*>::iterator	endUnitList = _listUnit.end();
	while (iterUnitList != endUnitList)
	{
		UNIT* pUnit = *iterUnitList;
		list<UNIT*>::iterator	iterUnitListCollision = _listUnit.begin();
		list<UNIT*>::iterator	endUnitListCollision = _listUnit.end();
		RECT _rc;
		bool bIsOk = false;
		while (iterUnitListCollision != endUnitListCollision)
		{
			UNIT* pCollUnit = *iterUnitListCollision;

			if (pUnit->getIndexNum() != pCollUnit->getIndexNum())
			{

				//RECT rcTmp = RectMakeCenter(pUnit->getPosX()+Mins::presentPowerX(pUnit->getDirAngle(), pUnit->getMoveSpeed()) , pUnit->getPosY() + Mins::presentPowerY(pUnit->getDirAngle(), pUnit->getMoveSpeed()),3, 3);
				RECT rcTmpA =  *pCollUnit->getCollisionRect();
				RECT rcTmp = _pMap->getTile((int)pCollUnit->getPosX() / TILESIZE, (int)pCollUnit->getPosY() / TILESIZE)->getRectTile();
				rcTmpA.left += 12;
				rcTmpA.right -= 12;
				rcTmpA.top+= 12;
				rcTmpA.bottom -= 12;

				if (pUnit->getBehavier() == UNIT::E_BEHAVIERNUM::E_MOVE)
				{
					if (pCollUnit->getBehavier() != UNIT::E_BEHAVIERNUM::E_MOVE)
					{
						if (IntersectRect(&_rc, & _pMap->getTile(pUnit->getMoveToPointEndX(), pUnit->getMoveToPointEndY())->getRectTile(), &rcTmpA))
						{
							bIsOk = true;
							pUnit->moveToDir();
							break;
						}
					}
					else if (!pCollUnit->getIsMovePointEmpty())
					{
						if (IntersectRect(&_rc, &_pMap->getTile(pCollUnit->getMoveToPointEndX() / TILESIZE, pCollUnit->getMoveToPointEndY() / TILESIZE)->getRectTile(), &rcTmpA))
						{
							bIsOk = true;
							pUnit->moveToDir();
							break;
						}
					}
					else if (IntersectRect(&_rc, &rcTmpA, pUnit->getCollisionRect()))
					{
						bIsOk = true;
						pUnit->moveToDir();
						break;
					}
				}
				
			}
			iterUnitListCollision++;
		}



		pUnit->updateBehavier();
		pUnit->update();
		iterUnitList++;
	}




}

void UNITMGR::release()
{
	_vSeletedUnit.clear();

	while (!_listUnit.empty())
	{
		UNIT* pUnit = _listUnit.front();
		pUnit->release();
		_listUnit.pop_front();
		delete pUnit;
		pUnit = nullptr;
	}

}

void UNITMGR::render(HDC hdc)
{
	for (int i = 0; i < static_cast<int>(_vSeletedUnit.size()); i++)
	{
		(*(_vSeletedUnit[i]))->renderSelected(hdc);
	}

}

void UNITMGR::selectedUnit()
{
	for (int i = 0; i < static_cast<int>(_vSeletedUnit.size()); i++)
	{
		(*(_vSeletedUnit[i]))->setSelected(true);
	}
}

void UNITMGR::commandSelectUnit()
{
	int nData = 0;
	for (int i = 0; i < static_cast<int>(_vSeletedUnit.size()); i++)
	{
		(*(_vSeletedUnit[i]))->commandMove(&nData);
		nData++;
	}
}

void UNITMGR::allocateUnitPopulation()
{
	for (int i = 0; i < static_cast<int>(UNIT::E_UNIT::E_MAX); i++)
	{
		_arUnitPopulation[i] = 2;
	}

	_arUnitPopulation[static_cast<int>(UNIT::E_UNIT::E_BALLISTA)] = 3;
	_arUnitPopulation[static_cast<int>(UNIT::E_UNIT::E_KNIGHT)] = 3;
	_arUnitPopulation[static_cast<int>(UNIT::E_UNIT::E_MAGICIAN)] = 3;
	_arUnitPopulation[static_cast<int>(UNIT::E_UNIT::E_FLYER)] = 3;
	_arUnitPopulation[static_cast<int>(UNIT::E_UNIT::E_BATTLESHIP)] = 3;
	_arUnitPopulation[static_cast<int>(UNIT::E_UNIT::E_SUBMARIN)] = 3;


	_arUnitPopulation[static_cast<int>(UNIT::E_UNIT::E_WORKMAN)] = 1;
	_arUnitPopulation[static_cast<int>(UNIT::E_UNIT::E_FOOTMAN)] = 1;
}

void UNITMGR::allocateUnitResource()
{
	for (int i = 0; i < static_cast<int>(UNIT::E_UNIT::E_MAX); i++)
	{
		for (int j = 0; j < static_cast<int>(E_RESOURCE::E_MAX); j++)
		{
			_arUnitResource[i][j] = 0;
		}
	}

	//workman
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_WORKMAN)][static_cast<int>(E_RESOURCE::E_GOLD)] = 400;

	//footman
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_FOOTMAN)][static_cast<int>(E_RESOURCE::E_GOLD)] = 600;

	//archer
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_ARCHER)][static_cast<int>(E_RESOURCE::E_GOLD)] = 500;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_ARCHER)][static_cast<int>(E_RESOURCE::E_TREE)] = 50;

	//ballista
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_BALLISTA)][static_cast<int>(E_RESOURCE::E_GOLD)] = 900;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_BALLISTA)][static_cast<int>(E_RESOURCE::E_TREE)] = 300;

	//knight
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_KNIGHT)][static_cast<int>(E_RESOURCE::E_GOLD)] = 800;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_KNIGHT)][static_cast<int>(E_RESOURCE::E_TREE)] = 100;

	//bomber
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_BOMBER)][static_cast<int>(E_RESOURCE::E_GOLD)] = 750;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_BOMBER)][static_cast<int>(E_RESOURCE::E_TREE)] = 50;

	//ditecter
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_RECONNAISSANCE)][static_cast<int>(E_RESOURCE::E_GOLD)] = 500;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_RECONNAISSANCE)][static_cast<int>(E_RESOURCE::E_TREE)] = 100;

	//mage
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_MAGICIAN)][static_cast<int>(E_RESOURCE::E_GOLD)] = 1200;

	//flyer
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_FLYER)][static_cast<int>(E_RESOURCE::E_GOLD)] = 2500;

	//oiltanger
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_OILTANKER)][static_cast<int>(E_RESOURCE::E_GOLD)] = 400;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_OILTANKER)][static_cast<int>(E_RESOURCE::E_TREE)] = 250;

	//transport
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_TRANSPORT)][static_cast<int>(E_RESOURCE::E_GOLD)] = 400;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_TRANSPORT)][static_cast<int>(E_RESOURCE::E_TREE)] = 250;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_TRANSPORT)][static_cast<int>(E_RESOURCE::E_OIL)] = 400;

	//galleys
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_GALLEYS)][static_cast<int>(E_RESOURCE::E_GOLD)] = 700;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_GALLEYS)][static_cast<int>(E_RESOURCE::E_TREE)] = 350;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_GALLEYS)][static_cast<int>(E_RESOURCE::E_OIL)] = 700;

	//battleShip
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_BATTLESHIP)][static_cast<int>(E_RESOURCE::E_GOLD)] = 1000;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_BATTLESHIP)][static_cast<int>(E_RESOURCE::E_TREE)] = 500;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_BATTLESHIP)][static_cast<int>(E_RESOURCE::E_OIL)] = 1000;

	//SubMarine
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_SUBMARIN)][static_cast<int>(E_RESOURCE::E_GOLD)] = 800;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_SUBMARIN)][static_cast<int>(E_RESOURCE::E_TREE)] = 150;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_SUBMARIN)][static_cast<int>(E_RESOURCE::E_OIL)] = 800;
}

void UNITMGR::allocateUnitStatus()
{
	//workman
	//hp는 40 방어력 0 최소공격력 1 공격력 2 생산시간 10초 한타일 이동 속도 0.3f 찾는 범위 128 공격 범위 48 공격속도 1초
	_arUnitHp[static_cast<const int>(UNIT::E_UNIT::E_WORKMAN)]				=40;
	_arUnitDefence[static_cast<const int>(UNIT::E_UNIT::E_WORKMAN)]			=0;
	_arUnitMinimalAttack[static_cast<const int>(UNIT::E_UNIT::E_WORKMAN)] = 1;
	_arUnitAttack[static_cast<const int>(UNIT::E_UNIT::E_WORKMAN)]			=2;
	_arUnitProductionTime[static_cast<const int>(UNIT::E_UNIT::E_WORKMAN)] = 10;
	_arUnitSpeed[static_cast<const int>(UNIT::E_UNIT::E_WORKMAN)]			=0.3f;
	_arSearchRange[static_cast<const int>(UNIT::E_UNIT::E_WORKMAN)]			=128.0f;
	_arAttackRange[static_cast<const int>(UNIT::E_UNIT::E_WORKMAN)]			=48.0f;
	_arAttackSpeed[static_cast<const int>(UNIT::E_UNIT::E_WORKMAN)]			= 1.0f;


	//footman
	_arUnitHp[static_cast<const int>(UNIT::E_UNIT::E_FOOTMAN)] = 60;
	_arUnitDefence[static_cast<const int>(UNIT::E_UNIT::E_FOOTMAN)] = 2;
	_arUnitMinimalAttack[static_cast<const int>(UNIT::E_UNIT::E_FOOTMAN)] = 1;
	_arUnitAttack[static_cast<const int>(UNIT::E_UNIT::E_FOOTMAN)] = 9;
	_arUnitProductionTime[static_cast<const int>(UNIT::E_UNIT::E_FOOTMAN)] = 15;
	_arUnitSpeed[static_cast<const int>(UNIT::E_UNIT::E_FOOTMAN)] = 0.3f;
	_arSearchRange[static_cast<const int>(UNIT::E_UNIT::E_FOOTMAN)] = 128.0f;
	_arAttackRange[static_cast<const int>(UNIT::E_UNIT::E_FOOTMAN)] = 48.0f;
	_arAttackSpeed[static_cast<const int>(UNIT::E_UNIT::E_FOOTMAN)] = 1.0f;

	//archer
	_arUnitHp[static_cast<const int>(UNIT::E_UNIT::E_ARCHER)] = 40;
	_arUnitDefence[static_cast<const int>(UNIT::E_UNIT::E_ARCHER)] = 0;
	_arUnitMinimalAttack[static_cast<const int>(UNIT::E_UNIT::E_ARCHER)] = 3;
	_arUnitAttack[static_cast<const int>(UNIT::E_UNIT::E_ARCHER)] = 9;
	_arUnitProductionTime[static_cast<const int>(UNIT::E_UNIT::E_ARCHER)] = 15;
	_arUnitSpeed[static_cast<const int>(UNIT::E_UNIT::E_ARCHER)] = 0.3f;
	_arSearchRange[static_cast<const int>(UNIT::E_UNIT::E_ARCHER)] = 128.0f;
	_arAttackRange[static_cast<const int>(UNIT::E_UNIT::E_ARCHER)] = 96.0f;
	_arAttackSpeed[static_cast<const int>(UNIT::E_UNIT::E_ARCHER)] = 1.0f;


	//ballista
	_arUnitHp[static_cast<const int>(UNIT::E_UNIT::E_BALLISTA)] = 110;
	_arUnitDefence[static_cast<const int>(UNIT::E_UNIT::E_BALLISTA)] = 0;
	_arUnitMinimalAttack[static_cast<const int>(UNIT::E_UNIT::E_BALLISTA)] = 25;
	_arUnitAttack[static_cast<const int>(UNIT::E_UNIT::E_BALLISTA)] = 80;
	_arUnitProductionTime[static_cast<const int>(UNIT::E_UNIT::E_BALLISTA)] = 30;
	_arUnitSpeed[static_cast<const int>(UNIT::E_UNIT::E_BALLISTA)] = 0.6f;
	_arSearchRange[static_cast<const int>(UNIT::E_UNIT::E_BALLISTA)] = 160.0f;
	_arAttackRange[static_cast<const int>(UNIT::E_UNIT::E_BALLISTA)] = 128.0f;
	_arAttackSpeed[static_cast<const int>(UNIT::E_UNIT::E_BALLISTA)] = 2.0f;

	//knight
	_arUnitHp[static_cast<const int>(UNIT::E_UNIT::E_KNIGHT)] = 90;
	_arUnitDefence[static_cast<const int>(UNIT::E_UNIT::E_KNIGHT)] = 4;
	_arUnitMinimalAttack[static_cast<const int>(UNIT::E_UNIT::E_KNIGHT)] = 2;
	_arUnitAttack[static_cast<const int>(UNIT::E_UNIT::E_KNIGHT)] = 12;
	_arUnitProductionTime[static_cast<const int>(UNIT::E_UNIT::E_KNIGHT)] = 20;
	_arUnitSpeed[static_cast<const int>(UNIT::E_UNIT::E_KNIGHT)] = 0.2f;
	_arSearchRange[static_cast<const int>(UNIT::E_UNIT::E_KNIGHT)] = 128.0f;
	_arAttackRange[static_cast<const int>(UNIT::E_UNIT::E_KNIGHT)] = 48.0f;
	_arAttackSpeed[static_cast<const int>(UNIT::E_UNIT::E_KNIGHT)] = 0.5f;


	//bomber
	_arUnitHp[static_cast<const int>(UNIT::E_UNIT::E_BOMBER)] = 40;
	_arUnitDefence[static_cast<const int>(UNIT::E_UNIT::E_BOMBER)] = 0;
	_arUnitMinimalAttack[static_cast<const int>(UNIT::E_UNIT::E_BOMBER)] = 1;
	_arUnitAttack[static_cast<const int>(UNIT::E_UNIT::E_BOMBER)] = 6;
	_arUnitProductionTime[static_cast<const int>(UNIT::E_UNIT::E_BOMBER)] = 20;
	_arUnitSpeed[static_cast<const int>(UNIT::E_UNIT::E_BOMBER)] = 0.2f;
	_arSearchRange[static_cast<const int>(UNIT::E_UNIT::E_BOMBER)] = 128.0f;
	_arAttackRange[static_cast<const int>(UNIT::E_UNIT::E_BOMBER)] = 48.0f;
	_arAttackSpeed[static_cast<const int>(UNIT::E_UNIT::E_BOMBER)] = 1.0f;


	//ditecter
	_arUnitHp[static_cast<const int>(UNIT::E_UNIT::E_RECONNAISSANCE)] = 150;
	_arUnitDefence[static_cast<const int>(UNIT::E_UNIT::E_RECONNAISSANCE)] = 2;
	_arUnitMinimalAttack[static_cast<const int>(UNIT::E_UNIT::E_RECONNAISSANCE)] = 0;
	_arUnitAttack[static_cast<const int>(UNIT::E_UNIT::E_RECONNAISSANCE)] = 0;
	_arUnitProductionTime[static_cast<const int>(UNIT::E_UNIT::E_RECONNAISSANCE)] = 20;
	_arUnitSpeed[static_cast<const int>(UNIT::E_UNIT::E_RECONNAISSANCE)] = 0.1f;
	_arSearchRange[static_cast<const int>(UNIT::E_UNIT::E_RECONNAISSANCE)] = 160.0f;
	_arAttackRange[static_cast<const int>(UNIT::E_UNIT::E_RECONNAISSANCE)] = 0.0f;
	_arAttackSpeed[static_cast<const int>(UNIT::E_UNIT::E_RECONNAISSANCE)] = 100.0f;

	//mage
	_arUnitHp[static_cast<const int>(UNIT::E_UNIT::E_MAGICIAN)] = 60;
	_arUnitDefence[static_cast<const int>(UNIT::E_UNIT::E_MAGICIAN)] = 0;
	_arUnitMinimalAttack[static_cast<const int>(UNIT::E_UNIT::E_MAGICIAN)] = 5;
	_arUnitAttack[static_cast<const int>(UNIT::E_UNIT::E_MAGICIAN)] = 9;
	_arUnitProductionTime[static_cast<const int>(UNIT::E_UNIT::E_MAGICIAN)] = 30;
	_arUnitSpeed[static_cast<const int>(UNIT::E_UNIT::E_MAGICIAN)] = 0.3f;
	_arSearchRange[static_cast<const int>(UNIT::E_UNIT::E_MAGICIAN)] = 128.0f;
	_arAttackRange[static_cast<const int>(UNIT::E_UNIT::E_MAGICIAN)] = 96.0f;
	_arAttackSpeed[static_cast<const int>(UNIT::E_UNIT::E_MAGICIAN)] = 1.0f;

	//flyer
	_arUnitHp[static_cast<const int>(UNIT::E_UNIT::E_FLYER)] = 100;
	_arUnitDefence[static_cast<const int>(UNIT::E_UNIT::E_FLYER)] = 5;
	_arUnitMinimalAttack[static_cast<const int>(UNIT::E_UNIT::E_FLYER)] = 8;
	_arUnitAttack[static_cast<const int>(UNIT::E_UNIT::E_FLYER)] = 16;
	_arUnitProductionTime[static_cast<const int>(UNIT::E_UNIT::E_FLYER)] = 40;
	_arUnitSpeed[static_cast<const int>(UNIT::E_UNIT::E_FLYER)] = 0.2f;
	_arSearchRange[static_cast<const int>(UNIT::E_UNIT::E_FLYER)] = 160.0f;
	_arAttackRange[static_cast<const int>(UNIT::E_UNIT::E_FLYER)] = 96.0f;
	_arAttackSpeed[static_cast<const int>(UNIT::E_UNIT::E_FLYER)] = 1.5f;

	//oiltanger
	_arUnitHp[static_cast<const int>(UNIT::E_UNIT::E_OILTANKER)] = 90;
	_arUnitDefence[static_cast<const int>(UNIT::E_UNIT::E_OILTANKER)] = 0;
	_arUnitMinimalAttack[static_cast<const int>(UNIT::E_UNIT::E_OILTANKER)] = 0;
	_arUnitAttack[static_cast<const int>(UNIT::E_UNIT::E_OILTANKER)] = 0;
	_arUnitProductionTime[static_cast<const int>(UNIT::E_UNIT::E_OILTANKER)] = 20;
	_arUnitSpeed[static_cast<const int>(UNIT::E_UNIT::E_OILTANKER)] = 0.5f;
	_arSearchRange[static_cast<const int>(UNIT::E_UNIT::E_OILTANKER)] = 128.0f;
	_arAttackRange[static_cast<const int>(UNIT::E_UNIT::E_OILTANKER)] = 0.0f;
	_arAttackSpeed[static_cast<const int>(UNIT::E_UNIT::E_OILTANKER)] = 100.0f;

	//transport
	_arUnitHp[static_cast<const int>(UNIT::E_UNIT::E_TRANSPORT)] = 150;
	_arUnitDefence[static_cast<const int>(UNIT::E_UNIT::E_TRANSPORT)] = 0;
	_arUnitMinimalAttack[static_cast<const int>(UNIT::E_UNIT::E_TRANSPORT)] = 0;
	_arUnitAttack[static_cast<const int>(UNIT::E_UNIT::E_TRANSPORT)] = 0;
	_arUnitProductionTime[static_cast<const int>(UNIT::E_UNIT::E_TRANSPORT)] = 20;
	_arUnitSpeed[static_cast<const int>(UNIT::E_UNIT::E_TRANSPORT)] = 0.3f;
	_arSearchRange[static_cast<const int>(UNIT::E_UNIT::E_TRANSPORT)] = 128.0f;
	_arAttackRange[static_cast<const int>(UNIT::E_UNIT::E_TRANSPORT)] = 0.0f;
	_arAttackSpeed[static_cast<const int>(UNIT::E_UNIT::E_TRANSPORT)] = 100.0f;


	//galleys
	_arUnitHp[static_cast<const int>(UNIT::E_UNIT::E_GALLEYS)] = 100;
	_arUnitDefence[static_cast<const int>(UNIT::E_UNIT::E_GALLEYS)] = 10;
	_arUnitMinimalAttack[static_cast<const int>(UNIT::E_UNIT::E_GALLEYS)] = 2;
	_arUnitAttack[static_cast<const int>(UNIT::E_UNIT::E_GALLEYS)] = 35;
	_arUnitProductionTime[static_cast<const int>(UNIT::E_UNIT::E_GALLEYS)] = 30;
	_arUnitSpeed[static_cast<const int>(UNIT::E_UNIT::E_GALLEYS)] = 0.3f;
	_arSearchRange[static_cast<const int>(UNIT::E_UNIT::E_GALLEYS)] = 128.0f;
	_arAttackRange[static_cast<const int>(UNIT::E_UNIT::E_GALLEYS)] = 256.0f;
	_arAttackSpeed[static_cast<const int>(UNIT::E_UNIT::E_GALLEYS)] = 3.0f;

	//battleShip
	_arUnitHp[static_cast<const int>(UNIT::E_UNIT::E_BATTLESHIP)] = 150;
	_arUnitDefence[static_cast<const int>(UNIT::E_UNIT::E_BATTLESHIP)] = 15;
	_arUnitMinimalAttack[static_cast<const int>(UNIT::E_UNIT::E_BATTLESHIP)] = 50;
	_arUnitAttack[static_cast<const int>(UNIT::E_UNIT::E_BATTLESHIP)] = 130;
	_arUnitProductionTime[static_cast<const int>(UNIT::E_UNIT::E_BATTLESHIP)] = 50;
	_arUnitSpeed[static_cast<const int>(UNIT::E_UNIT::E_BATTLESHIP)] = 0.5f;
	_arSearchRange[static_cast<const int>(UNIT::E_UNIT::E_BATTLESHIP)] = 128.0f;
	_arAttackRange[static_cast<const int>(UNIT::E_UNIT::E_BATTLESHIP)] = 256.0f;
	_arAttackSpeed[static_cast<const int>(UNIT::E_UNIT::E_BATTLESHIP)] = 3.0f;

	//SubMarine
	_arUnitHp[static_cast<const int>(UNIT::E_UNIT::E_SUBMARIN)] = 60;
	_arUnitDefence[static_cast<const int>(UNIT::E_UNIT::E_SUBMARIN)] = 0;
	_arUnitMinimalAttack[static_cast<const int>(UNIT::E_UNIT::E_SUBMARIN)] = 10;
	_arUnitAttack[static_cast<const int>(UNIT::E_UNIT::E_SUBMARIN)] = 50;
	_arUnitProductionTime[static_cast<const int>(UNIT::E_UNIT::E_SUBMARIN)] = 40;
	_arUnitSpeed[static_cast<const int>(UNIT::E_UNIT::E_SUBMARIN)] = 0.4f;
	_arSearchRange[static_cast<const int>(UNIT::E_UNIT::E_SUBMARIN)] = 128.0f;
	_arAttackRange[static_cast<const int>(UNIT::E_UNIT::E_SUBMARIN)] = 256.0f;
	_arAttackSpeed[static_cast<const int>(UNIT::E_UNIT::E_SUBMARIN)] = 2.0f;
}



void UNITMGR::dragSelect(RECT rcDragRect)
{
	list<UNIT*>::iterator	iterUnitList = _listUnit.begin();
	list<UNIT*>::iterator	endUnitList = _listUnit.end();

	iterUnitList = _listUnit.begin();
	endUnitList = _listUnit.end();

	bool bIsFind = false;
	while (iterUnitList != endUnitList)
	{
		RECT _rcTmp;
		UNIT* pUnit = *iterUnitList;
		if (IntersectRect(&_rcTmp, pUnit->getCollisionRect(), &rcDragRect))
		{
			if (!bIsFind)
			{
				clearSelectedUnit();
				_vSeletedUnit.clear();
				bIsFind = true;
			}
			_vSeletedUnit.push_back(&(*iterUnitList));
		}

		pUnit = nullptr;
		iterUnitList++;
	}

}

void UNITMGR::clearSelectedUnit()
{
	for (int i = 0; i < static_cast<int>(_vSeletedUnit.size()); i++)
	{
		(*(_vSeletedUnit[i]))->setSelected(false);
	}

}

void UNITMGR::allocateIntervalMove()
{
	_arIntervalMove[0][0] = 0;
	_arIntervalMove[0][1] = -1;
	_arIntervalMove[1][0] = 1;
	_arIntervalMove[1][1] = 0;

	//22
	for (int i = 2; i <= 3; i++)
	{
		_arIntervalMove[i][0] = 0;
		_arIntervalMove[i][1] = 1;		
	}
	for (int i = 4; i <= 5; i++)
	{
		_arIntervalMove[i][0] = -1;
		_arIntervalMove[i][1] = 0;
	}
	//33
	for (int i = 6; i <= 8; i++)
	{
		_arIntervalMove[i][0] = 0;
		_arIntervalMove[i][1] = -1;
	}
	for (int i = 9; i <= 11; i++)
	{
		_arIntervalMove[i][0] = 1;
		_arIntervalMove[i][1] = 0;
	}
	//44
	for (int i = 12; i <= 15; i++)
	{
		_arIntervalMove[i][0] = 0;
		_arIntervalMove[i][1] = 1;
	}
	for (int i = 16; i <= 19; i++)
	{
		_arIntervalMove[i][0] = -1;
		_arIntervalMove[i][1] = 0;
	}
	//55
	for (int i = 20; i <= 24; i++)
	{
		_arIntervalMove[i][0] = 0;
		_arIntervalMove[i][1] = -1;
	}
}

UNIT * UNITMGR::getUnit(int nIndex)
{
	list<UNIT*>::iterator	iterUnitList = _listUnit.begin();
	list<UNIT*>::iterator	endUnitList = _listUnit.end();

	int nCount = 0;
	while (iterUnitList != endUnitList && nCount < nIndex)
	{
		iterUnitList++;
		nCount++;
	}


	return *iterUnitList;
}

