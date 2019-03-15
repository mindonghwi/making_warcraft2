#include "stdafx.h"
#include "buildMgr.h"
#include "map.h"
#include "buildsHeader.h"

BUILDMGR::BUILDMGR()
{
}

BUILDMGR::~BUILDMGR()
{
}

void BUILDMGR::init()
{
	_nBuildLevel = 0;
	allocateBuildResource();
	allocateBuildSize();
	allocateBuildTime();
	allocateBuildHp();

	for (int i = 0; i < static_cast<int>(E_BUILDS::E_MAX); i++)
	{
		_arIsBuildTree[i] = false;
	}

	_listBuild.clear();
}

void BUILDMGR::update()
{
	for (int i = 0; i < static_cast<int>(E_BUILDS::E_MAX); i++)
	{
		_arIsBuildTree[i] = false;
	}
	
	list<BUILD*>::iterator iter = _listBuild.begin();

	while (iter != _listBuild.end())
	{
		BUILD*	pBuild = *iter;
		//빌드 되어있는지 확인
		updateBuildTree(pBuild);

		pBuild->update();

		iter++;
	}

	if (_pSelected)
	{
		_pSelected->commandProduce();
		_pSelected->upgradeBuild();
	}
}



void BUILDMGR::release()
{
	while (!_listBuild.empty())
	{
		BUILD* pBuild = _listBuild.back();
		_listBuild.pop_back();
		pBuild->release();
		delete pBuild;
		pBuild = nullptr;
	}
}

void BUILDMGR::buildBuilding(E_BUILDS eBuild, float fPosX, float fPosY)
{
	string	strImgKey = "";

	switch (eBuild)
	{
	case E_BUILDS::E_TOWN:
		strImgKey.append("town");
		_listBuild.push_back(new TOWN);

		break;
	case E_BUILDS::E_KEEP:
		strImgKey.append("keep");
		_listBuild.push_back(new KEEP);


		break;
	case E_BUILDS::E_CASTLE:
		strImgKey.append("castle");
		_listBuild.push_back(new CASTLE);

		break;
	case E_BUILDS::E_FARM:
		strImgKey.append("farm");
		_listBuild.push_back(new FARM);

		break;
	case E_BUILDS::E_BARRACKS:
		strImgKey.append("barracks");
		_listBuild.push_back(new BARRACKS);

		break;
	case E_BUILDS::E_LUMBER_MILL:
		strImgKey.append("miil");
		_listBuild.push_back(new LUMBER_MILL);

		break;
	case E_BUILDS::E_BLACK_SMITH:
		strImgKey.append("smithy");
		_listBuild.push_back(new BLACK_SMITH);

		break;
	case E_BUILDS::E_SCOUT_TOWER:
		strImgKey.append("scoutTower");
		_listBuild.push_back(new SCOUT_TOWER);

		break;
	case E_BUILDS::E_GUARD_TOWER:
		strImgKey.append("tower02");
		break;
	case E_BUILDS::E_CANNON_TOWER:
		strImgKey.append("tower03");
		break;
	case E_BUILDS::E_SHIPYARD:
		strImgKey.append("dockyard");
		break;
	case E_BUILDS::E_FOUNDRY:
		strImgKey.append("yard02");
		break;
	case E_BUILDS::E_OIL_REFINERY:
		strImgKey.append("oilRefinery");
		break;
	case E_BUILDS::E_OIL_PLATFORM:
		strImgKey.append("yard03");
		break;
	case E_BUILDS::E_GNOMISH_INVENTOR:
		strImgKey.append("gnomishSanctuary");
		break;
	case E_BUILDS::E_STABLE:
		strImgKey.append("stall");
		break;
	case E_BUILDS::E_CHURCH:
		strImgKey.append("church");
		break;
	case E_BUILDS::E_MAGE_TOWER:
		strImgKey.append("mageTemple");
		break;
	case E_BUILDS::E_GRYPHON_AVIARY:
		strImgKey.append("gryphonSanctuary");
		break;
	}


	int nIndexX = static_cast<int>(fPosX) / TILESIZE;
	int nIndexY = static_cast<int>(fPosY) / TILESIZE;

	int nLeft = _pMap->getTile(nIndexX, nIndexY)->getRectTile().left;
	int nTop = _pMap->getTile(nIndexX, nIndexY)->getRectTile().top;


	int nFrameCount = IMAGEMANAGER->findImage(strImgKey)->GetWidth() / _arBuildsWidth[static_cast<int>(eBuild)];
	int nTileCount = _arBuildsWidth[static_cast<int>(eBuild)] / TILESIZE;
	for (int i = 0; i < nTileCount; i++)
	{
		for (int j = 0; j < nTileCount; j++)
		{
			_pMap->getTile(nIndexX + i, nIndexY + j)->setObject(TILE::E_OBJECT::E_BUILDING);
		}
	}

	_listBuild.back()->setLinkCamera(_pCamera);
	_listBuild.back()->setLinkUnitMgr(_pUnitMgr);
	_listBuild.back()->setLinkPlayer(_pPlayer);
	_listBuild.back()->setLinkMap(_pMap);
	_listBuild.back()->setLinkBuildMgr(this);
	_listBuild.back()->create(nLeft, nTop, _arBuildsWidth[static_cast<int>(eBuild)], _arBuildsHeight[static_cast<int>(eBuild)], _arHp[static_cast<int>(eBuild)], _arBuildTime[static_cast<int>(eBuild)], nFrameCount, strImgKey);

}

