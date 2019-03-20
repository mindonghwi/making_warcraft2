#pragma once
#include "bullet.h"
#include "stdafx.h"
class CAMERA;
class PLAYER;
class BULLETMGR
{
private:
	map<string, queue<BULLET*>>	_mqBulletPool;
	list<BULLET*>				_listActiveBullet;

	CAMERA*		_pCamera;
	
	PLAYER*		_pUser;
	PLAYER*		_pCom;
public:
	BULLETMGR();
	~BULLETMGR();

	void init();
	void update();
	void render(HDC hdc);
	void release();

	void addBullet(const string& strKey, int nCount, const string& strImg, float fActiveTime, float fSpeed, int nAttack);
	void addGryphonBullet(const string& strKey, int nCount, const string& strImg, float fActiveTime, float fSpeed, int nAttack);

	void fire(const string& strKey, float fPosX, float fPosY,OBJECT* pTarget);
	void fire(const string& strKey, float fPosX, float fPosY, PLAYER* pTarget,float fTargetPosX,float fTargetPosY);

	inline	void	setLinkCamera(CAMERA*	pCamera) { _pCamera = pCamera; }
	inline	void	setLinkCom(PLAYER* pCom) { _pCom = pCom; }
	inline	void	setLinkPlayer(PLAYER* pUser) { _pUser = pUser; }


};