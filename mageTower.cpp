#include "stdafx.h"
#include "mageTower.h"
#include "buildMgr.h"

MAGETOWER::MAGETOWER()
{
}

MAGETOWER::~MAGETOWER()
{
}


void MAGETOWER::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);
	_nUnitMask += BUILDMGR::E_UNITMASK::E_MAGICIAN;


	int nIndexX = (nLeft + 16) / TILESIZE;
	int nIndexY = (ntop + 16) / TILESIZE;
	bool bIsFind = false;
	for (int i = -1; i < 6; i++)
	{
		for (int j = -1; j < 6; j++)
		{
			if (_pMap->getTile(nIndexX + i, nIndexY + j)->getObject() == TILE::E_OBJECT::E_NONE && (
				_pMap->getTile(nIndexX + i, nIndexY + j)->getTerrian() == TILE::E_TERRIAN::GROUND ||
				_pMap->getTile(nIndexX + i, nIndexY + j)->getTerrian() == TILE::E_TERRIAN::DIRT ||
				_pMap->getTile(nIndexX + i, nIndexY + j)->getTerrian() == TILE::E_TERRIAN::DIRT_GROUND))
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

	_eBuilds = E_BUILDS::E_MAGE_TOWER;
}

void MAGETOWER::release()
{
	setImage(nullptr);

}

void MAGETOWER::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);
}
