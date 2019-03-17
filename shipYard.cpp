#include "stdafx.h"
#include "shipYard.h"
#include "buildMgr.h"

SHIP_YARD::SHIP_YARD()
{
}

SHIP_YARD::~SHIP_YARD()
{
}

void SHIP_YARD::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);
	_nUnitMask += BUILDMGR::E_UNITMASK::E_BATTLESHIP;
	_nUnitMask += BUILDMGR::E_UNITMASK::E_GALLEYS;
	_nUnitMask += BUILDMGR::E_UNITMASK::E_TRANSPORT;
	_nUnitMask += BUILDMGR::E_UNITMASK::E_OILTANKER;
	_nUnitMask += BUILDMGR::E_UNITMASK::E_SUBMARIN;


	int nIndexX = (nLeft + 16) / TILESIZE;
	int nIndexY = (ntop + 16) / TILESIZE;
	bool bIsFind = false;
	for (int i = -1; i < 6; i++)
	{
		for (int j = -1; j < 6; j++)
		{
			if (_pMap->getTile(nIndexX + i, nIndexY + j)->getObject() == TILE::E_OBJECT::E_NONE &&
				(_pMap->getTile(nIndexX + i, nIndexY + j)->getTerrian() == TILE::E_TERRIAN::WATER
					//|| _pMap->getTile(nIndexX + i, nIndexY + j)->getTerrian() == TILE::E_TERRIAN::DIRT_WATER
					))
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

	_eBuilds = E_BUILDS::E_SHIPYARD;
}

void SHIP_YARD::release()
{
	setImage(nullptr);

}

void SHIP_YARD::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);
}
