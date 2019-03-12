#include "stdafx.h"
#include "town.h"
#include "buildMgr.h"
TOWN::TOWN()
{
}

TOWN::~TOWN()
{
}

void TOWN::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop,nWidth,nHeight,nHp,fBuildingTimer,nFrameCount,strImgKey);
	_nUnitMask += BUILDMGR::E_UNITMASK::E_WORKMAN;
}

void TOWN::update()
{
	_fTimer += TIMEMANAGER->getElapsedTime();

	if (_eState == BUILD::E_STATE::E_CREATING)
	{
		creatingUpdate();
	}
	createUnit();

	_pCamera->pushRenderObject(this);
}

void TOWN::release()
{
	setImage(nullptr);

}

void TOWN::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);
}

