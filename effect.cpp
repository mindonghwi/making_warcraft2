#include "stdafx.h"
#include "effect.h"

EFFECT::EFFECT():
	_fPosX(0.0f),
	_fPosY(0.0f),
	_pImg(nullptr),
	_bIsActive(false),
	_pAni(nullptr),
	_fPlayTime(0.0f),
	_bIsLoop(false),
	_nFrameImgX(0),
	_nFrameImgY(0),
	_fTimer(0.0f),
	_fAngle(0.0f),
	_fSpeed(0.0f)
{
}

EFFECT::~EFFECT()
{
}

void EFFECT::initGeneral(const char* strEffectKey, float fPlayTime)
{
	_fPosX = -2000.0f;
	_fPosY = -2000.0f;
	OBJECT::setPosX(_fPosX);
	OBJECT::setPosY(_fPosY);

	_bIsActive = false;
	_fPlayTime = fPlayTime;
	_bIsLoop = false;
	_strEffectKey = "";
	_strEffectKey.append(strEffectKey);
	_pAni = nullptr;
	_nFrameImgX = 0;
	_nFrameImgY = 0;

	_fTimer = 0.0f;
	_fAngle = 0.0f;
	_fSpeed = 0.0f;
}

void EFFECT::init(const char * pImgKey, const char * strEffectKey, float fPlayTime)
{
	initGeneral(strEffectKey, fPlayTime);
	_pImg = IMAGEMANAGER->findImage(pImgKey);
	OBJECT::setWidth(_pImg->getFrameWidth());
	OBJECT::setHeight(_pImg->getFrameHeight());
}

void EFFECT::setAniMation(int nWidth, int nHeight, int nFPS, bool bIsLoop, bool bIsReverse)
{
	_pAni = new animation;
	_bIsLoop = bIsLoop;
	_pAni->init(_pImg->GetWidth(), _pImg->GetHeight(), nWidth, nHeight);
	_pAni->setDefPlayFrame(bIsReverse, _bIsLoop);
	_pAni->setFPS(nFPS);
	_pAni->stop();

	OBJECT::setWidth(nWidth);
	OBJECT::setHeight(nHeight);
}

void EFFECT::create(float fPosX, float fPosY, float fAngle, float fSpeed)
{
	_fPosX = fPosX;
	_fPosY = fPosY;
	_bIsActive = true;
	if (_pAni)
	{
		_pAni->start();
	}
	_fTimer = 0.0f;

	_fAngle = fAngle;
	_fSpeed = fSpeed;

	OBJECT::setPosX(_fPosX);
	OBJECT::setPosY(_fPosY);
}

void EFFECT::update()
{
	if (!_bIsActive)
	{
		return;
	}
	
	//애니메이션이 있는 경우
	if (_pAni)
	{
		_pAni->frameUpdate(TIMEMANAGER->getElapsedTime());
		
		//애니메이션이 루프인지 아닌지
		if (_bIsLoop)
		{
			//루프일 때
			_fTimer += TIMEMANAGER->getElapsedTime();

			//종료 시점
			if (_fTimer > _fPlayTime)
			{
				_bIsActive = false;
			}
		}
		else
		{
			//종료 시점
			if (!_pAni->isPlay())
			{
				_bIsActive = false;
			}
		}
	}

	_fPosX += Mins::presentPowerX(_fAngle, _fSpeed * TIMEMANAGER->getElapsedTime());
	_fPosY += Mins::presentPowerY(_fAngle, _fSpeed * TIMEMANAGER->getElapsedTime());
	OBJECT::setPosX(_fPosX);
	OBJECT::setPosY(_fPosY);



	_pCamera->pushRenderObject(this);
}

void EFFECT::release()
{
	if (_pAni)
	{
		_pAni->release();
		delete _pAni;
	}
	_pAni = nullptr;
	_pImg = nullptr;
}

void EFFECT::render(HDC hdc)
{
	if (_bIsActive)
	{
		if (_pAni)
		{
			_pImg->aniRenderCenter(hdc, static_cast<int>(_fPosX), static_cast<int>(_fPosY), _pAni);
		}
		else
		{
			_pImg->frameRenderCenter(hdc, static_cast<int>(_fPosX), static_cast<int>(_fPosY),_nFrameImgX,_nFrameImgY);
		}
	}
}

bool EFFECT::isDeleteEffect()
{
	if (_bIsActive)
	{
		return false;
	}
	else {
		return true;
	}
}

void EFFECT::returnMemoryPool()
{
	_fPosX = -2000.0f;
	_fPosY = -2000.0f;
	_bIsActive = false;
	_fTimer = 0.0f;
	_fAngle = 0.0f;
	_fSpeed = 0.0f;
}

