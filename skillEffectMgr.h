#pragma once
#include "stdafx.h"
#include "skillEffect.h"

//전적으로 바닥에 깔리는 스킬이 끝나고 일정시간 지나고 사라지는 effect를 관리하는 매니저
class SKILL_EFFECT_MGR
{
private:
	map<string,queue<SKILL_EFFECT*>>	_mqEffectPool;
	list<SKILL_EFFECT*>					_lPlayList;

	

public:
	SKILL_EFFECT_MGR();
	~SKILL_EFFECT_MGR();

	bool addEffect(image* pImg, int nFps, int nFrameMaxX, int nFrameMaxY, int nEffectCount, string strEffecKey);
	void release();
	void update();
	void render(HDC hdc);
	
	bool activityEffect(string strEffectKey,float fPosX, float fPosY);
	
};
