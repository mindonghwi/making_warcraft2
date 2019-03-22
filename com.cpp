#include "stdafx.h"
#include "com.h"

COM::COM()
{
	_bIsTown = false;
	_fTimer = 0;
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

	if (_fTimer >= 2.0f)
	{
		commandTownBuild();		
	}
	
	if (_fTimer >= 10.0f && _fTimer <= 11.0f)
	{
		if (_nFarmCount < 4)
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

	if (_fTimer <= 5.0f)
	{
		if (_nFarmCount >= 1)
		{
			if (getGold() <= getTree() * 2)
			{
				_pUnitMgr->commandHarvestAi(E_RESOURCE::E_GOLD);
			}
			else
			{
				_pUnitMgr->commandHarvestAi(E_RESOURCE::E_TREE);
			}

		}
	}
	
	_pUnitMgr->update();
	_pBuildMgr->update();

}

void COM::render(HDC hdc)
{
	for (int i = 0; i < (int)_vvMapNode.size(); i++)
	{
		RECT rc = _pMap->getTile(_vvMapNode[i][0], _vvMapNode[i][1])->getRectTile();
		Rectangle(hdc, rc);
	}
}

void COM::commandTownBuild()
{
	if (_bIsTown)
	{
		return;
	}
	_pUnitMgr->commandBuildAi(_pUnitMgr->getUnit(UNIT::E_UNIT::E_WORKMAN)->getPosX(), _pUnitMgr->getUnit(UNIT::E_UNIT::E_WORKMAN)->getPosY(), E_BUILDS::E_TOWN, _pUnitMgr->getUnit(UNIT::E_UNIT::E_WORKMAN));
	

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
	_pBuildMgr->getBuild(0, E_BUILDS::E_TOWN)->commandCreateUnit(BUILDMGR::E_UNITMASK::E_WORKMAN);

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
			_nFarmCount++;
		}
	}

}

//타운은 무조건 금광 주변으로 짓는다.
//