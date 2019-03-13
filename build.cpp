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
	_fHp = 0.0f;
	_nMaxHp = nHp;
	_fOffsetHpTimer = fBuildingTimer/ static_cast<float>(_nMaxHp);	//hp1�� �����ϴ� �ð� ����
	_fHpTimer = 0.0f;
	_fBuildingTimer = fBuildingTimer;					//�ǹ����� �ѽð�
	_eState = BUILD::E_STATE::E_CREATING;				//�ǹ� ����
	_fTimer = 0.0f;

	_nMaxFrameX = nFrameCount;							//�� �����Ӽ�
	_nFrameX = 0;					

	setImage(IMAGEMANAGER->findImage(strImgKey));

	_fOffsetFrame = _fBuildingTimer / static_cast<float>(_nMaxFrameX);
	
	_nUnitMask = 0;
	_fRayPointX = 0.0f;
	_fRayPointY = 0.0f;

	_bIsProduce = false;
	_nCreateDamage = 0;
}

void BUILD::update()
{
	_fTimer += TIMEMANAGER->getElapsedTime();

	if (_eState == BUILD::E_STATE::E_CREATING)
	{
		creatingUpdate();
	}
	else
	{
		//commandProduce();
		if (_fTimer >= 5.0f && _bIsProduce)
		{
			createUnit();
		}
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

	char str[128];
	sprintf_s(str, "%f", _fHp);
	TextOut(hdc, OBJECT::getLeft(), OBJECT::getTop(), str, strlen(str));
}

void BUILD::creatingUpdate()
{
	_fHpTimer += TIMEMANAGER->getElapsedTime();
	if (_fHpTimer >= _fOffsetHpTimer)
	{
		_fHp += static_cast<float>(_nMaxHp) * _fHpTimer / _fBuildingTimer;
		

		if (_fHp > _nMaxHp)
		{
			_fHp = (float)_nMaxHp;
		}

		_fHpTimer = 0.0f;
	}

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
		OBJECT::setHp(_nMaxHp);
		OBJECT::decreaseHp(_nCreateDamage);//������ ����� �߻��Ѱ��� ������ش�.
	}


}

void BUILD::createUnit()
{
	//�ð��� ������ �ѹ��� ó���ؼ� �Ѹ���
	if (_nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_WORKMAN))
	{
		//��������Ʈ�� ��ų� �ǹ��ֺ����� �������ų�
		_bIsProduce = false;		
		_pUnitMgr->createUnit(UNIT::E_UNIT::E_WORKMAN, _fRayPointX, _fRayPointY);
		_fTimer = 0.0f;
	}


}

void BUILD::commandProduce()
{
	if (_eState != BUILD::E_STATE::E_ISON) return;

	if (KEYMANAGER->isOnceKeyDown('P') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_WORKMAN))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
	}
	if (KEYMANAGER->isOnceKeyDown('A') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_ARCHER))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
	}
	if (KEYMANAGER->isOnceKeyDown('B') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_BALLISTA))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
	}
	if (KEYMANAGER->isOnceKeyDown('K') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_KNIGHT))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
	}


}


