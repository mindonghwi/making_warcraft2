#pragma once
#include "gameNode.h"
#include "mapCreateScene.h"
#include "coverScene.h"
#include "mainMenuScene.h"

class playGround : public gameNode
{
private:
	gameNode*	_pMapCreate;
	gameNode*	_pCoverScene;
	gameNode*	_pMainMenuScene;
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

