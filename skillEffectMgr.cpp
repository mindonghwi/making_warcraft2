#include "stdafx.h"
#include "skillEffectMgr.h"

SKILL_EFFECT_MGR::SKILL_EFFECT_MGR()
{
}

SKILL_EFFECT_MGR::~SKILL_EFFECT_MGR()
{
}

bool SKILL_EFFECT_MGR::addEffect(image * pImg, int nFps, int nFrameMaxX, int nFrameMaxY, int nEffectCount, string strEffecKey)
{
	if (_mqEffectPool.find(strEffecKey) == _mqEffectPool.end())
	{
		queue<SKILL_EFFECT*> queEffect;
		//¾ø´Â ÀÌÆåÆ® 
		for (int i = 0; i < nEffectCount; i++)
		{
			SKILL_EFFECT* pSkillEffect = new SKILL_EFFECT();
			pSkillEffect->init(pImg, nFps, nFrameMaxX, nFrameMaxY,strEffecKey);
			queEffect.push(pSkillEffect);
		}

		_mqEffectPool.insert(pair<string, queue<SKILL_EFFECT*>>(strEffecKey, queEffect));

		return true;
	}
	return false;
}


void SKILL_EFFECT_MGR::release()
{
	list<SKILL_EFFECT*>::iterator iter = _lPlayList.begin();
	list<SKILL_EFFECT*>::iterator end = _lPlayList.end();
	while (iter != end)
	{
		SKILL_EFFECT* pEffect = *iter;
		pEffect->release();
		iter = _lPlayList.erase(iter);
		delete pEffect;
		pEffect = nullptr;
	}

	map<string, queue<SKILL_EFFECT*>>::iterator iterMq = _mqEffectPool.begin();
	map<string, queue<SKILL_EFFECT*>>::iterator iterMqEnd = _mqEffectPool.end();

	while (iterMq != iterMqEnd)
	{
		while (!(*iterMq).second.empty())
		{
			SKILL_EFFECT* pEffect = (*iterMq).second.front();
			pEffect->release();
			(*iterMq).second.pop();
			delete pEffect;
			pEffect = nullptr;
		}
		iterMq = _mqEffectPool.erase(iterMq);
	}

}

void SKILL_EFFECT_MGR::update()
{
	list<SKILL_EFFECT*>::iterator iter = _lPlayList.begin();
	list<SKILL_EFFECT*>::iterator end = _lPlayList.end();
	while (iter != end)
	{
		SKILL_EFFECT* pEffect = *iter;
		pEffect->update();

		if (pEffect->deleteEffect()) {
			iter = _lPlayList.erase(iter);
			_mqEffectPool.find(pEffect->getEffectKEy())->second.push(pEffect);
		}
		else
		{
			iter++;
		}

		pEffect = nullptr;
	}
}

void SKILL_EFFECT_MGR::render(HDC hdc)
{
	list<SKILL_EFFECT*>::iterator iter = _lPlayList.begin();
	list<SKILL_EFFECT*>::iterator end = _lPlayList.end();
	while (iter != end)
	{
		SKILL_EFFECT* pEffect = *iter;
		pEffect->render(hdc);
		iter++;
		pEffect = nullptr;
	}
}

bool SKILL_EFFECT_MGR::activityEffect(string strEffectKey, float fPosX, float fPosY)
{
	if (_mqEffectPool.find(strEffectKey) == _mqEffectPool.end() && _mqEffectPool.find(strEffectKey)->second.empty())
	{
		return false;
	}
	
	SKILL_EFFECT* pEffect = _mqEffectPool.find(strEffectKey)->second.front();
	_mqEffectPool.find(strEffectKey)->second.pop();
	pEffect->create(fPosX, fPosY);
	_lPlayList.push_back(pEffect);
	pEffect = nullptr;

	return true;
}
