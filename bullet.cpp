#include "stdafx.h"
#include "bullet.h"
#include "camera.h"
#include "player.h"

BULLET::BULLET()
{
}

BULLET::~BULLET()
{
}

void BULLET::init(float fPosX, float fPosY, int nWidth, int nHeight, const string & strImgKey, float fActiveTime, float fSpeed, int nAttack)
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
	OBJECT::setPosZ(3000);
	_nAttack = nAttack;
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

void BULLET::returnPool()
{
	OBJECT::setPosX(-2000);
	OBJECT::setPosY(-2000);
	_fAngle = 0.0f;
	_pTarget = nullptr;
	_eDirection = BULLET::E_DIRECTION::E_MAX;
	_bIsDestroy = true;
	_fTimer = 0.0f;
}

void BULLET::update()
{
	_fTimer += TIMEMANAGER->getElapsedTime();

	//충돌 서치
	//xy좌표로 맵의 타일 중심 좌표 계산  거기 타겟 유닛이나 건물이 있는지

	if (_pTarget->getUnitMgr()->getUnitCollisionBullet(OBJECT::getPosX(), OBJECT::getPosY(), _nAttack))
	{
		_bIsDestroy = true;
		return;
	}

	if (_fTimer >= _fActiveTime)
	{
		_bIsDestroy = true;
		return;
	}

	float fspeed = _fSpeed * TIMEMANAGER->getElapsedTime();
	
	OBJECT::setPosX(OBJECT::getPosX() + Mins::presentPowerX(_fAngle, fspeed));
	OBJECT::setPosY(OBJECT::getPosY() + Mins::presentPowerY(_fAngle, fspeed));

	_pCamera->pushRenderObject(this);
}

void BULLET::release()
{
	OBJECT::setImage(nullptr);
	_pTarget = nullptr;
}

void BULLET::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), static_cast<int>(_eDirection), 0);
}