bool BUILDMGR::bIsGroundCheck(E_BUILDS eBuilds, float fPosX, float fPosY)
{
	int nIndexX = static_cast<int>(fPosX) / TILESIZE;
	int nIndexY = static_cast<int>(fPosY) / TILESIZE;

	int nCount = 0;
	if (_arBuildsWidth[static_cast<int>(eBuilds)] == 128)
	{
		nCount = 4;
	}
	else if (_arBuildsWidth[static_cast<int>(eBuilds)] <= 64)
	{
		nCount = 2;
	}
	else
	{
		nCount = 3;

	}
	for (int i = 0; i < nCount; i++)
	{
		for (int j = 0; j < nCount; j++)
		{
			if (_pMap->getTile(nIndexX + i, nIndexY + j)->getObject() != TILE::E_OBJECT::E_NONE ||
				_pMap->getTile(nIndexX + i, nIndexY + j)->getTerrian() != TILE::E_TERRIAN::GROUND)
			{
				return false;
			}
		}
	}
	return true;
}

void BUILDMGR::render(HDC hdc)
{
	if (_pSelected)
	{
		_pSelected->selectRender(hdc);
	}
}

void BUILDMGR::allocateBuildResource()
{
	for (int i = 0; i < static_cast<int>(E_BUILDS::E_MAX); i++)
	{
		for (int j = 0; j < static_cast<int>(E_RESOURCE::E_MAX); j++)
		{
			_arConsumptionResource[i][j] = 1;
		}
	}

	_arConsumptionResource[static_cast<int>(E_BUILDS::E_TOWN)][static_cast<int>(E_RESOURCE::E_GOLD)] = 500;
}

void BUILDMGR::allocateBuildSize()
{
	for (int i = 0; i < static_cast<int>(E_BUILDS::E_MAX); i++)
	{
		_arBuildsWidth[i]  = 96;
		_arBuildsHeight[i] = 96;
	}

	_arBuildsWidth[static_cast<int>(E_BUILDS::E_TOWN)] = 128;
	_arBuildsHeight[static_cast<int>(E_BUILDS::E_TOWN)] = 128;
	_arBuildsWidth[static_cast<int>(E_BUILDS::E_KEEP)] = 128;
	_arBuildsHeight[static_cast<int>(E_BUILDS::E_KEEP)] = 128;
	_arBuildsWidth[static_cast<int>(E_BUILDS::E_CASTLE)] = 128;
	_arBuildsHeight[static_cast<int>(E_BUILDS::E_CASTLE)] = 128;

	_arBuildsWidth[static_cast<int>(E_BUILDS::E_SCOUT_TOWER)] = 64;
	_arBuildsHeight[static_cast<int>(E_BUILDS::E_SCOUT_TOWER)] = 64;
	_arBuildsWidth[static_cast<int>(E_BUILDS::E_GUARD_TOWER)] = 64;
	_arBuildsHeight[static_cast<int>(E_BUILDS::E_GUARD_TOWER)] = 64;
	_arBuildsWidth[static_cast<int>(E_BUILDS::E_CANNON_TOWER)] = 64;
	_arBuildsHeight[static_cast<int>(E_BUILDS::E_CANNON_TOWER)] = 64;
	_arBuildsWidth[static_cast<int>(E_BUILDS::E_FARM)] = 64;
	_arBuildsHeight[static_cast<int>(E_BUILDS::E_FARM)] = 64;


}

