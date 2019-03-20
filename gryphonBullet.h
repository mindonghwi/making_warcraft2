#pragma once
#include "stdafx.h"
#include "object.h"
#include "bullet.h"

class PLAYER;
class CAMERA;

class GRYPHONBULLET : public BULLET
{
private:
	int		_nFrameX;
	float	_fFrameTimer;


public:
	GRYPHONBULLET();
	~GRYPHONBULLET();

	//초기화
	virtual void init(float fPosX, float fPosY, int nWidth, int nHeight, const string& strImgKey, float fActiveTime, float fSpeed, int nAttack);

	//생성
	virtual void create(float fPosX, float fPosY, float fAngle);
	virtual void returnPool();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	//linker
	inline	void	setLinkCamera(CAMERA*	pCamera) { _pCamera = pCamera; }

	inline	bool	isDestroy() { return _bIsDestroy; }
	void setMapKey(const string& str) { _strMapKey = str; }
	const string&	getMapKey() { return _strMapKey; }
};