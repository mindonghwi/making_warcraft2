#pragma once
#include "singletonBase.h"
#include "stdafx.h"
#include "effect.h"

class CAMERA;

class EFFECTMANAGER : public singletonBase<EFFECTMANAGER>
{
private:
	//메모리 풀
	map<string, queue<EFFECT*>>		_mEffectPool;
	list<EFFECT*>					_listPlayList;


	CAMERA* _pCamera;
public:

	EFFECTMANAGER();
	~EFFECTMANAGER();


	HRESULT init();
	void release();
	void update();
	
	//이펙트 추가 (프레임 랜더용) 
	void addEffect(int nCount,const char* strEffectKey, const char * pImgKey, float fPlayTime);
	
	//이펙트 추가 (애니메이션 랜더용)
	void addEffect(int nCount, const char* strEffectKey, const char * pImgKey, float fPlayTime, int nWidth, int nHeight, int nFPS, bool bIsLoop = false, bool bIsReverse = false);

	//이펙트 생성
	bool createEffect(const char* strEffectKey,float fPosX,float fPosY,float fAngle,float fSpeed);

	void linkCamera(CAMERA* pCamera) { _pCamera = pCamera; }

};