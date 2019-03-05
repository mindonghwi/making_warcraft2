#include "stdafx.h"
#include "coverScene.h"

SCENECOVER::SCENECOVER()
{
}

SCENECOVER::~SCENECOVER()
{
}

HRESULT SCENECOVER::init()
{



	return S_OK;
}

void SCENECOVER::release()
{
}

void SCENECOVER::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SCENEMANAGER->changeScene("menuScene");
	}
}

void SCENECOVER::render()
{
	IMAGEMANAGER->render("warcraftMainView", getMemDC());
}
