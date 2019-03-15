#include "stdafx.h"
#include "church.h"

CHURCH::CHURCH()
{
}

CHURCH::~CHURCH()
{
}

void CHURCH::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);

	_eBuilds = E_BUILDS::E_CHURCH;
}

void CHURCH::release()
{
	setImage(nullptr);

}

void CHURCH::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);

}
