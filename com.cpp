#include "stdafx.h"
#include "com.h"

COM::COM():
	_arBuildsCount{},
	_arUnitCount{},
	_nPhaseCount(0)
{
	_bIsTown = false;
	_fTimer = 0;
	_nCount = 0;
}

COM::~COM()
{
}

void COM::update()
{
	//일군한테 마을 회관을 지으라고한다
	//마을회관이 다 지어지면 일군ㄴ한테 유닛을 뽑으라고 함
	//일군중 한명에게 농장을 지으라고 한다.
	//남은 일군한테 금채취를 시킨다
	//마을회관에서는 일군이 7~ 10마리까지 뽑느다.
	_fTimer += TIMEMANAGER->getElapsedTime();

//	phaseOne();
//	pahseTwo();
//	phaseThree();
//	if (_fTimer <= 5.0f)
//	{
//		if (_arBuildsCount[static_cast<int>(E_BUILDS::E_FARM)] >= 1)
//		{
//			if (_nCount % 4 == 0)
//			{
//				_pUnitMgr->commandHarvestAi(E_RESOURCE::E_GOLD);
//
//
//			}
//			else
//			{
//				_pUnitMgr->commandHarvestAi(E_RESOURCE::E_TREE);
//
//			}
//
//			_nCount++;
//		}
//	}
	_pUnitMgr->update();
	_pBuildMgr->update();


}

void COM::render(HDC hdc)
{
//	for (int i = 0; i < (int)_vvMapNode.size(); i++)
//	{
//		RECT rc = _pMap->getTile(_vvMapNode[i][0], _vvMapNode[i][1])->getRectTile();
//		Rectangle(hdc, rc);
//	}
}

void COM::commandTownBuild()
{
	if (_bIsTown)
	{
		return;
	}
	_pUnitMgr->commandBuildAi(_pUnitMgr->getUnit(UNIT::E_UNIT::E_WORKMAN)->getPosX(), _pUnitMgr->getUnit(UNIT::E_UNIT::E_WORKMAN)->getPosY(), E_BUILDS::E_TOWN, _pUnitMgr->getUnit(UNIT::E_UNIT::E_WORKMAN));
	

	if (!_pOpponent->getUnitMgr()->getUnit(0))
	{
		return;
	}
	_pAstar->startFinder(_pUnitMgr->getUnit(UNIT::E_UNIT::E_WORKMAN)->getPosX(), _pUnitMgr->getUnit(UNIT::E_UNIT::E_WORKMAN)->getPosY(),
		_pOpponent->getUnitMgr()->getUnit(0)->getPosX(), _pOpponent->getUnitMgr()->getUnit(0)->getPosY(), ASTAR::MOVEHEIGHT::GROUND);
	_pAstar->pathFinder();
	for (int i = 0; i < _pAstar->getListSize(); i++)
	{
		vector<int> vPos;
		vPos.push_back(_pAstar->getNode(i)->nIndexX);
		vPos.push_back(_pAstar->getNode(i)->nIndexY);
		_vvMapNode.push_back(vPos);
	}

	_arBuildsCount[static_cast<int>(E_BUILDS::E_TOWN)]++;
	_arUnitCount[static_cast<int>(UNIT::E_UNIT::E_WORKMAN)]++;
	_bIsTown = true;
}

void COM::commandFarmBuild(int nIndexX, int nIndexY)
{
	
}

void COM::commandBarrackBuild(int nIndexX, int nIndexY)
{
}

void COM::commandCreateWorkMan()
{
	if (_pBuildMgr->getBuild(0, E_BUILDS::E_TOWN) == nullptr)
	{
		return;
	}
	_pBuildMgr->getBuild(0, E_BUILDS::E_TOWN)->commandCreateUnit(BUILDMGR::E_UNITMASK::E_WORKMAN);
	_arUnitCount[static_cast<int>(UNIT::E_UNIT::E_WORKMAN)]++;
}

void COM::commandCreateUnit(BUILDMGR::E_UNITMASK eUnitMask)
{
	if (_pBuildMgr->getBuild(0, E_BUILDS::E_BARRACKS) == nullptr)
	{
		return;
	}
	_pBuildMgr->getBuild(0, E_BUILDS::E_BARRACKS)->commandCreateUnit(eUnitMask);
	int nDst = (int)log2((double)eUnitMask);
	
	_arUnitCount[nDst]++;
}

