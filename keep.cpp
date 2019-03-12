#include "stdafx.h"
#include "keep.h"
#include "buildMgr.h"

KEEP::KEEP()
{
}

KEEP::~KEEP()
{
}

void KEEP::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);
	_nUnitMask += BUILDMGR::E_UNITMASK::E_WORKMAN;
}

void KEEP::update()
{
	_fTimer += TIMEMANAGER->getElapsedTime();

	if (_eState == BUILD::E_STATE::E_CREATING)
	{
		creatingUpdate();
	}
	createUnit();

	_pCamera->pushRenderObject(this);
}

void KEEP::release()
{
	setImage(nullptr);

}

void KEEP::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);

}
