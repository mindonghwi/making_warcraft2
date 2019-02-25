#include "stdafx.h"
#include "effectManager.h"

EFFECTMANAGER::EFFECTMANAGER()
{
}

EFFECTMANAGER::~EFFECTMANAGER()
{
}

HRESULT EFFECTMANAGER::init()
{
	_mEffectPool.clear();
	_listPlayList.clear();

	return S_OK;
}

void EFFECTMANAGER::release()
{
	list<EFFECT*>::iterator iter = _listPlayList.begin();
	list<EFFECT*>::iterator end = _listPlayList.end();

	while (iter != end)
	{
		EFFECT* pEffect = *iter;
		pEffect->release();
		iter = _listPlayList.erase(iter);
		pEffect = nullptr;
	}

	map<string, queue<EFFECT*>>::iterator iterMemPool = _mEffectPool.begin();
	map<string, queue<EFFECT*>>::iterator endMemPool = _mEffectPool.end();

	while (iterMemPool != endMemPool)
	{
		while (!iterMemPool->second.empty())
		{
			EFFECT* pEffect = iterMemPool->second.front();
			iterMemPool->second.pop();
			pEffect->release();
			delete pEffect;
			pEffect = nullptr;
		}

		iterMemPool = _mEffectPool.erase(iterMemPool);
	}
}

void EFFECTMANAGER::update()
{
	list<EFFECT*>::iterator iter = _listPlayList.begin();
	list<EFFECT*>::iterator end = _listPlayList.end();

	while (iter != end)
	{
		EFFECT* pEffect = *iter;
		pEffect->update();

		if (pEffect->isDeleteEffect())
		{
			iter = _listPlayList.erase(iter);
			pEffect->returnMemoryPool();
			_mEffectPool.find(pEffect->getEffectKEy())->second.push(pEffect);
		}
		else
		{
			iter++;
		}

		pEffect = nullptr;
	}

}


void EFFECTMANAGER::addEffect(int nCount, const char * strEffectKey, const char * pImgKey, float fPlayTime)
{
	//이미 이펙트가 있으면 
	if (_mEffectPool.find(strEffectKey) != _mEffectPool.end())
	{
		return;
	}
	queue<EFFECT*> qEffect;
	for (int i = 0; i < nCount; i++)
	{
		EFFECT* pEffect = new EFFECT();
		pEffect->init(pImgKey, strEffectKey, fPlayTime);
		pEffect->linkCamera(_pCamera);
		qEffect.push(pEffect);
	}

	_mEffectPool.insert(pair<string,queue<EFFECT*>>( strEffectKey, qEffect));
}

void EFFECTMANAGER::addEffect(int nCount, const char * strEffectKey, const char * pImgKey, float fPlayTime, int nWidth, int nHeight, int nFPS, bool bIsLoop, bool bIsReverse)
{
	//이미 이펙트가 있으면 
	if (_mEffectPool.find(strEffectKey) != _mEffectPool.end())
	{
		return;
	}
	queue<EFFECT*> qEffect;
	for (int i = 0; i < nCount; i++)
	{
		EFFECT* pEffect = new EFFECT();
		pEffect->init(pImgKey, strEffectKey, fPlayTime);
		pEffect->setAniMation(nWidth, nHeight, nFPS, bIsLoop, bIsReverse);
		pEffect->linkCamera(_pCamera);
		qEffect.push(pEffect);
	}
	
	_mEffectPool.insert(pair<string, queue<EFFECT*>>(strEffectKey, qEffect));
}

bool EFFECTMANAGER::createEffect(const char * strEffectKey, float fPosX, float fPosY, float fAngle, float fSpeed)
{
	//키값에 이펙트가 없을때
	if (_mEffectPool.find(strEffectKey) != _mEffectPool.end())
	{
		return false;
	}
	//이펙트 풀에 이펙트가 비었을때
	if (_mEffectPool.find(strEffectKey)->second.empty())
	{
		return false;
	}

	EFFECT*	pEffect = nullptr;

	pEffect = _mEffectPool.find(strEffectKey)->second.front();
	_mEffectPool.find(strEffectKey)->second.pop();
	pEffect->create(fPosX, fPosY, fAngle,fSpeed);
	_listPlayList.push_back(pEffect);

	return true;
}


