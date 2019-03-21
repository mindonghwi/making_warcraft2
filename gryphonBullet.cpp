#include "stdafx.h"
#include "gryphonBullet.h"
#include "player.h"
GRYPHONBULLET::GRYPHONBULLET()
{
}

GRYPHONBULLET::~GRYPHONBULLET()
{
}

void GRYPHONBULLET::init(float fPosX, float fPosY, int nWidth, int nHeight, const string & strImgKey, float fActiveTime, float fSpeed, int nAttack)
{
	BULLET::init(fPosX, fPosY, nWidth, nHeight, strImgKey, fActiveTime, fSpeed, nAttack);
}



void GRYPHONBULLET::create(float fPosX, float fPosY, float fAngle)
{
	BULLET::create(fPosX, fPosY, fAngle);
	_nFrameX = 0;
	_fFrameTimer = 0.0f;
}

void GRYPHONBULLET::returnPool()
{
	OBJECT::setPosX(-2000);
	OBJECT::setPosY(-2000);
	_fAngle = 0.0f;
	_pTarget = nullptr;
	_eDirection = BULLET::E_DIRECTION::E_MAX;
	_bIsDestroy = true;
	_fTimer = 0.0f;
}

void GRYPHONBULLET::update()
{
	_fTimer += TIMEMANAGER->getElapsedTime();
	_fFrameTimer += TIMEMANAGER->getElapsedTime();
	//충돌 서치
	//xy좌표로 맵의 타일 중심 좌표 계산  거기 타겟 유닛이나 건물이 있는지
	
	RECT rcObject = RectMakeCenter(OBJECT::getPosX(), OBJECT::getPosY(), 32, 32);

	//if (_pUser)
	//{
	//	_pUser->getUnitMgr()->getUnitCollisionBullet(getPosX(), getPosY(), _nAttack);
	//}
	if (_pCom)
	{
		if (_nFrameX % 2 == 0)
		{
			_pCom->getUnitMgr()->getUnitCollisionBullet(getPosX(), getPosY(), _nAttack);
		}
	}

	if (_fFrameTimer >= 0.3f)
	{
		_nFrameX++;

		if (_nFrameX >= 6)
		{
			_nFrameX = 0;
		}
		_fFrameTimer = 0.0f;
	}

	if (_fTimer >= _fActiveTime)
	{
		_bIsDestroy = true;
		return;
	}

	float fSpeed = _fSpeed * TIMEMANAGER->getElapsedTime();
	OBJECT::setPosX(OBJECT::getPosX() + Mins::presentPowerX(_fAngle, fSpeed) );
	OBJECT::setPosY(OBJECT::getPosY() + Mins::presentPowerY(_fAngle, fSpeed) );

	_pCamera->pushRenderObject(this);
}

void GRYPHONBULLET::release()
{
	OBJECT::setImage(nullptr);
	_pTarget = nullptr;
}

void GRYPHONBULLET::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc, OBJECT::getPosX(), OBJECT::getPosY(), _nFrameX, 0);

}
