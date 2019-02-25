#include "stdafx.h"
#include "keyAniManager.h"
#include "image.h"
#include "animation.h"


keyAniManager::keyAniManager()
{
}


keyAniManager::~keyAniManager()
{
}

HRESULT keyAniManager::init()
{
	return S_OK;
}

void keyAniManager::release()
{
	deleteAllObject();
}

void keyAniManager::update()
{
	float fTime = TIMEMANAGER->getElapsedTime();
	iterObjectAnimation iter = _mmTotalAnimation.begin();
	iterObjectAnimation end = _mmTotalAnimation.end();
	while (iter != end)
	{
		iterAnimation iterAni = iter->second->begin();
		iterAnimation endAni = iter->second->end();

		while (iterAni != endAni)
		{
			if (!iterAni->second->isPlay())
			{
				iterAni++;
				continue;
			}
			if (!iterAni->second->getIsClickRender() && !iterAni->second->getIsFixedRender())
			{
				iterAni->second->frameUpdate(fTime * 1.0f);
			}
			else if(iterAni->second->getIsClickRender())
			{
				iterAni->second->frameClickUpdate();
			}
			else if (iterAni->second->getIsFixedRender()) 
			{
				iterAni->second->frameFixedFrame();
			}
			iterAni++;
		}
		iter++;
	}
}

void keyAniManager::render()
{
}

void keyAniManager::addObject(string strObjectKey)
{
	_mmTotalAnimation.insert(pair<string, arrAnimation*>(strObjectKey, new arrAnimation));
}

void keyAniManager::deleteObject(string strObjectKey)
{
	iterObjectAnimation iter = _mmTotalAnimation.begin();
	iterObjectAnimation end = _mmTotalAnimation.end();

	while (iter != end && iter->first != strObjectKey)
	{
		iter++;
	}

	if (iter != end && iter->first == strObjectKey)
	{
		iterAnimation iterA = (iter->second)->begin();

		iterAnimation endA = (iter->second)->end();

		while (iterA != endA)
		{
			animation* pAni = iterA->second;
			pAni->release();
			delete pAni;
			pAni = nullptr;
			iterA = iter->second->erase(iterA);

		}
		_mmTotalAnimation.erase(iter);
	}
}

void keyAniManager::deleteAllObject()
{
	iterObjectAnimation iter = _mmTotalAnimation.begin();
	iterObjectAnimation end = _mmTotalAnimation.end();

	while (iter != end)
	{
		iterAnimation iterA = (iter->second)->begin();

		iterAnimation endA = (iter->second)->end();

		while (iterA != endA)
		{
			animation* pAni = iterA->second;
			pAni->release();
			delete pAni;
			pAni = nullptr;
			iterA = iter->second->erase(iterA);
		}
		iter = _mmTotalAnimation.erase(iter);
	}
}

void keyAniManager::addDefaultFrameAnimation(string strObjectKey, string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		_mmTotalAnimation[strObjectKey]->insert(pair<string, animation*>(animationKeyName, ani));
	}

	//_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addDefaultFrameAnimation(string strObjectKey, string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, CALLBACK_FUNCTION cbFunction)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION(cbFunction));
	ani->setFPS(fps);

	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		_mmTotalAnimation[strObjectKey]->insert(pair<string, animation*>(animationKeyName, ani));
	}
	//_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addDefaultFrameAnimation(string strObjectKey, string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void * obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->setFPS(fps);

	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		_mmTotalAnimation[strObjectKey]->insert(pair<string, animation*>(animationKeyName, ani));
	}
	//_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addArrayFrameAnimation(string strObjectKey, string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop);
	ani->setFPS(fps);

	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		_mmTotalAnimation[strObjectKey]->insert(pair<string, animation*>(animationKeyName, ani));
	}
	//_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addArrayFrameAnimation(string strObjectKey, string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, CALLBACK_FUNCTION cbFunction)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, CALLBACK_FUNCTION(cbFunction));
	ani->setFPS(fps);

	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		_mmTotalAnimation[strObjectKey]->insert(pair<string, animation*>(animationKeyName, ani));
	}
	//_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addArrayFrameAnimation(string strObjectKey, string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void * obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		_mmTotalAnimation[strObjectKey]->insert(pair<string, animation*>(animationKeyName, ani));
	}
	//_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addArrayCoordinateFrameAnimation(string strObjectKey, string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, int loopCount)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, loopCount);
	ani->setFPS(fps);

	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		_mmTotalAnimation[strObjectKey]->insert(pair<string, animation*>(animationKeyName, ani));
	}
}

void keyAniManager::addArrayCoordinateFrameAnimation(string strObjectKey, string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, int loopCount, CALLBACK_FUNCTION cbFunction)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, loopCount, CALLBACK_FUNCTION(cbFunction));
	ani->setFPS(fps);

	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		_mmTotalAnimation[strObjectKey]->insert(pair<string, animation*>(animationKeyName, ani));
	}
}

void keyAniManager::addArrayCoordinateFrameAnimation(string strObjectKey, string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, int loopCount, CALLBACK_FUNCTION_PARAMETER cbFunction, void * obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, loopCount, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		_mmTotalAnimation[strObjectKey]->insert(pair<string, animation*>(animationKeyName, ani));
	}
}



void keyAniManager::addCoordinateFrameAnimation(string strObjectKey, string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		_mmTotalAnimation[strObjectKey]->insert(pair<string, animation*>(animationKeyName, ani));
	}
	//_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addCoordinateFrameAnimation(string strObjectKey, string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, CALLBACK_FUNCTION cbFunction)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		_mmTotalAnimation[strObjectKey]->insert(pair<string, animation*>(animationKeyName, ani));
	}
	//_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}

void keyAniManager::addCoordinateFrameAnimation(string strObjectKey, string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void * obj)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);

	animation* ani = new animation;

	ani->init(img->GetWidth(), img->GetHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, CALLBACK_FUNCTION_PARAMETER(cbFunction), obj);
	ani->setFPS(fps);

	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		_mmTotalAnimation[strObjectKey]->insert(pair<string, animation*>(animationKeyName, ani));
	}
	//_mTotalAnimation.insert(pair<string, animation*>(animationKeyName, ani));
}


void keyAniManager::start(string strObjectKey, string animationKeyName)
{
	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		iterAnimation iter = _mmTotalAnimation[strObjectKey]->find(animationKeyName);
		iter->second->start();
	}
}

void keyAniManager::stop(string strObjectKey, string animationKeyName)
{
	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		iterAnimation iter = _mmTotalAnimation[strObjectKey]->find(animationKeyName);
		iter->second->stop();
	}
}

void keyAniManager::pause(string strObjectKey, string animationKeyName)
{
	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		iterAnimation iter = _mmTotalAnimation[strObjectKey]->find(animationKeyName);
		iter->second->pause();
	}
}

void keyAniManager::resume(string strObjectKey, string animationKeyName)
{
	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		iterAnimation iter = _mmTotalAnimation[strObjectKey]->find(animationKeyName);
		iter->second->resume();
	}
}

animation * keyAniManager::findAnimation(string strObjectKey, string animationKeyName)
{
	if (_mmTotalAnimation.find(strObjectKey) != _mmTotalAnimation.end())
	{
		iterAnimation iter = _mmTotalAnimation[strObjectKey]->find(animationKeyName);
		if (iter != _mmTotalAnimation[strObjectKey]->end()) return iter->second;

	}
	return nullptr;
}

