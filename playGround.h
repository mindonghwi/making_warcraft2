#pragma once
#include "gameNode.h"
#include "mapCreateScene.h"
#include "coverScene.h"
#include "mainMenuScene.h"
#include "gameScene.h"
class playGround : public gameNode
{
private:
	gameNode*	_pMapCreate;
	gameNode*	_pCoverScene;
	gameNode*	_pMainMenuScene;
	gameNode*	_pGameScene;

	HFONT		_hFont;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	playGround();
	~playGround();

private:
	void	loadImage();
};

