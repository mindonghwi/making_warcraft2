#include "stdafx.h"
#include "gryphonAviary.h"
#include "buildMgr.h"
GRYPHON_AVIARY::GRYPHON_AVIARY()
{
}

GRYPHON_AVIARY::~GRYPHON_AVIARY()
{
}


void GRYPHON_AVIARY::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);
	_nUnitMask += BUILDMGR::E_UNITMASK::E_FLYER;


	int nIndexX = (nLeft + 16) / TILESIZE;
	int nIndexY = (ntop + 16) / TILESIZE;
	bool bIsFind = false;
	_fRayPointX = (float)_pMap->getTile(nIndexX , nIndexY)->getRectTile().left + 16.0f;
	_fRayPointY = (float)_pMap->getTile(nIndexX , nIndexY)->getRectTile().top + 16.0f;
	bIsFind = true;

	_eBuilds = E_BUILDS::E_GRYPHON_AVIARY;
}

void GRYPHON_AVIARY::release()
{
	setImage(nullptr);

}

void GRYPHON_AVIARY::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);
}
