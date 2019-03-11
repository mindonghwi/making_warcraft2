#include "stdafx.h"
#include "build.h"
#include "camera.h"
BUILD::BUILD()
{
}

BUILD::~BUILD()
{
}

void BUILD::create(float fPosX, float fPosY, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string& strImgKey)
{
	OBJECT::init(fPosX, fPosY, nWidth, nHeight);		//��ġ����
	_nHp = nHp;											//hp
	_fBuildingTimer = fBuildingTimer;					//�ǹ����� �ѽð�
	_eState = BUILD::E_STATE::E_CREATING;				//�ǹ� ����
	_fTimer = 0.0f;

	_nMaxFrameX = nFrameCount;							//�� �����Ӽ�
	_nFrameX = 0;					

	setImage(IMAGEMANAGER->findImage(strImgKey));

	_fOffsetFrame = _fBuildingTimer / static_cast<float>(_nMaxFrameX);
}

void BUILD::update()
{
	_fTimer += TIMEMANAGER->getElapsedTime();
	if (_eState == BUILD::E_STATE::E_CREATING)
	{
		creatingUpdate();
	}



	_pCamera->pushRenderObject(this);
}

void BUILD::release()
{
	setImage(nullptr);

}

void BUILD::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc,OBJECT::getPosX(),OBJECT::getPosY(),_nFrameX,0);

}

void BUILD::creatingUpdate()
{
	

	if (_fTimer >= _fOffsetFrame)
	{
		if (_nMaxFrameX-1 > _nFrameX)
		{
			_nFrameX++;
		}
		
		_fOffsetFrame += _fOffsetFrame;
	}
	
	
	if (_fTimer >=_fBuildingTimer)
	{
		_eState = BUILD::E_STATE::E_ISON;
		_fTimer = 0.0f;
	}


}