void COM::searchFindGround(int nPathIndex, E_BUILDS eBuilds)
{
	if (nPathIndex >= _vvMapNode.size())
	{
		return;
	}

	int nPosX = _vvMapNode[nPathIndex][0];
	int nPosY = _vvMapNode[nPathIndex][1];


	int nAddSubChangeCount = 2;
	int nAddSubChangeIndex = 0;
	int nInterval = -1;
	//x y xx yy xxx yyy xxxx yyyy
	int nMapChangeCount = 1;
	int nMapChangeIndex = 0;

	int nIntervalsX = 0;
	int nIntervalsY = 0;
	nIntervalsX = nInterval;



	while (!_pBuildMgr->bIsGroundCheck(eBuilds, static_cast<float>(nPosX * TILESIZE + 16), static_cast<float>(nPosY * TILESIZE + 16)))
	{
		nPosX += nIntervalsX;
		nPosY += nIntervalsY;

		nAddSubChangeIndex++;

		nMapChangeIndex++;

		if (nMapChangeIndex == nMapChangeCount)
		{
			//좌표를 더해주는게 변한다
			int nTmp = nIntervalsX;
			nIntervalsX = nIntervalsY;
			nIntervalsY = nTmp;

			nMapChangeIndex = 0;
		}

		if (nAddSubChangeCount == nAddSubChangeIndex)
		{
			nAddSubChangeCount += 2;
			nAddSubChangeIndex = 0;

			nInterval *= -1;

			if (nIntervalsX == 0)
			{
				nIntervalsY *= -1;
			}
			else
			{
				nIntervalsX *= -1;
			}
			nMapChangeCount++;

		}
	}

	if (_pBuildMgr->bIsGroundCheck(eBuilds, static_cast<float>(nPosX * TILESIZE + 16), static_cast<float>(nPosY * TILESIZE + 16)))
	{
		if (_pUnitMgr->searchIdleUnit(UNIT::E_UNIT::E_WORKMAN))
		{
			_pUnitMgr->commandBuildAi(static_cast<float>(nPosX * TILESIZE + 16), static_cast<float>(nPosY * TILESIZE + 16), eBuilds, _pUnitMgr->searchIdleUnit(UNIT::E_UNIT::E_WORKMAN));
			
			_arBuildsCount[static_cast<int>(eBuilds)]++;
		}
		else
		{
			//놀고있는 애는 없다 그럼 일하고 있는 애를 대려와야한다.
			_pUnitMgr->commandBuildAi(static_cast<float>(nPosX * TILESIZE + 16), static_cast<float>(nPosY * TILESIZE + 16), eBuilds, _pUnitMgr->getUnit(UNIT::E_UNIT::E_WORKMAN));
			_arBuildsCount[static_cast<int>(eBuilds)]++;
		}
	}

}

void COM::phaseOne()
{
	if (_arBuildsCount[static_cast<int>(E_BUILDS::E_FARM)] == 4 && _arBuildsCount[static_cast<int>(E_BUILDS::E_BARRACKS)] == 1
		&& _arBuildsCount[static_cast<int>(E_BUILDS::E_LUMBER_MILL)] == 1)
	{
		_bIsPhaseTwo = true;
		return;
	}
	_bIsPhaseTwo = false;

	if (_fTimer >= 2.0f)
	{
		commandTownBuild();
	}

	if (_fTimer >= 10.0f && _fTimer <= 11.0f)
	{
		if (_arBuildsCount[static_cast<int>(E_BUILDS::E_FARM)] < 4)
		{
			searchFindGround(4, E_BUILDS::E_FARM);
		}
		if (_nWorkManCount < 10)
		{
			commandCreateWorkMan();
			_nWorkManCount++;
		}
		_fTimer = 0.0f;
	}



	if (_arUnitCount[static_cast<int>(UNIT::E_UNIT::E_WORKMAN)] >= 10 && _arBuildsCount[static_cast<int>(E_BUILDS::E_FARM)] == 4 && _arBuildsCount[static_cast<int>(E_BUILDS::E_BARRACKS)] == 1
		&& _arBuildsCount[static_cast<int>(E_BUILDS::E_LUMBER_MILL)] == 0)
	{
		searchFindGround(10, E_BUILDS::E_LUMBER_MILL);
	}

	if (_nWorkManCount >= 10 && _arBuildsCount[static_cast<int>(E_BUILDS::E_FARM)] == 4 && _arBuildsCount[static_cast<int>(E_BUILDS::E_BARRACKS)] == 0)
	{
		searchFindGround(15, E_BUILDS::E_BARRACKS);
	}

}

void COM::pahseTwo()
{
	if (!_bIsPhaseTwo) return;
	
	if (_arUnitCount[static_cast<int>(UNIT::E_UNIT::E_FOOTMAN)] == 4 && _arUnitCount[static_cast<int>(UNIT::E_UNIT::E_ARCHER)] == 3)
	{
		_bIsPhaseThree = true;
		return;
	}
	_bIsPhaseThree = false;
	if (_fTimer >= 10.0f)
	{
		if (_arUnitCount[static_cast<int>(UNIT::E_UNIT::E_FOOTMAN)] < 4)
		{
			commandCreateUnit(BUILDMGR::E_UNITMASK::E_FOOTMAN);
		}
		else
		{
			commandCreateUnit(BUILDMGR::E_UNITMASK::E_ARCHER);
		}

		_fTimer = 0.0f;
	}


	
}

void COM::phaseThree()
{
	if (!_bIsPhaseThree) return;

	commandCreateWorkMan();
	
	if (_fTimer >= 20.0f)
	{
		if (_pOpponent->getBuildMgr()->getBuildCount() > 0)
		{
			_pUnitMgr->commandAttackAi(_pOpponent->getBuildMgr()->getBuild(0)->getPosX(), _pOpponent->getBuildMgr()->getBuild(0)->getPosY());
		}
		else if(_pOpponent->getUnitMgr()->getUnitCount() > 0)
		{
			_pUnitMgr->commandAttackAi(_pOpponent->getUnitMgr()->getUnit(0)->getPosX(), _pOpponent->getUnitMgr()->getUnit(0)->getPosY());
		}
		_fTimer = 0.0f;

		_arUnitCount[static_cast<int>(UNIT::E_UNIT::E_FOOTMAN)] = 0;
		_arUnitCount[static_cast<int>(UNIT::E_UNIT::E_ARCHER)] = 0;
		_nPhaseCount++;
	}

	if (_nPhaseCount > 5)
	{
		_bIsPhaseThree = false;
		_bIsPhaseTwo = true;
		_nPhaseCount = 0;
		searchFindGround(15, E_BUILDS::E_BARRACKS);
	}
}
