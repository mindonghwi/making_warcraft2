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
	
	RESOURCES::OBJECT::setPosX(static_cast<float>(nLeft + 32 + 16));
	RESOURCES::OBJECT::setPosY(static_cast<float>(nTop + 32 + 16));
	RESOURCES::OBJECT::setPosZ(0);
	RESOURCES::OBJECT::setWidth(96);
	RESOURCES::OBJECT::setHeight(96);
	RESOURCES::OBJECT::settingRect();
	RESOURCES::OBJECT::setImage(IMAGEMANAGER->findImage("goldMine"));

	_nHarvestCount = 0;
	_nMaxHarvestCount = 1;
}

void GOLDMINE::update()
{
	_pCamera->pushRenderObject(this);
}

void GOLDMINE::release()
{
	RESOURCES::OBJECT::setImage(nullptr);
}

void GOLDMINE::render(HDC hdc)
{
	RESOURCES::OBJECT::getImage()->renderCenter(hdc, static_cast<int>(OBJECT::getPosX()), static_cast<int>(OBJECT::getPosY()));
	DrawEdge(hdc, OBJECT::getRect(), BDR_RAISEDOUTER, BF_FLAT | BF_TOPLEFT | BF_BOTTOMRIGHT);

}
