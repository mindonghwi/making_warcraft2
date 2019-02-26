#pragma once
#include "mapTool.h"
#include "camera.h"
#include "stdafx.h"
#include "gameNode.h"
class SCENEMAPTOOL : public gameNode{
private:
	MAPTOOL*	_pMapTool;
	CAMERA*		_pCamera;	//Ä«¸Þ¶ó

public:
	SCENEMAPTOOL();
	~SCENEMAPTOOL();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};