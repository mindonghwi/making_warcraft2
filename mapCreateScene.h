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

	image*		_pRock;
	RECT		_rcRock;

	button*		_btnSave;
	button*		_btnLoad;

	image*		_pWidth;
	button*		_btnWidthAdd;
	button*		_btnWidthSub;

	image*		_pHeight;
	button*		_btnHeightAdd;
	button*		_btnHeightSub;

	RECT		_rcClient;
	POINT		_ptLeftTop;
	POINT		_ptRightBottom;


public:
	SCENEMAPTOOL();
	~SCENEMAPTOOL();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


public:
	void save();
	void load();
	void addWidth();
	void subWidth();
	void addHeight();
	void subHeight();
};