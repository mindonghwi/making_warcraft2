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

	OBJECT::init(static_cast<float>(nLeft + nWidth/2), static_cast<float>(ntop + nHeight/2), nWidth, nHeight);		//위치상정
	_fHp = 0.0f;
	_nMaxHp = nHp;
	_fOffsetHpTimer = fBuildingTimer/ static_cast<float>(_nMaxHp);	//hp1당 증가하는 시간 간격
	_fHpTimer = 0.0f;
	_fBuildingTimer = fBuildingTimer;					//건물짓는 총시간
	_eState = BUILD::E_STATE::E_CREATING;				//건물 상태
	_fTimer = 0.0f;

	_nMaxFrameX = nFrameCount;							//총 프레임수
	_nFrameX = 0;					

	setImage(IMAGEMANAGER->findImage(strImgKey));

	_fOffsetFrame = _fBuildingTimer / static_cast<float>(_nMaxFrameX);
	_fOffsetFrame += _fOffsetFrame;

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
			int nIndexX = (getLeft() + 16) / TILESIZE;
			int nIndexY = (getTop() + 16) / TILESIZE;
			bool bIsFind = false;
			for (int i = -1; i < 6; i++)
			{
				for (int j = -1; j < 6; j++)
				{
					if (_pMap->getTile(nIndexX + i, nIndexY + j)->getObject() == TILE::E_OBJECT::E_NONE)
					{
						_fRayPointX = (float)_pMap->getTile(nIndexX + i, nIndexY + j)->getRectTile().left + 16.0f;
						_fRayPointY = (float)_pMap->getTile(nIndexX + i, nIndexY + j)->getRectTile().top + 16.0f;
						bIsFind = true;
						break;
					}
				}
				if (bIsFind)
				{
					break;
				}
			}

			createUnit();
		}
		destroyBuild();

	}



}

void BUILD::release()
{
	setImage(nullptr);

}

void BUILD::render(HDC hdc)
{
	OBJECT::getImage()->frameRenderCenter(hdc,OBJECT::getPosX(),OBJECT::getPosY(),_nFrameX,0);

}

void BUILD::cameraUpdate()
{
	_pCamera->pushRenderObject(this);

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
		OBJECT::decreaseHp(_nCreateDamage);//생상중 대미지 발생한것을 계산해준다.
		_nFrameX = _nMaxFrameX - 1;
	}


}

void BUILD::createUnit()
{
	//시간이 없으니 한번에 처리해서 뿌리자
	if (_eUnitType == BUILDMGR::E_UNITMASK::E_WORKMAN && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_WORKMAN))
	{
		//레이포인트로 쏘거나 건물주변으로 내보내거나
		_bIsProduce = false;		
		_pUnitMgr->createUnit(UNIT::E_UNIT::E_WORKMAN, _fRayPointX, _fRayPointY);
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_NONE;

	}
	else if (_eUnitType == BUILDMGR::E_UNITMASK::E_ARCHER && _nUnitMask &  static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_ARCHER))
	{
		//레이포인트로 쏘거나 건물주변으로 내보내거나
		_bIsProduce = false;
		_pUnitMgr->createUnit(UNIT::E_UNIT::E_ARCHER, _fRayPointX, _fRayPointY);
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_NONE;
	}
	else if (_eUnitType == BUILDMGR::E_UNITMASK::E_BALLISTA && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_BALLISTA))
	{
		//레이포인트로 쏘거나 건물주변으로 내보내거나
		_bIsProduce = false;
		_pUnitMgr->createUnit(UNIT::E_UNIT::E_BALLISTA, _fRayPointX, _fRayPointY);
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_NONE;
	}
	else if (_eUnitType == BUILDMGR::E_UNITMASK::E_FOOTMAN && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_FOOTMAN))
	{
		//레이포인트로 쏘거나 건물주변으로 내보내거나
		_bIsProduce = false;
		_pUnitMgr->createUnit(UNIT::E_UNIT::E_FOOTMAN, _fRayPointX, _fRayPointY);
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_NONE;
	}
	else if (_eUnitType == BUILDMGR::E_UNITMASK::E_BATTLESHIP && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_BATTLESHIP))
	{
		//레이포인트로 쏘거나 건물주변으로 내보내거나
		_bIsProduce = false;
		_pUnitMgr->createUnit(UNIT::E_UNIT::E_BATTLESHIP, _fRayPointX, _fRayPointY);
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_NONE;
	}
	else if (_eUnitType == BUILDMGR::E_UNITMASK::E_BOMBER && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_BOMBER))
	{
		//레이포인트로 쏘거나 건물주변으로 내보내거나
		_bIsProduce = false;
		_pUnitMgr->createUnit(UNIT::E_UNIT::E_BOMBER, _fRayPointX, _fRayPointY);
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_NONE;
	}
	else if (_eUnitType == BUILDMGR::E_UNITMASK::E_FLYER && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_FLYER))
	{
		//레이포인트로 쏘거나 건물주변으로 내보내거나
		_bIsProduce = false;
		_pUnitMgr->createUnit(UNIT::E_UNIT::E_FLYER, _fRayPointX, _fRayPointY);
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_NONE;
	}
	else if (_eUnitType == BUILDMGR::E_UNITMASK::E_GALLEYS && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_GALLEYS))
	{
		//레이포인트로 쏘거나 건물주변으로 내보내거나
		_bIsProduce = false;
		_pUnitMgr->createUnit(UNIT::E_UNIT::E_GALLEYS, _fRayPointX, _fRayPointY);
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_NONE;
	}
	else if (_eUnitType == BUILDMGR::E_UNITMASK::E_KNIGHT && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_KNIGHT))
	{
		//레이포인트로 쏘거나 건물주변으로 내보내거나
		_bIsProduce = false;
		_pUnitMgr->createUnit(UNIT::E_UNIT::E_KNIGHT, _fRayPointX, _fRayPointY);
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_NONE;
	}
	else if (_eUnitType == BUILDMGR::E_UNITMASK::E_MAGICIAN && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_MAGICIAN))
	{
		//레이포인트로 쏘거나 건물주변으로 내보내거나
		_bIsProduce = false;
		_pUnitMgr->createUnit(UNIT::E_UNIT::E_MAGICIAN, _fRayPointX, _fRayPointY);
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_NONE;
	}
	else if (_eUnitType == BUILDMGR::E_UNITMASK::E_OILTANKER && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_OILTANKER))
	{
		//레이포인트로 쏘거나 건물주변으로 내보내거나
		_bIsProduce = false;
		_pUnitMgr->createUnit(UNIT::E_UNIT::E_OILTANKER, _fRayPointX, _fRayPointY);
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_NONE;
	}
	else if (_eUnitType == BUILDMGR::E_UNITMASK::E_RECONNAISSANCE && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_RECONNAISSANCE))
	{
		//레이포인트로 쏘거나 건물주변으로 내보내거나
		_bIsProduce = false;
		_pUnitMgr->createUnit(UNIT::E_UNIT::E_RECONNAISSANCE, _fRayPointX, _fRayPointY);
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_NONE;
	}
	else if (_eUnitType == BUILDMGR::E_UNITMASK::E_SUBMARIN && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_SUBMARIN))
	{
		//레이포인트로 쏘거나 건물주변으로 내보내거나
		_bIsProduce = false;
		_pUnitMgr->createUnit(UNIT::E_UNIT::E_SUBMARIN, _fRayPointX, _fRayPointY);
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_NONE;
	}
	else if (_eUnitType == BUILDMGR::E_UNITMASK::E_TRANSPORT && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_TRANSPORT))
	{
		//레이포인트로 쏘거나 건물주변으로 내보내거나
		_bIsProduce = false;
		_pUnitMgr->createUnit(UNIT::E_UNIT::E_TRANSPORT, _fRayPointX, _fRayPointY);
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_NONE;
	}
}

