#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

void playGround::loadImage()
{
	IMAGEMANAGER->addFrameImage("wall", "resource/wall.bmp", TILESIZE*16, TILESIZE, 16, 1, true, Mins::getMazenta());
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
}



HRESULT playGround::init()
{
	gameNode::init(true);
	loadImage();


	_pMapCreate = new SCENEMAPTOOL();

	SCENEMANAGER->addScene("mapTool", _pMapCreate);
	SCENEMANAGER->changeScene("mapTool");


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
	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	//===========================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
