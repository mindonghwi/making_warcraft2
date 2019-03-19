#include "stdafx.h"
#include "bulletMgr.h"

BULLETMGR::BULLETMGR()
{
}

BULLETMGR::~BULLETMGR()
{
}

void BULLETMGR::init()
{
	
}

void BULLETMGR::undate()
{
	list<BULLET*>::iterator iter = _listActiveBullet.begin();


	while (iter != _listActiveBullet.end())
	{
		BULLET*	pBullet = *iter;
		pBullet->update();

		if (pBullet->isDestroy())
		{
			iter = _listActiveBullet.erase(iter);
			pBullet->returnPool();
			_mqBulletPool.find(pBullet->getMapKey())->second.push(pBullet);
		}
		else
		{
			iter++;
		}
	}
}

void BULLETMGR::render(HDC hdc)
{
	list<BULLET*>::iterator iter = _listActiveBullet.begin();
	list<BULLET*>::iterator end = _listActiveBullet.end();


	while (iter != end)
	{
		BULLET*	pBullet = *iter;
		pBullet->render(hdc);
		iter++;
	}
}

void BULLETMGR::release()
{
	while (!_listActiveBullet.empty())
	{
		BULLET*	pBullet = _listActiveBullet.back();
		_listActiveBullet.pop_back();
		pBullet->release();
		delete pBullet;
		pBullet = nullptr;
	}

	while (!_mqBulletPool.empty())
	{
		while (!_mqBulletPool.begin()->second.empty())
		{
			BULLET*	pBullet = _mqBulletPool.begin()->second.front();
			_mqBulletPool.begin()->second.pop();
			pBullet->release();
			delete pBullet;
			pBullet = nullptr;
		}
	}
}

void BULLETMGR::addBullet(const string & strKey, int nCount, const string & strImg, float fActiveTime, float fSpeed, int nAttack)
{
	if (_mqBulletPool.find(strKey) != _mqBulletPool.end())
	{
		return;
	}

	queue<BULLET*>	queBullet;
	for (int i = 0; i < nCount; i++)
	{
		BULLET*	pBullet = new BULLET();
		pBullet->init(-2000, -2000, TILESIZE, TILESIZE, "strImg", fActiveTime, fSpeed, nAttack);
		pBullet->setMapKey(strKey);
		queBullet.push(pBullet);
	}
	_mqBulletPool.insert(pair<string, queue<BULLET*>>(strKey, queBullet));
}
