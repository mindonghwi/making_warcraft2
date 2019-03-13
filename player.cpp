#include "stdafx.h"
#include "player.h"
#include "workMan.h"

PLAYER::PLAYER()
{
}

PLAYER::~PLAYER()
{
}

void PLAYER::init()
{

	_pUnitMgr = new UNITMGR();
	_pBuildMgr = new BUILDMGR();

	_pUnitMgr->setLinkAstar(_pAstar);
	_pUnitMgr->setLinkCamera(_pCamera);
	_pUnitMgr->setLinkBuildMgr(_pBuildMgr);
	_pUnitMgr->setLinkMap(_pMap);


	_pBuildMgr->setLinkCamera(_pCamera);
	_pBuildMgr->setLinkUnitMgr(_pUnitMgr);
	_pBuildMgr->setLinkMap(_pMap);
	_pBuildMgr->setLinkPlayer(this);

	_pUnitMgr->init();

	_pBuildMgr->init();


	_pUnitMgr->createUnit(UNIT::E_UNIT::E_WORKMAN, TILESIZE * 19 + 16, TILESIZE * 11 + 16);
	_pUnitMgr->createUnit(UNIT::E_UNIT::E_WORKMAN, TILESIZE * 17 + 16, TILESIZE * 11 + 16);

	_pUnitMgr->createUnit(UNIT::E_UNIT::E_WORKMAN, TILESIZE * 19 + 16, TILESIZE * 10 + 16);
	_pUnitMgr->createUnit(UNIT::E_UNIT::E_WORKMAN, TILESIZE * 17 + 16, TILESIZE * 10 + 16);

	_pUnitMgr->createUnit(UNIT::E_UNIT::E_WORKMAN, TILESIZE * 13 + 16, TILESIZE * 10 + 16);
	_pUnitMgr->createUnit(UNIT::E_UNIT::E_WORKMAN, TILESIZE * 14 + 16, TILESIZE * 10 + 16);


	_ptCameraPtMouse.x = _ptMouse.x + _pCamera->getLeft();
	_ptCameraPtMouse.y = _ptMouse.y + _pCamera->getTop();


	_eBuilds = E_BUILDS::E_MAX;

	//initDrag
	initDrag();
}

void PLAYER::update()
{
	//마우스 위치 재설정
	_ptCameraPtMouse.x = _ptMouse.x + _pCamera->getLeft();
	_ptCameraPtMouse.y = _ptMouse.y + _pCamera->getTop();




	_pUnitMgr->selectedUnit();
	dragSelect();

	//여기서 무슨 커맨더를 주는지 넣어야한다.
	//_pUnitMgr->commandSelectUnit();
	commandSelectUnit();
	commandBuild();

	_pUnitMgr->update();



	_pBuildMgr->update();
}

void PLAYER::release()
{



}

void PLAYER::render(HDC hdc)
{
	_pUnitMgr->render(hdc);
	_pBuildMgr->render(hdc);

	DrawEdge(hdc,&_rcDragArea, BDR_RAISEDOUTER, BF_FLAT | BF_TOPLEFT | BF_BOTTOMRIGHT);


	char str[128];
	sprintf_s(str, "%d,%d,%d,%d", (_arResource[static_cast<int>(E_RESOURCE::E_GOLD)]), (_arResource[static_cast<int>(E_RESOURCE::E_TREE)]), (_arResource[static_cast<int>(E_RESOURCE::E_OIL)]),_nMaxPopulation);
	TextOut(hdc, WINSIZEX/2, 32, str, strlen(str));
}

bool PLAYER::createUnit(UNIT::E_UNIT eUnit)
{
	//인구수 부족
	if (_nMaxPopulation <= _nPopulation + _pUnitMgr->getUnitPopulation(eUnit)) return false;
	
	//자원 부족
	for (int i = 0; i < static_cast<int>(E_RESOURCE::E_MAX); i++)
	{
		if (_arResource[i] < _pUnitMgr->getUnitResource(eUnit,static_cast<E_RESOURCE>(i))) return false;
	}

	//생산을 허락한다.
	for (int i = 0; i < static_cast<int>(E_RESOURCE::E_MAX); i++)
	{
		_arResource[i] -= _pUnitMgr->getUnitResource(eUnit, static_cast<E_RESOURCE>(i));
	}

	_nPopulation += _pUnitMgr->getUnitPopulation(eUnit);

	//건물이 있으면 건물 주변
	//_pUnitMgr->createUnit(eUnit,)

	return true;
}



void PLAYER::selectedUnit()
{

}

void PLAYER::commandSelectUnit()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (_eBuilds == E_BUILDS::E_MAX)
		{
			_pUnitMgr->moveCommand((float)_ptCameraPtMouse.x, (float)_ptCameraPtMouse.y);
		}
	}						   
}

