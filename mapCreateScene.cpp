#include "stdafx.h"
#include "mapCreateScene.h"

SCENEMAPTOOL::SCENEMAPTOOL()
{
}

SCENEMAPTOOL::~SCENEMAPTOOL()
{
}

HRESULT SCENEMAPTOOL::init()
{
	_pMapTool = new MAPTOOL();
	_pCamera = new CAMERA();

	_pMapTool->setCamera(_pCamera);

	_pMapTool->init(TILECOUNTX, TILECOUNTY, TILESIZE);
	_pCamera->init(WINSIZEX/2,WINSIZEY/2, WINSIZEX-100,WINSIZEY, TILECOUNTX * TILESIZE, TILECOUNTY * TILESIZE);


	//파레트
	_pGround = IMAGEMANAGER->findImage("ground");
	_pDirt = IMAGEMANAGER->findImage("dirt");
	_pWater = IMAGEMANAGER->findImage("water");

	_rcGround = RectMake(WINSIZEX - TILESIZE, TILESIZE *0, TILESIZE, TILESIZE);
	_rcDirt = RectMake(WINSIZEX - TILESIZE, TILESIZE * 1, TILESIZE, TILESIZE);
	_rcWater = RectMake(WINSIZEX - TILESIZE, TILESIZE * 2, TILESIZE, TILESIZE);

	_pGoldMineIcon = IMAGEMANAGER->findImage("goldMineIcon");
	_rcGoldMine = RectMake(WINSIZEX - TILESIZE, TILESIZE * 3, TILESIZE, TILESIZE);

	_pTree = IMAGEMANAGER->findImage("treeIcon");
	_rcTree = RectMake(WINSIZEX - TILESIZE, TILESIZE * 4, TILESIZE, TILESIZE);

	_pOilPatch = IMAGEMANAGER->findImage("oilIcon");
	_rcOilPatch = RectMake(WINSIZEX - TILESIZE, TILESIZE * 5, TILESIZE, TILESIZE);

	return S_OK;
}

void SCENEMAPTOOL::release()
{
	_pMapTool->release();
	delete _pMapTool;
	_pMapTool = nullptr;

	_pCamera->release();
	delete _pCamera;
	_pCamera = nullptr;
}

void SCENEMAPTOOL::update()
{
	_pCamera->update();

	_pMapTool->update();


	//파레트 클릭
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rcGround,_ptMouse))
		{
			_pMapTool->setTerrian(TILE::E_TERRIAN::GROUND);
			_pMapTool->setObject(TILE::E_OBJECT::E_NONE);
		}
		else if (PtInRect(&_rcDirt, _ptMouse))
		{
			_pMapTool->setTerrian(TILE::E_TERRIAN::DIRT);
			_pMapTool->setObject(TILE::E_OBJECT::E_NONE);
		}
		else if (PtInRect(&_rcWater, _ptMouse))
		{
			_pMapTool->setTerrian(TILE::E_TERRIAN::WATER);
			_pMapTool->setObject(TILE::E_OBJECT::E_NONE);
		}
		else if (PtInRect(&_rcGoldMine,_ptMouse))
		{
			_pMapTool->setTerrian(TILE::E_TERRIAN::GROUND);
			_pMapTool->setObject(TILE::E_OBJECT::E_GOLDMINE);
		}
		else if (PtInRect(&_rcTree, _ptMouse))
		{
			_pMapTool->setTerrian(TILE::E_TERRIAN::GROUND);
			_pMapTool->setObject(TILE::E_OBJECT::E_TREE);
		}
		else if (PtInRect(&_rcOilPatch, _ptMouse))
		{
			_pMapTool->setTerrian(TILE::E_TERRIAN::WATER);
			_pMapTool->setObject(TILE::E_OBJECT::E_OILPATCH);
		}
	}

}

void SCENEMAPTOOL::render()
{
	_pCamera->renderinit();
	_pMapTool->render(_pCamera->getMemDC());

	_pCamera->render(getMemDC());


	_pGround->render(getMemDC(), _rcGround.left, _rcGround.top);
	_pDirt->render(getMemDC(), _rcDirt.left, _rcDirt.top);
	_pWater->render(getMemDC(), _rcWater.left, _rcWater.top);
	_pGoldMineIcon->render(getMemDC(), _rcGoldMine.left, _rcGoldMine.top);
	_pTree->render(getMemDC(), _rcTree.left, _rcTree.top);
	_pOilPatch->render(getMemDC(), _rcOilPatch.left, _rcOilPatch.top);

}
