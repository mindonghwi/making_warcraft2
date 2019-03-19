#include "stdafx.h"
#include "unitMGr.h"

#include "workMan.h"
#include "footMan.h"
#include "elvenArcher.h"
#include "ballista.h"
#include "knight.h"
#include "oilTanker.h"
#include "galley.h"
#include "battleShip.h"
#include "transport.h"
#include "submarin.h"
#include "reconnaissance.h"
#include "bomber.h"
#include "magician.h"
#include "gryphonRider.h"

#include "map.h"
#include "buildMgr.h"


#include "stopCommand.h"
#include "holdCommand.h"
#include "moveCommand.h"
#include "buildCommand.h"
#include "attackCommand.h"
#include "harvestCommand.h"


#include "player.h"
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
	
	addCommandPool(COMMAND::E_COMMAND::E_BUILD, 201);
	addCommandPool(COMMAND::E_COMMAND::E_HOLD, 201);
	addCommandPool(COMMAND::E_COMMAND::E_STOP, 201);
	addCommandPool(COMMAND::E_COMMAND::E_MOVE, 4000);
	addCommandPool(COMMAND::E_COMMAND::E_ATTACK, 2000);
	addCommandPool(COMMAND::E_COMMAND::E_HARVEST, 400);

}

bool UNITMGR::createUnit(UNIT::E_UNIT eUnit, float fPosX, float fPosY)
{
	switch (eUnit)
	{
	case UNIT::E_UNIT::E_WORKMAN:
		_listUnit.push_back(new WORKMAN);
		break;
	case UNIT::E_UNIT::E_FOOTMAN:
		_listUnit.push_back(new FOOTMAN);
		break;
	case UNIT::E_UNIT::E_ARCHER:
		_listUnit.push_back(new ELVENARCHER);

		break;
	case UNIT::E_UNIT::E_BALLISTA:
		_listUnit.push_back(new BALLISTA);

		break;
	case UNIT::E_UNIT::E_KNIGHT:
		_listUnit.push_back(new KNIGHT);

		break;
	case UNIT::E_UNIT::E_MAGICIAN:
		_listUnit.push_back(new MAGICIAN);

		break;
	case UNIT::E_UNIT::E_BOMBER:
		_listUnit.push_back(new BOMBER);
		break;
	case UNIT::E_UNIT::E_RECONNAISSANCE:
		_listUnit.push_back(new RECONNAISSANCE);

		break;
	case UNIT::E_UNIT::E_OILTANKER:
		_listUnit.push_back(new OILTANKER);

		break;
	case UNIT::E_UNIT::E_GALLEYS:
		_listUnit.push_back(new GALLEYS);

		break;
	case UNIT::E_UNIT::E_TRANSPORT:
		_listUnit.push_back(new TRANSPORT);

		break;
	case UNIT::E_UNIT::E_BATTLESHIP:
		_listUnit.push_back(new BATTLESHIP);

		break;
	case UNIT::E_UNIT::E_SUBMARIN:
		_listUnit.push_back(new SUBMARIN);
		break;
	case UNIT::E_UNIT::E_FLYER:
		_listUnit.push_back(new GRYPHONRIDER);

		break;
	}
	_listUnit.back()->setLinkResourceMgr(_pResourceMgr);
	_listUnit.back()->setLinkUnitMgr(this);
	_listUnit.back()->setLinkCamera(_pCamera);
	_listUnit.back()->setLinkAStar(_pAstar);
	//64 64 원래 이거였음
	_listUnit.back()->init(static_cast<int>(fPosX), static_cast<int>(fPosY), 32, 32, _nCount);
	_listUnit.back()->create(static_cast<int>(fPosX), static_cast<int>(fPosY), _arUnitHp[static_cast<int>(eUnit)], _arUnitSpeed[static_cast<int>(eUnit)],
		_arUnitAttack[static_cast<int>(eUnit)], _arUnitDefence[static_cast<int>(eUnit)], _arSearchRange[static_cast<int>(eUnit)], _arAttackRange[static_cast<int>(eUnit)], _arAttackSpeed[static_cast<int>(eUnit)],
		_arUnitMinimalAttack[static_cast<int>(eUnit)]);
	_listUnit.back()->setLinkBuildMgr(_pBuildMgr);
	_listUnit.back()->setLinkMap(_pMap);
	_listUnit.back()->setLinkMyPlayer(_pPlayer);
	_listUnit.back()->addMapUnitData();
	_nCount++;

	_pPlayer->addPopulation(_arUnitPopulation[static_cast<int>(eUnit)]);

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
		//list<UNIT*>::iterator	iterUnitListCollision = _listUnit.begin();
		//list<UNIT*>::iterator	endUnitListCollision = _listUnit.end();
		//RECT _rc;
		//bool bIsOk = false;
		//while (iterUnitListCollision != endUnitListCollision)
		//{
		//	UNIT* pCollUnit = *iterUnitListCollision;
		//
		//	if (pUnit->getIndexNum() != pCollUnit->getIndexNum())
		//	{
		//
		//		//RECT rcTmp = RectMakeCenter(pUnit->getPosX()+Mins::presentPowerX(pUnit->getDirAngle(), pUnit->getMoveSpeed()) , pUnit->getPosY() + Mins::presentPowerY(pUnit->getDirAngle(), pUnit->getMoveSpeed()),3, 3);
		//		RECT rcTmpA =  *pCollUnit->getCollisionRect();
		//		RECT rcTmp = _pMap->getTile((int)pCollUnit->getPosX() / TILESIZE, (int)pCollUnit->getPosY() / TILESIZE)->getRectTile();
		//		rcTmpA.left += 12;
		//		rcTmpA.right -= 12;
		//		rcTmpA.top+= 12;
		//		rcTmpA.bottom -= 12;
		//
		//		if (pUnit->getBehavier() == UNIT::E_BEHAVIERNUM::E_MOVE)
		//		{
		//			if (pCollUnit->getBehavier() != UNIT::E_BEHAVIERNUM::E_MOVE)
		//			{
		//				if (IntersectRect(&_rc, & _pMap->getTile(pUnit->getMoveToPointEndX(), pUnit->getMoveToPointEndY())->getRectTile(), &rcTmpA))
		//				{
		//					bIsOk = true;
		//					pUnit->moveToDir();
		//					break;
		//				}
		//			}
		//			else if (!pCollUnit->getIsMovePointEmpty())
		//			{
		//				if (IntersectRect(&_rc, &_pMap->getTile(pCollUnit->getMoveToPointEndX() / TILESIZE, pCollUnit->getMoveToPointEndY() / TILESIZE)->getRectTile(), &rcTmpA))
		//				{
		//					bIsOk = true;
		//					pUnit->moveToDir();
		//					break;
		//				}
		//			}
		//			else if (IntersectRect(&_rc, &rcTmpA, pUnit->getCollisionRect()))
		//			{
		//				bIsOk = true;
		//				pUnit->moveToDir();
		//				break;
		//			}
		//		}
		//
		//		
		//	}
		//	iterUnitListCollision++;
		//}

		if (pUnit->getHp() <= 0)
		{
	
			for (int i = 0; i < (int)_vSeletedUnit.size(); i++)
			{
				if (*(_vSeletedUnit[i]) == pUnit)
				{
					_vSeletedUnit.erase(_vSeletedUnit.begin() + i);
					break;
				}
			}
			pUnit->removeMapUnitData();
			iterUnitList = _listUnit.erase(iterUnitList);

	
			pUnit->release();
			delete pUnit;
			pUnit = nullptr;
		}
		else
		{
			pUnit->updateBehavier();
			pUnit->update();
			pUnit->updateRect();
			iterUnitList++;
		}

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

	while (!_mCommandPool.empty())
	{
		while (!_mCommandPool.begin()->second.empty())
		{
			COMMAND* pCommand = _mCommandPool.begin()->second.front();
			_mCommandPool.begin()->second.pop();
			delete pCommand;
			pCommand = nullptr;
		}

		_mCommandPool.erase(_mCommandPool.begin());
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
		(*(_vSeletedUnit[i]))->command();
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
	int nCount = 0;
	while (nCount < 9 && iterUnitList != endUnitList)
	{
		RECT _rcTmp;
		UNIT* pUnit = *iterUnitList;
		if (!bIsFind)
		{
			clearSelectedUnit();
			_vSeletedUnit.clear();
			bIsFind = true;
		}

		if (IntersectRect(&_rcTmp, pUnit->getCollisionRect(), &rcDragRect))
		{
			_pBuildMgr->releaseSelected();
			_vSeletedUnit.push_back(&(*iterUnitList));
			nCount++;
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

void UNITMGR::moveCommand(float fPosX, float fPosY)
{
	for (int i = 0; i < static_cast<int>(_vSeletedUnit.size()); i++)
	{
		COMMAND*  pCommand = _mCommandPool.find(COMMAND::E_COMMAND::E_MOVE)->second.front();
		_mCommandPool.find(COMMAND::E_COMMAND::E_MOVE)->second.pop();
		pCommand->init(COMMAND::E_COMMAND::E_MOVE, *(_vSeletedUnit[i]));
		pCommand->commandUnit(fPosX, fPosY);
		(*(_vSeletedUnit[i]))->addCommand(pCommand);
	}
}

void UNITMGR::buildCommand(float fPosX, float fPosY,E_BUILDS eBuilds)
{
	COMMAND*  pCommand = _mCommandPool.find(COMMAND::E_COMMAND::E_MOVE)->second.front();
	_mCommandPool.find(COMMAND::E_COMMAND::E_MOVE)->second.pop();
	pCommand->init(COMMAND::E_COMMAND::E_MOVE, *(_vSeletedUnit[0]));
	pCommand->commandUnit(fPosX, fPosY);
	(*(_vSeletedUnit[0]))->addCommand(pCommand);

	pCommand = _mCommandPool.find(COMMAND::E_COMMAND::E_BUILD)->second.front();
	_mCommandPool.find(COMMAND::E_COMMAND::E_BUILD)->second.pop();
	pCommand->init(COMMAND::E_COMMAND::E_BUILD, *(_vSeletedUnit[0]));
	pCommand->commandUnit(fPosX,fPosY,eBuilds);
	(*(_vSeletedUnit[0]))->addCommand(pCommand);
}

void UNITMGR::addCommandPool(COMMAND::E_COMMAND eCommand, int nCount)
{
	queue<COMMAND*> queTmp;

	switch (eCommand)
	{
	case COMMAND::E_COMMAND::E_STOP:
		for (int i = 0; i < nCount; i++)
		{
			queTmp.push(new COMMAND_STOP());
		}
		break;
	case COMMAND::E_COMMAND::E_HOLD:
		for (int i = 0; i < nCount; i++)
		{
			queTmp.push(new COMMAND_HOLD());	
		}
		break;
	case COMMAND::E_COMMAND::E_MOVE:
		for (int i = 0; i < nCount; i++)
		{
			queTmp.push(new COMMAND_MOVE());
		}
		break;
	case COMMAND::E_COMMAND::E_ATTACK:
		for (int i = 0; i < nCount; i++)
		{
			queTmp.push(new COMMAND_ATTACK());
		}
		break;
	case COMMAND::E_COMMAND::E_BUILD:
		for (int i = 0; i < nCount; i++)
		{
			queTmp.push(new COMMAND_BUILD());
		}
		break;
	case COMMAND::E_COMMAND::E_HARVEST:
		for (int i = 0; i < nCount; i++)
		{
			queTmp.push(new COMMAND_HARVEST());
		}
		break;
	case COMMAND::E_COMMAND::E_HEAL:
		break;
	case COMMAND::E_COMMAND::E_BLIZZARD:
		break;
	case COMMAND::E_COMMAND::E_RANGEATTACT:
		break;
	default:
		break;
	}
	

	_mCommandPool.insert(pair<COMMAND::E_COMMAND, queue<COMMAND*>>(eCommand, queTmp));
}

void UNITMGR::returnPool(COMMAND* pCommand)
{
	_mCommandPool.find(pCommand->getCommand())->second.push(pCommand);
}

void UNITMGR::commandAttack(OBJECT * pObject)
{
	for (int i = 0; i < static_cast<int>(_vSeletedUnit.size()); i++)
	{
		COMMAND*  pCommand = _mCommandPool.find(COMMAND::E_COMMAND::E_MOVE)->second.front();
		_mCommandPool.find(COMMAND::E_COMMAND::E_MOVE)->second.pop();
		pCommand->init(COMMAND::E_COMMAND::E_MOVE, *(_vSeletedUnit[i]));
		pCommand->commandUnit(pObject->getPosX(), pObject->getPosY());
		(*(_vSeletedUnit[i]))->addCommand(pCommand);
		(*(_vSeletedUnit[i]))->setTarget(pObject);
	}
	for (int i = 0; i < static_cast<int>(_vSeletedUnit.size()); i++)
	{
		COMMAND*  pCommand = _mCommandPool.find(COMMAND::E_COMMAND::E_ATTACK)->second.front();
		_mCommandPool.find(COMMAND::E_COMMAND::E_ATTACK)->second.pop();
		pCommand->init(COMMAND::E_COMMAND::E_ATTACK, *(_vSeletedUnit[i]));
		pCommand->commandUnit(pObject);
		(*(_vSeletedUnit[i]))->addCommand(pCommand);
	}
}

void UNITMGR::commandReAttack(UNIT* pUnit, OBJECT * pObject)
{
	COMMAND*  pCommand = _mCommandPool.find(COMMAND::E_COMMAND::E_MOVE)->second.front();
	_mCommandPool.find(COMMAND::E_COMMAND::E_MOVE)->second.pop();
	pCommand->init(COMMAND::E_COMMAND::E_MOVE, pUnit);
	pCommand->commandUnit(pObject->getPosX(), pObject->getPosY());
	(pUnit)->addCommand(pCommand);
	(pUnit)->setTarget(pObject);

	 pCommand = _mCommandPool.find(COMMAND::E_COMMAND::E_ATTACK)->second.front();
	_mCommandPool.find(COMMAND::E_COMMAND::E_ATTACK)->second.pop();
	pCommand->init(COMMAND::E_COMMAND::E_ATTACK, pUnit);
	pCommand->commandUnit(pObject);
	(pUnit)->addCommand(pCommand);
}

void UNITMGR::clearCommandSelectedUnit()
{
	for (int i = 0; i < static_cast<int>(_vSeletedUnit.size()); i++)
	{
		(*(_vSeletedUnit[i]))->clearCommand();
	}
	
}

void UNITMGR::commandHarvest(RESOURCES* pResource)
{
	for (int i = 0; i < static_cast<int>(_vSeletedUnit.size()); i++)
	{
		COMMAND*  pCommand = _mCommandPool.find(COMMAND::E_COMMAND::E_MOVE)->second.front();
		_mCommandPool.find(COMMAND::E_COMMAND::E_MOVE)->second.pop();
		pCommand->init(COMMAND::E_COMMAND::E_MOVE, *(_vSeletedUnit[i]));
		pCommand->commandUnit(pResource->getPosX(), pResource->getPosY());
		(*(_vSeletedUnit[i]))->addCommand(pCommand);
		//(*(_vSeletedUnit[i]))->setTarget(pResource);
	}
	for (int i = 0; i < static_cast<int>(_vSeletedUnit.size()); i++)
	{
		if ((*(_vSeletedUnit[i]))->getUnit() == UNIT::E_UNIT::E_WORKMAN && (*(_vSeletedUnit[i]))->getHarvest() == UNIT::E_HARVEST::E_NONE)
		{
			COMMAND*  pCommand = _mCommandPool.find(COMMAND::E_COMMAND::E_HARVEST)->second.front();
			_mCommandPool.find(COMMAND::E_COMMAND::E_HARVEST)->second.pop();
			pCommand->init(COMMAND::E_COMMAND::E_HARVEST, *(_vSeletedUnit[i]));
			pCommand->commandUnit(pResource);
			(*(_vSeletedUnit[i]))->addCommand(pCommand);
			(*(_vSeletedUnit[i]))->setTarget(pResource);
		}
	}

}

void UNITMGR::commandHarvestSingle(RESOURCES * pResource, UNIT * pUnit)
{
	float fDistacne = 128.0f * TILESIZE * 1.4f;
	fDistacne *= fDistacne;
	int nIndex = 10000;

	if (pUnit->getHarvest() == UNIT::E_HARVEST::E_GOLD)
	{
		pResource = _pResourceMgr->getfindNearGoldMine(pUnit->getPosX(), pUnit->getPosY());
	}
	else if (pUnit->getHarvest() == UNIT::E_HARVEST::E_TREE)
	{
		pResource = _pResourceMgr->getfindNearTree(pUnit->getPosX(), pUnit->getPosY());
	}

	if (pResource == nullptr)
	{
		return;
	}
	pUnit->clearCommand();

	COMMAND*  pCommand = _mCommandPool.find(COMMAND::E_COMMAND::E_MOVE)->second.front();
	_mCommandPool.find(COMMAND::E_COMMAND::E_MOVE)->second.pop();
	pCommand->init(COMMAND::E_COMMAND::E_MOVE, pUnit);
	pCommand->commandUnit(pResource->getPosX(), pResource->getPosY());
	pUnit->addCommand(pCommand);
	
	pCommand = _mCommandPool.find(COMMAND::E_COMMAND::E_HARVEST)->second.front();
	_mCommandPool.find(COMMAND::E_COMMAND::E_HARVEST)->second.pop();
	pCommand->init(COMMAND::E_COMMAND::E_HARVEST, pUnit);
	pCommand->commandUnit(pResource);
	pUnit->addCommand(pCommand);
	pUnit->setTarget(pResource);
}

void UNITMGR::commandMoveSingle(float fPosX, float fPosY, UNIT * pUnit)
{
	COMMAND*  pCommand = _mCommandPool.find(COMMAND::E_COMMAND::E_MOVE)->second.front();
	_mCommandPool.find(COMMAND::E_COMMAND::E_MOVE)->second.pop();
	pCommand->init(COMMAND::E_COMMAND::E_MOVE, pUnit);
	pCommand->commandUnit(fPosX, fPosY);
	(pUnit)->addCommand(pCommand);
}

void UNITMGR::removeSelectedUnit(UNIT * pUnit)
{
	for (int i = 0; i < getUnitSelectedCount(); i++)
	{
		if (_vSeletedUnit[i] == &pUnit) {
			_vSeletedUnit.erase(_vSeletedUnit.begin() + i);
			return;
		}
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

UNIT * UNITMGR::getSelectedUnit(int nIndex)
{
	if (static_cast<int>(_vSeletedUnit.size()) <= nIndex)
	{
		return nullptr;
	}


	return *(_vSeletedUnit[nIndex]);
}

