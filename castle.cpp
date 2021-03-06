#include "stdafx.h"
#include "castle.h"
#include "buildMgr.h"

CASTLE::CASTLE()
{
}

CASTLE::~CASTLE()
{
}

void CASTLE::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
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
	_eBuilds = E_BUILDS::E_CASTLE;
}

//void CASTLE::update()
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

void CASTLE::release()
{
	setImage(nullptr);

}

void CASTLE::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);

}
