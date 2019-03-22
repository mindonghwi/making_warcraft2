#include "stdafx.h"
#include "player.h"
#include "workMan.h"
PLAYER::PLAYER()
{
}

PLAYER::~PLAYER()
{
}

void PLAYER::init(float fPosX, float fPosY)
{

	_pUnitMgr = new UNITMGR();
	_pBuildMgr = new BUILDMGR();

	_pUnitMgr->setLinkAstar(_pAstar);
	_pUnitMgr->setLinkCamera(_pCamera);
	_pUnitMgr->setLinkBuildMgr(_pBuildMgr);
	_pUnitMgr->setLinkMap(_pMap);
	_pUnitMgr->setLinkResourceMgr(_pResourceMgr);
	_pUnitMgr->setLinkMyPlayer(this);
	_pUnitMgr->setLinkBulletMgr(_pBulletMgr);
	_pUnitMgr->setOpponent(_pOpponent);


	_pBuildMgr->setLinkCamera(_pCamera);
	_pBuildMgr->setLinkUnitMgr(_pUnitMgr);
	_pBuildMgr->setLinkMap(_pMap);
	_pBuildMgr->setLinkPlayer(this);

	_pUnitMgr->init();

	_pBuildMgr->init();


	//_pUnitMgr->createUnit(UNIT::E_UNIT::E_WORKMAN, TILESIZE * 19 + 16, TILESIZE * 11 + 16);
	//_pUnitMgr->createUnit(UNIT::E_UNIT::E_WORKMAN, TILESIZE * 17 + 16, TILESIZE * 11 + 16);
	//
	//_pUnitMgr->createUnit(UNIT::E_UNIT::E_WORKMAN, TILESIZE * 19 + 16, TILESIZE * 10 + 16);
	//_pUnitMgr->createUnit(UNIT::E_UNIT::E_WORKMAN, TILESIZE * 17 + 16, TILESIZE * 10 + 16);
	//
	//_pUnitMgr->createUnit(UNIT::E_UNIT::E_WORKMAN, TILESIZE * 13 + 16, TILESIZE * 10 + 16);
	//_pUnitMgr->createUnit(UNIT::E_UNIT::E_WORKMAN, TILESIZE * 14 + 16, TILESIZE * 10 + 16);
	//
	_pUnitMgr->createUnit(UNIT::E_UNIT::E_WORKMAN, fPosX,fPosY);

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
	commandAttack();
	commandBuild();
	commandHarvest();
	commandHold();
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
	


	if (_eBuilds != E_BUILDS::E_MAX)
	{
		int nTileCount = _pBuildMgr->getBuildWidth(_eBuilds) / TILESIZE;
		for (int i = 0; i < nTileCount; i++)
		{
			for (int j = 0; j < nTileCount; j++)
			{
				if (_ptCameraPtMouse.x / TILESIZE + i == 1)
				{
					IMAGEMANAGER->render("redTile", hdc, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().left, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().top);
				}
				else if (_ptCameraPtMouse.x / TILESIZE + i == TILECOUNTX-2)
				{
					IMAGEMANAGER->render("redTile", hdc, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().left, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().top);
				}
				else if (_ptCameraPtMouse.y / TILESIZE + j == 1)
				{
					IMAGEMANAGER->render("redTile", hdc, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().left, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().top);
				}
				else if (_ptCameraPtMouse.y / TILESIZE + j == TILECOUNTY - 2)
				{
					IMAGEMANAGER->render("redTile", hdc, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().left, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().top);
				}
				else if (_eBuilds == E_BUILDS::E_SHIPYARD || _eBuilds == E_BUILDS::E_OIL_PLATFORM || _eBuilds == E_BUILDS::E_FOUNDRY)
				{
					if ((_pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getTerrian() == TILE::E_TERRIAN::DIRT_WATER ||
						_pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getTerrian() == TILE::E_TERRIAN::WATER) &&
						(_pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getObject() == TILE::E_OBJECT::E_NONE || 
							_pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getObject() == TILE::E_OBJECT::E_UNIT))
					{
						IMAGEMANAGER->render("greenTile", hdc, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().left, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().top);
					}
					else
					{
						IMAGEMANAGER->render("redTile", hdc, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().left, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().top);
					}
				}
				else if (_eBuilds== E_BUILDS::E_OIL_REFINERY)
				{
					if (_pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getObject() == TILE::E_OBJECT::E_OILPATCH)
					{
						IMAGEMANAGER->render("greenTile", hdc, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().left, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().top);
					}
					else
					{
						IMAGEMANAGER->render("redTile", hdc, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().left, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().top);
					}
				}
				else
				{
					if ((_pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getTerrian() == TILE::E_TERRIAN::GROUND) &&
						(_pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getObject() == TILE::E_OBJECT::E_NONE ||
							_pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getObject() == TILE::E_OBJECT::E_UNIT))
					{
						IMAGEMANAGER->render("greenTile", hdc, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().left, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().top);
					}
					else
					{
						IMAGEMANAGER->render("redTile", hdc, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().left, _pMap->getTile(_ptCameraPtMouse.x / TILESIZE + i, _ptCameraPtMouse.y / TILESIZE + j)->getRectTile().top);
					}
				}
			}
		}

	}

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
		if (_eBuilds == E_BUILDS::E_MAX && !KEYMANAGER->isKeyDown('A'))
		{
			if (!KEYMANAGER->isKeyDown(VK_LCONTROL))
			{
				_pUnitMgr->clearCommandSelectedUnit();
			}
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
		if (_pUnitMgr->getUnitSelectedCount() > 0 && _pUnitMgr->getSelectedUnit(0)->getUnit() == UNIT::E_UNIT::E_WORKMAN && 	_eBuildType == E_BUILDTYPE::E_NONE)
		{
			//_pUnitMgr->getSelectedUnit(0)->setBuildingOn(true);
			_eBuildType = E_BUILDTYPE::E_B;
			return;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		if (_pUnitMgr->getUnitSelectedCount() > 0 && _pUnitMgr->getSelectedUnit(0)->getUnit() == UNIT::E_UNIT::E_WORKMAN && 	_eBuildType == E_BUILDTYPE::E_NONE)
		{
			//_pUnitMgr->getSelectedUnit(0)->setBuildingOn(true);
			_eBuildType = E_BUILDTYPE::E_V;
			return;
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		_eBuildType = E_BUILDTYPE::E_NONE;
		_eBuilds = E_BUILDS::E_MAX;

	}


	if (_pUnitMgr->getSelectedUnit(0) && _pUnitMgr->getSelectedUnit(0)->getUnit() == UNIT::E_UNIT::E_WORKMAN && _eBuildType == E_BUILDTYPE::E_B)
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

			if (KEYMANAGER->isOnceKeyDown('S') && _pBuildMgr->getIsBuildTree(E_BUILDS::E_TOWN))
			{
				_eBuilds = E_BUILDS::E_BLACK_SMITH;
			}

			if (KEYMANAGER->isOnceKeyDown('L') && _pBuildMgr->getIsBuildTree(E_BUILDS::E_TOWN))
			{
				_eBuilds = E_BUILDS::E_LUMBER_MILL;
			}

			if (KEYMANAGER->isOnceKeyDown('T') && _pBuildMgr->getIsBuildTree(E_BUILDS::E_BARRACKS))
			{
				_eBuilds = E_BUILDS::E_SCOUT_TOWER;
			}

			if (KEYMANAGER->isOnceKeyDown('G') && _pBuildMgr->getIsBuildTree(E_BUILDS::E_KEEP))
			{
				_eBuilds = E_BUILDS::E_GNOMISH_INVENTOR;
			}

			if (KEYMANAGER->isOnceKeyDown('K') && _pBuildMgr->getIsBuildTree(E_BUILDS::E_KEEP))
			{
				_eBuilds = E_BUILDS::E_STABLE;
			}
		}
	}
	
	if (_pUnitMgr->getSelectedUnit(0) && _pUnitMgr->getSelectedUnit(0)->getUnit() == UNIT::E_UNIT::E_WORKMAN && _eBuildType == E_BUILDTYPE::E_V)
	{
		if (KEYMANAGER->isOnceKeyDown('S') && _pBuildMgr->getIsBuildTree(E_BUILDS::E_KEEP))
		{
			_eBuilds = E_BUILDS::E_SHIPYARD;
		}

		if (KEYMANAGER->isOnceKeyDown('P'))// && _pBuildMgr->getIsBuildTree(E_BUILDS::E_CASTLE))
		{
			_eBuilds = E_BUILDS::E_OIL_PLATFORM;
		}
		
		if (KEYMANAGER->isOnceKeyDown('G') && _pBuildMgr->getIsBuildTree(E_BUILDS::E_CASTLE))
		{
			_eBuilds = E_BUILDS::E_GRYPHON_AVIARY;
		}

		if (KEYMANAGER->isOnceKeyDown('M') && _pBuildMgr->getIsBuildTree(E_BUILDS::E_CASTLE))
		{
			_eBuilds = E_BUILDS::E_MAGE_TOWER;
		}

		if (KEYMANAGER->isOnceKeyDown('F') && _pBuildMgr->getIsBuildTree(E_BUILDS::E_CASTLE))
		{
			_eBuilds = E_BUILDS::E_FOUNDRY;
		}
	}
	if (_pUnitMgr->getSelectedUnit(0) && _pUnitMgr->getSelectedUnit(0)->getUnit() == UNIT::E_UNIT::E_OILTANKER)
	{
		if (KEYMANAGER->isOnceKeyDown('O'))	
		{
			_eBuilds = E_BUILDS::E_OIL_REFINERY;
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
			_pUnitMgr->clearCommandSelectedUnit();
			_pUnitMgr->buildCommand((float)_ptCameraPtMouse.x, (float)_ptCameraPtMouse.y, _eBuilds);
			_eBuilds = E_BUILDS::E_MAX;
			_eBuildType = E_BUILDTYPE::E_NONE;
		}
		else if (_pUnitMgr->getSelectedUnit(0) && _pUnitMgr->getSelectedUnit(0)->getUnit() == UNIT::E_UNIT::E_OILTANKER && _eBuilds != E_BUILDS::E_MAX)
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
			if (!_pBuildMgr->bIsGroundCheck(_eBuilds, (float)_ptCameraPtMouse.x, (float)_ptCameraPtMouse.y))
			{
				return;
			}

			_arResource[static_cast<int>(E_RESOURCE::E_GOLD)] -= _pBuildMgr->getConsumptionResource(_pUnitMgr->getSelectedUnit(0)->getBuildType(), E_RESOURCE::E_GOLD);
			_arResource[static_cast<int>(E_RESOURCE::E_OIL)] -= _pBuildMgr->getConsumptionResource(_pUnitMgr->getSelectedUnit(0)->getBuildType(), E_RESOURCE::E_OIL);
			_arResource[static_cast<int>(E_RESOURCE::E_TREE)] -= _pBuildMgr->getConsumptionResource(_pUnitMgr->getSelectedUnit(0)->getBuildType(), E_RESOURCE::E_TREE);
			_pUnitMgr->clearCommandSelectedUnit();
			_pUnitMgr->buildCommand((float)_ptCameraPtMouse.x, (float)_ptCameraPtMouse.y, _eBuilds);
			_eBuilds = E_BUILDS::E_MAX;
			_eBuildType = E_BUILDTYPE::E_NONE;
		}
	}
}

