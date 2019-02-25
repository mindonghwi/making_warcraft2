#include "stdafx.h"
#include "skillEffect.h"

SKILL_EFFECT::SKILL_EFFECT():
	_fPosX(0.0f),
	_fPosY(0.0f),
	_pImg(nullptr),
	_bIsActive(false),
	_pAni(nullptr)
{
}

SKILL_EFFECT::~SKILL_EFFECT()
{
}

void SKILL_EFFECT::init(image * pImg, int nFPS, int nFrameMaxX, int nFrameMaxY,string strEffectKey)
{
	_fPosX = -2000.0f;
	_fPosY = -2000.0f;
	_pImg = pImg;
	_bIsActive = false;
	_pAni = new animation;

	_pAni->init(_pImg->GetWidth(), _pImg->GetHeight(), nFrameMaxX, nFrameMaxY);
	_pAni->setDefPlayFrame(false, false);
	_pAni->setFPS(nFPS);
	_pAni->stop();
	_strEffectKey = "";
	_strEffectKey.append(strEffectKey);
}

void SKILL_EFFECT::create(float fPosX, float fPosY)
{
	_fPosX = fPosX;
	_fPosY = fPosY;
	_bIsActive = true;
	_pAni->start();
}

void SKILL_EFFECT::update()
{
	if (_bIsActive && !_pAni->isPlay())
	{
		_bIsActive = false;
	}
	_pAni->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void SKILL_EFFECT::release()
{
	_pAni->release();
	delete _pAni;
	_pAni = nullptr;
	_pImg = nullptr;
}

void SKILL_EFFECT::render(HDC hdc)
{
	if (_bIsActive)
	{
		_pImg->aniRenderCenter(hdc, static_cast<int>(_fPosX), static_cast<int>(_fPosY), _pAni);
	}
}

bool SKILL_EFFECT::deleteEffect()
{
	if (_bIsActive)
	{
		return false;
	}
	else {
		return true;
	}
	
}
