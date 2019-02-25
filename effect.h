#pragma once

#include "stdafx.h"
#include "animation.h"
#include "object.h"
#include "camera.h"

class EFFECT : public OBJECT
{

protected:
	float		_fPosX;				//중심 X
	float		_fPosY;				//중심 Y
	image*		_pImg;				//이미지 경로
	bool		_bIsActive;			//활성화
	animation*	_pAni;				//애니메이션
	string		_strEffectKey;		//이펙트의 키
	float		_fPlayTime;			//플레이 타임
	float		_fTimer;
	bool		_bIsLoop;			//루프인지 아닌지

	int			_nFrameImgX;		//프레임랜더용 frameX
	int			_nFrameImgY;		//프레임랜더용 frameY

	float		_fAngle;			//움직이는 방향
	float		_fSpeed;			//움직이는 속도

	CAMERA*		_pCamera;
public:
	EFFECT();
	~EFFECT();

	
	//이미지 키로 받는 init
	void init(const char* pImgKey, const char* strEffectKey, float fPlayTime);

	//init후 애니메이션을 쓸거면 쓰는 함수(가로,세로,FPS,루프,리버스)
	void setAniMation(int nWidth, int nHeight,int nFPS, bool bIsLoop = false, bool bIsReverse = false);

	//실제 뿌릴때 쓰는 초기화 함수
	void create(float fPosX, float fPosY,float fAngle,float fSpeed);

	virtual void update()			override;
	virtual void release()			override;
	virtual void render(HDC hdc)	override;

	//메모리폴로 보낼때 쓰는 함수
	bool isDeleteEffect();

	void returnMemoryPool();
private:
	//메모리풀 담기전 일반적인 정보를 초기화
	void initGeneral(const char* strEffectKey, float fPlayTime);


public:
	//getter setter

	//이펙트 키를 가져오는 함수
	inline const string& getEffectKEy() { return _strEffectKey; }
	
	//프레임이미지시 프레임 설정용
	inline void setFrameX(int nFrameX){_nFrameImgX = nFrameX;}
	inline void setFrameY(int nFrameY){_nFrameImgY = nFrameY;}
	inline void linkCamera(CAMERA* pCamera) { _pCamera = pCamera; }
};