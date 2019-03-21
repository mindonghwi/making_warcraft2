#include "stdafx.h"
#include "scoutTower.h"
#include "buildMgr.h"
#include "unitMGr.h"
#include "player.h"
SCOUT_TOWER::SCOUT_TOWER()
{
}

SCOUT_TOWER::~SCOUT_TOWER()
{
}

void SCOUT_TOWER::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);

	_eBuilds = E_BUILDS::E_SCOUT_TOWER;
}

void SCOUT_TOWER::release()
{
	setImage(nullptr);

}

void SCOUT_TOWER::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);

}

void SCOUT_TOWER::upgradeBuild()
{
	if (KEYMANAGER->isOnceKeyDown('G'))
	{
		if (_pBuildMgr->getIsBuildTree(E_BUILDS::E_KEEP))
		{
			if (_pPlayer->getGold() <= _pBuildMgr->getConsumptionResource(E_BUILDS::E_GUARD_TOWER, E_RESOURCE::E_GOLD)) return;
			if (_pPlayer->getTree() <= _pBuildMgr->getConsumptionResource(E_BUILDS::E_GUARD_TOWER, E_RESOURCE::E_TREE)) return;
			if (_pPlayer->getOil() <= _pBuildMgr->getConsumptionResource(E_BUILDS::E_GUARD_TOWER, E_RESOURCE::E_OIL)) return;

			_pBuildMgr->buildBuilding(E_BUILDS::E_GUARD_TOWER, (float)OBJECT::getLeft(), (float)OBJECT::getTop());

			_pBuildMgr->removeBuild(this);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		if (_pBuildMgr->getIsBuildTree(E_BUILDS::E_KEEP))
		{
			if (_pPlayer->getGold() <= _pBuildMgr->getConsumptionResource(E_BUILDS::E_CANNON_TOWER, E_RESOURCE::E_GOLD)) return;
			if (_pPlayer->getTree() <= _pBuildMgr->getConsumptionResource(E_BUILDS::E_CANNON_TOWER, E_RESOURCE::E_TREE)) return;
			if (_pPlayer->getOil() <= _pBuildMgr->getConsumptionResource(E_BUILDS::E_CANNON_TOWER, E_RESOURCE::E_OIL)) return;

			_pBuildMgr->buildBuilding(E_BUILDS::E_CANNON_TOWER, (float)OBJECT::getLeft(), (float)OBJECT::getTop());

			_pBuildMgr->removeBuild(this);
		}
	}
}
