#pragma once

#include "stdafx.h"
#include "animation.h"
class SKILL_EFFECT 
{
private:
	float		_fPosX;
	float		_fPosY;
	image*		_pImg;
	bool		_bIsActive;
	animation*	_pAni;
	string		_strEffectKey;
public:
	SKILL_EFFECT();
	~SKILL_EFFECT();

	//메모리 풀에 넣을때 쓰는 초기화 함수
	void init(image* pImg,int nFPS, int nFrameMaxX,int nFrameMaxY, string strEffectKey);

	//실제 뿌릴때 쓰는 초기화 함수
	void create(float fPosX, float fPosY);
	
	void update();
	//메모리 해제시 사용
	void release();

	void render(HDC hdc);

	//메모리폴로 보낼때 쓰는 함수
	bool deleteEffect();

	inline const string& getEffectKEy() { return _strEffectKey; }
};