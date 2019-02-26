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



	_pMapTool->init(30, 30, 32);
	_pCamera->init(WINSIZEX/2,WINSIZEY/2, WINSIZEX,WINSIZEY,256*32,256*32);





	


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
}

void SCENEMAPTOOL::render()
{
	_pCamera->renderinit();
	_pMapTool->render(_pCamera->getMemDC());
	_pCamera->render(getMemDC());
}
