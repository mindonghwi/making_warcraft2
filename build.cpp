#include "stdafx.h"
#include "build.h"
#include "camera.h"
#include "unit.h"
#include "unitMGr.h"
#include "buildMgr.h"
BUILD::BUILD()
{
}

BUILD::~BUILD()
{
}

void BUILD::create(int nLeft, int ntop, int nWidth, int nHeight, int nHp, float fBuildingTimer, int nFrameCount, const string& strImgKey)
{

	OBJECT::init(static_cast<float>(nLeft + nWidth/2), static_cast<float>(ntop + nHeight/2), nWidth, nHeight);		//��ġ����
	_nHp = nHp;											//hp
	_fBuildingTimer = fBuildingTimer;					//�ǹ����� �ѽð�
	_eState = BUILD::E_STATE::E_CREATING;				//�ǹ� ����
	_fTimer = 0.0f;

	_nMaxFrameX = nFrameCount;							//�� �����Ӽ�
	_nFrameX = 0;					

	setImage(IMAGEMANAGER->findImage(strImgKey));

	_fOffsetFrame = _fBuildingTimer / static_cast<float>(_nMaxFrameX);
	
	_nUnitMask = 0;

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

void BUILD::selectRender(HDC hdc)
{
	DrawEdge(hdc, OBJECT::getRect(), BDR_RAISEDOUTER, BF_FLAT | BF_TOPLEFT | BF_BOTTOMRIGHT);

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

void BUILD::createUnit()
{
	//�ð��� ������ �ѹ��� ó���ؼ� �Ѹ���
	if (KEYMANAGER->isOnceKeyDown('P') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_WORKMAN))
	{
		//��������Ʈ�� ��ų� �ǹ��ֺ����� �������ų�
		_pUnitMgr->createUnit(UNIT::E_UNIT::E_WORKMAN, _fRayPointX, _fRayPointY);
	}


}


