#pragma once
#include "stdafx.h"
#include "object.h"

class PLAYER;

class BULLET : public OBJECT
{
public:
	enum class E_DIRECTION
	{
		E_RIGHT,
		E_RIGHT_TOP,
		E_TOP,
		E_LEFT_TOP,
		E_LEFT,
		E_LEFT_BOTTOM,
		E_BOTTOM,
		E_RIGHT_BOTTOM,
		E_MAX
	};

private:
	float					_fAngle;
	float					_fSpeed;
	float					_fActiveTime;
	PLAYER*					_pTarget;
	BULLET::E_DIRECTION		_eDirection;
	bool					_bIsDestroy;
	float					_fTimer;
public:
	BULLET();
	~BULLET();

	//초기화
	void init(float fPosX,float fPosY,int nWidth,int nHeight,const string& strImgKey, float fActiveTime,float fSpeed);
	//생성
	void create(float fPosX, float fPosY,PLAYER* pTarget,float fAngle);
	void update();
	void release();
	void render(HDC hdc);
};