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

	_pMapTool->init(128, 128, 32);
	_pCamera->init(WINSIZEX/2,WINSIZEY/2, WINSIZEX-100,WINSIZEY, 128 * 32, 128 * 32);


	//�ķ�Ʈ
	_pGround = IMAGEMANAGER->findImage("ground");
	_pDirt = IMAGEMANAGER->findImage("dirt");
	_pWater = IMAGEMANAGER->findImage("water");

	_rcGround = RectMake(WINSIZEX - 32, 0, 32, 32);
	_rcDirt = RectMake(WINSIZEX - 32, 32, 32, 32);
	_rcWater = RectMake(WINSIZEX - 32, 64, 32, 32);

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
	_pMapTool->update();
	_pCamera->update();



	//�ķ�Ʈ Ŭ��
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rcGround,_ptMouse))
		{
			_pMapTool->setTerrian(TILE::E_TERRIAN::GROUND);
		}
		else if (PtInRect(&_rcDirt, _ptMouse))
		{
			_pMapTool->setTerrian(TILE::E_TERRIAN::DIRT);
		}
		else if (PtInRect(&_rcWater, _ptMouse))
		{
			_pMapTool->setTerrian(TILE::E_TERRIAN::WATER);
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

}
