#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}



HRESULT playGround::init()
{
	gameNode::init(true);

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
