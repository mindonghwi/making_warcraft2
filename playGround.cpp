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
	IMAGEMANAGER->addFrameImage("mapSprites", "resource/mapSprites.bmp", 640, 160, 20, 5, true, Mins::getMazenta());
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
	IMAGEMANAGER->addFrameImage("peasantSprite", "resource/human/peasantSprite.bmp", 1280, 576, 20, 9, true, Mins::getMazenta());








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
