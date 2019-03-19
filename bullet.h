#pragma once
#include "stdafx.h"
#include "object.h"

class PLAYER;
class CAMERA;

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
	OBJECT*					_pTarget;
	BULLET::E_DIRECTION		_eDirection;
	bool					_bIsDestroy;
	float					_fTimer;
	CAMERA*					_pCamera;
	int						_nAttack;
	string					_strMapKey;
	float					_fTrableRange;
public:
	BULLET();
	~BULLET();

	//초기화
	void init(float fPosX,float fPosY,int nWidth,int nHeight,const string& strImgKey, float fActiveTime,float fSpeed,int nAttack);
	
	//생성
	void create(float fPosX, float fPosY, OBJECT* pTarget,float fAngle);

	void returnPool();
	void update();
	void release();
	void render(HDC hdc);

	//linker
	inline	void	setLinkCamera(CAMERA*	pCamera) { _pCamera = pCamera; }

	inline	bool	isDestroy() { return _bIsDestroy; }
	void setMapKey(const string& str) { _strMapKey = str; }
	const string&	getMapKey() { return _strMapKey; }
};