void BUILD::commandProduce()
{
	if (_eState != BUILD::E_STATE::E_ISON) return;

	if (KEYMANAGER->isOnceKeyDown('P') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_WORKMAN))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_WORKMAN;
	}
	if (KEYMANAGER->isOnceKeyDown('F') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_FOOTMAN))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_FOOTMAN;

	}
	if (KEYMANAGER->isOnceKeyDown('A') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_ARCHER) && (_pBuildMgr->getIsBuildTree(E_BUILDS::E_LUMBER_MILL)))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_ARCHER;

	}
	if (KEYMANAGER->isOnceKeyDown('B') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_BALLISTA))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_BALLISTA;

	}
	if (KEYMANAGER->isOnceKeyDown('K') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_KNIGHT))// && (_pBuildMgr->getIsBuildTree(E_BUILDS::E_STABLE)))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_KNIGHT;

	}

	if (KEYMANAGER->isOnceKeyDown('M') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_MAGICIAN))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_MAGICIAN;

	}

	if (KEYMANAGER->isOnceKeyDown('F') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_RECONNAISSANCE))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_RECONNAISSANCE;

	}
	if (KEYMANAGER->isOnceKeyDown('D') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_BOMBER))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_BOMBER;

	}

	if (KEYMANAGER->isOnceKeyDown('E') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_GALLEYS))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_GALLEYS;

	}
	if (KEYMANAGER->isOnceKeyDown('O') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_OILTANKER))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_OILTANKER;

	}

	if (KEYMANAGER->isOnceKeyDown('T') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_TRANSPORT) && (_pBuildMgr->getIsBuildTree(E_BUILDS::E_FOUNDRY)))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_TRANSPORT;

	}

	if (KEYMANAGER->isOnceKeyDown('B') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_BATTLESHIP) && (_pBuildMgr->getIsBuildTree(E_BUILDS::E_FOUNDRY)))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_BATTLESHIP;

	}

	if (KEYMANAGER->isOnceKeyDown('S') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_SUBMARIN) && (_pBuildMgr->getIsBuildTree(E_BUILDS::E_FOUNDRY)))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_SUBMARIN;

	}

	if (KEYMANAGER->isOnceKeyDown('G') && _nUnitMask & static_cast<unsigned int>(BUILDMGR::E_UNITMASK::E_FLYER))
	{
		_bIsProduce = true;
		_fTimer = 0.0f;
		_eUnitType = BUILDMGR::E_UNITMASK::E_FLYER;

	}
}

void BUILD::upgradeBuild()
{
}

void BUILD::destroyBuild()
{
	if (_nHp <= 0)
	{
		_eState = E_STATE::E_DESTROY;
	
		int nTileCount = _pBuildMgr->getBuildWidth(_eBuilds) / TILESIZE;

		int nIndexX = static_cast<int>(getLeft()+ 16) / TILESIZE;
		int nIndexY = static_cast<int>(getTop() + 16) / TILESIZE;


		for (int i = 0; i < nTileCount; i++)
		{
			for (int j = 0; j < nTileCount; j++)
			{
				_pMap->getTile(nIndexX + i, nIndexY + j)->setObject(TILE::E_OBJECT::E_NONE);
			}
		}
	
	}


}


