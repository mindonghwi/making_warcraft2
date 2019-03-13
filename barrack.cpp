#include "stdafx.h"
#include "barrack.h"
#include "buildMgr.h"

BARRACKS::BARRACKS()
{
}

BARRACKS::~BARRACKS()
{
}

void BARRACKS::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);
	_nUnitMask += BUILDMGR::E_UNITMASK::E_FOOTMAN;
	if (_pBuildBgr->getIsBuildTree(E_BUILDS::E_LUMBER_MILL))
	{
		_nUnitMask += BUILDMGR::E_UNITMASK::E_ARCHER;
	}
	if (_pBuildBgr->getIsBuildTree(E_BUILDS::E_BLACK_SMITH))
	{
		_nUnitMask += BUILDMGR::E_UNITMASK::E_BALLISTA;
	}
	if (_pBuildBgr->getIsBuildTree(E_BUILDS::E_STABLE))
	{
		_nUnitMask += BUILDMGR::E_UNITMASK::E_KNIGHT;
	}


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

	_eBuilds = E_BUILDS::E_BARRACKS;
}

void BARRACKS::release()
{
	setImage(nullptr);

}

void BARRACKS::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);

}
