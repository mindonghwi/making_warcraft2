#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//이미지 로드용
void playGround::loadImage()
{
	IMAGEMANAGER->addFrameImage("wall", "resource/wall.bmp", TILESIZE * 16, TILESIZE, 16, 1, true, Mins::getMazenta());

	IMAGEMANAGER->addFrameImage("mapSprites", "resource/mapSprite.bmp", 640, 160, 20, 5, true, Mins::getMazenta());
	
	
	IMAGEMANAGER->addFrameImage("ground", "resource/ground.bmp", TILESIZE, TILESIZE, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("dirt", "resource/dirt.bmp", TILESIZE, TILESIZE, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("water", "resource/water.bmp", TILESIZE, TILESIZE, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("goldMineIcon", "resource/goldMineIcon.bmp", TILESIZE, TILESIZE, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("goldMine", "resource/goldMine.bmp", 96, 96, 1, 1, true, Mins::getMazenta());

	IMAGEMANAGER->addFrameImage("treeIcon", "resource/treeIcon.bmp", TILESIZE, TILESIZE, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("tree", "resource/tree.bmp", 96, 96, 1, 1, true, Mins::getMazenta());

	IMAGEMANAGER->addFrameImage("oilIcon", "resource/oilIcon.bmp", TILESIZE, TILESIZE, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("oil", "resource/oil.bmp", 96, 96, 1, 1, true, Mins::getMazenta());

	IMAGEMANAGER->addFrameImage("rockIcon", "resource/rockIcon.bmp", TILESIZE, TILESIZE, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("rock", "resource/rock.bmp", TILESIZE * 16, TILESIZE, 16, 1, true, Mins::getMazenta());


	IMAGEMANAGER->addFrameImage("btnAdd", "resource/icon/btnAdd.bmp", TILESIZE, TILESIZE, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("btnSub", "resource/icon/btnSub.bmp", TILESIZE, TILESIZE, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("btnSave", "resource/icon/btnSave.bmp", TILESIZE, TILESIZE, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("btnLoad", "resource/icon/btnLoad.bmp", TILESIZE, TILESIZE, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("iconHeight", "resource/icon/iconHeight.bmp", TILESIZE, TILESIZE, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("iconWidth", "resource/icon/iconWidth.bmp", TILESIZE, TILESIZE, 1, 1, true, Mins::getMazenta());

	IMAGEMANAGER->addImage("warcraftMainView", "resource/wallpaper/warcraftMainView.bmp", WINSIZEX, WINSIZEY, true, Mins::getMazenta());
	IMAGEMANAGER->addImage("main", "resource/wallpaper/main.bmp", WINSIZEX, WINSIZEY, true, Mins::getMazenta());


	IMAGEMANAGER->addFrameImage("btnSingleGame", "resource/wallpaper/btnSingleGame.bmp", 224, 28, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("btnExit", "resource/wallpaper/btnExit.bmp", 224, 28, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("btnMapTool", "resource/wallpaper/btnMapTool.bmp", 224, 28, 1, 1, true, Mins::getMazenta());

	IMAGEMANAGER->addFrameImage("sbtnHuge", "resource/wallpaper/sbtnHuge.bmp", 112, 28, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("sbtnHuman", "resource/wallpaper/sbtnHuman.bmp", 112, 28, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("sbtnNormal", "resource/wallpaper/sbtnNormal.bmp", 112, 28, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("sbtnOrc", "resource/wallpaper/sbtnOrc.bmp", 112, 28, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("sbtnThin", "resource/wallpaper/sbtnThin.bmp", 112, 28, 1, 1, true, Mins::getMazenta());


	IMAGEMANAGER->addFrameImage("btnBack", "resource/wallpaper/btnBack.bmp", 224, 28, 1, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("btnStartGame", "resource/wallpaper/btnStartGame.bmp", 224, 28, 1, 1, true, Mins::getMazenta());



	//유닛
	//barrocks
	IMAGEMANAGER->addFrameImage("peasantSprite", "resource/human/peasantSprite.bmp", 1280, 576, 20, 9, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("ballistaSprite", "resource/human/ballistaSprite.bmp", 480, 768, 5, 8, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("elvenArcherSprite", "resource/human/elvenArcherSprite.bmp", 672, 864, 7, 9, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("knightSprite", "resource/human/knightSprite.bmp", 864, 864, 9, 9, true, Mins::getMazenta());
	
	//magician
	IMAGEMANAGER->addFrameImage("magicianSprite", "resource/human/magicianSprite.bmp", 864, 864, 9, 9, true, Mins::getMazenta());

	//factory
	IMAGEMANAGER->addFrameImage("gnomishFlying", "resource/human/gnomishFlying.bmp", 192, 864, 2, 9, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("dwavenDemolition", "resource/human/dwavenDemolition.bmp", 768, 864, 8, 9, true, Mins::getMazenta());

	//ship
	IMAGEMANAGER->addFrameImage("battleShipSprte", "resource/human/battleShipSprte.bmp", 288, 768, 3, 8, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("elvenDestroyerSprite", "resource/human/elvenDestroyerSprite.bmp", 288, 768, 3, 8, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("gnomishSubmarine", "resource/human/gnomishSubmarine.bmp", 288, 768, 3, 8, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("transportSprite", "resource/human/transportSprite.bmp", 288, 768, 3, 8, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("oiltankerSprite", "resource/human/oiltankerSprite.bmp", 384, 768, 4, 8, true, Mins::getMazenta());

	IMAGEMANAGER->addFrameImage("gryphonRiderSprite", "resource/human/gryphonRiderSprite.bmp", 672, 864, 7, 9, true, Mins::getMazenta());

	
	//건물
	IMAGEMANAGER->addFrameImage("town",				"resource/human/build/townhall.bmp",512,128,4,1,true,Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("keep",				"resource/human/build/keep.bmp", 256, 128, 2, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("castle",			"resource/human/build/castle.bmp", 256, 128, 2, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("barracks",			"resource/human/build/barracks.bmp", 384, 96, 4, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("miil",				"resource/human/build/branchOffice.bmp", 384, 96, 4, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("church",			"resource/human/build/church.bmp", 384, 96, 4, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("gnomishSanctuary", "resource/human/build/goblinSanctuary.bmp", 384, 96, 4, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("gryphonSanctuary", "resource/human/build/gryphonSanctuary.bmp", 384, 96, 4, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("mageTemple",		"resource/human/build/mageTemple.bmp", 384, 96, 4, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("smithy",			"resource/human/build/smithy.bmp", 384, 96, 4, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("stall",			"resource/human/build/stall.bmp", 384, 96, 4, 1, true, Mins::getMazenta());

	IMAGEMANAGER->addFrameImage("farm",				"resource/human/build/farm.bmp", 256, 64, 4, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("scoutTower",		"resource/human/build/tower01.bmp", 256, 64, 4, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("tower02",			"resource/human/build/tower02.bmp", 128, 64, 4, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("tower03",			"resource/human/build/tower03.bmp", 128, 64, 4, 1, true, Mins::getMazenta());

	IMAGEMANAGER->addFrameImage("dockyard",			"resource/human/build/dockyard.bmp", 192, 96, 4, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("yard02",			"resource/human/build/yard02.bmp", 192, 96, 4, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("yard03",			"resource/human/build/yard03.bmp", 192, 96, 4, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("oilRefinery",		"resource/human/build/oilRefinery.bmp", 288, 96, 4, 1, true, Mins::getMazenta());


	//ui
	IMAGEMANAGER->addImage("card", "resource/icon/UI/card.bmp", 54, 53, true, Mins::getMazenta());
	IMAGEMANAGER->addImage("UiGold", "resource/icon/UI/card.bmp", 54, 53, true, Mins::getMazenta());
	IMAGEMANAGER->addImage("UiTree", "resource/icon/UI/card.bmp", 54, 53, true, Mins::getMazenta());
	IMAGEMANAGER->addImage("UiOil", "resource/icon/UI/card.bmp", 54, 53, true, Mins::getMazenta());
	IMAGEMANAGER->addImage("UiPopulation", "resource/icon/UI/card.bmp", 54, 53, true, Mins::getMazenta());


}



HRESULT playGround::init()
{
	gameNode::init(true);

	AddFontResource("fonts/BMJUA_ttf.ttf");
	_hFont = CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0,
		DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("fonts/BMJUA_ttf.ttf"));

	loadImage();


	_pMapCreate = new SCENEMAPTOOL();
	_pCoverScene = new SCENECOVER();
	_pMainMenuScene = new SCENEMAINMENU();
	_pGameScene = new SCENEGAME();

	SCENEMANAGER->addScene("mapTool", _pMapCreate);
	SCENEMANAGER->addScene("menuScene", _pMainMenuScene);
	SCENEMANAGER->addScene("coverScene", _pCoverScene);
	SCENEMANAGER->addScene("gameScene", _pGameScene);

	SCENEMANAGER->changeScene("coverScene");


	SCENEMANAGER->changeScene("gameScene");
	//SCENEMANAGER->changeScene("mapTool");


	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	_pMapCreate = nullptr;
}


void playGround::update()
{
	gameNode::update();



	SCENEMANAGER->update();

}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	HFONT hOldFont = (HFONT)SelectObject(getMemDC(), _hFont);
	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	SelectObject(getMemDC(), hOldFont);
	DeleteObject(hOldFont);

	//===========================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
