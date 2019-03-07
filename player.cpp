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
	_listUnit.push_back(new WORKMAN);
	_listUnit.back()->setLinkCamera(_pCamera);
	_listUnit.back()->setLinkAStar(_pAstar);
	_listUnit.back()->init(WINSIZEX / 2, WINSIZEY / 2, 64, 64);
	_listUnit.back()->create(TILESIZE*19+16, TILESIZE * 11 + 16, 100, 1.0f, 10, 0, 100.0f, 50.0f, 1.0f);

	allocateUnitResource();
	allocateUnitPopulation();

	_ptCameraPtMouse.x = _ptMouse.x + _pCamera->getLeft();
	_ptCameraPtMouse.y = _ptMouse.y + _pCamera->getTop();

}

void PLAYER::update()
{
	//마우스 위치 재설정
	_ptCameraPtMouse.x = _ptMouse.x + _pCamera->getLeft();
	_ptCameraPtMouse.y = _ptMouse.y + _pCamera->getTop();
	list<UNIT*>::iterator	iterUnitList = _listUnit.begin();
	list<UNIT*>::iterator	endUnitList = _listUnit.end();

	selectedUnit();


	//클릭 드레그가 아니다.
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		iterUnitList = _listUnit.begin();
		endUnitList = _listUnit.end();
		bool bIsFind = false;

		while (iterUnitList != endUnitList && !bIsFind)
		{
			UNIT* pUnit = *iterUnitList;
			if (PtInRect(pUnit->getConstCollisionRect(), _ptCameraPtMouse))
			{
				_vSeletedUnit.clear();
				_vSeletedUnit.push_back(&(*iterUnitList));
				bIsFind = true;
			}

			pUnit = nullptr;
			iterUnitList++;
		}
	}

	commandSelectUnit();


	iterUnitList = _listUnit.begin();
	endUnitList = _listUnit.end();
	while (iterUnitList != endUnitList)
	{
		UNIT* pUnit = *iterUnitList;
		pUnit->update();
		iterUnitList++;
	}
}

void PLAYER::release()
{
	_vSeletedUnit.clear();

	while (!_listUnit.empty())
	{
		UNIT* pUnit = _listUnit.front();
		pUnit->release();
		_listUnit.pop_front();
		delete pUnit;
		pUnit = nullptr;
	}


}

void PLAYER::render(HDC hdc)
{
	for (int i = 0; i < static_cast<int>(_vSeletedUnit.size()); i++)
	{
		(*(_vSeletedUnit[i]))->renderSelected(hdc);
	}
}

bool PLAYER::createUnit(UNIT::E_UNIT eUnit)
{
	//인구수 부족
	if (_nMaxPopulation <= _nPopulation + _arUnitPopulation[static_cast<int>(eUnit)]) return false;
	
	//자원 부족
	for (int i = 0; i < static_cast<int>(PLAYER::E_RESOURCE::E_MAX); i++)
	{
		if (_arResource[i] < _arUnitResource[static_cast<int>(eUnit)][i]) return false;
	}

	//생산을 허락한다.
	for (int i = 0; i < static_cast<int>(PLAYER::E_RESOURCE::E_MAX); i++)
	{
		_arResource[i] -= _arUnitResource[static_cast<int>(eUnit)][i];
	}

	_nPopulation += _arUnitPopulation[static_cast<int>(eUnit)];


	return true;
}

void PLAYER::allocateUnitPopulation()
{
	for (int i = 0; i < static_cast<int>(UNIT::E_UNIT::E_MAX); i++)
	{
		_arUnitPopulation[i] = 2;
	}

	_arUnitPopulation[static_cast<int>(UNIT::E_UNIT::E_BALLISTA)] = 3;
	_arUnitPopulation[static_cast<int>(UNIT::E_UNIT::E_KNIGHT)] = 3;
	_arUnitPopulation[static_cast<int>(UNIT::E_UNIT::E_MAGICIAN)] = 3;
	_arUnitPopulation[static_cast<int>(UNIT::E_UNIT::E_FLYER)] = 3;
	_arUnitPopulation[static_cast<int>(UNIT::E_UNIT::E_BATTLESHIP)] = 3;
	_arUnitPopulation[static_cast<int>(UNIT::E_UNIT::E_SUBMARIN)] = 3;

	
	_arUnitPopulation[static_cast<int>(UNIT::E_UNIT::E_WORKMAN)] = 1;
	_arUnitPopulation[static_cast<int>(UNIT::E_UNIT::E_FOOTMAN)] = 1;
}

void PLAYER::allocateUnitResource()
{
	for (int i = 0; i < static_cast<int>(UNIT::E_UNIT::E_MAX); i++)
	{
		for (int j = 0; j <  static_cast<int>(PLAYER::E_RESOURCE::E_MAX); j++)
		{
			_arUnitResource[i][j] = 0;
		}
	}

	//workman
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_WORKMAN)][static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)] = 400;

	//footman
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_FOOTMAN)][static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)] = 600;

	//archer
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_ARCHER)][static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)] = 500;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_ARCHER)][static_cast<int>(PLAYER::E_RESOURCE::E_TREE)] = 50;

	//ballista
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_BALLISTA)][static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)] = 900;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_BALLISTA)][static_cast<int>(PLAYER::E_RESOURCE::E_TREE)] = 300;

	//knight
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_KNIGHT)][static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)] = 800;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_KNIGHT)][static_cast<int>(PLAYER::E_RESOURCE::E_TREE)] = 100;

	//bomber
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_BOMBER)][static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)] = 750;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_BOMBER)][static_cast<int>(PLAYER::E_RESOURCE::E_TREE)] = 50;

	//ditecter
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_RECONNAISSANCE)][static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)] = 500;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_RECONNAISSANCE)][static_cast<int>(PLAYER::E_RESOURCE::E_TREE)] = 100;

	//mage
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_MAGICIAN)][static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)] = 1200;

	//flyer
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_FLYER)][static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)] = 2500;

	//oiltanger
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_OILTANKER)][static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)] = 400;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_OILTANKER)][static_cast<int>(PLAYER::E_RESOURCE::E_TREE)] = 250;

	//transport
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_TRANSPORT)][static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)] = 400;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_TRANSPORT)][static_cast<int>(PLAYER::E_RESOURCE::E_TREE)] = 250;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_TRANSPORT)][static_cast<int>(PLAYER::E_RESOURCE::E_OIL)] = 400;

	//galleys
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_GALLEYS)][static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)] = 700;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_GALLEYS)][static_cast<int>(PLAYER::E_RESOURCE::E_TREE)] = 350;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_GALLEYS)][static_cast<int>(PLAYER::E_RESOURCE::E_OIL)] = 700;

	//battleShip
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_BATTLESHIP)][static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)] = 1000;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_BATTLESHIP)][static_cast<int>(PLAYER::E_RESOURCE::E_TREE)] = 500;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_BATTLESHIP)][static_cast<int>(PLAYER::E_RESOURCE::E_OIL)] = 1000;

	//SubMarine
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_SUBMARIN)][static_cast<int>(PLAYER::E_RESOURCE::E_GOLD)] = 800;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_SUBMARIN)][static_cast<int>(PLAYER::E_RESOURCE::E_TREE)] = 150;
	_arUnitResource[static_cast<int>(UNIT::E_UNIT::E_SUBMARIN)][static_cast<int>(PLAYER::E_RESOURCE::E_OIL)] = 800;
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
	for (int i = 0; i < static_cast<int>(_vSeletedUnit.size()); i++)
	{
		(*(_vSeletedUnit[i]))->command();
	}

}
