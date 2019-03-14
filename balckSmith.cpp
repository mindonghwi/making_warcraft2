#include "stdafx.h"
#include "balckSmith.h"

BLACK_SMITH::BLACK_SMITH()
{
}

BLACK_SMITH::~BLACK_SMITH()
{
}

void BLACK_SMITH::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);

	_eBuilds = E_BUILDS::E_BLACK_SMITH;
}

void BLACK_SMITH::release()
{
	setImage(nullptr);

}

void BLACK_SMITH::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);

}
