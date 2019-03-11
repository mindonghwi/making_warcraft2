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




	//initDrag
	initDrag();
}

void PLAYER::update()
{
	//마우스 위치 재설정
	_ptCameraPtMouse.x = _ptMouse.x + _pCamera->getLeft();
	_ptCameraPtMouse.y = _ptMouse.y + _pCamera->getTop();
	list<UNIT*>::iterator	iterUnitList = _listUnit.begin();
	list<UNIT*>::iterator	endUnitList = _listUnit.end();


	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		commandBuild();
	}

	_pUnitMgr->selectedUnit();
	dragSelect();

	//여기서 무슨 커맨더를 주는지 넣어야한다.
	_pUnitMgr->commandSelectUnit();

	_pUnitMgr->update();



	_pBuildMgr->update();
}

void PLAYER::release()
{



}

void PLAYER::render(HDC hdc)
{


	_pUnitMgr->render(hdc);

	DrawEdge(hdc,&_rcDragArea, BDR_RAISEDOUTER, BF_FLAT | BF_TOPLEFT | BF_BOTTOMRIGHT);

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
	for (int i = 0; i < static_cast<int>(_vSeletedUnit.size()); i++)
	{
		(*(_vSeletedUnit[i]))->setSelected(true);
	}
}

void PLAYER::commandSelectUnit()
{
	//for (int i = 0; i < static_cast<int>(_vSeletedUnit.size()); i++)
	//{
	//	(*(_vSeletedUnit[i]))->commandMove(i);
	//}

}

void PLAYER::commandBuild()
{
	_ptCameraPtMouse.x = _ptMouse.x + _pCamera->getLeft();
	_ptCameraPtMouse.y = _ptMouse.y + _pCamera->getTop();

	//선택된 애들중 workMan이 있을때
	//if (KEYMANAGER->isOnceKeyDown('B'))
	//{
	//	 _bNormalBuildingOn = true;
	//}
	//
	//if (_bNormalBuildingOn)
	//{
	//	if (KEYMANAGER->isOnceKeyDown('H'))
	//	{
	//		//지을 준비
	//		_eBuilds = BUILDMGR::E_BUILDS::E_TOWN;
	//	}
	//
	//}


	//선택된 일군이 하나이며 빌드 온 상태일때
	if (_vSeletedUnit.size() == 1 && (*_vSeletedUnit.front())->getBuildingOn())
	{
		//금부족
		if (_pBuildMgr->getConsumptionResource((*_vSeletedUnit.front())->getBuildType(),E_RESOURCE::E_GOLD) > getGold())
		{
			return;
		}
		if (_pBuildMgr->getConsumptionResource((*_vSeletedUnit.front())->getBuildType(), E_RESOURCE::E_OIL) > getOil())
		{
			return;
		}
		if (_pBuildMgr->getConsumptionResource((*_vSeletedUnit.front())->getBuildType(), E_RESOURCE::E_TREE) > getTree())
		{
			return;
		}
		//자리부족
		if (!_pBuildMgr->bIsGroundCheck(_ptCameraPtMouse.x,_ptCameraPtMouse.y))
		{
			return;
		}

		_arResource[static_cast<int>(E_RESOURCE::E_GOLD)] -= _pBuildMgr->getConsumptionResource((*_vSeletedUnit.front())->getBuildType(), E_RESOURCE::E_GOLD);
		_arResource[static_cast<int>(E_RESOURCE::E_OIL)] -= _pBuildMgr->getConsumptionResource((*_vSeletedUnit.front())->getBuildType(), E_RESOURCE::E_OIL);
		_arResource[static_cast<int>(E_RESOURCE::E_TREE)] -= _pBuildMgr->getConsumptionResource((*_vSeletedUnit.front())->getBuildType(), E_RESOURCE::E_TREE);

		(*_vSeletedUnit.front())->commandBuild();

		//(*_vSeletedUnit.front())->
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
	if (KEYMANAGER->isKeyDown(VK_LBUTTON))
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

}
