#include "stdafx.h"
#include "gameScene.h"
#include "user.h"
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
	_pPlayer = new USER();
	_pAstar = new ASTAR();
	_pUiMgr = new UIMGR();
	


	//player link other
	_pPlayer->setLinkCamera(_pCamera);
	_pPlayer->setLinkAstar(_pAstar);
	_pPlayer->setLinkMap(_pMap);
	_pPlayer->setLinkResourceMgr(_pResourceMgr);




	//resourceMgr link other
	_pResourceMgr->setLinkCamera(_pCamera);
	_pResourceMgr->setLinkMap(_pMap);

	//Map link other
	_pMap->setLinkCamera(_pCamera);
	_pMap->setLinkResourceMgr(_pResourceMgr);

	//uiMGr link
	_pUiMgr->setLinkPlayer(_pPlayer);


	_pMap->init("map");
	_pCamera->init(WINSIZEX/2, WINSIZEY / 2,WINSIZEX,WINSIZEY,_pMap->getMapCountX() * TILESIZE, _pMap->getMapCountY() * TILESIZE);

	_pCamera->setLimitToTile(_pMap->getMapCountX() , _pMap->getMapCountY() );
	_pCamera->outOfRange();

	_pMap->drawMap(_pCamera->getBackGoroundBuffer());
	_pCamera->drawMiniMap();


	//player init
	_pPlayer->init(static_cast<float>(TILESIZE * 19 + 16), static_cast<float>(TILESIZE * 11 + 16));
	_pPlayer->setGold(5000);
	_pPlayer->setOil(5000);
	_pPlayer->setTree(2000);



	_pAstar->init(8, _pMap);


	//astar link other
	_pAstar->setLinkUnitMgr(_pPlayer);

	_pUiMgr->init();
	
	
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


	_pUiMgr->release();
	delete _pUiMgr;
	_pUiMgr = nullptr;
}

void SCENEGAME::update()
{
	_pCamera->update();
	_pResourceMgr->update();
	_pPlayer->update();
	
	_pUiMgr->update();
}

void SCENEGAME::render()
{
	_pCamera->renderinit();


	_pPlayer->render(_pCamera->getMemDC());
	_pCamera->render(getMemDC());

	IMAGEMANAGER->findImage("edge")->render(getMemDC());

	_pCamera->renderMiniMap(getMemDC());

	_pUiMgr->render(getMemDC());
}