void BUILDMGR::allocateBuildTime()
{
	_arBuildTime[static_cast<int>(E_BUILDS::E_TOWN)] = 1.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_KEEP)] = 10.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_CASTLE)] = 100.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_FARM)] = 20.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_BARRACKS)] = 20.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_LUMBER_MILL)] = 30.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_BLACK_SMITH)] = 30.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_SCOUT_TOWER)] = 20.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_GUARD_TOWER)] = 20.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_CANNON_TOWER)] = 20.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_SHIPYARD)] = 40.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_FOUNDRY)] = 40.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_OIL_REFINERY)] = 40.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_OIL_PLATFORM)] = 40.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_GNOMISH_INVENTOR)] = 50.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_STABLE)] = 40.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_CHURCH)] = 40.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_MAGE_TOWER)] = 60.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_GRYPHON_AVIARY)] = 60.0f;
}

void BUILDMGR::allocateBuildHp()
{
	
	_arHp[static_cast<int>(E_BUILDS::E_TOWN)] = 300;
	_arHp[static_cast<int>(E_BUILDS::E_KEEP)] = 400;
	_arHp[static_cast<int>(E_BUILDS::E_CASTLE)] = 500;
	_arHp[static_cast<int>(E_BUILDS::E_FARM)] = 100;
	_arHp[static_cast<int>(E_BUILDS::E_BARRACKS)] = 200;
	_arHp[static_cast<int>(E_BUILDS::E_LUMBER_MILL)] = 200;
	_arHp[static_cast<int>(E_BUILDS::E_BLACK_SMITH)] = 200;
	_arHp[static_cast<int>(E_BUILDS::E_SCOUT_TOWER)] = 100;
	_arHp[static_cast<int>(E_BUILDS::E_GUARD_TOWER)] = 100;
	_arHp[static_cast<int>(E_BUILDS::E_CANNON_TOWER)] = 100;
	_arHp[static_cast<int>(E_BUILDS::E_SHIPYARD)] = 200;
	_arHp[static_cast<int>(E_BUILDS::E_FOUNDRY)] = 200;
	_arHp[static_cast<int>(E_BUILDS::E_OIL_REFINERY)] = 200;
	_arHp[static_cast<int>(E_BUILDS::E_OIL_PLATFORM)] = 200;
	_arHp[static_cast<int>(E_BUILDS::E_GNOMISH_INVENTOR)] = 200;
	_arHp[static_cast<int>(E_BUILDS::E_STABLE)] = 200;
	_arHp[static_cast<int>(E_BUILDS::E_CHURCH)] = 200;
	_arHp[static_cast<int>(E_BUILDS::E_MAGE_TOWER)] = 200;
	_arHp[static_cast<int>(E_BUILDS::E_GRYPHON_AVIARY)] = 200;
}

BUILD * BUILDMGR::getBuild(int nIndex)
{
	if (nIndex >= getBuildCount())
	{
		return nullptr;
	}

	list<BUILD*>::iterator iter = _listBuild.begin();
	for (int i = 0; i < nIndex; i++)
	{
		iter++;
	}
	return *iter;
}

void BUILDMGR::releaseSelected()
{
	_pSelected = nullptr;
}

void BUILDMGR::selectedBuild(RECT rcDrag)
{
	list<BUILD*>::iterator iter = _listBuild.begin();


	for (int i = 0; i < getBuildCount(); i++)
	{
		RECT rc;
		releaseSelected();
		if (IntersectRect(&rc,(*iter)->getRect(),&rcDrag))
		{
			_pSelected = *iter;
			break;
		}
		iter++;
	}
}

void BUILDMGR::removeBuild(BUILD * pBuild)
{
	list<BUILD*>::iterator iter = _listBuild.begin();
	releaseSelected();
	while (iter != _listBuild.end())
	{
		if (*iter == pBuild)
		{
			iter = _listBuild.erase(iter);
			break;
		}
		iter ++;
	}
}

void BUILDMGR::updateBuildTree(BUILD*	pBuild)
{

	if (pBuild->getBuildsTpye() == E_BUILDS::E_KEEP || pBuild->getBuildsTpye() == E_BUILDS::E_TOWN)
	{
		_arIsBuildTree[static_cast<int>(E_BUILDS::E_TOWN)] = true;
		_arIsBuildTree[static_cast<int>(E_BUILDS::E_KEEP)] = true;
	}
	_arIsBuildTree[static_cast<int>(pBuild->getBuildsTpye())] = true;
}
