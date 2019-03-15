#include "stdafx.h"
#include "lumbleMill.h"

LUMBER_MILL::LUMBER_MILL()
{
}

LUMBER_MILL::~LUMBER_MILL()
{
}

void LUMBER_MILL::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);

	_eBuilds = E_BUILDS::E_BLACK_SMITH;
}

void LUMBER_MILL::release()
{
	setImage(nullptr);

}

void LUMBER_MILL::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);

}
