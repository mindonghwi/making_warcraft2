#include "stdafx.h"
#include "foundry.h"

FOUNDRY::FOUNDRY()
{
}

FOUNDRY::~FOUNDRY()
{
}

void FOUNDRY::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);

	_eBuilds = E_BUILDS::E_FOUNDRY;
}

void FOUNDRY::release()
{
	setImage(nullptr);

}

void FOUNDRY::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);

}
