#include "stdafx.h"
#include "guardTower.h"

GUARD_TOWER::GUARD_TOWER()
{
}

GUARD_TOWER::~GUARD_TOWER()
{
}

void GUARD_TOWER::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);

	_eBuilds = E_BUILDS::E_GUARD_TOWER;
}

void GUARD_TOWER::release()
{
	setImage(nullptr);

}

void GUARD_TOWER::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);

}
