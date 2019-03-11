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
	_pPlayer = new PLAYER();
	_pAstar = new ASTAR();


	//player link other
	_pPlayer->setLinkCamera(_pCamera);
	_pPlayer->setLinkAstar(_pAstar);

	//resourceMgr link other
	_pResourceMgr->setLinkCamera(_pCamera);
	_pResourceMgr->setLinkMap(_pMap);

	//Map link other
	_pMap->setLinkCamera(_pCamera);
	_pMap->setLinkResourceMgr(_pResourceMgr);



	_pMap->init("map");
	_pCamera->init(WINSIZEX/2, WINSIZEY / 2,WINSIZEX,WINSIZEY,_pMap->getMapCountX() * TILESIZE, _pMap->getMapCountY() * TILESIZE);

	_pCamera->setLimitToTile(_pMap->getMapCountX() , _pMap->getMapCountY() );
	_pCamera->outOfRange();

	_pMap->drawMap(_pCamera->getBackGoroundBuffer());
	_pCamera->drawMiniMap();


	_pPlayer->init();

	_pAstar->init(8, _pMap);


	//astar link other
	_pAstar->setLinkUnitMgr(_pPlayer);
	_pPlayer->setLinkMap(_pMap);



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

	_pPlayer->release();
	delete _pPlayer;
	_pPlayer = nullptr;
}

void SCENEGAME::update()
{
	_pCamera->update();
	_pResourceMgr->update();
	_pPlayer->update();
}

void SCENEGAME::render()
{
	_pCamera->renderinit();


	_pPlayer->render(_pCamera->getMemDC());
	_pCamera->render(getMemDC());
	_pCamera->renderMiniMap(getMemDC());
}
