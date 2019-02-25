#pragma once

#include "stdafx.h"
#include "animation.h"
#include "object.h"
#include "camera.h"

class EFFECT : public OBJECT
{

protected:
	float		_fPosX;				//�߽� X
	float		_fPosY;				//�߽� Y
	image*		_pImg;				//�̹��� ���
	bool		_bIsActive;			//Ȱ��ȭ
	animation*	_pAni;				//�ִϸ��̼�
	string		_strEffectKey;		//����Ʈ�� Ű
	float		_fPlayTime;			//�÷��� Ÿ��
	float		_fTimer;
	bool		_bIsLoop;			//�������� �ƴ���

	int			_nFrameImgX;		//�����ӷ����� frameX
	int			_nFrameImgY;		//�����ӷ����� frameY

	float		_fAngle;			//�����̴� ����
	float		_fSpeed;			//�����̴� �ӵ�

	CAMERA*		_pCamera;
public:
	EFFECT();
	~EFFECT();

	
	//�̹��� Ű�� �޴� init
	void init(const char* pImgKey, const char* strEffectKey, float fPlayTime);

	//init�� �ִϸ��̼��� ���Ÿ� ���� �Լ�(����,����,FPS,����,������)
	void setAniMation(int nWidth, int nHeight,int nFPS, bool bIsLoop = false, bool bIsReverse = false);

	//���� �Ѹ��� ���� �ʱ�ȭ �Լ�
	void create(float fPosX, float fPosY,float fAngle,float fSpeed);

	virtual void update()			override;
	virtual void release()			override;
	virtual void render(HDC hdc)	override;

	//�޸����� ������ ���� �Լ�
	bool isDeleteEffect();

	void returnMemoryPool();
private:
	//�޸�Ǯ ����� �Ϲ����� ������ �ʱ�ȭ
	void initGeneral(const char* strEffectKey, float fPlayTime);


public:
	//getter setter

	//����Ʈ Ű�� �������� �Լ�
	inline const string& getEffectKEy() { return _strEffectKey; }
	
	//�������̹����� ������ ������
	inline void setFrameX(int nFrameX){_nFrameImgX = nFrameX;}
	inline void setFrameY(int nFrameY){_nFrameImgY = nFrameY;}
	inline void linkCamera(CAMERA* pCamera) { _pCamera = pCamera; }
};