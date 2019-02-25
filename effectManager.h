#pragma once
#include "singletonBase.h"
#include "stdafx.h"
#include "effect.h"

class CAMERA;

class EFFECTMANAGER : public singletonBase<EFFECTMANAGER>
{
private:
	//�޸� Ǯ
	map<string, queue<EFFECT*>>		_mEffectPool;
	list<EFFECT*>					_listPlayList;


	CAMERA* _pCamera;
public:

	EFFECTMANAGER();
	~EFFECTMANAGER();


	HRESULT init();
	void release();
	void update();
	
	//����Ʈ �߰� (������ ������) 
	void addEffect(int nCount,const char* strEffectKey, const char * pImgKey, float fPlayTime);
	
	//����Ʈ �߰� (�ִϸ��̼� ������)
	void addEffect(int nCount, const char* strEffectKey, const char * pImgKey, float fPlayTime, int nWidth, int nHeight, int nFPS, bool bIsLoop = false, bool bIsReverse = false);

	//����Ʈ ����
	bool createEffect(const char* strEffectKey,float fPosX,float fPosY,float fAngle,float fSpeed);

	void linkCamera(CAMERA* pCamera) { _pCamera = pCamera; }

};