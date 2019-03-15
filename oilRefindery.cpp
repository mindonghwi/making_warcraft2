#include "stdafx.h"
#include "oilRefindery.h"

OIL_REFINERY::OIL_REFINERY()
{
}

OIL_REFINERY::~OIL_REFINERY()
{
}


void OIL_REFINERY::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);

	_eBuilds = E_BUILDS::E_OIL_REFINERY;
}

void OIL_REFINERY::release()
{
	setImage(nullptr);

}

void OIL_REFINERY::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);

}
