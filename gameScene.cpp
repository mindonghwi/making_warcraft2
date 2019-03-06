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
	_pResourceMgr = new RESOURCEMGR();

	//tset
	_pWorkMan = new WORKMAN();
	_pWorkMan->setLinkCamera(_pCamera);
	_pWorkMan->init(WINSIZEX/2, WINSIZEY/2, 64, 64);


	_pResourceMgr->setLinkCamera(_pCamera);
	_pResourceMgr->setLinkMap(_pMap);
	_pMap->setLinkCamera(_pCamera);
	_pMap->setLinkResourceMgr(_pResourceMgr);
	
	_pMap->init("map");
	_pCamera->init(WINSIZEX/2, WINSIZEY / 2,WINSIZEX,WINSIZEY,_pMap->getMapCountX() * TILESIZE, _pMap->getMapCountY() * TILESIZE);

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
	_pResourceMgr->update();
	_pWorkMan->update();
}

void SCENEGAME::render()
{
	_pCamera->renderinit();

	_pCamera->render(getMemDC());
}
