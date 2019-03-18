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
	
	_eBuilds = E_BUILDS::E_FARM;
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
	_fHpTimer += TIMEMANAGER->getElapsedTime();
	if (_fHpTimer >= _fOffsetHpTimer)
	{
		_fHp += static_cast<float>(_nMaxHp) * _fHpTimer / _fBuildingTimer;


		if (_fHp > _nMaxHp)
		{
			_fHp = (float)_nMaxHp;
		}

		_fHpTimer = 0.0f;
	}

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
		OBJECT::setHp(_nMaxHp);
		OBJECT::decreaseHp(_nCreateDamage);//생상중 대미지 발생한것을 계산해준다.
		_nFrameX = _nMaxFrameX - 1;
		_pPlayer->addMaxPopulation(8);
	}

}
