#include "stdafx.h"
#include "mainMenuScene.h"

SCENEMAINMENU::SCENEMAINMENU()
{
}

SCENEMAINMENU::~SCENEMAINMENU()
{
}

HRESULT SCENEMAINMENU::init()
{
	_pScrollBtn = new SCROLLBUTTON();
	


	//IMAGEMANAGER->addFrameImage("btnSingleGame"
	//IMAGEMANAGER->addFrameImage("btnExit", "res
	//IMAGEMANAGER->addFrameImage("btnMapTool", "
	_pScrollBtn->init(WINSIZEX / 2, WINSIZEY / 2, 224, 28, 2);
	_pScrollBtn->addBtn("btnMapTool",bind(&SCENEMAINMENU::changeMapToolScene,this));
	_pScrollBtn->addBtn("btnSingleGame", bind(&SCENEMAINMENU::changeMapToolScene, this));
	_pScrollBtn->addBtn("btnExit", bind(&SCENEMAINMENU::exit, this));

	return S_OK;
}

void SCENEMAINMENU::release()
{
}

void SCENEMAINMENU::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD9))
	{
		SCENEMANAGER->changeScene("mapTool");
	}

	_pScrollBtn->update();
}

void SCENEMAINMENU::render()
{
	IMAGEMANAGER->render("main", getMemDC());
	_pScrollBtn->render(getMemDC());
}

void SCENEMAINMENU::updateMainMenuLayer()
{
}

void SCENEMAINMENU::updateSingleGameSettingLayer()
{
}

void SCENEMAINMENU::renderMainMenuLayer()
{
}

void SCENEMAINMENU::renderSingleGameSettingLayer()
{
}

void SCENEMAINMENU::changeMapToolScene()
{
	//SCENEMANAGER->changeScene("mapTool");
}

void SCENEMAINMENU::exit()
{
	//SendMessage(_hWnd, WM_DESTROY, 1, 0);
}