void PLAYER::commandAttack()
{
	if (KEYMANAGER->isKeyDown('A'))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			//타겟이 잡혔다.
				//플레이어의 유닛 메니저에서
			bool bIsTargetIng = false;
			_pUnitMgr->clearCommandSelectedUnit();
			for (int i = 0; i < _pUnitMgr->getUnitCount(); i++)
			{
				if (PtInRect(_pUnitMgr->getUnit(i)->getCollisionRect(),_ptCameraPtMouse))
				{
					//여기에 유닛 어택을 내린다
					_pUnitMgr->commandAttack(_pUnitMgr->getUnit(i));
					//for (int j = 0; j < _pUnitMgr->getUnitSelectedCount(); j++)
					//{
					//	if (i != j)
					//	{
					//		
					//		_pUnitMgr->getSelectedUnit(j)->attack(_pUnitMgr->getUnit(i));
					//	}
					//}
					bIsTargetIng = true;
					break;
				}
			}
			
			for (int i = 0; i < _pOpponent->getUnitMgr()->getUnitCount(); i++)
			{
				if (PtInRect(_pOpponent->getUnitMgr()->getUnit(i)->getCollisionRect(), _ptCameraPtMouse))
				{
					//여기에 유닛 어택을 내린다
					_pUnitMgr->commandAttack(_pOpponent->getUnitMgr()->getUnit(i));
					bIsTargetIng = true;
					break;
				}
			}


				//플레이어의 건물 매니저에서
			for (int i = 0; i < _pBuildMgr->getBuildCount(); i++)
			{
				if (PtInRect(_pBuildMgr->getBuild(i)->getRect(), _ptCameraPtMouse))
				{
					//여기에 유닛 어택을 내린다
					_pUnitMgr->commandAttack(_pBuildMgr->getBuild(i));
					bIsTargetIng = true;
					break;
				}
			}
				//상대 유닛매니저에서

				//상대 건물매니저에서
			for (int i = 0; i < _pOpponent->getBuildMgr()->getBuildCount(); i++)
			{
				if (PtInRect(_pOpponent->getBuildMgr()->getBuild(i)->getRect(), _ptCameraPtMouse))
				{
					//여기에 유닛 어택을 내린다
					_pUnitMgr->commandAttack(_pBuildMgr->getBuild(i));
					bIsTargetIng = true;
					break;
				}
			}
			//타겟이 잡히지 않았다.

			//유닛들은 플레이어의 유닛매니저 빌드매니저 상대의 유닛매니저 빌드매니저를 알아야한다.
			if (!bIsTargetIng)
			{
				_pUnitMgr->commandMoveAttack((float)_ptCameraPtMouse.x, (float)_ptCameraPtMouse.y);
			}
			
		}
	}

}

