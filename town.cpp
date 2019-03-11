#include "stdafx.h"
#include "town.h"

TOWN::TOWN()
{
}

TOWN::~TOWN()
{
}

void TOWN::create(float fPosX, float fPosY, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(fPosX,fPosY,nWidth,nHeight,nHp,fBuildingTimer,nFrameCount,strImgKey);

}

void TOWN::update()
{
	_fTimer += TIMEMANAGER->getElapsedTime();

	if (_eState == BUILD::E_STATE::E_CREATING)
	{
		creatingUpdate();
	}

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

//void TOWN::creatingUpdate()
//{
//}
