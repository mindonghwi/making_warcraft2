#include "stdafx.h"
#include "goldMine.h"

GOLDMINE::GOLDMINE():
	_nResourceCount(0)
{
}

GOLDMINE::~GOLDMINE()
{
}

void GOLDMINE::init(int nLeft, int nTop)
{
	OBJECT::setPosX(static_cast<float>(nLeft + 32 + 16));
	OBJECT::setPosY(static_cast<float>(nTop + 32 + 16));
	OBJECT::setWidth(96);
	OBJECT::setHeight(96);
	OBJECT::settingRect();
	OBJECT::setImage(IMAGEMANAGER->findImage("goldMine"));
}

void GOLDMINE::update()
{
	_pCamera->pushRenderObject(this);
}

void GOLDMINE::release()
{
	OBJECT::setImage(nullptr);
}

void GOLDMINE::render(HDC hdc)
{
	OBJECT::getImage()->renderCenter(hdc, static_cast<int>(OBJECT::getPosX()), static_cast<int>(OBJECT::getPosY()));
}