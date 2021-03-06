#include "stdafx.h"
#include "oliPatch.h"

OILPATCH::OILPATCH()
{
}

OILPATCH::~OILPATCH()
{
}

void OILPATCH::init(int nLeft, int nTop)
{
	OBJECT::setPosX(static_cast<float>(nLeft + 32 + 16));
	OBJECT::setPosY(static_cast<float>(nTop + 32 + 16));
	RESOURCES::OBJECT::setPosZ(0);
	OBJECT::setWidth(96);
	OBJECT::setHeight(96);
	OBJECT::settingRect();
	OBJECT::setImage(IMAGEMANAGER->findImage("oil"));
	
	_nHarvestCount = 0;
	_nMaxHarvestCount = 100;
}

void OILPATCH::update()
{


	_pCamera->pushRenderObject(this);

}

void OILPATCH::release()
{
	OBJECT::setImage(nullptr);
}

void OILPATCH::render(HDC hdc)
{
	OBJECT::getImage()->renderCenter(hdc, static_cast<int>(OBJECT::getPosX()), static_cast<int>(OBJECT::getPosY()));
}
