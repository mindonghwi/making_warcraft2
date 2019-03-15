#include "stdafx.h"
#include "tree.h"

TREE::TREE()
{
}

TREE::~TREE()
{
}

void TREE::init(int nLeft, int nTop)
{
	OBJECT::setPosX(static_cast<float>(nLeft + 32 + 16));
	OBJECT::setPosY(static_cast<float>(nTop + 32 + 16));
	RESOURCES::OBJECT::setPosZ(0);
	OBJECT::setWidth(96);
	OBJECT::setHeight(96);
	OBJECT::settingRect();
	OBJECT::setImage(IMAGEMANAGER->findImage("tree"));

	_nHarvestCount = 0;
	_nMaxHarvestCount = 2;
}

void TREE::update()
{
	_pCamera->pushRenderObject(this);

}

void TREE::release()
{
	OBJECT::setImage(nullptr);
}

void TREE::render(HDC hdc)
{
	OBJECT::getImage()->renderCenter(hdc, static_cast<int>(OBJECT::getPosX()), static_cast<int>(OBJECT::getPosY()));

}
