#include "stdafx.h"
#include "bullet.h"

BULLET::BULLET()
{
}

BULLET::~BULLET()
{
}

void BULLET::init(float fPosX, float fPosY, int nWidth, int nHeight, const string & strImgKey, float fActiveTime, float fSpeed)
{
	OBJECT::init(fPosX, fPosY, nWidth, nHeight);
	OBJECT::setImage(IMAGEMANAGER->findImage(strImgKey));
	_fAngle = 0.0f;
	_fSpeed = fSpeed;
	_fActiveTime = fActiveTime;
	_pTarget = nullptr;
	_eDirection = BULLET::E_DIRECTION::E_MAX;
	_bIsDestroy = true;
	_fTimer = 0.0f;
}

void BULLET::create(float fPosX, float fPosY, PLAYER * pTarget, float fAngle)
{
	OBJECT::setPosX(fPosX);
	OBJECT::setPosY(fPosY);
	_fAngle = fAngle;
	_pTarget = pTarget;
	_bIsDestroy = false;
	_fTimer = 0.0f;

	float fDirAngle = (_fAngle + PI8) / (PI / 4.0f);
	
	if (fDirAngle >= static_cast<float>(BULLET::E_DIRECTION::E_MAX))
	{
		fDirAngle = static_cast<float>(BULLET::E_DIRECTION::E_RIGHT);
	}

	_eDirection = static_cast<BULLET::E_DIRECTION>(static_cast<int>(fAngle));
	
}

void BULLET::update()
{
	_fTimer += TIMEMANAGER->getElapsedTime();

	//충돌 서치
	//xy좌표로 맵의 타일 중심 좌표 계산  거기 타겟 유닛이나 건물이 있는지

	if (_fTimer >= _fActiveTime)
	{
		_bIsDestroy = true;
	}
}

void BULLET::release()
{
}

void BULLET::render(HDC hdc)
{
}
