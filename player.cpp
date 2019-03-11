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

	_pUnitMgr->setLinkAstar(_pAstar);
	_pUnitMgr->setLinkCamera(_pCamera);

	_pUnitMgr->init();



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
	//���콺 ��ġ �缳��
	_ptCameraPtMouse.x = _ptMouse.x + _pCamera->getLeft();
	_ptCameraPtMouse.y = _ptMouse.y + _pCamera->getTop();
	list<UNIT*>::iterator	iterUnitList = _listUnit.begin();
	list<UNIT*>::iterator	endUnitList = _listUnit.end();


	_pUnitMgr->selectedUnit();
	dragSelect();

	_pUnitMgr->commandSelectUnit();

	_pUnitMgr->update();
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
	//�α��� ����
	if (_nMaxPopulation <= _nPopulation + _pUnitMgr->getUnitPopulation(eUnit)) return false;
	
	//�ڿ� ����
	for (int i = 0; i < static_cast<int>(E_RESOURCE::E_MAX); i++)
	{
		if (_arResource[i] < _pUnitMgr->getUnitResource(eUnit,static_cast<E_RESOURCE>(i))) return false;
	}

	//������ ����Ѵ�.
	for (int i = 0; i < static_cast<int>(E_RESOURCE::E_MAX); i++)
	{
		_arResource[i] -= _pUnitMgr->getUnitResource(eUnit, static_cast<E_RESOURCE>(i));
	}

	_nPopulation += _pUnitMgr->getUnitPopulation(eUnit);

	//�ǹ��� ������ �ǹ� �ֺ�
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
