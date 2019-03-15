#include "stdafx.h"
#include "cannonTower.h"

CANNON_TOWER::CANNON_TOWER()
{
}

CANNON_TOWER::~CANNON_TOWER()
{
}

void CANNON_TOWER::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);

	_eBuilds = E_BUILDS::E_CANNON_TOWER;
}

void CANNON_TOWER::release()
{
	setImage(nullptr);

}

void CANNON_TOWER::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);
}

