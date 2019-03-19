#pragma once
#include "bullet.h"
#include "stdafx.h"

class BULLETMGR
{
private:
	map<string, queue<BULLET*>>	_mqBulletPool;
	list<BULLET*>				_listActiveBullet;
public:
	BULLETMGR();
	~BULLETMGR();

	void init();
	void undate();
	void render(HDC hdc);
	void release();

	void addBullet(const string& strKey, int nCount, const string& strImg, float fActiveTime, float fSpeed, int nAttack);

	
};