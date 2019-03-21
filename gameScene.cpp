#include "stdafx.h"
#include "gameScene.h"
#include "user.h"

#include "com.h"
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
	_pBulletMgr = new BULLETMGR();
	_pCom = new COM();

	//player link other
	_pPlayer->setLinkCamera(_pCamera);
	_pPlayer->setLinkAstar(_pAstar);
	_pPlayer->setLinkMap(_pMap);
	_pPlayer->setLinkResourceMgr(_pResourceMgr);
	_pPlayer->setLinkBulletMgr(_pBulletMgr);
	_pPlayer->setOpponent(_pCom);

	//com link other
	_pCom->setLinkCamera(_pCamera);
	_pCom->setLinkAstar(_pAstar);
	_pCom->setLinkMap(_pMap);
	_pCom->setLinkResourceMgr(_pResourceMgr);
	_pCom->setLinkBulletMgr(_pBulletMgr);
	_pCom->setOpponent(_pPlayer);

	//resourceMgr link other
	_pResourceMgr->setLinkCamera(_pCamera);
	_pResourceMgr->setLinkMap(_pMap);

	//Map link other
	_pMap->setLinkCamera(_pCamera);
	_pMap->setLinkResourceMgr(_pResourceMgr);

	//uiMGr link
	_pUiMgr->setLinkPlayer(_pPlayer);

	//bulletMgr linl
	_pBulletMgr->setLinkCamera(_pCamera);
	_pBulletMgr->setLinkPlayer(_pPlayer);
	_pBulletMgr->setLinkCom(_pCom);

	_pMap->init("map");
	_pCamera->init(WINSIZEX/2, WINSIZEY / 2,WINSIZEX,WINSIZEY,_pMap->getMapCountX() * TILESIZE, _pMap->getMapCountY() * TILESIZE);

	_pCamera->setLimitToTile(_pMap->getMapCountX() , _pMap->getMapCountY() );
	_pCamera->outOfRange();

	_pMap->drawMap(_pCamera->getBackGoroundBuffer());
	_pCamera->drawMiniMap();


	//player init
	_pPlayer->init(static_cast<float>(TILESIZE * 5 + 16), static_cast<float>(TILESIZE * 12 + 16));
	_pPlayer->setGold(5000);
	_pPlayer->setOil(5000);
	_pPlayer->setTree(2000);

	//_pCom init
	_pCom->init(static_cast<float>(TILESIZE * 50 + 16), static_cast<float>(TILESIZE * 25 + 16));
	_pCom->setGold(5000);
	_pCom->setOil(5000);
	_pCom->setTree(2000);

	_pAstar->init(8, _pMap);


	//astar link other
	_pAstar->setLinkUnitMgr(_pPlayer);

	_pUiMgr->init();
	
	_pBulletMgr->init();

	_pBulletMgr->addBullet("arrows", 1000, "arrow", 100.0f, 0.4f, _pPlayer->getUnitMgr()->getAttack(UNIT::E_UNIT::E_ARCHER));
	_pBulletMgr->addBullet("ballises", 1000, "ballis", 100.0f, 1.0f, _pPlayer->getUnitMgr()->getAttack(UNIT::E_UNIT::E_BALLISTA));
	_pBulletMgr->addBullet("bullet", 1000, "bullet", 100.0f, 0.9f, _pPlayer->getUnitMgr()->getAttack(UNIT::E_UNIT::E_BATTLESHIP));
	_pBulletMgr->addBullet("fireBall", 1000, "fireBall", 100.0f, 0.5f, _pPlayer->getUnitMgr()->getAttack(UNIT::E_UNIT::E_MAGICIAN));
	//_pBulletMgr->addBullet("axe", 1000, "axe", 5.0f, 0.3f, _pPlayer->getUnitMgr()->getAttack(UNIT::E_UNIT::E_FLYER));
	_pBulletMgr->addGryphonBullet("axe", 1000, "axe", 3.0f, 120.0f, _pPlayer->getUnitMgr()->getAttack(UNIT::E_UNIT::E_FLYER));

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
	
	_pCom->update();

	_pBulletMgr->update();
	_pUiMgr->update();


}

void SCENEGAME::render()
{
	_pCamera->renderinit();
	//_pMap->render(_pCamera->getMemDC());


	_pCamera->render(getMemDC());
	_pPlayer->render(_pCamera->getMemDC());

	_pCamera->renderFin(getMemDC());
	IMAGEMANAGER->findImage("edge")->render(getMemDC());

	_pCamera->renderMiniMap(getMemDC());

	_pUiMgr->render(getMemDC());
}
