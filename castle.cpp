#include "stdafx.h"
#include "castle.h"
#include "buildMgr.h"

CASTLE::CASTLE()
{
}

CASTLE::~CASTLE()
{
}

void CASTLE::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);
	_nUnitMask += BUILDMGR::E_UNITMASK::E_WORKMAN;
}

void CASTLE::update()
{
	_fTimer += TIMEMANAGER->getElapsedTime();

	if (_eState == BUILD::E_STATE::E_CREATING)
	{
		creatingUpdate();
	}
	createUnit();

	_pCamera->pushRenderObject(this);
}

void CASTLE::release()
{
	setImage(nullptr);

}

void CASTLE::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);

}
