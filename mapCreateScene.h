#pragma once
#include "mapTool.h"
#include "camera.h"
#include "stdafx.h"
#include "gameNode.h"
#include "button.h"

class SCENEMAPTOOL : public gameNode{
private:
	MAPTOOL*	_pMapTool;
	CAMERA*		_pCamera;	//Ä«¸Þ¶ó


	image*		_pGround;
	image*		_pDirt;
	image*		_pWater;

	RECT		_rcGround;
	RECT		_rcDirt;
	RECT		_rcWater;

	image*		_pGoldMineIcon;
	RECT		_rcGoldMine;

	image*		_pTree;
	RECT		_rcTree;

	image*		_pOilPatch;
	RECT		_rcOilPatch;

public:
	SCENEMAPTOOL();
	~SCENEMAPTOOL();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};