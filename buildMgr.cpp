#include "stdafx.h"
#include "buildMgr.h"
#include "map.h"


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

	switch (eBuild)
	{
	case BUILDMGR::E_BUILDS::E_TOWN:
		strImgKey.append("town");
		_listBuild.push_back(new TOWN);
		_listBuild.back()->create(fPosX,fPosY, _arBuildsWidth[static_cast<int>(eBuild)], _arBuildsHeight[static_cast<int>(eBuild)],0,10,4,strImgKey);
		_listBuild.back()->setLinkCamera(_pCamera);

		break;
	case BUILDMGR::E_BUILDS::E_KEEP:
		break;
	case BUILDMGR::E_BUILDS::E_CASTLE:
		break;
	case BUILDMGR::E_BUILDS::E_FARM:
		break;
	case BUILDMGR::E_BUILDS::E_BARRACKS:
		break;
	case BUILDMGR::E_BUILDS::E_LUMBER_MILL:
		break;
	case BUILDMGR::E_BUILDS::E_BLACK_SMITH:
		break;
	case BUILDMGR::E_BUILDS::E_SCOUT_TOWER:
		break;
	case BUILDMGR::E_BUILDS::E_GUARD_TOWER:
		break;
	case BUILDMGR::E_BUILDS::E_CANNON_TOWER:
		break;
	case BUILDMGR::E_BUILDS::E_SHIPYARD:
		break;
	case BUILDMGR::E_BUILDS::E_FOUNDRY:
		break;
	case BUILDMGR::E_BUILDS::E_OIL_REFINERY:
		break;
	case BUILDMGR::E_BUILDS::E_OIL_PLATFORM:
		break;
	case BUILDMGR::E_BUILDS::E_GNOMISH_INVENTOR:
		break;
	case BUILDMGR::E_BUILDS::E_STABLE:
		break;
	case BUILDMGR::E_BUILDS::E_CHURCH:
		break;
	case BUILDMGR::E_BUILDS::E_MAGE_TOWER:
		break;
	case BUILDMGR::E_BUILDS::E_GRYPHON_AVIARY:
		break;
	case BUILDMGR::E_BUILDS::E_MAX:
		break;
	default:
		break;
	}
	
	

}

bool BUILDMGR::bIsGroundCheck(float fPosX, float fPosY)
{
	int nIndexX = static_cast<int>(fPosX) / TILESIZE + 16;
	int nIndexY = static_cast<int>(fPosY) / TILESIZE + 16;

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (_pMap->getTile(nIndexX + i, nIndexY + j)->getObject() != TILE::E_OBJECT::E_NONE)
			{
				return false;
			}
		}
	}
	return true;
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
