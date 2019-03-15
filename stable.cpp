#include "stdafx.h"
#include "stable.h"

STABLE::STABLE()
{
}

STABLE::~STABLE()
{
}


void STABLE::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);

	_eBuilds = E_BUILDS::E_STABLE;
}

void STABLE::release()
{
	setImage(nullptr);

}

void STABLE::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);

}