void PLAYER::commandHold()
{
	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		_pUnitMgr->commandHold();
	}
}

void PLAYER::commandHarvest()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (_eBuilds == E_BUILDS::E_MAX && !KEYMANAGER->isKeyDown('A'))
		{
			
			
			if (_pResourceMgr->clickedResources(_ptCameraPtMouse) == static_cast<int>(E_RESOURCE::E_GOLD))
			{
				_pUnitMgr->clearCommandSelectedUnit();
				_pUnitMgr->commandHarvest(_pResourceMgr->getResource(_ptCameraPtMouse));
			}
			else if (_pResourceMgr->clickedResources(_ptCameraPtMouse) == static_cast<int>(E_RESOURCE::E_TREE))
			{
				_pUnitMgr->clearCommandSelectedUnit();
				_pUnitMgr->commandHarvest(_pResourceMgr->getResource(_ptCameraPtMouse));
			}
			


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
			_eBuildType = E_BUILDTYPE::E_NONE;
			_eBuilds = E_BUILDS::E_MAX;

			_pBuildMgr->selectedBuild(_rcDragArea);
		}
		else
		{
			if (_pUnitMgr->getSelectedUnit(0)->getUnit() != UNIT::E_UNIT::E_WORKMAN)
			{
				_eBuildType = E_BUILDTYPE::E_NONE;
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

