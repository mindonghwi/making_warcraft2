#pragma once
#include "bullet.h"
#include "stdafx.h"
class CAMERA;
class BULLETMGR
{
private:
	map<string, queue<BULLET*>>	_mqBulletPool;
	list<BULLET*>				_listActiveBullet;

	CAMERA*		_pCamera;
public:
	BULLETMGR();
	~BULLETMGR();

	void init();
	void update();
	void render(HDC hdc);
	void release();

	void addBullet(const string& strKey, int nCount, const string& strImg, float fActiveTime, float fSpeed, int nAttack);

	void fire(const string& strKey, float fPosX, float fPosY,OBJECT* pTarget);

	inline	void	setLinkCamera(CAMERA*	pCamera) { _pCamera = pCamera; }
};