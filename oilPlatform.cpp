#include "stdafx.h"
#include "oilPlatform.h"

OIL_PLATFORM::OIL_PLATFORM()
{
}

OIL_PLATFORM::~OIL_PLATFORM()
{
}

void OIL_PLATFORM::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);

	_eBuilds = E_BUILDS::E_OIL_REFINERY;
}

void OIL_PLATFORM::release()
{
	setImage(nullptr);

}

void OIL_PLATFORM::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);

}
