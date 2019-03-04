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
	//생성
	_pMapTool = new MAPTOOL();
	_pCamera = new CAMERA();

	_btnSave = new button();
	_btnLoad = new button();
	_btnWidthAdd  = new button();
	_btnWidthSub  = new button();
	_btnHeightAdd = new button();
	_btnHeightSub = new button();

	//연결
	_pMapTool->setCamera(_pCamera);


	//초기화
	_pMapTool->init(TILECOUNTX, TILECOUNTY, TILESIZE);
	_pCamera->init(WINSIZEX/2,WINSIZEY/2, WINSIZEX-100,WINSIZEY, TILECOUNTX * TILESIZE*2, TILECOUNTY * TILESIZE * 2);
	
	_btnSave->init("btnSave", WINSIZEX - TILESIZE, TILESIZE * 8,bind(&SCENEMAPTOOL::save,this));
	_btnLoad->init("btnLoad", WINSIZEX - TILESIZE, TILESIZE * 9, bind(&SCENEMAPTOOL::load, this));
	_btnWidthAdd->init("btnAdd", WINSIZEX - (TILESIZE*2), TILESIZE * 10, bind(&SCENEMAPTOOL::addWidth, this));
	_btnWidthSub->init("btnSub", WINSIZEX - TILESIZE, TILESIZE * 10, bind(&SCENEMAPTOOL::subWidth, this));
	_btnHeightAdd->init("btnAdd", WINSIZEX - (TILESIZE * 2), TILESIZE * 11, bind(&SCENEMAPTOOL::addHeight, this));
	_btnHeightSub->init("btnSub", WINSIZEX - TILESIZE, TILESIZE * 11, bind(&SCENEMAPTOOL::subHeight, this));


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

	_pRock = IMAGEMANAGER->findImage("rockIcon");
	_rcRock = RectMake(WINSIZEX - TILESIZE, TILESIZE * 6, TILESIZE, TILESIZE);


	_pWidth = IMAGEMANAGER->findImage("iconWidth");
	_pHeight = IMAGEMANAGER->findImage("iconHeight");
	

	//카메로 초기 위치 오차범위 수정
	_pCamera->outOfRange();

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
		else if (PtInRect(&_rcRock, _ptMouse))
		{
			_pMapTool->setTerrian(TILE::E_TERRIAN::ROCK);
			_pMapTool->setObject(TILE::E_OBJECT::E_NONE);
		}
	}


	_btnSave->update();
	_btnLoad->update();
	_btnWidthAdd->update();
	_btnWidthSub->update();
	_btnHeightAdd->update();
	_btnHeightSub->update();
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
	_pRock->render(getMemDC(), _rcRock.left, _rcRock.top);


	_pWidth->render(getMemDC(), WINSIZEX - (TILESIZE * 3), TILESIZE * 10);
	_pHeight->render(getMemDC(), WINSIZEX - (TILESIZE * 3), TILESIZE * 11);


	_btnSave->render(getMemDC());
	_btnLoad->render(getMemDC());
	_btnWidthAdd->render(getMemDC());
	_btnWidthSub->render(getMemDC());
	_btnHeightAdd->render(getMemDC());
	_btnHeightSub->render(getMemDC());
}

void SCENEMAPTOOL::save()
{
	_pMapTool->save();
}

void SCENEMAPTOOL::load()
{
	_pMapTool->load();
}

void SCENEMAPTOOL::addWidth()
{
	_pMapTool->mapResize(_pMapTool->getMapCountX() + 1, _pMapTool->getMapCountY());
}

void SCENEMAPTOOL::subWidth()
{
	_pMapTool->mapResize(_pMapTool->getMapCountX() - 1, _pMapTool->getMapCountY());
}

void SCENEMAPTOOL::addHeight()
{
	_pMapTool->mapResize(_pMapTool->getMapCountX(), _pMapTool->getMapCountY() + 1);
}

void SCENEMAPTOOL::subHeight()
{
	_pMapTool->mapResize(_pMapTool->getMapCountX(), _pMapTool->getMapCountY() - 1);

}
