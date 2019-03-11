#include "stdafx.h"
#include "buildMgr.h"

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
}

void BUILDMGR::update()
{
}

void BUILDMGR::release()
{
}

void BUILDMGR::buildBuilding(BUILDMGR::E_BUILDS eBuild)
{
	switch (eBuild)
	{
	case BUILDMGR::E_BUILDS::E_TOWN:
	
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
