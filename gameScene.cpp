#include "stdafx.h"
#include "gameScene.h"

SCENEGAME::SCENEGAME()
{
}

SCENEGAME::~SCENEGAME()
{
}

HRESULT SCENEGAME::init()
{
	_pMap = new MAP();
	_pCamera = new CAMERA();


	
	_pMap->init("map");
	_pCamera->init(WINSIZEX/2, WINSIZEY / 2,WINSIZEX,WINSIZEY,_pMap->getMapCountX() * TILESIZE, _pMap->getMapCountY() * TILESIZE);
	_pMap->setLinkCamera(_pCamera);

	_pCamera->setLimitToTile(_pMap->getMapCountX() , _pMap->getMapCountY() );
	_pCamera->outOfRange();

	_pMap->drawMap(_pCamera->getBackGoroundBuffer());


	return S_OK;
}

void SCENEGAME::release()
{
	_pMap->release();
	delete _pMap;
	_pMap = nullptr;

	_pCamera->release();
	delete _pCamera;
	_pCamera = nullptr;
}

void SCENEGAME::update()
{
	_pCamera->update();
}

void SCENEGAME::render()
{
	_pCamera->renderinit();

	_pCamera->render(getMemDC());
}
