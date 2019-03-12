#include "stdafx.h"
#include "farm.h"
#include "buildMgr.h"
#include "player.h"

FARM::FARM()
{
}

FARM::~FARM()
{
}

void FARM::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string & strImgKey)
{
	BUILD::create(nLeft, ntop, nWidth, nHeight, nHp, fBuildingTimer, nFrameCount, strImgKey);
	
}

//void FARM::update()
//{
//	_fTimer += TIMEMANAGER->getElapsedTime();
//
//	if (_eState == BUILD::E_STATE::E_CREATING)
//	{
//		creatingUpdate();
//	}
//	
//	_pCamera->pushRenderObject(this);
//}

void FARM::release()
{
	setImage(nullptr);

}

void FARM::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);

}

void FARM::creatingUpdate()
{
	if (_fTimer >= _fOffsetFrame)
	{
		if (_nMaxFrameX - 1 > _nFrameX)
		{
			_nFrameX++;
		}

		_fOffsetFrame += _fOffsetFrame;
	}


	if (_fTimer >= _fBuildingTimer)
	{
		_eState = BUILD::E_STATE::E_ISON;
		_fTimer = 0.0f;
		_pPlayer->addMaxPopulation(8);
	}

}