void PLAYER::commandBuild()
{
	_ptCameraPtMouse.x = _ptMouse.x + _pCamera->getLeft();
	_ptCameraPtMouse.y = _ptMouse.y + _pCamera->getTop();

	


	//선택된 애들중 workMan이 있을때
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		if (_pUnitMgr->getSelectedUnit(0)->getUnit() == UNIT::E_UNIT::E_WORKMAN)
		{
			//_pUnitMgr->getSelectedUnit(0)->setBuildingOn(true);
			_bIsBuild = true;
		}
	}


	if (_pUnitMgr->getSelectedUnit(0) && _pUnitMgr->getSelectedUnit(0)->getUnit() == UNIT::E_UNIT::E_WORKMAN)
	{
		//if (_pUnitMgr->getSelectedUnit(0)->getBuildingOn())
		{
			if (KEYMANAGER->isOnceKeyDown('H'))
			{
				_eBuilds = E_BUILDS::E_TOWN;
				//_pUnitMgr->getSelectedUnit(0)->setBuildType(E_BUILDS::E_TOWN);
			}

			if (KEYMANAGER->isOnceKeyDown('F'))
			{
				_eBuilds = E_BUILDS::E_FARM;
			}

			if (KEYMANAGER->isOnceKeyDown('B'))
			{
				_eBuilds = E_BUILDS::E_BARRACKS;
			}
		}
	}
	

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		//선택된 일군이 하나이며 빌드 온 상태일때
		if (_pUnitMgr->getSelectedUnit(0) && _pUnitMgr->getSelectedUnit(0)->getUnit() == UNIT::E_UNIT::E_WORKMAN && _eBuilds != E_BUILDS::E_MAX)// && _pUnitMgr->getSelectedUnit(0)->getBuildingOn())
		{
			//금부족
			if (_pBuildMgr->getConsumptionResource(_pUnitMgr->getSelectedUnit(0)->getBuildType(), E_RESOURCE::E_GOLD) > getGold())
			{
				return;
			}
			if (_pBuildMgr->getConsumptionResource(_pUnitMgr->getSelectedUnit(0)->getBuildType(), E_RESOURCE::E_OIL) > getOil())
			{
				return;
			}
			if (_pBuildMgr->getConsumptionResource(_pUnitMgr->getSelectedUnit(0)->getBuildType(), E_RESOURCE::E_TREE) > getTree())
			{
				return;
			}
			//자리부족
			if (!_pBuildMgr->bIsGroundCheck(_eBuilds,(float)_ptCameraPtMouse.x, (float)_ptCameraPtMouse.y))
			{
				return;
			}

			_arResource[static_cast<int>(E_RESOURCE::E_GOLD)] -= _pBuildMgr->getConsumptionResource(_pUnitMgr->getSelectedUnit(0)->getBuildType(), E_RESOURCE::E_GOLD);
			_arResource[static_cast<int>(E_RESOURCE::E_OIL)] -= _pBuildMgr->getConsumptionResource( _pUnitMgr->getSelectedUnit(0)->getBuildType(), E_RESOURCE::E_OIL);
			_arResource[static_cast<int>(E_RESOURCE::E_TREE)] -= _pBuildMgr->getConsumptionResource(_pUnitMgr->getSelectedUnit(0)->getBuildType(), E_RESOURCE::E_TREE);

			_pUnitMgr->buildCommand((float)_ptCameraPtMouse.x, (float)_ptCameraPtMouse.y, _eBuilds);
			_eBuilds = E_BUILDS::E_MAX;
			_bIsBuild = false;
		}
	}
}

void PLAYER::initDrag()
{
	_rcDragArea = { 0,0,0,0 };
	_nDragLeft = 0;
	_nDragTop = 0;			
	_bIsDrag = false;			


}

void PLAYER::dragSelect()
{

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (!_bIsDrag)
		{
			_nDragLeft = _ptCameraPtMouse.x;
			_nDragTop = _ptCameraPtMouse.y;
			_bIsDrag = true;
		}
		
		_rcDragArea = { _nDragLeft, _nDragTop, _ptCameraPtMouse.x,_ptCameraPtMouse.y };
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		readjustDragRect();
		_pUnitMgr->dragSelect(_rcDragArea);


		if (_pUnitMgr->getUnitSelectedCount() == 0)
		{
			_pBuildMgr->selectedBuild(_rcDragArea);
		}
		else
		{
			if (_pUnitMgr->getSelectedUnit(0)->getUnit() != UNIT::E_UNIT::E_WORKMAN)
			{
				_bIsBuild = false;
				_eBuilds = E_BUILDS::E_MAX;
			}
		}
		initDrag();
	}
}

void PLAYER::readjustDragRect()
{
	if (_nDragLeft > _ptCameraPtMouse.x)
	{
		int nTmp = _nDragLeft;
		_nDragLeft = _ptCameraPtMouse.x;
		_ptCameraPtMouse.x = nTmp;
	}

	if (_nDragTop > _ptCameraPtMouse.y)
	{
		int nTmp = _nDragTop;
		_nDragTop = _ptCameraPtMouse.y;
		_ptCameraPtMouse.y = nTmp;
	}


	_rcDragArea = { _nDragLeft, _nDragTop, _ptCameraPtMouse.x,_ptCameraPtMouse.y };
	_rcDragArea.right++;
	_rcDragArea.bottom++;

}
