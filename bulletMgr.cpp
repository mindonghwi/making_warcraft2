#include "stdafx.h"
#include "bulletMgr.h"
#include "gryphonBullet.h"
BULLETMGR::BULLETMGR()
{
}

BULLETMGR::~BULLETMGR()
{
}

void BULLETMGR::init()
{
	_mqBulletPool.clear();
	_listActiveBullet.clear();
}

void BULLETMGR::update()
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
		pBullet->init(-2000, -2000, TILESIZE, TILESIZE, strImg, fActiveTime, fSpeed, nAttack);
		pBullet->setMapKey(strKey);
		pBullet->setLinkCamera(_pCamera);
		queBullet.push(pBullet);
	}
	_mqBulletPool.insert(pair<string, queue<BULLET*>>(strKey, queBullet));
}

void BULLETMGR::addGryphonBullet(const string & strKey, int nCount, const string & strImg, float fActiveTime, float fSpeed, int nAttack)
{
	if (_mqBulletPool.find(strKey) != _mqBulletPool.end())
	{
		return;
	}

	queue<BULLET*>	queBullet;
	for (int i = 0; i < nCount; i++)
	{
		BULLET*	pBullet = new GRYPHONBULLET();
		pBullet->init(-2000, -2000, TILESIZE, TILESIZE, strImg, fActiveTime, fSpeed, nAttack);
		pBullet->setMapKey(strKey);
		pBullet->setLinkCamera(_pCamera);
		pBullet->setLinkPlayer(_pUser);
		pBullet->setLinkCom(_pCom);
		queBullet.push(pBullet);
	}
	_mqBulletPool.insert(pair<string, queue<BULLET*>>(strKey, queBullet));
}

void BULLETMGR::fire(const string & strKey, float fPosX, float fPosY, OBJECT* pTarget)
{
	if (_mqBulletPool.find(strKey) == _mqBulletPool.end()) return;
	if (_mqBulletPool.find(strKey)->second.empty()) return;

	BULLET*	pBullet = _mqBulletPool.find(strKey)->second.front();
	_mqBulletPool.find(strKey)->second.pop();
	_listActiveBullet.push_back(pBullet);


	pBullet->create(fPosX, fPosY, pTarget, getAngle(fPosX, fPosY, pTarget->getPosX(), pTarget->getPosY()));
}

void BULLETMGR::fire(const string & strKey, float fPosX, float fPosY, PLAYER * pTarget, float fTargetPosX, float fTargetPosY)
{
	if (_mqBulletPool.find(strKey) == _mqBulletPool.end()) return;
	if (_mqBulletPool.find(strKey)->second.empty()) return;

	BULLET*	pBullet = _mqBulletPool.find(strKey)->second.front();
	_mqBulletPool.find(strKey)->second.pop();
	_listActiveBullet.push_back(pBullet);


	pBullet->create(fPosX, fPosY, getAngle(fPosX, fPosY, fTargetPosX, fTargetPosY));
}
