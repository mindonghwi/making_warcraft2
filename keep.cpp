#include "stdafx.h"
#include "keep.h"
#include "buildMgr.h"
#include "player.h"
KEEP::KEEP()
{
}

KEEP::~KEEP()
{
}

void KEEP::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);
	_nUnitMask += BUILDMGR::E_UNITMASK::E_WORKMAN;


	int nIndexX = (nLeft + 16) / TILESIZE;
	int nIndexY = (ntop + 16) / TILESIZE;
	bool bIsFind = false;
	for (int i = -1; i < 6; i++)
	{
		for (int j = -1; j < 6; j++)
		{
			if (_pMap->getTile(nIndexX + i, nIndexY + j)->getObject() == TILE::E_OBJECT::E_NONE)
			{
				_fRayPointX = (float)_pMap->getTile(nIndexX + i, nIndexY + j)->getRectTile().left + 16.0f;
				_fRayPointY = (float)_pMap->getTile(nIndexX + i, nIndexY + j)->getRectTile().top + 16.0f;
				bIsFind = true;
				break;
			}
		}
		if (bIsFind)
		{
			break;
		}
	}
	_eBuilds = E_BUILDS::E_KEEP;
}

//void KEEP::update()
//{
//	_fTimer += TIMEMANAGER->getElapsedTime();
//
//	if (_eState == BUILD::E_STATE::E_CREATING)
//	{
//		creatingUpdate();
//	}
//	createUnit();
//
//	_pCamera->pushRenderObject(this);
//}

void KEEP::release()
{
	setImage(nullptr);

}

void KEEP::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);

}

void KEEP::upgradeBuild()
{
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		if (_pBuildMgr->getIsBuildTree(E_BUILDS::E_GNOMISH_INVENTOR))
		{
			if (_pPlayer->getGold() <= _pBuildMgr->getConsumptionResource(E_BUILDS::E_CASTLE, E_RESOURCE::E_GOLD)) return;
			if (_pPlayer->getTree() <= _pBuildMgr->getConsumptionResource(E_BUILDS::E_CASTLE, E_RESOURCE::E_TREE)) return;
			if (_pPlayer->getOil() <= _pBuildMgr->getConsumptionResource(E_BUILDS::E_CASTLE, E_RESOURCE::E_OIL)) return;

			_pBuildMgr->buildBuilding(E_BUILDS::E_CASTLE, OBJECT::getLeft(), OBJECT::getTop());

			_pBuildMgr->removeBuild(this);
		}
	}
}
