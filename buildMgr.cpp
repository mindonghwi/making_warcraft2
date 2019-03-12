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
	_listBuild.clear();
}

void BUILDMGR::update()
{
	list<BUILD*>::iterator iter = _listBuild.begin();

	while (iter != _listBuild.end())
	{
		BUILD*	pBuild = *iter;
		pBuild->update();

		iter++;
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

void BUILDMGR::buildBuilding(BUILDMGR::E_BUILDS eBuild, float fPosX, float fPosY)
{
	string	strImgKey = "";

	int nIndexX = static_cast<int>(fPosX) / TILESIZE;
	int nIndexY = static_cast<int>(fPosY) / TILESIZE;

	int nLeft = _pMap->getTile(nIndexX, nIndexY)->getRectTile().left;
	int nTop = _pMap->getTile(nIndexX, nIndexY)->getRectTile().top;

	switch (eBuild)
	{
	case BUILDMGR::E_BUILDS::E_TOWN:
		strImgKey.append("town");
		_listBuild.push_back(new TOWN);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				_pMap->getTile(nIndexX+i, nIndexY+j)->setObject(TILE::E_OBJECT::E_BUILDING);
			}
		}

		_listBuild.back()->setLinkCamera(_pCamera);
		_listBuild.back()->setLinkUnitMgr(_pUnitMgr);
		_listBuild.back()->setLinkPlayer(_pPlayer);
		_listBuild.back()->setLinkMap(_pMap);

		_listBuild.back()->create(nLeft, nTop, _arBuildsWidth[static_cast<int>(eBuild)], _arBuildsHeight[static_cast<int>(eBuild)],100,_arBuildTime[static_cast<int>(eBuild)],4,strImgKey);

		break;
	case BUILDMGR::E_BUILDS::E_KEEP:
		strImgKey.append("keep");
		_listBuild.push_back(new KEEP);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				_pMap->getTile(nIndexX + i, nIndexY + j)->setObject(TILE::E_OBJECT::E_BUILDING);
			}
		}

		_listBuild.back()->setLinkCamera(_pCamera);
		_listBuild.back()->setLinkUnitMgr(_pUnitMgr);
		_listBuild.back()->setLinkPlayer(_pPlayer);
		_listBuild.back()->setLinkMap(_pMap);

		_listBuild.back()->create(nLeft, nTop, _arBuildsWidth[static_cast<int>(eBuild)], _arBuildsHeight[static_cast<int>(eBuild)], 100, _arBuildTime[static_cast<int>(eBuild)], 4, strImgKey);

		break;
	case BUILDMGR::E_BUILDS::E_CASTLE:
		strImgKey.append("castle");
		_listBuild.push_back(new CASTLE);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				_pMap->getTile(nIndexX + i, nIndexY + j)->setObject(TILE::E_OBJECT::E_BUILDING);
			}
		}
		_listBuild.back()->setLinkCamera(_pCamera);
		_listBuild.back()->setLinkUnitMgr(_pUnitMgr);
		_listBuild.back()->setLinkPlayer(_pPlayer);
		_listBuild.back()->setLinkMap(_pMap);

		_listBuild.back()->create(nLeft, nTop, _arBuildsWidth[static_cast<int>(eBuild)], _arBuildsHeight[static_cast<int>(eBuild)], 100, _arBuildTime[static_cast<int>(eBuild)], 4, strImgKey);

		break;
	case BUILDMGR::E_BUILDS::E_FARM:
		strImgKey.append("farm");
		_listBuild.push_back(new FARM);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				_pMap->getTile(nIndexX + i, nIndexY + j)->setObject(TILE::E_OBJECT::E_BUILDING);
			}
		}

		_listBuild.back()->setLinkCamera(_pCamera);
		_listBuild.back()->setLinkUnitMgr(_pUnitMgr);
		_listBuild.back()->setLinkPlayer(_pPlayer);
		_listBuild.back()->setLinkMap(_pMap);

		_listBuild.back()->create(nLeft, nTop, _arBuildsWidth[static_cast<int>(eBuild)], _arBuildsHeight[static_cast<int>(eBuild)], 50, _arBuildTime[static_cast<int>(eBuild)], 4, strImgKey);

		break;
	case BUILDMGR::E_BUILDS::E_BARRACKS:
		strImgKey.append("barracks");

		break;
	case BUILDMGR::E_BUILDS::E_LUMBER_MILL:
		strImgKey.append("miil");

		break;
	case BUILDMGR::E_BUILDS::E_BLACK_SMITH:
		strImgKey.append("smithy");

		break;
	case BUILDMGR::E_BUILDS::E_SCOUT_TOWER:
		strImgKey.append("scoutTower");
		break;
	case BUILDMGR::E_BUILDS::E_GUARD_TOWER:
		strImgKey.append("tower02");
		break;
	case BUILDMGR::E_BUILDS::E_CANNON_TOWER:
		strImgKey.append("tower03");
		break;
	case BUILDMGR::E_BUILDS::E_SHIPYARD:
		strImgKey.append("dockyard");
		break;
	case BUILDMGR::E_BUILDS::E_FOUNDRY:
		strImgKey.append("yard02");
		break;
	case BUILDMGR::E_BUILDS::E_OIL_REFINERY:
		strImgKey.append("oilRefinery");
		break;
	case BUILDMGR::E_BUILDS::E_OIL_PLATFORM:
		strImgKey.append("yard03");
		break;
	case BUILDMGR::E_BUILDS::E_GNOMISH_INVENTOR:
		strImgKey.append("gnomishSanctuary");
		break;
	case BUILDMGR::E_BUILDS::E_STABLE:
		strImgKey.append("stall");
		break;
	case BUILDMGR::E_BUILDS::E_CHURCH:
		strImgKey.append("church");
		break;
	case BUILDMGR::E_BUILDS::E_MAGE_TOWER:
		strImgKey.append("mageTemple");
		break;
	case BUILDMGR::E_BUILDS::E_GRYPHON_AVIARY:
		strImgKey.append("gryphonSanctuary");
		break;
	}



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
	_arBuildTime[static_cast<int>(E_BUILDS::E_TOWN)] = 30.0f;
	_arBuildTime[static_cast<int>(E_BUILDS::E_KEEP)] = 60.0f;
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
