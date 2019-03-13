#include "stdafx.h"
#include "town.h"
#include "buildMgr.h"
#include "unitMGr.h"
TOWN::TOWN()
{
}

TOWN::~TOWN()
{
}

void TOWN::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop,nWidth,nHeight,nHp,fBuildingTimer,nFrameCount,strImgKey);
	_nUnitMask += BUILDMGR::E_UNITMASK::E_WORKMAN;

	
	int nIndexX = (nLeft + 16 )/TILESIZE;
	int nIndexY = (ntop + 16) / TILESIZE;
	bool bIsFind = false;
	for (int i = -1; i < 6; i++)
	{
		for (int j = -1; j < 6; j++)
		{
			if (_pMap->getTile(nIndexX + i,nIndexY + j)->getObject() == TILE::E_OBJECT::E_NONE)
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

	_eBuilds = E_BUILDS::E_TOWN;
}

//void TOWN::update()
//{
//	_fTimer += TIMEMANAGER->getElapsedTime();
//
//	if (_eState == BUILD::E_STATE::E_CREATING)
//	{
//		creatingUpdate();
//	}
//	else
//	{
//		commandProduce();
//		if (_fTimer >= 5.0f && _bIsProduce)
//		{
//			createUnit();
//		}
//	}
//
//	_pCamera->pushRenderObject(this);
//}

void TOWN::release()
{
	setImage(nullptr);

}

void TOWN::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);
}

