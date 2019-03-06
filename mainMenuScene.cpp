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
	//_pScrollBtn = new SCROLLBUTTON();
	//메인 레이어
	_pBtnMapTool = new button();
	_pBtnSingleGame = new button();
	_pBtnExit = new button();

	_pBtnMapTool->init("btnMapTool", WINSIZEX / 2 - 112, WINSIZEY / 2, bind(&SCENEMAINMENU::changeMapToolScene, this));
	_pBtnSingleGame->init("btnSingleGame", WINSIZEX / 2 - 112, WINSIZEY / 2 + 40, bind(&SCENEMAINMENU::changeGameSettingLayer, this));
	_pBtnExit->init("btnExit", WINSIZEX / 2 - 112, WINSIZEY / 2 + 80, bind(&SCENEMAINMENU::exit, this));

	//게임세팅 레이어
	_pResourceDegreeBtn = new SCROLLBUTTON();
	_pRaceBtn = new SCROLLBUTTON();
	_pGameStart = new button();
	_pReturnMainMenu = new button();


	_pResourceDegreeBtn->init(WINSIZEX / 4, WINSIZEY / 2, 112, 28, 3);
	_pRaceBtn->init((WINSIZEX / 2), WINSIZEY / 2, 112, 28, 3);
	_pGameStart->init("btnStartGame", WINSIZEX - 400, WINSIZEY / 4 * 3, bind(&SCENEMAINMENU::changeGameScene, this));
	_pReturnMainMenu->init("btnBack", WINSIZEX - 400, (WINSIZEY / 4 * 3) + 50, bind(&SCENEMAINMENU::changeMainmenuLayer, this));


	_pResourceDegreeBtn->addBtn("sbtnHuge", bind(&SCENEMAINMENU::nullCallbackFunction, this));
	_pResourceDegreeBtn->addBtn("sbtnNormal", bind(&SCENEMAINMENU::nullCallbackFunction, this));
	_pResourceDegreeBtn->addBtn("sbtnThin", bind(&SCENEMAINMENU::nullCallbackFunction, this));

	_pRaceBtn->addBtn("sbtnOrc", bind(&SCENEMAINMENU::nullCallbackFunction, this));
	_pRaceBtn->addBtn("sbtnHuman", bind(&SCENEMAINMENU::nullCallbackFunction, this));


	_eLayer = SCENEMAINMENU::LAYER::E_MAINMENU;
	return S_OK;
}

void SCENEMAINMENU::release()
{
}

void SCENEMAINMENU::update()
{
	if (_eLayer == SCENEMAINMENU::LAYER::E_MAINMENU)
	{
		updateMainMenuLayer();
	}
	else
	{
		updateSingleGameSettingLayer();
	}
}

void SCENEMAINMENU::render()
{
	IMAGEMANAGER->render("main", getMemDC());
	if (_eLayer == SCENEMAINMENU::LAYER::E_MAINMENU)
	{
		renderMainMenuLayer();
	}
	else
	{
		renderSingleGameSettingLayer();
	}

}

void SCENEMAINMENU::updateMainMenuLayer()
{
	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		changeMapToolScene();
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		exit();
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		changeGameSettingLayer();
	}

	_pBtnMapTool->update();
	_pBtnSingleGame->update();
	_pBtnExit->update();
}

void SCENEMAINMENU::updateSingleGameSettingLayer()
{


	_pResourceDegreeBtn->update();
	_pRaceBtn->update();


	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		changeMainmenuLayer();
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		changeGameScene();
	}

	_pGameStart->update();
	_pReturnMainMenu->update();
}

void SCENEMAINMENU::renderMainMenuLayer()
{
	_pBtnMapTool->render(getMemDC());
	_pBtnSingleGame->render(getMemDC());
	_pBtnExit->render(getMemDC());

}

void SCENEMAINMENU::renderSingleGameSettingLayer()
{
	_pResourceDegreeBtn->render(getMemDC());
	_pRaceBtn->render(getMemDC());
	_pGameStart->render(getMemDC());
	_pReturnMainMenu->render(getMemDC());
}

void SCENEMAINMENU::changeMapToolScene()
{
	SCENEMANAGER->changeScene("mapTool");
}

void SCENEMAINMENU::exit()
{
	SendMessage(_hWnd, WM_DESTROY, 1, 0);
}

void SCENEMAINMENU::changeGameSettingLayer()
{
	_eLayer = SCENEMAINMENU::LAYER::E_GAMESEETING;
}

void SCENEMAINMENU::nullCallbackFunction()
{
}

void SCENEMAINMENU::changeGameScene()
{
	SCENEMANAGER->changeScene("gameScene");

}

void SCENEMAINMENU::changeMainmenuLayer()
{
	_eLayer = SCENEMAINMENU::LAYER::E_MAINMENU;

}

